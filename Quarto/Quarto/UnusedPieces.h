#pragma once

#include "Piece.h"

#include <unordered_map>

// Holds all the unused pieces throughout the game.
class UnusedPieces
{
public:
	// Creates a pool with the 16 possible pieces.
	UnusedPieces();

	// Removes the piece found with given name and returns it.
	// Raises exception if it is not found.
	Piece PickPiece(const std::string& name);
	
	friend std::ostream & operator << (std::ostream& os, const UnusedPieces& unusedPieces);

private:
	void GeneratePieces();
	void EmplacePiece(Piece&& piece);

private:
	std::unordered_map<std::string, Piece> m_pool;
};

