#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Fuel required to launch a given module is based on its mass. Specifically, to find the fuel required for a module, take its mass, divide by three, round down, and subtract 2.
*/
int massCalc(int num);

int main(void)
{
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        int total = 0, num = 0, mass = 0;

        fp = fopen("input", "r");

        if (fp == NULL)
        {
                exit(EXIT_FAILURE);
        }

        while ((read = getline(&line, &len, fp)) != -1)
        {
                num = atoi(line);
                mass = massCalc(num);
                total+=mass;
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
