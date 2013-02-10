// CodeGear C++Builder
// Copyright (c) 1995, 2008 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Lbrsa.pas' rev: 20.00

#ifndef LbrsaHPP
#define LbrsaHPP

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
#include <Lbbigint.hpp>	// Pascal unit
#include <Lbasym.hpp>	// Pascal unit
#include <Lbcipher.hpp>	// Pascal unit
#include <Lbconst.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Lbrsa
{
//-- type declarations -------------------------------------------------------
typedef StaticArray<System::Byte, 16> TRSACipherBlock128;

typedef TRSACipherBlock128 *PRSACipherBlock128;

typedef StaticArray<System::Byte, 32> TRSACipherBlock256;

typedef TRSACipherBlock256 *PRSACipherBlock256;

typedef StaticArray<System::Byte, 64> TRSACipherBlock512;

typedef TRSACipherBlock512 *PRSACipherBlock512;

typedef StaticArray<System::Byte, 96> TRSACipherBlock768;

typedef TRSACipherBlock768 *PRSACipherBlock768;

typedef StaticArray<System::Byte, 128> TRSACipherBlock1024;

typedef TRSACipherBlock1024 *PRSACipherBlock1024;

typedef StaticArray<System::Byte, 5> TRSAPlainBlock128;

typedef TRSAPlainBlock128 *PRSAPlainBlock128;

typedef StaticArray<System::Byte, 21> TRSAPlainBlock256;

typedef TRSAPlainBlock256 *PRSAPlainBlock256;

typedef StaticArray<System::Byte, 53> TRSAPlainBlock512;

typedef TRSAPlainBlock512 *PRSAPlainBlock512;

typedef StaticArray<System::Byte, 85> TRSAPlainBlock768;

typedef TRSAPlainBlock768 *PRSAPlainBlock768;

typedef StaticArray<System::Byte, 117> TRSAPlainBlock1024;

typedef TRSAPlainBlock1024 *PRSAPlainBlock1024;

typedef TRSAPlainBlock512 TRSAPlainBlock;

typedef TRSACipherBlock512 TRSACipherBlock;

typedef StaticArray<System::Byte, 128> TRSASignatureBlock;

#pragma option push -b-
enum TRSAHashMethod { hmMD5, hmSHA1 };
#pragma option pop

typedef void __fastcall (__closure *TLbRSAGetSignatureEvent)(System::TObject* Sender, System::Byte *Sig);

typedef void __fastcall (__closure *TLbRSACallback)(bool &Abort);

class DELPHICLASS TLbRSAKey;
class PASCALIMPLEMENTATION TLbRSAKey : public Lbasym::TLbAsymmetricKey
{
	typedef Lbasym::TLbAsymmetricKey inherited;
	
protected:
	Lbbigint::TLbBigInt* FModulus;
	Lbbigint::TLbBigInt* FExponent;
	virtual bool __fastcall ParseASNKey(Lbasym::pByte Input, int Length);
	virtual int __fastcall CreateASNKey(Sysutils::PByteArray Input, int Length);
	System::UnicodeString __fastcall GetModulusAsString();
	void __fastcall SetModulusAsString(System::UnicodeString Value);
	System::UnicodeString __fastcall GetExponentAsString();
	void __fastcall SetExponentAsString(System::UnicodeString Value);
	
public:
	__fastcall virtual TLbRSAKey(Lbasym::TLbAsymKeySize aKeySize);
	__fastcall virtual ~TLbRSAKey(void);
	virtual void __fastcall Assign(Lbasym::TLbAsymmetricKey* aKey);
	void __fastcall Clear(void);
	__property Lbbigint::TLbBigInt* Modulus = {read=FModulus};
	__property System::UnicodeString ModulusAsString = {read=GetModulusAsString, write=SetModulusAsString};
	__property Lbbigint::TLbBigInt* Exponent = {read=FExponent};
	__property System::UnicodeString ExponentAsString = {read=GetExponentAsString, write=SetExponentAsString};
	__property System::AnsiString Passphrase = {read=FPassphrase, write=FPassphrase};
};


class DELPHICLASS TLbRSA;
class PASCALIMPLEMENTATION TLbRSA : public Lbasym::TLbAsymmetricCipher
{
	typedef Lbasym::TLbAsymmetricCipher inherited;
	
protected:
	TLbRSAKey* FPrivateKey;
	TLbRSAKey* FPublicKey;
	System::Byte FPrimeTestIterations;
	virtual void __fastcall SetKeySize(Lbasym::TLbAsymKeySize Value);
	
public:
	__fastcall virtual TLbRSA(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbRSA(void);
	virtual void __fastcall DecryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile);
	virtual void __fastcall DecryptStream(Classes::TStream* InStream, Classes::TStream* OutStream);
	virtual System::AnsiString __fastcall DecryptStringA(const System::AnsiString InString);
	virtual System::UnicodeString __fastcall DecryptStringW(const System::UnicodeString InString);
	virtual void __fastcall EncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile);
	virtual void __fastcall EncryptStream(Classes::TStream* InStream, Classes::TStream* OutStream);
	virtual System::AnsiString __fastcall EncryptStringA(const System::AnsiString InString);
	virtual System::UnicodeString __fastcall EncryptStringW(const System::UnicodeString InString);
	virtual void __fastcall GenerateKeyPair(void);
	virtual unsigned __fastcall OutBufSizeNeeded(unsigned InBufSize);
	void __fastcall RSACallback(bool &Abort);
	__property TLbRSAKey* PrivateKey = {read=FPrivateKey};
	__property TLbRSAKey* PublicKey = {read=FPublicKey};
	
__published:
	__property System::Byte PrimeTestIterations = {read=FPrimeTestIterations, write=FPrimeTestIterations, nodefault};
	__property KeySize;
	__property OnProgress;
};


class DELPHICLASS TLbRSASSA;
class PASCALIMPLEMENTATION TLbRSASSA : public Lbasym::TLbSignature
{
	typedef Lbasym::TLbSignature inherited;
	
protected:
	TLbRSAKey* FPrivateKey;
	TLbRSAKey* FPublicKey;
	TRSAHashMethod FHashMethod;
	System::Byte FPrimeTestIterations;
	Lbbigint::TLbBigInt* FSignature;
	TLbRSAGetSignatureEvent FOnGetSignature;
	void __fastcall DoGetSignature(void);
	void __fastcall EncryptHash(const void *HashDigest, unsigned DigestLen);
	void __fastcall DecryptHash(void *HashDigest, unsigned DigestLen);
	void __fastcall RSACallback(bool &Abort);
	virtual void __fastcall SetKeySize(Lbasym::TLbAsymKeySize Value);
	
public:
	__fastcall virtual TLbRSASSA(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbRSASSA(void);
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
	__property TLbRSAKey* PrivateKey = {read=FPrivateKey};
	__property TLbRSAKey* PublicKey = {read=FPublicKey};
	__property Lbbigint::TLbBigInt* Signature = {read=FSignature};
	
__published:
	__property TRSAHashMethod HashMethod = {read=FHashMethod, write=FHashMethod, nodefault};
	__property System::Byte PrimeTestIterations = {read=FPrimeTestIterations, write=FPrimeTestIterations, nodefault};
	__property KeySize;
	__property TLbRSAGetSignatureEvent OnGetSignature = {read=FOnGetSignature, write=FOnGetSignature};
	__property OnProgress;
};


//-- var, const, procedure ---------------------------------------------------
static const ShortInt cRSAMinPadBytes = 0xb;
extern PACKAGE StaticArray<System::Word, 5> cRSACipherBlockSize;
extern PACKAGE StaticArray<System::Word, 5> cRSAPlainBlockSize;
extern PACKAGE void __fastcall GenerateRSAKeys(TLbRSAKey* &PrivateKey, TLbRSAKey* &PublicKey);
extern PACKAGE void __fastcall GenerateRSAKeysEx(TLbRSAKey* &PrivateKey, TLbRSAKey* &PublicKey, Lbasym::TLbAsymKeySize KeySize, System::Byte PrimeTestIterations, TLbRSACallback Callback);
extern PACKAGE int __fastcall EncryptRSAEx(TLbRSAKey* PublicKey, Sysutils::PByteArray pInBlock, Sysutils::PByteArray pOutBlock, int InDataSize);
extern PACKAGE int __fastcall DecryptRSAEx(TLbRSAKey* PrivateKey, Sysutils::PByteArray pInBlock, Sysutils::PByteArray pOutBlock);
extern PACKAGE int __fastcall EncryptRSA128(TLbRSAKey* PublicKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall DecryptRSA128(TLbRSAKey* PrivateKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall EncryptRSA256(TLbRSAKey* PublicKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall DecryptRSA256(TLbRSAKey* PrivateKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall EncryptRSA512(TLbRSAKey* PublicKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall DecryptRSA512(TLbRSAKey* PrivateKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall EncryptRSA768(TLbRSAKey* PublicKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall DecryptRSA768(TLbRSAKey* PrivateKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall EncryptRSA1024(TLbRSAKey* PublicKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall DecryptRSA1024(TLbRSAKey* PrivateKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall EncryptRSA(TLbRSAKey* PublicKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE int __fastcall DecryptRSA(TLbRSAKey* PrivateKey, System::Byte const *InBlock, System::Byte *OutBlock);
extern PACKAGE void __fastcall RSAEncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile, TLbRSAKey* Key, bool Encrypt);
extern PACKAGE void __fastcall RSAEncryptStream(Classes::TStream* InStream, Classes::TStream* OutStream, TLbRSAKey* Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall RSAEncryptString(const System::AnsiString InString, TLbRSAKey* Key, bool Encrypt);
extern PACKAGE System::AnsiString __fastcall RSAEncryptStringA(const System::AnsiString InString, TLbRSAKey* Key, bool Encrypt);
extern PACKAGE System::UnicodeString __fastcall RSAEncryptStringW(const System::UnicodeString InString, TLbRSAKey* Key, bool Encrypt);

}	/* namespace Lbrsa */
using namespace Lbrsa;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LbrsaHPP
