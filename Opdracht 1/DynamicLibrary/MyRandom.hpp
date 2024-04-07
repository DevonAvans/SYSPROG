#pragma once
#include <random>

#ifdef _WIN32
#	ifdef MAKEDLL
#		define EXPORT __declspec(dllexport)
#	else
#		define EXPORT __declspec(dllimport)
#	endif
#else
#	define EXPORT
#endif

namespace sysprog
{
	class MyRandom
	{
	public:
		EXPORT static MyRandom& get_instance()
		{
			return instance_;
		}

		MyRandom(const MyRandom&) = delete;
		MyRandom(MyRandom&&) = delete;
		MyRandom& operator=(const MyRandom&) = delete;
		MyRandom& operator=(MyRandom&&) = delete;
		~MyRandom() = default;

		EXPORT int get_int(int from, int to);
		EXPORT double get_double(double from, double to);
		EXPORT double get_double_between_zero_and_one();
		EXPORT bool get_bool();

		template <typename T>
		T get_item(std::vector<T> elements)
		{
			const auto size = get_int(0, elements.size() - 1);
			return elements[size];
		}


	private:
		static MyRandom instance_;

		std::default_random_engine engine_;

		MyRandom();
	};
}
