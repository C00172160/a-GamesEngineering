#include "stdafx.h"
#include "Tiles.h"


Tiles::Tiles(Rect rectangle,int row, int col)
{
	rect = rectangle;
	gridRow = row;
	gridCol = col;
	player = false;
	enemy = false;
	filled = false;
}

Tiles::Tiles(int row, int col, int f)
{
	gridRow = row;
	gridCol = col;
	fValue = f;
	player = false;
	enemy = false;
	filled = false;
}

Tiles::Tiles()
{
}

Tiles::~Tiles()
{
}

void Tiles::Render(Renderer & renderer)
{
	if (player == false && filled == false && enemy == false)
	{
		col = new Colour(255, 255, 255, 255);
		renderer.drawRect(rect, *col);
	}
	else if (player == true && filled == false && enemy == false)
	{
		col = new Colour(0, 0, 255, 255);
		renderer.drawFilledRect(rect, *col);
	}
	else if (player == false && filled == false && enemy == true)
	{
		col = new Colour(255, 0, 0, 255);
		renderer.drawFilledRect(rect, *col);
	}
	else if (player == false && filled == true && enemy == false)
	{
		col = new Colour(255, 255, 255, 255);
		renderer.drawFilledRect(rect, *col);
	}

}



Rect Tiles::getRectangle()
{
	return rect;
}

Colour Tiles::getColour()
{
	return *col;
}

bool Tiles::getPlayer()
{
	return player;
}

bool Tiles::getEnemy()
{
	return enemy;
}
int Tiles::getRow()
{
	return gridRow;
}
int Tiles::getCol()
{
	return gridCol;
}
bool Tiles::getFilled()
{
	return filled;
}

int Tiles::getFvalue()
{
	return fValue;
}

void Tiles::setPlayer(bool b)
{
	player = b;
}

void Tiles::setEnemy(bool b)
{
	enemy = b;
}

void Tiles::setFilled(bool b)
{
	filled = b;
}

void Tiles::setFvalue(int f)
{
	fValue = f;
}

void Tiles::setColour(int r, int g, int b, int a)
{
	col = new Colour(r, g, b, a);
}



