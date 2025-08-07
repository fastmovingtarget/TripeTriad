using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Media.Media3D;
using TripeTriadClassLib;

namespace TripeTriadUI
{
    /*  The View Model for the Tripe Triad game.
     *  Contains PlayerViewModels for both the player and the opponent,
     *  a BoardViewModel for the game board.
     *  Makes calls to the GameState class to update the game state (which would be the Model in MVVM).
     *  Stores the selected card index for the player to play a card, and processes the victory condition.
     */
    public class TTViewModel
    {
        // The GameState instance that manages the game logic
        private GameState GameState = new GameState();

        // ViewModels for the player, opponent, and board
        public PlayerViewModel PlayerViewModel { get; set; }
        public PlayerViewModel OpponentViewModel { get; set; }
        public BoardViewModel BoardViewModel { get; set; }

        // The index of the selected card in the player's hand
        public int SelectedCardIndex { get; set; } = -1;


        // Constructor initializes the view model and sets up the initial game state
        public TTViewModel()
        {
            // GameState.getGameState() returns a string in the format "PlayerHand;BoardState;OpponentHand;Scores"
            String gameStateString = GameState.getGameState();
            String[] gameStateParts = gameStateString.Split(';');
            // We create the PlayerViewModel and OpponentViewModel using the game state parts, specifying colors for each player
            // Don't need to input the score here, as it will be initialised at 0 regardless, then updated later
            PlayerViewModel = new PlayerViewModel(
                "Player",
                gameStateParts[0],
                "CornflowerBlue"
            );
            OpponentViewModel = new PlayerViewModel(
                "Computer",
                gameStateParts[2],
                "Tomato"
            );

            // We create the BoardViewModel using the board state from the game state parts
            BoardViewModel = new BoardViewModel(gameStateParts[1]);
        }

        // This method updates the PlayerViewModel, OpponentViewModel, and BoardViewModel based on the game state string
        private void UpdateViewModels(String gameStateString)
        {
            // Split the game state string into its components
            String[] gameStateParts = gameStateString.Split(';');
            if (gameStateParts.Length != 4)
            {
                throw new ArgumentException("Game state string is not in the expected format.");
            }
            // Update the player and opponent view models with their respective hands and scores
            PlayerViewModel.Update(gameStateParts[0], Int32.Parse(gameStateParts[3].Substring(0,1)));
            OpponentViewModel.Update(gameStateParts[2], Int32.Parse(gameStateParts[3].Substring(1, 1)));
            // Update the board view model
            BoardViewModel.Update(gameStateParts[1]);

            // Check for victory conditions based on the game state parts
            if (String.IsNullOrEmpty(gameStateParts[0])){
                if (PlayerViewModel.Score > OpponentViewModel.Score)
                {
                    BoardViewModel.DeclareVictory("You win!");
                }
                else if (PlayerViewModel.Score == OpponentViewModel.Score)
                {
                    BoardViewModel.DeclareVictory("It's a draw!");
                }
                else
                {
                    BoardViewModel.DeclareVictory("You lose!");
                }
            }
        }

        // Methods to handle player actions
        public void SelectCard(int cardIndex)
        {
            PlayerViewModel.SelectCard(cardIndex, SelectedCardIndex);

            SelectedCardIndex = cardIndex;
        }
        public void PlayCard(int boardIndex)
        {
            String gameStateString = GameState.placeCard("Player", boardIndex, SelectedCardIndex);
            SelectedCardIndex = -1; // Reset selected card after playing
            UpdateViewModels(gameStateString);
        }
        public void Reset()
        {
            GameState.resetGame();
            String gameStateString = GameState.getGameState();
            UpdateViewModels(gameStateString);
            BoardViewModel.DeclareVictory("");
        }
    }
}
