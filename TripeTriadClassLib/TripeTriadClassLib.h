#pragma once
#include "Board.h"
#include "Player.h"

using namespace System;


namespace TripeTriadClassLib {
	public ref class GameState
	{
		private:
			Board^ gameBoard = gcnew Board();
			HumanPlayer^ player = gcnew HumanPlayer();
			ComputerPlayer^ computer = gcnew ComputerPlayer();
			RuleSet^ ruleSet = gcnew RuleSet();

		public:
			GameState(){
				// Initialize the game with players and board
			}
			String^ placeCard(String^ playerName, int position, int cardIndex);
			String^ getGameState(); // Get the current state of the board
			void resetGame();
	};
}
