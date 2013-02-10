// CodeGear C++Builder
// Copyright (c) 1995, 2011 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'LbProc.pas' rev: 23.00 (Win32)

#ifndef LbprocHPP
#define LbprocHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Winapi.Windows.hpp>	// Pascal unit
#include <Winapi.MMSystem.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <LbCipher.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Lbproc
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ECipherException;
#pragma pack(push,4)
class PASCALIMPLEMENTATION ECipherException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ECipherException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ECipherException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size) : System::Sysutils::Exception(Msg, Args, Args_Size) { }
	/* Exception.CreateRes */ inline __fastcall ECipherException(int Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateResFmt */ inline __fastcall ECipherException(int Ident, System::TVarRec const *Args, const int Args_Size)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_Size) { }
	/* Exception.CreateHelp */ inline __fastcall ECipherException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ECipherException(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECipherException(int Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECipherException(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_Size, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ECipherException(void) { }
	
};

#pragma pack(pop)

typedef void __fastcall (*TProgressProc)(int CurPostion, int TotalSize);

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TProgressProc LbOnProgress;
extern PACKAGE int LbProgressSize;
extern PACKAGE void __fastcall BFEncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall BFEncryptFileCBC(const System::UnicodeString InFile, const System::UnicodeString OutFile, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall BFEncryptStream(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall BFEncryptStreamCBC(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall DESEncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall DESEncryptFileCBC(const System::UnicodeString InFile, const System::UnicodeString OutFile, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall DESEncryptStream(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall DESEncryptStreamCBC(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall LBCEncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile, System::Byte const *Key, int Rounds, bool Encrypt);
extern PACKAGE void __fastcall LBCEncryptFileCBC(const System::UnicodeString InFile, const System::UnicodeString OutFile, System::Byte const *Key, int Rounds, bool Encrypt);
extern PACKAGE void __fastcall LBCEncryptStream(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, System::Byte const *Key, int Rounds, bool Encrypt);
extern PACKAGE void __fastcall LBCEncryptStreamCBC(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, System::Byte const *Key, int Rounds, bool Encrypt);
extern PACKAGE void __fastcall LQCEncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall LQCEncryptFileCBC(const System::UnicodeString InFile, const System::UnicodeString OutFile, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall LQCEncryptStream(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall LQCEncryptStreamCBC(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall LSCEncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile, const void *Key, int KeySize);
extern PACKAGE void __fastcall RNG32EncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile, int Key);
extern PACKAGE void __fastcall RNG64EncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile, int KeyHi, int KeyLo);
extern PACKAGE void __fastcall TripleDESEncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall TripleDESEncryptFileCBC(const System::UnicodeString InFile, const System::UnicodeString OutFile, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall TripleDESEncryptStream(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall TripleDESEncryptStreamCBC(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall RDLEncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE void __fastcall RDLEncryptFileCBC(const System::UnicodeString InFile, const System::UnicodeString OutFile, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE void __fastcall RDLEncryptStream(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE void __fastcall RDLEncryptStreamCBC(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE void __fastcall FileHashMD5(System::Byte *Digest, const System::UnicodeString AFileName);
extern PACKAGE void __fastcall StreamHashMD5(System::Byte *Digest, System::Classes::TStream* AStream);
extern PACKAGE void __fastcall FileHashSHA1(System::Byte *Digest, const System::UnicodeString AFileName);
extern PACKAGE void __fastcall StreamHashSHA1(System::Byte *Digest, System::Classes::TStream* AStream);

}	/* namespace Lbproc */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_LBPROC)
using namespace Lbproc;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LbprocHPP
