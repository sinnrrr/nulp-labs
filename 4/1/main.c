#include <stdio.h>
#include <string.h>

int main(void)
{
    char sentence[1024], word[64], result[1024];

    printf("Enter input sentence: ");
    scanf("%[^\n]%*c", &sentence);

    printf("Enter word to replace the 4rd one in sentence: ");
    scanf("%s", &word);

    printf("\nResult: ");

    int i = 0;
    char *token = strtok(sentence, " ");
    while (token != NULL)
    {
        // Using printf to avoid g_strjoin function usage
        if (i == 4 - 1)
        {
            printf("%s ", word);
        }
        else
        {
            printf("%s ", token);
        }

        token = strtok(NULL, " ");
        i++;
    }

    return 0;
}