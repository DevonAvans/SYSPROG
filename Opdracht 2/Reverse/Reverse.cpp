#include "Reverse.hpp"

#include <algorithm>

namespace sp
{
	class Reverse final : public ITextTransformer
	{
	public:
		[[nodiscard]] std::string get_name() const override;
		[[nodiscard]] std::string transform(std::string text) const override;
	};
}

std::string sp::Reverse::get_name() const
{
	return "Reverse";
}

std::string sp::Reverse::transform(std::string text) const
{
	std::reverse(text.begin(), text.end());
	return text;
}

sp::ITextTransformer* create_instance()
{
	return new sp::Reverse();
}
