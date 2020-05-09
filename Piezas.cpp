#include "Piezas.h"
#include <vector>
#include <utility>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    board = std::vector<std::vector<Piece>>
        (BOARD_ROWS, std::vector<Piece>(BOARD_COLS, Blank));
    turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    board = std::vector<std::vector<Piece>>
        (BOARD_ROWS, std::vector<Piece>(BOARD_COLS, Blank));
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    if(column >= BOARD_COLS)
        return Invalid;
    int row;
    for(row=0; row<BOARD_ROWS && board.at(row).at(column) != Blank; row++);
    if(row > BOARD_ROWS-1)
        return Blank;

    board.at(row).at(column) = turn;
    if(turn == X)
    {
        turn = O;
    }
    else if(turn == O)
    {
        turn = X;
    } else {
        throw turn;
    }
    return board.at(row).at(column);
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    if(row > board.size() || column > board.at(0).size())
        return Invalid;
    return board.at(row).at(column);
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    auto update_max = [](const Piece& prevPiece, const unsigned int& localMax, 
        unsigned int& globalMaxX, unsigned int& globalMaxO)
    {
        switch(prevPiece)
        {
            case X:
                if(localMax > globalMaxX)
                    globalMaxX = localMax;
                break;
            case O:
                if(localMax > globalMaxO)
                    globalMaxO = localMax;
                break;
            default:
                throw prevPiece;
        }
    };
    
    unsigned int globalMaxX, globalMaxO, localMax;
    globalMaxX = globalMaxO = localMax = 0;
    Piece prevPiece;
    for(int i=0; i<BOARD_ROWS; i++)
    { // adjacents in the horizontal
        localMax = 0;
        prevPiece = board.at(i).at(0);
        for(int j=0; j<BOARD_COLS; j++)
        {
            if(board.at(i).at(j) == Blank)
                return Invalid;
            if(prevPiece == board.at(i).at(j))
            {
                localMax++;
            }
            else
            { // streak ended, compare to globalMax
                update_max(prevPiece, localMax, globalMaxX, globalMaxO);
                localMax = 1;
            }
            prevPiece = board.at(i).at(j);
        }
        // the ends of the board adjacency rules
        update_max(prevPiece, localMax, globalMaxX, globalMaxO);
    }
    
    for(int j=0; j<BOARD_COLS; j++)
    { // adjacents in the vertical
        localMax = 0;
        prevPiece = board.at(0).at(j);
        for(int i=0; i<BOARD_ROWS; i++)
        {
            if(prevPiece == board.at(i).at(j))
            {
                localMax++;
            }
            else
            { // streak ended, compare to globalMax
                update_max(prevPiece, localMax, globalMaxX, globalMaxO);
                localMax = 1;
            }
            prevPiece = board.at(i).at(j);
        }
        // the ends of the board break adjacency rules
        update_max(prevPiece, localMax, globalMaxX, globalMaxO);
    }

    return (globalMaxX == globalMaxO) ? Blank : (globalMaxX > globalMaxO ? X : O);
}