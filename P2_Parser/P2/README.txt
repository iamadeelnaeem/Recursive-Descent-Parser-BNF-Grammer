# CS4280-001 Project2
### Suhyun Lee

### 1. Project Option
I used 'Option 1' for Project1.

### 2. Project Description
This project contain eight files: main.c scanner.c scanner.h token.h parser.c parser.h testTree.c testTree.h


Create a parser based on the Lexical Analysis developed in Project 1, following the given grammar.  


**main.c**  
main function: Invocation file
There is three ways to invocate this file.
1. ./P2 // read from the keyboard until simulated EOF
2. ./P2 < somfile.f1
3. ./P2 somfile


**scanner.c**  
main function: Token scanner();
The strings in the file are stored in the array word[], based on spaces as delimiters. 
The stored word[] is then distinguished as to what type of token it represents through the Token scanner() function. 
The Token scanner() is implemented using if statements.

**parser.c** 
I implemented functions based on the BNF grammar, determining the First set for each grammar rule. The implementation largely relies on comparing the token instance with the grammar rules using strcmp.

### 3. BNF
<program>  ->     <vars> main <stats> end
<vars>     ->      empty | let <varList> .                       
<varList>  ->      id = integer | id = integer <varList>
<exp>      ->      <M> + <exp> | <M> - <exp> | <M>
<M>        ->      <N> * <M> | <N>      
<N>        ->     <R> / <N> | - <N> |  <R>
<R>        ->      [ <exp> ]  | id | integer
<stats>    ->      <stat>  <mStat>
<mStat>    ->      empty |  <stat>  <mStat>
<stat>     ->      <in>   | <out>   | <block> | <if>  | <loop>  | <assign>
<block>    ->      start <vars> <stats> stop
<in>       ->      scan identifier .
<out>      ->      print <exp> .
<if>       ->      cond ( <exp> <RO> <exp> ) <stat>
<loop>     ->      loop ( <exp> <RO> <exp> )  <stat>
<assign>   ->      id  ~ <exp> .
<RO>       ->      <= (one token)  | >=  (one token)  | < | > | = | ~  
  

### 4. Running the Project
make

1. ./P2 // read from the keyboard until simulated EOF
2. ./P2 < somefile.f1
3. ./P2 somfile
