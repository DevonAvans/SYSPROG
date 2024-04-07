#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

std::mutex mtx;

std::string read_from_file(const std::string& file_path)
{
	std::ifstream file;
	file.open(file_path, std::ios::in);
	std::string result;
	std::getline(file, result);
	file.close();
	return result;
}

void fun_stuff()
{
	std::unique_lock lock_one{mtx};

	std::cout << read_from_file("Alice_in_Wonderland.txt") << "\n";
	std::cout << read_from_file("Hallo.txt") << "\n";
}

int main()
{
	std::thread thread_one{fun_stuff};
	std::thread thread_two{fun_stuff};

	thread_one.join();
	thread_two.join();

	return 0;
}
