//John Hoffman IV

#include "Elevator.h"

int main()
{
	window w(800, 600, 0, 0);
	
	elev elevator(30);
	
	elevator.Operate(w);
	elevator.WaitNClear(w);
	return 0;
}

