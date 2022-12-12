#define WIN32_LEAN_AND_MEAN
#pragma once

#include <stdio.h>
#include <windows.h>
#include <cstdlib>

#include "includes/pieces.h"
#include "includes/board.h"
#include "includes/moves.h"



int main (void)
{

    bool turn = true;
    
    FILE* file = fopen("startingboard.txt", "r");

    piece *** board = CreateBoard(file);

    printBoard(board);
    
    piece *** newBoard = DeepCopyBoard(board);

    square orig(0,0);
    square dest(1,1);

    printf("making move\n");
    makeMove(newBoard, orig, dest);

    isValidMove(piece *** board, square orig, square dest)

    //newBoard[1][1] = empty;    

    printBoard(newBoard);

    printf("SUCCESS\n");

    return 0;
}

