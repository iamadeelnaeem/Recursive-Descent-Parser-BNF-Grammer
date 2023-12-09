#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 8
#define KEYWORDS 13

static FILE *newfp = NULL;
static int line_num = 1;

// keywords
char *keyword[KEYWORDS] = {
    "start", "stop", "loop", "void", "var", "end", "scan", "print", "main", "cond", "then", "let", "func"};

// Bring file from main
void call_file(FILE *fp)
{
    newfp = fp;
}

// structure of word
typedef struct
{
    char word[100];
    int length;
} WordInfo;

// Read characters until a space is encountered
WordInfo get_word()
{
    WordInfo wordinfo;
    int i = 0;
    char ch;

    while ((ch = getc(newfp)) != EOF && !isspace(ch))
    {
        wordinfo.word[i++] = ch;

        // count line number
        if (ch == '\n')
        {
            line_num++;
        }

        // prevent overflow
        if (i >= 99)
        {
            break;
        }
    }

    if (ch == EOF)
    {
        wordinfo.word[0] = 'E';
        wordinfo.word[1] = 'O';
        wordinfo.word[2] = 'F';
        wordinfo.word[3] = '\0';
        i = 3;
    }
    else
    {
        wordinfo.word[i] = '\0';
    }

    wordinfo.length = i;
    return wordinfo;
}

// Lexical Error
void lexicalError(int n)
{
    switch (n)
    {
    case 1:
        printf("LEXICAL ERROR: ");
        printf("The length cannot exceed 8.\n");
        break;
    case 2:
        printf("LEXICAL ERROR: ");
        printf("You cannot use any other characters, numbers, or symbols besides the given conditions.\n");
        break;
    case 3:
        break;
    case 4:
        printf("LEXICAL ERROR: ");
        printf("A comment must end with a # symbol.\n");
        break;
    }
}

Token scanner()
{
    Token token = {0};
    WordInfo wordinfo = get_word();
    int length = wordinfo.length;
    char word[length + 1];

    strncpy(word, wordinfo.word, length);
    word[length] = '\0';
    int k;
    for (k = 0; k < wordinfo.length; k++)
    {
        word[k] = wordinfo.word[k];
    }

    if (length == 1)
    {
        // Identifier
        if (isalpha(word[0]))
        {
            token.tokenID = IDENTIFIERtk;
        }

        // Integer
        else if (isdigit(word[0]))
        {
            token.tokenID = INTEGERtk;
        }

        // Operator and delimiter
        else if (word[0] == '=' || word[0] == '>' || word[0] == '<' || word[0] == '~' || word[0] == ':' || word[0] == '+' || word[0] == '-' || word[0] == '*' || word[0] == '/' || word[0] == '%' || word[0] == '.' || word[0] == '(' || word[0] == ')' || word[0] == ',' || word[0] == '{' || word[0] == '}' || word[0] == ';' || word[0] == '[' || word[0] == ']')
        {
            token.tokenID = OPERATORStk;
        }

        else
        {
            token.tokenID = ERROR;
            lexicalError(2);
        }

        strncpy(token.instance, word, sizeof(token.instance) - 1);
        token.instance[sizeof(token.instance) - 1] = '\0';
        token.line = line_num;
    }
    else
    {
        // EOF
        if (word[0] == 'E' && word[1] == 'O' && word[2] == 'F')
        {
            token.tokenID = EOFtk;
        }

        // Operators and delimiters
        else if (word[0] == '<' && word[1] == '=')
        {
            token.tokenID = OPERATORStk;
        }
        else if (word[0] == '>' && word[1] == '=')
        {
            token.tokenID = OPERATORStk;
        }

        // Identifier or keyword
        else if (isalpha(word[0]))
        {
            // Keyword
            int keyword_check = 0;
            int i;
            for (i = 0; i < KEYWORDS; i++)
            {
                if (strcmp(word, keyword[i]) == 0)
                {
                    token.tokenID = KEYWORDStk;
                    keyword_check = 1;
                    break;
                }

                // Identifier
                if (keyword_check != 1)
                {
                    int error_check = 0;
                    int j;
                    for (j = 1; j < length; j++)
                    {
                        // Error
                        if (!isalpha(word[j]))
                        {
                            token.tokenID = ERROR;
                            error_check = 1;
                            lexicalError(3);
                            break;
                        }
                    }

                    if (error_check != 1)
                    {
                        token.tokenID = IDENTIFIERtk;
                    }
                }
            }
        }

        // Integer
        else if (isdigit(word[0]))
        {
            int error_check = 0;
            int a;
            for (a = 1; a < length; a++)
            {
                // Error
                if (!isdigit(word[a]))
                {
                    token.tokenID = ERROR;
                    error_check = 1;
                    lexicalError(3);
                    break;
                }
            }

            if (error_check != 1)
            {
                token.tokenID = INTEGERtk;
            }
        }

        // Comment
        else if (word[0] == '#')
        {
            if (length == 2)
            {
                token.tokenID = ERROR;
                lexicalError(3);
            }
            else
            {
                if (word[length - 1] == '#')
                {
                    token.tokenID = COMMENTtk;
                }
                else
                {
                    token.tokenID = ERROR;
                    lexicalError(4);
                }
            }
        }

        else
        {
            token.tokenID = ERROR;
            lexicalError(3);
        }

        strncpy(token.instance, word, sizeof(token.instance) - 1);
        token.instance[sizeof(token.instance) - 1] = '\0';
        token.line = line_num;
    }

    return token;
}

const char *tokenTostring(TokenID tokenID)
{
    switch (tokenID)
    {
    case IDENTIFIERtk:
        return "IDENTIFIERtk";
    case KEYWORDStk:
        return "KEYWORDStk";
    case OPERATORStk:
        return "OPERATORStk";
    case INTEGERtk:
        return "INTEGERtk";
    case COMMENTtk:
        return "COMMENTtk";
    case ERROR:
        return "ERROR";
    case EOFtk:
        return "EOF";
    }
}

void testScanner()
{
    Token token;
    token = scanner();
    while (token.tokenID != EOFtk)
    {
        printf("Token: %s, Line: %d, Instance: %s\n", tokenTostring(token.tokenID), token.line, token.instance);
        token = scanner();
    }
}
