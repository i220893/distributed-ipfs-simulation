#include <iostream>
#include <cstring>
#include "BigInt.h"
using namespace std;

BigInt::BigInt(int val = 0)
{

    int temp1 = val % 10;
    int temp2 = val;
    int count = 0;

    for (int i = 0; temp2 != 0; i++)
    {
        count++;
        temp2 = temp2 / 10;
        temp1 = temp2 % 10;
    }

    value = new char[count];
    size = count;
    value[count] = '\0';
    count--;
    temp1 = val % 10;
    temp2 = val;

    while (count >= 0)
    {
        if (temp1 == 0)
            value[count] = '0';

        else if (temp1 == 1)
            value[count] = '1';

        else if (temp1 == 2)
            value[count] = '2';

        else if (temp1 == 3)
            value[count] = '3';

        else if (temp1 == 4)
            value[count] = '4';

        else if (temp1 == 5)
            value[count] = '5';

        else if (temp1 == 6)
            value[count] = '6';

        else if (temp1 == 7)
            value[count] = '7';

        else if (temp1 == 8)
            value[count] = '8';

        else if (temp1 == 9)
            value[count] = '9';

        count--;
        temp2 = temp2 / 10;
        temp1 = temp2 % 10;
    }
}

BigInt::BigInt(const string &text)
{
    int count = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        count++;
    }
    size = count;
    value = new char[count];
    value[count] = '\0';
    for (int i = 0; text[i] != '\0'; i++)
    {
        value[i] = text[i];
    }
}

BigInt::BigInt(const BigInt &copy) // copy constructor
{
    int count = 0;

    for (int i = 0; copy.getValue(i) != '\0'; i++)
    {
        count++;
    }
 
    value = new char[count];
    size = count;
    for (int i = 0; i < count; i++)
    {
        value[i] = copy.getValue(i);
    }

    value[size] = '\0';
}

char BigInt::getValue(int i) const
{
    return value[i];
}

void BigInt::setValue(char *ptr)
{
    for (int i = 0; ptr[i] != '\0'; i++)
    {
        value[i] = ptr[i];
    }
}

void BigInt::setValue(int i)
{
    value[i] = '\0';
}

void BigInt::setSize(int i)
{
    size = i;
}

int BigInt::getSize() const
{
    return size;
}

void BigInt::getValue()
{
    cout << value;
}

int *BigInt::BigInt_to_Int(const BigInt &val) const
{
    int *ptr = new int[val.getSize()];
    int count = val.getSize() - 1;

    while (count >= 0)
    {
        if (val.getValue(count) == '0')
            ptr[count] = 0;

        else if (val.getValue(count) == '1')
            ptr[count] = 1;

        else if (val.getValue(count) == '2')
            ptr[count] = 2;

        else if (val.getValue(count) == '3')
            ptr[count] = 3;

        else if (val.getValue(count) == '4')
            ptr[count] = 4;

        else if (val.getValue(count) == '5')
            ptr[count] = 5;

        else if (val.getValue(count) == '6')
            ptr[count] = 6;

        else if (val.getValue(count) == '7')
            ptr[count] = 7;

        else if (val.getValue(count) == '8')
            ptr[count] = 8;

        else if (val.getValue(count) == '9')
            ptr[count] = 9;

        count--;
    }
    return ptr;
}

BigInt BigInt::Int_to_BigInt(int *ptr, int count) const
{
    char *result = new char[count + 1];
    BigInt temp;
    temp.setSize(count + 1);

    while (count >= 0)
    {
        if (ptr[count] == 0)
            result[count] = '0';

        else if (ptr[count] == 1)
            result[count] = '1';

        else if (ptr[count] == 2)
            result[count] = '2';

        else if (ptr[count] == 3)
            result[count] = '3';

        else if (ptr[count] == 4)
            result[count] = '4';

        else if (ptr[count] == 5)
            result[count] = '5';

        else if (ptr[count] == 6)
            result[count] = '6';

        else if (ptr[count] == 7)
            result[count] = '7';

        else if (ptr[count] == 8)
            result[count] = '8';

        else if (ptr[count] == 9)
            result[count] = '9';

        count--;
    }

    temp.setValue(result);

    return temp;
}

int *BigInt::Int_to_Int(int val) const
{
    int *ans;

    int temp1 = val % 10;
    int temp2 = val;
    int count = 0;

    for (int i = 0; temp2 != 0; i++)
    {
        count++;
        temp2 = temp2 / 10;
        temp1 = temp2 % 10;
    }

    ans = new int[count];
    ans[count] = '\0';
    count--;
    temp1 = val % 10;
    temp2 = val;

    while (count >= 0)
    {
        if (temp1 == 0)
            ans[count] = 0;

        else if (temp1 == 1)
            ans[count] = 1;

        else if (temp1 == 2)
            ans[count] = 2;

        else if (temp1 == 3)
            ans[count] = 3;

        else if (temp1 == 4)
            ans[count] = 4;

        else if (temp1 == 5)
            ans[count] = 5;

        else if (temp1 == 6)
            ans[count] = 6;

        else if (temp1 == 7)
            ans[count] = 7;

        else if (temp1 == 8)
            ans[count] = 8;

        else if (temp1 == 9)
            ans[count] = 9;

        count--;
        temp2 = temp2 / 10;
        temp1 = temp2 % 10;
    }

    return ans;
}

BigInt BigInt::operator+(const BigInt &val) const
{
    int *num1 = BigInt_to_Int(*this);
    int *num2A = BigInt_to_Int(val);
    int *num2 = BigInt_to_Int(val);

    int *result;

    // result = new int[size + val.getSize()];

    int *tempo;
    int t;
    int size1 = size - 1;
    int size2 = val.getSize() - 1;
    int count = 0;
    int temp = 0;
    // count = size + val.getSize() - 1;

    if (size >= val.getSize())
    {
        result = new int[size + 1];
        count = size - 1;
    }

    else
    {
        result = new int[val.getSize() + 1];
        count = val.getSize() - 1;
    }

    for (int i = 0; i <= count + 1; i++)
    {
        result[i] = 0;
    }

    if (size1 > size2)
    {

        num2 = new int[size1];
        for (int i = 0; i <= size1 - size2; i++)
        {
            num2[i] = 0;
        }

        for (int i = size1 - size2, j = 0; i <= size1; j++, i++)
        {
            num2[i] = num2A[j];
        }

        size2 = size1;
    }

    /*else if(size1< size2)
    {
        tempo = num1;
        num1 = num2;
        num2 = tempo;

        t = size1;
        size1 = size2;
        size2 = t;


    }
*/
    for (int i = count + 1; i >= 1; i--)
    {
        result[i] = num1[size1] + num2[size2] + result[i];

        if (result[i] > 9)
        {
            temp = result[i];
            result[i] = result[i] % 10;
            result[i - 1] = temp / 10;
        }

        size1--;
        size2--;
    }

    while (result[0] == 0)
    {
        for (int j = 0; j < size; j++)
        {
            result[j] = result[j + 1];
        }
        count--;
    }

    BigInt *Ans = new BigInt;
    *Ans = Int_to_BigInt(result, count + 1);

    Ans->setValue(count + 2);

    return *Ans;
}

BigInt BigInt::operator+(int val) const
{

    int *result = new int[size + 1];
    // int *num1A = BigInt_to_Int(*this);
    int *num2A = Int_to_Int(val);
    int *num2 = Int_to_Int(val);
    int *num1 = BigInt_to_Int(*this);

    int size1 = size - 1;
    int size2 = 0;
    int temp = 0;
    int check = val;
    int count = size - 1;

    for (int i = 0;; i++)
    {
        if (check != 0)
        {
            check = check / 10;
            size2++;
        }

        else
            break;
    }

    size2--;

    for (int i = 0; i <= count + 1; i++)
    {
        result[i] = 0;
    }

    if (size1 > size2)
    {
        num2 = new int[size1];
        for (int i = 0; i <= size1 - size2; i++)
        {
            num2[i] = 0;
        }

        for (int i = size1 - size2, j = 0; i <= size1; j++, i++)
        {
            num2[i] = num2A[j];
        }

        size2 = size1;
    }

    if (size1 < size2)
    {
        int *temp = num1;
        num1 = num2;
        num2 = temp;
    }

    /*
    if (size1 < size2)
    {
        num1 = new int[size2];
        for (int i = 0; i <= size2 - size1; i++)
        {
            num1[i] = 0;
        }

        for (int i = size2 - size1, j = 0; i <= size2; j++, i++)
        {
            num1[i] = num1A[j];
        }

        size1 = size2;
    }
*/

    for (int i = count + 1; i >= 1; i--)
    {
        // cout<<num1[size1]<<" "<<num2[size2]<<"  "<<result[i]<<" "<<size2;
        result[i] = num1[size1] + num2[size2] + result[i];
        // cout<<"  "<<result[i]<<endl;
        if (result[i] > 9)
        {
            temp = result[i];
            result[i] = result[i] % 10;
            result[i - 1] = temp / 10;
        }

        size1--;
        size2--;
    }
    // cout<<result[0]<<result[1]<<result[2]<<endl;
    while (result[0] == 0)
    {
        for (int j = 0; j < size; j++)
        {
            result[j] = result[j + 1];
        }
        // result[size] = 0;
        count--;
    }

    // cout<<result[0]<<result[1]<<result[2]<<endl;

    BigInt *Ans = new BigInt;
    *Ans = Int_to_BigInt(result, count + 1);

    Ans->setValue(count + 2);
    // cout<<*Ans<<endl;
    return *Ans;
}

BigInt BigInt::operator-(const BigInt &val) const
{
    const int *num1 = BigInt_to_Int(*this);
    int *num2A = BigInt_to_Int(val);
    int *num2 = BigInt_to_Int(val);
    ;

    int *result;

    int size1 = size - 1;
    int size2 = val.getSize() - 1;
    int count = 0;
    int temp = 0;

    if (size >= val.getSize())
    {
        result = new int[size];
        count = size - 1;
    }

    else
    {
        result = new int[val.getSize()];
        count = val.getSize() - 1;
    }

    for (int i = 0; i <= count; i++)
    {
        result[i] = 0;
    }

    if (size1 > size2)
    {

        num2 = new int[size1];
        for (int i = 0; i <= size1 - size2; i++)
        {
            num2[i] = 0;
        }

        for (int i = size1 - size2, j = 0; i <= size1; j++, i++)
        {
            num2[i] = num2A[j];
        }

        size2 = size1;
    }

    for (int i = count; i >= 0; i--)
    {
        result[i] = num1[size1] - num2[size2] + result[i];

        if (result[i] < 0)
        {
            temp = result[i];
            result[i] = result[i] + 10;
            result[i - 1] = -1;
        }

        size1--;
        size2--;
    }

    while (result[0] == 0)
    {
        for (int j = 0; j < size - 1; j++)
        {
            result[j] = result[j + 1];
        }
        count--;
    }

    BigInt Ans = Int_to_BigInt(result, count);

    Ans.setValue(count + 1);
    return Ans;
}

BigInt BigInt::operator-(int val) const
{
    int *result = new int[size];
    const int *num1 = BigInt_to_Int(*this);
    const int *num2A = Int_to_Int(val);
    int *num2 = Int_to_Int(val);

    int size1 = size - 1;
    int size2 = 0;
    int temp = 0;
    int check = val;
    int count = size - 1;

    for (int i = 0;; i++)
    {
        if (check != 0)
        {
            check = check / 10;
            size2++;
        }

        else
            break;
    }

    size2--;

    for (int i = 0; i <= count; i++)
    {
        result[i] = 0;
    }

    if (size1 > size2)
    {
        num2 = new int[size1];
        for (int i = 0; i <= size1 - size2; i++)
        {
            num2[i] = 0;
        }

        for (int i = size1 - size2, j = 0; i <= size1; j++, i++)
        {
            num2[i] = num2A[j];
        }

        size2 = size1;
    }

    for (int i = count; i >= 0; i--)
    {
        // cout<<num1[size1]<<" "<<num2[size2]<<"  "<<result[i]<<" "<<size2<<endl;
        result[i] = num1[size1] - num2[size2] + result[i];
        if (result[i] < 0)
        {
            temp = result[i];
            result[i] = result[i] + 10;
            result[i - 1] = -1;
        }

        size1--;
        size2--;
    }

    while (result[0] == 0)
    {
        for (int j = 0; j < size - 1; j++)
        {
            result[j] = result[j + 1];
        }
        count--;
    }

    BigInt Ans = Int_to_BigInt(result, count);

    Ans.setValue(count + 1);
    return Ans;
}

BigInt BigInt::operator*(const BigInt &val) const
{
    BigInt temp;

    int *num1 = BigInt_to_Int(*this);
    int *num2 = BigInt_to_Int(val);

    int *result = new int[size + val.getSize()];

    return temp;
}

BigInt BigInt::operator=(const BigInt& val)
{
    size = val.getSize();

    value = new char[size];

    for (int i = 0; i < size; i++)
    {
        value[i] = val.getValue(i);
    }

    value[size] = '\0';

    return *this;

}

// Logical Operators
bool BigInt::operator==(const BigInt &val) const
{
    // if (size != val.getSize())
    //  return false;

    for (int i = 0; value[i] != '\0'; i++)
    {
        if (value[i] != val.getValue(i))
            return false;
    }

    return true;
}

bool BigInt::operator==(const char *val) const
{
    int size1 = 0;

    for (int i = 0; val[i] != '\0'; i++)
    {
        size1++;
    }

    // if (size != size1)
    //   return false;

    for (int i = 0; value[i] != '\0'; i++)
    {
        if (value[i] != val[i])
            return false;
    }

    return true;
}

bool BigInt::operator!=(const BigInt &val) const
{
    if (*this == val)
        return false;

    return true;
}

bool BigInt::operator<(const BigInt &val) const
{
    if (size < val.getSize())
        return true;

    if (size > val.getSize())
        return false;

    for (int i = 0; value[i] != '\0'; i++)
    {
        if (value[i] < val.getValue(i))
            return true;

        if (value[i] > val.getValue(i))
            return false;
    }

    return false;
}

bool BigInt::operator<=(const BigInt &val) const
{
    if (size < val.getSize())
        return true;

    if (size > val.getSize())
        return false;

    for (int i = 0; value[i] != '\0'; i++)
    {
        if (value[i] < val.getValue(i))
            return true;

        if (value[i] > val.getValue(i))
            return false;
    }

    return true;
}

bool BigInt::operator>(const BigInt &val) const
{
    if (size > val.getSize())
        return true;

    if (size < val.getSize())
        return false;

    for (int i = 0; value[i] != '\0'; i++)
    {
        if (value[i] > val.getValue(i))
            return true;

        if (value[i] < val.getValue(i))
            return false;
    }

    return false;
}

bool BigInt::operator>=(const BigInt &val) const
{
    if (size > val.getSize())
        return true;

    if (size < val.getSize())
        return false;

    for (int i = 0; value[i] != '\0'; i++)
    {
        if (value[i] > val.getValue(i))
            return true;

        if (value[i] < val.getValue(i))
            return false;
    }

    return true;
}

// Unary Operators

BigInt BigInt::operator++(int) // Post-increment Operator
{
    BigInt *temp = new BigInt;
    temp->value = value;
    *this = *this + 1;
    return *temp;
}

BigInt &BigInt::operator--() // Pre-decrement Operator
{
    BigInt *temp = new BigInt;
    *this = *this - 1;
    temp->value = value;
    return *temp;
}

// Conversion Operator
BigInt::operator string() // return value of the BigInt as string
{
    return value;
}
BigInt::operator int() // return the number of digits in big Integer
{
    return size;
}

BigInt::~BigInt() // destructor*/
{
}

ostream &operator<<(ostream &output, const BigInt &val) // outputs the BigInt
{
    output << val.value;

    return output;
}

istream &operator>>(istream &input, BigInt &val) // inputs the BigInt
{
    input >> val.value;
    return input;
}