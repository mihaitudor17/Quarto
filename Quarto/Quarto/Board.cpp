#include "Board.h"

#include <cassert>

const std::optional<Piece> Board::base_iterator::kInvalidPiece = Piece();
const char kEmptyBoardCell[] = "____";

Board::base_iterator::base_iterator(std::array<std::optional<Piece>, kSize>& data, size_t offset) :
	m_data(data), m_offset(offset)
{
	// empty
}

const std::optional<Piece>& Board::base_iterator::operator*()
{
	assert(m_offset < kSize); 
	return m_data[m_offset].has_value() ? m_data[m_offset] : kInvalidPiece;
}

const std::optional<Piece>* Board::base_iterator::operator->()
{
	return &**this;
}

bool Board::base_iterator::operator!=(const base_iterator& other)
{
	return m_offset != other.m_offset;
}

Board::line_iterator& Board::line_iterator::operator++()
{
	++m_offset; 
	return *this;
}

Board::line_iterator Board::line_iterator::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

Board::column_iterator& Board::column_iterator::operator++()
{
	m_offset += kWidth; 
	return *this;
}

Board::column_iterator Board::column_iterator::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

Board::main_diagonal_iterator& Board::main_diagonal_iterator::operator++()
{
	m_offset += kWidth + 1; 
	return *this;
}

Board::main_diagonal_iterator Board::main_diagonal_iterator::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

Board::secondary_diagonal_iterator& Board::secondary_diagonal_iterator::operator++()
{
	m_offset += kWidth - 1; 
	return *this;
}

Board::secondary_diagonal_iterator Board::secondary_diagonal_iterator::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

const std::optional<Piece>& Board::operator[](const Position& position) const
{
	const auto&[line, column] = position;

	if (line >= kHeight || column >= kWidth)
		throw std::out_of_range("Board index out of bound.");

	return m_pieces[line * kWidth + column];
}

std::optional<Piece>& Board::operator[](const Position& position)
{
	const auto&[line, column] = position;

	if (line >= kHeight || column >= kWidth)
		throw "Board index out of bound.";

	return m_pieces[line * kWidth + column];
}

std::pair<Board::line_iterator, Board::line_iterator> Board::GetLine(uint32_t index)
{
	return std::make_pair(line_iterator(m_pieces, index * kWidth), line_iterator(m_pieces, (index + 1) * kWidth));
}

std::pair<Board::column_iterator, Board::column_iterator> Board::GetColumn(uint32_t index)
{
	return std::make_pair(column_iterator(m_pieces, index), column_iterator(m_pieces, kSize + index));
}

std::pair<Board::main_diagonal_iterator, Board::main_diagonal_iterator> Board::GetMainDiagonal()
{
	return std::make_pair(main_diagonal_iterator(m_pieces, 0), main_diagonal_iterator(m_pieces, kSize + kWidth));
}

std::pair<Board::secondary_diagonal_iterator, Board::secondary_diagonal_iterator> Board::GetSecondaryDiagonal()
{
	return std::make_pair(secondary_diagonal_iterator(m_pieces, kWidth - 1), secondary_diagonal_iterator(m_pieces, kSize - 1));
}

bool Board::IsFull() const
{
	return std::all_of(
		m_pieces.begin(), 
		m_pieces.end(),
		[](const std::optional<Piece>& optionalPiece)
		{
			return optionalPiece.has_value();
		}
	);
}

std::ostream & operator<<(std::ostream & os, const Board & board)
{
	Board::Position position;
	auto&[line, column] = position;

	for (line = 0; line < Board::kHeight; ++line)
	{
		for (column = 0; column < Board::kWidth; ++column)
		{
			if (board[position])
				os << *board[position];
			else
				os << kEmptyBoardCell;	// TODO: change this to invalid piece, when possible
			os << ' ';
		}
		os << std::endl;
	}

	return os;
}