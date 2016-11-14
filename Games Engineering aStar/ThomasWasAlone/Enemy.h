
#ifndef Enemy


#include <vector>
#include "GameObject.h"
#include "BasicTypes.h"
#include "Tiles.h"
#include <iostream>


/**define a box that is used to represent the wall and water*/


class Enemy
{
public:
	Enemy(int row, int col,int gridsize);
	Enemy();
	~Enemy();
	void Update(unsigned int deltaTime,  Tiles **t);
	void aStar(int targetRow,int targetCol,Tiles **t);
	void getAdjacent(Tiles ** t, int tileRow, int tileCol);
	void calculateFValues(std::vector<Tiles>& tilelist);
private:
	std::vector<Tiles> adjacentList;
	std::vector<Tiles> openList;
	std::vector<Tiles> closedList;
	std::vector<Tiles> Path;
	int currentRow;
	int currentCol;
	int lowestElement;
	int lowestRow;
	int targetROW;
	int targetCOL;
	int lowestCol;
	int gridSize;
	int  positionX;
	int  positionY;
	int targetPositionX;
	int targetPositionY;
	bool targetFound = false;
	int StartRow;
	int StartCol;
	int count = 0;
	int fCost = 10000000;

};
#endif