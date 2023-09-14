#include "fooString.h"
#include <cstring>
#include <iostream>
FooString::FooString(const char *tbuf){
    len = std::strlen(tbuf);
    std::cout << "constr " << len << '\n';
    buf = new char[len + 1];
    std::strcpy(buf, tbuf);
}

void FooString::release_memory(){
    delete[] buf;
    buf = nullptr;
}

FooString::~FooString(){
    release_memory();
}

int FooString::length() const{
    return len;
}

bool FooString::compare(const FooString& str) const{
    return compare(str.buf);
}

bool FooString::compare(const char *str) const{
    if(buf == str) return true;
    if(buf == nullptr || str == nullptr) return false;
    return (std::strcmp(buf, str) == 0); // strcmp(a, b) == 0 тогда и только тогда, когда a equals b
}

void FooString::add(const FooString& str){
    char* tmp_buf = new char[len + str.len + 1];
    if(buf != nullptr) std::strcpy(tmp_buf, buf);
    if(str.buf != nullptr) std::strcpy(tmp_buf + len, str.buf);
    release_memory();
    len += str.len;
    buf = tmp_buf;
}

void FooString::add(const char* str){
    add(FooString(str));
}

void FooString::show(std::ostream& os) const{
    char* curr_char = buf;
    for(int i = 0; i < len; ++i){
        os << *curr_char;
        ++curr_char;
    }
}
