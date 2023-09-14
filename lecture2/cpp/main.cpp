#include "doctest.h"
#include "fooString.h"
#include <string>
#include <sstream>

bool checkFooString(const FooString& str, const std::string& checkStr){
    std::stringstream ss;
    str.show(ss);
    return ss.str() == checkStr;
}

TEST_CASE("FooString constructor works"){
    FooString str(std::string("Hello").c_str());
    CHECK(checkFooString(str, "Hello"));
    CHECK(str.length() == 5);
}

TEST_CASE("Constructor, show() and length() work correctly on empty string"){
    FooString str;
    CHECK(checkFooString(str, ""));
    CHECK(str.length() == 0);
}

TEST_CASE("compare() returns false on different strings"){
    FooString str1(std::string("Hello").c_str());
    FooString str2(std::string("Buy").c_str());
    CHECK(str1.compare(str2) == false);
    CHECK(str2.compare(str1) == false);
}

TEST_CASE("compare() returns true on same strings"){
    FooString str1(std::string("Hello").c_str());
    FooString str2(std::string("Hello").c_str());
    CHECK(str1.compare(str2) == true);
    CHECK(str2.compare(str1) == true);
}


TEST_CASE("compare() returns true on empty strings"){
    FooString str1;
    FooString str2;
    CHECK(str1.compare(str2) == true);
    CHECK(str2.compare(str1) == true);
}

TEST_CASE("compare() called on the same object returns true"){
    FooString str1(std::string("Hello").c_str());
    CHECK(str1.compare(str1) == true);
}

TEST_CASE("compare() works, if one of the strings is empty"){
    FooString str1;
    FooString str2(std::string("Hello").c_str());
    CHECK(str1.compare(str2) == false);
    CHECK(str2.compare(str1) == false);
}

TEST_CASE("add() works correctly (char*)"){
    FooString str1(std::string("Hello").c_str());
    str1.add(std::string("Buy").c_str());
    CHECK(str1.compare(std::string("HelloBuy").c_str()));
}

TEST_CASE("add() works correctly, if adding empty string (char*)"){
    FooString str1(std::string("Hello").c_str());
    str1.add(std::string("a").c_str());
    CHECK(str1.compare(std::string("Helloa").c_str()));
}
  
TEST_CASE("add() works correctly, if adding to empty string (char*)"){
    FooString str1;
    str1.add(std::string("Bye").c_str());
    CHECK(str1.compare(std::string("Bye").c_str()));
}

TEST_CASE("add() works correctly (FooString)"){
    FooString str1(std::string("Hello").c_str());
    FooString str2(std::string("Bye").c_str());
    str1.add(str2);
    CHECK(str1.compare(std::string("HelloBye").c_str()));
    CHECK(str2.compare(std::string("Bye").c_str())); // checking, that str2 didn't change
}

TEST_CASE("add() works correctly, if adding to empty string (FooString)"){
    FooString str1;
    FooString str2(std::string("Bye").c_str());
    str1.add(str2);
    CHECK(str1.compare(std::string("Bye").c_str()));
    CHECK(str2.compare(std::string("Bye").c_str())); // checking, that str2 didn't change
}

