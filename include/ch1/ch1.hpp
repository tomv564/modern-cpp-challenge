#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <string>
#include <istream>
#include <optional>
#include <array>
#include <filesystem>
#include <string_view>
#include <queue>

unsigned int gcd(unsigned int a, unsigned int b);
unsigned int lcm(const int a, const int b);
std::string to_roman(const int a);
bool is_valid_isbn10(std::string_view isbn);


// TODO: const, constexpr, copy ctors, noexcept, explicit ctor for ulong?
// switch to uint64_t
// To know:
// constexpr effect
// effect of missing equality and copy ctor (shallow copy is fine?)
// value semantics vs using c array (no pointers, can be copied?)



class IPV4Address {
public:
	IPV4Address() :  m_value{0}  {};
	IPV4Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d) : m_value{a, b, c, d} {};

	// explicit to not allow accidental conversions from non-longs
	explicit IPV4Address(unsigned long a) : m_value {
		static_cast<unsigned char>((a >> 24) & 0xFF),
		static_cast<unsigned char>((a >> 16) & 0xFF),
		static_cast<unsigned char>((a >> 8) & 0xFF),
		static_cast<unsigned char>((a) & 0xFF)
	} {}; // shift bits right, and strip 3 last bytes off.

	[[nodiscard]] std::string to_string() const;
	[[nodiscard]] unsigned long to_ulong() const;

	friend std::istream& operator>>(std::istream& input, IPV4Address& addr);
	friend std::ostream& operator<<(std::ostream& output, const IPV4Address& addr);

	friend bool operator<(const IPV4Address& a, const IPV4Address& b) {
	    return a.to_ulong() < b.to_ulong();
	};
	friend bool operator>(const IPV4Address& a, const IPV4Address& b) {
		return b < a;
	};

	friend bool operator==(const IPV4Address& a, const IPV4Address& b) {
		return a.m_value == b.m_value;
	};
	friend bool operator!=(const IPV4Address& a, const IPV4Address& b) {
		return !(a == b);
	};

	friend bool operator<=(const IPV4Address& a, const IPV4Address& b) {
		return b > a;
	};
	friend bool operator>=(const IPV4Address& a, const IPV4Address& b) {
		return b < a;
	};

	friend IPV4Address& operator++(IPV4Address& a);
	friend IPV4Address operator++(IPV4Address& a, int);
private:
	std::array<unsigned char, 4> m_value;
};

template<typename T, size_t R, size_t C>
class array2d {

	std::vector<T> m_items;
public:
	array2d() : m_items(R*C) {};
	array2d(std::initializer_list<T> list) : m_items(list) {}

	// accessors
	T& at(const size_t r, const size_t c) { return m_items.at(r*C + c); }
	const T& at(const size_t r, const size_t c) const { return m_items.at(r*C + c); }
	T& operator() (const size_t r, const size_t c) { return m_items[r*C + c]; }
	const T& operator() (const size_t r, const size_t c) const { return m_items[r*C + c]; }
	T* data() { return m_items.data(); }
	const T* data() const { return m_items.data(); }

	void fill(const T& val) { std::fill(m_items.begin(), m_items.end(), val); }
	void swap(array2d& other) { m_items.swap(other.m_items); }

	bool empty() { return R == 0 || C == 0; }
	size_t size(int rank) {
		if (rank == 1) { return R; }
		if (rank == 2) { return C; }
		throw std::out_of_range("Rank is out of range!");
	}

	auto begin() { return m_items.begin(); }
	auto end() { return m_items.end(); }
	auto cbegin() { return m_items.cbegin(); }
	auto cend() { return m_items.cend(); }
};

template<typename T>
T minimum(T a) {
	return a;
}

template<typename T, typename... Args>
T minimum(T a, Args... args) {
	if (a < minimum(args...)) {
		return a;
	}
	return minimum(args...);
}


template<typename C, typename T>
bool contains_any(C c, T a)
{
	return std::find(c.begin(), c.end(), a) != c.end();
}

template<typename C, typename T, typename... Args>
bool contains_any(C c, T a, Args... args)
{
	if (contains_any(c, a)) {
		return true;
	} else {
		return contains_any(c, args...);
	}
}

template<typename C, typename T>
bool contains_all(C c, T a)
{
	return std::find(c.begin(), c.end(), a) != c.end();
}

template<typename C, typename T, typename... Args>
bool contains_all(C c, T a, Args... args)
{
	if (!contains_all(c, a)) {
		return false;
	} else {
		return contains_all(c, args...);
	}
}

template<typename C, typename T>
bool contains_none(C c, T a) {
	return !contains_any(c, a);
}

template<typename C, typename T, typename... Args>
bool contains_none(C c, T a, Args... args)
{
	return !contains_any(c, a, args...);
}

std::string capitalize(const std::string_view str);

bool validate_license_plate(std::string_view str);

class Logger
{
	std::filesystem::path m_path;
	std::ofstream m_stream;
public:
	Logger();
	~Logger();
	void archive(std::filesystem::path path);
	friend Logger& operator<<(Logger& logger, std::string_view message);
};

/**
 * Can be implemented using tree (eg. red-black) but binary heap has better cache locality due to use of arrays.
 */
template<typename T>
class priority_queue
{
	std::vector<T> m_items;
public:
	priority_queue() { std::make_heap(m_items.begin(), m_items.end()); };
	void push(T e) {
		m_items.push_back(e);
		std::push_heap(m_items.begin(), m_items.end());
	}; // logarithmic time (better than linear) - binary search on sorted array, or a tree.
	T pop() {
		std::pop_heap(m_items.begin(), m_items.end());
		auto top = m_items.back();
		m_items.pop_back();
		return top;
		// return m_items.re(m_items.size() -1);
	}; // constant-time
	T top() {
		return m_items.at(0);
	}; // constant-time
	[[nodiscard]] bool empty() const { return m_items.empty(); }
	[[nodiscard]] size_t size() const { return m_items.size(); }
};

