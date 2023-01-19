// GameRunner.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iterator>
#include <windows.h> 

#include "game_validator.h"

std::string get_username()
{
    std::string name;
    std::cout << "Please enter your name: ";
    std::cin >> name;
    return name;
}

enum class turn
{
    PlayerHuman, 
    PlayerComputer
};

turn select_at_random_who_goes_first()
{
    if (rand() > (RAND_MAX / 2))
    {
        return turn::PlayerHuman;
    }
    return turn::PlayerComputer;
}

std::string get_word_from_human(std::string player_name)
{
    std::string word;
    std::cout << player_name << ", please enter your word: ";
    std::cin >> word;
    return word;
}

void print_error(std::string error_message, HANDLE handle_console)
{
    SetConsoleTextAttribute(handle_console, 12);
    std::cout << error_message << std::endl;
    SetConsoleTextAttribute(handle_console, 7);
}

int main()
{
    HANDLE handle_console = GetStdHandle(STD_OUTPUT_HANDLE);

    // Print info about the game. 
    std::cout << "Welcome to WORD GAME!\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "Rules:\n";
    std::cout << "- Human and Computer Players make alternating moves by entering 4 character words.  Which player goes first is chosen at random.\n";
    std::cout << "- Player which goes first has to enter any valid 4 character word (in English).\n";
    std::cout << "- Subsequent player has to enter previosuly unused word which also differs from the last used word by one character (moon --> noon).\n";
    std::cout << "- The player who enters the last valid word wins the game.  That means that the oponent has no valid words to use.\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "- For hint enter ?.\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------\n";

    // Set up Players.
    std::string player_human = get_username();
    std::string player_computer = "Charles AI Bot";

    // Set up game_validator. 
    auto word_processor = word_game::word_processor("valid_words.txt");
    auto game_validator = word_game::game_validator(word_processor, 4);

    // Announce who goes first.
    turn turn = select_at_random_who_goes_first();
    std::string first_player = turn == turn::PlayerHuman ? player_human : player_computer;
    std::cout << player_computer << " won the toss and will go first." << std::endl;

    // Run the game.
    while (!game_validator.is_game_over())
    {
        if (turn == turn::PlayerHuman)
        {
            std::string candidate_word = get_word_from_human(player_human);
            if (candidate_word == "?")
            {
                std::vector<std::string> hints = game_validator.get_hints();
                SetConsoleTextAttribute(handle_console, 14);
                for (auto &hint : hints)
                {
                    std::cout << "Hint: " << hint << std::endl;
                }
                SetConsoleTextAttribute(handle_console, 7);
                continue;
            }
            word_game::CanAddResult word_status = game_validator.can_add(candidate_word);
            switch (word_status)
            {
            case word_game::CanAddResult::Yes:
                game_validator.add_to_history(candidate_word);
                if (game_validator.is_game_over())
                {
                    SetConsoleTextAttribute(handle_console, 10);
                    std::cout << "Contratulations " << player_human << "! You won!\n";
                    SetConsoleTextAttribute(handle_console, 7);
                }
                else
                {
                    turn = turn::PlayerComputer;
                }
                break;
            case word_game::CanAddResult::NoTooLong:
                print_error("Invalid word: too long.", handle_console);
                break;
            case word_game::CanAddResult::NoTooShort:
                print_error("Invalid word: too short.", handle_console);
                break;
            case word_game::CanAddResult::NoNotOneCharacterChanged:
                print_error("Invalid word: not one character change compare to last submitted word.", handle_console);
                break;
            case word_game::CanAddResult::NoAlreadyUsedWord:
                print_error("Invalid word: this word has already been used.", handle_console);
                break;
            case word_game::CanAddResult::NoInvalidWord:
                print_error("Invalid word: not found in the dictionary.", handle_console);
                break;
            default:
                break;
            }
        }
        else
        {
            std::vector<std::string> candidate_words = game_validator.get_hints();
            std::vector<std::string>::iterator rand_it = candidate_words.begin();
            std::advance(rand_it, std::rand() % candidate_words.size());
            std::string candidate_word = *rand_it;
            std::cout << player_computer << " entered: " << candidate_word << std::endl;
            game_validator.add_to_history(candidate_word);
            if (game_validator.is_game_over())
            {
                std::cout << "Contratulations " << player_computer << "! You won!\n";
            }
            else
            {
                turn = turn::PlayerHuman;
            }
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
