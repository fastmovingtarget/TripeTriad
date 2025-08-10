# TripeTriad
This implementation Triple Triad is inspired by the minigame within Final Fantasy 8, owned by Square Enix. There is no capacity for monetisation within this project.

## Aims and targets
### MVP
  - Implementation of basic rules within a c++ library.
  - Barebones C# GUI linked to c++ game state management.
### MS1
  - Implement a roguelike deckbuilder structure where the player plays varying AI and swaps a card for the AI's when they win.
  - Allow differing rulesets (open/closed hand, PLUS, SAME, CASCADE)
### MS2
  - Implement roguelike style buffs that the player can select from.
  - Allow movement on an overworld map to challenge AI "Players".

# The Basic Rules
- Triple Triad is played on a 3x3 grid.
- Each player is given 5 cards.
- Whether in their hand or on the board, a player's cards are controlled by them until flipped.
- The first player to place a card is random.
- Each player takes turns to place a card on the grid.
  - Players MUST place a card during their turn.
- Each card has 4 values, up, left, down and right.
- Placing a card on the board compares the values of ALL the orthogonally adjacent cards.
  - If the adjacent space is empty or the placing player owns that card, the card is placed and there is no further change.
  - If the adjacent space is owned by the opposing player, the values of the adjacent edges are compared.
    - If the placed card's value is greater than the adjacent value on an existing card, the existing card flips to the player's ownership.
    - If the placed card's value is less than the adjacent value on an existing card, the existing card does not change.
- Play continues until all board spaces are taken.
## Optional Rules:
- Open (default) - the visibility of the opponent's hand. If open is not set, the opponent's hand is not visible.
- Same - When a card is played, its side values are compared to the cards around it. If the more than one side value is the SAME as the corresponding values of the cards next to it, flip those spaces to the user's control.
- Plus - When a card is played, its side values are compared to the cards around it. Add the side values of the card to the corresponding values of the cards next to it. If more than one side adds to the same total, flip those spaces to the user's control.
- Wall - For comparing values for PLUS and SAME, spaces outside the Tripe Triad board are counted as 0.

# Status:
- Basic Gameplay is now complete.
- Basic AI implementation is now complete.
- Able to play with different rulesets.
## Next Steps:
- Add an options menu to change the current ruleset to the UI.
