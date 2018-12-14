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
{*                  LBRSA.PAS 2.09                       *}
{*     Copyright (c) 2002 TurboPower Software Co         *}
{*                 All rights reserved.                  *}
{*********************************************************}

{$I LockBox.inc}

unit LbRSA;
  {-RSA encryption and signature components, classes, and routines}

interface

uses
{$IFNDEF FPC}
  Windows,
{$ENDIF}
{$IFDEF POSIX}
  Types,
{$ENDIF}
  Classes,
  SysUtils,
  LbBigInt,
  LbAsym,
  LbCipher,
  LbConst;


const
  { cipher block size constants }                                    {!!.02}
  cRSAMinPadBytes = 11;
  cRSACipherBlockSize : array[TLbAsymKeySize] of Word =
    (cBytes128, cBytes256, cBytes512, cBytes768, cBytes1024,
     cBytes2048, cBytes3072);
  cRSAPlainBlockSize : array[TLbAsymKeySize] of Word =
    (cBytes128-cRSAMinPadBytes, cBytes256-cRSAMinPadBytes,
     cBytes512-cRSAMinPadBytes, cBytes768-cRSAMinPadBytes,
     cBytes1024-cRSAMinPadBytes, cBytes2048-cRSAMinPadBytes,
     cBytes3072-cRSAMinPadBytes);

type
  { ciphertext block types }                                         {!!.02}
  PRSACipherBlock128 = ^TRSACipherBlock128;
  TRSACipherBlock128 = array[0..cBytes128-1] of Byte;
  PRSACipherBlock256 = ^TRSACipherBlock256;
  TRSACipherBlock256 = array[0..cBytes256-1] of Byte;
  PRSACipherBlock512 = ^TRSACipherBlock512;
  TRSACipherBlock512 = array[0..cBytes512-1] of Byte;
  PRSACipherBlock768 = ^TRSACipherBlock768;
  TRSACipherBlock768 = array[0..cBytes768-1] of Byte;
  PRSACipherBlock1024 = ^TRSACipherBlock1024;
  TRSACipherBlock1024 = array[0..cBytes1024-1] of Byte;
  PRSACipherBlock2048 = ^TRSACipherBlock2048;
  TRSACipherBlock2048 = array[0..cBytes2048-1] of Byte;
  PRSACipherBlock3072 = ^TRSACipherBlock3072;
  TRSACipherBlock3072 = array[0..cBytes3072-1] of Byte;

  { plaintext block types }                                          {!!.02}
  PRSAPlainBlock128 = ^TRSAPlainBlock128;
  TRSAPlainBlock128 = array[0..cBytes128-12] of Byte;
  PRSAPlainBlock256 = ^TRSAPlainBlock256;
  TRSAPlainBlock256 = array[0..cBytes256-12] of Byte;
  PRSAPlainBlock512 = ^TRSAPlainBlock512;
  TRSAPlainBlock512 = array[0..cBytes512-12] of Byte;
  PRSAPlainBlock768 = ^TRSAPlainBlock768;
  TRSAPlainBlock768 = array[0..cBytes768-12] of Byte;
  PRSAPlainBlock1024 = ^TRSAPlainBlock1024;
  TRSAPlainBlock1024 = array[0..cBytes1024-12] of Byte;
  PRSAPlainBlock2048 = ^TRSAPlainBlock2048;
  TRSAPlainBlock2048 = array[0..cBytes2048-12] of Byte;
  PRSAPlainBlock3072 = ^TRSAPlainBlock3072;
  TRSAPlainBlock3072 = array[0..cBytes3072-12] of Byte;

  { default block type }
  TRSAPlainBlock  = TRSAPlainBlock512;
  TRSACipherBlock = TRSACipherBlock512;

  { signature types }
  TRSASignatureBlock = array[0..cBytes3072-1] of Byte;
  TRSAHashMethod  = (hmMD5, hmSHA1);


type
  TLbRSAGetSignatureEvent = procedure(Sender : TObject;
                                      var Sig : TRSASignatureBlock) of object;
  TLbRSACallback = procedure(var Abort : Boolean) of object;


{ TLbRSAKey }
type
  TLbRSAKey = class(TLbAsymmetricKey)
    protected {private}
      FModulus  : TLbBigInt;
      FExponent : TLbBigInt;
      function ParseASNKey(Input : pByte; Length : Integer) : boolean; override;
      function  CreateASNKey(Input : pByteArray; Length : Integer) : Integer; override;
      function GetModulusAsHexString : string;
      procedure SetModulusAsHexString(Value : string);
      function GetExponentAsHexString : string;
      procedure SetExponentAsHexString(Value : string);

    public
      constructor Create(aKeySize : TLbAsymKeySize); override;
      destructor Destroy; override;

      procedure Assign(aKey : TLbAsymmetricKey); override;
      procedure Clear;

      property Modulus : TLbBigInt read FModulus;
      property ModulusAsString : string read GetModulusAsHexString write SetModulusAsHexString;
      property Exponent : TLbBigInt read FExponent;
      property ExponentAsString : string read GetExponentAsHexString write SetExponentAsHexString;
  end;


{ TLbRSA }
type
  TLbRSA = class(TLbAsymmetricCipher)
  private
    function GetCryptoServiceProviderXML(AIsForPrivateKey : Boolean) : String;
    function CalculatePQ : Boolean;
  protected {private}
      FPrivateKey : TLbRSAKey;
      FPublicKey : TLbRSAKey;
      FPrimeTestIterations : Byte;
      FFirstPrime : TLbBigInt;
      FSecondPrime : TLbBigInt;
      procedure SetKeySize(Value : TLbAsymKeySize); override;
    public {methods}
      constructor Create(AOwner : TComponent); override;
      destructor Destroy; override;

      procedure DecryptFile(const InFile, OutFile : string); override;
      procedure DecryptStream(InStream , OutStream : TStream); override;
      function  DecryptString(const InString : RawByteString) : RawByteString; override;
      procedure EncryptFile(const InFile, OutFile : string); override;
      procedure EncryptStream(InStream, OutStream : TStream); override;
      function  EncryptString(const InString : RawByteString) : RawByteString; override;
      procedure GenerateKeyPair; override;
      procedure GenerateKeyPairWithExponent(AExponent : TLbBigInt);
      function  OutBufSizeNeeded(InBufSize : Cardinal) : Cardinal; override;
      procedure RSACallback(var Abort : Boolean);

      property PrivateKey : TLbRSAKey read FPrivateKey;
      property PublicKey : TLbRSAKey read FPublicKey;

      property CryptoServiceProviderXML[AIsForPrivateKey : Boolean] : String read GetCryptoServiceProviderXML;
    published {properties}
      property PrimeTestIterations : Byte read FPrimeTestIterations write FPrimeTestIterations;
      property KeySize;
    published {events}
      property OnProgress;
  end;


{ TLbRSASSA }
type
  TLbRSASSA = class(TLbSignature)
    protected {private}
      FPrivateKey : TLbRSAKey;
      FPublicKey : TLbRSAKey;
      FHashMethod : TRSAHashMethod;
      FPrimeTestIterations : Byte;
      FSignature  : TLbBigInt;
      FOnGetSignature : TLbRSAGetSignatureEvent;
      procedure DoGetSignature;
      procedure EncryptHash(const HashDigest; DigestLen : Cardinal; WithHashDigestInfo : Boolean);
      procedure DecryptHash(var HashDigest; DigestLen : Cardinal; WithHashDigestInfo : Boolean);
      procedure RSACallback(var Abort : Boolean);
      procedure SetKeySize(Value : TLbAsymKeySize); override;
      function GetHashIdentifier : String;
    public {methods}
      constructor Create(AOwner : TComponent); override;
      destructor Destroy; override;

      procedure GenerateKeyPair; override;
      procedure SignBuffer(const Buf; BufLen : Cardinal); overload; override;
      procedure SignFile(const AFileName : string); overload; override;
      procedure SignStream(AStream : TStream); overload; override;
      procedure SignString(const AStr : RawByteString); overload; override;

      procedure SignBuffer(const Buf; BufLen : Cardinal; WithHashDigestInfo : Boolean); reintroduce; overload;
      procedure SignFile(const AFileName : string; WithHashDigestInfo : Boolean); reintroduce; overload;
      procedure SignStream(AStream : TStream; WithHashDigestInfo : Boolean); reintroduce; overload;
      procedure SignString(const AStr : RawByteString; WithHashDigestInfo : Boolean); reintroduce; overload;

      function  VerifyBuffer(const Buf; BufLen : Cardinal) : Boolean; overload; override;
      function  VerifyFile(const AFileName : string) : Boolean; overload; override;
      function  VerifyStream(AStream : TStream) : Boolean; overload; override;
      function  VerifyString(const AStr : RawByteString) : Boolean; overload; override;

      function  VerifyBuffer(const Buf; BufLen : Cardinal; WithHashDigestInfo : Boolean) : Boolean; reintroduce; overload;
      function  VerifyFile(const AFileName : string; WithHashDigestInfo : Boolean) : Boolean; reintroduce; overload;
      function  VerifyStream(AStream : TStream; WithHashDigestInfo : Boolean) : Boolean; reintroduce; overload;
      function  VerifyString(const AStr : RawByteString; WithHashDigestInfo : Boolean) : Boolean; reintroduce; overload;

    public {properties}
      property PrivateKey : TLbRSAKey
        read FPrivateKey;
      property PublicKey : TLbRSAKey
        read FPublicKey;
      property Signature : TLbBigInt
        read FSignature;

    published {properties}
      property HashMethod : TRSAHashMethod
        read FHashMethod write FHashMethod;
      property PrimeTestIterations : Byte
        read FPrimeTestIterations write FPrimeTestIterations;
      property KeySize;

    published {events}
      property OnGetSignature : TLbRSAGetSignatureEvent
        read FOnGetSignature write FOnGetSignature;
      property OnProgress;
    end;


{ low level RSA cipher public routines }

{ new public routines }                                              {!!.02}
function EncryptRSAEx(PublicKey : TLbRSAKey; pInBlock, pOutBlock : PByteArray;
           InDataSize : Integer) : Longint;
function DecryptRSAEx(PrivateKey : TLbRSAKey;
           pInBlock, pOutBlock : PByteArray) : Longint;
function  EncryptRSA128(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock128;
            var OutBlock : TRSACipherBlock128) : Longint;
function  DecryptRSA128(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock128;
            var OutBlock : TRSAPlainBlock128) : Longint;
function  EncryptRSA256(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock256;
            var OutBlock : TRSACipherBlock256) : Longint;
function  DecryptRSA256(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock256;
            var OutBlock : TRSAPlainBlock256) : Longint;
function  EncryptRSA512(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock512;
            var OutBlock : TRSACipherBlock512) : Longint;
function  DecryptRSA512(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock512;
            var OutBlock : TRSAPlainBlock512) : Longint;
function  EncryptRSA768(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock768;
            var OutBlock : TRSACipherBlock768) : Longint;
function  DecryptRSA768(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock768;
            var OutBlock : TRSAPlainBlock768) : Longint;
function  EncryptRSA1024(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock1024;
            var OutBlock : TRSACipherBlock1024) : Longint;
function  DecryptRSA1024(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock1024;
            var OutBlock : TRSAPlainBlock1024) : Longint;
function  EncryptRSA2048(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock2048;
            var OutBlock : TRSACipherBlock2048) : Longint;
function  DecryptRSA2048(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock2048;
            var OutBlock : TRSAPlainBlock2048) : Longint;
function  EncryptRSA3072(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock3072;
            var OutBlock : TRSACipherBlock3072) : Longint;
function  DecryptRSA3072(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock3072;
            var OutBlock : TRSAPlainBlock3072) : Longint;
{!!.02}

function  EncryptRSA(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock;
            var OutBlock : TRSACipherBlock) : Longint;
function  DecryptRSA(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock;
            var OutBlock : TRSAPlainBlock) : Longint;
procedure RSAEncryptFile(const InFile, OutFile : string;
            Key : TLbRSAKey; Encrypt : Boolean);
procedure RSAEncryptStream(InStream, OutStream : TStream;
            Key : TLbRSAKey; Encrypt : Boolean);
function RSAEncryptString(const InString : RawByteString;
            Key : TLbRSAKey; Encrypt : Boolean) : RawByteString;
procedure GenerateRSAKeysEx(var PrivateKey, PublicKey : TLbRSAKey;
            KeySize : TLbAsymKeySize; PrimeTestIterations : Byte;
            Exponent : TlbBigInt; Callback : TLbRSACallback);
procedure GenerateRSAKeys(var PrivateKey, PublicKey : TLbRSAKey); overload;
procedure GenerateRSAKeys(Exponent : TlbBigInt; var PrivateKey, PublicKey : TLbRSAKey); overload;


implementation

uses
  LbUtils, LbString, LbProc;

const
  cDefHashMethod  = hmMD5;

type
  TRSABlockType = (bt00, bt01, bt02);



{ == Local RSA routines ==================================================== }
procedure RSADecodeBlock(biBlock : TLbBigInt);
var
  i : DWord;
  Buf : TRSAPlainBlock3072;
begin
  { verify block format }
  i := biBlock.Size;
  if (i < cRSAMinPadBytes) then
    raise Exception.Create(sRSADecodingErrBTS);
  if (i > cBytes3072) then
    raise Exception.Create(sRSADecodingErrBTL);
  if (biBlock.GetByteValue(i) <> Byte(bt01)) and (biBlock.GetByteValue(i) <> Byte(bt02)) then
    raise Exception.Create(sRSADecodingErrIBT);
  Dec(i);

  { count padding bytes }
  while (biBlock.GetByteValue(i) <> 0) do begin
    Dec(i);
    if (i <= 0) then
    raise Exception.Create(sRSADecodingErrIBF);
  end;

  { strip off padding bytes }
  biBlock.ToBuffer(Buf, i-1);
  biBlock.CopyBuffer(Buf, i-1);
end;
{ -------------------------------------------------------------------------- }
procedure RSAFormatBlock(biBlock : TLbBigInt; BlockType : TRSABlockType);
begin
  if (biBlock.Int.IntBuf.dwLen - biBlock.Int.dwUsed) < 11 then       {!!.02}
    raise Exception.Create(sRSAEncodingErr);                         {!!.02}

  { separate data from padding }
  biBlock.AppendByte($00);

  { append padding }
  while (biBlock.Int.IntBuf.dwLen - biBlock.Int.dwUsed) > 2 do begin {!!.02}
    if (BlockType = bt01) then
      biBlock.AppendByte(Byte($FF))
    else
      biBlock.AppendByte(Byte(Random($FD) + 1));
  end;

  { append tag }
  if (BlockType = bt01) then
    biBlock.AppendByte($01)
  else
    biBlock.AppendByte($02);

  { last byte always 0 }
  biBlock.AppendByte($00);
end;
{ -------------------------------------------------------------------------- }
procedure RSAEncryptBigInt(biBlock : TLbBigInt; Key : TLbRSAKey;
                          BlockType : TRSABlockType; Encrypt : Boolean);
var
  dwSize, dwLen : DWORD;
  tmp1, tmp2 : TLbBigInt;
begin
  tmp1 := TLbBigInt.Create(cLbAsymKeyBytes[Key.KeySize]);
  tmp2 := TLbBigInt.Create(cLbAsymKeyBytes[Key.KeySize]);

  try
    if Encrypt then
      RSAFormatBlock(biBlock, BlockType);
    tmp1.Copy(biBlock);
    dwSize := tmp1.Size;
    biBlock.Clear;
    repeat
      dwLen := Min(dwSize, Key.Modulus.Size);
      tmp2.CopyLen(tmp1, dwLen);
      tmp2.PowerAndMod(Key.Exponent, Key.Modulus);

      biBlock.Append(tmp2);
      tmp1.Shr_(dwLen * 8);
      dwSize := dwSize - dwLen;
    until (dwSize <= 0);

    if Encrypt then                                                  {!!.02}
      { replace leading zeros that were trimmed in the math }        {!!.02}
      while (biBlock.Size < cLbAsymKeyBytes[Key.KeySize]) do         {!!.02}
        biBlock.AppendByte($00)                                      {!!.02}
    else                                                             {!!.02}
      RSADecodeBlock(biBlock);

  finally
    tmp1.Free;
    tmp2.Free;
  end;
end;


{ == Public RSA routines =================================================== }
procedure GenerateRSAKeys(Exponent : TLbBigInt; var PrivateKey, PublicKey : TLbRSAKey);
  { create RSA public/private key pair with default settings }
begin
  GenerateRSAKeysEx(PrivateKey, PublicKey, cLbDefAsymKeySize, cDefIterations, Exponent, nil);
end;
{ -------------------------------------------------------------------------- }
procedure GenerateRSAKeys(var PrivateKey, PublicKey : TLbRSAKey);
begin
  GenerateRSAKeys(nil, PrivateKey, PublicKey);
end;
{ -------------------------------------------------------------------------- }
procedure GenerateRSAKeysEx(var PrivateKey, PublicKey : TLbRSAKey;
                            KeySize : TLbAsymKeySize;
                            PrimeTestIterations : Byte;
                            Exponent : TlbBigInt;
                            Callback : TLbRSACallback);
  { create RSA key pair speciying size and prime test iterations and }
  { callback function }
var
  q : TLbBigInt;
  p : TLbBigInt;
  p1q1 : TLbBigInt;
  d : TLbBigInt;
  e : TLbBigInt;
  n : TLbBigInt;
  Abort : Boolean;
begin
  PrivateKey := TLbRSAKey.Create(KeySize);
  PublicKey := TLbRSAKey.Create(KeySize);

  { create temp variables }
  p1q1 := TLbBigInt.Create(cLbAsymKeyBytes[KeySize]);
  d := TLbBigInt.Create(cLbAsymKeyBytes[KeySize]);
  e := TLbBigInt.Create(cLbAsymKeyBytes[KeySize]);
  n := TLbBigInt.Create(cLbAsymKeyBytes[KeySize]);
  p := TLbBigInt.Create(cLbAsymKeyBytes[KeySize] div 2);
  q := TLbBigInt.Create(cLbAsymKeyBytes[KeySize] div 2);

  try
    Abort := False;
    repeat
      { p , q = random primes }
      repeat
        p.RandomPrime(PrimeTestIterations);
        { check for abort }
        if Assigned(Callback) then
          Callback(Abort);
        if Abort then
          Exit;
        q.RandomPrime(PrimeTestIterations);
        { check for abort }
        if Assigned(Callback) then
          Callback(Abort);
        if Abort then
          Exit;
      until (p.Compare(q) <> 0);

      { n = pq }
      n.Copy(p);
      n.Multiply(q);

      { p1q1 = (p-1)(q-1) }
      p.SubtractByte($01);
      q.SubtractByte($01);
      p1q1.Copy(p);
      p1q1.Multiply(q);

      if assigned(Exponent) then
      begin
        e.Copy(Exponent);
      end
      else
      begin
        { e = randomly chosen simple prime > 3 }
        e.RandomSimplePrime;
      end;


      { d = inverse(e) mod (p-1)(q-1) }
      d.Copy(e);
    until d.ModInv(p1q1);

    { assign n and d to private key }
    PrivateKey.Modulus.Copy(n);
    PrivateKey.Exponent.Copy(d);

    { assign n and e to public key }
    PublicKey.Modulus.Copy(n);
    PublicKey.Exponent.Copy(e);

  finally
    p1q1.Free;
    d.Free;
    e.Free;
    n.Free;
    p.Free;
    q.Free;
  end;
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function EncryptRSAEx(PublicKey : TLbRSAKey;
                      pInBlock, pOutBlock : PByteArray;
                      InDataSize : Integer) : Longint;
  { IMPORTANT: verify block sizes before calling this routine }
var
  biBlock : TLbBigInt;
  OutSize : DWord;
begin
  OutSize := cRSACipherBlockSize[PublicKey.KeySize];
  biBlock := TLbBigInt.Create(OutSize);
  try
    biBlock.CopyBuffer(pInBlock^, InDataSize);
    RSAEncryptBigInt(biBlock, PublicKey, bt02, True);
    if Integer(OutSize) < biBlock.Size then                          {!!.05}
      raise Exception.Create('OutBlock size too small');

    biBlock.ToBuffer(pOutBlock^, biBlock.Size);
  finally
    Result := biBlock.Size;
    biBlock.Free;
  end;
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function DecryptRSAEx(PrivateKey : TLbRSAKey;
                      pInBlock, pOutBlock : PByteArray) : Longint;
  { IMPORTANT: verify block sizes before calling this routine }
var
  biBlock : TLbBigInt;
  InSize, OutSize : DWord;
begin
  InSize := cRSACipherBlockSize[PrivateKey.KeySize];
  OutSize := cRSAPlainBlockSize[PrivateKey.KeySize];
  biBlock := TLbBigInt.Create(InSize);
  try
    biBlock.CopyBuffer(pInBlock^, InSize);
    RSAEncryptBigInt(biBlock, PrivateKey, bt02, False);
    if Integer(OutSize) < biBlock.Size then                          {!!.05}
      raise Exception.Create('OutBlock size too small');

    biBlock.ToBuffer(pOutBlock^, biBlock.Size);
  finally
    Result := biBlock.Size;
    biBlock.Free;
  end;
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  EncryptRSA128(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock128;
            var OutBlock : TRSACipherBlock128) : Longint;
  { encrypt plaintext block with 128-bit RSA public key }
begin
  if (PublicKey.KeySize <> aks128) then
    raise Exception.Create(sRSABlockSize128Err);
  Result := EncryptRSAEx(PublicKey, @InBlock, @OutBlock, SizeOf(InBlock));
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  DecryptRSA128(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock128;
            var OutBlock : TRSAPlainBlock128) : Longint;
  { decrypt ciphertext block with 128-bit RSA private key }
begin
  if (PrivateKey.KeySize <> aks128) then
    raise Exception.Create(sRSABlockSize128Err);
  Result := DecryptRSAEx(PrivateKey, @InBlock, @OutBlock);
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  EncryptRSA256(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock256;
            var OutBlock : TRSACipherBlock256) : Longint;
  { encrypt plaintext block with 256-bit RSA public key }
begin
  if (PublicKey.KeySize <> aks256) then
    raise Exception.Create(sRSABlockSize256Err);
  Result := EncryptRSAEx(PublicKey, @InBlock, @OutBlock, SizeOf(InBlock));
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  DecryptRSA256(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock256;
            var OutBlock : TRSAPlainBlock256) : Longint;
  { decrypt ciphertext block with 256-bit RSA private key }
begin
  if (PrivateKey.KeySize <> aks256) then
    raise Exception.Create(sRSABlockSize256Err);
  Result := DecryptRSAEx(PrivateKey, @InBlock, @OutBlock);
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  EncryptRSA512(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock512;
            var OutBlock : TRSACipherBlock512) : Longint;
  { encrypt plaintext block with 512-bit RSA public key }
begin
  if (PublicKey.KeySize <> aks512) then
    raise Exception.Create(sRSABlockSize512Err);
  Result := EncryptRSAEx(PublicKey, @InBlock, @OutBlock, SizeOf(InBlock));
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  DecryptRSA512(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock512;
            var OutBlock : TRSAPlainBlock512) : Longint;
  { decrypt ciphertext block with 512-bit RSA private key }
begin
  if (PrivateKey.KeySize <> aks512) then
    raise Exception.Create(sRSABlockSize512Err);
  Result := DecryptRSAEx(PrivateKey, @InBlock, @OutBlock);
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  EncryptRSA768(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock768;
            var OutBlock : TRSACipherBlock768) : Longint;
  { encrypt plaintext block with 768-bit RSA public key }
begin
  if (PublicKey.KeySize <> aks768) then
    raise Exception.Create(sRSABlockSize768Err);
  Result := EncryptRSAEx(PublicKey, @InBlock, @OutBlock, SizeOf(InBlock));
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  DecryptRSA768(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock768;
            var OutBlock : TRSAPlainBlock768) : Longint;
  { decrypt ciphertext block with 768-bit RSA private key }
begin
  if (PrivateKey.KeySize <> aks768) then
    raise Exception.Create(sRSABlockSize768Err);
  Result := DecryptRSAEx(PrivateKey, @InBlock, @OutBlock);
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  EncryptRSA1024(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock1024;
            var OutBlock : TRSACipherBlock1024) : Longint;
  { encrypt plaintext block with 1024-bit RSA public key }
begin
  if (PublicKey.KeySize <> aks1024) then
    raise Exception.Create(sRSABlockSize1024Err);
  Result := EncryptRSAEx(PublicKey, @InBlock, @OutBlock, SizeOf(InBlock));
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  DecryptRSA1024(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock1024;
            var OutBlock : TRSAPlainBlock1024) : Longint;
  { decrypt ciphertext block with 1024-bit RSA private key }
begin
  if (PrivateKey.KeySize <> aks1024) then
    raise Exception.Create(sRSABlockSize1024Err);
  Result := DecryptRSAEx(PrivateKey, @InBlock, @OutBlock);
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  EncryptRSA2048(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock2048;
            var OutBlock : TRSACipherBlock2048) : Longint;
  { encrypt plaintext block with 2048-bit RSA public key }
begin
  if (PublicKey.KeySize <> aks2048) then
    raise Exception.Create(sRSABlockSize2048Err);
  Result := EncryptRSAEx(PublicKey, @InBlock, @OutBlock, SizeOf(InBlock));
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  DecryptRSA2048(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock2048;
            var OutBlock : TRSAPlainBlock2048) : Longint;
  { decrypt ciphertext block with 2048-bit RSA private key }
begin
  if (PrivateKey.KeySize <> aks2048) then
    raise Exception.Create(sRSABlockSize2048Err);
  Result := DecryptRSAEx(PrivateKey, @InBlock, @OutBlock);
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  EncryptRSA3072(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock3072;
            var OutBlock : TRSACipherBlock3072) : Longint;
  { encrypt plaintext block with 3072-bit RSA public key }
begin
  if (PublicKey.KeySize <> aks3072) then
    raise Exception.Create(sRSABlockSize3072Err);
  Result := EncryptRSAEx(PublicKey, @InBlock, @OutBlock, SizeOf(InBlock));
end;
{ -------------------------------------------------------------------------- }
{!!.02}
function  DecryptRSA3072(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock3072;
            var OutBlock : TRSAPlainBlock3072) : Longint;
  { decrypt ciphertext block with 3072-bit RSA private key }
begin
  if (PrivateKey.KeySize <> aks3072) then
    raise Exception.Create(sRSABlockSize3072Err);
  Result := DecryptRSAEx(PrivateKey, @InBlock, @OutBlock);
end;
{ -------------------------------------------------------------------------- }
function EncryptRSA(PublicKey : TLbRSAKey; const InBlock : TRSAPlainBlock;
           var OutBlock : TRSACipherBlock) : Longint;
  { encrypt plaintext block with 512-bit RSA public key }
begin
  Result := EncryptRSA512(PublicKey, InBlock, OutBlock);             {!!.02}
end;
{ -------------------------------------------------------------------------- }
function DecryptRSA(PrivateKey : TLbRSAKey; const InBlock : TRSACipherBlock;
           var OutBlock : TRSAPlainBlock) : Longint;
  { decrypt ciphertext block with 512-bit RSA private key }
begin
  Result := DecryptRSA512(PrivateKey, InBlock, OutBlock);            {!!.02}
end;
{ -------------------------------------------------------------------------- }
procedure RSAEncryptFile(const InFile, OutFile : string;
            Key : TLbRSAKey; Encrypt : Boolean);
  { encrypt/decrypt file data with RSA key }
var
  InStream, OutStream : TStream;
begin
  InStream := TFileStream.Create(InFile, fmOpenRead or fmShareDenyWrite);
  try
    OutStream := TFileStream.Create(OutFile, fmCreate);
    try
      RSAEncryptStream(InStream, OutStream, Key, Encrypt);
    finally
      OutStream.Free;
    end;
  finally
    InStream.Free;
  end;
end;
{ -------------------------------------------------------------------------- }
procedure RSAEncryptStream(InStream, OutStream : TStream;
            Key : TLbRSAKey; Encrypt : Boolean);
  { encrypt/decrypt stream data with RSA key }
var
  InBlkCount  : Integer;
  InBlkSize, OutBlkSize : Integer;
  PlainBlockSize, CipherBlockSize : Integer;
  i : Integer;
  pInBlk, pOutBlk       : Pointer;
  PlainBlock, CipherBlock : TRSACipherBlock3072;
begin
  PlainBlockSize := cRSAPlainBlockSize[Key.KeySize];
  CipherBlockSize := cRSACipherBlockSize[Key.KeySize];
  if Encrypt then begin
    pInBlk := @PlainBlock;
    pOutBlk := @CipherBlock;
    InBlkSize := PlainBlockSize;
    OutBlkSize := CipherBlockSize;
  end else begin
    pInBlk := @CipherBlock;
    pOutBlk := @PlainBlock;
    InBlkSize := CipherBlockSize;
    OutBlkSize := PlainBlockSize;
  end;

  InBlkCount := InStream.Size div InBlkSize;
  if (InStream.Size mod InBlkSize) > 0 then
    Inc(InBlkCount);

  { process all except the last block }
  for i := 1 to (InBlkCount - 1) do begin
    InStream.Read(pInBlk^, InBlkSize);
    if Encrypt then
      EncryptRSAEx(Key, pInBlk, pOutBlk, InBlkSize)
    else
      DecryptRSAEx(Key, pInBlk, pOutBlk);
    OutStream.Write(pOutBlk^, OutBlkSize);
  end;

  { process the last block }
  i := InStream.Read(pInBlk^, InBlkSize);
  if Encrypt then
    i := EncryptRSAEx(Key, pInBlk, pOutBlk, i)
  else
    i := DecryptRSAEx(Key, pInBlk, pOutBlk);
  OutStream.Write(pOutBlk^, i);
end;
{ -------------------------------------------------------------------------- }
function RSAEncryptString(const InString : RawByteString; Key : TLbRSAKey; Encrypt : Boolean) : RawByteString;
  { encrypt/decrypt string data with RSA key }
var
  InStream  : TMemoryStream;
  OutStream : TMemoryStream;
  WorkStream : TMemoryStream;
begin
  InStream := TMemoryStream.Create;
  OutStream := TMemoryStream.Create;
  WorkStream := TMemoryStream.Create;
  InStream.Write(InString[1], Length(InString));
  InStream.Position := 0;

  if Encrypt then begin
    RSAEncryptStream(InStream, WorkStream, Key, True);
    WorkStream.Position := 0;
    LbEncodeBase64(WorkStream, OutStream);
  end else begin
    LbDecodeBase64(InStream, WorkStream);
    WorkStream.Position := 0;
    RSAEncryptStream(WorkStream, OutStream, Key, False);
  end;
  OutStream.Position := 0;
  SetLength(Result, OutStream.Size);
  OutStream.Read(Result[1], OutStream.Size);

  InStream.Free;
  OutStream.Free;
  WorkStream.Free;
end;

{ == TLbRSAKey ============================================================= }
constructor TLbRSAKey.Create(aKeySize : TLbAsymKeySize);
  { initialization }
begin
  inherited Create(aKeySize);

  FModulus := TLbBigInt.Create(cLbAsymKeyBytes[FKeySize]);
  FExponent := TLbBigInt.Create(cLbAsymKeyBytes[FKeySize]);
end;
{ -------------------------------------------------------------------------- }
destructor TLbRSAKey.Destroy;
  { finalization }
begin
  FModulus.Free;
  FExponent.Free;

  inherited Destroy;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSAKey.Assign(aKey : TLbAsymmetricKey);
  { copy exponent and modulus values from another key }
begin
  inherited Assign(aKey);

  if (aKey is TLbRSAKey) then begin
    FModulus.Copy(TLbRSAKey(aKey).Modulus);
    FExponent.Copy(TLbRSAKey(aKey).Exponent);
  end;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSAKey.Clear;
  { reset exponent and modulus }
begin
  FModulus.Clear;
  FExponent.Clear;
end;
{ -------------------------------------------------------------------------- }
function TLbRSAKey.GetModulusAsHexString : string;
  { return "big to little" hex string representation of modulus }
begin
  Result := FModulus.IntStr;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSAKey.SetModulusAsHexString(Value : string);
  { set modulus to value represented by "big to little" hex string }
begin
  FModulus.IntStr := Value;
end;
{ -------------------------------------------------------------------------- }
function TLbRSAKey.GetExponentAsHexString : string;
  { return "big to little" hex string representation of exponent }
begin
  Result := FExponent.IntStr;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSAKey.SetExponentAsHexString(Value : string);
  { set exponent to value represented by "big to little" hex string }
begin
  FExponent.IntStr := Value;
end;
{------------------------------------------------------------------------------}
function TLbRSAKey.CreateASNKey(Input : pByteArray; Length : Integer) : Integer;
const
  TAG30 = $30;
var
  ExpSize : Integer;
  ModSize : Integer;
  Total : Integer;
  pInput : PByteArray;
  Max : Integer;
begin
  pInput := Input;
  Max := Length;
  ModSize := EncodeASN1(FModulus, pInput, Max);
  ExpSize := EncodeASN1(FExponent, pInput, Max);
  Total := ExpSize + ModSize;
  CreateASN1(Input^, Total, TAG30);
  Result := Total;
end;
{------------------------------------------------------------------------------}
function TLbRSAKey.ParseASNKey(Input : PByte; Length : Integer) : Boolean;
var
  Tag : Integer;
  Max : Integer;
  pInput : PByte;
begin
  Max := Length;
  pInput := Input;

  { check for sequence }
  Tag := GetASN1StructNum(pInput, Max);
  GetASN1StructLen(pInput, Max);

  if (Tag <> ASN1_TYPE_SEQUENCE) then
    raise Exception.Create(sRSAKeyBadKey);

  KeySize := KeySizeFromBytes(ParseASN1(pInput, Max, FModulus));
  ParseASN1(pInput, Max, FExponent);

  Result := (Max = 0);
end;



{ == TLbRSA ================================================================ }
function TLbRSA.CalculatePQ: Boolean;
var
  d, e, n : TLbBigInt;
  k, r, t, y, g, Nminus1, j, TWO, x : TLbBigInt;
  index : Integer;
  IsFound, IsDone : boolean;
begin
  IsFound := false;

  d := FPrivateKey.Exponent;
  e := FPublicKey.Exponent;
  n := FPrivateKey.Modulus;

  k := TLbBigInt.Create(d.Size);
  try
    k.Copy(d);
    k.Multiply(e);
    k.SubtractByte($01);

    if k.IsEven then
    begin
      r := nil;
      t := nil;
      y := nil;
      g := nil;
      Nminus1 := nil; //n - 1
      TWO := nil;
      try
        Nminus1 := TLbBigInt.Create(n.Size);
        Nminus1.Copy(n);
        Nminus1.SubtractByte($01);

        TWO := TLbBigInt.Create(d.Size);
        TWO.CopyByte($02);

        r := TLbBigInt.Create(k.Size);
        r.Copy(k);
        r.Divide(TWO);

        t := TLbBigInt.Create(k.Size);
        t.CopyByte($01);
        while r.IsEven do
        begin
          r.Divide(TWO);
          t.AddByte($01);
        end;

        y := TLbBigInt.Create(n.Size);
        g := TLbBigInt.Create(n.Size);
        index := 0;
        while (index < 100) and not IsFound do
        begin
          g.RandomBytes(n.Size);

          y.Copy(g);
          y.PowerAndMod(r, n);
          if (not y.IsOne and (y.Compare(Nminus1) <> 0)) then
          begin
            j := nil;
            x := nil;
            try
              x := TLbBigInt.Create(y.Size);

              j := TLbBigInt.Create(k.Size);
              j.CopyByte($01);

              IsDone := false;
              while (j.Compare(t) <= 0) and not IsDone do
              begin
                x.Copy(y);
                x.PowerAndMod(TWO, n);
                IsFound := x.IsOne;
                IsDone := IsFound or (x.Compare(Nminus1) = 0);
                if not IsDone then
                begin
                  y.Copy(x);
                end;

                j.AddByte($01);
              end;

              if not IsFound then
              begin
                x.Copy(y);
                x.PowerAndMod(TWO, n);
                IsFound := x.IsOne;
              end;
            finally
              j.Free;
              x.Free;
            end;
          end;

          inc(index);
        end;

        if IsFound then
        begin
          FFirstPrime.Copy(y);
          FFirstPrime.SubtractByte($01);
          FFirstPrime.GCD(n);

          FSecondPrime.Copy(n);
          FSecondPrime.Divide(FFirstPrime);
        end;
      finally
        r.Free;
        t.Free;
        g.Free;
        y.Free;
        Nminus1.Free;
        TWO.Free;
      end;
    end;
  finally
    k.Free;
  end;

  Result := IsFound;
end;

constructor TLbRSA.Create(AOwner : TComponent);
  { initialize }
begin
  inherited Create(AOwner);

  FPrivateKey := TLbRSAKey.Create(FKeySize);
  FPublicKey  := TLbRSAKey.Create(FKeySize);
  FPrimeTestIterations := cDefIterations;
  FFirstPrime := TLbBigInt.Create(cLbAsymKeyBytes[FKeySize]);
  FSecondPrime := TLbBigInt.Create(FFirstPrime.Size);
end;
{ -------------------------------------------------------------------------- }
destructor TLbRSA.Destroy;
begin
  FPrivateKey.Free;
  FPublicKey.Free;

  FFirstPrime.Free;
  FSecondPrime.Free;

  inherited Destroy;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSA.DecryptFile(const InFile, OutFile : string);
  { decrypt file data with RSA private key }
begin
  RSAEncryptFile(InFile, OutFile, FPrivateKey, False);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSA.DecryptStream(InStream , OutStream : TStream);
  { decrypt stream data with RSA private key }
begin
  RSAEncryptStream(InStream, OutStream, FPrivateKey, False);
end;
{ -------------------------------------------------------------------------- }
function TLbRSA.DecryptString(const InString : RawByteString) : RawByteString;
  { decrypt string data with RSA private key }
begin
  Result := RSAEncryptString(InString, FPrivateKey, False);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSA.EncryptFile(const InFile, OutFile : string);
  { encrypt file data with RSA public key }
begin
  RSAEncryptFile(InFile, OutFile, FPublicKey, True);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSA.EncryptStream(InStream, OutStream : TStream);
  { encrypt stream data with RSA public key }
begin
  RSAEncryptStream(InStream, OutStream, FPublicKey, True);
end;
{ -------------------------------------------------------------------------- }
function TLbRSA.EncryptString(const InString : RawByteString) : RawByteString;
  { encrypt string data with RSA public key }
begin
  Result := RSAEncryptString(InString, FPublicKey, True);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSA.GenerateKeyPair;
  { generate RSA public/private key pair }
begin
  GenerateKeyPairWithExponent(nil);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSA.GenerateKeyPairWithExponent(AExponent : TLbBigInt);
begin
  if Assigned(FPrivateKey) then
    FPrivateKey.Free;
  if Assigned(FPublicKey) then
    FPublicKey.Free;
  try
    GenerateRSAKeysEx(FPrivateKey, FPublicKey, FKeySize, FPrimeTestIterations, AExponent, RSACallback);
  except
    raise Exception.Create(sRSAKeyPairErr);
  end;
end;
{ -------------------------------------------------------------------------- }
function TLbRSA.GetCryptoServiceProviderXML(AIsForPrivateKey : Boolean): String;
const
  RSA_KEY_VALUE = 'RSAKeyValue';
  RSA_MODULUS = 'Modulus';
  RSA_PUBLIC_EXPONENT = 'Exponent';
  RSA_PRIVATE_EXPONENT = 'D';
  RSA_PRIME_ONE = 'P';
  RSA_PRIME_TWO = 'Q';
  RSA_D_MOD_PRIME_ONE = 'DP';
  RSA_D_MOD_PRIME_TWO = 'DQ';
  RSA_PRIME_TWO_INVERSE = 'InverseQ';
  XML_TAG = '<%0:s>%1:s</%0:s>';
var
  Text : String;
  ReversedBigInt, P1, Q1 : TLbBigInt;
begin
  ReversedBigInt := TlbBigInt.Create(cLbAsymKeyBytes[FKeySize]);
  try
    ReversedBigInt.Copy(FPublicKey.Modulus);
    ReversedBigInt.Trim;
    ReversedBigInt.ReverseBytes;
    Text := Format(XML_TAG, [RSA_MODULUS, ReversedBigInt.Base64Str]);

    ReversedBigInt.Copy(FPublicKey.Exponent);
    ReversedBigInt.Trim;
    ReversedBigInt.ReverseBytes;
    Text := Text + Format(XML_TAG, [RSA_PUBLIC_EXPONENT, ReversedBigInt.Base64Str]);

    if AIsForPrivateKey then
    begin
      if not CalculatePQ then
      begin
        raise Exception.Create('Cannot calculate prime factors');
      end;

      ReversedBigInt.Copy(FFirstPrime);
      ReversedBigInt.Trim;
      ReversedBigInt.ReverseBytes;
      Text := Text + Format(XML_TAG, [RSA_PRIME_ONE, ReversedBigInt.Base64Str]);

      ReversedBigInt.Copy(FSecondPrime);
      ReversedBigInt.Trim;
      ReversedBigInt.ReverseBytes;
      Text := Text + Format(XML_TAG, [RSA_PRIME_TWO, ReversedBigInt.Base64Str]);

      P1 := TLbBigInt.Create(FFirstPrime.Size);
      try
        P1.Copy(FFirstPrime);
        P1.SubtractByte($01);

        ReversedBigInt.Copy(FPrivateKey.Exponent);
        ReversedBigInt.Modulus(P1);
        ReversedBigInt.Trim;
        ReversedBigInt.ReverseBytes;
        Text := Text + Format(XML_TAG, [RSA_D_MOD_PRIME_ONE, ReversedBigInt.Base64Str]);
      finally
        P1.Free;
      end;

      Q1 := TLbBigInt.Create(FSecondPrime.Size);
      try
        Q1.Copy(FSecondPrime);
        Q1.SubtractByte($01);

        ReversedBigInt.Copy(FPrivateKey.Exponent);
        ReversedBigInt.Modulus(Q1);
        ReversedBigInt.Trim;
        ReversedBigInt.ReverseBytes;
        Text := Text + Format(XML_TAG, [RSA_D_MOD_PRIME_TWO, ReversedBigInt.Base64Str]);
      finally
        Q1.Free;
      end;

      ReversedBigInt.Copy(FSecondPrime);
      ReversedBigInt.ModInv(FFirstPrime);
      ReversedBigInt.Trim;
      ReversedBigInt.ReverseBytes;
      Text := Text + Format(XML_TAG, [RSA_PRIME_TWO_INVERSE, ReversedBigInt.Base64Str]);

      ReversedBigInt.Copy(FPrivateKey.Exponent);
      ReversedBigInt.Trim;
      ReversedBigInt.ReverseBytes;
      Text := Text + Format(XML_TAG, [RSA_PRIVATE_EXPONENT, ReversedBigInt.Base64Str]);
    end;
  finally
    ReversedBigInt.Free;
  end;

  Result := Format(XML_TAG,[RSA_KEY_VALUE,Text]);
end;
{ -------------------------------------------------------------------------- }
function TLbRSA.OutBufSizeNeeded(InBufSize : Cardinal) : Cardinal;
  { return size of ciphertext buffer required to encrypt plaintext InBuf }
var
  BlkCount : Cardinal;
begin
  BlkCount := InBufSize div cRSAPlainBlockSize[FKeySize];            {!!.02}
  if (InBufSize mod cRSAPlainBlockSize[FKeySize]) > 0 then           {!!.02}
    Inc(BlkCount);
  Result := BlkCount * cRSACipherBlockSize[FKeySize];                {!!.02}
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSA.RSACallback(var Abort : Boolean);
  { pass callback on via OnProgress event }
begin
  Abort := False;
  if Assigned(FOnProgress) then
    FOnProgress(Self, Abort);
end;
{ -------------------------------------------------------------------------- }
{!!.02}
procedure TLbRSA.SetKeySize(Value : TLbAsymKeySize);
begin
  FKeySize := Value;
  FPublicKey.KeySize := FKeySize;
  FPrivateKey.KeySize := FKeySize;
end;



{ == TLbRSASSA ============================================================= }
constructor TLbRSASSA.Create(AOwner : TComponent);
  { initialize }
begin
  inherited Create(AOwner);

  FPrivateKey := TLbRSAKey.Create(FKeySize);
  FPublicKey  := TLbRSAKey.Create(FKeySize);
  FSignature  := TLbBigInt.Create(cLbAsymKeyBytes[FKeySize]);
  FHashMethod := cDefHashMethod;
  FPrimeTestIterations := cDefIterations;
end;
{ -------------------------------------------------------------------------- }
destructor TLbRSASSA.Destroy;
  { finalize }
begin
  FPrivateKey.Free;
  FPublicKey.Free;
  FSignature.Free;

  inherited Destroy;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.DoGetSignature;
  { fire OnGetSignature event to obtain RSA signature }
var
  SigBlock : TRSASignatureBlock;
begin
  if Assigned(FOnGetSignature) then begin
    FillChar(SigBlock, SizeOf(SigBlock), #0);
    FOnGetSignature(Self, SigBlock);
    FSignature.CopyBuffer(SigBlock, cLbAsymKeyBytes[FKeySize]);      {!!.02}
    FSignature.Trim;
  end;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.GenerateKeyPair;
  { generate RSA public/private key pair }
begin
  if Assigned(FPrivateKey) then
    FPrivateKey.Free;
  if Assigned(FPublicKey) then
    FPublicKey.Free;
  GenerateRSAKeysEx(FPrivateKey, FPublicKey, FKeySize, FPrimeTestIterations, nil, RSACallback);
end;
{ -------------------------------------------------------------------------- }
function TLbRSASSA.GetHashIdentifier : String;
var
  HashID : String;
begin
  case FHashMethod of
    hmMD5 :
      HashID := '30 20 30 0C 06 08 2A 86 48 86 F7 0D 02 05 05 00 04 10';

    hmSHA1 :
      HashID := '30 21 30 09 06 05 2B 0E 03 02 1A 05 00 04 14';
  else
    raise Exception.Create('Unknown hash type in GetHashIdentifier()');
  end;

  Result := StringReplace(HashID, #32, '', [rfReplaceAll]);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.EncryptHash(const HashDigest; DigestLen : Cardinal; WithHashDigestInfo : Boolean);
  { encrypt message digest into signature }
var
  DigestInfo : TLbBigInt;
begin
  if (FPrivateKey.Modulus.Size = 0) then                             {!!.02}
    raise Exception.Create(sRSAPrivateKeyErr);

  FSignature.CopyBuffer(HashDigest, DigestLen);

  if WithHashDigestInfo then
  begin
    FSignature.ReverseBytes;
    DigestInfo := TLbBigInt.Create(FSignature.Size);
    try
      DigestInfo.IntStr := GetHashIdentifier;
      DigestInfo.ReverseBytes;
      FSignature.Append(DigestInfo);
    finally
      DigestInfo.Free;
    end;
  end;

  RSAEncryptBigInt(FSignature, FPrivateKey, bt01, True);             {!!.02}

  if WithHashDigestInfo then
  begin
    FSignature.ReverseBytes;
  end;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.DecryptHash(var HashDigest; DigestLen : Cardinal; WithHashDigestInfo : Boolean);
  { decrypt signature into message digest }
var
  biBlock, DigestInfo : TLbBigInt;
begin
  if (FPublicKey.Modulus.Size = 0) then                              {!!.02}
    raise Exception.Create(sRSAPublicKeyErr);

  biBlock := TLbBigInt.Create(cLbAsymKeyBytes[FKeySize]);
  try
    DoGetSignature;
    biBlock.Copy(FSignature);

    if (WithHashDigestInfo) then
    begin
      biBlock.ReverseBytes;
    end;

    RSAEncryptBigInt(biBlock, FPublicKey, bt01, False);              {!!.02}

    if (WithHashDigestInfo) then
    begin
      biBlock.ReverseBytes;

      DigestInfo := TLbBigInt.Create(FSignature.Size);
      try
        DigestInfo.IntStr := GetHashIdentifier;
        biBlock.Subtract(DigestInfo);
        biBlock.ReverseBytes;
        biBlock.Trim;
      finally
        DigestInfo.Free;
      end;

      biBlock.ReverseBytes;
    end;

    FillChar(HashDigest, DigestLen, #0);
    if biBlock.Size < Integer(DigestLen) then                        {!!.05}
      biBlock.ToBuffer(HashDigest, biBlock.Size)
    else
      biBlock.ToBuffer(HashDigest, DigestLen);
  except
    { just swallow the error, signature comparison will fail benignly }
  end;
  biBlock.Free;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.SignBuffer(const Buf; BufLen : Cardinal);
begin
  SignBuffer(Buf, BufLen, false);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.SignBuffer(const Buf; BufLen : Cardinal; WithHashDigestInfo : Boolean);
  { generate RSA signature of buffer data }
var
  MD5Digest  : TMD5Digest;
  SHA1Digest : TSHA1Digest;
begin
  case FHashMethod of
    hmMD5  :
      begin
        HashMD5(MD5Digest, Buf, BufLen);
        EncryptHash(MD5Digest, SizeOf(MD5Digest), WithHashDigestInfo);
      end;
    hmSHA1 :
      begin
        HashSHA1(SHA1Digest, Buf, BufLen);
        EncryptHash(SHA1Digest, SizeOf(SHA1Digest), WithHashDigestInfo);
      end;
  end;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.SignFile(const AFileName : string);
begin
  SignFile(AFileName, false);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.SignFile(const AFileName : string; WithHashDigestInfo : Boolean);
  { generate RSA signature of file data }
var
  Stream : TStream;
begin
  Stream := TFileStream.Create(AFileName, fmOpenRead);
  try
    SignStream(Stream, WithHashDigestInfo);
  finally
    Stream.Free;
  end;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.SignStream(AStream : TStream);
begin
  SignStream(AStream, false);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.SignStream(AStream : TStream; WithHashDigestInfo : Boolean);
  { generate RSA signature of stream data }
var
  MD5Digest  : TMD5Digest;
  SHA1Digest : TSHA1Digest;
begin
  case FHashMethod of
    hmMD5  :
      begin
        StreamHashMD5(MD5Digest, AStream);
        EncryptHash(MD5Digest, SizeOf(MD5Digest), WithHashDigestInfo);
      end;
    hmSHA1 :
      begin
        StreamHashSHA1(SHA1Digest, AStream);
        EncryptHash(SHA1Digest, SizeOf(SHA1Digest), WithHashDigestInfo);
      end;
  end;
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.SignString(const AStr : RawByteString);
begin
  SignString(AStr, false);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.SignString(const AStr : RawByteString; WithHashDigestInfo : Boolean);
  { generate RSA signature of string data }
begin
  SignBuffer(AStr[1], Length(AStr), WithHashDigestInfo);
end;
{ -------------------------------------------------------------------------- }
function TLbRSASSA.VerifyBuffer(const Buf; BufLen : Cardinal) : Boolean;
begin
  Result := VerifyBuffer(Buf, BufLen, False);
end;
{ -------------------------------------------------------------------------- }
function TLbRSASSA.VerifyBuffer(const Buf; BufLen : Cardinal; WithHashDigestInfo : Boolean) : Boolean;
  { verify RSA signature agrees with buffer data }
var
  MD5Digest1  : TMD5Digest;
  MD5Digest2  : TMD5Digest;
  SHA1Digest1 : TSHA1Digest;
  SHA1Digest2 : TSHA1Digest;
begin
  case FHashMethod of
    hmMD5 :
      begin
        DecryptHash(MD5Digest1, SizeOf(TMD5Digest), WithHashDigestInfo);
        HashMD5(MD5Digest2, Buf, BufLen);
        Result := CompareBuffers(MD5Digest1, MD5Digest2, SizeOf(TMD5Digest));
      end;
    hmSHA1 :
      begin
        DecryptHash(SHA1Digest1, SizeOf(TSHA1Digest), WithHashDigestInfo);
        HashSHA1(SHA1Digest2, Buf, BufLen);
        Result := CompareBuffers(SHA1Digest1, SHA1Digest2, SizeOf(TSHA1Digest));
      end;
  else
    Result := False;
  end;
end;
{ -------------------------------------------------------------------------- }
function TLbRSASSA.VerifyFile(const AFileName : string) : Boolean;
begin
  Result := VerifyFile(AFileName, False);
end;
{ -------------------------------------------------------------------------- }
function TLbRSASSA.VerifyFile(const AFileName : string; WithHashDigestInfo : Boolean) : Boolean;
  { verify RSA signature agrees with file data }
var
  Stream : TStream;
begin
  Stream := TFileStream.Create(AFileName, fmOpenRead);
  try
    Result := VerifyStream(Stream, WithHashDigestInfo);
  finally
    Stream.Free;
  end;
end;
{ -------------------------------------------------------------------------- }
function TLbRSASSA.VerifyStream(AStream : TStream) : Boolean;
begin
  Result := VerifyStream(AStream, False);
end;
{ -------------------------------------------------------------------------- }
function TLbRSASSA.VerifyStream(AStream : TStream; WithHashDigestInfo : Boolean) : Boolean;
  { verify RSA signature agrees with stream data }
var
  MD5Digest1  : TMD5Digest;
  MD5Digest2  : TMD5Digest;
  SHA1Digest1 : TSHA1Digest;
  SHA1Digest2 : TSHA1Digest;
begin
  case FHashMethod of
    hmMD5 :
      begin
        DecryptHash(MD5Digest1, SizeOf(TMD5Digest), WithHashDigestInfo);
        StreamHashMD5(MD5Digest2, AStream);
        Result := CompareBuffers(MD5Digest1, MD5Digest2, SizeOf(TMD5Digest));
      end;
    hmSHA1 :
      begin
        DecryptHash(SHA1Digest1, SizeOf(TSHA1Digest), WithHashDigestInfo);
        StreamHashSHA1(SHA1Digest2, AStream);
        Result := CompareBuffers(SHA1Digest1, SHA1Digest2, SizeOf(TSHA1Digest));
      end;
  else
    Result := False;
  end;
end;
{ -------------------------------------------------------------------------- }
function TLbRSASSA.VerifyString(const AStr : RawByteString) : Boolean;
begin
  Result := VerifyString(AStr, False);
end;
{ -------------------------------------------------------------------------- }
function TLbRSASSA.VerifyString(const AStr : RawByteString; WithHashDigestInfo : Boolean) : Boolean;
  { verify RSA signature agrees with string data }
begin
  Result := VerifyBuffer(AStr[1], Length(AStr), WithHashDigestInfo);
end;
{ -------------------------------------------------------------------------- }
procedure TLbRSASSA.RSACallback(var Abort : Boolean);
  { pass callback on via OnProgress event }
begin
  Abort := False;
  if Assigned(FOnProgress) then
    FOnProgress(Self, Abort);
end;
{ -------------------------------------------------------------------------- }
{!!.02}
procedure TLbRSASSA.SetKeySize(Value : TLbAsymKeySize);
begin
  if (Ord(Value) < Ord(aks256)) then begin
    if (csDesigning in ComponentState) then
      FKeySize := aks256
    else
      raise Exception.Create('Invalid key size for RSASSA');
  end else
    FKeySize := Value;
  FPublicKey.KeySize := FKeySize;
  FPrivateKey.KeySize := FKeySize;
  FSignature.Free;
  FSignature := TLbBigInt.Create(cLbAsymKeyBytes[FKeySize]);
end;


end.

