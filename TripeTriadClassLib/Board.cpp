#include "pch.h"
#include "Board.h"

Board::Board(RuleSet^ ruleSet) {
	rules = ruleSet; // Initialize the rules of the game
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
    if(player != Control::CONTROL_PLAYER && player != Control::CONTROL_COMPUTER)
		throw gcnew ArgumentException("Invalid player control type");

    spaces[position]->placeCard(card, player); // Place the card in the specified position

    if(rules->isSame()) 
        computeBoardSame(position, card, player); // Compute the board state based on same rules
    if (rules->isPlus())
        computeBoardPlus(position, card, player);
    if (rules->isStandard()) 
        computeBoardStandard(position, card, player, false); // Compute the board state based on standard rules
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

void Board::flipRelativeSpace(Control newControl, int position, Direction direction, bool cascade) {
    if (position < 0 || position >= 9)
        return;

    switch (direction) {
    case Direction::DIRECTION_UP:
		if (position >= 3 //check that the position is not in the first row (so up would not be possible)
			&& spaces[position - 3]->occupied() // Check if the space above is occupied
			&& spaces[position - 3]->getControl() != (Char)newControl) { // Ensure the space above has a different control so it doesn't cascade too far
                spaces[position - 3]->flipSpace(newControl); // Flip the space above
                if(cascade) 
                    computeBoardStandard(position - 3, spaces[position - 3]->getCard(), newControl, true); // Cascade the flip if enabled
            }
            break;
        case Direction::DIRECTION_RIGHT:
			if (position % 3 != 2 && spaces[position + 1]->occupied() && spaces[position + 1]->getControl() != (Char)newControl) {
                spaces[position + 1]->flipSpace(newControl); // Flip the space to the right
                if(cascade) 
					computeBoardStandard(position + 1, spaces[position + 1]->getCard(), newControl, true); // Cascade the flip if enabled
            }
            break;
        case Direction::DIRECTION_DOWN:
			if (position < 6 && spaces[position + 3]->occupied() && spaces[position + 3]->getControl() != (Char)newControl) {
                spaces[position + 3]->flipSpace(newControl); // Flip the space below
				if (cascade) 
					computeBoardStandard(position + 3, spaces[position + 3]->getCard(), newControl, true); // Cascade the flip if enabled
            }
            break;
        case Direction::DIRECTION_LEFT:
			if (position % 3 != 0 && spaces[position - 1]->occupied() && spaces[position - 1]->getControl() != (Char)newControl) {
                spaces[position - 1]->flipSpace(newControl); // Flip the space to the left
                if (cascade)
					computeBoardStandard(position - 1, spaces[position - 1]->getCard(), newControl, true); // Cascade the flip if enabled
            }
            break;
        default:
            throw gcnew ArgumentException("Invalid direction");
    }

}

void Board::computeBoardStandard(int position, Card^ card, Control player, bool cascade) {

    Control control; // Variable to hold the control of the space
	player == Control::CONTROL_PLAYER ? //if the player is the human player
		control = Control::CONTROL_PLAYER : //sets the control to player
		control = Control::CONTROL_COMPUTER; // otherwise sets the control to computer
    // Check if the card can flip adjacent spaces
    if (position % 3 != 0 && spaces[position - 1]->occupied()) { // Check left
        if (spaces[position - 1]->getCard()->getRightInt() < card->getLeftInt()) {
            flipRelativeSpace(player, position, Direction::DIRECTION_LEFT, cascade); // Flip the left space
        }
    }
    if (position % 3 != 2 && spaces[position + 1]->occupied()) { // Check righ\t
        if (spaces[position + 1]->getCard()->getLeftInt() < card->getRightInt()) {
			flipRelativeSpace(player, position, Direction::DIRECTION_RIGHT, cascade);// Flip the right space
        }
    }
    if (position >= 3 && spaces[position - 3]->occupied()) { // Check above
        if (spaces[position - 3]->getCard()->getBottomInt() < card->getTopInt()) {
			flipRelativeSpace(player, position, Direction::DIRECTION_UP, cascade); // Flip the space above
        }
    }
    if (position < 6 && spaces[position + 3]->occupied()) { // Check below
        if (spaces[position + 3]->getCard()->getTopInt() < card->getBottomInt()) {
			flipRelativeSpace(player, position, Direction::DIRECTION_DOWN, cascade); // Flip the space below
        }
    }
}

void Board::computeBoardSame(int position, Card^ card, Control player) {

    Control control; // Variable to hold the control of the space
    player == Control::CONTROL_PLAYER ? //if the player is the human player
        control = Control::CONTROL_PLAYER : //sets the control to player
        control = Control::CONTROL_COMPUTER; // otherwise sets the control to computer

	bool wall = rules->isWall(); // Check if the wall rule is enabled

    int sameTop = 0;
	int sameLeft = 0;
	int sameRight = 0;
	int sameBottom = 0;
    // Check if the card can flip adjacent spaces
    if (position % 3 != 0) { // Check left
        if (spaces[position - 1]->occupied() && spaces[position - 1]->getCard()->getRightInt() == card->getLeftInt())
            sameLeft = 1; // Mark that the left space is a potential equal
    }
    else if (wall && card->getLeftInt() == 0)
        sameLeft = 1;

    if (position % 3 != 2){ // Check right
        if (spaces[position + 1]->occupied() && spaces[position + 1]->getCard()->getLeftInt() == card->getRightInt()) 
			sameRight = 1; // Mark that the right space is a potential equal
    }
    else if (wall && card->getRightInt() == 0)
        sameRight = 1;
    
    if (position >= 3){ // Check above
        if (spaces[position - 3]->occupied() && spaces[position - 3]->getCard()->getBottomInt() == card->getTopInt())
            sameTop = 1; // Mark that the top space is a potential equal
    }
    else if (wall && card->getTopInt() == 0)
		sameTop = 1;
    
    if (position < 6){ // Check below
        if (spaces[position + 3]->occupied() && spaces[position + 3]->getCard()->getTopInt() == card->getBottomInt()) 
            sameBottom = 1; // Mark that the bottom space is a potential equal
    }
	else if (wall && card->getBottomInt() == 0)
		sameBottom = 1;

    if(sameTop + sameLeft + sameRight + sameBottom >= 2) {
		bool cascade = rules->isCascade(); // Check if the cascade rule is enabled
        if (sameTop == 1)//don't try to flip the wall if there's no space above
			flipRelativeSpace(control, position, Direction::DIRECTION_UP, cascade); // Flip the space above if it is an equal
        if (sameBottom == 1)
			flipRelativeSpace(control, position, Direction::DIRECTION_DOWN, cascade); // Flip the space below if it is an equal
        if (sameLeft == 1)
			flipRelativeSpace(control, position, Direction::DIRECTION_LEFT, cascade); // Flip the left space if it is an equal
        if (sameRight == 1)
			flipRelativeSpace(control, position, Direction::DIRECTION_RIGHT, cascade); // Flip the right space if it is an equal
	}
}

void Board::computeBoardPlus(int position, Card^ card, Control player) {

    Control control; // Variable to hold the control of the space
    player == Control::CONTROL_PLAYER ? //if the player is the human player
        control = Control::CONTROL_PLAYER : //sets the control to player
        control = Control::CONTROL_COMPUTER; // otherwise sets the control to computer

	bool wall = rules->isWall(); // Check if the wall rule is enabled

    int plusTop = -1;
    int plusLeft = -1;
    int plusRight = -1;
    int plusBottom = -1;
    // Check if the card can flip adjacent spaces
    if (position % 3 != 0) { // Check left
        if (spaces[position - 1]->occupied())
            plusLeft = spaces[position - 1]->getCard()->getRightInt() + card->getLeftInt();
    }
    else if (wall)
        plusLeft = card->getLeftInt();

    if (position % 3 != 2) { // Check right
        if (spaces[position + 1]->occupied())
            plusRight = spaces[position + 1]->getCard()->getLeftInt() + card->getRightInt();
    }
    else if (wall)
		plusRight = card->getRightInt();

    if (position >= 3) { // Check above
        if (spaces[position - 3]->occupied())
            plusTop = spaces[position - 3]->getCard()->getBottomInt() + card->getTopInt();
    }
	else if (wall)
		plusTop = card->getTopInt();

    if (position < 6) { // Check below
        if (spaces[position + 3]->occupied())
            plusBottom = spaces[position + 3]->getCard()->getTopInt() + card->getBottomInt();
	}
	else if (wall)
		plusBottom = card->getBottomInt();

    bool cascade = rules->isCascade(); // Check if the cascade rule is enabled
    
	//compare the plus values for all directions to see whether they are equal
    if (plusTop != -1){
        if (plusTop == plusRight) {
			flipRelativeSpace(control, position, Direction::DIRECTION_UP, cascade); // Flip the space above
			flipRelativeSpace(control, position, Direction::DIRECTION_RIGHT, cascade); // Flip the right space
        }
        if (plusTop == plusBottom) {
			flipRelativeSpace(control, position, Direction::DIRECTION_UP, cascade); // Flip the space above
			flipRelativeSpace(control, position, Direction::DIRECTION_DOWN, cascade); // Flip the space below
        }        
        if (plusTop == plusLeft) {
			flipRelativeSpace(control, position, Direction::DIRECTION_UP, cascade); // Flip the space above
			flipRelativeSpace(control, position, Direction::DIRECTION_LEFT, cascade); // Flip the left space
        }
    }
    if(plusRight != -1) {
        if (plusRight == plusBottom) {
			flipRelativeSpace(control, position, Direction::DIRECTION_RIGHT, cascade); // Flip the right space
			flipRelativeSpace(control, position, Direction::DIRECTION_DOWN, cascade); // Flip the space below
        }
		if (plusRight == plusLeft) {
            flipRelativeSpace(control, position, Direction::DIRECTION_RIGHT, cascade); // Flip the right space
            flipRelativeSpace(control, position, Direction::DIRECTION_LEFT, cascade); // Flip the left space
        }
    }
    if (plusBottom != -1) {
        if (plusBottom == plusLeft) {
            flipRelativeSpace(control, position, Direction::DIRECTION_DOWN, cascade); // Flip the space below
            flipRelativeSpace(control, position, Direction::DIRECTION_LEFT, cascade); // Flip the left space
        }
    }
}