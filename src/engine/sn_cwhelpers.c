/* SN Systems runtime helpers for the CodeWarrior-compiled Nintendo SDK code:
   the runtime names that code calls for double-to-unsigned conversion and for
   64-bit shifts, division and remainder. The conversion is a small function;
   each 64-bit helper is a single branch to the matching libgcc routine. */

#if defined(DECOMP_COMPARE)
unsigned long __cvt_fp2unsigned(double d)
{
    if (d >= 2147483648.0)
        return (long)(d - 2147483648.0) ^ 0x80000000;
    return (long)d;
}
#endif

asm(".section \".text\"\n"
    ".align 2\n"
    "\n"
    ".globl __shr2u\n"
    ".type __shr2u,@function\n"
    "__shr2u:\n"
    "\tb __lshrdi3\n"
    ".size __shr2u,.-__shr2u\n"
    "\n"
    ".globl __div2i\n"
    ".type __div2i,@function\n"
    "__div2i:\n"
    "\tb __divdi3\n"
    ".size __div2i,.-__div2i\n"
    "\n"
    ".globl __shl2i\n"
    ".type __shl2i,@function\n"
    "__shl2i:\n"
    "\tb __ashldi3\n"
    ".size __shl2i,.-__shl2i\n"
    "\n"
    ".globl __mod2i\n"
    ".type __mod2i,@function\n"
    "__mod2i:\n"
    "\tb __moddi3\n"
    ".size __mod2i,.-__mod2i\n"
    "\n"
    ".globl __shr2i\n"
    ".type __shr2i,@function\n"
    "__shr2i:\n"
    "\tb __ashrdi3\n"
    ".size __shr2i,.-__shr2i\n"
    "\n"
    ".globl __div2u\n"
    ".type __div2u,@function\n"
    "__div2u:\n"
    "\tb __udivdi3\n"
    ".size __div2u,.-__div2u\n"
    "\n"
    ".globl __mod2u\n"
    ".type __mod2u,@function\n"
    "__mod2u:\n"
    "\tb __umoddi3\n"
    ".size __mod2u,.-__mod2u\n");
