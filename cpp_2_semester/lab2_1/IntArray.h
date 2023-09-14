#ifndef Array_H
#define Array_H
namespace array {
	struct IntArray {
	private:
		int* data_m = nullptr;
		int size_m = 0;
		int capacity_m = 0;
		bool checkIndex(int index) const;
	public:
		IntArray(int size);
		IntArray(const IntArray& other);
		~IntArray();
		void set(int index, int new_val);
		int get(int index) const;
		void print(std::ostream& os = std::cout) const;
		int size() const;
		void push_back(int val);
	};
}
#endif