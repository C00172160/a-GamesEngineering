#pragma once

#include <vector>

#include "Renderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "EventListener.h"
#include "Tiles.h"
#include <thread>
#include "Enemy.h"
#include <queue>

/** The game objct whic manages the game loop*/
class Game:public EventListener
{
	

	

	InputManager inputManager;
	Renderer renderer;
	
	std::vector<GameObject*> gameObjects;
	unsigned int lastTime;//time of last update;
	int gridSize = 100;
	int playerRow;
	int playerCol;
	int tileWidth;
	int tileHeight;
	bool pause;
	bool quit;
	int MaxEnemies;
	
	Rect* CameraBounds;
	float cameraOffsetX;
	float cameraOffsetY;

	unsigned int deltaTime;
	float PlayerDelay;
	int maxThreads;
	
public:
	Game();
	~Game();
	bool init(int num);
	void aStar();
	void SetupMap();
	void destroy();
	void update();
	void updateArray();
	void render();
	void loop();
	void MovePlayer();
	void onEvent(EventListener::Event);
	void addJob(int index);
	static int  threadFunction(void* data);
	std::vector<SDL_Thread*> threads;

	
};

