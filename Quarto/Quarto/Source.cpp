#include "Player.h"
#include "QuartoGame.h"

#include <iostream>

int tests()
{
	Piece piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);
	std::cout << "Full, Dark, Short, Square piece: " << piece << std::endl;

	Board board;
	std::cout << "Empty board:\n" << board << std::endl;
	
	board[{0, 0}] = std::move(piece);
	std::cout << "Moved piece to board:\n" << board << std::endl;

	UnusedPieces unusedPieces;
	std::cout << "All available pieces:\n" << unusedPieces << std::endl;
	unusedPieces.PickPiece("0001");
	std::cout << "Extracted \"0001\" remaining pieces after extracted:\n" << unusedPieces << std::endl;

	Player player("Player_1");
	Piece pickedPiece = player.PickPiece(std::cin, unusedPieces);
	std::cout << "Picked piece: " << pickedPiece << std::endl;
	std::cout << "Remaining pieces:\n" << unusedPieces << std::endl;
	const auto&[line, column] = player.PlacePiece(std::cin, std::move(pickedPiece), board);
	std::cout << "Board after placing piece on position (" 
		<< static_cast<uint16_t>(line) << "," << static_cast<uint16_t>(column) << "):\n" << board;

	return 0;
}

int main()
{
    QuartoGame quartoGame;
    quartoGame.Run();

    return 0;
}