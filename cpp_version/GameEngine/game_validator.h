#pragma once
#include "validation_statuses.h"
#include "validation_handler.h"
#include "word_processor.h"
#include <vector>

namespace word_game
{
	class game_validator
	{
	public:
		game_validator(word_game::word_processor& word_processor, int word_length);
		CanAddResult can_add(std::string word);
		void add_to_history(std::string word);
		bool is_game_over();
		std::vector<std::string> get_hints();
	private:
		word_game::word_processor& word_processor_;
		int word_length_;
		word_game::validation_handler* validation_handler_;
		std::vector<std::string> used_words_;
		std::string characters_;
		//bool is_not_too_long(std::string word);
		//bool is_not_too_short(std::string word);
		//bool is_only_one_character_changed(std::string word);
		//bool is_not_yet_used(std::string word);
	};

	
}



