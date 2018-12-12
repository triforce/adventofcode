#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        int twice = 0, thrice = 0, result = 0;

        fp = fopen("input", "r");

        if (fp == NULL)
        {
                exit(EXIT_FAILURE);
        }

        while ((read = getline(&line, &len, fp)) != -1)
        {
                int occurances[256] = { 0 };
                int twicedone = 0, thricedone = 0;

                for (int i = 0; i < strlen(line); i++) {
                        occurances[(int)(line[i])]++;
                }
                for (int i = 0; i < 256; i++) {
                        char c = (char)i;
                        if (occurances[i] == 2 && !twicedone)
                        {
                                twice++;
                                twicedone = 1;
                        }
                        if (occurances[i] == 3 && !thricedone)
                        {
                                thrice++;
                                thricedone = 1;
                        }
                }
        }

        fclose(fp);

        if (line)
        {
                free(line);
        }

        result = twice * thrice;
        printf("%i\n", result);
        exit(EXIT_SUCCESS);
}
