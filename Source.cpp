#include <iostream>
#include <time.h>  
#include <cmath>
using namespace std;

//direction
int xm[] = { 1, 0, -1, 0 };
int ym[] = { 0, 1, 0, -1 };
		// {E, N, W, S}

struct Node{
	int dataX;
	int dataY;
	int data;
};

int RandGen(int size) 
{
	//if it have not picked before
	int picked = rand()% size;
	return picked;
	//return RoomA and his neighbour
}
void convert(Node* n, int size, int a, int b)
{
	for (int i = 0; i < size * size; i++)
	{
		if (n[i].data == a)
		{
			n[i].data = b;
		}
	}
}
void RoomUnion(Node* a, int size, int p, int *maze) 
{
	int k = RandGen(size * size);
	int m = RandGen(4);
	//Debuging...////////////////////////////////////////////////////////////////// 
	//cout << "The Chosen One: " << k << endl;
	//cout << "The direction: " << m << endl;
	//cout << "Which Room: " << a[k].data << endl;
	//// cout << "Node.X: " << a->dataX << " Node.Y: " << a->dataY << endl;
	//cout << "Node[k].X: " << a[k].dataX << " Node[k].Y: " << a[k].dataY << endl;
	//cout << endl;
	////////////////////////////////////////////////////////////////// ////////////
	//in the boundary
	if ((a[k].dataX + xm[m] >= 0) && (a[k].dataX + xm[m] < p) && (a[k].dataY + ym[m] >= 0) && (a[k].dataY + ym[m] < p) )
	{
		switch (m)
		{ 
		case 0: if (a[k].data != a[k + 1].data && maze[(p * a[k].dataX) + a[k].dataY + 1] != -1)  //east
		{
			maze[(p * a[k].dataX) + a[k].dataY+1] = 0;
			convert(a, size, a[k + 1].data, a[k].data);
			maze[(p * a[k].dataX) + a[k].dataY] = 0;
		}
			  break;
		case 1: if (a[k].data != a[k - p].data && maze[(p * a[k].dataX) + a[k].dataY - p] != -1)  //north
		{
			maze[(p * a[k].dataX) + a[k].dataY-p] = 0;
			convert(a, size, a[k - size].data, a[k].data);
			maze[(p * a[k].dataX) + a[k].dataY] = 0;
		}
			  break;
		case 2: if (a[k].data != a[k - 1].data && maze[(p * a[k].dataX) + a[k].dataY - 1] != -1) //west
		{
			maze[(p * a[k].dataX) + a[k].dataY - 1] = 0;
			convert(a, size, a[k - 1].data, a[k].data);
			maze[(p * a[k].dataX) + a[k].dataY] = 0;
		}
			break;
		case 3: if (a[k].data != a[k + p].data && maze[(p * a[k].dataX) + a[k].dataY + p] != -1) //south
		{
			maze[(p * a[k].dataX) + a[k].dataY + p] = 0;
			convert(a, size, a[k + size].data, a[k].data);
			maze[(p * a[k].dataX) + a[k].dataY] = 0;
		}
		}	
	}
}



int main() 
{
	system("CLS");
	/////////////////////variables define//////////////////////////////////////////////////
	srand(time(NULL));
	int size;

	cout << "Please Insert the size of Maze (max.50): ";
	cin >> size;



	// Wait for input /////////////////////////////////////////////////////////////////////
	system("CLS");
	cout << "<Your Maze Has been Generated>   ";
	for (int j = 0; j < 2; j++)
		cout << endl;

	int x{}, y{};
	int i = 0;
	int pixels = (2 * size) + 1;

	int* maze = new int[pixels * pixels];
	Node* room = new Node[size * size];

	

	////////////////////////ROOM GENERATION PRINT//////////////////////////////////////
	// breakable wall = 1; unbreakable = -1, path/room = 0 
	for (x=0; x < pixels; x++) //GRID //x = column y = row 
	{
		cout << "   ";
		for (y = 0; y < pixels; y++)
		{
			//Start and Goal --need to be determine
			if (y == 0 && x == 1 || x == (2 * size) - 1 && y == (2 * size)) 
			{ 
				maze[(pixels * x) + y] = 0;
			} 
			else if (y%2 == 1 && x%2 == 1) //center of room //
				{
				//int norm = ((size * x) + y) - ((size * x) + y - 1);
				maze[(pixels * x) + y] = 0; 
				
				//each room is defined//
				room[i].data = i;
				room[i].dataX = x;
				room[i].dataY = y;
				i++;
				} 
			else if (x % 2 == 0 && y % 2 == 0) //corners,
			{ 
				maze[(pixels * x) + y] = -1;
			} 
			else if (x % 2 == 0 && y % 2 == 1) //wall that can be break : 1
			{ 
				if (x!=0 && x!= pixels-1) {
					maze[(pixels * x) + y] = 1;
				} 
				else maze[(pixels * x) + y] = -1;
			} 
			else if (x % 2 == 1 && y % 2 == 0) //wall that can be break : 1
			{ 
				if (y != 0 && y != pixels - 1) {
					maze[(pixels * x) + y] = 1;
				}
				else maze[(pixels * x) + y] = -1;
			} 
			
		}
		cout << endl;
	}
	////////////////////////ROOM GENERATION PRINT//////////////////////////////////////

	while (room[0].data != room[(size * size) - 1].data) {
		RoomUnion(room, size, pixels, maze);
	}
	//Final Printing Aftter applied the UNion/////////////////////////////////////////
	bool gameOver = false;
	int PlayerX = 1; int PlayerY = 0;
	int PlayerD;

	while (!gameOver) {
		system("CLS");
		cout << "THE " << size << "x" << size << "'s MAZE Is FULLY GENERATED:" << endl;
		cout << endl;
		//Maze
		

		int count = 0;
		for (int j = 0; j < (pixels); j++) //checking the status
		{
			cout << "  ";
			for (int k = 0; k < pixels; k++)
			{
				if (maze[(pixels * j) + k] == -1 || maze[(pixels * j) + k] == 1)
				{
					cout << "#";
					
				}
				if (maze[(pixels * j) + k] == 0)
				{
					// DRAW PLAYER
					if (k == PlayerY && j == PlayerX)
					{
						cout << 'P';
					} else cout << " ";
					
				}
				
			}
			cout << endl;
		}
		
		//Player Input
		char Action;
		cout << endl;
		//cout << "Your current POS: " << "X: " << PlayerX << " Y: " << PlayerY << endl;
		cout << "Your Input (Move: W,A,S,D): ";
		cin >> Action;
		//if (maze[(pixels * x) + y] == 0) 
		//{
			switch (Action)
			{
			case 'W':
				if (maze[(pixels * PlayerX) + PlayerY - pixels] != 0) break;
				if (maze[(pixels * PlayerX) + PlayerY] == 0) // move right
				{
					PlayerX--;
				}
				break;
			case 'A':
				if (maze[(pixels * PlayerX) + PlayerY - 1] != 0) break;
				if (maze[(pixels * PlayerX) + PlayerY] == 0) // move right
				{
					PlayerY--;
				}
				break;
			case 'S':
				if (maze[(pixels * PlayerX) + PlayerY + pixels] != 0) break;
				if (maze[(pixels * PlayerX) + PlayerY] == 0) // move right
				{
					PlayerX++;
				}
				break;
			case 'D': 
				if (maze[(pixels * PlayerX) + PlayerY + 1] != 0) break;
				if (maze[(pixels * PlayerX) + PlayerY] == 0) // move right
				{
					PlayerY++;
				}
			}
		//}
		
			if (PlayerX == (2 * size) - 1 && PlayerY == (2 * size)) 
			{
				gameOver = true;
				break;

			
			}
		

	}
	
	system("CLS");
	cout << endl;
	cout << "GG You finished the game";
	cout << endl;
	cout << endl;
	cout << endl;






	delete [] maze;
	return 0;
}