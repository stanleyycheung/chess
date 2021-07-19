#include "ChessBoard.h"

#include <iostream>

using std::cout;

void test1()
{
	ChessBoard cb;
	// cb.submitMove("E2", "F3");
	cb.submitMove("A2", "A3");
	cb.submitMove("E7", "E6");
	cb.submitMove("A3", "A4");
	cb.submitMove("F8", "B4");
	cb.printBoard();
	cb.submitMove("B1", "C3");

	// cb.submitMove("C1", "G5");
	// cb.submitMove("D1", "D8");

	// cb.submitMove("E7", "E6");
}

void test2()
{
	ChessBoard cb;
	cb.submitMove("e4");
	cb.submitMove("e5");
	cb.submitMove("Nc3");
	cb.submitMove("Nf6");
}

void test_engine()
{
	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb;
	// cb.resetBoard();
	cout << '\n';

	cb.submitMove("D7", "D6");
	cout << '\n';

	cb.submitMove("D4", "H6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cout << '\n';

	cb.submitMove("F8", "B4");
	cout << '\n';
}

void test_castling() {
	ChessBoard cb;
	cout << '\n';
	cb.submitMove("E2", "E4");
	cb.submitMove("E7", "E5");
	cout << '\n';
	cb.submitMove("G1", "F3");
	cb.submitMove("G8", "F6");
	cout << '\n';
	cb.submitMove("F1", "C4");
	cb.submitMove("F8", "C5");
	cout << '\n';
	
}

void test_game()
{
	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	ChessBoard cb;
	// cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("E7", "E6");
	// cb.printBoard();
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("D7", "D5");
	// cb.printBoard();
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("F8", "B4");
	// cb.printBoard();
	cout << '\n';

	cb.submitMove("F1", "D3");
	cb.submitMove("B4", "C3");
	// cb.printBoard();
	cout << '\n';

	cb.submitMove("B2", "C3");
	cb.submitMove("H7", "H6");
	cout << '\n';

	cb.submitMove("C1", "A3");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D1", "E2");
	cb.submitMove("D5", "E4");
	cout << '\n';

	cb.submitMove("D3", "E4");
	cb.submitMove("G8", "F6");
	cout << '\n';

	cb.submitMove("E4", "D3");
	cb.submitMove("B7", "B6");
	cout << '\n';

	cb.submitMove("E2", "E6");
	cb.submitMove("F7", "E6");
	cout << '\n';

	cb.submitMove("D3", "G6");
	cout << '\n';
}

int main()
{

	// test1();
	test2();
	// test_engine();
	// test_game();
	return 0;
}
