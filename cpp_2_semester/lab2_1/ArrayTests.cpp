 #include "doctest.h"
#include "Array.h"
#include <sstream>
#include <exception>
#include <vector>
#include <string>

/*
void func(){
    array::MyArray<int> arr(10);
    arr.set(1, 2);
    CHECK(arr.get(3) == 0);
    CHECK(arr.get(1) == 2);
}

TEST_CASE("constructor(), set(), get() work and do not throw any errors"){
    CHECK_NOTHROW(func());
}


TEST_CASE("print() array works"){
    std::stringstream test_ss{};
    array::MyArray<int> arr = array::MyArray<int>(4);
    arr.set(0, 2);
    arr.set(2, 32);
    arr.print(test_ss);
    CHECK(test_ss.str() == "2 0 32 0\n");
}

TEST_CASE("print() array with size=1 works"){
    std::stringstream test_ss{};
    array::MyArray<int> arr(1);
    arr.set(0, 12);
    arr.print(test_ss);
    CHECK(test_ss.str() == "12\n");
}


TEST_CASE("get() works, if index in [0, size_m)"){
    array::MyArray<int> arr(10);
    arr.set(1, 10);
    CHECK(arr.get(1) == 10);
    CHECK(arr.get(2) == 0);
}


TEST_CASE("If index out of bounds -> get() throws error"){
    array::MyArray<int> arr(10);
    CHECK_THROWS_AS(arr.get(-1), const std::out_of_range&);
    CHECK_THROWS_AS(arr.get(2000), const std::out_of_range&);
}


TEST_CASE("If index out of bounds -> set() throws error"){
    array::MyArray<int> arr(10);
    CHECK_THROWS_AS(arr.set(-1, 102), const std::out_of_range&);
    CHECK_THROWS_AS(arr.set(203, 102), const std::out_of_range&);
    CHECK_THROWS_AS(arr.set(200, 99), const std::out_of_range&);
    CHECK_THROWS_AS(arr.set(-2, 23), const std::out_of_range&);
}


TEST_CASE("Trying to create array of negative size throws error"){
    CHECK_THROWS_WITH(array::MyArray<int> arr(-1), "Cannot create array of negative length");
}


TEST_CASE("Setting value out of [-100, 100] throws error"){
    array::MyArray<int> arr(4);
    CHECK_THROWS_AS(arr.set(2, 123), std::invalid_argument);
}


TEST_CASE("set() works with correct value and index"){
    array::MyArray<int> arr(4);
    arr.set(2, 99);
    CHECK(arr.get(2) == 99);
}

TEST_CASE("Copy constructor works"){
    array::MyArray<int> arr1(4);
    arr1.set(2, 23);
    arr1.set(0, 21);
    arr1.set(3, -1);
    array::MyArray<int> arr2 = arr1;
    arr1.set(2, 12);
    CHECK(arr2.size() == arr1.size());
    CHECK(arr2.get(2) == 23);
    for(int i = 0; i < arr1.size(); ++i){
        if(i == 2) continue;
        CHECK(arr2.get(i) == arr1.get(i));
    }
}


template<typename T>
std::vector<T> arrToVec(const array::MyArray<T>& arr){
    std::vector<T> ans(arr.size());
    for(int i = 0; i < arr.size(); ++i){
        ans[i] = arr.get(i);
    }
    return ans;
}

TEST_CASE("push_back() works"){
    array::MyArray<int> arr(0);
    int cnt = 0;
    std::vector<int> checkArr;
    do{
        CHECK(arrToVec(arr) == checkArr);
        checkArr.push_back(cnt);
        arr.push_back(cnt);
        ++cnt;
    }while(cnt < 10);
}
 

TEST_CASE("String array "){
    array::MyArray<std::string> arr(10);
    arr.set(1, "Hello");
    arr.set(2, "Bye");
    std::stringstream ss;
    ss << arr;
    std::cout << "Str: \"" << ss.str() << "\"\n";
}

*/


using namespace array;

struct T{};
TEST_CASE("Array can be created with any type"){
    CHECK_NOTHROW(MyArray<std::string> arr{});
    CHECK_NOTHROW(MyArray<int> arr(32));
    CHECK_NOTHROW(MyArray<long long> arr(2));
    CHECK_NOTHROW(MyArray<T> arr(2));
}

// TEST FOR DISTANCE
bool closeDoubles(double l, double r){
    return std::abs(l - r) <= 1e-5;
}

template<typename T>
void fillArrayFromVector(MyArray<T>& arr, const std::vector<T>& vec){
    int i = 0;
    for(const T& val : vec){
        arr.set(i, val);
        ++i;
    }
}

TEST_CASE("Distance works correctly for integral types"){
    MyArray<char> a11(4);
    MyArray<char> a12(4);
    fillArrayFromVector<char>(a11, std::vector<char>{1, 2, 3, 5});
    fillArrayFromVector<char>(a12, std::vector<char>{2, 3, 1, 10});
    CHECK((closeDoubles(a11.dist(a12), a12.dist(a11)) && closeDoubles(a11.dist(a12), 5.56776436)));
    
    MyArray<short> a21(3);
    MyArray<short> a22(3);
    fillArrayFromVector<short>(a21, std::vector<short>{-1, 3, 0});
    fillArrayFromVector<short>(a22, std::vector<short>{100, 100, 100});
    CHECK((closeDoubles(a21.dist(a22), a22.dist(a21)) && closeDoubles(a21.dist(a22), 172.07556479)));

    
    MyArray<int> a31(5);
    MyArray<int> a32(5);
    fillArrayFromVector<int>(a31, std::vector<int>{1, 2, -10, -43, 2});
    fillArrayFromVector<int>(a32, std::vector<int>{2, 70, 1, 4, 2});
    CHECK((closeDoubles(a31.dist(a32), a32.dist(a31)) && closeDoubles(a31.dist(a32), 83.396642)));
    
    
    MyArray<long> a41(2);
    MyArray<long> a42(2);
    fillArrayFromVector<long>(a41, std::vector<long>{0, 12});
    fillArrayFromVector<long>(a42, std::vector<long>{11, 1});
    CHECK((closeDoubles(a41.dist(a42), a42.dist(a41)) && closeDoubles(a41.dist(a42), 15.556349)));
    
    
    MyArray<long long> a51(6);
    MyArray<long long> a52(6);
    fillArrayFromVector<long long>(a51, std::vector<long long>{1, 2, 3, 4, 5});
    fillArrayFromVector<long long>(a52, std::vector<long long>{2, 3, 1, 4, 2});
    CHECK((closeDoubles(a51.dist(a52), a52.dist(a51)) && closeDoubles(a51.dist(a52), 3.872983)));
    
}

TEST_CASE("Distance wokrs if length of arrays is 1 or 0"){
    MyArray<int> a1(1);
    MyArray<int> b1(1);
    a1.set(0, 10);
    b1.set(0, 1);
    CHECK((a1.dist(b1) == b1.dist(a1) && a1.dist(b1) == 9));
    
    MyArray<long long> a2(0);
    MyArray<long long> b2(0);
    CHECK((a2.dist(b2) == b2.dist(a2) && a2.dist(b2) == 0));
}

struct ObjWithIntCast{
    operator int() const{
        return 1;
    }
};

TEST_CASE("Distance throws error, if non-integral type"){
    MyArray<std::string> a0(0);
    MyArray<std::string> b0(0);
    CHECK_THROWS_AS(a0.dist(b0), const std::bad_typeid&);
    CHECK_THROWS_AS(b0.dist(a0), const std::bad_typeid&);
    
    MyArray<std::string> a1(1);
    MyArray<std::string> b1(1);
    CHECK_THROWS_AS(a1.dist(b1), const std::bad_typeid&);
    CHECK_THROWS_AS(b1.dist(a1), const std::bad_typeid&);

    MyArray<std::vector<int>> a2(2);
    MyArray<std::vector<int>> b2(2);
    CHECK_THROWS_AS(a2.dist(b2), const std::bad_typeid&);
    CHECK_THROWS_AS(b2.dist(a2), const std::bad_typeid&);
    
    MyArray<std::pair<long, long>> a3(3);
    MyArray<std::pair<long, long>> b3(3);
    CHECK_THROWS_AS(a3.dist(b3), const std::bad_typeid&);
    CHECK_THROWS_AS(b3.dist(a3), const std::bad_typeid&);
    
    MyArray<ObjWithIntCast> a4(4);
    MyArray<ObjWithIntCast> b4(4);
    CHECK_THROWS_AS(a4.dist(b4), const std::bad_typeid&);
    CHECK_THROWS_AS(b4.dist(a4), const std::bad_typeid&);
}

TEST_CASE("Distance throws error, if arrays are of different sizes"){
    MyArray<int> a1(23);
    MyArray<int> b1(1);
    CHECK_THROWS_AS(a1.dist(b1), const std::invalid_argument&);
    CHECK_THROWS_AS(b1.dist(a1), const std::invalid_argument&);
    
    MyArray<long long> a2;
    MyArray<long long> b2(1);
    CHECK_THROWS_AS(a2.dist(b2), const std::invalid_argument&);
    CHECK_THROWS_AS(b2.dist(a2), const std::invalid_argument&);
}

TEST_CASE("Distance gives 0 if array is created without initialization"){
    MyArray<int> a1(30);
    MyArray<int> b1(30);
    CHECK((closeDoubles(a1.dist(b1), b1.dist(a1)) && closeDoubles(a1.dist(b1), 0)));
    
    MyArray<long> a2;
    MyArray<long> b2;
    CHECK((closeDoubles(a2.dist(b2), b2.dist(a2)) && closeDoubles(a2.dist(b2), 0)));
}

// TESTS FOR SET

template<typename T>
void checkWithVector(const MyArray<T>& arr, const std::vector<T>& vec){
    for(std::size_t i = 0; i < vec.size(); ++i){
        CHECK(arr.get(i) == vec[i]);
    }
}

TEST_CASE("Set for integral values works, if value in [-100, 100]"){
    MyArray<char> a(2);
    a.set(1, 12);
    checkWithVector<char>(a, std::vector<char>{0, 12});
    
    MyArray<int> b(3);
    b.set(2, -99);
    b.set(1, 12);
    checkWithVector<int>(b, std::vector<int>{0, 12, -99});
    b.set(1, 0);
    checkWithVector<int>(b, std::vector<int>{0, 0, -99});
}

TEST_CASE("Set for integal values throw error, if value not in [-100, 100]"){
    MyArray<int> a(12);
    CHECK_THROWS_AS(a.set(0, -200), const std::invalid_argument&);
    CHECK_THROWS_AS(a.set(1, 101), const std::invalid_argument&);
    
    MyArray<long long> b(21);
    CHECK_THROWS_AS(b.set(1, -19999), const std::invalid_argument&);
    CHECK_THROWS_AS(b.set(2, 190), const std::invalid_argument&);
}

TEST_CASE("Set for non-integral types works without checking value"){
    MyArray<float> a1(4);
    CHECK_NOTHROW(a1.set(2, 1001.1));
    CHECK_NOTHROW(a1.set(0, -231));
    checkWithVector<float>(a1, std::vector<float>{-231, 0, 1001.1, 0});
    
    MyArray<std::string> a2(3);
    CHECK_NOTHROW(a2.set(0, "101"));
    CHECK_NOTHROW(a2.set(1, "-10101"));
    checkWithVector<std::string>(a2, std::vector<std::string>{"101", "-10101", ""});
}

TEST_CASE("push_back works"){
    MyArray<std::string> a1;
    std::vector<std::string> b1;
    for(int i = 0; i < 100; ++i){
        checkWithVector<std::string>(a1, b1);
        b1.push_back(std::to_string(i));
        a1.push_back(std::to_string(i));
    }
    checkWithVector<std::string>(a1, b1);
    
    MyArray<int> a2;
    std::vector<int> b2;
    for(int i = 0; i <= 100; ++i){
        checkWithVector<int>(a2, b2);
        b2.push_back(i);
        a2.push_back(i);
    }
    checkWithVector<int>(a2, b2);
}

TEST_CASE("push_back throws error, if integral value not in [-100, 100]"){
    MyArray<int> a1(2);
    CHECK_THROWS_AS(a1.push_back(-121), const std::invalid_argument&);
    CHECK_THROWS_AS(a1.push_back(101), const std::invalid_argument&);
    CHECK_NOTHROW(a1.push_back(10));
    checkWithVector(a1, std::vector<int>{0, 0, 10});
}

/*
template<typename T>
void foo(const std::vector<T> v){
    MyArray<T> arr;
    for(const T& val : v){
        arr.push_back(val);
    }
}

// TESTS FOR <<
TEST_CASE("<< works"){
    MyArray<std::string> a1(3);
    std
}
*/


/*
 struct temp{
 private:
 int b = -1;
 public:
 temp(int a) : b(a){}
 temp(){}
 };
 
 using namespace array;
 
 TEST_CASE("creating integral type"){
 MyArray<int> arr(10);
 arr.set(1, 20);
 
 MyArray<std::string> arr1(3);
 arr1.set(2, "Hello");
 std::cout << arr1 << '\n';
 
 MyArray<char> arr2(3);
 arr2.set(2, 10);
 std::cout << arr2 << '\n';
 
 MyArray<long long> arr3(3);
 arr3.set(2, 12);
 std::cout << arr3 << '\n';
 
 MyArray<temp> arr4(3);
 arr4.set(2, temp(2));
 //std::cout << arr3 << '\n';
 }
 */
