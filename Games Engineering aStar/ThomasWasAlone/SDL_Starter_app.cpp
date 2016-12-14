//  Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
using namespace std;
#include "Game.h"


/**Create and initialises an instance of game, and clean up when the game is closed*/

int main()
{
	int num;
	int size;
	Game game;

	cout << "Initialising Game" << endl;

	cout << "Select Grid Size" << endl;
	cout << "1 = 30x30" << endl;
	cout << "2 = 100x100" << endl;
	cout << "3 = 1000x1000" << endl;
	
	cin >> num;
	
	if (num == 1)
	{
		size = 30;
	}
	else if (num == 2)
	{
		size = 100;
	}
	if (num == 3)
	{
		size = 1000;
	}
	
	if (num != 1&& num != 2&& num != 3 && num != 4)
	{
		cout << " invalid number not accepted. defaulting to 10x10";
		size = 10;
	}


	if (!game.init(size)) {
		cout << "Failed to init game"<<'\n';
	}

	//run the game loop
	game.loop();

	game.destroy();

    return 0;
}

