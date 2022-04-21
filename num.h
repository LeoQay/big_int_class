//
// Created by leonid on 6/17/21.
//

#ifndef HAH_NUM_H
#define HAH_NUM_H

#include <vector>

using namespace std;

typedef long long type_int;

class num
        {
        private:
            vector <type_int> vec;  // число хранится в перевернутом виде, начиная с младших разрядов
            bool is_minus;         // false - positive, true - negative
            type_int degree = 9;
            type_int power = 1000000000;

            long size();

            void push_back(type_int value);

            void pop_back();

            type_int& operator[] (type_int index);

            num add (num & operand1, num & operand2);

            num sub (num & operand1, num & operand2);

            num mul_on_int (type_int operand);

            num mul_on_num (num & operand);

            num div_on_int(type_int val);

            bool large (num & operand1, num & operand2);

            bool equal (num & operand1, num & operand2);

            void eraser ();

        public:
            num();

            num(string value);

            explicit num (type_int value);

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
