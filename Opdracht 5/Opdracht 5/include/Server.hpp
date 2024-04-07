#pragma once
#include <string>
#include <vector>


class Server
{
public:
	explicit Server(std::vector<std::string> list);
	void start(const std::string& ip, int port);
	void stop() const;

private:
	std::vector<std::string> list_;
	bool is_running;
};
