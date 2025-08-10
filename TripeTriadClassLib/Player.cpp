#include "pch.h"
#include "Player.h"

using namespace System;

Player::Player() {
	name = "Player"; // Default player name
	hand = gcnew array<Card^>(5); // Initialize hand with 5 cards
	Random^ rand = gcnew Random(); // Random number generator
	for(int i = 0; i < 5; i++) {
		hand[i] = gcnew Card(
			String::Format("{0}", rand->NextInt64() % 10),
			String::Format("{0}", rand->NextInt64() % 10),
			String::Format("{0}", rand->NextInt64() % 10),
			String::Format("{0}", rand->NextInt64() % 10)
		); // Generate random cards for the hand
	}
}

String^ Player::getHandState() {
	String^ handState = "";
	for (int i = 0; i < remainingCards; i++) {
		handState += String::Format("{0}{1}{2}{3},", hand[i]->getTop(), hand[i]->getLeft(), hand[i]->getRight(), hand[i]->getBottom());
	}
	return handState->TrimEnd(','); 
}

void Player::removeCard(int index) {
	if (index < 0 || index >= remainingCards) {
		throw gcnew ArgumentOutOfRangeException("Index out of range");
	}
	// Shift cards to remove the selected card
	for (int i = index; i < remainingCards - 1; i++) {
		hand[i] = hand[i + 1];
	}
	remainingCards--; // Decrease the count of remaining cards
	hand[remainingCards] = nullptr; // Clear the last card reference
}

Card^ HumanPlayer::selectCard(int index) {
	if (index < 0 || index >= remainingCards) {
		throw gcnew ArgumentOutOfRangeException("Index out of range");
	}
	return hand[index];
}

Card^ ComputerPlayer::selectCard(int _) {
	int index = rand->NextInt64() % remainingCards; // Randomly select a card from the hand
	Card^ cpuCard = hand[index];
	removeCard(index); // Remove the selected card from the hand
	return cpuCard;
}

String^ ComputerPlayer::getHandState(bool isOpen) {
	String^ handState = "";
	for (int i = 0; i < remainingCards; i++) {
		if (isOpen) {
			handState += String::Format("{0}{1}{2}{3},", hand[i]->getTop(), hand[i]->getLeft(), hand[i]->getRight(), hand[i]->getBottom());
		} else {
			handState += String::Format("****,"); // Hide card details if not open
		}
	}
	return handState->TrimEnd(',');
}

void ComputerPlayer::takeTurn(Board^ board, RuleSet^ ruleSet) {
	if (board->isFull())
		return;

	int bestCardIndex = -1;
	int bestPlacementIndex = -1;
	int bestScoreAddition = -1;
	for (int i = 0; i < remainingCards; i++) {
		for (int position = 0; position < 9; position++) {
			if (board->isSpaceOccupied(position))
				continue;

			int scoreAddition = 0;
			// Check if the card can flip adjacent spaces
			if (position % 3 != 0)  // Check left
				if (board->isSpaceOccupied(position - 1) && board->getCardAt(position - 1)->getRightInt() < hand[i]->getLeftInt()) {
					scoreAddition++;
				}
			if (position % 3 != 2)  // Check right
				if (board->isSpaceOccupied(position + 1) && board->getCardAt(position + 1)->getLeftInt() < hand[i]->getRightInt()) {
					scoreAddition++;
				}
			
			if (position >= 3) // Check above
				if (board->isSpaceOccupied(position - 3) && board->getCardAt(position - 3)->getBottomInt() < hand[i]->getTopInt()) {
					scoreAddition++;
				}
			
			if (position < 6) // Check below
				if (board->isSpaceOccupied(position + 3) && board->getCardAt(position + 3)->getTopInt() < hand[i]->getBottomInt()) {
					scoreAddition++;
				}

			if(scoreAddition > bestScoreAddition) {
				bestScoreAddition = scoreAddition;
				bestCardIndex = i;
				bestPlacementIndex = position;
			}
		}
	}
	board->placeCard(bestPlacementIndex, hand[bestCardIndex], Control::CONTROL_COMPUTER, ruleSet); // Place the best card on the board
	removeCard(bestCardIndex); // Remove the card from the hand
}