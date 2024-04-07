#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <memory>

#include "ITextTransformer.hpp"
#include "PluginWrapper.hpp"

std::vector<std::string> scan_dir(const std::string& path, const std::string& ext)
{
	std::vector<std::string> plugins;
	for (const auto& entry : std::filesystem::directory_iterator{path})
	{
		if (std::string filename{entry.path().string()}; filename.substr(filename.size() - ext.size(), ext.size()) ==
			ext)
		{
			plugins.push_back(filename);
		}
	}
	return plugins;
}

int main(int argc, char* argv[])
{
	try
	{
		// (1) scan directory for plugins
		const std::vector files{scan_dir("plugins", "plug")};
		// (2) open them
		std::vector<sp::PluginWrapper> plugins;
		for (const std::string& file : files)
		{
			plugins.emplace_back(file);
		}
		// (3) instantiate objects
		using factory = sp::ITextTransformer* (*)();
		std::vector<std::shared_ptr<sp::ITextTransformer>> objects;
		for (const sp::PluginWrapper& wrapper : plugins)
		{
			const auto str = "create_instance";
			const auto func = reinterpret_cast<factory>(wrapper.lookup(str));
			objects.emplace_back(func());
		}
		std::cout << "Choose the plugin by typing the name" << std::endl;
		// (4) call methods
		for (const auto& plug : objects)
		{
			std::cout << plug->get_name() << '\n';
		}

		std::string input;
		std::cin >> input;

		std::shared_ptr<sp::ITextTransformer> selected_plugin = nullptr;
		for (const auto& plug : objects)
		{
			if (plug->get_name() == input)
			{
				selected_plugin = plug;
				break;
			}
		}

		if (selected_plugin == nullptr)
		{
			std::cout << "Plugin not found!" << std::endl;
			exit(1);
		}

		std::cout << "Type something cool to transform you text!!!" << std::endl;

		std::string input_transform;
		std::cin >> input_transform;
		std::getline(std::cin, input_transform);
		std::cout << selected_plugin->transform(input_transform) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
