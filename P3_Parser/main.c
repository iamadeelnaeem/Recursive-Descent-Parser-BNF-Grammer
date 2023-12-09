// CS4280 P1
// Option1
// Suhyun Lee

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "scanner.h"
#include "parser.h"
#include "testTree.h"
#include "staticSemantics.h"

void call_file(FILE *fp);

int main(int argc, char *argv[])
{
    FILE *fp = NULL;

    // Invocation
    if (argc == 1) // If filename is not given
    {
        // P1
        char filename[100] = {0};
        char c;
        int i = 0;

        if (isatty(STDIN_FILENO))
        {
            printf("Write a file name and enter EOF to end: ");
            while ((c = getchar()) != '\n' && c != EOF && i < 99)
            {
                filename[i++] = c;
            }
            filename[i] = '\0';
            fp = fopen(filename, "r");

            if (fp == NULL)
            {
                perror("File open error");
                return 1;
            }
            call_file(fp);
        }
        // P1 < somefile
        else
        {
            fp = stdin;
            if (fp == NULL)
            {
                perror("File open error");
                return 1;
            }
            call_file(fp);
        }
    }
    else if (argc == 2) // If the filename is given, add .f1 extension
    {
        char file_name[100];
        strcpy(file_name, argv[1]);
        int i;
        for (i = 0; i < 100; i++)
        {
            if (file_name[i] == '\0')
            {
                file_name[i] = '.';
                file_name[i + 1] = 'f';
                file_name[i + 2] = '1';
                file_name[i + 3] = '\0';
                break;
            }
        }
        fp = fopen(file_name, "r");
        call_file(fp);
    }
    else
    {
        perror("Too many arguments");
        return 1;
    }

    parser();

    // Perform static semantics check
    staticSemantics(root);

    fclose(fp);

    return 0;
}