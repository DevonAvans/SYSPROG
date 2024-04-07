#include "MyRandom.hpp"

#include <random>

sysprog::MyRandom sysprog::MyRandom::instance_;

sysprog::MyRandom::MyRandom()
{
	std::random_device device;
	engine_ = std::default_random_engine(device());
}

int sysprog::MyRandom::get_int(const int from, const int to)
{
	std::uniform_int_distribution dist{from, to};
	return dist(engine_);
}

double sysprog::MyRandom::get_double(const double from, const double to)
{
	std::uniform_real_distribution dist{from, to};
	return dist(engine_);
}

double sysprog::MyRandom::get_double_between_zero_and_one()
{
	return get_double(0, 1);
}

bool sysprog::MyRandom::get_bool()
{
	return get_int(0, 1) == 0;
}
