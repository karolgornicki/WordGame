#pragma once

#include <string>

#include "validation_statuses.h"

namespace word_game
{
	class validation_handler
	{
	private:
		validation_handler* next_handeler_;
	public:
		validation_handler() : next_handeler_(nullptr) {}
		virtual CanAddResult validate(std::string word);
		virtual validation_handler* set_next(validation_handler* handler);
	};
}


