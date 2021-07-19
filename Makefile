comp = g++ -g -Wall -std=c++11
general = ChessMain.o ChessBoard.o
pieces = pawn.o rook.o bishop.o queen.o king.o knight.o

chess: $(pieces) ChessBoard.o ChessMain.o square.o
	$(comp) $(pieces) ChessMain.o ChessBoard.o square.o -o chess

# compile chessmain object
ChessMain.o: ChessMain.cpp
	$(comp) -c ChessMain.cpp

# compile chessboard object
ChessBoard.o: ChessBoard.cpp ChessBoard.h
	$(comp) -c ChessBoard.cpp

# # compile pieces
%.o : %.cpp %.h square.h ChessPiece.h
	$(comp) -c $<

# compile square object
square.o: square.cpp square.h 
	$(comp) -c square.cpp

tidy:
	rm -rf *.o

clean:
	rm -rf chess test *.o 
