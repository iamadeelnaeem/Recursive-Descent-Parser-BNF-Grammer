#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    IDENTIFIERtk,
    KEYWORDStk,
    OPERATORStk,
    INTEGERtk,
    COMMENTtk,
    ERROR,
    EOFtk
} TokenID;

typedef struct
{
    TokenID tokenID;
    char instance[100];
    int line;
} Token;

#endif