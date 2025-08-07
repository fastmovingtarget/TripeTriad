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

void Board::placeCard(Card^ card, Control player) {
    if (player != Control::CONTROL_PLAYER && player != Control::CONTROL_COMPUTER)
        throw gcnew ArgumentException("Invalid player control type");
    for (int i = 0; i < 9; i++) {
        if (!spaces[i]->occupied()) { // Find the first empty space
            placeCard(i, card, player); // Place the card in the empty space
            return; // Exit after placing the card
        }
    }
    return;
}

void Board::placeCard(int position, Card^ card, Control player) {
    int playerScore = 1;
	Control control; // Variable to hold the control of the space
    if(player != Control::CONTROL_PLAYER && player != Control::CONTROL_COMPUTER)
		throw gcnew ArgumentException("Invalid player control type");

    player == Control::CONTROL_PLAYER ? control = Control::CONTROL_PLAYER : control = Control::CONTROL_COMPUTER; // Set the control based on the player

    spaces[position]->placeCard(card, player); // Place the card in the specified position
    // Check if the card can flip adjacent spaces
    if (position % 3 != 0) { // Check left
        if (spaces[position - 1]->occupied() && spaces[position - 1]->getCard()->getRightInt() < card->getLeftInt()) {
            spaces[position - 1]->flipSpace(control); // Flip the left space
            playerScore++;
        }
    }
    if (position % 3 != 2) { // Check right
        if (spaces[position + 1]->occupied() && spaces[position + 1]->getCard()->getLeftInt() < card->getRightInt()) {
            spaces[position + 1]->flipSpace(control); // Flip the right space
            playerScore++;
        }
    }
    if (position >= 3) { // Check above
        if (spaces[position - 3]->occupied() && spaces[position - 3]->getCard()->getBottomInt() < card->getTopInt()) {
            spaces[position - 3]->flipSpace(control); // Flip the space above
            playerScore++;
        }
    }
    if (position < 6) { // Check below
        if (spaces[position + 3]->occupied() && spaces[position + 3]->getCard()->getTopInt() < card->getBottomInt()) {
            spaces[position + 3]->flipSpace(control); // Flip the space below
            playerScore++;
        }
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