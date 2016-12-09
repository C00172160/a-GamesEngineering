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

	
	gridSize = num;
	
	

	 m_tiles = new Tiles*[gridSize];
	 for (int i = 0; i < gridSize; ++i)//initilize 2d array
	 {
		 m_tiles[i] = new Tiles[gridSize];
	 }

	 tileWidth = 20;//winSize.w / gridSize;//find the width of a tiles depending on how big the screen is
		 tileHeight = 20;// winSize.h / gridSize;
	//creates our renderer, which looks after drawing and the window
	
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
		Size2D winSize(200, 200);
		renderer.init(winSize, "Simple SDL App");
		CameraBounds = new Rect(0, 0, winSize.w,winSize.h);
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
		Size2D winSize(400, 400);
		renderer.init(winSize, "Simple SDL App");
		CameraBounds = new Rect(0, 0, winSize.w, winSize.h);
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
	else if (gridSize == 1000)
	{
		Size2D winSize(800, 800);
		renderer.init(winSize, "Simple SDL App");
		CameraBounds = new Rect(0, 0, winSize.w, winSize.h);
		int mm = 800;
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
	

	/*	std::thread t1(&Game::ThreadAstar, this, 0, MaxEnemies / 8);
		std::thread t2(&Game::ThreadAstar, this, MaxEnemies / 8, MaxEnemies / 8* 2);
		std::thread t3(&Game::ThreadAstar, this, MaxEnemies / 8 * 2, MaxEnemies / 8 * 3);
		std::thread t4(&Game::ThreadAstar, this, MaxEnemies / 8 * 3, MaxEnemies / 8 * 4);

		std::thread t5(&Game::ThreadAstar, this, MaxEnemies / 8 * 4, MaxEnemies / 8 * 5);
		std::thread t6(&Game::ThreadAstar, this, MaxEnemies / 8 * 5, MaxEnemies / 8 * 6);
		std::thread t7(&Game::ThreadAstar, this, MaxEnemies / 8 * 6, MaxEnemies / 8 * 7);
		std::thread t8(&Game::ThreadAstar, this, MaxEnemies / 8 * 7, MaxEnemies / 8);
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
		t7.join();
		t8.join();*/
	

	m_tiles[4][2].setFilled(true);
	m_tiles[4][3].setFilled(true);
	m_tiles[4][4].setFilled(true);
	m_tiles[4][5].setFilled(true);
	m_tiles[4][6].setFilled(true);
	m_tiles[4][7].setFilled(true);

	//aStar();
	
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
	
	

	for (int row = CameraBounds->pos.y; row < CameraBounds->size.w/tileHeight; row++)
	{

		for (int col = CameraBounds->pos.x; col < CameraBounds->size.w / tileWidth; col++)
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
		//aStar();
		//std::thread t1(&Game::ThreadAstar, this, 0, MaxEnemies / 8);
		//std::thread t2(&Game::ThreadAstar, this, MaxEnemies / 8, MaxEnemies / 8* 2);
		//std::thread t3(&Game::ThreadAstar, this, MaxEnemies / 8 * 2, MaxEnemies / 8 * 3);
		//std::thread t4(&Game::ThreadAstar, this, MaxEnemies / 8 * 3, MaxEnemies / 8 * 4);

		//std::thread t5(&Game::ThreadAstar, this, MaxEnemies / 8 * 4, MaxEnemies / 8 * 5);
		//std::thread t6(&Game::ThreadAstar, this, MaxEnemies / 8 * 5, MaxEnemies / 8 * 6);
		//std::thread t7(&Game::ThreadAstar, this, MaxEnemies / 8 * 6, MaxEnemies / 8 * 7);
		//std::thread t8(&Game::ThreadAstar, this, MaxEnemies / 8 * 7, MaxEnemies / 8);
		//t1.join();
		//t2.join();
		//t3.join();
		//t4.join();
		//t5.join();
		//t6.join();
		//t7.join();
		//t8.join();
	
		
	}
	if (evt == EventListener::Event::UP) {

		if (playerRow > 0 && m_tiles[playerRow - 1][playerCol].getFilled() == false)//only move up if you are not at top and there is an empty space above
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerRow--;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
		//aStar();

	}

	if (evt == EventListener::Event::DOWN) {

		if (playerRow < gridSize-1 && m_tiles[playerRow + 1][playerCol].getFilled() == false)
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerRow++;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
		//aStar();
	}

	if (evt == EventListener::Event::LEFT) {

		if (playerCol > 0  && m_tiles[playerRow ][playerCol -1].getFilled() == false)
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerCol--;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
		//aStar();
	}

	if (evt == EventListener::Event::RIGHT) {
		CameraBounds->pos.x++;
		/*if (playerCol < gridSize-1 && m_tiles[playerRow][playerCol + 1].getFilled() == false)
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerCol++;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}*/
		//aStar();
		
	}

}
