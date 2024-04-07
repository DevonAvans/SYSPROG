#pragma once
#include "../Textprocessing/ITextTransformer.hpp"

extern "C" {
__declspec(dllexport) sp::ITextTransformer* create_instance();
}
