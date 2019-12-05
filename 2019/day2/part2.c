#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcCodes (int *intcodes, int total_intcodes);

int main(void)
{
        FILE * fp;
        size_t len = 0;
        ssize_t read;
        int *intcodes, *original_intcodes;

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
        int total_size = (total_intcodes + 1) * sizeof(int);
        original_intcodes = malloc(total_size); 
        memcpy(original_intcodes, intcodes, total_size);
        int noun, verb, result;

        for (noun = 0; noun<99; noun++)
        {
                for (verb = 0; verb<99; verb++)
                {                       
                        memcpy(intcodes, original_intcodes, total_size);
                        intcodes[1] = noun;
                        intcodes[2] = verb;
                        result = calcCodes(intcodes, total_intcodes);
                        if (result == 19690720)
                        {
                                printf("%i\n", 100 * noun + verb);
                                free(string);
                                free(intcodes);
                                free(original_intcodes);
                                fclose(fp);
                                exit(EXIT_SUCCESS);
                        }
                }
        }

        free(string);
        free(intcodes);
        free(original_intcodes);
        fclose(fp);
        exit(EXIT_FAILURE);
}


int calcCodes (int *intcodes, int total_intcodes)
{
        const int OPCODE_ADD = 1;
        const int OPCODE_MULTIPLY = 2;
        const int OPCODE_END = 99;
        int opcode_val_1, opcode_val_2, opcode_val_3, opcode_total, result;

        for (int i = 0;i<total_intcodes;i++)
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
        result = intcodes[0];
        return result;
}
