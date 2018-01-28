/************************************************************************
****	> File Name:    	HasPtr.h
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Mon 22 Jan 2018 08:27:36 PM CST
************************************************************************/

#ifndef _HASPTR_H
#define _HASPTR_H

#include <iostream>
#include <string>
#include <memory>
using namespace std;
class HasPtr {
public:
    HasPtr() : ps(new string()), i(0), use(new std::size_t(1)) {
        cout << "this is default constructor" << endl;
    }
    HasPtr(const std::string &s) :
        ps(new string(s)), i(0), use(new std::size_t(1)) { 
            cout << "this is constructor" << endl;
        }
    HasPtr(const HasPtr &p) :
        ps(p.ps), i(p.i), use(p.use) { 
            cout << "this is copy constructor" << endl;
            ++*use; 
        }
    ~HasPtr() { 
        cout << "this is destructor" << endl;
        if (--*use == 0) {
            delete ps;
            delete use;
        }  
    }
    const HasPtr &operator=(const HasPtr &p);
    void dispString() { 
        cout << "address is: " << hex << this->ps << " value is: " << *this->ps << endl; 
    }
private:
    std::string *ps;
    int i;
    std::size_t *use;
};
const HasPtr &HasPtr::operator=(const HasPtr &p) {
    cout << "this is copy-assignment operator" << endl;
    ++*p.use;
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    ps = p.ps;
    i = p.i;
    use = p.use;
    return *this;
}
#endif
