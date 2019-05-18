/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  return ~ ((~x)&(~y));
      
}
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
    int x = 0; 
    int y = 85;
    
    x =  x | y; 
    x = x << 8;
    
    x = x | y; 
    x = x << 8; 
    
    x = x | y; 
    x = x << 8; 
    
    x = x | y;
    
    return x;
    
}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
    int x = 0;
    return ~x;
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
    int y = 0;
        
   // y = y | 85; 
    y = y |0x55;
    
    y = y << 8;
    
    y = y | 0x55; 
    y = y << 8; 
    
    y = y | 0x55; 
    y = y << 8; 
    
    y = y | 0x55;
    
    x = x & y;
    
    return !(x ^ y);
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
    int y = 0;
    
    y = y | 85; 
    y = y << 8;
    
    y = y | 85; 
    y = y << 8; 
    
    y = y | 85; 
    y = y << 8; 
    
    y = ~(y | 85);
    
    x = x & y;
    return !(!(x));
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    
    int n8 = n << 3; //multiplying by 8
    int m8 = m << 3;
    // shift all 1 bytes to the left for each byte to swap
    int mask = ((0xFF << n8) | (0xFF<<m8));
    // taking the inverse of it
    int invmask = ~mask;
    // shifting the byte and isolating it
    int b1 = (x >> n8) & 0x000000FF; 
    int b2 = (x >> m8) & 0x000000FF;
    //
    int z1 = (x & invmask);
    int z2 = (b1 << m8);
    int z3 = z1 | z2;
    int z4 = (b2 << n8);
    int z5 = z3 | z4;
    return z5; 
    
    
    
    
    //int mult = 0xff << (n << 3);
    //int mult2 = 0xff << (m << 3);
    //int one = mult & 
   // int a = 0xff; //setting variable to 8 bit 1's 
    // isolate
    //int initial_shift = (a << n) & x; 
    // isolation of m variable 
    //int second_shift = (a << m) & x;
    // step 1: left shift byte 3 positions for both n and m, it shifts by 8, and 24 in the class example 
    //int first = n << 8; 
    //int second = m << 24;
    
    // step 2: extract byte using and operation 
    
    //n = n & a;
    //m = m & a;
    // step 3: shift by 8, and shift by 24
    
    // step 4: After extracting the bytes, right shift by 24, and right shift by 8 
    // step 5: to leave the rest, mask and use a negation to get remaining bytes. 
    
 //   n = x & (a << 8);//
   // m = x & (a << 8);//
    
    //return x | initial_shift;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
    
    
    // 1 0 0 is -4, the two zeros can be a maximum of 3
    // two numbers that are added must have same significant bit and must difer from the result
    // To determine: (MSB OF X = = MSB OF Y) & (MSB OF X) = MSB OF
    // use xor
    
    // move signed bit of x to lsb
    int x1 = (x>>31);
    // move signed bit of y to lsb
    int y1 = (y>>31);
    // lsb of sum into sum 1 
    int sum1 = (x+y)>>31;
    int sum_xor_x1 = (sum1 ^ x1);
    //true if only one sign bit is set
    int x1_xor_y1 = x1 ^ y1;
    //negate exclusive sign bit in final calc
    // This way, both are positive or both are negative
    // Overflow occurs when that is true and sum sign bit not the same as x1
    // compound statement will be true, return ! to indicate error
    int areBothTrue = (!x1_xor_y1 & sum_xor_x1);
    // both true, we have an overflow
    return !areBothTrue; 
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    // 2 ? 4 
    // not x = !2 = 0;
    // mask = 0 + ~ 0
    // ( ~ mask )
    
    int var = 0x00; 
    int mask = !x + ~var;
    int total = ((~mask)&z) | ((mask) & y);
    
    return total;
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    /* To compute 2's complement subtraction:
    Negate x: 1) reverse all bits 2) add 1 to form -x
    add -x and y 
    doscard any bits greater than n ????
    */
    
    // 1) 1000...00000000 <- bigneg
    // 2) 1000...00111001 <- bigneg | 0x39
    // 3) 0111...11000110 <- ~(bigneg | 0x39) <= less than
    // 4) 0000...00110000 <- 0x30
    // 5) 1111...11001111 <- ~0x30
    int bignegative = 1 << 31;      //1)
    int overflowpoint = ~(bignegative | 0x39);  //3)
    int nearlybiggestneg = ~0x30;              // 5)
    int toobig = bignegative & (overflowpoint+x) >> 31; 
    int toosmall = bignegative & (nearlybiggestneg + 1 + x) >> 31;
    return !(toobig | toosmall);
    
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
    int n8 = n << 3; 
    int mask = 0xff << n8;
    int mask_bar = ~mask;
    int c2 = c << n8;
    int y_partial = x & mask_bar; 
    int y = y_partial | c2;
    return y;
    
    
  return 2;
}
/* reverseBits - reverse the bits in a 32-bit integer,
              i.e. b0 swaps with b31, b1 with b30, etc
 *  Examples: reverseBits(0x11111111) = 0x88888888
 *            reverseBits(0xdeadbeef) = 0xf77db57b
 *            reverseBits(0x88888888) = 0x11111111
 *            reverseBits(0)  = 0
 *            reverseBits(-1) = -1
 *            reverseBits(0x9) = 0x90000000
 *  Legal ops: ! ~ & ^ | + << >> and unsigned int type
 *  Max ops: 90
 *  Rating: 4
 */
int reverseBits(int x) {
    /*step 1: swap odd and even bits
      step 2: swap pair of bits
      step 3: swap a nibble (4 bits)
      step 4: swap a byte
      THIS WORKS FOR 16 BITS
      
      For 32 bits, 
      One more step: swap two bytes.
    */
    
    int m1r = (x >> 1) & 0x55555555u; // shift one bit right 5 - 1010
    int m1l = (x & 0x55555555u) << 1; // shift one bit right
    int m1b = m1r | m1l;
    
    int m2r = (m1b >> 2) & 0x33333333u; // shift pairs 2 bits 3 = 0011
    int m2l = (m1b & 0x33333333u) << 2;
    int m2b = m2r | m2l; 
    
    int m4r = (m2b >> 4) & 0x0f0f0f0fu; // shift nibbles 4 bits 0F =00001111;
    int m4l = (m2b & 0x0f0f0f0fu) << 4;
    int m4b = m4r | m4l;
    
    int m8r = (m4b >> 8) & 0x00ff00ffu; // shift bytes 8 bits 00FF = 00001111
    int m8l = (m4b & 0x00ff00ffu) << 8;
    int m8b = m8l | m8r;
    
    int m16r = (m8b >> 16) & 0x0000ffffu; // shift 2 byte words 
    int m16l = (m8b & 0x0000ffffu) << 16; // shift 2 byte words
    int ans = m16r | m16l;
    return ans;
}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
    /* 
    Two numbers a and b 
    a - b = a + -b 
    Once you do this, verify if overflow or underflow is happening
    */
    int sum = x + y; 
    int sum_xor_x = sum ^ x;
    int sum_xor_y = sum ^y;
    // if sign (sum_xor_x) == 0 then same sign 
    // if sign(sum_xor_y) == 0 then same sign again
    // xor to test if sum xor against x and y are same 
    // if same then they overflow
    // shift it down to act as bool. then shift it
    // up to msb to act as check
    // return xor of
    
    int overflowBit = (sum_xor_x & sum_xor_y) >> 31;
    int overflowMsb = overflowBit << 31; // move it back to sign bit
    return (sum >> overflowBit) ^ overflowMsb;
    
  
}
/*
 * Extra credit
 */
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  return 2;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  return 2;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  return 2;
}
