#include "pch.h"
#include "Board.h"

Board::Board() {
    for (int i = 0; i < 9; i++) {
        spaces[i] = gcnew BoardSpace(i); // Initialize each board space
    }
}

void Board::BoardSpace::placeCard(Card^ c, Control player) {
    if (control == Control::CONTROL_EMPTY) {
        card = c; // Place the card in this space
		player == Control::CONTROL_PLAYER ? control = Control::CONTROL_PLAYER : control = Control::CONTROL_COMPUTER; // Set the control based on the player
    }
}

String^ Board::getBoardState() {
    String^ boardState = "";
    for (int i = 0; i < 9; i++) {
		BoardSpace^ space = spaces[i]; // Get the space at position i
		Card^ card = space->getCard(); // Get the card in the space

        boardState += String::Format("{0}{1}{2}{3}{4},", space->getControl(), card->getTop(), card->getLeft(), card->getRight(), card->getBottom());
    }
    return boardState->TrimEnd(','); // Return the complete board state
}

void Board::placeCard(Card^ card, Control player, RuleSet^ ruleSet) {
    if (player != Control::CONTROL_PLAYER && player != Control::CONTROL_COMPUTER)
        throw gcnew ArgumentException("Invalid player control type");
    for (int i = 0; i < 9; i++) {
        if (!spaces[i]->occupied()) { // Find the first empty space
            placeCard(i, card, player, ruleSet); // Place the card in the empty space
            return; // Exit after placing the card
        }
    }
    return;
}

void Board::placeCard(int position, Card^ card, Control player, RuleSet^ ruleSet) {
    int playerScore = 1;
    if(player != Control::CONTROL_PLAYER && player != Control::CONTROL_COMPUTER)
		throw gcnew ArgumentException("Invalid player control type");

    spaces[position]->placeCard(card, player); // Place the card in the specified position

    if (ruleSet->isStandard()) {
        computeBoardStandard(position, card, player); // Compute the board state based on standard rules
    }

}

bool Board::isFull() {
    for (int i = 0; i < 9; i++) {
        if (!spaces[i]->occupied()) {
            return false; // If any space is not occupied, the board is not full
        }
    }
    return true; // All spaces are occupied, the board is full
}

String^ Board::getScore() {
    int playerScore = 0;
    int computerScore = 0;
    for (int i = 0; i < 9; i++) {
        if (spaces[i]->getControl() == (Char)Control::CONTROL_PLAYER) {
            playerScore++;
        } else if (spaces[i]->getControl() == (Char)Control::CONTROL_COMPUTER) {
            computerScore++;
        }
    }
    return String::Format("{0}{1}", playerScore, computerScore); // Return the scores of both players
}   

void Board::computeBoardStandard(int position, Card^ card, Control player) {

    Control control; // Variable to hold the control of the space
	player == Control::CONTROL_PLAYER ? //if the player is the human player
		control = Control::CONTROL_PLAYER : //sets the control to player
		control = Control::CONTROL_COMPUTER; // otherwise sets the control to computer
    // Check if the card can flip adjacent spaces
    if (position % 3 != 0) { // Check left
        if (spaces[position - 1]->occupied() && spaces[position - 1]->getCard()->getRightInt() < card->getLeftInt()) {
            spaces[position - 1]->flipSpace(control); // Flip the left space
        }
    }
    if (position % 3 != 2) { // Check right
        if (spaces[position + 1]->occupied() && spaces[position + 1]->getCard()->getLeftInt() < card->getRightInt()) {
            spaces[position + 1]->flipSpace(control); // Flip the right space
        }
    }
    if (position >= 3) { // Check above
        if (spaces[position - 3]->occupied() && spaces[position - 3]->getCard()->getBottomInt() < card->getTopInt()) {
            spaces[position - 3]->flipSpace(control); // Flip the space above
        }
    }
    if (position < 6) { // Check below
        if (spaces[position + 3]->occupied() && spaces[position + 3]->getCard()->getTopInt() < card->getBottomInt()) {
            spaces[position + 3]->flipSpace(control); // Flip the space below
        }
    }
}