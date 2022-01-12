#include "Piece.h"
#include <cassert>

Piece::Piece() :
	Piece(Body::None, Color::None, Height::None, Shape::None)
{
	// Empty
}

Piece::Piece(Body body, Color color, Height height, Shape shape) :
	m_body(body),
	m_color(color),
	m_height(height),
	m_shape(shape)
{
	// Empty
	static_assert(sizeof(*this) <= 1, "This class should be 1 byte in size");
}

Piece::Piece(const Piece& other)
{
	*this = other;
}

Piece::Piece(Piece&& other)
{
	*this = std::move(other);
}

Piece::~Piece()
{
	m_body = Body::None;
	m_color = Color::None;
	m_height = Height::None;
	m_shape = Shape::None;
}

Piece& Piece::operator= (const Piece& other)
{
	// should not copy construct or assign this class in Quarto Game
	// assert(false);

	m_body = other.m_body;
	m_color = other.m_color;
	m_height = other.m_height;
	m_shape = other.m_shape;

	return *this;
}

Piece& Piece::operator= (Piece&& other)
{
	m_body = other.m_body;
	m_color = other.m_color;
	m_height = other.m_height;
	m_shape = other.m_shape;

	//other.m_body = Body::None;
	//other.m_color = Color::None;
	//other.m_height = Height::None;
	//other.m_shape = Shape::None;

	new(&other) Piece;

	return *this;
}

Piece::Body Piece::GetBody() const
{
	return m_body;
}

Piece::Color Piece::GetColor() const
{
	return m_color;
}

Piece::Height Piece::GetHeight() const
{
	return m_height;
}

Piece::Shape Piece::GetShape() const
{
	return m_shape;
}

Piece Piece::Intersection(const Piece& other) const
{
	Piece piece = *this;

	if (piece.m_body != other.m_body)
		piece.m_body = Body::None;

	if (piece.m_color != other.m_color)
		piece.m_color = Color::None;

	if (piece.m_height != other.m_height)
		piece.m_height = Height::None;

	if (piece.m_shape != other.m_shape)
		piece.m_shape = Shape::None;

	return piece;
}

bool Piece::HasAnyFeatureSet() const
{
	return 
		GetBody() != Piece::Body::None ||
		GetColor() != Piece::Color::None ||
		GetHeight() != Piece::Height::None ||
		GetShape() != Piece::Shape::None;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
	return os << 
		static_cast<int>(piece.m_body) - 1 << 
		static_cast<int>(piece.m_color) - 1 << 
		static_cast<int>(piece.m_height) - 1 << 
		static_cast<int>(piece.m_shape) - 1;
}
