// CodeGear C++Builder
// Copyright (c) 1995, 2008 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Lbrandom.pas' rev: 20.00

#ifndef LbrandomHPP
#define LbrandomHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Math.hpp>	// Pascal unit
#include <Lbcipher.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Lbrandom
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TLbRandomGenerator;
class PASCALIMPLEMENTATION TLbRandomGenerator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int RandCount;
	Lbcipher::TMD5Digest Seed;
	void __fastcall ChurnSeed(void);
	
public:
	__fastcall TLbRandomGenerator(void);
	__fastcall virtual ~TLbRandomGenerator(void);
	void __fastcall RandomBytes(void *buff, unsigned len);
};


class DELPHICLASS TLbRanLFS;
class PASCALIMPLEMENTATION TLbRanLFS : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	unsigned ShiftRegister;
	void __fastcall SetSeed(void);
	System::Byte __fastcall LFS(void);
	
public:
	__fastcall TLbRanLFS(void);
	__fastcall virtual ~TLbRanLFS(void);
	void __fastcall FillBuf(void *buff, unsigned len);
};


//-- var, const, procedure ---------------------------------------------------
static const ShortInt tmp = 0x1;

}	/* namespace Lbrandom */
using namespace Lbrandom;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LbrandomHPP
