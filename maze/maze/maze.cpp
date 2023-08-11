#include <iostream>
#include <windows.h>

using namespace std;

const int WIDTH = 25, HEIGHT = 25; // dimensions of the maze
char player = 'P'; // player character
int posX, posY = 0; // position for character
char input = ' '; // input from user

void Player();
void Welcome();
void End();

char map[WIDTH][HEIGHT] = { // maze
' ',' ','|','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
' ',' ','|',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',
'|',' ','|',' ','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#','#','#',' ','#',
'|',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ','#',
'|','-','-',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#',
'#',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',
'#','#','#',' ','#',' ','#','#','#',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#',' ','#',
'#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',
'#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#','#','#','#','#',' ','#','#','#',
'#',' ',' ',' ',' ',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',
'#',' ','#','#','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#',
'#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',
'#','#','#','#','#','#','#',' ','#','#','#','#','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',
'#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',
'#',' ','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#','#','#',' ','#','#','#','#','#','#','#',
'#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ','#',
'#',' ','#','#','#','#','#',' ','#','#','#',' ','#','#','#',' ','#',' ','#','#','#',' ','#',' ','#',
'#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',
'#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#',' ','#',' ','#',
'#',' ','#',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',
'#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#','#','#',' ','#','#','#','#','#',
'#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ','#',' ','#',
'#','#','#','#','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#','#','#',' ','#','#','#','#','#',
'#',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ','#',' ','#',' ','#',' ',' ',' ',' ',' ',' ','#',
'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','F',
};

int main()
{
	SetConsoleTitle(TEXT("Maze")); // changes console title
	Welcome(); // calls welcome screen
	system("cls"); // clears screen after welcome
	while (map[posX][posY] != 'F') { // while loop will continue updating map everytime the character moves and is not at the finish line
		map[posX][posY] = player; // gets player position
		for (int y = 0; y < HEIGHT; y++) { // displays the map
			for (int x = 0; x < WIDTH; x++)
				cout << map[y][x];
			cout << endl;
		}
		Player(); // gets movement from user
	}
	End(); // shows the end after finishing maze
	return 0;
}

void Welcome() // a quick how to play screen before you start the maze
{
	cout << "To control your character(P)" << endl;
	cout << "w - to go up" << endl;
	cout << "s - to go down" << endl;
	cout << "a - to go left" << endl;
	cout << "d - to go right" << endl;
	cout << "Find your way out of the maze." << endl;
	system("pause"); // press any key to continue
}

void Player() // handles the player input
{
	cout << "\nDirection: ";
	cin >> input;
	int prevposX = posX;
	int prevposY = posY;
	char space = ' ';

	switch (input) // movement based off which character was entered
	{
	case 'w':
		if (map[posX - 1][posY] != '#') { // collision check
			posX--; // if no # then it moves
			map[prevposX][prevposY] = space; // changes the characters previous pos to a white space
		}
		system("cls"); // clears old position and input option
		break;
	case 'a':
		if (map[posX][posY - 1] != '#') {
			posY--;
			map[prevposX][prevposY] = space;
		}
		system("cls");
		break;
	case 's':
		if (map[posX + 1][posY] != '#') {
			posX++;
			map[prevposX][prevposY] = space;
		}
		system("cls");
		break;
	case 'd':
		if (map[posX][posY + 1] != '#') {
			posY++;
			map[prevposX][prevposY] = space;
		}
		system("cls");
		break;
	default:
		cout << "Not WASD." << endl;
		break;
	}
}

void End() // end screen for beating the maze
{
	system("cls");
	cout << "Congratulations, You Beat the Maze!" << endl;
	system("pause");
}