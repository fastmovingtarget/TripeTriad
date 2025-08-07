#pragma once

#include "Card.h"

using namespace System;

public enum class Control : char {
    CONTROL_EMPTY = ' ', // Space is empty
    CONTROL_PLAYER = 'P', // Controlled by Player 1
    CONTROL_COMPUTER = 'C' // Controlled by Player 2
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

        // Place a card on the board
        void placeCard(int position, Card^ card, Control player);
        void placeCard(Card^ card, Control player);

        // Check if the board is full
        bool isFull();

		// Get the score of the board
        String^ getScore();
};