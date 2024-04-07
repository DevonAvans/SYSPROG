#include "../include/Server.hpp"

#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>

Server::Server(std::vector<std::string> list) : list_{std::move(list)}, is_running{false}
{
	WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != 0)
	{
		std::cerr << "WSAStartup failed: " << result << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Server::start(const std::string& ip, int port)
{
	std::cout << "Start server :) \n";
	SOCKADDR_IN address;
	int addrlen = sizeof(address);
	timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;

	SOCKET server_fd;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
		stop();
		exit(EXIT_FAILURE);
	}

	const int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&opt), sizeof(opt)) ==
		SOCKET_ERROR)
	{
		std::cerr << "setsockopt failed with error: " << WSAGetLastError() << std::endl;
		stop();
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ip.c_str());
	address.sin_port = htons(static_cast<u_short>(port));

	if (bind(server_fd, reinterpret_cast<SOCKADDR*>(&address), sizeof(ip)) == SOCKET_ERROR)
	{
		std::cerr << "bind failed with error: " << WSAGetLastError() << std::endl;
		stop();
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) == SOCKET_ERROR)
	{
		std::cerr << "listen failed with error: " << WSAGetLastError() << std::endl;
		stop();
		exit(EXIT_FAILURE);
	}

	is_running = true;
	std::cout << "[SERVER] Server started on " << ip << ":" << port << std::endl;
}

void Server::stop() const
{
}
