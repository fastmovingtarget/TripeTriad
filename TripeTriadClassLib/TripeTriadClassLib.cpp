#include "pch.h"

#include "TripeTriadClassLib.h"

using namespace TripeTriadClassLib;
using namespace System;

String^ GameState::placeCard(String^ playerName, int position, int cardIndex) {
	// This function should handle placing a card on the board
	// and return a message indicating the result of the action.
	if(playerName != "Player")
		return "Invalid player name.";

	Control control = Control::CONTROL_PLAYER;

	Card^ selectedCard = player->selectCard(cardIndex); // Get the card from the player's hand
	if (selectedCard == nullptr) {
		return "Invalid card index.";
	}

	gameBoard->placeCard(position, selectedCard, control, ruleSet); // Place the card on the board
	player->removeCard(cardIndex); // Remove the card from the player's hand

	computer->takeTurn(gameBoard, ruleSet); // Let the computer take its turn
		
	// For now, we will just return a simple message.
	return getGameState();
}

String^ GameState::getGameState() {
	
	return String::Format("{0};{1};{2};{3}", player->getHandState(), gameBoard->getBoardState(), computer->getHandState(), gameBoard->getScore());
}

void GameState::resetGame() {
	// Reset the game state, including the board and players
	gameBoard = gcnew Board();
	player = gcnew HumanPlayer();
	computer = gcnew ComputerPlayer();
}