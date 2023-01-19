#pragma once

#include "validation_handler.h"

namespace word_game
{
	class validation_handler_too_long:
		public validation_handler
	{
	public:
		validation_handler_too_long(int word_length) : word_length_(word_length) {}
		CanAddResult validate(std::string word) override;
	private:
		int word_length_;
	};
}


