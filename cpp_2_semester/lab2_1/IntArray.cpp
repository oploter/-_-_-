#include <iostream>
#include <exception>
#include <sstream>
#include "IntArray.h"
namespace array {
	IntArray::IntArray(int size_m) {
		if (size_m < 0) {
			throw std::logic_error("Cannot create array of negative length");
		}
		this->size_m = size_m;
		capacity_m = size_m * 2 + 1;
		data_m = new int[capacity_m] {0};
	}

	IntArray::IntArray(const IntArray& other) : size_m(other.size_m), capacity_m(other.capacity_m) {
		data_m = new int[capacity_m];
		if (size_m > 0) {
			std::copy(other.data_m, other.data_m + other.capacity_m, data_m);
		}
	}

	void IntArray::set(int index, int new_val) {
		if (!checkIndex(index)) {
			throw std::out_of_range("Index out of range");
		}
		if (new_val < -100 || 100 < new_val) {
			throw std::invalid_argument("Value is not in [-100, 100]");
		}
		data_m[index] = new_val;
	}

	int IntArray::get(int index) const {
		if (!checkIndex(index)) {
			throw std::out_of_range("Index out of range");
		}
		return data_m[index];
	}

	IntArray::~IntArray() {
		delete[] data_m;
	}

	int IntArray::size() const {
		return size_m;
	}

	void IntArray::print(std::ostream& os) const {
		os << "{";
		for (int i = 0; i < size_m - 1; ++i) {
			os << data_m[i] << ", ";
		}
		if (size_m > 0) {
			os << data_m[size_m - 1];
		}
		os << "}\n";
	}

	bool IntArray::checkIndex(int index) const {
		return (0 <= index && index < size_m);
	}

	void IntArray::push_back(int val) {
		if (val < -100 || 100 < val) {
			throw std::invalid_argument("Value is not in [-100, 100]");
		}
		if (size_m * 2 >= capacity_m) {
			capacity_m = (capacity_m == 0 ? 1 : 2 * capacity_m);
			int* tmp_data = data_m;
			data_m = new int[capacity_m] {0};
			if (tmp_data != nullptr) {
				std::copy(tmp_data, tmp_data + size_m, data_m);
				delete[] tmp_data;
			}
		}
		data_m[size_m] = val;
		++size_m;
	}

}
int main() {
	std::stringstream test_ss{};
	{ // Test1
		std::cout << "Test1: ";
		try {
			array::IntArray arr(10);
			arr.set(1, 2);
			std::cout << arr.get(3) << '\n';
			std::cout << "PASS\n";
		}
		catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << '\n';
			std::cout << "FAIL\n";
		}
		
	}
	{ // Test2: Creating array works
		std::cout << "Test2: ";
		array::IntArray arr = array::IntArray(4);
		arr.print(test_ss);
		if (test_ss.str() == "{0, 0, 0, 0}\n") {
			std::cout << "PASS\n";
		}
		else {
			std::cout << "FAIL\n";
		}
		test_ss.str("");
	}
	{ // Test3: Print array of size_m 1 is ok
		std::cout << "Test3: ";
		array::IntArray arr(1);
		arr.set(0, 12);
		arr.print(test_ss);
		if (test_ss.str() == "{12}\n") {
			std::cout << "PASS\n";
		}
		else {
			std::cout << "FAIL\n";
		}
		
	}
	{ // Test4 : get works, if index in [0, size_m)
		std::cout << "Test4: ";
		array::IntArray arr(10);
		arr.set(1, 10);
		std::cout << (arr.get(1) == 10) << '\n';
		if (arr.get(1) == 10) {
			std::cout << "PASS\n";
		}
		else {
			std::cout << "FAIL\n";
		}
		
	}
	{ // Test5: out-of-bounds get throws error
		std::cout << "Test5: ";
		int cnt_excpts = 0;
		array::IntArray arr(10);
		try {
			std::cout << arr.get(-1) << '\n';
			
		}
		catch (const std::exception& e) {
			++cnt_excpts;
			std::cerr << e.what() << '\n';
		}
		try {
			std::cout << arr.get(2000) << '\n';

		}
		catch (const std::exception& e) {
			++cnt_excpts;
			std::cerr << e.what() << '\n';
		}
		if (cnt_excpts == 2) {
			std::cout << "PASS\n";
		}
		else {
			std::cout << "FAIL\n";
		}
	}
	{ // Test6: out-of-bounds set throws error
		std::cout << "Test6: ";
		int cnt_excpts = 0;
		array::IntArray arr(10);
		try {
			arr.set(-1, 102);
		}
		catch (const std::exception& e) {
			++cnt_excpts;
			std::cerr << e.what() << '\n';
		}
		try {
			arr.set(203, 102);
		}
		catch (const std::exception& e) {
			++cnt_excpts;
			std::cerr << e.what() << '\n';
		}
		if (cnt_excpts == 2) {
			std::cout << "PASS\n";
		}
		else {
			std::cout << "FAIL\n";
		}	
	}
	{ // Test7: cannot create array with negative size_m
		std::cout << "Test7: ";
		try {
			array::IntArray arr(-1);
			std::cout << "FAIL\n";
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			std::cout << "PASS\n";
		}
	}
	{ // Test8: if setting value out of [-100, 100], exception is thrown
		std::cout << "Test8: ";
		array::IntArray arr(4);
		try {
			arr.set(2, 300);
			std::cout << "FAIL\n";
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			std::cout << "PASS\n";
		}
	}
	{ // Test9: set works
		std::cout << "Test9: ";
		array::IntArray arr(4);
		arr.set(2, 99);
		if (arr.get(2) != 99) {
			std::cout << "FAIL\n";
		}
		else {
			std::cout << "PASS\n";
		}
	}
	{ // Test10: copy constructor works
		std::cout << "Test10: ";
		array::IntArray arr1(4);
		arr1.set(2, 23);
		array::IntArray arr2 = arr1;
		arr1.set(2, 12);
		if (arr2.size() != arr1.size() || arr2.get(2) != 23) {
			std::cout << "FAIL\n";
		}
		else {
			std::cout << "PASS\n";
		}
	}
	{ //Test11: push_back works
		array::IntArray arr(0);
		try {
			for (int i = 3; i < 20; ++i) {
				arr.push_back(i);
				arr.print();
			}
		}
		catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << '\n';
		}
		array::IntArray arr2(2);
		try {

		}
		catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << '\n';
		}
	}
	return 0;
}