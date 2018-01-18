(* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is TurboPower LockBox
 *
 * The Initial Developer of the Original Code is
 * TurboPower Software
 *
 * Portions created by the Initial Developer are Copyright (C) 1997-2002
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s): Sebastian Zierer, Jarto Tarpio
 *
 * ***** END LICENSE BLOCK ***** *)
{*********************************************************}
{*                  LBRANDOM.PAS 2.09                    *}
{*     Copyright (c) 2002 TurboPower Software Co         *}
{*                 All rights reserved.                  *}
{*********************************************************}

{$I LockBox.inc}
{$IFDEF MSWINDOWS}
  {$WRITEABLECONST ON}
{$ENDIF}

unit LbRandom;

interface
uses
{$IFDEF MSWINDOWS}
  Windows, { only needed for get tick count }
{$ENDIF}
{$IFDEF POSIX}
  Types,
{$ENDIF}
{$IFDEF UsingCLX}
  libc,
{$ENDIF}
  Sysutils,
  SyncObjs,
  LbCipher;

const
  tmp = 1;

{$IFNDEF FPC}
type
  PtrInt = Integer;
  PtrUInt = Cardinal;
{$ENDIF}

{ TLbRandomGenerator }
type
  TLbRandomGenerator = class
    private
      RandCount : Integer;
      Seed : TMD5Digest;
      procedure ChurnSeed;
    public
      constructor Create;
      destructor Destroy; override;
      procedure RandomBytes( var buff; len : DWORD );
  end;


{ TLbRanLFS }
type
  TLbRanLFS = class
    private
      ShiftRegister : DWORD;
      procedure SetSeed;
      function LFS : byte;
    public
      constructor Create;
      destructor Destroy; override;
      procedure FillBuf( var buff; len : DWORD );
  end;

{ TSha1HashRandom }

//This is a fallback random number generator, which will be used by
//LbSysRandom32 and LbSysRandomByte if a random number can't be produced
//from a cryptographically secure source.

  TSha1HashRandom = class
  private
    FCounter: Int64;
    FRandomPos: Integer;
    FHashSource: String;
    FDigest: TSHA1Digest;
    FResultPos: pDword;
    FLock: TCriticalSection;
  public
    constructor Create;
    destructor Destroy; override;
    function Random32: DWord;
  end;

function LbSysRandom32: DWORD;
function lbSysRandomByte: Byte;
procedure lbSysRandomBuff( var buff; len : DWORD );

implementation

uses
  Classes {$IFDEF MACOS}, Macapi.CoreServices{$ENDIF};

var
  FLbFallbackRandomGenerator: TSha1HashRandom;


{$IFDEF HAS_ARC4RANDOM}
function arc4random: LongWord; cdecl; external '/usr/lib/libc.dylib' name '_arc4random';
{$ENDIF}

function LbDevRandom32(const FileName: string; out RandomNumber: DWORD): Boolean;
//  Get a 32 bit random number from /dev/random or /dev/urandom
var
  Stream: TFileStream;
begin
  Stream := TFileStream.Create(FileName,fmOpenRead);
  try
    RandomNumber := 0;
    Stream.Read(RandomNumber, SizeOf(RandomNumber));
    Result := True;
  finally
    Stream.Free;
  end;
end;

function LbDevRandomByte(const FileName: string; out RandomNumber: Byte): Boolean;
//  Get a 32 bit random number from /dev/random or /dev/urandom
var
  Stream: TFileStream;
begin
  Stream := TFileStream.Create(FileName,fmOpenRead);
  try
    RandomNumber := 0;
    Stream.Read(RandomNumber, SizeOf(RandomNumber));
    Result := True;
  finally
    Stream.Free;
  end;
end;

function lbSysRandomByte: Byte;
begin
{$IFDEF HAS_ARC4RANDOM}
  Result := arc4random and $FF;
  Exit;
{$ENDIF HAS_ARC4RANDOM}
{$IFDEF USE_DEV_RANDOM}
  if LbDevRandomByte('/dev/random', Result) then exit;
{$ENDIF}
{$IFDEF USE_DEV_URANDOM}
  if LbDevRandomByte('/dev/urandom', Result) then exit;
{$ENDIF}
  result:=FLbFallbackRandomGenerator.Random32 and $FF;
end;

function LbSysRandom32: DWORD;
//  This one returns 32 bit random numbers using available sources in the OS/Compiler.
begin
{$IFDEF HAS_ARC4RANDOM}
  Result := arc4random;
  Exit;
{$ENDIF}
{$IFDEF USE_DEV_RANDOM}
  if LbDevRandom32('/dev/random', Result) then exit;
{$ENDIF}
{$IFDEF USE_DEV_URANDOM}
  if LbDevRandom32('/dev/urandom', Result) then exit;
{$ENDIF}
  result:=FLbFallbackRandomGenerator.Random32;
end;

procedure lbSysRandomBuff( var buff; len : DWORD );
var i,c: DWord;
    pd: pDword;
begin
  c:=0; pd:=addr(buff);
  for i:=1 to (len div 4) do begin
    pd^:=LbSysRandom32;
    inc(pd); inc(c,4);
  end;
  while c<len do begin
    TByteArray(buff)[c]:=lbSysRandomByte;
    inc(c);
  end;
end;

{ == TLbRandomGenerator ==================================================== }
constructor TLbRandomGenerator.create;
begin
  inherited;
  ChurnSeed;
end;
{ -------------------------------------------------------------------------- }
destructor TLbRandomGenerator.Destroy;
begin
  RandCount := 0;
  FillChar( Seed, SizeOf( Seed ), $00 );
  inherited;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRandomGenerator.ChurnSeed;
var
  RandomSeed : array[ 0..15 ] of byte;
  Context : TMD5Context;
  lcg : TLbRanLFS;
  i : integer;
begin
  lcg := TLbRanLFS.Create;
  try
    lcg.FillBuf( RandomSeed, SizeOf( RandomSeed ));
    for i := 0 to 4 do begin
      InitMD5( Context );
      UpdateMD5( Context, Seed, SizeOf( Seed ));
      UpdateMD5( Context, RandomSeed, SizeOf( RandomSeed ));
      FinalizeMD5( Context, Seed );
    end;
  finally
    lcg.Free;
  end;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRandomGenerator.RandomBytes( var buff; len : DWORD );
var
  Context : TMD5Context;
  TmpDig : TMD5Digest;
  Index : DWORD;
  m : integer;
  SizeOfTmpDig : integer;
begin
  SizeOfTmpDig := SizeOf( TmpDig );
  Index := 0;

  if(( len - Index ) < 16 )then
    m := len - Index
  else
    m := SizeOfTmpDig;

  While Index < len do begin
    InitMD5( Context );
    UpdateMD5( Context, Seed, sizeof( Seed ));
    UpdateMD5( Context, RandCount, sizeof( RandCount ));
    FinalizeMD5( Context, TmpDig );

    inc( RandCount );
    move( tmpDig, TByteArray( buff )[ Index ], m );
    inc( Index, m );

    if(( len - Index ) < 16 )then
      m := len - Index
    else
      m := SizeOfTmpDig;
  end;
end;
{ == TLbRanLFS ============================================================= }
constructor TLbRanLFS.Create;
begin
  inherited;
  SetSeed;
end;
{ -------------------------------------------------------------------------- }
destructor TLbRanLFS.Destroy;
begin
  inherited;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRanLFS.FillBuf( var buff; len : DWORD );
var
  l : DWORD;
  b : byte;
  tmp_byt : byte;
begin
  for l := 0 to pred( len )do begin
    tmp_byt := 0;
    for b := 0 to 7 do begin
      tmp_byt := ( tmp_byt shl 1 ) or LFS;
    end;
    TByteArray( buff )[ l ] := tmp_byt;
  end;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRanLFS.SetSeed;
{$IFDEF MSWINDOWS}
const
  hold : integer = 1;
var
  _time : TSYSTEMTIME;
{$ENDIF}
begin
  while true do begin
{$IFDEF MSWINDOWS}         // could use CryptGenRandom as a better random number generator - http://msdn.microsoft.com/en-us/aa379942(VS.85).aspx
    ShiftRegister := hold;
    GetLocalTime( _time );
    ShiftRegister := ( ShiftRegister shl ( hold and $0000000F )) xor
                     (( DWORD( _time.wHour or _time.wSecond ) shl 16 ) or
                      ( DWORD( _time.wMinute or _time.wMilliseconds  )));
    hold := ShiftRegister;
    inc( hold );
{$ELSE}
  ShiftRegister := LbSysRandom32;   // arc4random does not wait until a random number is available in /dev/random
{$ENDIF}
    if( ShiftRegister <> 0 )then
      break;
  end;
end;
{ -------------------------------------------------------------------------- }
function TLbRanLFS.LFS : byte;
begin
  ShiftRegister := (((( ShiftRegister shr 31 ) xor
                      ( ShiftRegister shr 6  ) xor
                      ( ShiftRegister shr 4  ) xor
                      ( ShiftRegister shr 2  ) xor
                      ( ShiftRegister shr 1  ) xor
                      ( ShiftRegister )) and $00000001 ) shl 31 ) or
                      ( ShiftRegister shr 1 );

  result := ShiftRegister and $00000001;
end;

{ TSha1HashRandom }

constructor TSha1HashRandom.Create;
begin
  FLock:=TCriticalSection.Create;
  FRandomPos:=-1;
end;

destructor TSha1HashRandom.Destroy;
begin
  FLock.Free;
  inherited Destroy;
end;

{$IFDEF MACOS}
function GetTickCount: DWORD;
begin
  Result := AbsoluteToNanoseconds(UpTime) div 1000000;
end;

function GetCurrentThreadId: TThreadID;
begin
  Result := TThread.CurrentThread.ThreadID;
end;
{$ENDIF}

function TSha1HashRandom.Random32: DWord;
begin
  FLock.Acquire;
  try
    if FRandomPos=-1 then begin
      Randomize;
      FRandomPos:=0;
      FCounter:=Random($FFFF);
    end;
    if FRandomPos=0 then begin
      inc(FCounter);
      //Hash is calculated from a buffer consisting of current time, two 32-bit random integers, the current thread id and a counter
      FHashSource:=FloatToStr(Now)+IntToStr(Random($7FFFFFFF))+IntToStr(Random($7FFFFFFF))+IntToStr(PtrUInt(GetCurrentThreadId))+IntToStr(FCounter);
      HashSHA1(FDigest,FHashSource[1],Length(FHashSource));
    end;
    FResultPos:=Addr(FDigest[FRandomPos]);
    result:=FResultPos^;
    inc(FRandomPos,4); if FRandomPos>=20 then FRandomPos:=0;
  finally
    FLock.Release;
  end;
end;

initialization
  FLbFallbackRandomGenerator := TSha1HashRandom.Create;

finalization
  FreeAndNil(FLbFallbackRandomGenerator);

end.
