#pragma once
#include "FBullCowGame.h"
#include <map>

// To make Syntax Unreal friendly
#define TMap std::map
using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); } // default Constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLenghtToMaxTries{ {3,5}, { 4,7 }, { 5,10 }, { 6,14 }, { 7,18 }, };
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // If the Guess isn't and isogram, return error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // If the guess isn't all lowercase, return error 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong, return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise, return OK
	{
		return EGuessStatus::OK;
	}

	return EGuessStatus::OK; 
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{ // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else
				{
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
		if (!islower(Letter)) { return false; }
		else { return true; }
	return true;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	
	// Setup Map
	TMap<char, bool> LetterSeen;

	// Loop for every Character in GuessWord
	for (auto Letter : Word) // for all letters in the word
	{
		Letter = tolower(Letter); //handle mixed Case
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true; }
	}

	return true; // for example in cases where /0 is entered
}
