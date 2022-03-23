//
//  Blackjack.cpp
//  blackjack
//
//  Created by Rod Regado on 4/22/19.
//  Copyright © 2019 Rod Regado. All rights reserved.
//

#include "Blackjack.hpp"
#include <iostream>
#include <iomanip>
#include "CardDeck.hpp"
#include <vector>
using namespace std;
cardDeck Deck;
vector<card> playerHand;
vector<card> dealerHand;

//Constrcutor for the Blackjack object
Blackjack::Blackjack()
{
    srand( static_cast<unsigned int>(time(NULL)));
    playerValue = 500.00;
    dealerValue = 500.00;
}

//function that is the whole implementation for the blackjack game
void Blackjack::playGame()
{
    srand( static_cast<unsigned int>(time(NULL))); // uses computer's internal clock to control choice of see for continually changing seed
    playerHand.clear();
    dealerHand.clear();
    dealerhandSize = 0;
    playerhandSize = 0;
    dealerhandSum = 0;
    playerhandSum = 0;
    playerbetValue = 0;
    dealerbetValue = 0;
    pot = 0;
    playerDone = false;
    dealerDone = false;
    cout << "Welcome to Blackjack!\n";
    cout << endl;
    // Starts by asking for wagers between the player and dealer
    playerBet();
    dealerBet();
    // Displays the current pot: the sum of the player's and dealer's bets
    displayPot();
    // Shuffles the created deck
    Deck.shuffle();
    // Player and dealer with two cards
    addPlayerCard();
    addPlayerCard();
    addDealerCard();
    addDealerCard();
    // Prints the current hands of the player and dealer
    printHand();
    // Checks if player has a softhand
    softHand();
    // Adds the total value of the player's hand and Dealer's hand
    sumHands();
    // Asks if the player would like to double their bet
//    doubleDown();
    
    // Checks for naturals
    if (dealerhandSum == 21)
    {
        cout << "Dealer has blackjack. Dealer wins and house takes your wager!.\n";
        return;
    }
    else if (playerhandSum == 21 && dealerhandSum != 21)
    {
        cout << "You have blackjack. You are returned your own bet plus 3:2 of their bet!.\n";
        playerValue += (pot*1.5);
        return;
    }
    else if (playerhandSum == 21 && dealerhandSum == 21)
    {
        cout << "Push: Your wager is returned and no additional chips are rewarded!" << endl;
        playerValue += playerbetValue;
        return;
    }
    
    // After dealing the starting hand, player is prompt on whether they want to hit (get another card) or stand (stay with their current hand and pass their turn to the dealer)
    while (dealerDone == false || playerDone == false)
    {
        if (playerDone == false)
        {
            int option = 0;
            bool doubleD = false;
//            cout << "Would you like to hit? [Y] for Yes, [N] for No\n";
//            cout << "Enter: ";
//            cin >> playerhit;
//            while (playerhit != 'Y' && playerhit != 'N'){
//                cout << "Error! Invalid option" << endl;
//                cout << "Would you like to hit? [Y] for Yes, [N] for No\n";
//                cout << "Enter: ";
//                cin >> playerhit;
            cout << "-------------------" << endl;
            cout << "| Player Options  |" << endl;
            cout << "-------------------" << endl;
            cout << "| [1] Hit         |" << endl;
            cout << "| [2] Stand       |" << endl;
            cout << "| [3] Double Down |" << endl;
            cout << "| [4] Surrender   |" << endl;
            cout << "-------------------" << endl;
            cout << endl;
        label:
            cout << "Enter: ";
            cin >> option;
            switch(option){
                case 1:
                    addPlayerCard();
                    printHand();
                    sumHands();
                    if (playerhandSum > 21)
                    {
                        cout << "Player's hand exceeded 21. Player loses.\n";
                        return;
                    }
                    break;
                case 2:
                    playerDone = true;
                    break;
                case 3:
                    if (doubleD == false){
                    doubleDown();
                        doubleD = true;
                        cout << "What else would you like to do?" << endl;
                        goto label;
                    }
                    else
                    {
                        cout << "You've already doubled down!" << endl;
                        cout << "What else would you like to do?" << endl;
                        goto label;
                    }
                case 4:
                    surrender();
                    return;
                    break;
            }
//            if (playerhit == 'Y')
//            {
//                addPlayerCard();
//                printHand();
//                sumHands();
//
//                if (playerhandSum > 21)
//                {
//                    cout << "Player's hand exceeded 21. Player loses.\n";
//                    return;
//                }
//            }
//        }
        
//        if (playerDone == false)
//        {
//            cout << "Would you like to stand? [Y] for Yes, [N] for No\n";
//            cin >> playerstand;
//        }
//
//        if (playerstand == 'Y')
//        {
//            playerDone = true;
//        }
        }
        // Dealer must hit until they reach a hand with a sum greater than or equal to 17
        if (dealerhandSum < 17 && dealerDone != true)
        {
            addDealerCard();
            printHand();
            sumHands();
            // If dealer hits and gains a sum over 21, then they bust
            if (dealerhandSum > 21)
            {
                cout << "Bust: Dealer hand exceeded 21. Dealer loses.\n";
                cout << "Player gains the pot of: $" << pot << endl;
                playerValue += pot;
                return;
            }
        }
        // if Dealer reach 17 or more, then they stop their turn
        else if (dealerhandSum >= 17)
        {
            dealerDone = true;
        }
        // code that checks for pushes
        if (playerhandSum == 21 && dealerhandSum == 21)
        {
            cout << "Push: Player and dealer reached 21.\n";
            cout << "Wagers are returned";
            playerValue += playerbetValue;
            return;
        }
        // code that checks for player blackjack & pays pot to player
        else if (playerhandSum == 21)
        {
            cout << "Player reached 21. Player wins.\n";
            cout << "Player gains the pot of: $" << pot << endl;
            playerValue += pot;
            return;
        }
        // code that checks for dealer blackjack
        else if (dealerhandSum == 21)
        {
            cout << "Dealer reached 21. Dealer wins.\n";
            cout << "House takes your wager!" << endl;
            return;
        }
        
        //code that compares the hands of the player and dealer
        if ((playerDone == true && dealerDone == true) || (playerhandSize == 5 && playerhandSize == 5))
        {
            if (dealerhandSum < playerhandSum)
            {
                cout << "Sum of your hand exceeds the dealer's sum of " << dealerhandSum << "! You win!";
                cout << "You gain a pot of: $" << pot << endl;
                playerValue += pot;
                return;
            }
            else if (playerhandSum == dealerhandSum)
            {
                cout << "Push: Dealer hand sum is " << dealerhandSum << " and is equal to the sum of your hand. Wager is returned to you and no additional chips are awarded.";
                playerValue += playerbetValue;
                return;
            }
            else if (dealerhandSum > playerhandSum)
            {
                cout << "Sum of your hand is lower than the dealer's sum of " << dealerhandSum << ". You lose your wager to the house!";
                return;
            }
        }
    }
}


//function that adds a card object to the vector that is the player's hand
void Blackjack::addPlayerCard()
{
    if (playerhandSize <= 5)
    {
        playerHand.push_back(Deck.dealCard());
        playerhandSize++;
    }
    else
    {
        cout << "Sorry. You have reached the maximum number of cards (5)." << endl;
        playerDone = true;
    }
}
//function that adds a card object to the vector that is the dealer's hand
void Blackjack::addDealerCard()
{
    if (dealerhandSize <= 5)
    {
        dealerHand.push_back(Deck.dealCard());
        dealerhandSize++;
    }
    else
    {
        dealerDone = true;
    }
}

//fucntion that prints the hand of both the player and dealer
void Blackjack::printHand()
{
    cout << endl;
    cout << "Your current hand is...\n";
    
    for (int i = 0; i < playerhandSize; i++)
    {
        cout << "    -" << playerHand[i].print() << "-    \n\n";
    }
    
    cout << "Dealer's current hand is...\n";
    
    for (int j = 0; j < dealerhandSize; j++)
    {
        cout << "    -" << dealerHand[j].print() << "-    \n\n";
    }
}

//function that creates the value for each of the player's and dealer's hand
void Blackjack::sumHands()
{
    dealerhandSum = 0;
    playerhandSum = 0;
    for (int i = 0; i < playerhandSize; i++)
    {
        playerhandSum += playerHand[i].get_card_value();
    }
    
    for (int j = 0; j < dealerhandSize; j++)
    {
        dealerhandSum += dealerHand[j].get_card_value();
    }
    
    cout << "Current player hand sum is: " << playerhandSum << endl;
    cout << endl;
}

//function that allows the player to switch the value of their ace upon receiving it in the first hand
void Blackjack::softHand(){
    int option;
    for (int i = 0; i < playerHand.size(); i++){
        if (playerHand[i].get_card_value() == 1){
    cout << "For what value would you like to make your ace?" << endl;
    cout << "[1] for 1" << endl;
    cout << "[2] for 11" << endl;
    cout << "Enter: ";
    cin >> option;
    cout << endl;
    while (option != 1 && option != 2){
        cout << "Error! Invalid option" << endl;
        cout << "Enter: ";
        cin >> option;
        cout << endl;
            }
    if (option == 2){
        string f;
        string s;
        f = playerHand[i].get_card_face();
        s = playerHand[i].get_card_suit();
        playerHand.erase(playerHand.begin()+i);
        card Ace;
        Ace.set_card_value(11);
        Ace.set_card_face(f);
        Ace.set_card_suit(s);
        playerHand.push_back(Ace);
        
    }
        }
    }
}

//function that sets the player's money
void Blackjack::set_player_value(int value)
{
    playerValue = value;
}

//function that displays the pot of the game
void Blackjack::displayPot(){
    cout << "The current pot is: $" << pot << endl;
    cout << endl;
}

//function that allows the player to bet a specific type of chip and a certain amount
void Blackjack::playerBet()
{
    int option = 0;
    int width = 31;
    char choice;
    float chipValue;
    float chipAmount;
    if (playerValue > 1000){
        width -= 1;
    }
    cout << "--------------------------------------------------" << endl;
    cout << "| Player Bank: $" << playerValue << setw(width) << "|" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "| What kind of chip(s) would you like to put in? |" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "| [1] for white                                  |" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "| [2] for yellow                                 |" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "| [3] for red                                    |" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "| [4] for blue                                   |" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "| [5] for grey                                   |" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "| [6] for green                                  |" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "| [7] for orange                                 |" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "| [8] for black                                  |" << endl;
    cout << "--------------------------------------------------" << endl;
    
label:
    cout << "Enter: ";
    cin >> option;
    if (option >= 1 && option <= 8){
        if (option == 1 && playerValue < 1){
            cout << "Error! Invalid Funds" << endl;
            cout << "Your current bank is: $" << playerValue << endl;
            cout << "Please enter a valid bet!" << endl;
            cout << endl;
            goto label;
        }
        if (option == 2 && playerValue < 2){
            cout << "Error! Invalid Funds" << endl;
            cout << "Your current bank is: $" << playerValue << endl;
            cout << "Please enter a valid bet!" << endl;
            cout << endl;
            goto label;
        }
        if (option == 3 && playerValue < 5){
            cout << "Error! Invalid Funds" << endl;
            cout << "Your current bank is: $" << playerValue << endl;
            cout << "Please enter a valid bet!" << endl;
            cout << endl;
            goto label;
        }
        if (option == 4 && playerValue < 10){
            cout << "Error! Invalid Funds" << endl;
            cout << "Your current bank is: $" << playerValue << endl;
            cout << "Please enter a valid bet!" << endl;
            cout << endl;
            goto label;
        }
        if (option == 5 && playerValue < 20){
            cout << "Error! Invalid Funds" << endl;
            cout << "Your current bank is: $" << playerValue << endl;
            cout << "Please enter a valid bet!" << endl;
            cout << endl;
            goto label;
        }
        if (option == 6 && playerValue < 25){
            cout << "Error! Invalid Funds" << endl;
            cout << "Your current bank is: $" << playerValue << endl;
            cout << "Please enter a valid bet!" << endl;
            cout << endl;
            goto label;
        }
        if (option == 7 && playerValue < 50){
            cout << "Error! Invalid Funds" << endl;
            cout << "Your current bank is: $" << playerValue << endl;
            cout << "Please enter a valid bet!" << endl;
            cout << endl;
            goto label;
        }
        if (option == 8 && playerValue < 100){
            cout << "Error! Invalid Funds" << endl;
            cout << "Your current bank is: $" << playerValue << endl;
            cout << "Please enter a valid bet!" << endl;
            cout << endl;
            goto label;
        }
    }
    else
    {
        cout << "Invalid option!"<< endl;
        goto label;
    }
        
    switch (option){
        case 1:
        {
            chipValue = 1.00;
            cout << "How many white chips would you like to bet?" << endl;
            cout << "Enter: ";
            cin >> chipAmount;
            while ((chipAmount * chipValue) > playerValue){
                cout << "Error! Not enough funds to place this many chips!" << endl;
                cout << "Your current bank is: $" << playerValue << endl;
                cout << "Please enter a valid bet!" << endl;
                cout << "Enter: ";
                cin >> chipAmount;
            }
            cout << "You bet " << chipAmount << " white chip(s)" << endl;
            playerValue -= (chipAmount * chipValue);
            playerbetValue += (chipAmount * chipValue);
            pot += (chipAmount * chipValue);
            break;
    }
        case 2:
        {
            chipValue = 2.00;
            cout << "How many yellow chips would you like to bet?" << endl;
            cout << "Enter: ";
            cin >> chipAmount;
            while ((chipAmount * chipValue) > playerValue){
                cout << "Error! Not enough funds to place this many chips!" << endl;
                cout << "Your current bank is: $" << playerValue << endl;
                cout << "Please enter a valid bet!" << endl;
                cout << "Enter: ";
                cin >> chipAmount;
            }
            cout << "You bet " << chipAmount << " yellow chip(s)" << endl;
            playerValue -= (chipAmount * chipValue);
            playerbetValue += (chipAmount * chipValue);
            pot += (chipAmount * chipValue);
            break;
        }
        case 3:
        {
            chipValue = 5.00;
            cout << "How many red chips would you like to bet?" << endl;
            cout << "Enter: ";
            cin >> chipAmount;
            while ((chipAmount * chipValue) > playerValue){
                cout << "Error! Not enough funds to place this many chips!" << endl;
                cout << "Your current bank is: $" << playerValue << endl;
                cout << "Please enter a valid bet!" << endl;
                cout << "Enter: ";
                cin >> chipAmount;
            }
            cout << "You bet " << chipAmount << " red chip(s)" << endl;
            playerValue -= (chipAmount * chipValue);
            playerbetValue += (chipAmount * chipValue);
            pot += (chipAmount * chipValue);
            break;
        }
        case 4:
        {
            chipValue = 10.00;
            cout << "How many blue chips would you like to bet?" << endl;
            cout << "Enter: ";
            cin >> chipAmount;
            while ((chipAmount * chipValue) > playerValue){
                cout << "Error! Not enough funds to place this many chips!" << endl;
                cout << "Your current bank is: $" << playerValue << endl;
                cout << "Please enter a valid bet!" << endl;
                cout << "Enter: ";
                cin >> chipAmount;
            }
            cout << "You bet " << chipAmount << " blue chip(s)" << endl;
            playerValue -= (chipAmount * chipValue);
            playerbetValue += (chipAmount * chipValue);
            pot += (chipAmount * chipValue);
            break;
        }
        case 5:
        {
            chipValue = 20.00;
            cout << "How many grey chips would you like to bet?" << endl;
            cout << "Enter: ";
            cin >> chipAmount;
            while ((chipAmount * chipValue) > playerValue){
                cout << "Error! Not enough funds to place this many chips!" << endl;
                cout << "Your current bank is: $" << playerValue << endl;
                cout << "Please enter a valid bet!" << endl;
                cout << "Enter: ";
                cin >> chipAmount;
            }
            cout << "You bet " << chipAmount << " grey chip(s)" << endl;
            playerValue -= (chipAmount * chipValue);
            playerbetValue += (chipAmount * chipValue);
            pot += (chipAmount * chipValue);
            break;
        }
        case 6:
        {
            chipValue = 25.00;
            cout << "How many green chips would you like to bet?" << endl;
            cout << "Enter: ";
            cin >> chipAmount;
            while ((chipAmount * chipValue) > playerValue){
                cout << "Error! Not enough funds to place this many chips!" << endl;
                cout << "Your current bank is: $" << playerValue << endl;
                cout << "Please enter a valid bet!" << endl;
                cout << "Enter: ";
                cin >> chipAmount;
            }
            cout << "You bet " << chipAmount << " green chip(s)" << endl;
            playerValue -= (chipAmount * chipValue);
            playerbetValue += (chipAmount * chipValue);
            pot += (chipAmount * chipValue);
            break;
        }
        case 7:
        {
            chipValue = 50.00;
            cout << "How many orange chips would you like to bet?" << endl;
            cout << "Enter: ";
            cin >> chipAmount;
            while ((chipAmount * chipValue) > playerValue){
                cout << "Error! Not enough funds to place this many chips!" << endl;
                cout << "Your current bank is: $" << playerValue << endl;
                cout << "Please enter a valid bet!" << endl;
                cout << "Enter: ";
                cin >> chipAmount;
            }
            cout << "You bet " << chipAmount << " orange chip(s)" << endl;
            playerValue -= (chipAmount * chipValue);
            playerbetValue += (chipAmount * chipValue);
            pot += (chipAmount * chipValue);
            break;
    }
        case 8:
        {
            chipValue = 100.00;
            cout << "How many black chips would you like to bet?" << endl;
            cout << "Enter: ";
            cin >> chipAmount;
            while ((chipAmount * chipValue) > playerValue){
                cout << "Error! Not enough funds to place this many chips!" << endl;
                cout << "Your current bank is: $" << playerValue << endl;
                cout << "Please enter a valid bet!" << endl;
                cout << "Enter: ";
                cin >> chipAmount;
            }
            cout << "You bet " << chipAmount << " black chip(s)" << endl;
            playerValue -= (chipAmount * chipValue);
            playerbetValue += (chipAmount * chipValue);
            pot += (chipAmount * chipValue);
            break;
        }
    }
    cout << "Would you like to bet more chips? [Y] for yes, [N] for No" << endl;
    cout << "Your current bank is: $" << playerValue << endl;
    cout << "Enter: ";
    cin >> choice;
    cout << endl;
    while (choice != 'Y' && choice != 'N'){
        cout << "Error! Invalid option" << endl;
        cout << "Would you like to bet another chip? [Y] for Yes, [N] for No" << endl;
        cout << "Enter: ";
        cin >> choice;
        cout << endl;
    }
    if (choice == 'Y'){
        cout << endl;
        if (playerValue > 2){
           playerBet();
        }
        else
        {
            cout << "Not enough funds to place another bet!" << endl;
        }
    }
}

//function that randomly generates a bet for the dealer by the kind of chip and amount
void Blackjack::dealerBet()
{
    srand( static_cast<unsigned int>(time(NULL)));
    int option = rand() % 8 + 1;
    float chips = rand() % 3 + 1;
    switch (option){
        case 1:
            cout << "Dealer bets " << chips << " white chip(s)" << endl;
            dealerValue -= 1.00*chips;
            pot += 1.00*chips;
            break;
        case 2:
            cout << "Dealer bets " << chips << " yellow chip(s)" << endl;
            dealerValue -= 2.00*chips;
            pot += 2.00*chips;
            break;
        case 3:
            cout << "Dealer bets " << chips << " red chip(s)" << endl;
            dealerValue -= 5.00*chips;
            pot += 5.00*chips;
            break;
        case 4:
            cout << "Dealer bets " << chips << " blue chip(s)" << endl;
            dealerValue -= 10.00*chips;
            pot += 10.00*chips;
            break;
        case 5:
            cout << "Dealer bets " << chips << " grey chip(s)" << endl;
            dealerValue -= 20.00*chips;
            pot += 20.00*chips;
            break;
        case 6:
            cout << "Dealer bets " << chips << " green chip(s)" << endl;
            dealerValue -= 25.00*chips;
            pot += 25.00*chips;
            break;
        case 7:
            cout << "Dealer bets " << chips << " orange chip(s)" << endl;
            dealerValue -= 50.00;
            pot += 50.00*chips;
            break;
        case 8:
            cout << "Dealer bets " << chips << " black chip(s)" << endl;
            dealerValue -= 100.00*chips;
            pot += 100.00*chips;
            break;
    }
}

//function that allows player to double down on their bet8
void Blackjack::doubleDown(){
    char choice;
    cout << "Would you like to double down on your bet? [Y] for Yes, [N] for No" << endl;
    cout << "Enter: ";
    cin >> choice;
    while (choice != 'Y' && choice != 'N'){
        cout << "Error! Invalid option" << endl;
        cout << "Would you like to double down on your bet? [Y] for Yes, [N] for No" << endl;
        cout << "Enter: ";
        cin >> choice;
        cout << endl;
    }
    if (choice == 'Y'){
        if (playerbetValue > playerValue){
            cout << "Cannot double down, invalid funds!" << endl;
        }
        else
        {
            playerValue -= playerbetValue;
            playerbetValue *= 2;
            cout << "Your bet is now at $" << playerbetValue << endl;
            pot += playerbetValue;
        }
    }
}

//Function that ends the game and returns half of the bet to the player
void Blackjack::surrender(){
    cout << "You surrendered your hand!" << endl;
    cout << "1:2 of your bet is returned to you" << endl;
    playerValue += (playerbetValue / 2);
}
