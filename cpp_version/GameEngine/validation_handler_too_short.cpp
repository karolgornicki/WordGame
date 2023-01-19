#include "pch.h"
#include "validation_handler_too_short.h"

word_game::CanAddResult word_game::validation_handler_too_short::validate(std::string word) 
{
	if (word.size() < word_length_)
	{
		return CanAddResult::NoTooShort;
	}

	return word_game::validation_handler::validate(word);
}