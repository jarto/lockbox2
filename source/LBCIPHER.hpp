// CodeGear C++Builder
// Copyright (c) 1995, 2008 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Lbcipher.pas' rev: 20.00

#ifndef LbcipherHPP
#define LbcipherHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Lbcipher
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TLBBase;
class PASCALIMPLEMENTATION TLBBase : public Classes::TComponent
{
	typedef Classes::TComponent inherited;
	
public:
	/* TComponent.Create */ inline __fastcall virtual TLBBase(Classes::TComponent* AOwner) : Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TLBBase(void) { }
	
};


typedef StaticArray<int, 512000000> TLongIntArray;

typedef TLongIntArray *pLongIntArray;

#pragma pack(push,1)
struct TLongIntRec
{
	
	union
	{
		struct 
		{
			System::Byte LoLo;
			System::Byte LoHi;
			System::Byte HiLo;
			System::Byte HiHi;
			
		};
		struct 
		{
			System::Word Lo;
			System::Word Hi;
			
		};
		
	};
};
#pragma pack(pop)


#pragma pack(push,1)
struct TInt64
{
	
	union
	{
		struct 
		{
			System::Byte LoLoLo;
			System::Byte LoLoHi;
			System::Byte LoHiLo;
			System::Byte LoHiHi;
			System::Byte HiLoLo;
			System::Byte HiLoHi;
			System::Byte HiHiLo;
			System::Byte HiHiHi;
			
		};
		struct 
		{
			System::Word LoLo;
			System::Word LoHi;
			System::Word HiLo;
			System::Word HiHi;
			
		};
		struct 
		{
			int Lo;
			int Hi;
			
		};
		
	};
};
#pragma pack(pop)


struct TRDLVector
{
	
	#pragma pack(push,1)
	union
	{
		struct 
		{
			StaticArray<System::Byte, 4> bt;
			
		};
		struct 
		{
			unsigned dw;
			
		};
		
	};
	#pragma pack(pop)
};


typedef StaticArray<System::Byte, 8> TKey64;

typedef TKey64 *PKey64;

typedef StaticArray<System::Byte, 16> TKey128;

typedef TKey128 *PKey128;

typedef StaticArray<System::Byte, 24> TKey192;

typedef TKey192 *PKey192;

typedef StaticArray<System::Byte, 32> TKey256;

typedef TKey256 *PKey256;

typedef StaticArray<int, 4> TLBCBlock;

typedef TLBCBlock *PLBCBlock;

typedef StaticArray<System::Byte, 8> TDESBlock;

typedef StaticArray<int, 2> TLQCBlock;

typedef StaticArray<int, 2> TBFBlock;

typedef StaticArray<System::Byte, 16> TRDLBlock;

#pragma pack(push,1)
struct TBFContext
{
	
public:
	StaticArray<int, 18> PBox;
	StaticArray<StaticArray<int, 256>, 4> SBox;
};
#pragma pack(pop)


#pragma pack(push,1)
struct TDESContext
{
	
public:
	StaticArray<int, 32> TransformedKey;
	bool Encrypt;
};
#pragma pack(pop)


typedef StaticArray<TDESContext, 2> TTripleDESContext;

typedef StaticArray<TDESContext, 3> TTripleDESContext3Key;

#pragma pack(push,1)
struct TLBCContext
{
	
public:
	bool Encrypt;
	StaticArray<System::Byte, 3> Dummy;
	int Rounds;
	union
	{
		struct 
		{
			StaticArray<StaticArray<int, 8>, 4> SubKeysInts;
			
		};
		struct 
		{
			StaticArray<StaticArray<System::Byte, 8>, 16> SubKeys64;
			
		};
		
	};
};
#pragma pack(pop)


#pragma pack(push,1)
struct TRDLContext
{
	
public:
	bool Encrypt;
	StaticArray<System::Byte, 3> Dummy;
	unsigned Rounds;
	union
	{
		struct 
		{
			StaticArray<StaticArray<System::Byte, 16>, 15> Rk;
			
		};
		struct 
		{
			StaticArray<TRDLVector, 57> W;
			
		};
		
	};
};
#pragma pack(pop)


#pragma pack(push,1)
struct TLSCContext
{
	
public:
	int Index;
	int Accumulator;
	StaticArray<System::Byte, 256> SBox;
};
#pragma pack(pop)


typedef StaticArray<System::Byte, 4> TRNG32Context;

typedef StaticArray<System::Byte, 8> TRNG64Context;

typedef StaticArray<System::Byte, 16> TMD5Digest;

typedef StaticArray<System::Byte, 20> TSHA1Digest;

typedef StaticArray<System::Byte, 280> TLMDContext;

typedef StaticArray<System::Byte, 88> TMD5Context;

struct TSHA1Context
{
	
public:
	unsigned sdHi;
	unsigned sdLo;
	unsigned sdIndex;
	StaticArray<unsigned, 5> sdHash;
	StaticArray<System::Byte, 64> sdBuf;
};


//-- var, const, procedure ---------------------------------------------------
static const int MaxStructSize = 0x7a120000;
static const ShortInt BFRounds = 0x10;
static const ShortInt MaxRDLRounds = 0xe;
extern PACKAGE void __fastcall EncryptLBC(const TLBCContext &Context, int *Block);
extern PACKAGE void __fastcall EncryptLBCCBC(const TLBCContext &Context, int const *Prev, int *Block);
extern PACKAGE void __fastcall InitEncryptDES(System::Byte const *Key, TDESContext &Context, bool Encrypt);
extern PACKAGE void __fastcall InitEncryptLBC(System::Byte const *Key, TLBCContext &Context, int Rounds, bool Encrypt);
extern PACKAGE void __fastcall EncryptDES(const TDESContext &Context, System::Byte *Block);
extern PACKAGE void __fastcall EncryptDESCBC(const TDESContext &Context, System::Byte const *Prev, System::Byte *Block);
extern PACKAGE void __fastcall InitEncryptTripleDES(System::Byte const *Key, TDESContext *Context, bool Encrypt);
extern PACKAGE void __fastcall EncryptTripleDES(TDESContext const *Context, System::Byte *Block);
extern PACKAGE void __fastcall EncryptTripleDESCBC(TDESContext const *Context, System::Byte const *Prev, System::Byte *Block);
extern PACKAGE void __fastcall InitEncryptTripleDES3Key(System::Byte const *Key1, System::Byte const *Key2, System::Byte const *Key3, TDESContext *Context, bool Encrypt);
extern PACKAGE void __fastcall EncryptTripleDES3Key(TDESContext const *Context, System::Byte *Block);
extern PACKAGE void __fastcall EncryptTripleDESCBC3Key(TDESContext const *Context, System::Byte const *Prev, System::Byte *Block);
extern PACKAGE void __fastcall EncryptLQC(System::Byte const *Key, int *Block, bool Encrypt);
extern PACKAGE void __fastcall EncryptLQCCBC(System::Byte const *Key, int const *Prev, int *Block, bool Encrypt);
extern PACKAGE void __fastcall InitEncryptBF(System::Byte *Key, TBFContext &Context);
extern PACKAGE void __fastcall EncryptBF(const TBFContext &Context, int *Block, bool Encrypt);
extern PACKAGE void __fastcall EncryptBFCBC(const TBFContext &Context, int const *Prev, int *Block, bool Encrypt);
extern PACKAGE void __fastcall InitEncryptLSC(const void *Key, int KeySize, TLSCContext &Context);
extern PACKAGE void __fastcall EncryptLSC(TLSCContext &Context, void *Buf, int BufSize);
extern PACKAGE void __fastcall InitEncryptRNG32(int Key, TRNG32Context &Context);
extern PACKAGE void __fastcall EncryptRNG32(TRNG32Context &Context, void *Buf, int BufSize);
extern PACKAGE void __fastcall InitEncryptRNG64(int KeyHi, int KeyLo, System::Byte *Context);
extern PACKAGE void __fastcall EncryptRNG64(System::Byte *Context, void *Buf, int BufSize);
extern PACKAGE void __fastcall GenerateRandomKey(void *Key, int KeySize);
extern PACKAGE void __fastcall GenerateLMDKey(void *Key, int KeySize, const System::AnsiString Str);
extern PACKAGE void __fastcall GenerateLMDKeyA(void *Key, int KeySize, const System::AnsiString Str);
extern PACKAGE void __fastcall GenerateLMDKeyW(void *Key, int KeySize, const System::UnicodeString Str);
extern PACKAGE void __fastcall GenerateMD5Key(System::Byte *Key, const System::AnsiString Str);
extern PACKAGE void __fastcall GenerateMD5KeyA(System::Byte *Key, const System::AnsiString Str);
extern PACKAGE void __fastcall GenerateMD5KeyW(System::Byte *Key, const System::UnicodeString Str);
extern PACKAGE int __fastcall Ran01(int &Seed);
extern PACKAGE int __fastcall Ran02(int &Seed);
extern PACKAGE int __fastcall Ran03(int &Seed);
extern PACKAGE System::Byte __fastcall Random32Byte(int &Seed);
extern PACKAGE System::Byte __fastcall Random64Byte(TInt64 &Seed);
extern PACKAGE void __fastcall ShrinkDESKey(System::Byte *Key);
extern PACKAGE void __fastcall HashELF(int &Digest, const void *Buf, int BufSize);
extern PACKAGE void __fastcall StringHashELFW(int &Digest, const System::UnicodeString Str);
extern PACKAGE void __fastcall StringHashELFA(int &Digest, const System::AnsiString Str);
extern PACKAGE unsigned __fastcall RolX(unsigned I, unsigned C);
extern PACKAGE void __fastcall InitMD5(System::Byte *Context);
extern PACKAGE void __fastcall UpdateMD5(System::Byte *Context, const void *Buf, int BufSize);
extern PACKAGE void __fastcall FinalizeMD5(System::Byte *Context, System::Byte *Digest);
extern PACKAGE void __fastcall HashMD5(System::Byte *Digest, const void *Buf, int BufSize);
extern PACKAGE void __fastcall InitLMD(System::Byte *Context);
extern PACKAGE void __fastcall UpdateLMD(System::Byte *Context, const void *Buf, int BufSize);
extern PACKAGE void __fastcall FinalizeLMD(System::Byte *Context, void *Digest, int DigestSize);
extern PACKAGE void __fastcall HashLMD(void *Digest, int DigestSize, const void *Buf, int BufSize);
extern PACKAGE void __fastcall HashMix128(int &Digest, const void *Buf, int BufSize);
extern PACKAGE void __fastcall StringHashMix128W(int &Digest, const System::UnicodeString Str);
extern PACKAGE void __fastcall StringHashMix128A(int &Digest, const System::AnsiString Str);
extern PACKAGE void __fastcall StringHashMD5W(System::Byte *Digest, const System::UnicodeString Str);
extern PACKAGE void __fastcall StringHashMD5A(System::Byte *Digest, const System::AnsiString Str);
extern PACKAGE void __fastcall StringHashLMDW(void *Digest, int DigestSize, const System::UnicodeString Str);
extern PACKAGE void __fastcall StringHashLMDA(void *Digest, int DigestSize, const System::AnsiString Str);
extern PACKAGE void __fastcall XorMem(void *Mem1, const void *Mem2, unsigned Count);
extern PACKAGE void __fastcall HashSHA1(System::Byte *Digest, const void *Buf, int BufSize);
extern PACKAGE void __fastcall StringHashSHA1W(System::Byte *Digest, const System::UnicodeString Str);
extern PACKAGE void __fastcall StringHashSHA1A(System::Byte *Digest, const System::AnsiString Str);
extern PACKAGE void __fastcall InitSHA1(TSHA1Context &Context);
extern PACKAGE void __fastcall UpdateSHA1(TSHA1Context &Context, const void *Buf, int BufSize);
extern PACKAGE void __fastcall FinalizeSHA1(TSHA1Context &Context, System::Byte *Digest);
extern PACKAGE void __fastcall EncryptRDL(const TRDLContext &Context, System::Byte *Block);
extern PACKAGE void __fastcall EncryptRDLCBC(const TRDLContext &Context, System::Byte const *Prev, System::Byte *Block);
extern PACKAGE void __fastcall InitEncryptRDL(const void *Key, int KeySize, TRDLContext &Context, bool Encrypt);
extern PACKAGE void __fastcall StringHashELF(int &Digest, const System::AnsiString Str);
extern PACKAGE void __fastcall StringHashLMD(void *Digest, int DigestSize, const System::AnsiString Str);
extern PACKAGE void __fastcall StringHashMD5(System::Byte *Digest, const System::AnsiString Str);
extern PACKAGE void __fastcall StringHashMix128(int &Digest, const System::AnsiString Str);
extern PACKAGE void __fastcall StringHashSHA1(System::Byte *Digest, const System::AnsiString Str);

}	/* namespace Lbcipher */
using namespace Lbcipher;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LbcipherHPP
