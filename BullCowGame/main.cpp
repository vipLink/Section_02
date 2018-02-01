/* This is the console executabe that makes use of the BullCow Class
This acts as the View in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame Class

*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make Syntax Unreal friendly
using FText = std::string;
using int32 = int;

// Funktion prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();



FBullCowGame BCGame; //instantiate a new game, which we re-uese across plays 

// the entry point for our Application 
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	std::cout << std::endl;
	return 0; // Exit the Application
}
// Plays a Single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		
		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// Print number of bulls and cows

		//print the guess back to them
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop until the player gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try: " << CurrentTry << " out of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word that is an isogram\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a letter word, using only lowercase.\n\n";
			break;
		default:
			// assume Case is valid
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "           {___}        ___  " << std::endl;
	std::cout << "           (o o)       (o o) " << std::endl;
	std::cout << "   /--------\\  /        \\ /--------\\" << std::endl;
	std::cout << "  / |  BULL |O           O | COW  | \\" << std::endl;
	std::cout << " *  |-,-----|              |------|  * "<< std::endl;
	std::cout << "    ^       ^              ^      ^"<< std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "Congratulations! You Win the Game!\n";
	}
	else
	{
		std::cout << "That's too bad, better luck next time!\n";
	}
}
