using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TripeTriadUI
{
    public class BoardViewModel : INotifyPropertyChanged
    {
        public class BoardSpaceViewModel
        {
            public Control Owner { get; set; } // Player or Opponent or Uncontrolled
            public String Colour { get; set; }
            public CardViewModel Card { get; set; }

            public BoardSpaceViewModel(String boardSpaceString)
            {
                switch (boardSpaceString[0])
                {
                    case 'P':
                        Owner = Control.Player;
                        Colour = "CornflowerBlue"; // Default color for player
                        break;
                    case 'C':
                        Owner = Control.Computer;
                        Colour = "Tomato"; // Default color for opponent
                        break;
                    default:
                        Owner = Control.Uncontrolled;
                        Colour = "LightGray"; // Default color for uncontrolled space
                        break;
                }
                Card = new CardViewModel(boardSpaceString.Substring(1, 4), Colour);
            }
            public void Update(String boardSpaceString)
            {
                switch (boardSpaceString[0])
                {
                    case 'P':
                        Owner = Control.Player;
                        break;
                    case 'C':
                        Owner = Control.Computer;
                        break;
                    default:
                        Owner = Control.Uncontrolled;
                        break;
                }
                Card = new CardViewModel(boardSpaceString.Substring(1, 4));
            }
        }

        public String VictoryString { get; set; } // This could be used to display the victory condition in the UI
        public List<BoardSpaceViewModel> Spaces { get; }

        public event PropertyChangedEventHandler? PropertyChanged;
        public BoardViewModel(List<BoardSpaceViewModel> inputSpaces)
        {
            Spaces = inputSpaces;
            VictoryString = "";
        }
        public BoardViewModel(String spacesString)
        {
            Spaces = spacesString.Split(',').Select((boardSpaceString, index) =>
                    new BoardSpaceViewModel(boardSpaceString)).ToList(); ;
            VictoryString = "";
        }
        public void Update(String boardStateString)
        {
            List<String> boardSpaceStrings = boardStateString.Split(',').ToList();
            if (boardSpaceStrings.Count != Spaces.Count)
            {
                throw new ArgumentException("Board state string does not match the number of board spaces.");
            }
            for (int i = 0; i < boardSpaceStrings.Count; i++)
            {
                Spaces[i] = new BoardSpaceViewModel(boardSpaceStrings[i]);
            }
            OnPropertyChanged(nameof(Spaces));
        }
        public void DeclareVictory(String victoryString)
        {
            VictoryString = victoryString;
            OnPropertyChanged(nameof(VictoryString));
        }
        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
