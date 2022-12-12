#define WIN32_LEAN_AND_MEAN
#pragma once

#include <stdio.h>
#include <cstdlib>
// only defining each piece once, all board states will be represented by reference to these global structs.

#include "pieces.h"

#define DIMENSION 8 

piece * wPawn = new piece(WHITE, PAWN);
piece * WBishop = new piece(WHITE, BISHOP);
piece * WKnight = new piece(WHITE, KNIGHT);
piece * WRook = new piece(WHITE, ROOK);
piece * WQueen = new piece(WHITE, QUEEN);
piece * WKing = new piece(WHITE, KING);

piece * BPawn = new piece(BLACK, PAWN);
piece * BBishop = new piece(BLACK, BISHOP);
piece * BKnight = new piece(BLACK, KNIGHT);
piece * BRook = new piece(BLACK, ROOK);
piece * BQueen = new piece(BLACK, QUEEN);
piece * BKing = new piece(BLACK, KING);

piece * emptySq = new piece(EMPTY, NONE);

piece * DeserializePiece (FILE * fp)
{
    char c = getc(fp);

    switch(c)
    {
        case 'e':
            return emptySq;
        case 'p':
            return wPawn;
        case 'r':
            return WRook;
        case 'n':
            return WKnight;
        case 'b':
            return WBishop;
        case 'q':
            return WQueen;
        case 'k':
            return WKing;
        case 'P':
            return BPawn;
        case 'R':
            return BRook;
        case 'N':
            return BKnight;
        case 'B':
            return BBishop;
        case 'Q':
            return BQueen;
        case 'K':
            return BKing;
        default:
            printf("ERROR while parsing char %x\n", c);
    }
}

piece *** CreateBoard(FILE * fp)
{
    piece *** board = NULL;
    board = new piece**[DIMENSION];
    
    for (int h = 0; h < DIMENSION; h++)
    {
        board[h] = new piece * [DIMENSION];
    
        for (int w = 0; w < DIMENSION; w++)
        {
            // fill in some initial values
            // (filling in zeros would be more logic, but this is just for the example)
            board[h][w] = DeserializePiece(fp);
        }
    }
    
    return board;
}

piece *** DeepCopyBoard(piece *** board)
{
    piece *** newBoard = NULL;
    newBoard = new piece**[DIMENSION];

    for (int h = 0; h < DIMENSION; h++)
    {
        newBoard[h] = new piece * [DIMENSION];
    
        for (int w = 0; w < DIMENSION; w++)
        {
            // fill in some initial values
            // (filling in zeros would be more logic, but this is just for the example)
            newBoard[h][w] = board[h][w];
        }
    }
    
    return board;
}

piece * promoteQueen(BYTE color)
{
    if(color == BLACK) {return BQueen;}
    return WQueen;
}

//two value swap
void makeMove(piece *** board, int origX, int origY, int destX, int destY)
{
    piece * tmp = board[origY][origX];
    board[origY][origX] = emptySq;
    
    if(board[origY][origX]->type == PAWN && (destY == 7 || destY == 0)) {tmp = promoteQueen(tmp->color);}
    
    board[destY][destX] = tmp;
}

