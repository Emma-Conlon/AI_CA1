#pragma once
#include "Board.h";
#include "Game.h"
struct AiMove
{
	AiMove() {}
	AiMove(int Score) : score(Score) {}
	int x;
	int y;
	int score;
};


class AI
{
public:
	void init();
    void preformMove(Board& board1, Board& board2, Board& board3, Board& board4);
private:
	
	AiMove getBestMove(Board& board1, Board& board2, Board& board3, Board& board4, GameState copy, int depth = 0);

	

};

