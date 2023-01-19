#pragma once
#include "validation_statuses.h"
#include "validation_handler.h"
#include "word_processor.h"
#include <unordered_set>
namespace word_game
{
	class validation_handler_invalid_word:
		public validation_handler
	{
	public:
		validation_handler_invalid_word(word_game::word_processor word_processor): word_processor_(word_processor) {}
		CanAddResult validate(std::string word) override;
	private:
		word_game::word_processor word_processor_;
	};
}


