#pragma once

#include "Card.h"
#include "Board.h"

using namespace System;

public ref class Player abstract {
	private:
		String^ name;

	public:
		array<Card^>^ hand; // Array of cards in the player's hand
        int remainingCards = 5; // Number of cards remaining in the player's hand
        Player();
        String^ getHandState();
        virtual Card^ selectCard(int index) = 0;
        void removeCard(int index);
        int getHandSize() { return remainingCards; } // Get the number of cards in the player's hand
};

public ref class ComputerPlayer : public Player {
    private:
		Random^ rand = gcnew Random(); // Random number generator for selecting cards
    public:
        ComputerPlayer() : Player() {} // Inherit constructor from Player
        // Override selectCard to randomly select a card from the hand
        Card^ selectCard(int index) override;
        String^ getHandState(bool isOpen);
		void takeTurn(Board^ board, RuleSet^ ruleSet); // Method for the computer to take its turn
};

public ref class HumanPlayer : public Player {
    public:
        HumanPlayer() : Player() {} // Inherit constructor from Player
        // Override selectCard to allow the player to select a card by index
        Card^ selectCard(int _) override;
};