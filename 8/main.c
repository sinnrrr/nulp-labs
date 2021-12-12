#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER "|"
#define BUFFER_LENGTH 255
#define DELIMITING_PARTS_COUNT 5

int main(void)
{
    char filename[64];

    printf("Enter filename (max 63 characters): ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        puts("Entered file does not exist");

        return 1;
    }

    char *info[BUFFER_LENGTH][DELIMITING_PARTS_COUNT + 1];
    char buffer[BUFFER_LENGTH];

    for (int i = 0; fgets(buffer, BUFFER_LENGTH, file); i++)
    {
        char *token = strtok(buffer, DELIMITER);
        for (int j = 0; token != NULL; j++)
        {
            char *newline = strchr(token, '\n');
            if (newline) *newline = 0;

            info[i][j] = token; // array of arrays of char[] -> array of char[] = char[] 
            token = strtok(NULL, DELIMITER);

            printf("%s\n", info[i][j]);
        }
    }

    fclose(file);

    printf("%s %s %s %s %s", info[0][0], info[0][1], info[0][2], info[1][0], info[1][1]);

    return 0;
}