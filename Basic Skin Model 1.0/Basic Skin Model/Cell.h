#include <stdlib.h>
#include <stdio.h>

#pragma once
class Cell
{
public:
	Cell();
	void setType(int toSet);
	int getType();
	int getSplitType();
	void changeToDead();
	void changeToAlive();
	void changetoEmpty();
	bool countDown();
private:
	/*	
	0 = empty 
	1 = alive
	2 = dead
	*/
	int type = 0;
	/*
	0 = (Dead,Dead)
	1 = (Alive,Dead)
	2 = (Dead,Alive)
	3 = (Alive,Alive)
	*/
	int splitType = 0;

	//Turns until dead cell lifts from grid
	int tillLift = 0;

};

