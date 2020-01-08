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
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
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
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) { // using Demorgan's Law
  return ~(~x|~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {// first transform n bytes to n*2^3 bits. After right shift, using 0xff extract byte n
  return 0xff & (x>>(n<<3));
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >> 
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n)	{ // first I make 0x7fffffff(~(1<<31)). and arthmetic right shift n. it will be 00000....11111. and left shift, then it will be 0000....11110. so add 1 to th					  is to make 00000...1111111(#of 0 is n). to make first n bits 0, I use & with (x>>n) & 0000....11111.
  return (x>>n) & (((~(1<<31)>>n)<<1)+1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) { // first I make 00010001 00010001 00010001 00010001. and I check the number of 1s per 4 bits. and using right shift 16,12,8,4, save total number of 1s at first 4bits, using & and 0x0f, return total number of 1s.
	int base=(0x11|(0x11<<8));
	int sto1=0;
	int k1=0;
	int k2=0;
	int k3=0;
	int k4=0;
	base += base<<16;//00010001 00010001 00010001 00010001
	sto1+=x&base;
	sto1+=(x>>1)&base;
	sto1+=(x>>2)&base;
	sto1+=(x>>3)&base;// save number of 1s per 4bits
	sto1+=sto1>>16;
	k1=0x0f&sto1;
	k2=0x0f&(sto1>>4);
	k3=0x0f&(sto1>>8);
	k4=0x0f&(sto1>>12);// make sum of the number of 1s per 4bits at 1st byte.
	return k1+k2+k3+k4;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) { // compare the sign bit between x and -x(~x+1). if sign bit is different between x and -x, then x is not 0. if not, x is 0. so return 0 or 1 using ^. 
 	return (((x>>31)&1)|(((~x+1)>>31)&1))^1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) { //minimum two's complment integer is 0x80000000.0x01 left shift 31 to make 0x80000000.
  return 1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) { //left shift 32-n(32+~n+1) and right shift 32-n, check if first x value and value after shift are same.
  return !(((x<<(32+~n+1))>>(32+~n+1))+~x+1);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) { //first right shift n. it will return value that maximum integer among values smaller than or same with x/(2^n). we should round toward zero, so when x is smaller than zero, add 1 to x>>n.
    return (x>>n)+ ((!!((x<<(31+~n+1)&(~(1<<31)))))&((x>>31)&1));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { // using x+~x=-1
  return ~x+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) { // if x is not 0, then !!x will return 0x01(true). And check the sign bit to determine whether x is negative number. so return true when x is not zeor and  x's signbit is 0.
  return (((x>>31)&0x01)^0x01)&(!!x);

}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) { // when sign bit of x and y are same, check y-x's sign bit, when sign bit of x and y are different, then check y's sign bit(if 1 y is negative, if 0 y is positive)
  return ((!(((x>>31)&1)^((y>>31)&1)))&(!(((y+~x+1)>>31)&1)))|((((x>>31)&1)^((y>>31)&1))&(!((y>>31)&1)));
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	int fr=0;
	int a4=0;
	int a3=0;
	int a2=0;
	int a1=0;
	int a0=0;
	fr=!!(x>>16);//check x takes up more than 16bits.
	a4=fr<<4;//we should multiply 16 to fr according to above process.
	fr=!!(x>>(a4+8));//check x takes up more than (a4+8)bits.
	a3=fr<<3;//we should multiply 8 to fr according to above process.
	fr=!!(x>>(a4+a3+4));//check x takes up more than(a4+a3+4)bits.
	a2=fr<<2;//we should multiply 4 to fr according to above process.
	fr=!!(x>>(a4+a3+a2+2));//check x takes up more than (a4+a3+a2+2)bits.
	a1=fr<<1;//we should multiply 2 to fr according to above process.
	fr=!!(x>>(a4+a3+a2+a1+1));//check x takes up more than (a4+a3+a2+a1+1).
	a0=fr;//we don't need to multiply value to x.
  return a4+a3+a2+a1+a0;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	if ((uf<<9 != 0)&&(0xff<<23==(0xff<<23&uf))){
	return uf;  //check uf is NaN(fractional part is not zero, exp part consists of 1s.).
	}
 return uf ^ 0x80000000;// change sign bit
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	int s = x&0x80000000;//extract sign of x
	int result=0;
	int E=0;
	int exp=0;
	int frac=0;
	int b=0;
	if (x==0) {
	return 0;
	}
	if (x==0x80000000){//we can't negate tmin value so we handle it specially.
		return 0xcf000000;
	}
	if (s){// we handle sign value separately at float so we handle absolute value of x.
		x=~x+1;
	}
	b=x;
	while ((b/=2)!=0){// to find value E using while loop, while b/2 is not 0, add 1 to E.
	E=E+1;
	}
	exp=127+E;//exp=127+E(sum of bias and E
	x=x<<(31-E);//before move to fractional part move int to left side.
	frac=(x&0x7fffffff)>>8;
	if (((x&0x80)&&(x&0x7f))||((x&0x80)&&(frac&1))){
	frac=frac+1;
	}// round fractional part. using GRS.
	
	result += s;
	result += exp<<23;
	result += frac;//make a sum of s,exp,frac
	
	
	
	
  return result;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	if (0xff<<23==(0xff<<23&uf)){
	return uf; //when uf's exp part is 11111111. 
	}
	if ((uf<<1) == 0){
	return uf; //when uf is 0 return uf
	}
	if (((uf>>23)&0xff) ==0){//case: denormalized value
	return (uf&0x80000000)|(uf<<1);
	}
	
	return uf+0x00800000;//case: normalized value 
	
}
