#include "catch.hpp"
#include "word_processor.h"
#include <string>
#include <algorithm>

TEST_CASE("read_word_file: Arrange: Read test file Assert: generated set with 3 entries")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";

	// Act:
	std::unordered_set<std::string> words = word_game::read_word_file(path_test_file);

	// Assert: 
	REQUIRE(words.size() == 3);
}

TEST_CASE("read_word_file | Read test file | Expect to find words aahs aals abas")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";

	// Act:
	std::unordered_set<std::string> words = word_game::read_word_file(path_test_file);

	// Assert: 
	REQUIRE(words.find("aahs") != words.end());
	REQUIRE(words.find("aals") != words.end());
	REQUIRE(words.find("abas") != words.end());
}

TEST_CASE("read_word_file | Read test file | Expect not to find words aaaa bbbb")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";

	// Act:
	std::unordered_set<std::string> words = word_game::read_word_file(path_test_file);

	// Assert: 
	REQUIRE(words.find("aaaa") == words.end());
	REQUIRE(words.find("bbbb") == words.end());
}

TEST_CASE("word_processor::word_processor() | Path to test file | Initialised without exception")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";

	// Act: 
	REQUIRE_NOTHROW(word_game::word_processor::word_processor(path_test_file));
}

TEST_CASE("word_processor::is_valid_word | Path to test file | Correctly returns true for words aahs, aals, abas")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";

	// Act: 
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	
	REQUIRE(word_processor.is_valid_word("aahs") == true);
	REQUIRE(word_processor.is_valid_word("aals") == true);
	REQUIRE(word_processor.is_valid_word("abas") == true);
}

TEST_CASE("word_processor::get_all_words | Path to test file | Returns a vector with aahs, aals, abas")
{
	//std::unordered_set<std::string>::const_iterator get_iterator()
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";

	// Act: 
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	std::vector<std::string> all_words = word_processor.get_all_words();

	// Assert: 
	std::sort(all_words.begin(), all_words.end());
	REQUIRE(all_words.at(0) == "aahs");
	REQUIRE(all_words.at(1) == "aals");
	REQUIRE(all_words.at(2) == "abas");
}

TEST_CASE("word_processor::is_valid_word | Path to test file | Correctly returns flase for words aaaa, bbbb")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";

	// Act: 
	auto word_processor = word_game::word_processor::word_processor(path_test_file);

	REQUIRE(word_processor.is_valid_word("aaaa") == false);
	REQUIRE(word_processor.is_valid_word("bbbb") == false);
}