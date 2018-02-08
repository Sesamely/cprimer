/************************************************************************
****	> File Name:    	print_f_1_to_n.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 05 Feb 2018 04:23:59 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

using number_type = string;

class bignumber {
private:
    const unsigned MASK_LOW = 0x0F,
                    MASK_HIGH = 0xF0;
    number_type number;
    long sz;    

public:
    void allocate(long n) {
        sz = n;
        number.assign(n/2+1, '0');
    }
    long size() const {
        return sz;
    }
    int operator[](int i) const {
        return (i & 0x01) ? ((number[i>>1] & MASK_HIGH)>>4) :
                                (number[i>>1] & MASK_LOW);
    }
    void assign(int loc, int value) {
        if (value<0 || value>=10) 
            throw out_of_range("only allow value int [1,9]");
        unsigned uv = value;
        if (loc & 0x01) {
            number[loc>>1] = ((number[loc>>1] & MASK_LOW) | ((uv & MASK_LOW) << 4));
        }
        else {
            number[loc>>1] = (number[loc>>1] & MASK_HIGH) | (uv & MASK_LOW);
        }
    }
};

int cnt = 0;
void print_bn(const bignumber &bn)
{
    if (!(++cnt % 11)) {
        cout << endl;
    }
    unsigned index=~(0);
    while(++index<bn.size() && bn[index]==0);

    cout << setw(2);
    for (; index<bn.size(); ++index) {
        cout << bn[index];
    }
}
void bn_print_f_1_to_n_auxiliary(bignumber &bn, int index);
void bn_print_f_1_to_n(int n)
{
    bignumber bn;
    bn.allocate(n);

    bn_print_f_1_to_n_auxiliary(bn, 0);
    cout << endl;
}
void bn_print_f_1_to_n_auxiliary(bignumber &bn, int index) 
{
    if (index == bn.size()) {
        print_bn(bn);
        return;
    }
    for (int i=0; i<10; ++i) {
        bn.assign(index, i);
        bn_print_f_1_to_n_auxiliary(bn, index+1);
    }
}


void print(const number_type &number)
{
    unsigned index=~(0);
    while(++index<number.size() && number[index]=='0');

    for (; index<number.size(); ++index) {
        cout << number[index];
    }
    cout << " ";
}

void print_f_1_to_n_auxiliary(number_type &number, int index);
void print_f_1_to_n(int n)
{
    number_type number;
    number.assign(n, '0');

    print_f_1_to_n_auxiliary(number, 0);
    cout << endl;
}
void print_f_1_to_n_auxiliary(number_type &number, int index) 
{
    if (index == static_cast<int>(number.size())) {
        print(number);
        return;
    }
    for (int i=0; i<10; ++i) {
        number[index] = i + '0';
        print_f_1_to_n_auxiliary(number, index+1);
    }
}

int main()
{
    int n;
    cin >> n;
    bn_print_f_1_to_n(n);
    return 0;
}
