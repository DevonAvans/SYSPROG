#include "PluginWrapper.hpp"

#include <stdexcept>
#include <sstream>
#include <windows.h>

sp::PluginWrapper::PluginWrapper(const std::string& path)
{
	plugin_ = LoadLibraryA(path.c_str());
	if (! plugin_)
	{
		std::ostringstream oss;
		oss << "plugin could not be opened, error " << GetLastError();
		throw std::runtime_error(oss.str());
	}
}

sp::PluginWrapper::~PluginWrapper()
{
	cleanup();
}

sp::PluginWrapper::PluginWrapper(PluginWrapper&& other) noexcept
{
	move(std::move(other));
}

sp::PluginWrapper& sp::PluginWrapper::operator=(PluginWrapper&& other) noexcept
{
	if (&other != this)
	{
		cleanup();
		move(std::move(other));
	}
	return *this;
}

void* sp::PluginWrapper::lookup(const std::string& symbol) const
{
	void* result = GetProcAddress(static_cast<HMODULE>(plugin_), symbol.c_str());
	if (!result)
	{
		std::ostringstream oss;
		oss << "symbol '" << symbol << "' could not be found, error " << GetLastError();
		throw std::runtime_error(oss.str());
	}
	return result;
}

void sp::PluginWrapper::cleanup() const
{
	if (plugin_)
	{
		FreeLibrary(static_cast<HMODULE>(plugin_));
	}
}

void sp::PluginWrapper::move(PluginWrapper&& other)
{
	plugin_ = other.plugin_;
	other.plugin_ = nullptr;
}
