#include "pch.h"
#include "validation_handler_already_used_word.h"
#include <algorithm>

word_game::CanAddResult word_game::validation_handler_already_used_word::validate(std::string word)
{
	if (std::find(used_words_.begin(), used_words_.end(), word) != used_words_.end())
	{
		return CanAddResult::NoAlreadyUsedWord;
	}

	return word_game::validation_handler::validate(word);
}