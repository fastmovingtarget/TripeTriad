using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TripeTriadUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

        }
        private void cardButton_Click(object sender, RoutedEventArgs e)
        {
            if(sender == null)
                return;
            
            // Handle card button click event
            Button clickedButton = sender as Button;
            if (clickedButton != null)
            {
                TTViewModel viewModel = this.DataContext as TTViewModel;
                if(viewModel == null || !viewModel.PlayerViewModel.inputEnabled)
                    return;

                viewModel.SelectCard(
                    int.Parse(clickedButton.Tag.ToString())
                );
            }
        }
        private void boardButton_Click(object sender, RoutedEventArgs e)
        {
            if (sender == null)
                return;

            // Handle card button click event
            Button clickedButton = sender as Button;
            if (clickedButton != null)
            {
                TTViewModel viewModel = DataContext as TTViewModel;
                if (viewModel == null || viewModel.SelectedCardIndex == -1)
                    return;

                viewModel.PlayCard(
                    int.Parse(clickedButton.Tag.ToString()) - 1
                );
            }
        }

        private void newGameButton_Click(object sender, RoutedEventArgs e)
        {
            TTViewModel viewModel = DataContext as TTViewModel;
            if (viewModel != null)
            {
                viewModel.Reset();
            }
        }

        private void newRulesButton_Click(object sender, RoutedEventArgs e)
        {
            TTViewModel viewModel = DataContext as TTViewModel;
            if (viewModel != null)
            {
                viewModel.SubmitRules();
            }
        }
    }
}