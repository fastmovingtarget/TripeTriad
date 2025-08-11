using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TripeTriadUI
{
    public class CardViewModel : INotifyPropertyChanged
    {
        public char Top { get; }// these should never be set, only read
        public char Left { get; }
        public char Right { get; }
        public char Bottom { get; }
        public String Index { get; }
        public String Print { get; }
        public String Colour { get; set; }
        public event PropertyChangedEventHandler? PropertyChanged;
        public CardViewModel(String cardState, String colour = "LightGray", int index = -1)
        {
            Top = cardState[0];
            Left = cardState[1];
            Right = cardState[2];
            Bottom = cardState[3];
            Print = $"     {Top}\n{Left}         {Right}\n     {Bottom}";
            Index=index.ToString();
            if(cardState.Length == 4)
                Colour = colour;
            else
                Colour = "SandyBrown"; // Colour for selected computer card
        }
        public void setColour(String newColour)
        {
            Colour = newColour;
            OnPropertyChanged(nameof(Colour));
        }
        protected void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

    }
}
