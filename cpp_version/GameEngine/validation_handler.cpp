#include "pch.h"

#include <string>

#include "validation_statuses.h"
#include "validation_handler.h"
#include "game_validator.h"

word_game::CanAddResult word_game::validation_handler::validate(std::string word)
{
	if (next_handeler_)
	{
		return next_handeler_->validate(word);
	}

	return word_game::CanAddResult::Yes;
}

word_game::validation_handler* word_game::validation_handler::set_next(word_game::validation_handler* handler)
{
	next_handeler_ = handler;
	return handler;
}