#include "pch.h"
#include "validation_handler_one_character_changed.h"

word_game::CanAddResult word_game::validation_handler_one_character_changed::validate(std::string word)
{
	if (used_words_.size() > 0)
	{
		std::string last_word = used_words_.back();
		int number_of_different_chars = 0;
		for (int i = 0; i < last_word.size(); i++)
		{
			if (last_word[i] != word[i])
			{
				number_of_different_chars++;
			}
		}

		if (number_of_different_chars != 1)
		{
			return CanAddResult::NoNotOneCharacterChanged;
		}
	}

	return word_game::validation_handler::validate(word);
}