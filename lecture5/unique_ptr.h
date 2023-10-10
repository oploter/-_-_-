#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

template <typename T>
struct unique_ptr {
private:
    T *obj;

public:
    unique_ptr(const unique_ptr<T> &obj_) = delete;
    unique_ptr &operator=(const unique_ptr<T> &obj_) = delete;

    unique_ptr() : obj(nullptr) {
    }

    unique_ptr(std::nullptr_t) : obj(nullptr) {
    }

    unique_ptr(T *obj_) : obj(obj_) {
    }

    ~unique_ptr() {
        reset();
    }

    T *release() {
        return std::exchange(obj, nullptr);
    }

    void reset(T *x = nullptr) {
        if (obj != nullptr) {
            delete obj;
        }
        obj = x;
    }

    T *get() const {
        return obj;
    }

    T *operator->() const {
        return get();
    }

    T &operator*() const {
        return *obj;
    }

    explicit operator bool() const {
        return (obj != nullptr);
    }
};

#endif
