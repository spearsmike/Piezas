/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
#include <cstdlib>

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	srand(9001);
	ASSERT_TRUE(true);
}

TEST(PiezasTest, constructor_initialization_first_space)
{
	Piezas game = Piezas();
	ASSERT_EQ(game.pieceAt(0, 0), Blank);
}

TEST(PiezasTest, constructor_initialization_first_row)
{
	Piezas game = Piezas();
	for(int i=0; i<BOARD_ROWS; i++) {
		ASSERT_EQ(game.pieceAt(i, 0), Blank);
	}
}

TEST(PiezasTest, constructor_initialization_all_rows)
{
	Piezas game = Piezas();
	for(int i=0; i<BOARD_ROWS; i++) {
		for(int j=0; j<BOARD_COLS; j++) {
			ASSERT_EQ(game.pieceAt(i, j), Blank);
		}
	}
}

TEST(PiezasTest, turn)
{
	Piezas game = Piezas();
	ASSERT_EQ(game.dropPiece(0), X);
	ASSERT_EQ(game.dropPiece(0), O);
}

TEST(PiezasTest, drop_piece1)
{
	Piezas game = Piezas();
	ASSERT_EQ(game.dropPiece(0), X);
}

TEST(PiezasTest, drop_piece2)
{
	Piezas game = Piezas();
	game.dropPiece(0);
	ASSERT_NE(game.pieceAt(0, 0), O);
	ASSERT_EQ(game.pieceAt(0, 0), X);
}

TEST(PiezasTest, drop_pieces)
{
	Piezas game = Piezas();
	for(int i=0; i<BOARD_ROWS; i++) {
		game.dropPiece(i);
	}
	for(int i=0; i<BOARD_ROWS; i+=2) {
		ASSERT_EQ(game.pieceAt(0, i), X);
	}
	for(int i=1; i<BOARD_ROWS; i+=2) {
		ASSERT_EQ(game.pieceAt(0, i), O);
	}
}

TEST(PiezasTest, reset)
{
	Piezas game = Piezas();
	for(int i=0; i<BOARD_ROWS; i++) {
		game.dropPiece(i);
	}
	game.reset();
	for(int i=0; i<BOARD_ROWS; i++) {
		ASSERT_EQ(game.pieceAt(0, i), Blank);
	}
}

TEST(PiezasTest, game_state_empty)
{
	Piezas game = Piezas();
	ASSERT_EQ(game.gameState(), Invalid);
}

TEST(PiezasTest, game_state1)
{
	Piezas game = Piezas();
	game.dropPiece(0);
	game.reset();
	ASSERT_EQ(game.pieceAt(0, 0), Blank);
}

TEST(PiezasTest, game_state2)
{
	Piezas game = Piezas();
	for(int i=0; i<BOARD_ROWS; i++) {
		game.dropPiece(i);
	}
	game.reset();
	for(int i=0; i<BOARD_ROWS; i++) {
		ASSERT_EQ(game.pieceAt(0, i), Blank);
	}
}

TEST(PiezasTest, game_state_one_piece)
{
	Piezas game = Piezas();
	game.dropPiece(0);
	ASSERT_EQ(game.gameState(), Invalid);
}

TEST(PiezasTest, tie1)
{
	/** Game board
	 * X O X O
	 * X O X O
	 * X O X O
	 */
	Piezas game = Piezas();
	for(int i=0; i<BOARD_ROWS*BOARD_COLS; i=(i+1)%BOARD_COLS) {
		game.dropPiece(i);
	}
	ASSERT_EQ(game.gameState(), Blank);
}

TEST(PiezasTest, Xwin1)
{
	/** Game board
	 * X X X X
	 * O O O O
	 * X X X X
	 */
	Piezas game = Piezas();
	for(int i=0; i<BOARD_COLS; i++) {
		for(int j=0; j<BOARD_ROWS; j++) {
			game.dropPiece(i);
		}
	}
	ASSERT_EQ(game.gameState(), X);
}

TEST(PiezasTest, Owin1)
{

	/** Game board
	 * O X X X
	 * O O O O
	 * X X X O
	 */
	Piezas game = Piezas();
	while(game.gameState() == Invalid)
        game.dropPiece(rand()%BOARD_COLS);
	ASSERT_EQ(game.gameState(), O);
}

TEST(PiezasTest, Owin2)
{

	/** Game board
	 * X O O X
	 * X X O O
	 * O X O X
	 */
	Piezas game = Piezas();
	while(game.gameState() == Invalid)
        game.dropPiece(rand()%BOARD_COLS);
	ASSERT_EQ(game.gameState(), O);
}

TEST(PiezasTest, Owin3)
{

	/** Game board
	 * O X O X
	 * X X O O
	 * X O O X
	 */
	Piezas game = Piezas();
	while(game.gameState() == Invalid)
        game.dropPiece(rand()%BOARD_COLS);
	ASSERT_EQ(game.gameState(), O);
}


TEST(PiezasTest, Owin4)
{

	/** Game board
	 * X O X X
	 * O O O O
	 * X X X O
	 */
	Piezas game = Piezas();
	while(game.gameState() == Invalid)
        game.dropPiece(rand()%BOARD_COLS);
	ASSERT_EQ(game.gameState(), O);
}

TEST(PiezasTest, tie2)
{

	/** Game board
	 * X X O O                                                                                                 
	 * O X X X                                                                                                 
	 * O O O X 
	 */
	Piezas game = Piezas();
	while(game.gameState() == Invalid)
        game.dropPiece(rand()%BOARD_COLS);
	ASSERT_EQ(game.gameState(), O);
}

TEST(PiezasTest, Xwin2)
{

	/** Game board
	 * X X X X                                                                                                 
	 * O O O X                                                                                                 
	 * O O X O
	 */
	Piezas game = Piezas();
	while(game.gameState() == Invalid)
        game.dropPiece(rand()%BOARD_COLS);
	ASSERT_EQ(game.gameState(), O);
}