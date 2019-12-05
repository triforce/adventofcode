#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
        FILE * fp;
        size_t len = 0;
        ssize_t read;
        int *intcodes;
        const int OPCODE_ADD = 1;
        const int OPCODE_MULTIPLY = 2;
        const int OPCODE_END = 99;
        int opcode_val_1, opcode_val_2, opcode_val_3, opcode_total;

        fp = fopen("input", "r");

        if (fp == NULL)
        {
                exit(EXIT_FAILURE);
        }

        fseek(fp, 0, SEEK_END);
        long fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char *string = malloc(fsize + 1);
        fread(string, 1, fsize, fp);

        char *p = strtok(string, ",");
        intcodes = (int*)malloc(1 * sizeof(int));
        intcodes[0] = strtol(p, NULL, 10);
        int i = 0;
        do
        {
                i++;
                p = strtok(NULL, ",");
                if (p != NULL)
                {
                        intcodes = (int*)realloc(intcodes, (i + 1) * sizeof(int));
                        intcodes[i] = strtol(p, NULL, 10);
                }
        } while (p != NULL);

        int total_intcodes = i;

        intcodes[1] = 12;
        intcodes[2] = 2;

        for (i = 0;i<total_intcodes;i++)
        {
                if (intcodes[i] == OPCODE_ADD)
                {
                        opcode_val_1 = intcodes[i + 1];
                        opcode_val_2 = intcodes[i + 2];
                        opcode_val_3 = intcodes[i + 3];

                        opcode_total =  intcodes[opcode_val_1] + intcodes[opcode_val_2];
                        intcodes[opcode_val_3] = opcode_total;
                        i = i + 3;
                        continue;
                } else if (intcodes[i] == OPCODE_MULTIPLY)
                {

                        opcode_val_1 = intcodes[i + 1];
                        opcode_val_2 = intcodes[i + 2];
                        opcode_val_3 = intcodes[i + 3];

                        opcode_total =  intcodes[opcode_val_1] * intcodes[opcode_val_2];
                        intcodes[opcode_val_3] = opcode_total;
                        i = i + 3;
                        continue;
                } else if (intcodes[i] == OPCODE_END)
                {
                        break;
                }
        }

        printf("%i\n", intcodes[0]);

        free(string);
        free(intcodes);
        fclose(fp);

        exit(EXIT_SUCCESS);
}

