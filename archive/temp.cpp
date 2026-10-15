#include <iostream>
#include <cmath>
#include <string>
#include "BigInt.h"

using namespace std;
//using namespace boost::multiprecision;
BigInt FindingPower(int a, BigInt num) {
    BigInt result(0);
    char* product = new char [num.getSize()];
    for (int i = 0; i < num.getSize(); i++) {
        product[i] = '0';
    }
    product[num.getSize() - 1] = '1';
    product[num.getSize()] = '\0';
    cout << product << endl;
    cout << sizeof(product) << endl;
    for (int i = num.getSize() - 1, j = num.getSize(); i >= 0; i--, j++) {
        int number = 2 * int(num.getValue(i));
        if (number > 10) {
            product[j] += (char(number % 10) + '0');
            product[j - 1] = '1';
        }
        else {
            product[j] += (char(number) + 0);
        }
    }
    product[num.getSize()] = '\0';
    cout << product << endl;
    
    return num;
}

int main()
{
    BigInt n("1234567890123456789");
    cout << "N size = " << n.getSize()<<endl;
    int number = n;
    //cout<<number<<endl;
    BigInt res1(0);
    res1 = FindingPower(2, n);
    // int res = pow(2, number);
    // cout << "2 raised to the power of " << n << " is " << res << endl;
    cout << "Hello World" << endl;
    return 0;
}