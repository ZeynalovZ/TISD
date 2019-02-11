#include <stdio.h>
#include <stdlib.h>


#define OK 0
#define ERR_OPEN -1
#define ERR_READ -2

/*
*
*
*
for (int j = 0; j < i; j++)
	{
		printf("%d %d\n", array[j].x, array[j].y);
	}
*
*/
typedef struct POINTS points;

struct POINTS
{
    int x;
    int y;
};

int read_from_file(char *filename, points *array)
{
	
    FILE *f;
	int i = 0;
	f = fopen(filename, "r");
	if (f)
	{
		while (fscanf(f, "%d %d", &array[i].x, &array[i].y) == 2)
		{
			i++;
		}
		if ( i == 0)
		{
			return ERR_READ;
		}
	}
	else
	{
		return ERR_OPEN;
	}
	return OK;
}

int user_input_data(int order, int value)
{
	
}

int main (void)
{
	setbuf(stdout, NULL);
	char *filename = "in.txt";
	points array[7];
	read_from_file(filename, array);
	return 0;
}