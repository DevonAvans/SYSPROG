#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>

#include "split-join.hpp"
#include "MyRandom.hpp"

std::vector<std::string> read_lines(const std::string& filename)
{
	std::ifstream ifs(filename);

	std::vector<std::string> lines;

	if (!ifs)
	{
		std::cerr << "Cannot open file: " << filename << std::endl;
	}
	else
	{
		for (std::string line; std::getline(ifs, line);)
		{
			lines.push_back(line);
		}
	}

	return lines;
}

int main()
{
	const std::vector<std::string> lines = read_lines("resources/Alice_in_Wonderland.txt");

	std::vector<std::string> random_lines;

	random_lines.reserve(10);

	for (int i = 0; i < 10; ++i)
	{
		const auto line = sysprog::MyRandom::get_instance().get_item(lines);
		random_lines.emplace_back(line);
	}

	const std::regex pat{R"([^a-zA-Z0-9]+)"};

	for (const auto line : random_lines)
	{
		std::cout << line << std::endl;
	}

	return 0;
}
