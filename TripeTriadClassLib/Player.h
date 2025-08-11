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
        void removeCard(int index);
        int getHandSize() { return remainingCards; } // Get the number of cards in the player's hand
};

public ref class ComputerPlayer : public Player {
    private:
		Random^ rand = gcnew Random(); // Random number generator for selecting cards
		int selectedCardIndex = -1; // Index of the selected card for the computer player
		int selectedPosition = -1; // Position where the card will be placed on the board
    public:
        ComputerPlayer() : Player() {} // Inherit constructor from Player
        // Override selectCard to randomly select a card from the hand
		int getSelectedCardIndex() { return selectedCardIndex; } // Get the index of the selected card
		int getSelectedPosition() { return selectedPosition; } // Get the position where the card will be placed
        Card^ selectCard(); 
        String^ getHandState(bool isOpen);
		void calculateTurn(Board^ board, RuleSet^ ruleSet); // Method for the computer to take its turn
        void resetTurn() {
            selectedCardIndex = -1; // Reset the selected card index
            selectedPosition = -1; // Reset the selected position
		}
};

public ref class HumanPlayer : public Player {
    public:
        HumanPlayer() : Player() {} // Inherit constructor from Player
        // Override selectCard to allow the player to select a card by index
        Card^ selectCard(int index) ;
};