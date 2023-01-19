#include "catch.hpp"

#include "game_validator.h"

TEST_CASE("game_validator::game_validator | Path to test file and word_length = 4 | Successfully creates and object and does not throw")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);

	// Act & Assert:
	REQUIRE_NOTHROW(word_game::game_validator::game_validator(word_processor, word_length));
}

TEST_CASE("game_validator::game_validator | Path to test file and word_length = 5 | Throws because words in the file are 4 characters long and word_length is set to 5")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 5;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);

	// Act & Assert:
	REQUIRE_THROWS(word_game::game_validator::game_validator(word_processor, word_length));
}

TEST_CASE("game_validatior::can_add | word_length = 4, word =abc | Returns NoTooShort")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);

	// Act & Assert
	REQUIRE(game_validator.can_add("abc") == word_game::CanAddResult::NoTooShort);
}

TEST_CASE("game_validatior::can_add | word_length = 4, word =abcef | Returns NoTooLOng")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);

	// Act & Assert
	REQUIRE(game_validator.can_add("abcde") == word_game::CanAddResult::NoTooLong);
}

TEST_CASE("game_validatior::can_add | word_length = 4, word = abcd | Returns NoInvalidWord")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);

	// Act & Assert
	REQUIRE(game_validator.can_add("abcd") == word_game::CanAddResult::NoInvalidWord);
}

TEST_CASE("game_validatior::can_add | word_length = 4, word = aahs | Returns Yes")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);

	// Act & Assert
	REQUIRE(game_validator.can_add("aahs") == word_game::CanAddResult::Yes);
}

TEST_CASE("game_validatior::add_to_history | word_length = 4, word = aahs | Does not throw")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);

	// Act & Assert
	REQUIRE_NOTHROW(game_validator.add_to_history("aahs"));
}

TEST_CASE("game_validatior::can_add | word_length = 4, word = aahs (already added before) | Returns NoAlreadyUsedWord")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);
	game_validator.add_to_history("aahs");

	// Act & Assert
	REQUIRE(game_validator.can_add("aahs") == word_game::CanAddResult::NoAlreadyUsedWord);
}

TEST_CASE("game_validatior::can_add | word_length = 4, word = aahs --> abas  | Returns NoNotOneCharacterChanged")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);
	game_validator.add_to_history("aahs");

	// Act & Assert
	REQUIRE(game_validator.can_add("abas") == word_game::CanAddResult::NoNotOneCharacterChanged);
}

TEST_CASE("game_validatior::can_add | word_length = 4, word = aahs --> aals  | Returns Yes")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);
	game_validator.add_to_history("aahs");

	// Act & Assert
	REQUIRE(game_validator.can_add("aals") == word_game::CanAddResult::Yes);
}

TEST_CASE("game_validatior::is_game_over | word_length = 4, word = none were provided  | Returns false")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);

	// Act & Assert
	REQUIRE(game_validator.is_game_over() == false);
}

TEST_CASE("game_validatior::is_game_over | word_length = 4, word = aahs  | Returns false")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);
	game_validator.add_to_history("aahs");

	// Act & Assert
	REQUIRE(game_validator.is_game_over() == false);
}

TEST_CASE("game_validatior::is_game_over | word_length = 4, word = aahs,aals, valid_words = first 3 | Returns true")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);
	game_validator.add_to_history("aahs");
	game_validator.add_to_history("aals");

	// Act & Assert
	REQUIRE(game_validator.is_game_over() == true);
}

TEST_CASE("game_validatior::get_hints | word_length = 4, word = aahs valid_words = first 3 | Returns [aals]")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);
	game_validator.add_to_history("aahs");
	//game_validator.add_to_history("aals");

	// Act & Assert
	REQUIRE(game_validator.get_hints().size() == 1);
	REQUIRE(game_validator.get_hints()[0] == "aals");
}

TEST_CASE("game_validatior::get_hints | word_length = 4, word = nothing entered valid_words = first 3 | Returns 3 elements")
{
	// Arrange: 
	std::string path_test_file = "valid_words_limit_3.txt";
	int word_length = 4;
	auto word_processor = word_game::word_processor::word_processor(path_test_file);
	auto game_validator = word_game::game_validator::game_validator(word_processor, word_length);

	// Act & Assert
	REQUIRE(game_validator.get_hints().size() == 3);
}