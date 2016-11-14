#include "stdafx.h"

#include <iostream>
using namespace std;



#include "LTimer.h"
#include "Tiles.h"
#include "Game.h"


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


bool Game::init() {	
	Size2D winSize(800,600);

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

	enemy1 = new Enemy(9,8,gridSize);
	enemy1->aStar(playerRow, playerCol, m_tiles);
	m_tiles[9][8].setEnemy(true);
	m_tiles[4][1].setFilled(true);
	m_tiles[4][2].setFilled(true);
	m_tiles[4][3].setFilled(true);
	m_tiles[4][4].setFilled(true);
	m_tiles[4][5].setFilled(true);
	m_tiles[4][6].setFilled(true);
	m_tiles[4][7].setFilled(true);
	m_tiles[4][8].setFilled(true);

	return true;

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
	if (evt == EventListener::Event::UP) {

		if (playerRow > 0 && m_tiles[playerRow - 1][playerCol].getFilled() == false)//only move up if you are not at top and there is an empty space above
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerRow--;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
	}

	if (evt == EventListener::Event::DOWN) {

		if (playerRow < gridSize-1 && m_tiles[playerRow + 1][playerCol].getFilled() == false)
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerRow++;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
	}

	if (evt == EventListener::Event::LEFT) {

		if (playerCol > 0  && m_tiles[playerRow ][playerCol -1].getFilled() == false)
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerCol--;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
	}

	if (evt == EventListener::Event::RIGHT) {

		if (playerCol < gridSize-1 && m_tiles[playerRow][playerCol + 1].getFilled() == false)
		{
			m_tiles[playerRow][playerCol].setPlayer(false);
			playerCol++;
			m_tiles[playerRow][playerCol].setPlayer(true);
		}
		
	}

}
