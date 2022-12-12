#define WIN32_LEAN_AND_MEAN
#pragma once

#include "pieces.h"


bool isPiece(piece * piece) {return piece->color != EMPTY;}

bool isEmpty(piece * piece) {return piece->color == EMPTY;}

bool isEnemy(piece * piece1, piece * piece2) {return piece1->color != piece2->color;}

bool isEnemy(BYTE turn, piece * piece2) {return turn != piece2->color;}

bool isOwned(BYTE turn, piece * piece1) {return piece1->color == turn;}

bool onSameLine (BYTE p1, BYTE p2) {return p1 == p2;}

bool onDiagonal (BYTE x1, BYTE y1, BYTE x2, BYTE y2) {printf("%d. %d\n", abs(y2 - y1), abs(x2 - x1)); return abs(y2 - y1) == abs(x2 - x1);}

bool clearPathHorizontal(piece *** board, BYTE p1, BYTE p2, BYTE y) 
{
    BYTE direction = 1;
    if(p1 > p2) {direction = -1;}   
    
    if(isOwned(board[y][p1]->color, board[y][p2])) {return false;}

    for(BYTE n = p1 + direction; n != p2 && n > 0 && n < 8; n = n + direction) 
    {
        if(!isEmpty(board[y][n])) {return false;}
    }

    return true;

}

bool clearPathVertical(piece *** board, BYTE p1, BYTE p2, BYTE x) 
{

    BYTE direction = 1;
    if(p1 > p2) {direction = -1;}    

    if(isOwned(board[p1][x]->color, board[p2][x])) {return false;}

    for(BYTE n = p1 + direction; n != p2 && n > 0 && n < 8; n = n + direction) 
    {
        if(!isEmpty(board[n][x])) {return false;}
    }

    return true;

}

bool clearPathDiagonal(piece *** board, BYTE x1, BYTE y1, BYTE x2, BYTE y2)
{
    BYTE dirY = 1;
    BYTE dirX = 1;
    if(y1 > y2) {dirY = -1;}
    if(x1 > x2) {dirX = -1;}    

    if(isOwned(board[y1][x1]->color, board[y2][x2])) {printf("guh...\n"); return false;}

    BYTE n = 1;

    while(x1 + (n * dirX) >= 0 && x1 + (n * dirX) < 8 && y1 + (n * dirX) >= 0 && y1 + (n * dirX) < 8)
    {

        if(x1 + (n * dirX) == x2) {break;}

        if(!isEmpty(board[y1 + (n * dirY)][x1 + (n * dirX)])) {return false;}
        n++;
    }

    return true;
}

#define BPAWNROW 6
#define WPAWNROW 1

bool pawnMove(BYTE turn, piece *** board, BYTE x1, BYTE y1, BYTE x2, BYTE y2)
{

    bool firstMove = false;

    if(turn == BLACK && y1 == BPAWNROW) {firstMove = true;}

    if(turn == BLACK)
    {
        if(x1 == x2)
        {
            if(y1 - y2 == 1 && isEmpty(board[y2][x2]))
            {
                return true;
            }
            
            else if(firstMove)
            {
                if(y1 - y2 == 2 && isEmpty(board[y2 + 1][x2]) && isEmpty(board[y2][x2])) {return true;}
            }
        }
        if(y1 - y2 == 1 && abs(x1-x2) == 1 && isEnemy(turn, board[y2][x2])) {return true;}
        return false;
    }
    
    if(turn == WHITE && y1 == WPAWNROW) {firstMove = true; printf("first pawn move\n");}

    if(turn == WHITE)
    {
        if(x1 == x2)
        {

            if(y2 - y1 == 1 && isEmpty(board[y2][x2]))
            {
                return true;
            }
            
            else if(firstMove)
            {
                if(y2 - y1 == 2 && isEmpty(board[y2 - 1][x2]) && isEmpty(board[y2][x2])) {return true;}
            }
        }
        if(y2 - y1 == 1 && abs(x1-x2) == 1 && isEnemy(turn, board[y2][x2])) {return true;}
        return false;
    }

}

bool bishopMove(BYTE turn, piece *** board, BYTE x1, BYTE y1, BYTE x2, BYTE y2)
{
    if(onDiagonal(x1, y1, x2, y2))
    {
        if(clearPathDiagonal(board, x1, y1, x2, y2)) {return true;}
        return false;
    } 
    return false;
}

bool knightMove(BYTE turn, piece *** board, BYTE x1, BYTE y1, BYTE x2, BYTE y2)
{
    if((abs(x1-x2) == 2 && abs(y1-y2) == 1) || abs(x1-x2) == 1 && abs(y1-y2) == 2)
    {
        printf("knight square\n");
        return !isOwned(turn, board[y2][x2]);
    }
    printf("not knight square\n");
    return false;
}

bool rookMove(BYTE turn, piece *** board, BYTE x1, BYTE y1, BYTE x2, BYTE y2)
{
    if(onSameLine(x1, x2)) {return clearPathVertical(board, y1, y2, x1);}
    if(onSameLine(y1, y2)) {return clearPathHorizontal(board, x1, x2, y1);}
    return false;
}

bool queenMove(BYTE turn, piece *** board, BYTE x1, BYTE y1, BYTE x2, BYTE y2) {return rookMove(turn, board, x1, y1, x2, y2) || bishopMove(turn, board, x1, y1, x2, y2);}

bool kingMoves(BYTE turn, piece *** board, BYTE x1, BYTE y1, BYTE x2, BYTE y2) {if(abs(x1-x2) <= 1 && abs(y1-y2) <= 1) {return !isOwned(turn, board[y2][x2]);}}

bool isValidMove(BYTE turn, piece *** board, BYTE x1, BYTE y1, BYTE x2, BYTE y2) 
{

    piece * pieceptr = board[y1][x1];

    switch(pieceptr->type)
        {
            case PAWN:
                return pawnMove(turn, board, x1, y1, x2, y2);
                break;

            case BISHOP:
                return bishopMove(turn, board, x1, y1, x2, y2);
                break;
            
            case KNIGHT:
                return knightMove(turn, board, x1, y1, x2, y2);
                break;
            
            case ROOK:
                return rookMove(turn, board, x1, y1, x2, y2);
                break;
            
            case QUEEN:
                return queenMove(turn, board, x1, y1, x2, y2);
                break;

            case KING:
                return kingMoves(turn, board, x1, y1, x2, y2);
                break;
        }

        return true;
}