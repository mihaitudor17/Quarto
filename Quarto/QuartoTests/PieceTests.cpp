#include "stdafx.h"
#include "CppUnitTest.h"

#include "Piece.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QuartoTests
{		
	TEST_CLASS(PieceTests)
	{
	public:
		
		TEST_METHOD(DefaultConstructor)
		{
			Piece piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);

			Assert::IsTrue(Piece::Body::Full == piece.GetBody());
			Assert::IsTrue(Piece::Color::Dark == piece.GetColor());
			Assert::IsTrue(Piece::Height::Short == piece.GetHeight());
			Assert::IsTrue(Piece::Shape::Square == piece.GetShape());
		}

		TEST_METHOD(Print)
		{
			Piece piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);

			std::stringstream stream;
			stream << piece;
			Assert::AreEqual(std::string("0001"), stream.str(), L"If you see this message, piece is not printed correctly");
		}
	};
}