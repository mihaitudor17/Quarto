#include "stdafx.h"
#include "CppUnitTest.h"

#include "BoardStateChecker.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<> inline std::wstring ToString<BoardStateChecker::State>(const BoardStateChecker::State& t)
			{
				switch (t)
				{
				case BoardStateChecker::State::None:
					return L"None";
				case BoardStateChecker::State::Win:
					return L"Win";
				case BoardStateChecker::State::Draw:
					return L"Draw";
				}
			}
		}
	}
}

namespace QuartoTests
{
	TEST_CLASS(BoardStateCheckerTests)
	{
	public:

		TEST_METHOD(Draw)
		{
			Board board;
			board[{0, 0}] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Tall, Piece::Shape::Square);
			board[{0, 1}] = Piece(Piece::Body::Full, Piece::Color::Light, Piece::Height::Short, Piece::Shape::Round);
			board[{0, 2}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Tall, Piece::Shape::Square);
			board[{0, 3}] = Piece(Piece::Body::Hollow, Piece::Color::Light, Piece::Height::Short, Piece::Shape::Round);
			
			board[{1, 0}] = Piece(Piece::Body::Full, Piece::Color::Light, Piece::Height::Tall, Piece::Shape::Round);
			board[{1, 1}] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);
			board[{1, 2}] = Piece(Piece::Body::Hollow, Piece::Color::Light, Piece::Height::Tall, Piece::Shape::Round);
			board[{1, 3}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);
			
			board[{2, 0}] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Tall, Piece::Shape::Round);
			board[{2, 1}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Tall, Piece::Shape::Round);
			board[{2, 2}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{2, 3}] = Piece(Piece::Body::Hollow, Piece::Color::Light, Piece::Height::Tall, Piece::Shape::Square);
			
			board[{3, 0}] = Piece(Piece::Body::Hollow, Piece::Color::Light, Piece::Height::Short, Piece::Shape::Square);
			board[{3, 1}] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{3, 2}] = Piece(Piece::Body::Full, Piece::Color::Light, Piece::Height::Tall, Piece::Shape::Square);
			Board::Position lastPosition{ 3, 3 };
			board[lastPosition] = Piece(Piece::Body::Full, Piece::Color::Light, Piece::Height::Short, Piece::Shape::Square);

			Assert::AreEqual(BoardStateChecker::State::Draw, BoardStateChecker::Check(board, lastPosition));
		}

		TEST_METHOD(NoneOnePiece)
		{
			Board board;
			Board::Position lastPosition{ 2, 1 };
			board[lastPosition] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);

			Assert::IsTrue(BoardStateChecker::Check(board, lastPosition) == BoardStateChecker::State::None);
		}

		TEST_METHOD(NoneLineOne)
		{
			Board board;
			board[{0, 0}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{0, 1}] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			Board::Position lastPosition{ 0, 2 };
			board[lastPosition] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);

			Assert::IsTrue(BoardStateChecker::Check(board, lastPosition) == BoardStateChecker::State::None);
		}

		TEST_METHOD(WinLineOne)
		{
			Board board;
			board[{0, 0}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{0, 1}] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{0, 2}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Tall, Piece::Shape::Square);
			Board::Position lastPosition {0, 3};
			board[lastPosition] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);

			Assert::IsTrue(BoardStateChecker::Check(board, lastPosition) == BoardStateChecker::State::Win);
		}

		TEST_METHOD(WinColumnThree)
		{
			Board board;
			board[{0, 2}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{1, 2}] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{2, 2}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Tall, Piece::Shape::Square);
			Board::Position lastPosition{ 3, 2 };
			board[lastPosition] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);

			Assert::IsTrue(BoardStateChecker::Check(board, lastPosition) == BoardStateChecker::State::Win);
		}

		TEST_METHOD(WinMainDiagonal)
		{
			Board board;
			board[{0, 0}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{1, 1}] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{2, 2}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Tall, Piece::Shape::Square);
			Board::Position lastPosition{ 3, 3 };
			board[lastPosition] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);

			Assert::IsTrue(BoardStateChecker::Check(board, lastPosition) == BoardStateChecker::State::Win);
		}

		TEST_METHOD(WinSecondaryDiagonal)
		{
			Board board;
			board[{0, 3}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{1, 2}] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Round);
			board[{2, 1}] = Piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Tall, Piece::Shape::Square);
			Board::Position lastPosition{ 3, 0 };
			board[lastPosition] = Piece(Piece::Body::Hollow, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);

			Assert::IsTrue(BoardStateChecker::Check(board, lastPosition) == BoardStateChecker::State::Win);
		}
	};
}