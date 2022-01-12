#include "AI.h"

#include <vector>
void AI::init(GameState copy)
{
    state = copy;
}
void AI::preformMove(GameBoard& m_gameboard)
{
    AiMove bestMove = getBestMove(m_gameboard, state,0,AiMove());
    m_gameboard.m_boards[bestMove.z]->setPiece(bestMove.x, bestMove.y, sf::Color::Red);
}
AiMove AI::getBestMove(GameBoard& m_gameboard, GameState copy, int depth, AiMove t_move)
{
    int retv = m_gameboard.victoryCheck(copy);
    if (retv == ai)
    {
        return AiMove(10 - depth);
    }
    else if (retv == player)
    {
        return AiMove(depth - 10);
    }
    else if (retv == 4)
    {
        return AiMove(0);
    }


    

    std::vector<AiMove> moves;
    if (depth >= 2)
    {
        AiMove newMove;
        newMove.x = t_move.x;
        newMove.y = t_move.y;
        newMove.z = t_move.z;
        newMove.score = 12;

        return newMove;
    }
    for (int z = 0; z < 4; z++)
    {
        for (int x = 0; x < 4; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                if (m_gameboard.m_boards[z]->getPiece(x, y).getFillColor() == sf::Color::White)
                {
                    AiMove move;
                    move.x = x;
                    move.y = y;
                    move.z = z;
                    if (copy == playerTurn)
                    {

                        m_gameboard.m_boards[z]->setPiece(x, y, sf::Color::Yellow);
                        move.score = getBestMove(m_gameboard, GameState::AiTurn, depth+1,move).score;

                    }
                    if(copy ==AiTurn)
                    {
                        
                        m_gameboard.m_boards[z]->setPiece(x, y, sf::Color::Red);
                        move.score = getBestMove(m_gameboard, GameState::playerTurn, depth+1,move).score;

                    }
                    
                         

                         moves.push_back(move);
                         
                         m_gameboard.m_boards[z]->setPiece(x, y, sf::Color::White);
                   
                }
            }

        }

    }

    int bestMove = 0;
    if (copy == playerTurn)
    {
        int bestScore = -100000;
        for (size_t i = 0; i < moves.size(); i++)
        {
            if (moves[i].score > bestScore)
            {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
    else
    {
        int bestScore = 100000;
        for (size_t i = 0; i < moves.size(); i++)
        {
            if (moves[i].score < bestScore)
            {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
    return moves[bestMove];
}
