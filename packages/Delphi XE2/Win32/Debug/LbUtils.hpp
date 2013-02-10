// CodeGear C++Builder
// Copyright (c) 1995, 2011 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'LbUtils.pas' rev: 23.00 (Win32)

#ifndef LbutilsHPP
#define LbutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.SysUtils.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Lbutils
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::UnicodeString __fastcall BufferToHex(const void *Buf, unsigned BufSize);
extern PACKAGE bool __fastcall HexToBuffer(const System::UnicodeString Hex, void *Buf, unsigned BufSize);
extern PACKAGE int __fastcall Min(int A, int B);
extern PACKAGE int __fastcall Max(int A, int B);
extern PACKAGE bool __fastcall CompareBuffers(const void *Buf1, const void *Buf2, unsigned BufSize);

}	/* namespace Lbutils */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_LBUTILS)
using namespace Lbutils;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LbutilsHPP
