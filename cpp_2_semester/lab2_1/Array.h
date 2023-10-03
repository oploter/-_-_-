#ifndef MyArray_H
#define MyArray_H
#include <exception>
#include <stdexcept>
#include <cmath>
#include <iostream>

namespace array {
template<typename T>
struct MyArray {
private:
    T* data_m = nullptr;
    int size_m = 0;
    bool check_index(int index) const;
    void release_memory();
    void set_private(int index, const T& val, std::true_type);
    void set_private(int index, const T& val, std::false_type);
    double dist_private(const MyArray<T>& other, std::true_type) const ;
    double dist_private(const MyArray<T>& other, std::false_type) const ;
    void push_back_private(const T& val, std::true_type);
    void push_back_private(const T& val, std::false_type);
public:
    MyArray();
    ~MyArray();
    MyArray(int size);
    int size() const;
    MyArray(const MyArray<T>& other);
    MyArray& operator=(const MyArray<T>& other);
    const T& get(int index) const;
    T& get(int index);
    void print(std::ostream& os = std::cout) const;
    void set(int index, const T& val);
    void push_back(const T& val);
    double dist(const MyArray<T>& other) const;
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const MyArray<U>& arr);
    
};


/*
 For integral:
 print
 set
 push_back
 */

// CONSTRUCTOR, DESTRUCTOR, OPERATOR=
template<typename T>
MyArray<T>::MyArray() : MyArray(0) {}

template<typename T>
MyArray<T>::MyArray(int sz) {
    if (sz < 0) throw std::logic_error("Cannot create array of negative length");
    size_m = sz;
    if(sz > 0){
        data_m = new T[size_m]{};
    }
}

template<typename T>
MyArray<T>::MyArray(const MyArray<T>& other) : size_m(other.size_m) {
    data_m = new T[size_m]{};
    if (size_m > 0) {
        std::copy(other.data_m, other.data_m + other.size_m, data_m);
    }
}

template<typename T>
void MyArray<T>::release_memory(){
    if (data_m != nullptr) {
        delete[] data_m;
        data_m = nullptr;
    }
}

template<typename T>
MyArray<T>::~MyArray() {
    release_memory();
}

template<typename T>
MyArray<T>& MyArray<T>::operator=(const MyArray<T>& other) {
    if(this == &other){
        return *this;
    }
    release_memory();
    size_m = other.size_m;
    data_m = new T[size_m]{};
    std::copy(other.data_m, other.data_m + other.size_m, data_m);
    return *this;
}
//

// SET,USH_BACK, GET
template<typename T>
void MyArray<T>::set(int index, const T& val){
    set_private(index, val, std::is_integral<T>());
}


template<typename T>
void MyArray<T>::set_private(int index, const T& val, std::false_type) {
    if (!check_index(index)) {
        throw std::out_of_range("Index out of range");
    }
    data_m[index] = val;
}

template<typename T>
void MyArray<T>::set_private(int index, const T& val, std::true_type) {
    if (!check_index(index)) {
        throw std::out_of_range("Index out of range");
    }
    if (val < -100 || 100 < val) {
        throw std::invalid_argument("Value is not in [-100, 100]");
    }
    data_m[index] = val;
}

template<typename T>
const T& MyArray<T>::get(int index) const{
    if (!check_index(index)) {
        throw std::out_of_range("_index out of range");
    }
    return data_m[index];
}

template<typename T>
T& MyArray<T>::get(int index){
    if (!check_index(index)) {
        throw std::out_of_range("_index out of range");
    }
    return data_m[index];
}

template<typename T>
void MyArray<T>::push_back(const T& val) {
    push_back_private(val, std::is_integral<T>());
}

template<typename T>
void MyArray<T>::push_back_private(const T& val, std::true_type){
    if (val < -100 || 100 < val) {
        throw std::invalid_argument("Value is not in [-100, 100]");
    }
    int* tmp_data = data_m;
    data_m = new int[size_m + 1]{};
    if(tmp_data != nullptr){
        std::copy(tmp_data, tmp_data + size_m, data_m);
        delete[] tmp_data;
    }
    data_m[size_m] = val;
    ++size_m;
}

template<typename T>
void MyArray<T>::push_back_private(const T& val, std::false_type){
    T* tmp_data = data_m;
    data_m = new T[size_m + 1]{};
    if(tmp_data != nullptr){
        std::copy(tmp_data, tmp_data + size_m, data_m);
        delete[] tmp_data;
    }
    data_m[size_m] = val;
    ++size_m;
}

// SIZE, PRINT, <<, DIST
template<typename T>
int MyArray<T>::size() const {
    return size_m;
}

template<typename T>
void MyArray<T>::print(std::ostream& os) const {
    for (int i = 0; i < size_m - 1; ++i) {
        os << data_m[i] << ", ";
    }
    if (size_m > 0) {
        os << data_m[size_m - 1];
    }
    os << '\n';
}

template<>
void MyArray<int8_t>::print(std::ostream& os) const {
    for (int i = 0; i < size_m - 1; ++i) {
        os << (int)data_m[i] << " ";
    }
    if (size_m > 0) {
        os << (int)data_m[size_m - 1];
    }
    os << '\n';
}


template<typename T>
bool MyArray<T>::check_index(int index) const {
    return (0 <= index && index < size_m);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyArray<T>& arr){
    arr.print(os);
    return os;
}

template<typename T>
double MyArray<T>::dist(const MyArray<T>& other) const {
    return dist_private(other, std::is_integral<T>());
}

template<typename T>
double MyArray<T>::dist_private(const MyArray<T>&, std::false_type) const {
    throw std::bad_typeid();
}
template<typename T>
double MyArray<T>::dist_private(const MyArray<T>& other, std::true_type) const {
    if(size_m != other.size_m){
        throw std::invalid_argument("Distance can be calculated only for arrays with equal sizes");
    }
    double ans = 0;
    if(size_m == 0) return 0;
    //std::cout << "COUNTING DIST:\n";
    for(int i = 0; i <  size_m; ++i){
        ans += (data_m[i] - other.data_m[i]) * (data_m[i] - other.data_m[i]); // does not work for chars | overflow?
        //std::cout << ans << ' ';
    }
    //std::cout << "\nSQAURED " << ans << ' ' << std::sqrt(ans) << '\n';
    return std::sqrt(ans);
}




}// namespace array




/*
bool IntArray::check_index(int index) const {
    return (0 <= index && index < size_m);
}

void IntArray::push_back(int8_t val) {
    if (val < -100 || 100 < val) {
        throw std::invalid_argument("Value is not in [-100, 100]");
    }
    int8_t* tmp_data = data_m;
    data_m = new int8_t[size_m + 1];
    if(tmp_data != nullptr){
        std::copy(tmp_data, tmp_data + size_m, data_m);
        delete[] tmp_data;
    }
    data_m[size_m] = val;
    ++size_m;
}

void IntArray::add(const IntArray& other){
    for(int i = 0; i < std::min(size_m, other.size()); ++i){
        data_m[i] += other.data_m[i];
    }
}

void IntArray::subtrc(const IntArray& other){
    for(int i = 0; i < std::min(size_m, other.size()); ++i){
        data_m[i] -= other.get(i);
    }
}
 */


#endif
