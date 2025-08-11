using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TripeTriadUI
{
    public class PlayerViewModel : INotifyPropertyChanged
    {
        public bool inputEnabled { get; set; } = true; // This is used to prevent input during the opponent's turn
        public String Name { get; }
        public String Colour { get; set; } // This could be used to set the color of the player in the UI
        public int Score { get; set; } = 0; // This could be used to track the player's score
        public List<CardViewModel> Hand { get; set; }
        public void setInputEnabled(bool locked){
            inputEnabled = locked;
            OnPropertyChanged(nameof(inputEnabled));
        }

        public event PropertyChangedEventHandler? PropertyChanged;

        public PlayerViewModel(String name, List<CardViewModel> hand, String colour)
        {
            Name = name;
            Hand = hand;

            Colour = colour;
        }
        public PlayerViewModel(String name, String handString, String colour)
        {
            Name = name;
            Colour = colour;
            Hand = handString.Split(',').Select(
                    (card, index) => new CardViewModel(card, Colour, index)
                ).ToList();

        }
        public void Update(List<CardViewModel> inputHand)
        {
            Hand = inputHand;
            OnPropertyChanged(nameof(Hand));
        }
        public void Update(String inputHandString, int score)
        {
            if (String.IsNullOrEmpty(inputHandString))
                EmptyHand();
            else
                Hand = inputHandString.Split(',').Select((card, index) => new CardViewModel(card, Colour, index)).ToList();

            Score = score;
            OnPropertyChanged(nameof(Hand));
            OnPropertyChanged(nameof(Score));
        }
        public void SelectCard(int newSelectedindex, int oldSelectedIndex)
        {
            // If the new index is the same as the old index, do nothing
            if (newSelectedindex == oldSelectedIndex)
                return;
            if(oldSelectedIndex >= 0)//If there was a previously selected card, reset its color
                Hand[oldSelectedIndex].setColour("CornflowerBlue");
            
            Hand[newSelectedindex].setColour("DodgerBlue");//this can only be done by the player, so we can set the color to a blue highlight colour
        }
        public void EmptyHand()
        {
            Hand = new List<CardViewModel>();
        }
        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
