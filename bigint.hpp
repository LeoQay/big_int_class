#ifndef MSU_CPP_SPRING_2022_BIGINT_H
#define MSU_CPP_SPRING_2022_BIGINT_H

#include <iostream>
#include <string>


class BigInt
{
public:
    BigInt();
    virtual ~BigInt();

    BigInt(int32_t value);
    BigInt & operator= (int32_t value);

    BigInt(const std::string & str);
    BigInt & operator= (const std::string & str);

    BigInt(const BigInt & other);
    BigInt & operator= (const BigInt & other);

    BigInt(BigInt && other) noexcept;
    BigInt & operator= (BigInt && other) noexcept;

    BigInt & operator-();

    bool operator== (const BigInt & other) const;
    bool operator!= (const BigInt & other) const;
    bool operator> (const BigInt & other) const;
    bool operator<= (const BigInt & other) const;
    bool operator< (const BigInt & other) const;
    bool operator>= (const BigInt & other) const;

    BigInt & operator+= (const BigInt & other);
    BigInt & operator+= (int32_t value);

    BigInt operator+ (const BigInt & other) const;
    BigInt operator+ (int32_t value) const;

    friend BigInt operator+ (int32_t value, const BigInt & other);

    BigInt & operator-= (const BigInt & other);
    BigInt & operator-= (int32_t value);

    BigInt operator- (const BigInt & other) const;
    BigInt operator- (int32_t value) const;

    friend BigInt operator- (int32_t value, const BigInt & other);

    BigInt & operator*= (const BigInt & other);
    BigInt & operator*= (int32_t value);

    BigInt operator* (const BigInt & other) const;
    BigInt operator* (int32_t value) const;

    friend BigInt operator* (int32_t value, const BigInt & other);

    friend std::ostream & operator<< (std::ostream & stream, const BigInt & num);
private:
    // не обращают внимания на знаки

    // is self more large than other
    [[nodiscard]] bool large(const BigInt & other) const;

    [[nodiscard]] bool equal(const BigInt & other) const;

    [[nodiscard]] BigInt add(const BigInt & other) const;

    // ожидает, что |self| >= |other|
    [[nodiscard]] BigInt sub(const BigInt & other) const;

    [[nodiscard]] BigInt mul(const BigInt & other) const;

    void inplace_add(const BigInt & other);

    // |self| >= |other|
    void inplace_sub(const BigInt & other);

    void inplace_mul(const BigInt & other);

    // dest, a, b - могут быть одним адресом
    // Ожидает, что по адресу dest места не меньше, чем 1 + max(len_a, len_b)
    size_t low_add(uint32_t * dest,
                   const uint32_t * a, size_t len_a,
                   const uint32_t * b, size_t len_b) const;

    // dest, a, b - могут быть одним адресом
    // Ожидает, что по адресу dest места не меньше, чем max(len_a, len_b)
    // Ожидает, что a >= b
    size_t low_sub(uint32_t * dest,
                   const uint32_t * a, size_t len_a,
                   const uint32_t * b, size_t len_b) const;

    // ожидает, что по адресу dest места не меньше, чем (size + 2)
    size_t low_mul(uint32_t * dest,
                   const uint32_t * src, size_t size,
                   uint32_t value) const;

    static int digit_num(uint32_t value, uint32_t _base);

    void make_zero();

    void cut_zeros();

    void check_none() const;

    void set_zero_sign();

    [[nodiscard]] bool check_zero() const;

    static bool check_num_token(const std::string & str);

    // ожидает, что строка не длиннее, чем digits,
    // а также корректные символы (только цифры)
    static uint32_t str_to_uint(const std::string & str);


    uint32_t * ptr = nullptr;
    size_t len = 0;
    size_t real_len = 0;
    bool is_minus = false;

    size_t offset = 10;

    // 2 * (basis ^ power) < 2 ^ 32
    uint32_t base = 1000000000;
    int digits = 9;
    /*
    int basis = 10;
    int power = 9;
     */
};


#endif //MSU_CPP_SPRING_2022_BIGINT_H
