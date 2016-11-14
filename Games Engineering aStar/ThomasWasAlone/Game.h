#pragma once

#include <vector>

#include "Renderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "EventListener.h"
#include "Tiles.h"
#include "Enemy.h"

/** The game objct whic manages the game loop*/
class Game:public EventListener
{
	InputManager inputManager;
	Renderer renderer;

	std::vector<GameObject*> gameObjects;
	unsigned int lastTime;//time of last update;
	int gridSize = 10;
	Tiles** m_tiles;
	int playerRow;
	int playerCol;
	int tileWidth;
	int tileHeight;
	bool pause;
	bool quit;
	Enemy *enemy1;

public:
	Game();
	~Game();

	bool init();
	void destroy();

	void update();
	void updateArray();
	void render();
	void loop();

	void onEvent(EventListener::Event);
};

