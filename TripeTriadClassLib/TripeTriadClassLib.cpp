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

	gameBoard->placeCard(position, selectedCard, control); // Place the card on the board
	player->removeCard(cardIndex); // Remove the card from the player's hand
			
	// For now, we will just return a simple message.
	return getGameState();
}

String^ GameState::selectOpponentCard() {
	computer->calculateTurn(gameBoard, ruleSet); // Let the computer calculate its turn
	
	return getGameState();
}

String^ GameState::playOpponentCard() {
	gameBoard->placeCard(computer->getSelectedPosition(), computer->selectCard(), Control::CONTROL_COMPUTER); // Place the computer's selected card on the board
	computer->removeCard(computer->getSelectedCardIndex()); // Remove the card from the computer's hand
	computer->resetTurn(); // Reset the computer's turn
	return getGameState();
}

String^ GameState::setNewRules(String^ ruleSetString) {

	// Set the new rules for the game
	ruleSet = gcnew RuleSet(ruleSetString->Contains("Open"),
							ruleSetString->Contains("Standard"),
							ruleSetString->Contains("Same"),
							ruleSetString->Contains("Plus"),
							ruleSetString->Contains("Wall"),
							ruleSetString->Contains("Cascade"));
	// Reset the game board and players to apply the new rules
	resetGame();
	return getGameState();
}

String^ GameState::getGameState() {	
	return String::Format("{0};{1};{2};{3}", player->getHandState(), gameBoard->getBoardState(), computer->getHandState(ruleSet->isOpen()), gameBoard->getScore());
}

void GameState::resetGame() {
	// Reset the game state, including the board and players
	gameBoard = gcnew Board(ruleSet);
	player = gcnew HumanPlayer();
	computer = gcnew ComputerPlayer();
}