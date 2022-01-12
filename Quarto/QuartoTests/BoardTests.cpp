#include "stdafx.h"
#include "CppUnitTest.h"

#include "Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QuartoTests
{
	TEST_CLASS(BoardTests)
	{
	public:

		TEST_METHOD(DefaultConstructorEmptyBoard)
		{
			Board board;
			Board::Position position;
			auto&[i, j] = position;
			for (i = 0; i < Board::kHeight; ++i)
				for (j = 0; j < Board::kWidth; ++j)
					if (board[position].has_value())
						Assert::Fail();
		}

		TEST_METHOD(SetGetAtOneOne)
		{
			Board board;
			Piece piece;
			Board::Position position{ 1, 1 };
			board[position] = piece;

			Assert::IsTrue(board[position].has_value());
			
			// Solution 1
			int memDiff = memcmp(&board[position], &piece, sizeof piece);
			Assert::AreEqual(0, memDiff);

			// Solution 2
			Assert::IsTrue(
				board[position]->GetBody() == piece.GetBody() &&
				board[position]->GetColor() == piece.GetColor() &&
				board[position]->GetHeight() == piece.GetHeight() &&
				board[position]->GetShape() == piece.GetShape()
			);

			// Solution 3
			// overload operator == for Piece
			// and use Assert::AreEqual(*board[position], piece)
		}

		TEST_METHOD(GetAtOneOneConst)
		{
			const Board board;
			Board::Position position{ 1, 1 };

			Assert::IsFalse(board[position].has_value());
		}

		TEST_METHOD(GetAtMinusOneOne)
		{
			Board board;
			Board::Position position{ -1, 1 };

			Assert::ExpectException<const char*>( [&]() {
				board[position];
			});
		}

		TEST_METHOD(GetAtMinusOneOneConst)
		{
			const Board board;
			Board::Position position{ -1, 1 };

			Assert::ExpectException<std::out_of_range>([&]() {
				board[position];
			});
		}

		TEST_METHOD(GetAtOneMinusOne)
		{
			Board board;
			Board::Position position{ 1, -1 };

			Assert::ExpectException<const char*>([&]() {
				board[position];
			});
		}

		TEST_METHOD(GetAtOneMinusOneConst)
		{
			const Board board;
			Board::Position position{ 1, -1 };

			Assert::ExpectException<std::out_of_range>([&]() {
				board[position];
			});
		}
	};
}