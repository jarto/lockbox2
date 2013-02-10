// CodeGear C++Builder
// Copyright (c) 1995, 2008 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Lbasym.pas' rev: 20.00

#ifndef LbasymHPP
#define LbasymHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Lbbigint.hpp>	// Pascal unit
#include <Lbclass.hpp>	// Pascal unit
#include <Lbconst.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Lbasym
{
//-- type declarations -------------------------------------------------------
typedef System::Byte *pByte;

#pragma option push -b-
enum TLbAsymKeySize { aks128, aks256, aks512, aks768, aks1024 };
#pragma option pop

typedef void __fastcall (__closure *TLbProgressEvent)(System::TObject* Sender, bool &Abort);

class DELPHICLASS TLbAsymmetricKey;
class PASCALIMPLEMENTATION TLbAsymmetricKey : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TLbAsymKeySize FKeySize;
	System::AnsiString FPassphrase;
	virtual void __fastcall SetKeySize(TLbAsymKeySize Value);
	void __fastcall MovePtr(pByte &Ptr, int &Max);
	void __fastcall MovePtrCount(pByte &Ptr, int &Max, int Count);
	int __fastcall GetASN1StructLen(pByte &input, int &len);
	int __fastcall GetASN1StructNum(pByte &input, int &len);
	void __fastcall CreateASN1(void *Buf, int &BufLen, System::Byte Tag);
	void __fastcall ParseASN1(pByte &input, int &length, Lbbigint::TLbBigInt* biValue);
	int __fastcall EncodeASN1(Lbbigint::TLbBigInt* biValue, Sysutils::PByteArray &pBuf, int &MaxLen);
	virtual int __fastcall CreateASNKey(Sysutils::PByteArray Input, int Length) = 0 ;
	virtual bool __fastcall ParseASNKey(pByte Input, int Length) = 0 ;
	
public:
	__fastcall virtual TLbAsymmetricKey(TLbAsymKeySize aKeySize);
	__fastcall virtual ~TLbAsymmetricKey(void);
	virtual void __fastcall Assign(TLbAsymmetricKey* aKey);
	virtual void __fastcall LoadFromStream(Classes::TStream* aStream);
	virtual void __fastcall StoreToStream(Classes::TStream* aStream);
	virtual void __fastcall LoadFromFile(System::UnicodeString aFileName);
	virtual void __fastcall StoreToFile(System::UnicodeString aFileName);
	__property TLbAsymKeySize KeySize = {read=FKeySize, write=SetKeySize, nodefault};
	__property System::AnsiString Passphrase = {read=FPassphrase, write=FPassphrase};
};


class DELPHICLASS TLbAsymmetricCipher;
class PASCALIMPLEMENTATION TLbAsymmetricCipher : public Lbclass::TLbCipher
{
	typedef Lbclass::TLbCipher inherited;
	
protected:
	TLbAsymKeySize FKeySize;
	TLbProgressEvent FOnProgress;
	virtual void __fastcall SetKeySize(TLbAsymKeySize Value);
	
public:
	__fastcall virtual TLbAsymmetricCipher(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbAsymmetricCipher(void);
	virtual void __fastcall GenerateKeyPair(void) = 0 ;
	__property TLbAsymKeySize KeySize = {read=FKeySize, write=SetKeySize, nodefault};
	__property TLbProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
};


class DELPHICLASS TLbSignature;
class PASCALIMPLEMENTATION TLbSignature : public Lbclass::TLBBaseComponent
{
	typedef Lbclass::TLBBaseComponent inherited;
	
protected:
	TLbAsymKeySize FKeySize;
	TLbProgressEvent FOnProgress;
	virtual void __fastcall SetKeySize(TLbAsymKeySize Value);
	
public:
	__fastcall virtual TLbSignature(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbSignature(void);
	virtual void __fastcall GenerateKeyPair(void) = 0 ;
	virtual void __fastcall SignBuffer(const void *Buf, unsigned BufLen) = 0 ;
	virtual void __fastcall SignFile(const System::UnicodeString AFileName) = 0 ;
	virtual void __fastcall SignStream(Classes::TStream* AStream) = 0 ;
	void __fastcall SignString(const System::AnsiString AStr);
	virtual void __fastcall SignStringA(const System::AnsiString AStr) = 0 ;
	virtual void __fastcall SignStringW(const System::UnicodeString AStr) = 0 ;
	virtual bool __fastcall VerifyBuffer(const void *Buf, unsigned BufLen) = 0 ;
	virtual bool __fastcall VerifyFile(const System::UnicodeString AFileName) = 0 ;
	virtual bool __fastcall VerifyStream(Classes::TStream* AStream) = 0 ;
	bool __fastcall VerifyString(const System::AnsiString AStr);
	virtual bool __fastcall VerifyStringA(const System::AnsiString AStr) = 0 ;
	virtual bool __fastcall VerifyStringW(const System::UnicodeString AStr) = 0 ;
	__property TLbAsymKeySize KeySize = {read=FKeySize, write=SetKeySize, nodefault};
	__property TLbProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
};


//-- var, const, procedure ---------------------------------------------------
static const TLbAsymKeySize cLbDefAsymKeySize = (TLbAsymKeySize)(2);
extern PACKAGE StaticArray<System::Word, 5> cLbAsymKeyBytes;

}	/* namespace Lbasym */
using namespace Lbasym;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LbasymHPP
