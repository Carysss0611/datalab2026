/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x && !y)
    {
        // 都等于0
        return 1;
    }
    else if (!(x && y))
    {
        // 其中一个等于0
        return 0;
    }
    else
    {
        // 都不等于0
        return !((x ^ y) >> 31);
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int res  = 0;

    // 分成两个16位判断是否有1
    res = ((v >> 16) > 0) << 4;  // 16位以上有1，res=16; 没有1, res=0

    // 右移res位后，1一定在低16位，分成两个8位判断是否有1
    res |= (((v >> res) >> 8) > 0) << 3;  // 8位以上有1，res+=8; 没有1, res=0

    // 分成两个4位判断是否有1
    res |= (((v >> res) >> 4) > 0) << 2;  // 4位以上有1，res+=4; 没有1, res=0

    // 分成两个2位判断是否有1
    res |= (((v >> res) >> 2) > 0) << 1;  // 2位以上有1，res+=2; 没有1, res=0

    // 最后检查第1位
    res |= (((v >> res) >> 1) > 0);  // 1位以上有1，res+=1; 没有1, res=0

    return res;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int shift_n = n << 3;  // n字节左移3位(×8)，得到n字节的位移量
    int shift_m = m << 3;  // m字节左移3位(×8)，得到m字节的位移量

    int byte_n = (x >> shift_n) & 0xFF;  // 提取第n字节
    int byte_m = (x >> shift_m) & 0xFF;  // 提取第m字节

    // 清除第n字节和第m字节
    int mask = ~((0xFF << shift_n) | (0xFF << shift_m));
    int res = x & mask;

    // 将第n字节和第m字节交换
    res |= (byte_n << shift_m) | (byte_m << shift_n);
    return res;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    // 奇数位和偶数位交换
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    // 2位一组交换
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    // 4位一组交换
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    // 8位一组交换
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    // 16位一组交换
    v = (v >> 16) | (v << 16);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    // >> 是算数右移
    int res = (x >> n);
    int mask = ~(((1 << 31) & (!!n << 31)) >> (n  + (~0)));  // 如果n=0则不用移位
    res &= mask;
    return res;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int cnt = 0;
    int mask;
    
    // 检查高16位是否全1
    mask = !~(x >> 16); // 全1 mask=1；有0 mask=0
    cnt += (mask << 4); // 全1 +16；全0 +0
    x <<= (mask << 4); // x左移，把统计过的1去掉

    // 检查高8位
    mask = !~(x >> 24);
    cnt += (mask << 3);
    x <<= (mask << 3);

    // 检查高4位
    mask = !~(x >> 28);
    cnt += (mask << 2);
    x <<= (mask << 2);

    // 检查高2位
    mask = !~(x >> 30);
    cnt += (mask << 1);
    x <<= (mask << 1);

    // 检查最高位
    mask = !~(x >> 31);
    cnt += mask;
    x <<= mask;

    mask = !~(x >>31);
    cnt += mask;

    return cnt;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = (x >> 31) & 1; // 符号位
    unsigned ux = x;
    if (sign) {
        ux = -ux; // 取绝对值
    }

    
    if (ux == 0) {
        return 0;
    }
    unsigned temp = ux;
    unsigned exp = 0; // 指数位
    while (temp >> 1) {
        temp >>= 1;
        exp++;
    }

    unsigned n = ux << (32 + ~exp); // 将最高位移到第31位，要移动 31-exp 位
    unsigned f = (n >> 8) & 0x7FFFFF; // 尾数位，取23位
    unsigned low = n & 0xFF; // 低8位，用于舍入
    unsigned up = (low > 0x80) | ((low == 0x80) & (f & 1)); // 舍入判断
    f += up; // 尾数加上舍入位
    if (f & 0x800000) {  // f = 0x7FFFFF且需要向上舍入，导致尾数溢出
        f = 0;
        exp++;
    }
    return (sign << 31) | ((exp + 127) << 23) | f;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000; // 符号位
    unsigned exp = (uf >> 23) & 0xFF; // 指数
    unsigned frac = uf & 0x7FFFFF; // 尾数

    // 1. 阶码全1，返回原数
    if (exp == 0xFF) {
        return uf;
    }

    // 2. 阶码为0，非规格化数，将尾数左移一位
    if (exp == 0) {
        frac <<= 1; // 左移1位 数值*2
        if (frac & 0x800000) { // 如果左移后尾数溢出，变为规格化数
            exp = 1; // 阶码变为1
            frac &= 0x7FFFFF; // 清除溢出的位
        }
    }

    // 3. 阶码不为0，规格化数，阶码加1
    else {
        exp += 1;
        if (exp == 0xFF) { // 如果阶码溢出，变为无穷大
            frac = 0; // 尾数清零
        }
    }

    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = (uf2 >> 31) & 1; // 符号位
    unsigned exp = (uf2 >> 20) & 0x7FF; // 阶码
    unsigned frac_high = uf2 & 0xFFFFF; // 尾数高20位
    unsigned frac_low = uf1;  // 尾数低32位
    int real_exp = exp - 1023;  // 真实指数，偏移量1023

    // 阶码全1 0x7FF
    if (exp > 0x7FE)
    {
        return 0x80000000;
    }

    // 真实指数小于0，舍入为0
    if (real_exp < 0)
    {
        return 0;
    }

    // 真实指数>=31
    if (real_exp >= 31)
    {
        return 0x80000000;
    }

    unsigned hi32 = (1 << 20) | frac_high;
    int shift = 52 - real_exp;  // 需要右移的总位数
    unsigned abs_val;

    if (shift >= 32)
    {
        abs_val = hi32 >> (shift - 32);
    }
    else
    {
        abs_val = (hi32 << (32 - shift)) | (frac_low >> shift);
    }

    
    if (!sign)
    {
        return abs_val;
    }
    else
    {
        return -abs_val;
    }

}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    // 符号位一定是0，可以不用
    unsigned exp = 0;
    unsigned frac = 0;

    if (x > 127)
    {
        exp = 0xFF;
    }
    else if (x >= -149 && x <= -127)
    {
        // 非规格数
        exp = 0;
        int shift = 126 + 23 + x;
        frac = 1 << shift;
    }
    else if (x >= -126 && x <= 127)
    {
        // 规格数
        exp = x + 127;
    }
    else
    {
        // 数太小，下溢
        return 0;
    }

    return (exp << 23) | frac;
}
