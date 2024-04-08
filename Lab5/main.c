#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_STR 200
#define SENTENCES 20

void print_string(char **string, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s\n", string[i]);
    }
}

void swap(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void swap_sentences(char **string, int count)
{
    int n;
    printf("Input step of swap:");
    scanf("%d", &n);
    if (n > 0 && n < count)
    {
        swap(&string[0], &string[n]);
    }
    else
    {
        n = (n % count + count) % count;
        swap(&string[0], &string[n]);
    }
}

int main()
{
    FILE *ptr_r;
    FILE *ptr_w;
    char ch;

    char **string = (char **)malloc(sizeof(char *) * SENTENCES);
    for (int i = 0; i < SENTENCES; i++)
    {
        string[i] = (char *)malloc(sizeof(char) * BUFFER_STR);
    }

    ptr_r = fopen("input.txt", "r");

    if (NULL == ptr_r)
    {
        printf("file can't be opened \n");
        exit(1);
    }

    printf("content of this file are \n");

    int i = 0;
    int j = 0;
    int count = 0;

    while ((ch = fgetc(ptr_r)) != EOF && i < SENTENCES)
    {
        if (ch != '.')
        {
            string[i][j] = ch;
            j++;
        }
        else
        {
            string[i][j] = '\0';
            i++;
            j = 0;
            count++;
        }
    }
    print_string(string, count);
    swap_sentences(string, count);
    print_string(string, count);

    fclose(ptr_r);

    ptr_w = fopen("./output.txt", "w");

    if (ptr_w == NULL)
    {
        printf("Error Occurred While creating a file !");
        exit(1);
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(ptr_w, "%s.", string[i]);
    }

    fclose(ptr_w);

    printf("File created\n\n");

    for (int k = 0; k < SENTENCES; k++)
    {
        free(string[k]);
    }
    free(string);

    return 0;
}
