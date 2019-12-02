#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
So, for each module mass, calculate its fuel and add it to the total. Then, treat the fuel amount you just calculated as the input mass and repeat the process, continuing until a fuel requirement is zero or negative. For example:
*/

int massCalc(int num);

int main(void)
{
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read; 
        int mass = 0, total = 0, num = 0;

        fp = fopen("input", "r");

        if (fp == NULL)
        {
                exit(EXIT_FAILURE);
        }

        while ((read = getline(&line, &len, fp)) != -1)
        {
                int currmass = 0;
                num = atoi(line);
                currmass = massCalc(num);
                mass+=currmass;
                do
                {
                        total+=currmass;
                } while ((currmass = massCalc(currmass)) > 0);
        }

        fclose(fp);

        if (line)
        {
                free(line);
        }

        printf("%i\n", total);

        exit(EXIT_SUCCESS);
}

int massCalc(int num)
{
        return floor(num / 3) - 2;
}
