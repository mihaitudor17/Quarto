#include "Player.h"

#include <string>

Player::Player(const std::string& name) :
	m_name(name)
{
	// Empty
}

Piece Player::PickPiece(std::istream& in, UnusedPieces& unusedPieces) const
{
	std::string pickedPieceName;
	in >> pickedPieceName;
	Piece pickedPiece = unusedPieces.PickPiece(pickedPieceName);
	return pickedPiece;
}

Board::Position Player::PlacePiece(std::istream& in, Piece&& piece, Board& board) const
{
	uint16_t line = UINT16_MAX;
	uint16_t column = UINT16_MAX;

	if (in >> line)
		if (in >> column)
		{
			Board::Position position = { static_cast<uint8_t>(line), static_cast<uint8_t>(column) };

			auto& optionalPiece = board[position];

			if (optionalPiece)
				throw "That position is occupied by another piece.";

			optionalPiece = std::move(piece);

			return position;
		}

	in.clear();
	in.seekg(std::ios::end);
	// in.ignore(std::numeric_limits<size_t>::max());

	throw "Please enter only two numbers from 0 to 3.";
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os << player.m_name;
}
