LockBox 2.08 for 64 bit Delphi, FPC and Kylix

This version introduces 64 bit support to the LockBox2. It is based on
Sebastian Zierer's version of LockBox. Please read readme-tiburon.txt
for his original changes.

Biggest changes:

1. Changes in asm code

The original LockBox had 32 bit asm-code, which prevented it from being
compiled on 64 bit FPC. I and Arthur Pijpers wrote pascal versions of
those. All the old asm code is still used with 32 bit Delphi.
Sebastian Zierer also wrote new assembly code for 64 bit Delphi. 

If you try to compile LockBox2 on other non-intel platforms that FPC
supports, use {$DEFINE NO_ASSEMBLY} to use the pascal code.

2. Changes in the way random numbers are used

There are several places where LockBox2 needs random numbers. All these
places used to have lots of ifdefs for Kylix compatibility. To clean up
the code, all these were changed to call new functions in LbRandom.pas:

function LbSysRandom32: DWORD;
function lbSysRandomByte: Byte;

These two contain all the complexity of obtaining high quality random
numbers in different operating systems and programming languages.

The source of random numbers are controlled by these ifdefs:

{$DEFINE USE_DEV_RANDOM}   // Uses /dev/random on Linux
{$DEFINE USE_DEV_URANDOM}  // Uses /dev/urandom on Linux
{$DEFINE HAS_ARC4RANDOM}   // For platforms that do have arc4random

If a random number can't be obtained from a cryptographically secure
random number source, TSha1HashRandom is used as a source for high quality
random numbers. TSha1HashRandom is new SHA1-based random number generator.

LbRandom.pas also contains a new procedure, that can be used to fill buffers
with random content: lbSysRandomBuff.

NOTICE!

Even though this code works with FPC and Lazarus, I haven't created any
packages for Lazarus. No changes have been made to packages and examples,
so there's no guarantee that they will work on Delphi and Kylix.

Contributions are welcome.

Jarto Tarpio

