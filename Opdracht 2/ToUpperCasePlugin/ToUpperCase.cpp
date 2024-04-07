#include "ToUpperCase.hpp"

#include <algorithm>

namespace sp
{
	class ToUpperCase final : public ITextTransformer
	{
	public:
		[[nodiscard]] std::string get_name() const override;
		[[nodiscard]] std::string transform(std::string text) const override;
	};
}

std::string sp::ToUpperCase::get_name() const
{
	return "ToUpperCase";
}

std::string sp::ToUpperCase::transform(std::string text) const
{
	std::ranges::transform(text, text.begin(), ::toupper);
	return text;
}

sp::ITextTransformer* create_instance()
{
	return new sp::ToUpperCase();
}
