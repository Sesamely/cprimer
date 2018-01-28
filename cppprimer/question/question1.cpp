/************************************************************************
****	> File Name:    	temp.cpp
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 22 Jan 2018 11:34:22 PM CST
************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

struct Date { 
    int64_t start;
    char a;
    char a2;
    char a3;
    char a4;
    char a5;
    int b;
    int testfunc(int &i) {
        return i;
    }
private:
    int test;
    //int64_t c;
    //char d;
    //char e[10];
    //int32_t f;
};

int main1() {
    Date test[2];
    cout << hex << reinterpret_cast<int64_t>(&test[0].start) << endl;
    cout << hex << reinterpret_cast<int64_t>(&test[0].a ) << endl;
    cout << hex << reinterpret_cast<int64_t>(&test[0].a2) << endl;
    cout << hex << reinterpret_cast<int64_t>(&test[0].a3)<< endl;
    cout << hex << reinterpret_cast<int64_t>(&test[0].a4)<< endl;
    cout << hex << reinterpret_cast<int64_t>(&test[0].a5)<< endl;
    cout << hex << reinterpret_cast<int64_t>(&test[0].b) << endl;
    /*
     *cout << hex << reinterpret_cast<int64_t>(&test[0].c) << endl;
     *cout << hex << reinterpret_cast<int64_t>(&test[0].d) << endl;
     *cout << hex << reinterpret_cast<int64_t>(&test[0].e) << endl;
     *cout << hex << reinterpret_cast<int64_t>(&test[0].f) << endl;
     */

    cout << hex << reinterpret_cast<int64_t>(&test[1]) << endl;
    return 0;
}



struct CopyTest {
    CopyTest(int a=0, string s="", double d=0, int *p = nullptr) :
        a(a), s(s), d(d), p(p==nullptr?p:new int(*p)) { cout << "this is default" << endl; }
    CopyTest(const CopyTest &ct) : 
        a(ct.a), s(ct.s), d(ct.d), p(new int(*ct.p)) { cout << "this is copy constructor" << endl; }
    const CopyTest &operator=(const CopyTest &ct);
    ~CopyTest() {delete p; cout << "this is destructor" << endl;}
private:
    int a;
    string s;
    double d;
public:
    int *p;
};
const CopyTest &CopyTest::operator=(const CopyTest &ct) {
    cout << "this is copy-assignment operator" << endl;
    a = ct.a;
    s = ct.s;
    d = ct.d;
    p = new int(*ct.p);
    return *this;
} 


int main2()
{
    int *p = new int(10);
    CopyTest ct(1,"liuyiwen", 0, p);
    delete p;
    CopyTest ct1=ct, ct2, ct3;
    ct2 = ct1;
    ct3 = ct2;

    cout << ct.p  << endl;
    cout << ct1.p << endl;
    cout << ct2.p << endl;
    cout << ct3.p << endl;

    cout << '\n';
    swap (ct.p, ct1.p);
    cout << ct.p  << endl;
    cout << ct1.p << endl;
    return 0;
}

struct test2  {
    int a;
    int b; 
    void dispTest2C() {cout << c << endl;}
private:
    double c;
};
int main() {
    test2 t2;
    cout << t2.a << ' ' << t2.b << ' ';
    t2.dispTest2C();
    return 0;
}
