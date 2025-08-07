#include "pch.h"

#include "TripeTriadClassLib.h"

using namespace TripeTriadClassLib;
using namespace System;

String^ GameState::placeCard(String^ playerName, int position, int cardIndex) {
	// This function should handle placing a card on the board
	// and return a message indicating the result of the action.
	Control control = Control::CONTROL_EMPTY;
	if(playerName == "Player")
		control = Control::CONTROL_PLAYER;
	else
		return "Invalid player name.";

	Card^ selectedCard = player->selectCard(cardIndex); // Get the card from the player's hand
	if (selectedCard == nullptr) {
		return "Invalid card index.";
	}
	gameBoard->placeCard(position, selectedCard, control); // Place the card on the board
	player->removeCard(cardIndex); // Remove the card from the player's hand

	Card^ computerCard = computer->selectCard(); // The computer selects a card from its hand

	gameBoard->placeCard(computerCard, Control::CONTROL_COMPUTER); // Place the computer's card on the board
		
	// For now, we will just return a simple message.
	return getGameState();
}

String^ GameState::getGameState() {
	
	return String::Format("{0};{1};{2};{3}", player->getHandState(), gameBoard->getBoardState(), computer->getHandState(), gameBoard->getScore());
}

void GameState::resetGame() {
	// Reset the game state, including the board and players
	gameBoard = gcnew Board();
	player = gcnew Player();
	computer = gcnew Player();
}