#pragma once

#include <string>

#include "validation_statuses.h"
#include "validation_handler.h"

namespace word_game
{
	class validation_handler_too_short :
		public validation_handler
	{
	public:
		validation_handler_too_short(int word_length):word_length_(word_length) {}
		CanAddResult validate(std::string word);
	private:
		int word_length_;
	};
}


