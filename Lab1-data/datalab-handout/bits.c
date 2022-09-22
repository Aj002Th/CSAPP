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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // 不同时为零, 也不同时为一
  return ~(~x & ~y) & ~(x & y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // 最小的补码: 仅最高位为 1 
  return 1<<31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
  // 等于: X==Y = !(X ^ Y) = !bitXor = !(~(~x & ~y) & ~(x & y))
  // 最大的补码: 仅最高位为 0
  unsigned maxMask = ~(1 << 31);
  return !(x ^ maxMask);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // 表示出奇数位的位模式,然后再用之前推出来的 等于
  // 它这里的奇数指的是从高位开始算的, oddMask = 0xAAAAAAAA
  unsigned oddMask = 0xAA  + (0xAA << 8);
  oddMask = oddMask + (oddMask << 16);
  x = x & oddMask;
  return !(x ^ oddMask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // 按位取反加一
  return ~x + 1;
}
//3
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
  // 小于: a < b = a + (-b) < 0 = a + negate(b) < 0 = a + (~b) + 1 < 0 = a + (~b) + 1 是负数 = (a + ~b + 1) >> 31
  // 这个小于有点缺陷, 只能判断同符号的数, 同时还要警惕int类型的右移是算术右移
  // 0x30 : 0011 0000
  // 0x39 : 0011 1001
  // 倒数第二个十六进制数等于3, 倒数第一个十六进制数小于10, 其他十六进制位全是0
  return (!((x >> 4) ^ 0x3)) & (((x & 0xF) + ~0xA + 1) >> 31);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // 判断一个数是否为0: !!x
  // 0 的补码是全0, 1 的补码是全1
  // 用全零和全一来进行选择
  unsigned flag = !!x;
  unsigned mask = ~flag + 1;
  return (mask & y) | (~mask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // 给之前的同符号小于补充不同符号的情况,然后和等于或起来即可
  unsigned signx = (1 << 31) & x;
  unsigned signy = (1 << 31) & y;

  // 完整的小于: conditional((signx ^ signy), signx >> 31, (x + ~y + 1) >> 31)
  // 注意int的算术右移
  unsigned flag = !!(signx ^ signy);
  unsigned mask = ~flag + 1;
  unsigned less = (mask & (signx >> 31)) | (~mask & (((unsigned)x + ~y + 1) >> 31));
  unsigned equal = !(x ^ y);

  return less | equal;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // 只有 0 和最小值的补码相反数是自身
  return ((x | (~x + 1)) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  // 将问题转换为找到最高位的1的位数, 将结果 + 1(符号位)就是所需的结果
  // 对于正数来说是找最高位的1, 对于负数来说就是找最高位的0, 所以对负数取反即可
  unsigned ux = x;
  if(ux >> 31) {
    ux = ~ux;
  }

  // 因为不能使用循环, 暴力的方法就是从32位一位一位用掩码找, 但是这显然有点笨了
  // 有个很妙的二分法
  int cnt = 0;
  if(!!(ux >> 16)) {
    cnt += 16;
    ux >>= 16;
  }
  if(!!(ux >> 8)) {
    cnt += 8;
    ux >>= 8;
  }
  if(!!(ux >> 4)) {
    cnt += 4;
    ux >>= 4;
  }
  if (!!(ux >> 2)) {
    cnt += 2;
    ux >>= 2;
  }
  if (!!(ux >> 1)) {
    cnt += 1;
    ux >>= 1;
  }
  if(!!ux) {
    cnt += 1;
  }
  
  return cnt + 1;
}
//float
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
  // 公式: float = s E M = -1*(s) * 2^E * M
  // 取每个部分
  unsigned s = uf & (1 << 31);
  unsigned e = (uf & (0xff << 23)) >> 23;
  unsigned m = uf & ~(0x1ff << 23);

  // 普通情况把 E 加一即可, E = 0 和 255 要单独处理一下
  if (e == 0) return s | (m << 1);
  if (e == 255) return uf;
  e++;
  if (e == 255) return (e << 23) | s;
  return s | m | (e << 23);
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
  // 取每个部分
  unsigned s = x & (1 << 31);
  unsigned E = 0;
  unsigned e = 0;
  unsigned m = x;

  // 0 直接返回
  if(!x) return 0;
  // 负数先转正数
  if(s) {
    m = ~m + 1;
  }

  // 统计 E, 计算 e
  for (unsigned i = m; i ; i >>= 1) E++;
  E--;
  e = E + 127;

  // 计算尾数 m
  m = m & (~(1 << E)); // 去掉最高位的1
  if (E < 24) {
    m <<= (23 - E);
  } else {
    // 位移到能取的 23 位
    unsigned left = 0;
    while(E > 24) {
      if(m & 1) left++; // 移出的位是1就说明有精度的丢失
      m >>= 1;
      E--;
    }
    // 留了一位来判断进位
    unsigned carry = m & 1;
    m >>= 1;

    // 偶数舍入
    if(carry) {
      if(left)
        m++;
      else if(m & 1)
        m++;
    }

    // 处理舍入完出现的进位
    if(m & (1 << 23)) {
      e++;
      m &= ~(1 << 23) ; // 因为其实最前面还有一个1, 又进了一次位, 所以直接将进位抹除就好
    }
  }

  return s | (e << 23) | m;
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
  // 取每个部分
  unsigned s = uf & (1 << 31);
  unsigned e = (uf & (0xff << 23)) >> 23;
  unsigned m = uf & ~(0x1ff << 23);

  // 处理特殊情况
  int E = e - 127;
  if (E < 0) return 0;
  if (E == 255 || E > 31) return 1 << 31;

  // 计算结果
  m |= (1 << 23); // 最高位补1
  if(E > 23) m >>= (E - 23);
  else m >>= (23 - E);

  // 正负号
  int ret = m;
  if(s) {
    ret *= -1;
  }

  return ret;
}
