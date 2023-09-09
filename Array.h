#ifndef MyArray_H
#define MyArray_H
#include <iosfwd>
#include <exception>
#include <stdexcept>

namespace array {
	template<typename T>
	struct MyArray {
	private:
		T* data_m = nullptr;
		int size_m = 0;
		int capacity_m = 0;
		bool checkIndex(int index) const;
	public:
		MyArray();
		~MyArray();
		MyArray(int size);
		int size() const;
		MyArray(const MyArray<T>& other);
		MyArray& operator=(const MyArray<T>& other);
		T get(int index) const;
		void print(std::ostream& os = std::cout) const;
		void set(int index, T val);
		void push_back(T val);
		friend std::ostream& operator<<(std::ostream& os, const MyArray& arr);
	};

	template<typename T>
	MyArray<T>::MyArray() : MyArray(0) {}

	template<typename T>
	MyArray<T>::MyArray(int size_m) {
		if (size_m < 0) {
			throw std::logic_error("Cannot create array of negative length");
		}
		this->size_m = size_m;
		capacity_m = size_m * 2;
		data_m = new T[capacity_m];
	}

	template<typename T>
	MyArray<T>::MyArray(const MyArray<T>& other) : size_m(other.size_m),
		capacity_m(other.capacity_m) {
		data_m = new T[capacity_m];
		if (size_m > 0) {
			std::copy(other.data_m, other.data_m + other.capacity_m, data_m);
		}
	}

	template<typename T>
	void MyArray<T>::set(int index, T val) {
		if (!checkIndex(index)) {
			throw std::out_of_range("Index out of range");
		}
		data_m[index] = new_val;
	}

	template<>
	void MyArray<int>::set(int index, int val) {
		if (!checkIndex(index)) {
			throw std::out_of_range("Index out of range");
		}
		if (val < -100 || 100 < val) {
			throw std::invalid_argument("Value is not in [-100, 100]");
		}
		data_m[index] = val;
	}

	template<typename T>
	T MyArray<T>::get(int index) const {
		if (!checkIndex(index)) {
			throw std::out_of_range("Index out of range");
		}
		return data_m[index];
	}

	template<typename T>
	int MyArray<T>::size() const {
		return size_m;
	}
	template<typename T>
	MyArray<T>::~MyArray() {
		if (data_m != nullptr) {
			delete[] data_m;
			data_m = nullptr;
		}
	}

	template<typename T>
	void MyArray<T>::print(std::ostream& os) const {
		os << "{";
		for (int i = 0; i < size_m - 1; ++i) {
			os << data_m[i] << ", ";
		}
		if (size_m > 0) {
			os << data_m[size_m - 1];
		}
		os << "}\n";
	}

	template<typename T>
	void MyArray<T>::push_back(T val) {
		if (size_m * 2 >= capacity_m) {
			capacity_m = (capacity_m == 0 ? 1 : 2 * capacity_m);
			T* tmp_data = data_m;
			data_m = new T[capacity_m] {0};
			if (tmp_data != nullptr) {
				std::copy(tmp_data, tmp_data + size_m, data_m);
				delete[] tmp_data;
			}
		}
		data_m[size_m] = val;
		++size_m;
	}

	template<typename T>
	bool MyArray<T>::checkIndex(int index) const {
		return (0 <= index && index < size_m);
	}

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const MyArray<T>& arr) {
		arr.print(os);
		return os;
	}

	template<typename T>
	MyArray<T>& MyArray<T>::operator=(const MyArray<T>& other) {
		if (data_m != nullptr) {
			delete[] data_m;
			data_m = nullptr;
		}
		size_m = other.size_m;
		capacity_m = 2 * size_m;
		data_m = new T[capacity_m];
		std::copy(other.data_m, other.data_m + other.size_m, data_m);
	}

}// namespace array



#endif
