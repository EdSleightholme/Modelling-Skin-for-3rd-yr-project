#include "Cell.h"



Cell::Cell()
{
}

void Cell::setType(int toSet)
{
	type = toSet;
}

int Cell::getType()
{
	return type;
}

int Cell::getSplitType()
{
	return splitType;
}

void Cell::changeToDead()
{
	type = 2;
	splitType = -1;
	tillLift = 10;
}

void Cell::changeToAlive()
{
	type = 1;
	splitType =rand()%4;
	tillLift = 10;
}

void Cell::changetoEmpty()
{
	type = 0;
	splitType = -1;
}

bool Cell::countDown()
{
	if (tillLift != 0) {
		tillLift--;
		return false;
	}
	return true;
}
