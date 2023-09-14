#ifndef FooString_H
#define FooString_H
#include <iostream>
class FooString{
    char* buf;
    int len;
    void release_memory();
public:
    FooString() : buf(nullptr), len(0){}
    FooString(const char *tbuf);
    ~FooString();
    void show(std::ostream& os = std::cout) const;
    int length() const;
    bool compare(const FooString& str) const;
    bool compare(const char *str) const;
    void add(const FooString& str);
    void add(const char* str);
};
#endif
