#include "pch.h"
#include "game_validator.h"
#include "validation_handler_too_short.h"
#include "validation_handler_too_long.h"
#include "validation_handler_invalid_word.h"
#include "validation_handler_already_used_word.h"
#include "validation_handler_one_character_changed.h"

#include <exception>
#include <stdexcept>
#include <memory>
#include <iostream>

word_game::game_validator::game_validator(word_game::word_processor& word_processor, int word_length)
	: word_processor_(word_processor), word_length_(word_length)
{
	// Validate that all valid words are of requested length. 
	for (auto const& word: word_processor_.get_all_words())
	{
		if (word.size() != word_length_)
		{
			std::string error_message = "Invalid word [" + word + "].  Expected length was [" + std::to_string(word_length_) + "].";
			throw std::logic_error(error_message);
		}
	}

	used_words_ = std::vector<std::string>();

	validation_handler_ = new word_game::validation_handler;
	word_game::validation_handler_too_short* too_short_validation_handler = new word_game::validation_handler_too_short(word_length_);
	word_game::validation_handler_too_long* too_long_validation_handler = new word_game::validation_handler_too_long(word_length_);
	word_game::validation_handler_invalid_word* invalid_word_validation_handler = new word_game::validation_handler_invalid_word(word_processor_);
	word_game::validation_handler_already_used_word* already_used_word_validation_handler = new word_game::validation_handler_already_used_word(used_words_);
	word_game::validation_handler_one_character_changed* one_character_changed_validation_handler = new word_game::validation_handler_one_character_changed(used_words_);

	validation_handler_
		->set_next(too_short_validation_handler)
		->set_next(too_long_validation_handler)
		->set_next(invalid_word_validation_handler)
		->set_next(already_used_word_validation_handler)
		->set_next(one_character_changed_validation_handler);

	characters_ = "qwertyuiopasdfghjklzxcvbnm";
}

void word_game::game_validator::add_to_history(std::string word)
{
	used_words_.push_back(word);
}

bool word_game::game_validator::is_game_over()
{
	if (used_words_.size() == 0)
	{
		return false;
	}
	else
	{
		std::string last_word = used_words_.back();
		for (int i = 0; i < word_length_; i++)
		{
			for (char& character : characters_)
			{
				std::string new_word = last_word;
				new_word[i] = character;
				if (can_add(new_word) == CanAddResult::Yes)
				{
					return false;
				}
			}
		}
	}
	return true;
}

word_game::CanAddResult word_game::game_validator::can_add(std::string word)
{
	return (validation_handler_->validate(word));
}

std::vector<std::string> word_game::game_validator::get_hints()
{
	if (used_words_.size() == 0)
	{
		return word_processor_.get_all_words();
	}
	else
	{
		std::vector<std::string> hints;
		std::string last_word = used_words_.back();
		for (int i = 0; i < word_length_; i++)
		{
			for (char& character : characters_)
			{
				std::string new_word = last_word;
				new_word[i] = character;
				if (can_add(new_word) == CanAddResult::Yes)
				{
					hints.push_back(new_word);
				}
			}
		}
		return hints;
	}
}