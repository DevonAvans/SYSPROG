#include "split-join.hpp"

#include <sstream>

std::vector<std::string> sp::split(const std::string& str,
                                   const std::string& sep)
{
	std::vector<std::string> result;

	size_t next, last = 0;

	while ((next = str.find(sep, last)) != std::string::npos)
	{
		result.push_back(str.substr(last, next - last));
		last = next + 1;
	}

	result.push_back(str.substr(last));

	return result;
}

std::vector<std::string> sp::split(const std::string& str,
                                   const std::regex& sep)
{
	std::vector<std::string> result;

	std::sregex_token_iterator iterator(str.begin(),
	                                    str.end(),
	                                    sep,
	                                    -1);

	for (const std::sregex_token_iterator end; iterator != end; ++iterator)
	{
		result.push_back(*iterator);
	}

	return result;
}

std::string sp::join(const std::vector<std::string>& components,
                     const std::string& join)
{
	if (join.empty())
	{
		throw std::invalid_argument("Join string mag niet leeg zijn");
	}

	std::ostringstream imploded;

	std::ranges::copy(components,
	                  std::ostream_iterator<std::string>(
		                  imploded,
		                  join.c_str()));

	return imploded.str();
}
