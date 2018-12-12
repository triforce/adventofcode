#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Got this from https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return(column[s1len]);
}

int main(void)
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int charsSize = 0;
	char ** chars = NULL;
	unsigned int lowest = 100; // Cheating big number
	char * match1 = NULL;
	char * match2 = NULL;
	char * matches = NULL;
	int matchIndex = 0;

	fp = fopen("input", "r");

	if (fp == NULL)
	{
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, fp)) != -1)
	{
		charsSize++;
		chars = realloc(chars, sizeof(char *) * charsSize);
		chars[charsSize-1] = malloc(sizeof(char) * strlen(line));
		strcpy(chars[charsSize-1], line);
	}

	for (int i = 0; i < charsSize; i++)
	{
		for (int ii = 0; ii < charsSize; ii++)
		{
			if (chars[i] != chars[ii])
			{
				// The levenshtein function could be modified to also show the matching chars but that is to much effort
				unsigned int lev = levenshtein(chars[i], chars[ii]);

				if (lev < lowest)
				{
					lowest = lev;
					match1 = malloc(sizeof(char) * strlen(chars[i]));
					match2 = malloc(sizeof(char) * strlen(chars[ii]));
					strncpy(match1, chars[i], strlen(chars[i]));
					strncpy(match2, chars[ii], strlen(chars[ii]));
				}
			}
		}
	}

	fclose(fp);

	if (line)
	{
		free(line);
	}

	free(chars);

	matches = malloc(sizeof(char) * lowest);

	// Add all of the matching chars between the two strings to 'matches'
	for (int i = 0; i < strlen(match1); i++)
	{
		for (int ii = 0; ii < strlen(match2); ii++)
		{
			if (match1[i] == match2[ii])
			{
				matches[matchIndex] = match1[i];
				matchIndex++;
				break;
			}
		}
	}

	free(match1);
	free(match2);

	printf("%s\n", matches);
	exit(EXIT_SUCCESS);
}
