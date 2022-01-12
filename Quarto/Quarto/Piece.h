#pragma once

#include <iostream>

class Piece
{
public:
	enum class Body : uint8_t
	{
		None,
		Full,
		Hollow
	};

	enum class Color : uint8_t
	{
		None,
		Dark,
		Light
	};

	enum class Height : uint8_t
	{
		None,
		Short,
		Tall
	};

	enum class Shape : uint8_t
	{
		None,
		Round,
		Square
	};

public:
	Piece();
	Piece(Body body, Color color, Height height, Shape shape);
	Piece(const Piece &other);
	Piece(Piece && other);
	~Piece();

	Piece & operator = (const Piece & other);
	Piece & operator = (Piece && other);

	Piece & operator &= (const Piece & other);

	Body GetBody() const;;
	Color GetColor() const;
	Height GetHeight() const;
	Shape GetShape() const;

	Piece Intersection(const Piece& piece) const;
	bool HasAnyFeatureSet() const;

	friend std::ostream& operator << (std::ostream& os, const Piece& piece);

private:
	Body m_body : 2;
	Color m_color : 2;
	Height m_height : 2;
	Shape m_shape : 2;
};

