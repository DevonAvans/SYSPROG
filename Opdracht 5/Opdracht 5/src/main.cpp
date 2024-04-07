#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <WinSock2.h>

#include "../include/Server.hpp"

const std::string path = "resources/nl.words.txt";
const std::string ip = "127.0.0.1";
const int port = 3000;

std::vector<std::string> read_words(const std::string& path)
{
	std::vector<std::string> words;
	std::ifstream file(path);
	if (file.is_open())
	{
		std::string word;
		while (std::getline(file, word) && !word.empty())
		{
			words.push_back(word);
		}
		file.close();
	}
	return words;
}

int main()
{
	WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != 0)
	{
		std::cerr << "WSAStartup failed: " << result << std::endl;
		return EXIT_FAILURE;
	}

	const auto word_list = read_words(path);
	Server server(word_list);
	std::thread server_thread([&server]() { server.start(ip, port); });
	return 0;
}
