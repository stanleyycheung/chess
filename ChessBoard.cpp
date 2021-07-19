#include "ChessBoard.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "knight.h"

using namespace std;

ChessBoard::ChessBoard()
{
    setBoard();
    // printBoard();
}

ChessBoard::~ChessBoard()
{
    clearBoard();
}

void ChessBoard::submitMove(std::string move)
{   
    // can optimise by placing a virtual piece on the ending move and only check those squares
    std::string moveType = returnMoveType(move);
    Square toSquare = getToSquare(move);
    if (moveType == " " || toSquare.x >= BOARD_SIZE || toSquare.y >= BOARD_SIZE || toSquare.x < 0 || toSquare.y < 0)
    {
        cout << "This move is invalid: " << move << endl;
    }
    if (moveType == "Castling")
    {
        // deal with castling
    }
    std::vector <ChessPiece *> possiblePieces;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] != nullptr && board[i][j]->getColour() == turn && board[i][j]->getName() == moveType)
            {
                vector<Square> possibleMoves = board[i][j]->getMoveSquares(board);
                for (Square square : possibleMoves)
                {
                    if (square == toSquare)
                    {
                        possiblePieces.push_back(board[i][j]);
                    }
                }
            }
        }
    }
    // cout << toSquare.squareRepresentation() << endl;
    // cout << possiblePieces.size() << endl;
    if (possiblePieces.size() == 1) {
        ChessPiece *piece = possiblePieces[0];
        ChessPiece *targetPiece = getPiece(toSquare);
    }
    else if (possiblePieces.size() == 2)
    {
        // need to find specific move

    }
    else 
    {

    }
    
}

std::string ChessBoard::returnMoveType(std::string move)
{
    std::string moveType;
    if (!isupper(move[0])) moveType = "Pawn";
    else
    {
        switch (move[0]) 
        {
            case 'B':
                moveType = "Bishop";
                break;
            case 'N':
                moveType = "Knight";
                break;
            case 'R':
                moveType = "Rook";
                break;
            case 'Q':
                moveType = "Queen";
                break;
            case 'K':
                moveType = "King";
                break;
            case 'O':
                moveType = "Castling";
                break;
            default:
                moveType = " ";
        }
    }
    return moveType;
}

Square ChessBoard::getToSquare(std::string move)
{
    int i = 0;
    for (; i < move.size(); i++)
    {
        if (isdigit(move[i])) break;
    }
    return Square(move.substr(i-1, i+1));
}

void ChessBoard::submitMove(std::string fromStr, std::string toStr)
{
    if (!validMoveString(fromStr))
    {
        cout << "This move is invalid: " << fromStr << endl;
    }
    if (!validMoveString(toStr))
    {
        cout << "This move is invalid: " << toStr << endl;
    }
    // convert move strings into coordinates
    Square fromSquare = Square(fromStr);
    Square toSquare = Square(toStr);
    // get piece at from string
    ChessPiece *piece = getPiece(fromSquare);
    ChessPiece *targetPiece = getPiece(toSquare);
    if (piece == nullptr)
    {
        cout << "There is no piece at position " << fromStr << "!" << endl;
        return;
    }
    if (piece->getColour() != getTurn())
    {
        cout << "It is not " + piece->getColourString() << "'s turn to move!" << endl;
        return;
    }
    // if target square is not a piece - must be a move
    bool capture;
    if (targetPiece == nullptr)
    {
        capture = false;
        if (!validMove(fromSquare, toSquare))
            return;
    }
    else
    {
        capture = true;
        if (!validAttack(fromSquare, toSquare))
            return;
    }

    // bool inCheck = kingIfInCheck(turn);
    // if (inCheck) {
    //     string turnString = getTurnString();
    //     cout << "Move is illegal as " << turnString << "'s is in check" << endl;
    //     return;
    // }

    string turnString = getTurnString();
    if (!ifMoveInCheck(fromSquare, toSquare))
    {
        cout << piece->getName() << " on " << fromSquare.squareRepresentation() << " moving to " << toSquare.squareRepresentation() << " exposes " << getTurnString() << " to be in check!\n";
        return;
    }
    cout << turnString << "'s " << piece->getName() << " moves from " << fromSquare.squareRepresentation() << " to " << toSquare.squareRepresentation();
    if (capture)
    {
        ChessPiece *capturedPiece = board[toSquare.x][toSquare.y];
        string opponentTurnString = getOpponentTurnString();
        cout << " taking " << opponentTurnString << "'s " << capturedPiece->getName();
    }
    cout << endl;
    movePiece(fromSquare, toSquare);
    int opponentTurn = (turn == WHITE) ? BLACK : WHITE;
    bool opponentCheck = kingIfInCheck(opponentTurn);
    if (opponentCheck)
    {
        string opponentTurnString = getOpponentTurnString();
        if (!haveValidMove(opponentTurn))
        {
            cout << opponentTurnString << " is in checkmate" << endl;
        }
        else
        {
            cout << opponentTurnString << " is in check" << endl;
        }
    }
    else
    {
        if (!haveValidMove(opponentTurn))
        {
            cout << "Stalemate!" << endl;
        }
    }
    // printBoard();
    changeTurn();
}

bool ChessBoard::validMove(Square fromSquare, Square toSquare)
{
    // cout << "moving" << endl;
    ChessPiece *piece = getPiece(fromSquare);
    vector<Square> possibleMoves = piece->getMoveSquares(board);
    bool found = false;
    for (auto it = possibleMoves.begin(); it != possibleMoves.end(); it++)
    {
        // cout << "Possible moves: " + it->squareRepresentation() << endl;
        if (*it == toSquare)
        {
            found = true;
        }
    }
    if (!found)
    {
        // cout << "Not possible to move " << piece->getInfo() << " to " << toSquare.squareRepresentation() << endl;
        string turnString = getTurnString();
        cout << turnString << "'s " << piece->getName() << " cannot move to " << toSquare.squareRepresentation() << "!" << endl;
        return false;
    }
    return true;
}

bool ChessBoard::validAttack(Square fromSquare, Square toSquare)
{
    // cout << "attacking" << endl;
    ChessPiece *piece = getPiece(fromSquare);
    vector<Square> possibleAttacks = piece->getAttackSquares(board);
    bool found = false;
    for (auto it = possibleAttacks.begin(); it != possibleAttacks.end(); it++)
    {
        // cout << "Possible attacks: " + it->squareRepresentation() << endl;
        if (*it == toSquare)
        {
            found = true;
        }
    }
    if (!found)
    {
        // cout << "Not possible to capture " << getPiece(toSquare)->getInfo() << " with " << piece->getInfo() << endl;
        string turnString = getTurnString();
        cout << turnString << "'s " << piece->getName() << " cannot move to " << toSquare.squareRepresentation() << "!" << endl;
        return false;
    }
    return true;
}

bool ChessBoard::ifMoveInCheck(Square fromSquare, Square toSquare)
{
    ChessPiece *piece = getPiece(fromSquare);
    ChessPiece *temp = board[toSquare.x][toSquare.y];
    movePiece(fromSquare, toSquare);
    bool safeMove = true;
    if (kingIfInCheck(piece->getColour()))
    {
        safeMove = false;
    }
    movePiece(toSquare, fromSquare);
    board[toSquare.x][toSquare.y] = temp;
    return safeMove;
}

bool ChessBoard::kingIfInCheck(int colour)
{
    Square kingSquare(-1, -1);
    vector<ChessPiece *> opponentPieces;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] != nullptr && board[i][j]->getName() == "King" && board[i][j]->getColour() == colour)
            {
                kingSquare = board[i][j]->getPosition();
            }
            if (board[i][j] != nullptr && board[i][j]->getColour() != colour)
            {
                opponentPieces.push_back(board[i][j]);
            }
        }
    }
    // cout << "found king" << endl;
    // cout << opponentPieces.size() << endl;
    // cout << kingSquare.squareRepresentation() << endl;
    for (auto it = opponentPieces.begin(); it != opponentPieces.end(); it++)
    {
        vector<Square> attackedSquares;
        attackedSquares = (*it)->getAttackSquares(board);
        // if ((*it)->getName() == "Bishop") {
        //     for (auto its = attackedSquares.begin(); its != attackedSquares.end(); its++)
        //     {
        //         cout << "square: " << (its)->squareRepresentation() << endl;
        //     }
        // }
        for (Square square : attackedSquares)
        {
            if (square == kingSquare)
            {
                // cout << "king is attacked" << endl;
                // cout << "attacked by: " << (*it)->getInfo() << endl;
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::haveValidMove(int turn)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            ChessPiece *piece = board[i][j];
            if (piece != nullptr && piece->getColour() == turn)
            {
                Square fromSquare = piece->getPosition();
                vector<Square> moves = piece->getMoveSquares(board);
                for (Square move : moves)
                {
                    ChessPiece *temp = getPiece(move);
                    movePiece(fromSquare, move);
                    bool checked = kingIfInCheck(turn);
                    movePiece(move, fromSquare);
                    board[move.x][move.y] = temp;
                    if (!checked)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ChessBoard::validMoveString(std::string move)
{
    if (move.length() != 2)
        return false;
    if (move[0] < 'A' || move[0] > 'H' || move[1] < '1' || move[1] > '8')
        return false;
    return true;
}

void ChessBoard::changeTurn()
{
    turn *= -1;
}

ChessPiece *ChessBoard::getPiece(Square square)
{
    return board[square.x][square.y];
}

int ChessBoard::getTurn()
{
    return turn;
}

string ChessBoard::getTurnString()
{
    string turnString = (turn == WHITE) ? "White" : "Black";
    return turnString;
}

string ChessBoard::getOpponentTurnString()
{
    string opponentTurnString = (turn == WHITE) ? "Black" : "White";
    return opponentTurnString;
}

void ChessBoard::movePiece(Square fromSquare, Square toSquare)
{
    ChessPiece *piece = getPiece(fromSquare);
    board[toSquare.x][toSquare.y] = piece;
    if (piece != nullptr)
    {
        piece->setPosition(toSquare);
    }
    board[fromSquare.x][fromSquare.y] = nullptr;
    piece->setMoved();
}

void ChessBoard::setBoard()
{
    cout << "A new chess game is started!" << endl;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = nullptr;
        }
    }
    // initialising pawns
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        board[1][i] = new Pawn(BLACK, Square(1, i));
        board[6][i] = new Pawn(WHITE, Square(6, i));
    }
    // board[6][4] = new Pawn(WHITE, Square(6, 4));
    // board[5][5] = new Pawn(WHITE, Square(5, 5));
    // board[4][5] = new Pawn(BLACK, Square(4, 5));
    // board[7][4] = new Pawn(WHITE, Square(7, 4));
    // placing rooks
    board[0][0] = new Rook(BLACK, Square(0, 0));
    board[0][BOARD_SIZE - 1] = new Rook(BLACK, Square(0, BOARD_SIZE - 1));
    board[BOARD_SIZE - 1][0] = new Rook(WHITE, Square(BOARD_SIZE - 1, 0));
    board[BOARD_SIZE - 1][BOARD_SIZE - 1] = new Rook(WHITE, Square(BOARD_SIZE - 1, BOARD_SIZE - 1));
    // placing bishops
    board[BOARD_SIZE - 1][2] = new Bishop(WHITE, Square(BOARD_SIZE - 1, 2));
    board[BOARD_SIZE - 1][5] = new Bishop(WHITE, Square(BOARD_SIZE - 1, 5));
    board[0][2] = new Bishop(BLACK, Square(0, 2));
    board[0][5] = new Bishop(BLACK, Square(0, 5));
    // placing queen
    // board[BOARD_SIZE - 1][3] = new Queen(WHITE, Square(BOARD_SIZE - 1, 3));
    // board[0][3] = new Queen(BLACK, Square(0, 3));
    // placing king
    board[BOARD_SIZE - 1][4] = new King(WHITE, Square(BOARD_SIZE - 1, 4));
    board[0][4] = new King(BLACK, Square(0, 4));
    // placing queen
    board[0][3] = new Queen(BLACK, Square(0, 3));
    board[BOARD_SIZE - 1][3] = new Queen(WHITE, Square(BOARD_SIZE - 1, 3));
    // placing knights
    board[0][1] = new Knight(BLACK, Square(0, 1));
    board[0][6] = new Knight(BLACK, Square(0, 6));
    board[BOARD_SIZE - 1][1] = new Knight(WHITE, Square(BOARD_SIZE - 1, 1));
    board[BOARD_SIZE - 1][6] = new Knight(WHITE, Square(BOARD_SIZE - 1, 6));

    turn = WHITE;
}

void ChessBoard::clearBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            delete board[i][j];
        }
    }
}

void ChessBoard::resetBoard()
{
    clearBoard();
    setBoard();
}

void ChessBoard::printRowKey()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cout << "  " << (char)('A' + i) << " ";
    }
    cout << endl;
}

void ChessBoard::printRowFrame()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cout << "+---";
    }
    cout << "+\n";
}

void ChessBoard::printBoard()
{
    cout << "  ";
    printRowKey();
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cout << "  ";
        printRowFrame();
        cout << BOARD_SIZE - i << " ";
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            cout << "| " << board[i][j] << " ";
        }
        cout << "| " << BOARD_SIZE - i << endl;
    }
    cout << "  ";
    printRowFrame();
    cout << "  ";
    printRowKey();
}