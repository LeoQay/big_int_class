#include <iostream>

#include "num.h"

int main()
{
    string a, b;

    getline(cin, a);
    getline(cin, b);

    num num_a(a), num_b(b);

    num res = num_a * num_b;

    res.print();

    return 0;
}