#include "stdafx.h"

#include <iostream>
using namespace std;



#include "LTimer.h"
#include "Tiles.h"
#include "Game.h"
#include <thread> 

const int SCREEN_FPS = 100;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


Game::Game()
{
	pause = false;
	quit = false;
}


Game::~Game()
{
}

void Game::ThreadAstar(int start, int end)
{

	for (int i = start; i < end; i++)
	{
		enemies[i].aStar(playerRow, playerCol, m_tiles);
	}

}


bool Game::init(int num) {	
	Size2D winSize(500,500);
	gridSize = num;

	 m_tiles = new Tiles*[gridSize];
	 for (int i = 0; i < gridSize; ++i)//initilize 2d array
	 {
		 m_tiles[i] = new Tiles[gridSize];
	 }

	tileWidth = winSize.w / gridSize;//find the width of a tiles depending on how big the screen is
	tileHeight = winSize.h / gridSize;
	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize,"Simple SDL App");
	lastTime = LTimer::gameTime();




	
	inputManager.AddListener(EventListener::Event::PAUSE, this);
	inputManager.AddListener(EventListener::Event::QUIT, this);
	inputManager.AddListener(EventListener::Event::UP, this);
	inputManager.AddListener(EventListener::Event::DOWN, this);
	inputManager.AddListener(EventListener::Event::LEFT, this);
	inputManager.AddListener(EventListener::Event::RIGHT, this);


	for (int row = 0; row < gridSize; row++)
	{

		for (int col = 0; col < gridSize; col++)
		{
			m_tiles[row][col] = Tiles(Rect((col * tileWidth) , (row * tileHeight), tileWidth, tileHeight),row,col);
		
		}
	}

	playerRow = 0;
	playerCol = 0;
	m_tiles[playerRow][playerCol].setPlayer(true);

	if (gridSize == 10)
	{
		MaxEnemies = 2;

		for (int i = 0; i < MaxEnemies; i++)
		{
			int row = rand() % (gridSize - 1) + 1;
			int col = rand() % (gridSize - 1) + 1;

			if (m_tiles[row][col].getEnemy()==false)
			{
				m_tiles[row][col].setEnemy(true);
				enemies.push_back(Enemy(row, col, gridSize));
			}
			else
			{
				MaxEnemies -= 1;
			}
		
		}
	
	}
	else if (gridSize == 20)
	{
		MaxEnemies = 4;

		for (int i = 0; i < MaxEnemies; i++)
		{
			int row = rand() % (gridSize - 1) + 1;
			int col = rand() % (gridSize - 1) + 1;
			if (m_tiles[row][col].getEnemy() == false)
			{
				m_tiles[row][col].setEnemy(true);
				enemies.push_back(Enemy(row, col, gridSize));
			}
			else
			{
				MaxEnemies -= 1;
			}
			
		}
		
	}
	else if (gridSize == 100)
	{
		int mm = 700;
		MaxEnemies = 0;

		for (int i = 0; i < mm; i++)
		{
			int row = rand() % (gridSize - 1) + 1;
			int col = rand() % (gridSize - 1) + 1;
			if (m_tiles[row][col].getEnemy() == false)
			{
				m_tiles[row][col].setEnemy(true);
				enemies.push_back(Enemy(row, col, gridSize));
				MaxEnemies++;
			}
			

		
		}
	
	}


	//std::thread t1(&Game::ThreadAstar, this, 0, 2);
	//std::thread t2(&Game::ThreadAstar, this, 2, 4);
	//t1.join();
	//t2.join();
	
	m_tiles[4][2].setFilled(true);
	m_tiles[4][3].setFilled(true);
	m_tiles[4][4].setFilled(true);
	m_tiles[4][5].setFilled(true);
	m_tiles[4][6].setFilled(true);
	m_tiles[4][7].setFilled(true);


	for (int i = 0; i < MaxEnemies; i++)
	{
		enemies[i].aStar(playerRow, playerCol, m_tiles);
	}
	
//	enemy1->aStar(playerRow, playerCol, m_tiles);
//	enemy2->aStar(playerRow, playerCol, m_tiles);
	return true;

}

void Game::aStar()
{
	for (int i = 0; i < MaxEnemies; i++)
	{
		enemies[i].aStar(playerRow, playerCol, m_tiles);
	}
}


void Game::destroy()
{
	
	
	renderer.destroy();
}

//** calls update on all game entities*/
void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	unsigned int deltaTime = currentTime - lastTime;//time since last update

	//enemy1->Update(deltaTime,playerRow,playerCol,m_tiles);
	//save the curent time for next frame
	lastTime = currentTime;
	for (int i = 0; i < MaxEnemies; i++)
	{
		enemies[i].Update(deltaTime, m_tiles);
	}
	/*enemy1->Update(deltaTime, m_tiles);
	enemy2->Update(deltaTime, m_tiles);*/
}

void Game::updateArray()
{


}

//** calls render on all game entities*/

void Game::render()
{
	renderer.clear(Colour(0,0,0));// prepare for new frame
	
	

	for (int row = 0; row < gridSize; row++)
	{

		for (int col = 0; col < gridSize; col++)
		{
			m_tiles[row][col].Render(renderer);
		}
	}

	renderer.present();// display the new frame (swap buffers)

	
}

/** update and render game entities*/
void Game::loop()
{
	
	LTimer capTimer;//to cap framerate

	int frameNum = 0;
	while (!quit) { //game loop
		capTimer.start();

		inputManager.ProcessInput();

		if(!pause) //in pause mode don't bother updateing
			update();
		render();

		int frameTicks = capTimer.getTicks();//time since start of frame
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time before going to next frame
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}

	
	}
}

void Game::onEvent(EventListener::Event evt) {

	if (evt == EventListener::Event::PAUSE) {
		pause = !pause;
	}
	
	if (evt == EventListener::Event::QUIT) {
		quit=true;
	}
	if (evt == EventListener::Event::UP||evt == EventListener::Event::DOWN||evt == EventListener::Event::LEFT||evt == EventListener::Event::RIGHT) {
		//enemy1->aStar(playerRow, playerCol, m_tiles);
		//enemy2->aStar(playerRow, playerCol, m_tiles);
	/*	std::thread t1(&Game::ThreadAstar, this, 0, 2);
		std::thread t2(&Game::ThreadAstar, this, 2, 4);
		t1.join();
		t2.join();*/
	
		
	}
	if (evt == EventListener::Event::UP) {

		if (playerRow > 0 && m_tiles[playerRow - 1][playerCol].getFilled() == false)//only move up if you are not at top and there is an empty space above
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerRow--;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
		aStar();

	}

	if (evt == EventListener::Event::DOWN) {

		if (playerRow < gridSize-1 && m_tiles[playerRow + 1][playerCol].getFilled() == false)
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerRow++;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
		aStar();
	}

	if (evt == EventListener::Event::LEFT) {

		if (playerCol > 0  && m_tiles[playerRow ][playerCol -1].getFilled() == false)
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerCol--;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
		aStar();
	}

	if (evt == EventListener::Event::RIGHT) {

		if (playerCol < gridSize-1 && m_tiles[playerRow][playerCol + 1].getFilled() == false)
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerCol++;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
		aStar();
		
	}

}
