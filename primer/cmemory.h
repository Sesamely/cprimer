/************************************************************************
****	> File Name:    	cmemory.h
****	> Author:       	yiwen liu
****	> Mail:         	newiyuil@163.com
****	> Created Time: 	Sun 21 Jan 2018 10:47:16 PM CST
************************************************************************/

#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <string>
using namespace std;

class StrBlob;
class StrBlobPtr {
public:
    StrBlobPtr() : curr(0) {  }
    StrBlobPtr(StrBlob &a, size_t sz = 0);
    std::string& deref() const;
    StrBlobPtr& incr();
    bool curr_equal(StrBlobPtr &strbp) const;
    void getCurr() const {cout << curr << endl;}
private:
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};
std::shared_ptr<std::vector<std::string>>/*{{{*/
StrBlobPtr::check(std::size_t i, const std::string&) const {
    auto ret = wptr.lock();
    if (!ret) {
        throw std::runtime_error("unbound StrBlobStr");
    }
    if (i >= ret->size()) {
        throw std::out_of_range("msg");
    }
    return ret;
}

std::string& StrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
    check(curr, "increase pase end of StrBlobPtr");
    ++curr;
    return *this;
}
bool StrBlobPtr::curr_equal(StrBlobPtr &strbp) const {
    return strbp.curr == this->curr;
}
/*}}}*/

class StrBlob {
    friend class StrBlobPtr;
public:
    typedef std::vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    size_type size() const {return data->size();}
    bool empty() const { return data->empty(); }
    void push_back(const string &t) {data->push_back(t);}
    void pop_back();
    std::string &front();
    std::string &back();
    const std::string &front() const;
    const std::string &back() const;
    void disp_all_ele() const;
    StrBlobPtr begin() {return StrBlobPtr(*this);}
    StrBlobPtr end() {
        auto ret = StrBlobPtr(*this, data->size());
        return ret;
    }
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};
/*{{{*/
StrBlob::StrBlob(): data(make_shared<vector<string>>()) {};
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {};
void StrBlob::check(size_type i, const string &msg) const {
    if (i > data->size()) {
        throw out_of_range(msg);
    }
}
void StrBlob::disp_all_ele() const {
    for (auto i : *this->data) {
        cout << i << ' ';
    }
    cout << endl;
}
const string& StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();    
}
const std::string& StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}
string &StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}
string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}/*}}}*/

/*
 *why
 */
StrBlobPtr::StrBlobPtr(StrBlob &a, size_t sz) : wptr(a.data), curr(sz) {  };






