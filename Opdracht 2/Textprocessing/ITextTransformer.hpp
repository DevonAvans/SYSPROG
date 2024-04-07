#pragma once
#include <string>

namespace sp
{
	class ITextTransformer
	{
	public:
		virtual ~ITextTransformer() = default;
		virtual std::string get_name() const = 0;
		virtual std::string transform(std::string) const = 0;
	};
}
