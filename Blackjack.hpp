//
//  Blackjack.hpp
//  blackjack
//
//  Created by Rod Regado on 4/22/19.
//  Copyright © 2019 Rod Regado. All rights reserved.
//

#ifndef Blackjack_hpp
#define Blackjack_hpp

#pragma once


#include <string>

class Blackjack
{
private:
    //attributes for the Blackjack class
    int dealerhand[5];
    int playerhand[5];
    int dealerhandSize;
    int playerhandSize;
    int dealerhandSum;
    int playerhandSum;
    char playerhit;
    char playerstand;
    float playerValue;
    float dealerValue;
    float playerbetValue;
    float dealerbetValue;
    float pot;
public:
    //constructor
    Blackjack();
    
    //class methods
    void playGame();
    bool playerDone;
    bool dealerDone;
    void addPlayerCard();
    void addDealerCard();
    void printHand();
    void sumHands();
    void softHand();
    void playerBet();
    void dealerBet();
    void set_player_value(int value);
    void displayPot();
    void doubleDown();
    void surrender();
    float get_player_value();
};
#endif /* Blackjack_hpp */
