// CodeGear C++Builder
// Copyright (c) 1995, 2008 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Lbdsa.pas' rev: 20.00

#ifndef LbdsaHPP
#define LbdsaHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Lbrandom.hpp>	// Pascal unit
#include <Lbcipher.hpp>	// Pascal unit
#include <Lbbigint.hpp>	// Pascal unit
#include <Lbasym.hpp>	// Pascal unit
#include <Lbconst.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Lbdsa
{
//-- type declarations -------------------------------------------------------
typedef StaticArray<System::Byte, 20> TLbDSABlock;

typedef void __fastcall (__closure *TLbGetDSABlockEvent)(System::TObject* Sender, System::Byte *Block);

typedef void __fastcall (__closure *TLbDSACallback)(bool &Abort);

class DELPHICLASS TLbDSAParameters;
class PASCALIMPLEMENTATION TLbDSAParameters : public Lbasym::TLbAsymmetricKey
{
	typedef Lbasym::TLbAsymmetricKey inherited;
	
protected:
	Lbbigint::TLbBigInt* FP;
	Lbbigint::TLbBigInt* FQ;
	Lbbigint::TLbBigInt* FG;
	Lbbigint::TLbBigInt* F2Tog;
	Lbbigint::TLbBigInt* FMostLeast;
	System::Byte FPrimeTestIterations;
	TLbDSACallback FCallback;
	bool __fastcall GenerateP(System::Byte const *ASeed);
	bool __fastcall GenerateQ(System::Byte const *ASeed);
	bool __fastcall GenerateG(void);
	System::UnicodeString __fastcall GetPAsString();
	void __fastcall SetPAsString(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetQAsString();
	void __fastcall SetQAsString(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetGAsString();
	void __fastcall SetGAsString(const System::UnicodeString Value);
	virtual void __fastcall SetKeySize(Lbasym::TLbAsymKeySize Value);
	
public:
	__fastcall virtual TLbDSAParameters(Lbasym::TLbAsymKeySize aKeySize);
	__fastcall virtual ~TLbDSAParameters(void);
	virtual void __fastcall Clear(void);
	void __fastcall CopyDSAParameters(TLbDSAParameters* AKey);
	bool __fastcall GenerateDSAParameters(System::Byte const *ASeed);
	__property Lbbigint::TLbBigInt* P = {read=FP};
	__property Lbbigint::TLbBigInt* Q = {read=FQ};
	__property Lbbigint::TLbBigInt* G = {read=FG};
	__property System::UnicodeString PAsString = {read=GetPAsString, write=SetPAsString};
	__property System::UnicodeString QAsString = {read=GetQAsString, write=SetQAsString};
	__property System::UnicodeString GAsString = {read=GetGAsString, write=SetGAsString};
	__property System::Byte PrimeTestIterations = {read=FPrimeTestIterations, write=FPrimeTestIterations, nodefault};
	__property TLbDSACallback Callback = {read=FCallback, write=FCallback};
};


class DELPHICLASS TLbDSAPrivateKey;
class PASCALIMPLEMENTATION TLbDSAPrivateKey : public TLbDSAParameters
{
	typedef TLbDSAParameters inherited;
	
protected:
	Lbbigint::TLbBigInt* FX;
	TLbDSABlock FXKey;
	System::UnicodeString __fastcall GetXAsString();
	void __fastcall SetXAsString(const System::UnicodeString Value);
	virtual int __fastcall CreateASNKey(Sysutils::PByteArray Input, int Length);
	virtual bool __fastcall ParseASNKey(Lbasym::pByte Input, int Length);
	
public:
	__fastcall virtual TLbDSAPrivateKey(Lbasym::TLbAsymKeySize aKeySize);
	__fastcall virtual ~TLbDSAPrivateKey(void);
	virtual void __fastcall Clear(void);
	void __fastcall GenerateX(System::Byte const *AXKey);
	__property Lbbigint::TLbBigInt* X = {read=FX};
	__property System::UnicodeString XAsString = {read=GetXAsString, write=SetXAsString};
};


class DELPHICLASS TLbDSAPublicKey;
class PASCALIMPLEMENTATION TLbDSAPublicKey : public TLbDSAParameters
{
	typedef TLbDSAParameters inherited;
	
protected:
	Lbbigint::TLbBigInt* FY;
	System::UnicodeString __fastcall GetYAsString();
	void __fastcall SetYAsString(const System::UnicodeString Value);
	virtual int __fastcall CreateASNKey(Sysutils::PByteArray Input, int Length);
	virtual bool __fastcall ParseASNKey(Lbasym::pByte Input, int Length);
	
public:
	__fastcall virtual TLbDSAPublicKey(Lbasym::TLbAsymKeySize aKeySize);
	__fastcall virtual ~TLbDSAPublicKey(void);
	virtual void __fastcall Clear(void);
	void __fastcall GenerateY(Lbbigint::TLbBigInt* aX);
	__property Lbbigint::TLbBigInt* Y = {read=FY};
	__property System::UnicodeString YAsString = {read=GetYAsString, write=SetYAsString};
};


class DELPHICLASS TLbDSA;
class PASCALIMPLEMENTATION TLbDSA : public Lbasym::TLbSignature
{
	typedef Lbasym::TLbSignature inherited;
	
protected:
	TLbDSAPrivateKey* FPrivateKey;
	TLbDSAPublicKey* FPublicKey;
	System::Byte FPrimeTestIterations;
	Lbbigint::TLbBigInt* FSignatureR;
	Lbbigint::TLbBigInt* FSignatureS;
	TLbGetDSABlockEvent FOnGetR;
	TLbGetDSABlockEvent FOnGetS;
	TLbGetDSABlockEvent FOnGetSeed;
	TLbGetDSABlockEvent FOnGetXKey;
	TLbGetDSABlockEvent FOnGetKKey;
	bool FRandomSeed;
	void __fastcall SignHash(System::Byte const *ADigest);
	bool __fastcall VerifyHash(System::Byte const *ADigest);
	void __fastcall SHA1KKey(System::Byte *AKKey);
	void __fastcall RandomBlock(System::Byte *ABlock);
	void __fastcall DoGetR(void);
	void __fastcall DoGetS(void);
	void __fastcall DoGetSeed(System::Byte *ASeed);
	void __fastcall DoGetXKey(System::Byte *AXKey);
	void __fastcall DoGetKKey(System::Byte *AKKey);
	virtual void __fastcall SetKeySize(Lbasym::TLbAsymKeySize Value);
	void __fastcall SetPrimeTestIterations(System::Byte Value);
	void __fastcall DSAParameterCallback(bool &Abort);
	
public:
	__fastcall virtual TLbDSA(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbDSA(void);
	virtual void __fastcall GenerateKeyPair(void);
	virtual void __fastcall SignBuffer(const void *Buf, unsigned BufLen);
	virtual void __fastcall SignFile(const System::UnicodeString AFileName);
	virtual void __fastcall SignStream(Classes::TStream* AStream);
	virtual void __fastcall SignStringA(const System::AnsiString AStr);
	virtual void __fastcall SignStringW(const System::UnicodeString AStr);
	virtual bool __fastcall VerifyBuffer(const void *Buf, unsigned BufLen);
	virtual bool __fastcall VerifyFile(const System::UnicodeString AFileName);
	virtual bool __fastcall VerifyStream(Classes::TStream* AStream);
	virtual bool __fastcall VerifyStringA(const System::AnsiString AStr);
	virtual bool __fastcall VerifyStringW(const System::UnicodeString AStr);
	void __fastcall Clear(void);
	bool __fastcall GeneratePQG(void);
	void __fastcall GenerateXY(void);
	__property TLbDSAPrivateKey* PrivateKey = {read=FPrivateKey};
	__property TLbDSAPublicKey* PublicKey = {read=FPublicKey};
	__property Lbbigint::TLbBigInt* SignatureR = {read=FSignatureR};
	__property Lbbigint::TLbBigInt* SignatureS = {read=FSignatureS};
	
__published:
	__property System::Byte PrimeTestIterations = {read=FPrimeTestIterations, write=SetPrimeTestIterations, nodefault};
	__property KeySize;
	__property TLbGetDSABlockEvent OnGetR = {read=FOnGetR, write=FOnGetR};
	__property TLbGetDSABlockEvent OnGetS = {read=FOnGetS, write=FOnGetS};
	__property TLbGetDSABlockEvent OnGetSeed = {read=FOnGetSeed, write=FOnGetSeed};
	__property TLbGetDSABlockEvent OnGetXKey = {read=FOnGetXKey, write=FOnGetXKey};
	__property TLbGetDSABlockEvent OnGetKKey = {read=FOnGetKKey, write=FOnGetKKey};
	__property Lbasym::TLbProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Lbdsa */
using namespace Lbdsa;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LbdsaHPP
