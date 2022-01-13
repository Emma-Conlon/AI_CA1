#pragma once
#include "GameBoard.h";
struct AiMove
{
	AiMove() {}
	AiMove(int Score) : score(Score) {}
	int x;
	int y;
	int z;
	int score;
};


class AI
{
public:
	void init(GameState copy);
    void preformMove(GameBoard &m_gameboard,int t_maxD);
private:
	
	AiMove getBestMove(GameBoard& m_gameboard, GameState copy, int depth, AiMove move);
	int evaluation(GameBoard& m_gameboard,AiMove newMove, GameState copy);
	GameState state;
	int ai = 1;
	int player = 2;
	int maxDepth = 1;
	int easy = -10;
	int hard = 0;
};

