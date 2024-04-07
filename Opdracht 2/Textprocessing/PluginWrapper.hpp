#pragma once
#include <string>

namespace sp
{
	class PluginWrapper
	{
	public:
		explicit PluginWrapper(const std::string& path);
		~PluginWrapper();

		PluginWrapper(const PluginWrapper&) = delete;
		PluginWrapper& operator=(const PluginWrapper&) = delete;
		PluginWrapper(PluginWrapper&& other) noexcept;
		PluginWrapper& operator=(PluginWrapper&& other) noexcept;

		void* plugin() const { return plugin_; }
		void* lookup(const std::string& symbol) const;
		void hello();

	private:
		void* plugin_{nullptr};
		void cleanup() const;
		void move(PluginWrapper&& other);
	};
}
