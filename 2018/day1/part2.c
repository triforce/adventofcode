#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        int freqSize = 1;
        int * freqs = malloc(freqSize * sizeof(int));
        int result = 0, diff = 0, prev = 0;

        fp = fopen("input", "r");

        if (fp == NULL)
        {
                free(freqs);
                exit(EXIT_FAILURE);
        }

        while (result == 0)
        {
                read = getline(&line, &len, fp);

                if (read == -1)
                {
                        rewind(fp);
                        continue;
                }

                int cur = atoi(line);
                diff = cur+prev;

                for (int i = 0; i < freqSize; i++)
                {
                        if (freqs[i] == diff)
                        {
                                result = diff;
                                break;
                        }
                }

                freqs[freqSize-1] = diff;
                freqSize++;
                freqs = realloc(freqs, freqSize * sizeof(int));
                prev = diff;
        }

        fclose(fp);

        if (line)
        {
                free(line);
        }

        free(freqs);

        printf("%i\n", result);
        exit(EXIT_SUCCESS);
}
