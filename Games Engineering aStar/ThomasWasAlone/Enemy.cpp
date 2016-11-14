#include "stdafx.h"
#include "Enemy.h"
#include "Tiles.h"






	

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

		if (count > 30)
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

	targetCOL = targetCol;
	targetROW = targetRow;
	StartRow = positionY;
	StartCol = positionX;
	targetFound = false;
	Path.clear();
	while (targetFound == false)
	{
		
		fCost = 1000;


		openList.push_back(Tiles(StartRow, StartCol, 0));//add first node to open list
		getAdjacent(t, StartRow, StartCol);
		//t[StartRow][StartCol].setEnemy(true);
		Path.push_back(Tiles(StartRow, StartCol, 0));

		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i].getRow() == StartRow  && openList[i].getCol() == StartCol)
			{
				openList.erase(openList.begin() + i);
			}
		}

		calculateFValues(openList);
		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i].getFvalue() < fCost)
			{
				StartRow = openList[i].getRow();
				StartCol = openList[i].getCol();
				fCost = openList[i].getFvalue();
			}
		}

		openList.clear();


		if (targetROW == StartRow && targetCOL == StartCol)
		{
			targetFound = true;
		}


	}
	
	/*std::reverse(Path.begin(), Path.end());
	int i = 0;*/

	

}

void Enemy::getAdjacent(Tiles ** t, int tileRow, int tileCol)
{
	adjacentList.clear();

	if (tileRow > 0 && tileCol >0)
	adjacentList.push_back(Tiles(tileRow-1,tileCol-1,0));//only check the tiles around yourself so you are not checking the whole array
	if (tileRow >0)
	adjacentList.push_back(Tiles(tileRow - 1, tileCol, 0));
	if (tileRow>0 && tileCol < gridSize -1)
	adjacentList.push_back(Tiles(tileRow - 1, tileCol +1 , 0));
	if (tileCol >0)
	adjacentList.push_back(Tiles(tileRow , tileCol - 1, 0));
	if (tileCol < gridSize -1)
	adjacentList.push_back(Tiles(tileRow , tileCol +1, 0));
	if (tileRow < gridSize -1 && tileCol > 0)
	adjacentList.push_back(Tiles(tileRow + 1, tileCol - 1, 0));
	if (tileRow < gridSize -1)
	adjacentList.push_back(Tiles(tileRow + 1, tileCol, 0));
	if (tileRow < gridSize -1 && tileCol < gridSize -1)
	adjacentList.push_back(Tiles(tileRow +1, tileCol + 1, 0));

	for (int i = 0; i < adjacentList.size(); i++)
	{
		//if (adjacentList[i].getFilled() == true || adjacentList[i].getEnemy() == true )//only check viable tiles.
		//{
		//	adjacentList.erase(adjacentList.begin() + i);
		//	continue;
		//}	

		
		openList.push_back(Tiles(adjacentList[i].getRow(),adjacentList[i].getCol(),0));

	}
	
}

void Enemy::calculateFValues(std::vector<Tiles>& tilelist)
{
	for (int i = 0; i < tilelist.size(); i++)
	{
		//int h = (std::abs(tilelist[i].getRow() - targetROW) + std::abs(tilelist[i].getCol() - targetCOL));
		int h = sqrt((tilelist[i].getRow() - targetROW)*(tilelist[i].getRow() - targetROW) + (tilelist[i].getCol() - targetCOL)*(tilelist[i].getCol() - targetCOL));
		int g = (std::abs(tilelist[i].getRow() - StartRow) + std::abs(tilelist[i].getCol() - StartCol));
		tilelist[i].setFvalue(h + g);
	}
}


	
		








