#pragma once

#include "Piece.h"

#include <array>
#include <optional>

class Board
{
public:
	static const size_t kWidth = 4;
	static const size_t kHeight = 4;
	static const size_t kSize = kWidth * kHeight;

public:
	using Position = std::pair<uint8_t, uint8_t>;

    class base_iterator
    {
        static const std::optional<Piece> kInvalidPiece;

    public:
		base_iterator(std::array<std::optional<Piece>, kSize>& data, size_t offset);
		const std::optional<Piece>& operator *();
		const std::optional<Piece>* operator ->();
		bool operator != (const base_iterator& other);

    protected:
        std::array<std::optional<Piece>, kSize>& m_data;
        size_t m_offset;
    };

    class line_iterator : public base_iterator
    {
    public:
        using base_iterator::base_iterator;

        line_iterator& operator ++();
        line_iterator operator ++(int);
    };

    class column_iterator : public base_iterator
    {
    public:
        using base_iterator::base_iterator;

        column_iterator& operator ++();
        column_iterator operator ++(int);
    };

    class main_diagonal_iterator : public base_iterator
    {
    public:
        using base_iterator::base_iterator;

        main_diagonal_iterator& operator ++();
        main_diagonal_iterator operator ++(int);
    };

    class secondary_diagonal_iterator : public base_iterator
    {
    public:
        using base_iterator::base_iterator;

        secondary_diagonal_iterator& operator ++();
        secondary_diagonal_iterator operator ++(int);
    };

public:
	Board() = default;

	// Getter
	const std::optional<Piece>& operator[] (const Position& pos) const;
	// Getter and/or Setter
	std::optional<Piece>& operator[] (const Position& pos);

	std::pair<line_iterator, line_iterator> GetLine(uint32_t index);
    std::pair<column_iterator, column_iterator> GetColumn(uint32_t index);
    std::pair<main_diagonal_iterator, main_diagonal_iterator> GetMainDiagonal();
    std::pair<secondary_diagonal_iterator, secondary_diagonal_iterator> GetSecondaryDiagonal();

	bool IsFull() const;

	friend std::ostream& operator << (std::ostream& os, const Board& board);

private:
	std::array<std::optional<Piece>, kSize> m_pieces;
};

