#pragma once

#include "Card.h"
#include "RuleSet.h"

using namespace System;

public enum class Control : char {
    CONTROL_EMPTY = ' ', // Space is empty
    CONTROL_PLAYER = 'P', // Controlled by Player 1
    CONTROL_COMPUTER = 'C' // Controlled by Player 2
};

public enum class Direction : int {//(NESW style)
    DIRECTION_UP = 0, // Up direction
    DIRECTION_RIGHT = 1, // Right direction
    DIRECTION_DOWN = 2, // Down direction
	DIRECTION_LEFT = 3 // Left direction 
};

public ref class Board {

    ref class BoardSpace {
        private:
            Card^ card; // Card placed in this space, default is an empty card
            Control control = Control::CONTROL_EMPTY; // Flag to indicate if the space is occupied
        public:
            BoardSpace(int pos) : card(gcnew Card(" ")) {} // Constructor to initialize the position

            void placeCard(Card^ c, Control player);

            void flipSpace(Control newControl) {
                control = newControl; // Change the control of the space
            }

            Card^ getCard() { return card; } // Get the card in this space
            bool occupied() { return control != Control::CONTROL_EMPTY; } // Check if the space is occupied
			Char getControl() { return (Char)control; } // Get the control of the space
    };    

    private:
        array<BoardSpace^>^ spaces = gcnew array<BoardSpace^>(9); // Create an array of 9 BoardSpace objects
        

    public:
        Board();
        // Print the current state of the board
        String^ getBoardState();
        bool isSpaceOccupied(int position) {
            return spaces[position]->occupied(); // Check if the space at the given position is occupied
		}
        Card^ getCardAt(int position) {
            return spaces[position]->getCard(); // Get the card at the specified position
		}

        // Place a card on the board
        void placeCard(int position, Card^ card, Control player, RuleSet^ ruleSet);
        void placeCard(Card^ card, Control player, RuleSet^ ruleSet);

        void flipRelativeSpace(Control newControl, int position, Direction direction);

        void computeBoardStandard(int position, Card^ card, Control player);
		void computeBoardSame(int position, Card^ card, Control player, bool wall);
		void computeBoardPlus(int position, Card^ card, Control player, bool wall);

        // Check if the board is full
        bool isFull();

		// Get the score of the board
        String^ getScore();
};