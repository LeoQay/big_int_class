//
// Created by leonid on 6/17/21.
//
#include <iostream>
#include <cmath>

#include "num.h"

using namespace std;


void num::eraser()
{
    type_int k = this->vec.size();

    while (k > 1 and (*this)[k - 1] == 0)
    {
        this->pop_back();
        k--;
    }
}


long num::size()
{
    return vec.size();
}


void num::push_back(type_int value)
{
    vec.push_back(value);
}


void num::pop_back()
{
    vec.pop_back();
}


type_int& num::operator[] (type_int index)
{
    return vec[index];
}


bool num::large(num &operand1, num & operand2)
{
    if (operand1.size() > operand2.size()) return true;
    if (operand1.size() < operand2.size()) return false;

    for (long i = operand1.size() - 1; i >= 0; i--)
        if (operand1[i] > operand2[i]) return true;

        return false;
}


bool num::equal(num &operand1, num &operand2)
{
    if (operand1.size() != operand2.size()) return false;

    for (long i = operand1.size() - 1; i >= 0; i--)
        if (operand1[i] != operand2[i]) return false;

        return true;
}


num num::add (num & operand1, num & operand2)
{
    type_int n = operand1.size() > operand2.size() ? operand1.size() : operand2.size();

    type_int s1 = operand1.size();
    type_int s2 = operand2.size();

    for (type_int i = 0; i < n - s1; i++) operand1.push_back(0);
    for (type_int i = 0; i < n - s2; i++) operand2.push_back(0);

    num result = operand1;

    type_int ost = 0;

    for (long i = 0; i < n; i++)
    {
        type_int value = result[i] + operand2[i] + ost;
        result[i] = value % power;
        ost       = value / power;
    }
    if (ost != 0) result.push_back(ost);

    return result;
}


/// предполагется, что |operand1| >= |operand2|
num num::sub (num & operand1, num & operand2)
{
    type_int n = operand1.size();
    type_int s2 = operand2.size();

    for (long i = 0; i < n - s2; i++) operand2.push_back(0);

    num result = operand1;

    for (type_int i = 0; i < n; i++)
    {
        if (result[i] < operand2[i])
        {
            result[i] += power;
            type_int j = i + 1;
            while (result[j] == 0)
            {
                result[j] += power - 1;
                j++;
            }
            result[j]--;
        }

        result[i] -= operand2[i];
    }

    result.eraser();

    return result;
}


num num::mul_on_int(type_int operand)
{
    num result;
    result.vec.clear();

    long size = (*this).vec.size();

    type_int ostatok = 0;

    for (long i = 0; i < size; i++)
    {
        type_int value = (*this).vec[i] * operand + ostatok;

        result.push_back(value % power);

        ostatok = value / power;
    }

    while (ostatok != 0)
    {
        result.push_back(ostatok % power);
        ostatok /= power;
    }

    result.eraser();

    return result;
}


num num::mul_on_num(num & operand)
{
    num result;

    num * operand1;
    num * operand2;

    if (large(*this, operand))
    {
        operand1 = this;
        operand2 = &operand;
    }else
    {
        operand1 = &operand;
        operand2 = this;
    }

    type_int size = operand2->size();

    for (type_int i = 0; i < size; i++)
    {
        num buffer = operand1->mul_on_int((*operand2)[i]);

        for (type_int j = 0; j < i; j++)
            buffer = buffer.mul_on_int(power);

        result = result + buffer;
    }

    return result;
}


bool num::operator> (num & operand)
{
    if ((*this).is_minus == operand.is_minus)
        return large(*this, operand) xor operand.is_minus;
    else
        return !(*this).is_minus;
}


bool num::operator== (num & operand)
{
    return ((*this).is_minus == operand.is_minus) && equal(*this, operand);
}


bool num::operator>= (num & operand)
{
    return ((*this) > operand) || ((*this) == operand);
}


bool num::operator< (num & operand)
{
    return !((*this) >= operand);
}


bool num::operator!= (num & operand)
{
    return !((*this) == operand);
}


bool num::operator<= (num & operand)
{
    return !((*this) > operand);
}


num num::operator+ (num & operand)
{
    num result;

    if ((*this).is_minus == operand.is_minus)
    {
        result = add (*this, operand);
        result.is_minus = (*this).is_minus;
    }else if (large(*this, operand))
    {
        result = sub (*this, operand);
        result.is_minus = (*this).is_minus;
    }else
    {
        result = sub (operand, *this);
        result.is_minus = operand.is_minus;
    }

    return result;
}


num num::operator- (num &operand)
{
    num result;

    if ((*this).is_minus != operand.is_minus)
    {
        result = add (*this, operand);
        result.is_minus = (*this).is_minus;
    }else if (large(*this, operand))
    {
        result = sub (*this, operand);
        result.is_minus = (*this).is_minus;
    }else
    {
        result = sub (operand, *this);
        result.is_minus = !(*this).is_minus;
    }

    return result;
}


num::num()
{
    is_minus = false;
    vec.push_back(0);
}


num::num(string value)
{
    if(value[0] == '-')
    {
        is_minus = true;
        value.erase(0, 1);
    }else
        is_minus = false;


    type_int size = value.length();

    for(type_int i = 0; i < (degree - size % degree) % degree; i++)
        value =  '0' + value;

    while(value != "")
    {
        type_int buffer = 0;

        type_int size_now = value.length();

        for (type_int i = size_now - degree; i < size_now; i++)
            buffer = buffer * 10 + (value[i] - '0');

        vec.push_back(buffer);

        value.erase(size_now - degree, degree);
    }
}


num::num(type_int value)
{
    is_minus = value < 0;

    if(is_minus) value = -1 * value;

    do {
        vec.push_back(value % power);
        value /= power;
    } while (value > 0);
}


void num::print()
{
    if (is_minus) cout << "-";

    for (type_int i = vec.size() - 1; i >= 0; i--)
    {
        if (i != vec.size() - 1)
        {
            type_int kol;

            if (vec[i] == 0)
                kol = degree - 1;
            else
                kol = degree - floor(log(vec[i]) / log(10)) - 1;

            for (type_int j = 0; j < kol; j++)
                cout << "0";
        }

        cout << vec[i];
    }
}


num num::operator% (num & operand)
{

}


num num::operator/ (num & operand)
{

}


num num::operator* (num & operand)
{
    num result = this->mul_on_num(operand);

    num zero;

    result.is_minus = this->is_minus != operand.is_minus and *this != zero and operand != zero;

    return result;
}