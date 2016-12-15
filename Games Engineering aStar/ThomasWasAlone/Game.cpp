#include "stdafx.h"

#include <iostream>
using namespace std;


#include <SDL_thread.h>
#include "LTimer.h"
#include "Tiles.h"
#include "Game.h"


const int SCREEN_FPS = 100;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;




//std::queue<AStarData> Joblist;
//vector<Enemy>enemies;
//Tiles** m_tiles;
//SDL_mutex* jobListLock = SDL_CreateMutex();

Game::Game()
{
	pause = false;
	quit = false;
}


Game::~Game()
{
}

struct AStarData
{
	int index;
	int targetRow;
	int targetCol;
	bool valid = false;
};

 SDL_mutex* jobListLock = SDL_CreateMutex();
 SDL_sem *sem = SDL_CreateSemaphore(0);
 
 std::queue<AStarData> Joblist;
 vector<Enemy>enemies;
 Tiles** m_tiles;


 int  Game::threadFunction(void* data )
{
	while (true)
	{
		while (Joblist.size() == 0) {}; //stuck here until there is a job

	
		SDL_LockMutex(jobListLock);//lock this section.
		AStarData data; //got a job so take the one that is first
		if (Joblist.size() > 0)
		{
			SDL_SemWait(sem);
			data = Joblist.front();
			//cout << "hi" << endl;
			Joblist.pop(); //pop it 
		}
		SDL_UnlockMutex(jobListLock);
		//unlock

		//if data not empty/null/0
		if (data.valid == true)
		{
			enemies[data.index].aStar(data.targetRow, data.targetCol, m_tiles);//run astar
			
		}
	}
	return 0;
}


bool Game::init(int num) {	
	gridSize = num;
	
	maxThreads= thread::hardware_concurrency() - 1;

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

	if (gridSize == 30)
	{
		
		Size2D winSize(gridSize * tileWidth, gridSize *tileHeight);
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


	else if (gridSize == 100)
	{
		Size2D winSize(500,500);
		renderer.init(winSize, "Simple SDL App");
		CameraBounds = new Rect(0, 0, winSize.w, winSize.h);
		MaxEnemies = 50;

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
		MaxEnemies = 200;

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





	for (int i = 0; i < maxThreads; i++)
	{
		threads.push_back(SDL_CreateThread(threadFunction, "thread" + i, (void*)NULL));
	}
	for (int i = 0; i < MaxEnemies; i++)
	{
		addJob(i);
	}

	

	

	//SetupMap();	
	m_tiles[10][10].setFilled(true);
	m_tiles[10][9].setFilled(true);
	m_tiles[10][8].setFilled(true);
	m_tiles[10][7].setFilled(true);
	m_tiles[10][6].setFilled(true);
	m_tiles[10][5].setFilled(true);
	m_tiles[10][4].setFilled(true);
	m_tiles[10][3].setFilled(true);
	m_tiles[10][2].setFilled(true);
	m_tiles[10][1].setFilled(true);

	m_tiles[9][10].setFilled(true);
	m_tiles[8][10].setFilled(true);
	m_tiles[7][10].setFilled(true);
	m_tiles[6][10].setFilled(true);
	m_tiles[5][10].setFilled(true);
	m_tiles[4][10].setFilled(true);
	m_tiles[3][10].setFilled(true);
	m_tiles[2][10].setFilled(true);
	m_tiles[1][10].setFilled(true);

	//aStar();

	
	return true;

}

void Game::aStar()
{
	for (int i = 0; i < MaxEnemies; i++)
	{
		enemies[i].aStar(playerRow, playerCol, m_tiles);
	}
}
void Game::SetupMap()
{
	for (int row =0; row < gridSize; row++)
	{

		for (int col = 0; col <gridSize; col++)
		{
			if (row < gridSize /2  && col == gridSize /3)
			{
				m_tiles[row][col].setFilled(true);
			}

			if (row < gridSize / 2  && col == gridSize / 3 * 2)
			{
				m_tiles[row][col].setFilled(true);
			}

			if (row > gridSize / 2 && col == gridSize / 2 )
			{
				m_tiles[row][col].setFilled(true);
			}
		
		}
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
	 deltaTime = currentTime - lastTime;//time since last update


	lastTime = currentTime;
	for (int i = 0; i < MaxEnemies; i++)
	{
		enemies[i].Update(deltaTime, m_tiles);		
	}
	//MovePlayer();

	
	
}

void Game::updateArray()
{


}

//** calls render on all game entities*/

void Game::render()
{
		cameraOffsetX = CameraBounds->pos.x * tileWidth;
		cameraOffsetY = CameraBounds->pos.y * tileHeight;

		renderer.clear(Colour(0, 0, 0));// prepare for new frame



		for (int row = CameraBounds->pos.y; row < (CameraBounds->size.h / tileHeight) + CameraBounds->pos.y; row++)
		{

			for (int col = CameraBounds->pos.x; col < (CameraBounds->size.w / tileWidth) + CameraBounds->pos.x; col++)
			{
				m_tiles[row][col].Render(renderer, cameraOffsetX, cameraOffsetY);//only render tiles within camera bounds
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

void Game::MovePlayer()
{

	PlayerDelay += deltaTime;

	if (PlayerDelay > 100)
	{
		m_tiles[playerRow][playerCol].setPlayer(false);
		playerCol++;
		playerRow++;
		m_tiles[playerRow][playerCol].setPlayer(true);
		PlayerDelay = 0;
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

		
	
		
	}
	if (evt == EventListener::Event::UP) {

		if (CameraBounds->pos.y != 0)
		{ 
		CameraBounds->pos.y -= 1;
		}
	


	}

	if (evt == EventListener::Event::DOWN) {
		if (CameraBounds->pos.y < gridSize - (CameraBounds->size.w / tileHeight))
		{
			CameraBounds->pos.y += 1;
		}
	
		
	}

	if (evt == EventListener::Event::LEFT) {
		if (CameraBounds->pos.x != 0)
		{
			CameraBounds->pos.x -= 1;
		}
	}

		if (evt == EventListener::Event::RIGHT) {

			if (CameraBounds->pos.x < gridSize - (CameraBounds->size.w / tileWidth))
			{
				CameraBounds->pos.x += 1;
			}

			for (int i = 0; i < MaxEnemies; i++)
			{
				addJob(i);
			}


		}
	

	

}

void Game::addJob(int index )
{
	AStarData data;
	data.index = index;
	data.targetRow = playerRow;
	data.targetCol = playerCol;
	data.valid = true;

	SDL_LockMutex(jobListLock);
	Joblist.push(data);
	SDL_SemPost(sem);
	SDL_UnlockMutex(jobListLock);
	
}


