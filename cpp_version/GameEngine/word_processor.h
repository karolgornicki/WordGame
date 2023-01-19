#pragma once

#include <unordered_set>
#include <string>
#include <vector>

namespace word_game
{
	class word_processor
	{
	public:
		word_processor(std::string path_valid_words_file);
		bool is_valid_word(std::string word);
		std::vector<std::string> get_all_words();
	private:
		std::unordered_set<std::string> valid_words_;
	};
	std::unordered_set<std::string> read_word_file(std::string path);
	
}


