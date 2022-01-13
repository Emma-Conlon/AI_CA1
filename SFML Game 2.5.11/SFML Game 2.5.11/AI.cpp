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
        return AiMove(100 - depth);
    }
    else if (retv == player)
    {
        return AiMove(depth + 1);
    }
    else if (retv == 4)
    {
        return AiMove(depth);
    }


    

    std::vector<AiMove> moves;
    if (depth >= 2)
    {
        AiMove newMove;
        newMove.x = t_move.x;
        newMove.y = t_move.y;
        newMove.z = t_move.z;
        //newMove.score = 12;

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

/// <summary>
/// evaluates 
/// </summary>
/// <param name="m_gameboard">board place</param>
/// <param name="newMove"></param>
/// <param name="copy"></param>
/// <returns></returns>
int AI::evaluation(GameBoard& m_gameboard, AiMove newMove, GameState copy)
{
    
    int score = 0;
    
    m_gameboard.m_boards[newMove.z]->getPiece(newMove.x, newMove.y);
    if (newMove.x == newMove.y &&( newMove.x == 0 || newMove.x == 3))//all corners of every board
    {
        score =6;
    }
    for (int x = 0,int z=x; x < 4; x++)//layers + horizontal
    {
        if (newMove.x == x)
        {
            continue;
        }
        if (m_gameboard.m_boards[z]->getPiece(x, newMove.y).getFillColor() == sf::Color::Yellow)
        {
            score += 2;
        }
    }
    for (int x = 3, int z = x; x >= 0; x--)//layers - horizontal
    {
        if (newMove.x == x)
        {
            continue;
        }
        if (m_gameboard.m_boards[z]->getPiece(x, newMove.y).getFillColor() == sf::Color::Yellow)
        {
            score += 2;
        }
    }
        
        for (int x = 0; x < 4; x++)//horizontal
        {
            if (newMove.x == x)
            {
                continue;
            }
             if (m_gameboard.m_boards[newMove.z]->getPiece(x, newMove.y).getFillColor() == sf::Color::Yellow)
             {
                 score += 2;
             }
        }


        for (int y = 0,int z=y; y < 4; y++)//layers vertical
        {
            if (newMove.y == y)
            {
                continue;
            }
            if (m_gameboard.m_boards[z]->getPiece(newMove.x, y).getFillColor() == sf::Color::Yellow)
            {
                score += 2;
            }
        }

        for (int y = 0, int z = y; y >= 0; y--)//layers vertical
        {
            if (newMove.y == y)
            {
                continue;
            }
            if (m_gameboard.m_boards[z]->getPiece(newMove.x, y).getFillColor() == sf::Color::Yellow)
            {
                score += 2;
            }
        }

        for (int y = 0; y < 4; y++)//vertical
        {
            if (newMove.y== y)
            {
                continue;
            }
            if (m_gameboard.m_boards[newMove.z]->getPiece(newMove.x, y).getFillColor() == sf::Color::Yellow)
            {
                score += 2;
            }
        }

        for (int z = 0; z < 4; z++)//layers
        {
            if (newMove.z == z)
            {
                continue;
            }
            if (m_gameboard.m_boards[z]->getPiece(newMove.x, newMove.y).getFillColor() == sf::Color::Yellow)
            {
                score += 2;
            }
        }

         //Layer diagonals 
        for (int x = 0, int y = 0,int z=0; x < 4; x++,y++,z++)
        {
            if (newMove.x == x)
            {
                continue;
            }
            if (m_gameboard.m_boards[z]->getPiece(x, y).getFillColor() == sf::Color::Yellow)
            {
                score += 2;
            }
          
        }
        for (int x = 3, int y = 3,int z=3; x >= 0; x--,y--,z--)
        {
            if (newMove.x == x)
            {
                continue;
            }
            if (m_gameboard.m_boards[z]->getPiece(x, y).getFillColor() == sf::Color::Yellow)
            {
                score += 2;
            }

        }
        //normal diagonals 
        for (int x = 3, int y = x; x >= 0; x--)
        {
            if (newMove.x == x)
            {
                continue;
            }
            if (m_gameboard.m_boards[newMove.z]->getPiece(x, y).getFillColor() == sf::Color::Yellow)
            {
                score += 2;
            }

        }
        for (int x = 0, int y = x; x < 4; x++)
        {
            if (newMove.x == x)
            {
                continue;
            }
            if (m_gameboard.m_boards[newMove.z]->getPiece(x, y).getFillColor() == sf::Color::Yellow)
            {
                score += 2;
            }

        }
    //onlys 1 piece ;-;
    if (m_gameboard.m_boards[newMove.z]->getPiece(newMove.x, newMove.y).getFillColor() == sf::Color::Yellow)//player-
    {
        if (copy == playerTurn)
        {
            score = 5;
        }
        else if (copy == AiTurn)
        {
            score = -5;
        }
        
        //if (newMove.x < 3)//x
        //{
        //    if (m_gameboard.m_boards[newMove.z]->getPiece(newMove.x + 1, newMove.y).getFillColor() == sf::Color::Yellow)//player-
        //    {
        //        if (copy == playerTurn)
        //        {
        //            score = 6;
        //        }
        //        else if (copy == AiTurn)
        //        {
        //            score = -6;
        //        }
        //        if (newMove.x < 2)
        //        {
        //            if (m_gameboard.m_boards[newMove.z]->getPiece(newMove.x + 2, newMove.y).getFillColor() == sf::Color::Yellow)//player-
        //            {
        //                if (copy == playerTurn)
        //                {
        //                    score = 7;
        //                }
        //                else if (copy == AiTurn)
        //                {
        //                    score = -7;
        //                }
        //                if (newMove.x < 1)
        //                {
        //                    if (m_gameboard.m_boards[newMove.z]->getPiece(newMove.x + 3, newMove.y).getFillColor() == sf::Color::Yellow)//player-
        //                    {
        //                        if (copy == playerTurn)
        //                        {
        //                            score = 8;
        //                        }
        //                        else if (copy == AiTurn)
        //                        {
        //                            score = -8;
        //                        }
        //                    }
        //                }
        //            }
        //        }
        //    }

        //}
       
    }
    if (m_gameboard.m_boards[newMove.z]->getPiece(newMove.x, newMove.y).getFillColor() == sf::Color::Red)//AI+
    {
        if (copy == playerTurn)
        {
            score=-5;
        }
        else if(copy == AiTurn) 
        {
            score =5;
        }
    }
   
    //evalgroup(m_gameboard, score, copy);
    if (copy == playerTurn)
    {
        score = -score;
    }
    return score;
}

int AI::evalgroup(GameBoard& m_gameboard, int score, GameState copy)
{
    /*if (copy == playerTurn)
    {
        score = +30;
    }
    else if (copy == AiTurn)
    {
        score -= 15;
    }*/
    return 0;
}
