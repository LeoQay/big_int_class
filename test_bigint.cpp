#include <string>
#include <sstream>
#include <gtest/gtest.h>

#include "bigint.hpp"


class TestBigInt : public ::testing::Test
{
public:
    static void cmp(const BigInt & obj, const std::string & s);
};

void TestBigInt::cmp(const BigInt & obj, const std::string & s)
{
    std::stringstream stream;
    stream << obj;
    std::string str = stream.str();
    ASSERT_EQ(str, s);
}


class TestBigIntInit : public TestBigInt {};

class TestBigIntInitNoArgs : public TestBigIntInit {};

class TestBigIntInitInt : public TestBigIntInit {};

class TestBigIntInitStr : public TestBigIntInit
{
public:
    static void wrong_argument(const std::string & str);
    static void difficult_argument(const std::string & str);
};

class TestBigIntInitCopy : public TestBigIntInit {};

class TestBigIntInitMove : public TestBigIntInit
{
public:
    static BigInt for_test_move_1();
    static BigInt for_test_move_2();
    static BigInt for_test_move_3();
    static BigInt for_test_move_4(BigInt & obj);
    static BigInt for_test_move_5(const BigInt & num);
};

class TestBigIntCmp : public TestBigInt {};

class TestBigIntEQ : public TestBigIntCmp {};

class TestBigIntNE : public TestBigIntCmp {};

class TestBigIntGT : public TestBigIntCmp {};

class TestBigIntGE : public TestBigIntCmp {};

class TestBigIntLT : public TestBigIntCmp {};

class TestBigIntLE : public TestBigIntCmp {};

class TestBigIntAdd : public TestBigInt {};

class TestBigIntSub : public TestBigInt {};

class TestBigIntMul : public TestBigInt {};



TEST_F(TestBigIntInitNoArgs, test_init_no_args_1)
{
    BigInt num;
    cmp(num, "0");
}


TEST_F(TestBigIntInitInt, test_init_int_1)
{
    BigInt num1(2);
    cmp(num1, "2");
}

TEST_F(TestBigIntInitInt, test_init_int_2)
{
    BigInt num2(45);
    cmp(num2, "45");
}

TEST_F(TestBigIntInitInt, test_init_int_3)
{
    BigInt num3(-12);
    cmp(num3, "-12");
}

TEST_F(TestBigIntInitInt, test_init_int_4)
{
    BigInt num4(0);
    cmp(num4, "0");
}

TEST_F(TestBigIntInitInt, test_init_int_5)
{
    BigInt num5(2147483647);
    cmp(num5, "2147483647");
}

TEST_F(TestBigIntInitInt, test_init_int_6)
{
    BigInt num6(-2147483648);
    cmp(num6, "-2147483648");
}


TEST_F(TestBigIntInitStr, test_init_str_1)
{
    BigInt num1("2");
    cmp(num1, "2");
}

TEST_F(TestBigIntInitStr, test_init_str_2)
{
    BigInt num2("23");
    cmp(num2, "23");
}

TEST_F(TestBigIntInitStr, test_init_str_3)
{
    BigInt num3("124");
    cmp(num3, "124");
}

TEST_F(TestBigIntInitStr, test_init_str_4)
{
    BigInt num4("-1234");
    cmp(num4, "-1234");
}

TEST_F(TestBigIntInitStr, test_init_str_5)
{
    BigInt num5("0000");
    cmp(num5, "0");
}

TEST_F(TestBigIntInitStr, test_init_str_6)
{
    BigInt num6("");
    cmp(num6, "0");
}

TEST_F(TestBigIntInitStr, test_init_str_7)
{
    BigInt num7("4294967295");
    cmp(num7, "4294967295");
}

TEST_F(TestBigIntInitStr, test_init_str_8)
{
    BigInt num8("4294967296");
    cmp(num8, "4294967296");
}

TEST_F(TestBigIntInitStr, test_init_str_9)
{
    BigInt num9("-4294967296");
    cmp(num9, "-4294967296");
}

TEST_F(TestBigIntInitStr, test_init_str_10)
{
    BigInt num10("-4294967297");
    cmp(num10, "-4294967297");
}

TEST_F(TestBigIntInitStr, test_init_str_11)
{
    BigInt num11("12423345436356575674684835567468");
    cmp(num11, "12423345436356575674684835567468");
}

void TestBigIntInitStr::wrong_argument(const std::string & str)
{
    try {
        BigInt num(str);
    }
    catch (std::exception &)
    {
        return;
    }
    ASSERT_TRUE(false);
}

void TestBigIntInitStr::difficult_argument(const std::string & str)
{
    try {
        BigInt num(str);
    }
    catch (std::exception &)
    {
        ASSERT_TRUE(false);
    }
}

TEST_F(TestBigIntInitStr, test_init_str_wrong_1)
{
    wrong_argument("-");
}

TEST_F(TestBigIntInitStr, test_init_str_wrong_2)
{
    wrong_argument("0-");
    wrong_argument("1235-");
    wrong_argument("234-234");
}

TEST_F(TestBigIntInitStr, test_init_str_wrong_3)
{
    wrong_argument("WEGRAH");
    wrong_argument("e12");
    wrong_argument("_233");
    wrong_argument("934f");
}

TEST_F(TestBigIntInitStr, test_init_str_diff_1)
{
    difficult_argument("00000");
    difficult_argument("0000102");
    difficult_argument("-01023");
    difficult_argument("-0000000000120000012");
}

TEST_F(TestBigIntInitStr, test_init_str_diff_2)
{
    difficult_argument("");
}


TEST_F(TestBigIntInitCopy, test_copy_1)
{
    BigInt num1;
    BigInt num2(num1);
    cmp(num2, "0");
    cmp(num1, "0");
}

TEST_F(TestBigIntInitCopy, test_copy_2)
{
    BigInt num1 = 234346;
    cmp(num1, "234346");
    BigInt num2 = num1;
    cmp(num2, "234346");
    cmp(num1, "234346");
}

TEST_F(TestBigIntInitCopy, test_copy_3)
{
    BigInt num1 = BigInt("2545847634758378365");
    cmp(num1, "2545847634758378365");
    BigInt num2 = num1;
    cmp(num1, "2545847634758378365");
    cmp(num2, "2545847634758378365");
}

TEST_F(TestBigIntInitCopy, test_copy_4)
{
    BigInt num1 = -124124;
    BigInt num2 = num1;
    cmp(num1, "-124124");
    cmp(num2, "-124124");

    num1 = BigInt("16545323254657");
    num1 = num1;
    num2 = num2;
    cmp(num1, "16545323254657");
    cmp(num2, "-124124");
}

TEST_F(TestBigIntInitCopy, test_copy_5)
{
    BigInt num1 = 123;
    cmp(num1, "123");
    BigInt num2 = 345;
    num1 = num2;
    cmp(num1, "345");
    cmp(num2, "345");
}


BigInt TestBigIntInitMove::for_test_move_1()
{
    BigInt num = 1245;
    return num;
}

TEST_F(TestBigIntInitMove, test_move_1)
{
    BigInt num;
    num = for_test_move_1();
    cmp(num, "1245");
}

BigInt TestBigIntInitMove::for_test_move_2()
{
    BigInt num;
    return num;
}

TEST_F(TestBigIntInitMove, test_move_2)
{
    BigInt num;
    num = for_test_move_2();
    cmp(num, "0");
}

BigInt TestBigIntInitMove::for_test_move_3()
{
    BigInt num("-124235534235243");
    return num;
}

TEST_F(TestBigIntInitMove, test_move_3)
{
    BigInt num;
    num = for_test_move_3();
    cmp(num, "-124235534235243");
    num = for_test_move_4(num);
    cmp(num, "-124235534235243");
}

BigInt TestBigIntInitMove::for_test_move_4(BigInt & obj)
{
    return obj;
}

TEST_F(TestBigIntInitMove, test_move_4)
{
    BigInt num("-124235534235243");
    num = for_test_move_4(num);
    cmp(num, "-124235534235243");
}

BigInt TestBigIntInitMove::for_test_move_5(const BigInt & num)
{
    BigInt num2 = num + 23;
    return num2;
}

TEST_F(TestBigIntInitMove, test_move_5)
{
    BigInt num1 = 42343;
    BigInt num = for_test_move_5(num1);
    cmp(num, "42366");
}


TEST_F(TestBigIntEQ, test_eq_1)
{
    BigInt num1, num2 = 0;
    ASSERT_TRUE(num1 == num2);
}

TEST_F(TestBigIntEQ, test_eq_2)
{
    BigInt num1 = 123, num2 = -123;
    ASSERT_FALSE(num1 == num2);
}

TEST_F(TestBigIntEQ, test_eq_3)
{
    BigInt num1("123456789987654321"), num2("123456789987654321");
    ASSERT_TRUE(num1 == num2);
}

TEST_F(TestBigIntEQ, test_eq_4)
{
    BigInt num1("-987654321123456789987654321");
    BigInt num2("987654321123456789987654321");
    ASSERT_FALSE(num1 == num2);
}

TEST_F(TestBigIntEQ, test_eq_5)
{
    BigInt num1("123456789123456789123456789");
    BigInt num2("123455789123456789123456789");
    ASSERT_FALSE(num1 == num2);
}

TEST_F(TestBigIntEQ, test_eq_6)
{
    BigInt num1("111111111123456789");
    BigInt num2("211111111123456789");
    ASSERT_FALSE(num1 == num2);
}

TEST_F(TestBigIntEQ, test_eq_7)
{
    BigInt num1("111111");
    BigInt num2("2189");
    ASSERT_FALSE(num1 == num2);
}

TEST_F(TestBigIntEQ, test_eq_8)
{
    BigInt num1("1111112345345345354345345345");
    BigInt num2("218934534534535345345534343");
    ASSERT_FALSE(num1 == num2);
}


TEST_F(TestBigIntNE, test_ne_1)
{
    BigInt num1, num2 = 0;
    ASSERT_FALSE(num1 != num2);
}

TEST_F(TestBigIntNE, test_ne_2)
{
    BigInt num1 = 123, num2 = -123;
    ASSERT_TRUE(num1 != num2);
}

TEST_F(TestBigIntNE, test_ne_3)
{
    BigInt num1("123456789987654321"), num2("123456789987654321");
    ASSERT_FALSE(num1 != num2);
}

TEST_F(TestBigIntNE, test_ne_4)
{
    BigInt num1("-987654321123456789987654321");
    BigInt num2("987654321123456789987654321");
    ASSERT_TRUE(num1 != num2);
}

TEST_F(TestBigIntNE, test_ne_5)
{
    BigInt num1("123456789123456789123456789");
    BigInt num2("123455789123456789123456789");
    ASSERT_TRUE(num1 != num2);
}

TEST_F(TestBigIntNE, test_ne_6)
{
    BigInt num1("111111111123456789");
    BigInt num2("211111111123456789");
    ASSERT_TRUE(num1 != num2);
}


TEST_F(TestBigIntGT, test_gt_1)
{
    BigInt num1("1");
    BigInt num2("1");
    ASSERT_FALSE(num1 > num2);
}

TEST_F(TestBigIntGT, test_gt_2)
{
    BigInt num1("2");
    BigInt num2("1");
    ASSERT_TRUE(num1 > num2);
}

TEST_F(TestBigIntGT, test_gt_3)
{
    BigInt num1("2");
    BigInt num2("4");
    ASSERT_FALSE(num1 > num2);
}

TEST_F(TestBigIntGT, test_gt_4)
{
    BigInt num1("-123");
    BigInt num2("122");
    ASSERT_FALSE(num1 > num2);
}

TEST_F(TestBigIntGT, test_gt_5)
{
    BigInt num1("23746283765783234123");
    BigInt num2("122");
    ASSERT_TRUE(num1 > num2);
}

TEST_F(TestBigIntGT, test_gt_6)
{
    BigInt num1("23746283765783234123");
    BigInt num2("-4553122");
    ASSERT_TRUE(num1 > num2);
}

TEST_F(TestBigIntGT, test_gt_7)
{
    BigInt num1("0");
    BigInt num2("4553122");
    ASSERT_FALSE(num1 > num2);
}

TEST_F(TestBigIntGT, test_gt_8)
{
    BigInt num1("1230");
    BigInt num2("0");
    ASSERT_TRUE(num1 > num2);
}


TEST_F(TestBigIntLE, test_le_1)
{
    BigInt num1("1");
    BigInt num2("1");
    ASSERT_TRUE(num1 <= num2);
}

TEST_F(TestBigIntLE, test_le_2)
{
    BigInt num1("2");
    BigInt num2("1");
    ASSERT_FALSE(num1 <= num2);
}

TEST_F(TestBigIntLE, test_le_3)
{
    BigInt num1("2");
    BigInt num2("4");
    ASSERT_TRUE(num1 <= num2);
}

TEST_F(TestBigIntLE, test_le_4)
{
    BigInt num1("-123");
    BigInt num2("122");
    ASSERT_TRUE(num1 <= num2);
}

TEST_F(TestBigIntLE, test_le_5)
{
    BigInt num1("23746283765783234123");
    BigInt num2("122");
    ASSERT_FALSE(num1 <= num2);
}

TEST_F(TestBigIntLE, test_le_6)
{
    BigInt num1("23746283765783234123");
    BigInt num2("-4553122");
    ASSERT_FALSE(num1 <= num2);
}

TEST_F(TestBigIntLE, test_le_7)
{
    BigInt num1("0");
    BigInt num2("4553122");
    ASSERT_TRUE(num1 <= num2);
}

TEST_F(TestBigIntLE, test_le_8)
{
    BigInt num1("1230");
    BigInt num2("0");
    ASSERT_FALSE(num1 <= num2);
}


TEST_F(TestBigIntGE, test_ge_1)
{
    BigInt num1("123");
    BigInt num2("123");
    ASSERT_TRUE(num1 >= num2);
}

TEST_F(TestBigIntGE, test_ge_2)
{
    BigInt num1("143");
    BigInt num2("-144");
    ASSERT_TRUE(num1 >= num2);
}

TEST_F(TestBigIntGE, test_ge_3)
{
    BigInt num1("0");
    BigInt num2("0");
    ASSERT_TRUE(num1 >= num2);
}

TEST_F(TestBigIntGE, test_ge_4)
{
    BigInt num1("0");
    BigInt num2("1245342");
    ASSERT_FALSE(num1 >= num2);
}

TEST_F(TestBigIntGE, test_ge_5)
{
    BigInt num1("12435432");
    BigInt num2("1245342");
    ASSERT_TRUE(num1 >= num2);
}

TEST_F(TestBigIntGE, test_ge_6)
{
    BigInt num1("124354321243543212435432");
    BigInt num2("124354321243543212435432");
    ASSERT_TRUE(num1 >= num2);
}

TEST_F(TestBigIntGE, test_ge_7)
{
    BigInt num1("-124354321243543212435432");
    BigInt num2("-124354321243543212435432");
    ASSERT_TRUE(num1 >= num2);
}

TEST_F(TestBigIntGE, test_ge_8)
{
    BigInt num1("-124354321243543212435433");
    BigInt num2("-124354321243543212435432");
    ASSERT_FALSE(num1 >= num2);
}


TEST_F(TestBigIntLT, test_lt_1)
{
    BigInt num1("123");
    BigInt num2("123");
    ASSERT_FALSE(num1 < num2);
}

TEST_F(TestBigIntLT, test_lt_2)
{
    BigInt num1("143");
    BigInt num2("-144");
    ASSERT_FALSE(num1 < num2);
}

TEST_F(TestBigIntLT, test_lt_3)
{
    BigInt num1("0");
    BigInt num2("0");
    ASSERT_FALSE(num1 < num2);
}

TEST_F(TestBigIntLT, test_lt_4)
{
    BigInt num1("0");
    BigInt num2("1245342");
    ASSERT_TRUE(num1 < num2);
}

TEST_F(TestBigIntLT, test_lt_5)
{
    BigInt num1("12435432");
    BigInt num2("1245342");
    ASSERT_FALSE(num1 < num2);
}

TEST_F(TestBigIntLT, test_lt_6)
{
    BigInt num1("124354321243543212435432");
    BigInt num2("124354321243543212435432");
    ASSERT_FALSE(num1 < num2);
}

TEST_F(TestBigIntLT, test_lt_7)
{
    BigInt num1("-124354321243543212435432");
    BigInt num2("-124354321243543212435432");
    ASSERT_FALSE(num1 < num2);
}

TEST_F(TestBigIntLT, test_lt_8)
{
    BigInt num1("-124354321243543212435433");
    BigInt num2("-124354321243543212435432");
    ASSERT_TRUE(num1 < num2);
}


TEST_F(TestBigIntAdd, test_add_1)
{
    BigInt num1 = 1;
    BigInt num2 = 1;
    BigInt num3 = num1 + num2;
    cmp(num3, "2");
}

TEST_F(TestBigIntAdd, test_add_2)
{
    BigInt num1 = 1;
    BigInt num2 = -1;
    BigInt num3 = num1 + num2;
    cmp(num3, "0");
}

TEST_F(TestBigIntAdd, test_add_3)
{
    BigInt num1 = 12345;
    BigInt num2 = -1;
    BigInt num3 = num1 + num2;
    cmp(num3, "12344");
}

TEST_F(TestBigIntAdd, test_add_4)
{
    BigInt num1("123456789123456789");
    BigInt num2("-123456789123456789");
    BigInt num3 = num1 + num2;
    cmp(num3, "0");
}

TEST_F(TestBigIntAdd, test_add_5)
{
    BigInt num1("999999999999999999999999999999999999");
    BigInt num2("1");
    BigInt num3 = num1 + num2;
    cmp(num3, "1000000000000000000000000000000000000");
}

TEST_F(TestBigIntAdd, test_add_6)
{

    BigInt num1("1000000000000000000000000000000000000");
    BigInt num2("-1");
    BigInt num3 = num1 + num2;
    cmp(num3, "999999999999999999999999999999999999");
}

TEST_F(TestBigIntAdd, test_add_7)
{

    BigInt num1("1000000000000000000000000000000000000");
    BigInt num2("-9999999999991");
    BigInt num3 = num1 + num2;
    cmp(num3, "999999999999999999999990000000000009");
}

TEST_F(TestBigIntAdd, test_add_8)
{
    BigInt num1("999999999");
    BigInt num2("999999999");
    BigInt num3 = num1 + num2;
    cmp(num3, "1999999998");
}

TEST_F(TestBigIntAdd, test_add_9)
{
    BigInt num1("1000000000");
    BigInt num2("123");
    BigInt num3 = num1 + num2;
    cmp(num3, "1000000123");
}

TEST_F(TestBigIntAdd, test_add_10)
{
    BigInt num1("99999999999999999");
    BigInt num2("-100000000000000000");
    BigInt num3 = num1 + num2;
    cmp(num3, "-1");
}

TEST_F(TestBigIntAdd, test_add_int_1)
{
    BigInt num1("10000");
    int32_t val2 = 1234;
    BigInt num3 = num1 + val2;
    cmp(num3, "11234");
    num3 = val2 + num1;
    cmp(num3, "11234");
}

TEST_F(TestBigIntAdd, test_add_int_2)
{
    BigInt num1("99999999999999999");
    int32_t val2 = 1;
    BigInt num3 = num1 + val2;
    cmp(num3, "100000000000000000");
    num3 = val2 + num1;
    cmp(num3, "100000000000000000");
}

TEST_F(TestBigIntAdd, test_add_int_3)
{
    BigInt num1("99999999999999999");
    int32_t val2 = -999999999;
    BigInt num3 = num1 + val2;
    cmp(num3, "99999999000000000");
    num3 = val2 + num1;
    cmp(num3, "99999999000000000");
}

TEST_F(TestBigIntAdd, test_inplace_add_1)
{
    BigInt num1("1");
    BigInt num2("1");
    num1 += num2;
    cmp(num1, "2");
}

TEST_F(TestBigIntAdd, test_inpalce_add_2)
{
    BigInt num1("1");
    BigInt num2("-1");
    num1 += num2;
    cmp(num1, "0");
}

TEST_F(TestBigIntAdd, test_inplace_add_3)
{
    BigInt num1("10000");
    int32_t val2 = 1234;
    num1 += val2;
    cmp(num1, "11234");
}

TEST_F(TestBigIntAdd, test_inplace_add_4)
{
    BigInt num1("99999999999999999");
    BigInt num2("-100000000000000000");
    num1 += num2;
    cmp(num1, "-1");
}

TEST_F(TestBigIntAdd, test_inplace_add_5)
{
    BigInt num1("3478573456823658376457834657836857346858347");
    BigInt num2("-23875384754765873627864276872762812712987394878563782568374");
    num1 += num2;
    cmp(num1, "-23875384754765870149290820049104436255152737041706435710027");
}

TEST_F(TestBigIntAdd, test_inplace_add_6)
{
    BigInt num1("23875384754765873627864276872762812712987394878563782568374");
    BigInt num2("-3478573456823658376457834657836857346858347");
    num1 += num2;
    cmp(num1, "23875384754765870149290820049104436255152737041706435710027");
}

TEST_F(TestBigIntSub, test_sub_1)
{
    BigInt num1("1023");
    BigInt num2("1022");
    BigInt num3 = num1 - num2;
    cmp(num3, "1");
}

TEST_F(TestBigIntSub, test_sub_2)
{
    BigInt num1("11111111111111111111111111111111111111111");
    BigInt num2("01111111111111111111111111111111111111111");
    BigInt num3 = num1 - num2;
    cmp(num3, "10000000000000000000000000000000000000000");
}

TEST_F(TestBigIntSub, test_sub_3)
{
    BigInt num1("-123456789987654321");
    BigInt num2("-123456789987654321");
    BigInt num3 = num1 - num2;
    cmp(num3, "0");
}

TEST_F(TestBigIntSub, test_sub_4)
{
    BigInt num1("-987654321");
    BigInt num2("-123456789987654321");
    BigInt num3 = num1 - num2;
    cmp(num3, "123456789000000000");
}

TEST_F(TestBigIntSub, test_sub_5)
{
    BigInt num1("1000");
    int32_t val2 = 1000;
    BigInt num3 = num1 - val2;
    cmp(num3, "0");
    num3 = val2 - num1;
    cmp(num3, "0");
}

TEST_F(TestBigIntSub, test_sub_6)
{
    BigInt num1("-1000000000000000000");
    int32_t val2 = -1;
    BigInt num3 = num1 - val2;
    cmp(num3, "-999999999999999999");
    num3 = val2 - num1;
    cmp(num3, "999999999999999999");
}

TEST_F(TestBigIntSub, test_sub_7)
{
    BigInt num1("1000000000000000000");
    int32_t val2 = -1;
    BigInt num3 = num1 - val2;
    cmp(num3, "1000000000000000001");
    num3 = val2 - num1;
    cmp(num3, "-1000000000000000001");
}

TEST_F(TestBigIntSub, test_sub_8)
{
    BigInt num1("123456789987654321");
    BigInt num2("-1");
    BigInt num3 = num1 - num2;
    cmp(num3, "123456789987654322");
}

TEST_F(TestBigIntSub, test_inplace_sub_1)
{
    BigInt num1("1023");
    BigInt num2("1022");
    num1 -= num2;
    cmp(num1, "1");
}

TEST_F(TestBigIntSub, test_inplace_sub_2)
{
    BigInt num1("11111111111111111111111111111111111111111");
    BigInt num2("01111111111111111111111111111111111111111");
    num1 -= num2;
    cmp(num1, "10000000000000000000000000000000000000000");
}

TEST_F(TestBigIntSub, test_inplace_sub_3)
{
    BigInt num1("-123456789987654321");
    BigInt num2("-123456789987654321");
    num1 -= num2;
    cmp(num1, "0");
}

TEST_F(TestBigIntSub, test_inplace_sub_4)
{
    BigInt num1("-987654321");
    BigInt num2("-123456789987654321");
    num1 -= num2;
    cmp(num1, "123456789000000000");
}

TEST_F(TestBigIntSub, test_inplace_sub_5)
{
    BigInt num1("123456789987654321");
    BigInt num2("-1");
    num1 -= num2;
    cmp(num1, "123456789987654322");
}

TEST_F(TestBigIntSub, test_inplace_sub_6)
{
    BigInt num1("123456789987654321");
    int32_t val2 = -1;
    num1 -= val2;
    cmp(num1, "123456789987654322");
}

TEST_F(TestBigIntSub, test_inplace_sub_7)
{
    int32_t val2 = -987654321;
    BigInt num1("-123456789987654321");
    num1 -= val2;
    cmp(num1, "-123456789000000000");
}

TEST_F(TestBigIntSub, test_inplace_sub_8)
{
    BigInt num2 = -987654321;
    BigInt num1("-987654321");
    num1 -= num2;
    cmp(num1, "0");
}

TEST_F(TestBigIntMul, test_mul_1)
{
    BigInt num1("123");
    BigInt num2("3");
    BigInt num3 = num1 * num2;
    cmp(num3, "369");
}

TEST_F(TestBigIntMul, test_mul_2)
{
    BigInt num1("-123");
    BigInt num2("3");
    BigInt num3 = num1 * num2;
    cmp(num3, "-369");
}

TEST_F(TestBigIntMul, test_mul_3)
{
    BigInt num1("-1233745637845673485637485");
    BigInt num2("0");
    BigInt num3 = num1 * num2;
    cmp(num3, "0");
}

TEST_F(TestBigIntMul, test_mul_4)
{
    BigInt num1("-1233745637845673485637485");
    BigInt num2("9");
    BigInt num3 = num1 * num2;
    cmp(num3, "-11103710740611061370737365");
}

TEST_F(TestBigIntMul, test_mul_5)
{
    BigInt num1("-12337456378738563475384435345723489345673485637485");
    BigInt num2("938757723637432436783247646734673476346734632547645356"
                "4676543256786543567865434732463247");
    BigInt num3 = num1 * num2;
    cmp(num3, "-115818824655807343436492038733856935632287215318902799"
              "33097331542991369825078340988824869167008284195290480583036"
              "8878480092885330128013795");
}


TEST_F(TestBigIntMul, test_inplace_mul_1)
{
    BigInt num1("-1233745637845673485637485");
    BigInt num2("9");
    num1 *= num2;
    cmp(num1, "-11103710740611061370737365");
    num1 = BigInt("-1233745637845673485637485");
    num1 *= 9;
    cmp(num1, "-11103710740611061370737365");
}

TEST_F(TestBigIntMul, test_inplace_mul_2)
{
    BigInt num1("123");
    BigInt num2("3");
    num1 *= num2;
    cmp(num1, "369");
}

TEST_F(TestBigIntMul, test_inplace_mul_3)
{
    BigInt num1("-123");
    BigInt num2("3");
    num1 *= num2;
    cmp(num1, "-369");
}

TEST_F(TestBigIntMul, test_inplace_mul_4)
{
    BigInt num1("-1233745637845673485637485");
    BigInt num2("0");
    num1 *= num2;
    cmp(num1, "0");
}





int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
