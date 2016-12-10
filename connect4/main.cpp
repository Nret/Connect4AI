#include "core.h"
#include <time.h>
#include <iostream>
using namespace std;

///////////////////////////////////////
// TODO write the tree here:
///////////////////////////////////////
class gamefieldstate
	{
	public:
		unsigned char gf[6][7];	//should have a copy of the current situation
		int evaluate;			//kinda 1 .. win -1...loose, 0 ..unknown, or whatever...
		gamefieldstate *parent; //pointer to last move
		gamefieldstate *next[7]; //pointer to the next 7 possibilities, for each row! let it NULL if the row is full
		//unsigned char AI = 'O';
		int bestMovePos;
		gamefieldstate()
			{
			bestMovePos = 0;
			parent = NULL;
			evaluate = 0;
			for (int ii = 0; ii < 7; ii++)
				next[ii] = NULL;
			}
		//suggestion:
		void make_new_moves(unsigned char gf[6][7], unsigned char me) //makes all 7 new moves and detects weither or not this is a good idea. 
		{
			setBoardState(gf);

			children_make_moves(0, me, me);

			// detect direct win
			for (int i = 0; i < 7; i++)
			{
				//print_gamefield(next[i]->gf);
				if (detect_win(next[i]->gf, me))
				{
					cout << "Yay a win" << endl;
					bestMovePos = i;
					return;
				}
				// detect direct lose
				for (int j = 0; j < 7; j++)
				{
					if (next[i]->next[j])
					{
						if (detect_win(next[i]->next[j]->gf, otherPlayer(me)))
						{
							cout << "Oh no almost lost" << endl;
							bestMovePos = j;
							return;
						}
					}
				}
			}

			bestMovePos = 0;
			bool noMove = true;
			if (next[bestMovePos]->evaluate != 0)
				noMove = false;

			for (int i = 1; i < 7; i++)
			{
				if (next[bestMovePos]->evaluate < next[i]->evaluate) {
					bestMovePos = i;
					noMove = false;
				}

			}
			if (noMove)
				cout << "No good moves" << endl;
		}

		int children_make_moves(int level, unsigned char player, unsigned char me)
		{
			if (level == 8)
				return 0;

			if (detect_win(gf, me))
				return 0;
			else if (detect_win(gf, otherPlayer(me)))
				return 0;

			evaluate = 0;

			for (int i = 0; i < 7; i++) 
			{
				//cout << level << " " << i << endl;
				next[i] = new gamefieldstate();
				next[i]->setBoardState(gf);
				if (!next[i]->place_piece(i, player))
					continue;
				
				//print_gamefield(next[i]->gf);

				if (detect_win(next[i]->gf, me))
					evaluate += 1;
				else if (detect_win(next[i]->gf, otherPlayer(me)))
					evaluate += -1;

				evaluate += next[i]->children_make_moves(level + 1, otherPlayer(player), me);
			}


			return evaluate;
		}

		unsigned char otherPlayer(unsigned char player)
		{
			return player == 'X' ? 'O' : 'X';
		}

		bool place_piece(int colums_throw, unsigned char player)
		{
			if (colums_throw < 0 || colums_throw >= 7)
				return false;

			int row = 5;
			for (row = 5; row >= 0; row--)
			{
				if (gf[row][colums_throw] == 250)
				{
					gf[row][colums_throw] = player; // O or X
					break;
				}
			}
			if (row < 0)
				return false;

			return true;

		}

		void setBoardState(unsigned char gf[6][7])
		{
			for (int xx = 0; xx < 6; xx++)
				for (int yy = 0; yy < 7; yy++)
					this->gf[xx][yy] = gf[xx][yy];
		}

		~gamefieldstate() 
		{
			for (int i = 0; i < 7; i++)
				if (next[i])
					delete next[i];
		}
	};
//**************************************
// TODO: make your AI move here
//**************************************

bool place_piece(unsigned char gf[6][7], int colums_throw, unsigned char who)
{
	if (colums_throw < 0 || colums_throw >= 7)
		return false;//wrong entry, call function again


					 //check how far it goes from bottom to top: 
	int row = 5;
	for (row = 5; row >= 0; row--)
	{
		if (gf[row][colums_throw] == 250)
		{
			gf[row][colums_throw] = who;
			break;
		}
	}
	if (row < 0)
		return false;
	
	return true;

}

void seed() 
{
	srand(time(0));
}

void random_move(unsigned char gf[6][7])
{
	int pos = rand() % 7;
	place_piece(gf, pos, 'O');

}

bool artificial_intelligence(unsigned char gf[6][7], unsigned char player)
{
	/* POA
	GST cur(gf)
	cur.makemove()
	nextmove = cur.best
	delete gst
	*/

	//*
	gamefieldstate gfs;
	gfs.make_new_moves(gf, player);
	int nextMove = gfs.bestMovePos;
	//gfs.delete_tree(); //used a deconstructor instead
	place_piece(gf, nextMove, player);
	return true;
	//*/

	/*
	random_move(gf);

	return true;
	//*/

	//do your stuff here.
	//you can use detect_win(gamefield, 'O') for detection if the AI wins and 'X' if tt eplayer wins
	//it returns true or false (win or not)

	/*
	// at the moment, you have to enter a stone by keyboard. replace this with a real AI
	int colums_throw = -1;
	cout << "select column: ";
	cin >> colums_throw;
	if (colums_throw < 0 || colums_throw >= 7)
		return false;//wrong entry, call function again


	//check how far it goes from bottom to top: 
	int row = 5;
	for (row = 5; row >= 0; row--)
		{
		if (gf[row][colums_throw] == 250)
			{
			gf[row][colums_throw] = 'O'; break;
			}
		}
	if (row < 0)
		{
		cout << "row is full, choose again" << endl;
		return false;//wrong entry, call function again
		}
	return true;
	//*/
}



void main()
	{
	seed();

	unsigned char gamefield[6][7];//6 rows, 7 columns

	for (int xx = 0; xx < 6; xx++)
		for (int yy = 0; yy < 7; yy++)
			gamefield[xx][yy] = 250;


print_gamefield(gamefield);
	while (1)
		{
		
		//*
		//read
		int colums_throw = -1;
		cout << "select column (0..6,9): ";
		cin >> colums_throw;
		//*
		if (colums_throw == 9)
			artificial_intelligence(gamefield, 'X');
		else if (colums_throw < 0 || colums_throw >= 7)break;//end program
		else {


		//check how far it goes from bottom to top:
		int row = 5;
		for (row = 5; row >= 0; row--)
			{
			if (gamefield[row][colums_throw] == 250)
				{
				gamefield[row][colums_throw] = 'X'; break;
				}
			}
		if (row < 0)
			{
			cout << "row is full, choose again" << endl;
			continue;
			}
		}
		print_gamefield(gamefield);
		if(detect_win(gamefield, 'X')==true)
			{
			print_gamefield(gamefield);
			cout << "you have won!" << endl;
			break;
			}

		//AI:
		while (!artificial_intelligence(gamefield, 'O'))
			;
		print_gamefield(gamefield);
		if (detect_win(gamefield, 'O') == true)
			{
			print_gamefield(gamefield);
			cout << "you have lost!" << endl;
			break;
			}
		}
	system("pause");

	}