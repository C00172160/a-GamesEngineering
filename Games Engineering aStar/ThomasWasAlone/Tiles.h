#include "BasicTypes.h"
#include "GameObject.h"
#pragma once

class Tiles
{
public:
	Tiles(Rect rectangle, int row, int col);
	Tiles( int row, int col, int f);
	Tiles();
	~Tiles();

	void Render(Renderer & renderer, float cameraOffsetX, float cameraOffsetY);

	
	
	void Update(unsigned int deltaTime);

	Rect getRectangle();
	Colour getColour();

	bool getPlayer();
	bool getEnemy();
	int getRow();
	int getCol();
	bool getFilled();
	int getFvalue();
	void setParent(int row, int col);
	void setPlayer(bool b);
	void setEnemy(bool b);
	void setFilled(bool b);
	void setFvalue(int f);

	void setColour(int r, int g, int b, int a);


private:
	Rect rect;
	Colour *col;
	int gridRow, gridCol;
	bool player;
	bool enemy;
	bool filled;
	int fValue;
	int parentROW, parentCOL;
};

