#define WIN32_LEAN_AND_MEAN
#pragma once

#include <windows.h>
#include <queue>

#include "board.h"
#include "movement.h"
#include "pieces.h" 

// store move information

class move
{   
    public:

        BYTE x1;
        BYTE x2;
        BYTE y1;
        BYTE y2;

        move() {}

        move(BYTE origX, BYTE origY, BYTE destX, BYTE destY)
        {
            x1=origX;
            x2=destX;
            y1=origY;
            y2=destY;
        }
};

void printMove(move Move) {printf("(%d, %d)->(%d, %d)\n");}


std::queue<move> * moveQueue = new std::queue<move>;

// there are only 4 possible moves for a pawn so I'm just hardcoding them all

void pushMove(BYTE x1, BYTE y1, BYTE x2, BYTE y2) {moveQueue->push(move(x1,y1,x2,y2));}

void pawnPath(BYTE turn, piece *** board, BYTE x1, BYTE y1, BYTE x2, BYTE y2)
{
    if(turn == BLACK)
    {
        if(pawnMove(turn, board, x1 - 1, y1 - 1, x2, y2)) {pushMove(x1, y1, x2, y2);}
        if(pawnMove(turn, board, x1 + 1, y1 - 1, x2, y2)) {pushMove(x1, y1, x2, y2);}
        if(pawnMove(turn, board, x1, y1 - 1, x2, y2)) {pushMove(x1, y1, x2, y2);}
        if(pawnMove(turn, board, x1, y1 - 2, x2, y2)) {pushMove(x1, y1, x2, y2);}
    }
    if(turn == WHITE)
    {
        if(pawnMove(turn, board, x1 - 1, y1 + 1, x2, y2)) {pushMove(x1, y1, x2, y2);}
        if(pawnMove(turn, board, x1 + 1, y1 + 1, x2, y2)) {pushMove(x1, y1, x2, y2);}
        if(pawnMove(turn, board, x1, y1 + 1, x2, y2)) {pushMove(x1, y1, x2, y2);}
        if(pawnMove(turn, board, x1, y1 + 2, x2, y2)) {pushMove(x1, y1, x2, y2);}
    }
}

//void rookPath(BYTE )

int getPosVal(BYTE turn, piece * board) {return 0;}

int getPieceVal(BYTE turn, piece * board) {return 0;}

int evalGameState(piece *** board, BYTE turn)
{

    int total = 0;

    for(int y = 0; y < DIMENSION; y ++)
    {
        for(int x = 0; x < DIMENSION; x++)
        {
            total = total + getPieceVal(turn, board[y][x]) + getPosVal(turn, board[y][x]);
        }
    }

    return 0; 

}