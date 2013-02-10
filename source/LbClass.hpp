// CodeGear C++Builder
// Copyright (c) 1995, 2008 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Lbclass.pas' rev: 20.00

#ifndef LbclassHPP
#define LbclassHPP

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
#include <Lbcipher.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Lbclass
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TLBBaseComponent;
class PASCALIMPLEMENTATION TLBBaseComponent : public Lbcipher::TLBBase
{
	typedef Lbcipher::TLBBase inherited;
	
protected:
	System::UnicodeString __fastcall GetVersion();
	void __fastcall SetVersion(const System::UnicodeString Value);
	
__published:
	__property System::UnicodeString Version = {read=GetVersion, write=SetVersion, stored=false};
public:
	/* TComponent.Create */ inline __fastcall virtual TLBBaseComponent(Classes::TComponent* AOwner) : Lbcipher::TLBBase(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TLBBaseComponent(void) { }
	
};


#pragma option push -b-
enum TLbCipherMode { cmECB, cmCBC };
#pragma option pop

class DELPHICLASS TLbCipher;
class PASCALIMPLEMENTATION TLbCipher : public TLBBaseComponent
{
	typedef TLBBaseComponent inherited;
	
public:
	__fastcall virtual TLbCipher(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbCipher(void);
	unsigned __fastcall DecryptBuffer(const void *InBuf, unsigned InBufSize, void *OutBuf);
	unsigned __fastcall EncryptBuffer(const void *InBuf, unsigned InBufSize, void *OutBuf);
	virtual void __fastcall DecryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile) = 0 ;
	virtual void __fastcall DecryptStream(Classes::TStream* InStream, Classes::TStream* OutStream) = 0 ;
	System::AnsiString __fastcall DecryptString(const System::AnsiString InString);
	virtual System::AnsiString __fastcall DecryptStringA(const System::AnsiString InString) = 0 ;
	virtual System::UnicodeString __fastcall DecryptStringW(const System::UnicodeString InString) = 0 ;
	virtual void __fastcall EncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile) = 0 ;
	virtual void __fastcall EncryptStream(Classes::TStream* InStream, Classes::TStream* OutStream) = 0 ;
	System::AnsiString __fastcall EncryptString(const System::AnsiString InString);
	virtual System::AnsiString __fastcall EncryptStringA(const System::AnsiString InString) = 0 ;
	virtual System::UnicodeString __fastcall EncryptStringW(const System::UnicodeString InString) = 0 ;
	virtual unsigned __fastcall OutBufSizeNeeded(unsigned InBufSize) = 0 ;
};


class DELPHICLASS TLbSymmetricCipher;
class PASCALIMPLEMENTATION TLbSymmetricCipher : public TLbCipher
{
	typedef TLbCipher inherited;
	
protected:
	TLbCipherMode FCipherMode;
	
public:
	__fastcall virtual TLbSymmetricCipher(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbSymmetricCipher(void);
	void __fastcall GenerateKey(const System::AnsiString Passphrase);
	virtual void __fastcall GenerateKeyA(const System::AnsiString Passphrase) = 0 ;
	virtual void __fastcall GenerateKeyW(const System::UnicodeString Passphrase) = 0 ;
	virtual void __fastcall GenerateRandomKey(void) = 0 ;
	__property TLbCipherMode CipherMode = {read=FCipherMode, write=FCipherMode, nodefault};
};


class DELPHICLASS TLbBlowfish;
class PASCALIMPLEMENTATION TLbBlowfish : public TLbSymmetricCipher
{
	typedef TLbSymmetricCipher inherited;
	
protected:
	Lbcipher::TKey128 FKey;
	
public:
	__fastcall virtual TLbBlowfish(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbBlowfish(void);
	virtual void __fastcall DecryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile);
	virtual void __fastcall DecryptStream(Classes::TStream* InStream, Classes::TStream* OutStream);
	virtual System::AnsiString __fastcall DecryptStringA(const System::AnsiString InString);
	virtual System::UnicodeString __fastcall DecryptStringW(const System::UnicodeString InString);
	virtual void __fastcall EncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile);
	virtual void __fastcall EncryptStream(Classes::TStream* InStream, Classes::TStream* OutStream);
	virtual System::AnsiString __fastcall EncryptStringA(const System::AnsiString InString);
	virtual System::UnicodeString __fastcall EncryptStringW(const System::UnicodeString InString);
	virtual void __fastcall GenerateKeyA(const System::AnsiString Passphrase);
	virtual void __fastcall GenerateKeyW(const System::UnicodeString Passphrase);
	virtual void __fastcall GenerateRandomKey(void);
	void __fastcall GetKey(System::Byte *Key);
	void __fastcall SetKey(System::Byte const *Key);
	virtual unsigned __fastcall OutBufSizeNeeded(unsigned InBufSize);
	
__published:
	__property CipherMode;
};


class DELPHICLASS TLbDES;
class PASCALIMPLEMENTATION TLbDES : public TLbSymmetricCipher
{
	typedef TLbSymmetricCipher inherited;
	
protected:
	Lbcipher::TKey64 FKey;
	
public:
	__fastcall virtual TLbDES(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbDES(void);
	virtual void __fastcall DecryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile);
	virtual void __fastcall DecryptStream(Classes::TStream* InStream, Classes::TStream* OutStream);
	virtual System::AnsiString __fastcall DecryptStringA(const System::AnsiString InString);
	virtual System::UnicodeString __fastcall DecryptStringW(const System::UnicodeString InString);
	virtual void __fastcall EncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile);
	virtual void __fastcall EncryptStream(Classes::TStream* InStream, Classes::TStream* OutStream);
	virtual System::AnsiString __fastcall EncryptStringA(const System::AnsiString InString);
	virtual System::UnicodeString __fastcall EncryptStringW(const System::UnicodeString InString);
	virtual void __fastcall GenerateKeyA(const System::AnsiString Passphrase);
	virtual void __fastcall GenerateKeyW(const System::UnicodeString Passphrase);
	virtual void __fastcall GenerateRandomKey(void);
	void __fastcall GetKey(System::Byte *Key);
	void __fastcall SetKey(System::Byte const *Key);
	virtual unsigned __fastcall OutBufSizeNeeded(unsigned InBufSize);
	
__published:
	__property CipherMode;
};


class DELPHICLASS TLb3DES;
class PASCALIMPLEMENTATION TLb3DES : public TLbSymmetricCipher
{
	typedef TLbSymmetricCipher inherited;
	
protected:
	Lbcipher::TKey128 FKey;
	
public:
	__fastcall virtual TLb3DES(Classes::TComponent* AOwner);
	__fastcall virtual ~TLb3DES(void);
	virtual void __fastcall DecryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile);
	virtual void __fastcall DecryptStream(Classes::TStream* InStream, Classes::TStream* OutStream);
	virtual System::AnsiString __fastcall DecryptStringA(const System::AnsiString InString);
	virtual System::UnicodeString __fastcall DecryptStringW(const System::UnicodeString InString);
	virtual void __fastcall EncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile);
	virtual void __fastcall EncryptStream(Classes::TStream* InStream, Classes::TStream* OutStream);
	virtual System::AnsiString __fastcall EncryptStringA(const System::AnsiString InString);
	virtual System::UnicodeString __fastcall EncryptStringW(const System::UnicodeString InString);
	virtual void __fastcall GenerateKeyA(const System::AnsiString Passphrase);
	virtual void __fastcall GenerateKeyW(const System::UnicodeString Passphrase);
	virtual void __fastcall GenerateRandomKey(void);
	void __fastcall GetKey(System::Byte *Key);
	void __fastcall SetKey(System::Byte const *Key);
	virtual unsigned __fastcall OutBufSizeNeeded(unsigned InBufSize);
	
__published:
	__property CipherMode;
};


#pragma option push -b-
enum TLbKeySizeRDL { ks128, ks192, ks256 };
#pragma option pop

class DELPHICLASS TLbRijndael;
class PASCALIMPLEMENTATION TLbRijndael : public TLbSymmetricCipher
{
	typedef TLbSymmetricCipher inherited;
	
protected:
	Lbcipher::TKey256 FKey;
	TLbKeySizeRDL FKeySize;
	int FKeySizeBytes;
	void __fastcall SetKeySize(TLbKeySizeRDL Value);
	
public:
	__fastcall virtual TLbRijndael(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbRijndael(void);
	virtual void __fastcall DecryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile);
	virtual void __fastcall DecryptStream(Classes::TStream* InStream, Classes::TStream* OutStream);
	virtual System::AnsiString __fastcall DecryptStringA(const System::AnsiString InString);
	virtual System::UnicodeString __fastcall DecryptStringW(const System::UnicodeString InString);
	virtual void __fastcall EncryptFile(const System::UnicodeString InFile, const System::UnicodeString OutFile);
	virtual void __fastcall EncryptStream(Classes::TStream* InStream, Classes::TStream* OutStream);
	virtual System::AnsiString __fastcall EncryptStringA(const System::AnsiString InString);
	virtual System::UnicodeString __fastcall EncryptStringW(const System::UnicodeString InString);
	virtual void __fastcall GenerateKeyA(const System::AnsiString Passphrase);
	virtual void __fastcall GenerateKeyW(const System::UnicodeString Passphrase);
	virtual void __fastcall GenerateRandomKey(void);
	void __fastcall GetKey(void *Key);
	void __fastcall SetKey(const void *Key);
	virtual unsigned __fastcall OutBufSizeNeeded(unsigned InBufSize);
	
__published:
	__property CipherMode;
	__property TLbKeySizeRDL KeySize = {read=FKeySize, write=SetKeySize, nodefault};
};


class DELPHICLASS TLbHash;
class PASCALIMPLEMENTATION TLbHash : public TLBBaseComponent
{
	typedef TLBBaseComponent inherited;
	
protected:
	StaticArray<System::Byte, 1024> FBuf;
	
public:
	__fastcall virtual TLbHash(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbHash(void);
	virtual void __fastcall HashBuffer(const void *Buf, unsigned BufSize) = 0 ;
	virtual void __fastcall HashFile(const System::UnicodeString AFileName) = 0 ;
	virtual void __fastcall HashStream(Classes::TStream* AStream) = 0 ;
	void __fastcall HashString(const System::AnsiString AStr);
	virtual void __fastcall HashStringA(const System::AnsiString AStr) = 0 ;
	virtual void __fastcall HashStringW(const System::UnicodeString AStr) = 0 ;
};


class DELPHICLASS TLbMD5;
class PASCALIMPLEMENTATION TLbMD5 : public TLbHash
{
	typedef TLbHash inherited;
	
protected:
	Lbcipher::TMD5Digest FDigest;
	
public:
	__fastcall virtual TLbMD5(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbMD5(void);
	void __fastcall GetDigest(System::Byte *Digest);
	virtual void __fastcall HashBuffer(const void *Buf, unsigned BufSize);
	virtual void __fastcall HashFile(const System::UnicodeString AFileName);
	virtual void __fastcall HashStream(Classes::TStream* AStream);
	virtual void __fastcall HashStringA(const System::AnsiString AStr);
	virtual void __fastcall HashStringW(const System::UnicodeString AStr);
};


class DELPHICLASS TLbSHA1;
class PASCALIMPLEMENTATION TLbSHA1 : public TLbHash
{
	typedef TLbHash inherited;
	
protected:
	Lbcipher::TSHA1Digest FDigest;
	
public:
	__fastcall virtual TLbSHA1(Classes::TComponent* AOwner);
	__fastcall virtual ~TLbSHA1(void);
	void __fastcall GetDigest(System::Byte *Digest);
	virtual void __fastcall HashBuffer(const void *Buf, unsigned BufSize);
	virtual void __fastcall HashFile(const System::UnicodeString AFileName);
	virtual void __fastcall HashStream(Classes::TStream* AStream);
	virtual void __fastcall HashStringA(const System::AnsiString AStr);
	virtual void __fastcall HashStringW(const System::UnicodeString AStr);
};


class DELPHICLASS TLbSCStream;
class PASCALIMPLEMENTATION TLbSCStream : public Classes::TMemoryStream
{
	typedef Classes::TMemoryStream inherited;
	
protected:
	Lbcipher::TLSCContext FContext;
	
public:
	__fastcall TLbSCStream(const void *Key, int KeySize);
	DYNAMIC void __fastcall Reinitialize(const void *Key, int KeySize);
	DYNAMIC void __fastcall ChangeKey(const void *Key, int KeySize);
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Write(const void *Buffer, int Count);
public:
	/* TMemoryStream.Destroy */ inline __fastcall virtual ~TLbSCStream(void) { }
	
};


class DELPHICLASS TLbSCFileStream;
class PASCALIMPLEMENTATION TLbSCFileStream : public Classes::TFileStream
{
	typedef Classes::TFileStream inherited;
	
protected:
	Lbcipher::TLSCContext FContext;
	
public:
	__fastcall TLbSCFileStream(const System::UnicodeString FileName, System::Word Mode, const void *Key, int KeySize);
	DYNAMIC void __fastcall Reinitialize(const void *Key, int KeySize);
	DYNAMIC void __fastcall ChangeKey(const void *Key, int KeySize);
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Write(const void *Buffer, int Count);
public:
	/* TFileStream.Destroy */ inline __fastcall virtual ~TLbSCFileStream(void) { }
	
};


class DELPHICLASS TLbRNG32Stream;
class PASCALIMPLEMENTATION TLbRNG32Stream : public Classes::TMemoryStream
{
	typedef Classes::TMemoryStream inherited;
	
protected:
	Lbcipher::TRNG32Context FContext;
	
public:
	__fastcall TLbRNG32Stream(const int Key);
	DYNAMIC void __fastcall Reinitialize(const int Key);
	DYNAMIC void __fastcall ChangeKey(const int Key);
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Write(const void *Buffer, int Count);
public:
	/* TMemoryStream.Destroy */ inline __fastcall virtual ~TLbRNG32Stream(void) { }
	
};


class DELPHICLASS TLbRNG32FileStream;
class PASCALIMPLEMENTATION TLbRNG32FileStream : public Classes::TFileStream
{
	typedef Classes::TFileStream inherited;
	
protected:
	Lbcipher::TRNG32Context FContext;
	
public:
	__fastcall TLbRNG32FileStream(const System::UnicodeString FileName, System::Word Mode, const int Key);
	DYNAMIC void __fastcall Reinitialize(const int Key);
	DYNAMIC void __fastcall ChangeKey(const int Key);
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Write(const void *Buffer, int Count);
public:
	/* TFileStream.Destroy */ inline __fastcall virtual ~TLbRNG32FileStream(void) { }
	
};


class DELPHICLASS TLbRNG64Stream;
class PASCALIMPLEMENTATION TLbRNG64Stream : public Classes::TMemoryStream
{
	typedef Classes::TMemoryStream inherited;
	
protected:
	Lbcipher::TRNG64Context FContext;
	
public:
	__fastcall TLbRNG64Stream(const int KeyHi, const int KeyLo);
	DYNAMIC void __fastcall Reinitialize(const int KeyHi, const int KeyLo);
	DYNAMIC void __fastcall ChangeKey(const int KeyHi, const int KeyLo);
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Write(const void *Buffer, int Count);
public:
	/* TMemoryStream.Destroy */ inline __fastcall virtual ~TLbRNG64Stream(void) { }
	
};


class DELPHICLASS TLbRNG64FileStream;
class PASCALIMPLEMENTATION TLbRNG64FileStream : public Classes::TFileStream
{
	typedef Classes::TFileStream inherited;
	
protected:
	Lbcipher::TRNG64Context FContext;
	
public:
	__fastcall TLbRNG64FileStream(const System::UnicodeString FileName, System::Word Mode, const int KeyHi, const int KeyLo);
	DYNAMIC void __fastcall Reinitialize(const int KeyHi, const int KeyLo);
	DYNAMIC void __fastcall ChangeKey(const int KeyHi, const int KeyLo);
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Write(const void *Buffer, int Count);
public:
	/* TFileStream.Destroy */ inline __fastcall virtual ~TLbRNG64FileStream(void) { }
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Lbclass */
using namespace Lbclass;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LbclassHPP
