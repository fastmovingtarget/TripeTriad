#pragma once
#include "Board.h"
#include "Player.h"

using namespace System;


namespace TripeTriadClassLib {
	public ref class GameState
	{
		private:
			HumanPlayer^ player = gcnew HumanPlayer();
			ComputerPlayer^ computer = gcnew ComputerPlayer();
			RuleSet^ ruleSet = gcnew RuleSet();
			Board^ gameBoard = gcnew Board(ruleSet);

		public:
			GameState(){
				// Initialize the game with players and board
			}
			String^ placeCard(String^ playerName, int position, int cardIndex);
			String^ selectOpponentCard();
			String^ playOpponentCard();
			String^ setNewRules(String^ ruleSet);
			String^ getGameState(); // Get the current state of the board
			void resetGame();
	};
}
