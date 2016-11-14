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

void Enemy::Update(unsigned int deltaTime, int targetRow, int targetCol, Tiles ** t)
{
	


	//if (targetFound == false)
	//{
	//	StartRow = positionY;
	//	StartCol = positionX;
	//	getAdjacent(t, positionY, positionX, targetRow, targetCol);//finds all tiles adjacent
	//	fCost = 1000;
	//	for (int i = 0; i < openList.size(); i++)
	//	{
	//		if (openList[i].getFvalue() < fCost)
	//		{
	//			fCost = openList[i].getFvalue();
	//		}
	//	}
	//	for (int i = 0; i < openList.size(); i++)
	//	{
	//		if (openList[i].getFvalue() == fCost)
	//		{
	//			closedList.push_back(openList[i]);
	//			break;
	//		}
	//	}

	//}
	//targetPositionX = targetCol;
	//targetPositionY = targetRow;

	//getAdjacent(t, positionY, positionX);//finds all tiles adjacent
	//
	//
	//	int gCost = 0;
	//	int hCost = 0;
	//
	//	for (int i = 0; i < openList.size(); i++)
	//	{
	//		
	//		gCost = sqrt(  (openList[i].getRow() - positionY)*(openList[i].getRow() - positionY)  + (openList[i].getCol() - positionX)*(openList[i].getCol() - positionX));
	//		//gCost = sqrt(  (openList[i].getRow() - originalPosY)*(openList[i].getRow() - originalPosY)  + (openList[i].getCol() - originalPosX)*(openList[i].getCol() - originalPosX));
	//		//hCost = sqrt((openList[i].getRow() - targetRow)*(openList[i].getRow() - targetRow) + (openList[i].getCol() - targetCol)*(openList[i].getCol() - targetCol));// distance form tile to target
	//		hCost = ((targetRow - positionY) + (targetCol - positionX));
	//		if (t[openList[i].getRow()][openList[i].getCol()].getFilled() == true  )
	//		{
	//			hCost = 10000000;
	//		}
	//		
	//		

	//		if (hCost + gCost < fCost)
	//		{
	//			fCost = hCost + gCost;
	//			lowestRow = openList[i].getRow();
	//			lowestCol = openList[i].getCol();

	//		}

	//	}
	//	
	//	t[positionY][positionY].setEnemy(true);

	//	lastRow = positionY;
	//	lastCol = positionX;

	//	positionX = lowestCol;
	//	positionY = lowestRow;

	//	//t[lowestRow][lowestCol].setEnemy(true);
	//	openList.clear();
	//	
	//	
	//
	//
		
}

void Enemy::aStar(int targetRow, int targetCol, Tiles ** t)
{
	//targetCOL = targetCol;
	//targetROW = targetRow;
	//StartRow = positionY;
	//StartCol = positionX;
	//fCost = 100000000;

	//openList.push_back(Tiles(positionY, positionX, 0));//add the tile you are on to the open list


	//while (targetFound == false)
	//{
	//	
	//
	//	calculateFValues();//calculate all the f values of open list
	//	for (int i = 0; i < openList.size(); i++)//finf the lowest f value
	//	{
	//		if (openList[i].getFvalue() < fCost)
	//		{
	//			
	//			lowestRow = openList[i].getRow();
	//			lowestCol = openList[i].getCol();
	//			lowestElement = i;
	//			fCost = openList[i].getFvalue();
	//		}
	//	}

	//	//currentTile = openList[lowestRow, lowestCol];//make current tile equal to tile in the open list with the lowest value
	//	currentRow = lowestRow;
	//	currentCol = lowestCol;
	//	closedList.push_back(openList[lowestElement]);//add current tile to the closed list
	//	openList.erase(openList.begin() + lowestElement);//remove current from open list

	//	for (int i = 0; i < closedList.size(); i++)
	//	{
	//		if (closedList[i].getCol() == targetCOL && closedList[i].getRow() == targetROW)
	//		{
	//			targetFound = true;
	//		}
	//	}

	//	getAdjacent(t, currentRow, currentCol);

	//	for (int i = 0; i < adjacentList.size(); i++)
	//	{

	//		for (int j = 0; j < closedList.size(); j++)
	//		{
	//			if (adjacentList[i].getRow() == closedList[j].getRow() && adjacentList[i].getCol() == closedList[j].getCol())
	//			{
	//				continue;
	//			}
	//		}

	//		if (openList.size() == 0)
	//		{
	//			int h = (std::abs(adjacentList[i].getRow() - targetROW) + std::abs(adjacentList[i].getCol() - targetCOL));
	//			int g = (std::abs(adjacentList[i].getRow() - StartRow) + std::abs(adjacentList[i].getCol() - StartCol));
	//			adjacentList[i].setFvalue(h + g);
	//			openList.push_back(adjacentList[i]);
	//		}
	//		for (int j = 0; j < openList.size(); j++)
	//		{
	//			if (adjacentList[i].getRow() != openList[j].getRow() && adjacentList[i].getCol() != openList[j].getCol())
	//			{
	//				int h = (std::abs(adjacentList[i].getRow() - targetROW) + std::abs(adjacentList[i].getCol() - targetCOL));
	//				int g = (std::abs(adjacentList[i].getRow() - StartRow) + std::abs(adjacentList[i].getCol() - StartCol));
	//				adjacentList[i].setFvalue(h + g);
	//				openList.push_back(adjacentList[i]);
	//			}
	//	
	//		
	//		}


	//	}


	//}while (openList.size() > 0);

	//int i = 0;

}

void Enemy::getAdjacent(Tiles ** t, int tileRow, int tileCol)
{
	

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
		if (adjacentList[i].getFilled() == true || adjacentList[i].getEnemy() == true )//only check viable tiles.
		{
			adjacentList.erase(adjacentList.begin() + i);
		
		}	

		/*for (int j = 0; j < closedList.size(); j++)
		{
			if (adjacentList[i].getRow() == closedList[j].getRow() && adjacentList[i].getCol() == closedList[j].getCol())
			{
				adjacentList.erase(adjacentList.begin() + i);
			}
		}*/

	}
	//x-tarx + y - tarY
	/*for (int i = 0; i < adjacentList.size(); i++)
	{
		
	
		openList.push_back(adjacentList[i]);
	}*/

	
	//adjacentList.clear();
}

void Enemy::calculateFValues()
{
	for (int i = 0; i < openList.size(); i++)
	{
		int h = (std::abs(openList[i].getRow() - targetROW) + std::abs(openList[i].getCol() - targetCOL));
		int g = (std::abs(openList[i].getRow() - StartRow) + std::abs(openList[i].getCol() - StartCol));
		openList[i].setFvalue(h + g);
	}
}
	
		








