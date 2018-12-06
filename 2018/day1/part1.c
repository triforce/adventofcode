#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        int result = 0, num = 0;

        fp = fopen("input", "r");

        if (fp == NULL)
        {
                exit(EXIT_FAILURE);
        }

        while ((read = getline(&line, &len, fp)) != -1)
        {
                num = atoi(line);
                result+=num;
        }

        fclose(fp);

        if (line)
        {
                free(line);
        }

        printf("%i\n", result);

        exit(EXIT_SUCCESS);
}
