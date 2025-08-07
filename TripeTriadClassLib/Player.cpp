
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

Card^ Player::selectCard(int index) {
	if (index < 0 || index >= remainingCards) {
		throw gcnew ArgumentOutOfRangeException("Index out of range");
	}
	return hand[index];
}
Card^ Player::selectCard() {
	int index = rand() % remainingCards; // Randomly select a card from the hand
	Card^ cpuCard = hand[index];
	removeCard(index); // Remove the selected card from the hand
	return cpuCard;
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