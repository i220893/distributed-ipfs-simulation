#include <iostream>
#include <cstring>
using namespace std;

class BigInt
{
    char *value;
    int size;

public:
    BigInt(int);

    BigInt(const string &text);

    BigInt(const BigInt &copy); // copy constructor

    char getValue(int i) const;

    void setValue(char *ptr);

    void setValue(int i);

    void setSize(int i);

    int getSize() const;

    void getValue();

    int *BigInt_to_Int(const BigInt &val) const;

    BigInt Int_to_BigInt(int *ptr, int count) const;

    int *Int_to_Int(int val) const;

    BigInt operator+(const BigInt &val) const;

    BigInt operator+(int val) const;

    BigInt operator-(const BigInt &val) const;

    BigInt operator-(int val) const;

    BigInt operator*(const BigInt &val) const;

    BigInt operator=(const BigInt& val);
    // Logical Operators
    bool operator==(const BigInt &val) const;

    bool operator==(const char *val) const;

    bool operator!=(const BigInt &val) const;

    bool operator<(const BigInt &val) const;

    bool operator<=(const BigInt &val) const;

    bool operator>(const BigInt &val) const;

    bool operator>=(const BigInt &val) const;

    // Unary Operators


    BigInt operator++(int); // Post-increment Operator

    BigInt &operator--(); // Pre-decrement Operator



    // Conversion Operator
    operator string(); // return value of the BigInt as string

    operator int(); // return the number of digits in big Integer

    ~BigInt(); // destructor*/

    friend ostream &operator<<(ostream &output, const BigInt &val); // outputs the BigInt

    friend istream &operator>>(istream &input, BigInt &val); // inputs the BigInt
};
