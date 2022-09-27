## CSAPP Lab1-datalab

### 前置知识

- 无符号数的表示方法
- 有符号数的补码表示方法
- 浮点数 IEEE 754 标准
- 位运算规则

### 环境构建

实验需要 linux 环境，可以选择

- 虚拟机
- 云服务器
- wsl

在 linux 环境下，进入 datalab 后执行 `make` 命令，实验环境就配置好了

*可能遇到的问题*：

**错误: fatal error: bits/libc-header-start.h: No such file or directory #include <bits/libc-header-start.h>**

你出现这个错误多半是由于所编译的项目是想在 64 位机器上生成 32 位的项目，你需要安装对应 gcc 32位的库，这属于是编程环境没有完善好。

主要原因是你系统中的 gcc 没有安装multilib 库，这个库可以在 64 位的机器上产生 32 位的程序或者库文件。

可以使用：`apt install gcc-multilib` 进行安装

### 开始实验

**题目1：bitXor**

```c
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
```

题干：使用 非 和 与 两种位运算实现 异或

依据异或的定义来想，位不相同时异或输出才为 1，即两者既不同时为零，也不同时为一，以此写出表达式



**题目2：tmin**

```c
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
```

题干：返回最小的补码

最小的补码就是小的负数，补码最高位是负权重，其余都是正权重，所以仅当最高位为 1 时得到最小值



**题目3：isTmax**

```c
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
```

题干：判断输入是否为最大的补码

因为补码除最高位之外全是正权重，所以除了最高位以外其他位全 1 就是最大补码的二进制表示，这可以先得到最小补码然后取反来得到。

然后需要实现 等于 这个逻辑，由于异或的特性，一个数只有和自身异或才能得到全 0，利用这个特定将待比较的两数进行异或，然后逻辑非一下就可以实现。



**题目4：allOddBits**

```c
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
```

题干：判断输入数值的位模式是否奇数位是全 1

可以用奇数位全 1 的掩码取出输入数值的所有奇数位，然后判断其和掩码是否相等。



**题目5：negate**

```c
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
```

题干：求相反数

有符号数的补码表示求相反数就是按位取反加一



**题目6：isAsciiDigit**

```c
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
```

题干：判断输入数值的二进制位能否表示 ASCII 码中的数字

要实现一个同符号的小于逻辑，通过逻辑推导 a < b = a + (-b) < 0，-b 这个补码的相反数可以按位取反加一得到，和 0 的比较可以检查最高位，组合一下这几个点，就实现了小于逻辑

把小于逻辑取个反就是大于逻辑，判断一下 x  大于 0x30 并且小于 0x39 再或上两个边界的等于即可

进一步观察一下两个边界数的位模式可以发现更加简洁的实现方法：0x30 到 0x39 这 10 个数除了低 4 位不一样其余位模式完全一致，这一部分可以用一个右移和等于逻辑进行判断；低四位从 0 到 9，可以用掩码取出低 4 位然后判断一下保证小于 10 即可。这样只使用了一个等于逻辑和一个小于逻辑，比起原来的实现更加简洁。



**题目7：conditional**

```c
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
```

题干：实现一个三目运算符

全 1 的掩码与一个数，得到的结果是数自身；全 0 的掩码与一个数，得到的结果是全0

0 的 相反数是全 0，1的相反数是全 1

依据这两个性质，我们可以依据 x 的布尔值来设置掩码是全0 还是 全1，以此决定返回的结果是 y 还是 z。



**题目8：isLessOrEqual**

```c
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
```

题干：实现小于等于逻辑

在前面已经实现了一个同符号的小于逻辑，在此基础上加上不同符号的小于逻辑、等于逻辑就能完成本题。

不同符号的小于逻辑实现起来其实很简单：两个数的符号不同，负数肯定是小的。如果确定两者是不同符号，判断第一个数是否为负数（最高位是否为 1）即可。

我们可以应用一下上一题才实现的 conditional 逻辑，判断一下两输入是同符号还是不同符号，以此决定返回同符号小于逻辑的处理结果还是不同符号小于逻辑的处理结果。

这里有一个很坑的地方就是，int 的右移操作是算术右移，`((unsigned)x + ~y + 1) >> 31` 这一步是为了得到一个逻辑值，如果`x + ~y + 1` 的结果为 负数，由于其类型为 int，右移后得到的是全 1 ，而不是预想的逻辑1，所以需要一个 unsigned 类型转换。



**题目9：logicalNeg**

```c
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
```

题干：实现逻辑非

这里利用的是这样一个特性：只有 0 和 最小补码 的相反数是自身，其他数和自己的相反数符号是不同的（这很显然，一个正一个负）。

所以非 0 的数和自己的相反数最高位必有一个为 1（将最小补码也和 0 区分了），其和自己的相反数或运算的结果最高位必为 1，右移 31 位后符号位由于 int 类型逻辑右移，变成全 1，加 1 刚好变全 0；同时 0 进行或运算和右移后还是 0，加 1 刚好是 1，符合题目。

就是这么神奇。



**题目10：howManyBits**

```c
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
```

题干：对于输入的数，最少可以用几个比特表示出来

我是从 “一个数用最少的比特表示后扩展成更多位时是如何操作的” 这个点切入找到思路的，对于正数符号位为 0  直接在高位补 0 完成扩展，对于负数符号位为 1 直接在高位补 1 完成扩展。

此时再考虑上述扩展过程的逆过程：对于正数而言，最高位连续的 0 其实可以合并成一位 0；负数最高位连续的 1 可以合并成一位 1。因此，对于正数而言，决定最少表示位数的是最高位的 1；对于负数而言，决定最少表示位数的是最高位的 0。在最高位有效位数的基础上加一位符号位就是最少表示位数。

经过上面的分析之后其实我们已经明确了工作的目标了，此时就是一个实现上的问题：

- 将负数进行取反操作，就可以和正数的处理一样了，将目标统一成找最高位的 1。
- 因为不能使用循环, 暴力的方法就是写 31 个语句，从 31 位一位一位用掩码找，但是这显然有点笨了，而且操作数不够。
- 二分的方法就很妙。一次找一半的位数，判断高一半有没有1，然后进行累加。



**题目11：float_twice**

```c
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
```

题目：浮点数乘2

首先就是明确好浮点数的表示方法：-1*(s) * 2^E * M。

所以很直接就会想到一般的情况就是 E 加 1 就行了，然后再讨论一下其他情况。

先用掩码和与运算取出浮点数的三个组成部分 s、e、m。

如果 e 等于 0 ，说明此时是非标准形式，不能直接操作 e，直接左移一位 m 就行（由于最大非标准形式和最小标准形式之间过度是平滑的，所以此时即使 m 为低 23 位全 1 也没有关系）。

如果 e 等于 255，依据题干信息，NaN 直接返回输入，而对于无穷来说乘 2 还是等于自身，所以这一类都直接返回输入。

其他情况就是 E 加 1 就行，但是要检查一下输入乘 2 之后是否就溢出了，如果溢出就返回对应符号的无穷大。



**题目12：float_i2f**

```c
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
```

题干：补码到浮点数的转换

浮点数的表示范围比 int 大，不用担心溢出的问题，同时肯定不会表示 0到1 之间数，不用考虑 e = 0 的情况。

先处理符号位：浮点数的符号位在最前面，m 总是一个正数，所以对于负数补码，取了符号位后，需要变成相反数。

再计算阶码：将补码一步步右移判断是否为 0 来粗略得出 E 的值，加上偏置 127 得到粗略的阶码 e。

最后得出尾数：

- 标准形式的浮点数最高位的 1 被省略了，要清除最高位的 1。
- 如果有效位小于 23 直接将尾数左移到顶
- 如果有效位大于 23，就可能会有精度的丢失，需要考虑舍入的情况
- c 语言中浮点数的舍入是向偶数舍入
- 在循环右移的过程中记录一下是否有 1 被移出（精度丢失），同时还要特别记录最后一个移出的位，以此为依据，按照偶数舍入的规则，判断要不要进一位。
- 舍入引发进位后，检查一下是否会出现尾数溢出了，如果溢出了就调整一下 e 即可，因为浮点数表示范围更大，不需要担心 e 也因此溢出了

这题估计是最最繁琐的一个题了！



题目13：float_f2i

```c
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
  if (E > 31) return 1 << 31;

  // 计算结果
  m |= (1 << 23); // 最高位补1
  if(E > 23) m <<= (E - 23);
  else m >>= (23 - E);

  // 正负号
  int ret = m;
  if(s) {
    ret *= -1;
  }

  return ret;
}
```

题干：浮点数到补码的转换

第一步也是用掩码取出浮点数的各个部分。

对于普通的情况，我们对尾数最高位补1 后按照阶码进行位移就行了。

如果 E 小于 0 ，说明是小数，直接舍成 0 就行。

如果 E 大于31，对于 int 而言就是溢出了，按照题目返回 0x80000000u。

最后依据符号位调整一下 int 的正负就完成了。



### 小结

实验之前还觉得位运算也没什么东西，但是写的时候还是发现卡在了不少地方，比如说没有注意到有符号数的右移是算数右移、考虑不到浮点数运算中的特殊情况、浮点数运算中精度丢失怎么舍入等等，感觉还是完成实验之后对相应内容还是理解更深了。

那道判断最少表示位数的题用到二分这个思想还是挺厉害的。

最后两道题还是比较繁琐的，需要考虑到很多边界情况，完成之后看感觉没有什么很难很难的点，但是一开始实现的时候就是没有先完整考虑好所有的问题，把思路捋顺，结果 debug 挺久。
