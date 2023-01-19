#include "pch.h"
#include "validation_handler_invalid_word.h"

word_game::CanAddResult word_game::validation_handler_invalid_word::validate(std::string word)
{
	if (!word_processor_.is_valid_word(word))
	{
		return CanAddResult::NoInvalidWord;
	}

	return word_game::validation_handler::validate(word);
}