#pragma once
#include "validation_handler.h"
#include <vector>
#include <string>
namespace word_game
{
	class validation_handler_one_character_changed:
		public validation_handler
	{
	public:
		validation_handler_one_character_changed(std::vector<std::string>& used_words) : used_words_(used_words) {}
		CanAddResult validate(std::string word) override;
	private: 
		std::vector<std::string>& used_words_;
	};
}


