#include "pch.h"
#include "word_processor.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

std::unordered_set<std::string> word_game::read_word_file(std::string path)
{
	std::unordered_set<std::string> set = std::unordered_set<std::string>();

	std::ifstream input_file = std::ifstream(path);
	std::string line;
	while (std::getline(input_file, line))
	{
		set.insert(line);
	}

	return set;
}

word_game::word_processor::word_processor(std::string path_to_file)
{
	valid_words_ = read_word_file(path_to_file);
}

bool word_game::word_processor::is_valid_word(std::string word)
{
	return valid_words_.find(word) != valid_words_.end();
}

std::vector<std::string> word_game::word_processor::get_all_words()
{
	std::vector<std::string> return_vector;
	return_vector.insert(return_vector.end(), valid_words_.begin(), valid_words_.end());
	return return_vector;
}