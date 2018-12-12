#include <stdio.h>

int main(void)
{
    char c;
    //char C[40];

    for (int i = 0; i < 30; i++)
    {
        if (scanf("%c", &c) == 1)
        {
            printf("%c", c);

        }
    }
    return 0;
}
