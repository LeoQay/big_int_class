//
// Created by leonid on 6/17/21.
//

#ifndef HAH_NUM_H
#define HAH_NUM_H

#include <vector>

using namespace std;

class num
{
private:
    vector <int> vec;  // число хранится в перевернутом виде, начиная с младших разрядов
    bool is_minus;         // false - positive, true - negative
    int degree = 3;
    int power = 1000;

    long size();

    void push_back(int value);

    void pop_back();

    int& operator[] (long index);

    num add (num & operand1, num & operand2);

    num sub (num & operand1, num & operand2);

    num mul_on_int (int operand);

    num mul_on_num (num & operand);

    bool large (num & operand1, num & operand2);

    bool equal (num & operand1, num & operand2);

    void eraser ();

public:
    num();

    num(string value);

    explicit num (long long value);

    num operator+ (num & operand);

    num operator- (num & operand);

    num operator* (num & operand);

    num operator/ (num & operand);

    num operator% (num & operand);

    bool operator> (num & operand);

    bool operator< (num & operand);

    bool operator== (num & operand);

    bool operator>= (num & operand);

    bool operator<= (num & operand);

    bool operator!= (num & operand);

    void print ();
};


#endif //HAH_NUM_H
