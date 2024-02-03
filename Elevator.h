//John Hoffman IV
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "CMUgraphicsLib\CMUgraphics.h"
#include "CMUgraphicsLib\auxil.h"
#include <iostream>
#include <sstream>
#include <cmath>



class elev
{
public:
	
	elev(int floors);
	elev(int bottom, int top);

	Operate(window &w);
	WaitNClear(window &inputWindow);
	FloorNumbers(window &w);
	OpenDoors(window &w);
	CloseDoors(window &w);
	Drawmyfloor(window &w);
	BringUp(window &w);
	BringDown(window &w);
	DrawOut(window &w);
	DrawIn(window &w);
	int ClickArrow(window &w);
	DrawButton(window &w,int x,int y,int n);
	InNums(window &w);
	CloseInDoor(window &w);
	ClickButton(window &w);
	int FindRow(int iY);
	int FindCol(int iX);
	OpenInDoor(window &w);
	

private:

	int myFloor;
	int curFloor;
	int numFloors;
};

#endif
