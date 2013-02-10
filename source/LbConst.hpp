// CodeGear C++Builder
// Copyright (c) 1995, 2008 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Lbconst.pas' rev: 20.00

#ifndef LbconstHPP
#define LbconstHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Lbconst
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const ShortInt cBytes128 = 0x10;
static const ShortInt cBytes160 = 0x14;
static const ShortInt cBytes192 = 0x18;
static const ShortInt cBytes256 = 0x20;
static const ShortInt cBytes512 = 0x40;
static const ShortInt cBytes768 = 0x60;
static const Byte cBytes1024 = 0x80;
static const ShortInt cDefIterations = 0x14;
static const ShortInt ASN1_TYPE_SEQUENCE = 0x10;
static const ShortInt ASN1_TYPE_Integer = 0x2;
static const ShortInt ASN1_TAG_NUM_MASK = 0x1f;
static const ShortInt ASN1_TYPE_HIGH_TAG_NUMBER = 0x1f;
static const Byte HIGH_BIT_MASK = 0x80;
static const ShortInt BIT_MASK_7F = 0x7f;
extern PACKAGE System::ResourceString _sLbVersion;
#define Lbconst_sLbVersion System::LoadResourceString(&Lbconst::_sLbVersion)
extern PACKAGE System::ResourceString _sBIBufferUnderflow;
#define Lbconst_sBIBufferUnderflow System::LoadResourceString(&Lbconst::_sBIBufferUnderflow)
extern PACKAGE System::ResourceString _sBIBufferNotAssigned;
#define Lbconst_sBIBufferNotAssigned System::LoadResourceString(&Lbconst::_sBIBufferNotAssigned)
extern PACKAGE System::ResourceString _sBINoNumber;
#define Lbconst_sBINoNumber System::LoadResourceString(&Lbconst::_sBINoNumber)
extern PACKAGE System::ResourceString _sBISubtractErr;
#define Lbconst_sBISubtractErr System::LoadResourceString(&Lbconst::_sBISubtractErr)
extern PACKAGE System::ResourceString _sBIZeroDivide;
#define Lbconst_sBIZeroDivide System::LoadResourceString(&Lbconst::_sBIZeroDivide)
extern PACKAGE System::ResourceString _sBIQuotientErr;
#define Lbconst_sBIQuotientErr System::LoadResourceString(&Lbconst::_sBIQuotientErr)
extern PACKAGE System::ResourceString _sBIZeroFactor;
#define Lbconst_sBIZeroFactor System::LoadResourceString(&Lbconst::_sBIZeroFactor)
extern PACKAGE System::ResourceString _sBIIterationCount;
#define Lbconst_sBIIterationCount System::LoadResourceString(&Lbconst::_sBIIterationCount)
extern PACKAGE System::ResourceString _sASNKeyTooLarge;
#define Lbconst_sASNKeyTooLarge System::LoadResourceString(&Lbconst::_sASNKeyTooLarge)
extern PACKAGE System::ResourceString _sASNKeyBufferOverflow;
#define Lbconst_sASNKeyBufferOverflow System::LoadResourceString(&Lbconst::_sASNKeyBufferOverflow)
extern PACKAGE System::ResourceString _sASNKeyBadModulus;
#define Lbconst_sASNKeyBadModulus System::LoadResourceString(&Lbconst::_sASNKeyBadModulus)
extern PACKAGE System::ResourceString _sASNKeyBadExponent;
#define Lbconst_sASNKeyBadExponent System::LoadResourceString(&Lbconst::_sASNKeyBadExponent)
extern PACKAGE System::ResourceString _sASNKeyBufferTooSmall;
#define Lbconst_sASNKeyBufferTooSmall System::LoadResourceString(&Lbconst::_sASNKeyBufferTooSmall)
extern PACKAGE System::ResourceString _sASNKeyBadKey;
#define Lbconst_sASNKeyBadKey System::LoadResourceString(&Lbconst::_sASNKeyBadKey)
extern PACKAGE System::ResourceString _sRSAKeyBadKey;
#define Lbconst_sRSAKeyBadKey System::LoadResourceString(&Lbconst::_sRSAKeyBadKey)
extern PACKAGE System::ResourceString _sModulusStringTooBig;
#define Lbconst_sModulusStringTooBig System::LoadResourceString(&Lbconst::_sModulusStringTooBig)
extern PACKAGE System::ResourceString _sExponentStringTooBig;
#define Lbconst_sExponentStringTooBig System::LoadResourceString(&Lbconst::_sExponentStringTooBig)
extern PACKAGE System::ResourceString _sRSAKeyPairErr;
#define Lbconst_sRSAKeyPairErr System::LoadResourceString(&Lbconst::_sRSAKeyPairErr)
extern PACKAGE System::ResourceString _sRSAPublicKeyErr;
#define Lbconst_sRSAPublicKeyErr System::LoadResourceString(&Lbconst::_sRSAPublicKeyErr)
extern PACKAGE System::ResourceString _sRSAPrivateKeyErr;
#define Lbconst_sRSAPrivateKeyErr System::LoadResourceString(&Lbconst::_sRSAPrivateKeyErr)
extern PACKAGE System::ResourceString _sRSAEncryptErr;
#define Lbconst_sRSAEncryptErr System::LoadResourceString(&Lbconst::_sRSAEncryptErr)
extern PACKAGE System::ResourceString _sRSADecryptErr;
#define Lbconst_sRSADecryptErr System::LoadResourceString(&Lbconst::_sRSADecryptErr)
extern PACKAGE System::ResourceString _sRSABlockSize128Err;
#define Lbconst_sRSABlockSize128Err System::LoadResourceString(&Lbconst::_sRSABlockSize128Err)
extern PACKAGE System::ResourceString _sRSABlockSize256Err;
#define Lbconst_sRSABlockSize256Err System::LoadResourceString(&Lbconst::_sRSABlockSize256Err)
extern PACKAGE System::ResourceString _sRSABlockSize512Err;
#define Lbconst_sRSABlockSize512Err System::LoadResourceString(&Lbconst::_sRSABlockSize512Err)
extern PACKAGE System::ResourceString _sRSABlockSize768Err;
#define Lbconst_sRSABlockSize768Err System::LoadResourceString(&Lbconst::_sRSABlockSize768Err)
extern PACKAGE System::ResourceString _sRSABlockSize1024Err;
#define Lbconst_sRSABlockSize1024Err System::LoadResourceString(&Lbconst::_sRSABlockSize1024Err)
extern PACKAGE System::ResourceString _sRSAEncodingErr;
#define Lbconst_sRSAEncodingErr System::LoadResourceString(&Lbconst::_sRSAEncodingErr)
extern PACKAGE System::ResourceString _sRSADecodingErrBTS;
#define Lbconst_sRSADecodingErrBTS System::LoadResourceString(&Lbconst::_sRSADecodingErrBTS)
extern PACKAGE System::ResourceString _sRSADecodingErrBTL;
#define Lbconst_sRSADecodingErrBTL System::LoadResourceString(&Lbconst::_sRSADecodingErrBTL)
extern PACKAGE System::ResourceString _sRSADecodingErrIBT;
#define Lbconst_sRSADecodingErrIBT System::LoadResourceString(&Lbconst::_sRSADecodingErrIBT)
extern PACKAGE System::ResourceString _sRSADecodingErrIBF;
#define Lbconst_sRSADecodingErrIBF System::LoadResourceString(&Lbconst::_sRSADecodingErrIBF)
extern PACKAGE System::ResourceString _sDSAKeyBadKey;
#define Lbconst_sDSAKeyBadKey System::LoadResourceString(&Lbconst::_sDSAKeyBadKey)
extern PACKAGE System::ResourceString _sDSAParametersPQGErr;
#define Lbconst_sDSAParametersPQGErr System::LoadResourceString(&Lbconst::_sDSAParametersPQGErr)
extern PACKAGE System::ResourceString _sDSAParametersXYErr;
#define Lbconst_sDSAParametersXYErr System::LoadResourceString(&Lbconst::_sDSAParametersXYErr)
extern PACKAGE System::ResourceString _sDSASignatureZeroR;
#define Lbconst_sDSASignatureZeroR System::LoadResourceString(&Lbconst::_sDSASignatureZeroR)
extern PACKAGE System::ResourceString _sDSASignatureZeroS;
#define Lbconst_sDSASignatureZeroS System::LoadResourceString(&Lbconst::_sDSASignatureZeroS)
extern PACKAGE System::ResourceString _sDSASignatureErr;
#define Lbconst_sDSASignatureErr System::LoadResourceString(&Lbconst::_sDSASignatureErr)
extern PACKAGE System::ResourceString _SNoStart;
#define Lbconst_SNoStart System::LoadResourceString(&Lbconst::_SNoStart)

}	/* namespace Lbconst */
using namespace Lbconst;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// LbconstHPP
