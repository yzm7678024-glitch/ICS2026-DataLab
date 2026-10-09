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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  int xt,yt,ans;
  xt=(~x)&y;
  yt=(~y)&x;
  ans=~(~xt&~yt);
	return ans;
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int sign;
  sign=x>>31;//非负数为0，负数为-1
  return sign&(~x+1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int a,b,c,d;
  a=255<<(dst<<3);//构造掩码清零dst处的byte
  d=~a&x;
  b=x>>(src<<3);//构造掩码取出src处的byte
  c=b&255;
  c=c<<(dst<<3);//将src处byte位移到dst处
  return c|d;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int mask;
  mask=~((1<<31)>>n<<1);//构造0x80000000，之后右移(n-1)位取反，得到目标位全0的掩码
  return (x>>n&mask);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int a,b,logshift,xa,xb;
  a=(((((15<<8)+15)<<8)+15)<<8)+15;//构造0x0F0F0F0F
  b=a<<4;//构造0xF0F0F0F0
  xa=(x&a)<<4;
  logshift=~((1<<31)>>4<<1);//借用上一题的逻辑位移
  xb=(x&b)>>4&logshift;
  return xa|xb;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int y;
  x=~x;
  y=x&(x+(~0));//去掉最低位1
  return y&(~y+1);//取出第二位的1
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  int x1,x2,x3,x4,x5;
  x1=(x^(x>>16));//异或的折叠不改变1个数的奇偶性，1^1=0,1^0=1
  x2=(x1^(x1>>8));
  x3=(x2^(x2>>4));
  x4=(x3^(x3>>2));
  x5=(x4^(x4>>1));
  return !(x5&1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int tail,logshift;
  n=n&31;//防止n大于31
  tail=x<<((~n+1)&31);//取出尾部n个bits
  logshift=~((1<<31)>>n<<1);//用之前的逻辑位移
  x=(x>>n)&logshift;//将x右移并把头部清零空出位置
  return x|tail;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int q,r,t;
  q=x>>n;//取出倍数
  r=1<<(n+(~0));
  t=x+r+(~0)+(q&1);//用2^(n-1)来进位，(q&1)考虑了q的奇偶性，为奇则+1，为偶则向下取整
  return t>>n<<n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int mid,mask,ans,p;
  mid=(x&y)+((x^y)>>1);//将进位和/2直接融入一起算，以免溢出
  p=((x^y)&1)+(~0);//x+y为奇则p=0，为偶数p=-1
  mask=(((x>>31)^(y>>31))&1)+(~0);//x、y同号则mask=-1，异号则mask=0
  ans=mid+(((mask&((x+(~y)+1)>>31)+1))  |  (~mask&((x>>31)+1)));//同号直接相减不会溢出，异号直接看x的正负
  return (p&mid) | (~p)&ans;//x+y为偶数则不用再看ans
}

// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int mask1,mask2,xa,xb,equal;
  mask1=(((a>>31)^(x>>31))&1)+(~0);//x、a同号则mask1=-1，异号则mask1=0
  mask2=(((b>>31)^(x>>31))&1)+(~0);//x、b同号则mask2=-1，异号则mask2=0
  xa=(((mask1&((x+(~a)+1)>>31)+1))  |  (~mask1&((x>>31)+1)));//x>=a则xa=1,x<a则返回0
  xb=(((mask2&((x+(~b)+1)>>31)+1))  |  (~mask2&((x>>31)+1)));//x>=b则xb=1,x<b则返回0
  equal=((!(x^a))|(!(x^b)))+(~0);//针对相等的额外判断
  return (equal&(xa^xb)) | ((~equal)&1);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int x1,x2,x3,full,overflow,overflow1,overflow2,overflow3,sign;
  sign=x>>31;
  full=((~sign)&(~(1<<31)))|(sign&(1<<31));
  x1=x<<1;
  overflow1=(x1^x)>>31;//x1有溢出变号，则overflow1=-1
  x2=x1<<1;
  overflow2=(x2^x)>>31;//x2有溢出变号，则overflow2=-1
  x3=x2+x;
  overflow3=(x3^x)>>31;//x3有溢出变号，则overflow3=-1
  overflow=overflow1 | overflow2 | overflow3;

  return ((~overflow)&x3) | (overflow&full);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int a,b,c,s1,s2,carry1,carry2,carry;
  a=x^(1<<31);
  b=y^(1<<31);
  c=z^(1<<31);
  s1=a+b;
  carry1=(((a&b) | ((a|b)&(~s1)))>>31)&1;
  s2=s1+c;
  carry2=(((s1&c) | ((s1|c)&(~s2)))>>31)&1;
  carry=carry1+carry2+(~0);
  return carry;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned sign, exp, frac;
    unsigned m, scaled, q, r;
    //提取符号位、exp和frac
    sign=uf&0x80000000;
    exp=(uf>>23)&0xFF;
    frac=uf&0x7FFFFF;
    //NaN和无穷大直接返回原值
    if(exp==255)
        return uf;
    //非规格化数的处理
    if(exp==0) {
        //非规格化数没有隐藏的最高位1
        //将尾数乘3，再除以2
        scaled=frac*3;
        q=scaled>>1;
        // 除以2时采用向最近偶数舍入
        if((scaled&1)&&(q&1))
            q++;
        // 如果尾数达到2^23，转为规格化数
        if(q>=0x800000) {
            exp=1;
        }
        return sign | (exp << 23) | (q & 0x7FFFFF);
    }
    // 规格化数处理
    m=frac|0x800000;
    scaled=m*3;
    if(scaled >= 0x2000000) {
        //结果的有效数值达到2，需要exp加1
        exp++;
        //恢复尾数范围
        q=scaled>>2;
        r=scaled&3;
        //向最近偶数舍入
        if(r>2 || (r==2&&(q&1)))
            q++;
    }
    else{
        //结果的有效数值小于2，exp不变
        q=scaled>>1;
        //向最近偶数舍入
        if((scaled&1)&&(q&1))
            q++;
    }
    //处理舍入导致的尾数进位
    if(q>=0x1000000) {
        q=q>>1;
        exp++;
    }
    // exp溢出，返回对应符号的无穷大
    if(exp>=255)
        return sign | 0x7F800000;
    // 重新组合符号位、exp和frac
    return sign | (exp<<23) | (q&0x7FFFFF);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned sign,exp,frac,shift,mask,rest,half,mant;
    sign=uf&0x80000000;
    exp=(uf>>23)&0xFF;
    frac=uf&0x7FFFFF;
    if(exp>=150)  return uf;//已经是整数或NaN、无穷大
    if(exp<126)  return sign;//绝对值小于0.5，保留符号位
    if(exp==126)
    {
        if(frac)return sign|0x3F800000;//绝对值大于0.5，舍入为1
        return sign;//恰好为0.5，舍入为0
    }
    shift=150-exp;//需要舍去的小数位数
    mask=(1u<<shift)-1;
    rest=frac&mask;//被舍去的部分
    half=1u<<(shift-1);
    mant=frac|0x800000;//补上隐藏的最高位1
    uf=uf&(~mask);//先截去小数部分
    //大于一半时进位，恰好一半时向偶数舍入
    if(rest>half||(rest==half&&((mant>>shift)&1)))
        uf=uf+(1u<<shift);
    return uf;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    unsigned sign=0,absx,exp,frac,remain,half;
    int pos=31,shift;
    if(x==0)  return 0;
    absx=x;
    if(x<0)
    {
        sign=0x80000000;
        absx=~absx+1;//取绝对值，可正确处理INT_MIN
    }

    //寻找最高有效位1的位置
    while(!((absx>>pos)&1))  pos--;
    exp=pos+127;
    if(pos<=23)
    {
        frac=(absx<<(23-pos))&0x7FFFFF;//左移补齐尾数
    }
    else
    {
        shift=pos-23;
        frac=(absx>>shift)&0x7FFFFF;//保留最高24位中的低23位
        remain=absx&((1u<<shift)-1);//被舍去的低位
        half=1u<<(shift-1);
        //向最近偶数舍入
        if(remain>half||(remain==half&&(frac&1)))
        {
            frac++;
            if(frac==0x800000)
            {
                frac=0;
                exp++;//尾数进位导致阶码增加
            }
        }
    }
    return sign|(exp<<23)|frac;//组合符号位、exp和frac
}


// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int mask1,mask2,mask3;
  mask1=(0x55<<8)|0x55;
  mask1=(mask1<<16) | mask1;//通过复制构造的方法减少操作数
  x=(mask1&x)+((x>>1)&mask1);//拆解成低位加上高位，所得结果两位一分恰好为这两位含有1的个数
  mask2=(0x33<<8)|0x33;
  mask2=(mask2<<16)|mask2;
  x=(mask2&x)+((x>>2)&mask2);//再进行一次2位一分，结果是四位一分，每四位的数值恰好为这四位含有1的个数
  mask3=(0x0F<<8)|0x0F;
  mask3=(mask3<<16)|mask3;
  x=(x+(x>>4))&mask3;//此时最多有8个1，因此前四位没有用，可以少一次操作
  x=x+(x>>8);
  x=x+(x>>16);//这两次甚至连掩码都不需要构造，因为每次前半段的信息都没有用，最多只有32个1，也就是取出前6个bit即可
  return x&0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int mask1,mask2,mask3,mask4,mask5;//每次交换一半，逐次交换完成
  mask1=(0xFF<<8)+0x00FF;
  x=(x<<16)+((x>>16)&mask1);//左移的时候不用&，因为低位一定为0
  mask2=(mask1<<8)^mask1;//用先前的掩码进一步裂变，减少操作数
  x=((x&mask2)<<8)+((x>>8)&mask2);
  mask3=(mask2<<4)^mask2;
  x=((x&mask3)<<4)+((x>>4)&mask3);
  mask4=(mask3<<2)^mask3;
  x=((x&mask4)<<2)+((x>>2)&mask4);
  mask5=(mask4<<1)^mask4;
  x=((x&mask5)<<1)+((x>>1)&mask5);
  return x;
}
