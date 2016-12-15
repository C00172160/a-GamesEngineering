#include "stdafx.h"
#include "Enemy.h"
#include "Tiles.h"
#include <iostream>





	

Enemy::Enemy(int row, int col, int gridsize)
{
	positionX = col;
	positionY = row;
	///originalPosX = col;
	//originalPosY = row;
	gridSize = gridsize;

}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(unsigned int deltaTime,  Tiles ** t)
{

	
	if (Path.size() > 0)
	{
	
		count += deltaTime;

		if (count > 2)// && t[Path[0].getRow()][Path[0].getCol()].getEnemy() == false //) targetFound == true)
		{

			t[positionY][positionX].setEnemy(false);

			positionY = Path[0].getRow();
			positionX = Path[0].getCol();

			t[positionY][positionX].setEnemy(true);
			Path.erase(Path.begin());
			count = 0;
		}

		
		
	}
	

	
	

	


}

void Enemy::aStar(int targetRow, int targetCol, Tiles ** t)
{

	Path.clear();
	targetCOL = targetCol;
	targetROW = targetRow;
	StartRow = positionY;
	StartCol = positionX;
	
	targetFound = false;
	fCost = 100000;
	openList.clear();
	int  Loopcount = 0;
	currentRow = StartRow;
	currentCol = StartCol;

	openList.push_back(&t[StartRow][StartCol]);//add first node to open list
	calculateFValues(openList);

	while (targetFound == false)
	{		
		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i]->getFvalue() < fCost)
			{
				fCost = openList[i]->getFvalue();
				closedList.push_back(openList[i]);			
				currentRow = openList[i]->getRow();
				currentCol = openList[i]->getCol();
				Path.push_back(t[currentRow][currentCol]);
				openList.clear();
			}
	   }
		
		getAdjacent(t, currentRow, currentCol);
		for (int i = 0; i < closedList.size(); i++)
		{
			for (int j = 0; j < openList.size(); j++)
			{
				if (closedList[i]->getRow() == openList[j]->getRow()  && closedList[i]->getCol() == openList[j]->getCol())
				{
					openList.erase(openList.begin() + j);
				}
			}
		}
		calculateFValues(openList);
	
		if (currentRow == targetROW && currentCol == targetCOL)
		{
			targetFound = true;
		}

		
		if (openList.size() >= 400)
		{
			targetFound = true;
		}

	}

	

}

void Enemy::getAdjacent(Tiles ** t, int tileRow, int tileCol)
{


	adjacentList.clear();
	if (tileRow > 0 && tileCol >0)///
	adjacentList.push_back(new Tiles(tileRow-1,tileCol-1,0));//only check the tiles around yourself so you are not checking the whole array///
	if (tileRow >0)
	adjacentList.push_back(new Tiles(tileRow - 1, tileCol, 0));
	if (tileRow>0 && tileCol < gridSize -1)//
	adjacentList.push_back(new Tiles(tileRow - 1, tileCol +1 , 0));//
	if (tileCol >0)
	adjacentList.push_back(new Tiles(tileRow , tileCol - 1, 0));
	if (tileCol < gridSize -1)
	adjacentList.push_back(new Tiles(tileRow , tileCol +1, 0));
	if (tileRow < gridSize -1 && tileCol > 0)//
	adjacentList.push_back(new Tiles(tileRow + 1, tileCol - 1, 0));//
	if (tileRow < gridSize -1)
	adjacentList.push_back(new Tiles(tileRow + 1, tileCol, 0));
	if (tileRow < gridSize -1 && tileCol < gridSize -1)//
	adjacentList.push_back(new Tiles(tileRow +1, tileCol + 1, 0));//

	

	for (int i = 0; i < adjacentList.size(); i++)
	{	
		int row = adjacentList[i]->getRow();
		int col = adjacentList[i]->getCol();

				if (t[row][col].getFilled() == false)
				{
					adjacentList[i]->setParent(row, col);
					openList.push_back(adjacentList[i]);
				}

	
	}
	

	
}

void Enemy::calculateFValues(std::vector<Tiles*>& tilelist)
{
	for (int i = 0; i < tilelist.size(); i++)
	{

		/*int gvalue = (StartRow - tilelist[i]->getRow()) + ( StartCol - tilelist[i]->getCol());
		gvalue = abs(gvalue);*/
		int hvalue = (targetROW - tilelist[i]->getRow()) + (targetCOL - tilelist[i]->getCol());
		hvalue = abs(hvalue);
		tilelist[i]->setFvalue(hvalue + gValue);
	}
}




	
		








