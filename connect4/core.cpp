#include "core.h"

void print_gamefield(unsigned char gf[6][7])
	{
	//system("CLS");
	cout << endl;
	cout << endl;
	for (int xx = 0; xx < 6; xx++)
		{

		for (int yy = 0; yy < 7; yy++)
			{
			cout << gf[xx][yy];
			}
		cout << endl;
		}
	cout << endl;
	cout << endl;
	}

bool detect_win(unsigned char gf[6][7],unsigned char playersign)
	{
	//:vertical
	int count = 0;
	for (int yy = 0; yy < 7; yy++)
		{
		count = 0;
		for (int xx = 0; xx < 6; xx++)
			{
			if (gf[xx][yy] == playersign)
				{
				count++;
				if (count == 4)
					return true;
				}
			else
				count = 0;
			}
		}
	//:horizontal
	count = 0;
	for (int xx = 0; xx < 6; xx++)
		{
		count = 0;
		for (int yy = 0; yy < 7; yy++)		
			{
			if (gf[xx][yy] == playersign)
				{
				count++;
				if (count == 4)
					return true;
				}
			else
				count = 0;
			}
		}

	//:diagonal
	//left top to down bottom:
	count = 0;
	for (int xx_anf = 5; xx_anf >=3; xx_anf--)
		{
		count = 0;
		for (int ii = 0; ii < (xx_anf+1); ii++)
			{
			if (gf[xx_anf-ii][ii] == playersign)
				{
				count++;
				if (count == 4)
					return true;
				}
			else
				count = 0;
			}
		}
	//right top to left bottom:
	count = 0;
	for (int xx_anf = 5; xx_anf >= 3; xx_anf--)
		{
		count = 0;
		for (int ii = 0; ii < (xx_anf + 1); ii++)
			{
			if (gf[xx_anf - ii][6-ii] == playersign)
				{
				count++;
				if (count == 4)
					return true;
				}
			else
				count = 0;
			}
		}
	//left bottom to right top:
	for (int xx_anf = 0; xx_anf < 3; xx_anf++)
		{
		count = 0;
		for (int ii = 0; ii < (6 - xx_anf); ii++)
			{
			if (gf[ii][ii] == playersign)
				{
				count++;
				if (count == 4)
					return true;
				}
			else
				count = 0;
			}
		}
	//right bottom to left top:
	for (int xx_anf = 0; xx_anf < 3; xx_anf++)
		{
		count = 0;
		for (int ii = 0; ii < (6 - xx_anf); ii++)
			{
			if (gf[ii][6-ii] == playersign)
				{
				count++;
				if (count == 4)
					return true;
				}
			else
				count = 0;
			}
		}
	return false;
	}