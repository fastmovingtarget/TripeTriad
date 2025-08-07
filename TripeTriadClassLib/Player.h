#pragma once

#include "Card.h"

using namespace System;

public ref class Player {
	private:
		String^ name;
		array<Card^>^ hand; // Array of cards in the player's hand
        int remainingCards = 5; // Number of cards remaining in the player's hand
		int score = 5; // Player's score

	public:
        Player();
        String^ getHandState();
        Card^ selectCard(int index);
        Card^ selectCard();
        void removeCard(int index);
        int getHandSize() { return remainingCards; } // Get the number of cards in the player's hand
        int getScore() { return score; }
        void increaseScore(int amount) { score += amount; }
};