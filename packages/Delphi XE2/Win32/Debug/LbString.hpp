// CodeGear C++Builder
// Copyright (c) 1995, 2011 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'LbString.pas' rev: 23.00 (Win32)

#ifndef LbstringHPP
#define LbstringHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit
#include <LbCipher.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Lbstring
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall LbDecodeBase64A(System::Classes::TStream* InStream, System::Classes::TStream* OutStream);
extern PACKAGE void __fastcall LbDecodeBase64W(System::Classes::TStream* InStream, System::Classes::TStream* OutStream);
extern PACKAGE void __fastcall LbEncodeBase64A(System::Classes::TStream* InStream, System::Classes::TStream* OutStream);
extern PACKAGE void __fastcall LbEncodeBase64W(System::Classes::TStream* InStream, System::Classes::TStream* OutStream);
extern PACKAGE System::AnsiString __fastcall BFEncryptStringEx(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall BFEncryptStringExA(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::UnicodeString __fastcall BFEncryptStringExW(const System::UnicodeString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall BFEncryptStringCBCEx(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall BFEncryptStringCBCExA(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::UnicodeString __fastcall BFEncryptStringCBCExW(const System::UnicodeString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall BFEncryptString(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall BFEncryptStringA(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall BFEncryptStringW(const System::UnicodeString InString, System::UnicodeString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall BFEncryptStringCBC(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall BFEncryptStringCBCA(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall BFEncryptStringCBCW(const System::UnicodeString InString, System::UnicodeString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall DESEncryptStringEx(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::UnicodeString __fastcall DESEncryptStringExW(const System::UnicodeString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall DESEncryptStringExA(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall DESEncryptStringCBCEx(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::UnicodeString __fastcall DESEncryptStringCBCExW(const System::UnicodeString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall DESEncryptStringCBCExA(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall DESEncryptString(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall DESEncryptStringA(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall DESEncryptStringW(const System::UnicodeString InString, System::UnicodeString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall DESEncryptStringCBC(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall DESEncryptStringCBCA(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall DESEncryptStringCBCW(const System::UnicodeString InString, System::UnicodeString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall TripleDESEncryptStringEx(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::UnicodeString __fastcall TripleDESEncryptStringExW(const System::UnicodeString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall TripleDESEncryptStringExA(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall TripleDESEncryptStringCBCEx(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::UnicodeString __fastcall TripleDESEncryptStringCBCExW(const System::UnicodeString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall TripleDESEncryptStringCBCExA(const System::AnsiString InString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall TripleDESEncryptString(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall TripleDESEncryptStringA(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall TripleDESEncryptStringW(const System::UnicodeString InString, System::UnicodeString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall TripleDESEncryptStringCBC(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall TripleDESEncryptStringCBCA(const System::AnsiString InString, System::AnsiString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE void __fastcall TripleDESEncryptStringCBCW(const System::UnicodeString InString, System::UnicodeString &OutString, System::Byte const *Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall RDLEncryptStringEx(const System::AnsiString InString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE System::UnicodeString __fastcall RDLEncryptStringExW(const System::UnicodeString InString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall RDLEncryptStringExA(const System::AnsiString InString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall RDLEncryptStringCBCEx(const System::AnsiString InString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE System::UnicodeString __fastcall RDLEncryptStringCBCExW(const System::UnicodeString InString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall RDLEncryptStringCBCExA(const System::AnsiString InString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE void __fastcall RDLEncryptString(const System::AnsiString InString, System::AnsiString &OutString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE void __fastcall RDLEncryptStringA(const System::AnsiString InString, System::AnsiString &OutString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE void __fastcall RDLEncryptStringW(const System::UnicodeString InString, System::UnicodeString &OutString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE void __fastcall RDLEncryptStringCBC(const System::AnsiString InString, System::AnsiString &OutString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE void __fastcall RDLEncryptStringCBCA(const System::AnsiString InString, System::AnsiString &OutString, const void *Key, int KeySize, bool Encrypt);
extern PACKAGE void __fastcall RDLEncryptStringCBCW(const System::UnicodeString InString, System::UnicodeString &OutString, const void *Key, int KeySize, bool Encrypt);

}	/* namespace Lbstring */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_LBSTRING)
using namespace Lbstring;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LbstringHPP
