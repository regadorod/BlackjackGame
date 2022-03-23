//
//  main.cpp
//  blackjack
//
//  Created by Rod Regado on 4/22/19.
//  Copyright © 2019 Rod Regado. All rights reserved.
//

#include <iostream>
#include "Blackjack.hpp"
using namespace std;
    
    int main()
    {
        
        char exitGame = 'Y';
        Blackjack BlackJack;
        do
        {
            BlackJack.playGame();
            cout << "\nWould you like to play again? [Y] Yes [N] No\n";
            cout << "Enter: ";
            cin >> exitGame;
        }while (exitGame == 'Y');
        cout << "\nThanks for playing!\n";
        return 0;
}
