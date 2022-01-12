#include "UnusedPieces.h"

#include <sstream>
#include <array>
#include <algorithm>

UnusedPieces::UnusedPieces()
{
	GeneratePieces();
}

Piece UnusedPieces::PickPiece(const std::string& name)
{
	/*auto itMap = m_pool.find(name);
	if (itMap != m_pool.end())
	{
		auto piece = std::move(itMap->second);
		m_pool.erase(itMap);
		return piece;
	}
	else
		throw "Piece not found";*/

	auto node = m_pool.extract(name);
	if (node)
		return std::move(node.mapped());
	else
		throw "Piece not found";
}

std::ostream & operator <<(std::ostream& os, const UnusedPieces& unusedPieces)
{
	/*for (const auto &it : unusedPieces.m_pool)
		os << it.first << " ";*/

	for (const auto&[pieceName, piece] : unusedPieces.m_pool)
		os << pieceName << "  ";
	return os;
}

void UnusedPieces::GeneratePieces()
{
	const uint8_t kPermutationPoolSize = 8;
	std::array<uint8_t, kPermutationPoolSize> permutationPool = { 1, 1, 1, 1, 2, 2, 2, 2 };
	const uint8_t kMaxPermutations = 5;
	const uint8_t kPermutationSize = 4;

	for (uint8_t currentPermutation = 0; currentPermutation < kMaxPermutations; ++currentPermutation)
	{
		auto itPoolBegin = permutationPool.begin() + currentPermutation;
		auto itPoolEnd = permutationPool.begin() + currentPermutation + kPermutationSize;

		do
		{
			EmplacePiece(Piece(
				static_cast<Piece::Body>(*itPoolBegin),
				static_cast<Piece::Color>(*(itPoolBegin + 1)),
				static_cast<Piece::Height>(*(itPoolBegin + 2)),
				static_cast<Piece::Shape>(*(itPoolBegin + 3))
			));
		} while (std::next_permutation(itPoolBegin, itPoolEnd));
	}
}

void UnusedPieces::EmplacePiece(Piece&& piece)
{
	std::stringstream stringStream;
	stringStream << piece;
	m_pool.insert(std::make_pair(stringStream.str(), std::forward<Piece&&>(piece)));
}
