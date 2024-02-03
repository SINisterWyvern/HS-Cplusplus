#include "Elevator.h"


elev:: elev(int floors)
{
	myFloor=1;
	numFloors=floors;
	curFloor=numFloors/2;
	if(numFloors>20)
		numFloors=20;
}

elev:: Operate(window &w)
{
	int exit=1;
	while(exit!=0)
	{
		DrawOut(w);
		exit=ClickArrow(w);
		if(exit!=0)
		{
			Pause(2000);
			DrawIn(w);
			ClickButton(w);
		}
	}
}

elev:: FloorNumbers(window &w)
{
	w.SetPen(WHITE,1);
	w.SetFont(10,PLAIN,SWISS);
	int n=1;
	for(int i=250;i<550;i+=15)
	{	
		if((n==curFloor)||((n==20)&&(curFloor>20)))
			w.SetPen(RED,1);

		w.DrawInteger(i,90,n);
		w.SetPen(WHITE,1);
		if(n==numFloors)
			break;
		++n;
	}
	if(curFloor<=20)
	{
	w.SetPen(WHITE,1);
	w.DrawString(545,90,"+");
	}
	if(curFloor>20)
	{
	w.SetPen(YELLOW,1);
	w.DrawString(545,90,"+");
	}
}

elev:: WaitNClear(window &inputWindow)
{
 int iX, iY;
 
 	inputWindow.SetPen(ORANGE);
	inputWindow.SetFont(16, BOLD, SWISS);
    inputWindow.DrawString(inputWindow.GetWidth()/2 - 100, inputWindow.GetHeight() - 75, "Click mouse to continue...");

    // Flush the mouse queue
    inputWindow.FlushMouseQueue();

    // Ignore return value since we don't care what type of click it was
    inputWindow.WaitMouseClick(iX, iY);

    // Set the brush and pen white so we can clear the background
    inputWindow.SetPen(RED, 10);    
    inputWindow.SetBrush(BLACK);
    
    // Draw a rectangle that covers the entire window
    //inputWindow.DrawRectangle(0, 0, inputWindow.GetWidth(), inputWindow.GetHeight());

}

elev:: OpenDoors(window &w)
{
	int x1=400;
	int x2=400;
	
	if(myFloor<curFloor)
		BringDown(w);
	else if(myFloor>curFloor)
		BringUp(w);

	w.SetPen(BLACK,1);
	w.SetBrush(BLACK);

	for(int i=0;i<75;++i)
	{
		w.DrawRectangle(x1,100,x2,400,FILLED);
		Pause(75);
		x1-=2;
		x2+=2;
	}
}

elev:: CloseDoors(window &w)
{
	int x1=250;
	int x2=250;
	int x3=550;
	int x4=550;

	w.SetPen(BLACK,1);
	w.SetBrush(DARKGOLDENROD);

	for(int i=0;i<152;++i)
	{
		w.DrawRectangle(x1,100,x2,400,FILLED);
		w.DrawRectangle(x3,100,x4,400,FILLED);
		Pause(37.5);
		x2+=1;
		x4-=1;
	}
}

elev:: Drawmyfloor(window &w)
{
	int wi,h;

	w.SetPen(FORESTGREEN,1);
	w.SetBrush(DARKRED);
	w.SetFont(75,PLAIN,SWISS);
	w.GetIntegerSize(wi,h,myFloor);
	w.DrawRectangle(100,50,100+wi,50+h);
	w.DrawInteger(100,50,myFloor);
}

elev:: BringDown(window &w)
{
	while(curFloor>myFloor)
	{
		--curFloor;
		FloorNumbers(w);
		Pause(1000);
	}
}

elev:: BringUp(window &w)
{
	while(curFloor<myFloor)
	{
		++curFloor;
		FloorNumbers(w);
		Pause(1000);
	}
}

elev::DrawOut(window &w)
{
	//Exit sign var.
	int X2, Y2;

	w.ChangeTitle("Draco Tower");
	
	//wall
	w.SetPen(DARKSLATEGREY,1);
	w.SetBrush(DARKSLATEGREY);
	w.DrawRectangle(0,0,800,600,FILLED);
	w.SetPen(WHITE,1);
	for(int i=0;i<=w.GetHeight();i+=50)
		w.DrawLine(0,i,800,i);
	for(int j=0;j<=w.GetWidth();j+=75)
		w.DrawLine(j,0,j,600);
	
	//border
	w.SetPen(DARKGREY,10);
	w.DrawRectangle(240,90,560,410,FRAME);
	
	//floor
	w.SetPen(STEELBLUE,1);
	w.SetBrush(STEELBLUE);
	w.DrawRectangle(0,400,800,600,FILLED);
	
	//elevator
	w.SetPen(BLACK,1);
	w.SetBrush(DARKGOLDENROD);
	w.DrawRectangle(250,100,550,400,FILLED);
	w.DrawLine(400,100,400,400);
	
	//arrowup
	w.SetPen(GHOSTWHITE,1);
	w.SetBrush(GHOSTWHITE);
	int XP1[] = {555,552,554,554,556,556,558};
	int YP1[] = {230,234,234,240,240,234,234};
	w.DrawPolygon(XP1,YP1,7,FILLED);

	//arrowdown
	w.SetPen(SNOW,1);
	w.SetBrush(SNOW);
	int XP2[] = {555,552,554,554,556,556,558};
	int YP2[] = {260,256,256,250,250,256,256};
	w.DrawPolygon(XP2,YP2,7,FILLED);

	//floor numbers
	FloorNumbers(w);
	
	if(myFloor==1)
	{
	//Exit Sign
	w.SetPen(BLACK,1);
	w.SetBrush(RED);
	w.SetFont(25,BOLD,MODERN);
	w.GetStringSize(X2,Y2,"EXIT");
	w.DrawRectangle(650,40,650+X2,40+Y2);
	w.DrawString(650,40,"EXIT");
	}

	//myFloor
	Drawmyfloor(w);
}

int elev:: ClickArrow(window &w)
{
	//mouse click var.
	int iX, iY;
	//within arrows' x
	bool arrowx=false;
	//within arrow up's y
	bool arupy=false;
	//within arrow down's y
	bool ardwny=false;
	//within exit x;
	bool exitx=false;
	//within exit y;
	bool exity=false;
	//Exit sign var.
	int X2, Y2;
	
	//Click Arrow
	while( ((!arrowx) && ((!arupy)||(!ardwny))) && ((!exitx)&&(!exity)))
	{
	arrowx=false;
	arupy=false;
	ardwny=false;
	exitx=false;
	exity=false;

	w.FlushMouseQueue();
    w.WaitMouseClick(iX, iY);
	if((iX<=558)&&(iX>=555))
	{
		
		if((iY<=240)&&(iY>=230))
		{
			OpenDoors(w);
			arupy=true;
			arrowx=true;
			return 1;
		}
		if((iY<=260)&&(iY>=250))
		{
			OpenDoors(w);
			ardwny=true;
			arrowx=true;
			return 1;
		}
	}
	if(myFloor==1)
	{
	w.SetPen(BLACK,1);
	w.SetFont(25,BOLD,MODERN);
	w.GetStringSize(X2,Y2,"EXIT");
	if(((iX<=650+X2)&&(iX>=650))&&((iY<=40+Y2)&&(iY>=40)))
	{
		exitx=exity=true;
		return 0;
	}
	}//if myFloor==1
	} //while }
	return 1;
}

elev:: DrawIn(window &w)
{	
	//wall
	w.SetPen(DARKSLATEGREY,1);
	w.SetBrush(DARKSLATEGREY);
	w.DrawRectangle(0,0,800,600,FILLED);
	w.SetPen(WHITE,1);
	for(int i=0;i<=w.GetHeight();i+=50)
		w.DrawLine(0,i,800,i);
	for(int j=0;j<=w.GetWidth();j+=75)
		w.DrawLine(j,0,j,600);

	//floor
	w.SetPen(STEELBLUE,1);
	w.SetBrush(STEELBLUE);
	w.DrawRectangle(0,400,800,600,FILLED);

	//Inside wall
	w.SetPen(CHROME,1);
	w.SetBrush(CHROME);
	w.DrawRectangle(400,0,800,600);
	w.DrawRectangle(0,0,800,100);
	w.SetPen(BLACK,1);
	w.DrawLine(0,100,350,100);
	
	//Door
	w.SetPen(BLACK,1);
	w.SetBrush(DARKGOLDENROD);
	w.DrawRectangle(400,100,350,600);
	
	//panel
	w.SetBrush(FIREBRICK);
	w.DrawRectangle(450,150,700,350);

	//buttons
	int n=1;
	for (int y=175;y<=350;y+=45)
		for (int x=475;x<=675;x+=45)
		{
			DrawButton(w,x,y,n);
			n+=1;
		}

	//numbers
	w.SetPen(BLACK,1);
	w.SetBrush(BLACK);
	w.DrawRectangle(100,50,510,70);
	InNums(w);

}

elev:: DrawButton(window &w,int x,int y,int n)
{	
	w.SetPen(BLACK,1);
	w.SetFont(25,PLAIN,SWISS);
	w.SetBrush(DARKBLUE);
	w.DrawCircle(x,y,20,FILLED);
	w.SetPen(YELLOW,1);
	w.DrawInteger(x-10,y-15,n);
}

elev:: InNums(window &w)
{
	w.SetPen(WHITE,1);
	w.SetFont(20,PLAIN,SWISS);
	int n=1;
	for(int i=100;i<500;i+=20)
	{	
		if((n==curFloor)||((n==20)&&(curFloor>20)))
			w.SetPen(RED,1);

		w.DrawInteger(i,50,n);
		w.SetPen(WHITE,1);
		if(n==numFloors)
			break;
		++n;
	}
	if(curFloor<=20)
	{
	w.SetPen(WHITE,1);
	w.DrawString(500,50,"+");
	}
	if(curFloor>20)
	{
	w.SetPen(YELLOW,1);
	w.DrawString(500,50,"+");
	}
}

elev:: CloseInDoor(window &w)
{
	int x=350;
	
	w.SetPen(BLACK,1);
	w.SetBrush(DARKGOLDENROD);

	for(int i=0;i<=350;++i)
	{
		w.DrawRectangle(400,100,x,600);
		Pause(10);
		x-=1;
	}
}

elev:: ClickButton(window &w)
{
	//mouse click var.
	int iX, iY;
	int r=0,c=0;
	int floor;
	bool button=false;

	while(button==false)
	{
		w.FlushMouseQueue();
		w.WaitMouseClick(iX, iY);
		
		r=FindRow(iY);
		c=FindCol(iX);
		
		if((r!=0)&&(c!=0))
		{
		button=true;
		floor=c+((r-1)*5);
			if (floor<curFloor)
			{
				CloseInDoor(w);
				Pause(500);
				while(curFloor>floor)
				{
					--curFloor;
					--myFloor;
					InNums(w);
					Pause(1000);
				}
			}
			if (floor>curFloor)
			{
				CloseInDoor(w);
				Pause(500);
				while(curFloor<floor)
				{
					++curFloor;
					++myFloor;
					InNums(w);
					Pause(1000);
				}
			}
		}//if r and c != 0
	}//while }

	OpenInDoor(w);
	Pause(2000);
}

int elev:: FindRow(int iY)
{
	if((iY>=155)&&(iY<=195))
		return 1;
	else if((iY>=200)&&(iY<=240))
		return 2;
	else if((iY>=245)&&(iY<=285))
		return 3;
	else if((iY>=290)&&(iY<=330))
		return 4;
	else 
		return 0;
}

int elev:: FindCol(int iX)
{
	if((iX>=455)&&(iX<=495))
		return 1;
	else if((iX>=500)&&(iX<=540))
		return 2;
	else if((iX>=545)&&(iX<=585))
		return 3;
	else if((iX>=590)&&(iX<=630))
		return 4;
	else if((iX>=635)&&(iX<=675))
		return 5;
	else
		return 0;
}

elev:: OpenInDoor(window &w)
{
int x=0;
	
	w.SetPen(BLACK,1);
	w.SetBrush(BLACK);

	for(int i=0;i<=350;++i)
	{
		w.DrawRectangle(0,100,x,600);
		Pause(10);
		x+=1;
	}
}
