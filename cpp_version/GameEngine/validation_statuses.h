#pragma once

namespace word_game
{
	enum class CanAddResult
	{
		Yes,
		NoTooLong,
		NoTooShort,
		NoNotOneCharacterChanged,
		NoAlreadyUsedWord,
		NoInvalidWord
	};
}