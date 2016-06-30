#include "functions.h"

#define MAXMODE1 4
#define MAXMODE2 6

int main(int argc, char **argv)
{
	srand(time(NULL));

	EkNNSystem *foo = NULL;
	int menu = 1, menuMax = MAXMODE1, mode = 1;

	while(menu != menuMax)
	{
		displayMenu(&menu, menuMax, mode);

		if(menu == menuMax-1)
			printAbout();
		else if(menu != menuMax)
			switch(mode)
			{
				case 1:
					switch(menu)
					{
						case 1:
							initRandomSystem(&foo);
							mode = 2;
							menuMax = MAXMODE2;
							break;
						case 2:
							printf("NEW\n");
							mode = 2;
							menuMax = MAXMODE2;
							break;
						default:
							break;
					}
					break;
				case 2:
					switch(menu)
					{
						case 1:
							clusterize(foo);
							break;
						case 2:
							printState(foo);
							break;
						case 3:
							deleteSystem(foo);
							foo = NULL;
							mode = 1;
							menuMax = MAXMODE1;
							break;
						case 4:
							exportToCSV(foo);
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
	}
	if(foo != NULL) EkNNDestroy(foo);
	CLEAR_SCREEN();

	return 0;
}
