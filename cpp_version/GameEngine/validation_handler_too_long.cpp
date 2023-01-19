#include "pch.h"
#include "validation_handler_too_long.h"

word_game::CanAddResult word_game::validation_handler_too_long::validate(std::string word)
{
	if (word.size() > word_length_)
	{
		return word_game::CanAddResult::NoTooLong;
	}

	return word_game::validation_handler::validate(word);
}