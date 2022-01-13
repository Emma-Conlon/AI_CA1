#include "AI.h"

#include <vector>
void AI::init(GameState copy)
{
    state = copy;
}
void AI::preformMove(GameBoard& m_gameboard,int t_maxD)
{
    maxDepth = t_maxD;
    AiMove bestMove = getBestMove(m_gameboard, state,0,AiMove(),-10000,10000);
    m_gameboard.m_boards[bestMove.z]->setPiece(bestMove.x, bestMove.y, sf::Color::Red);
}
AiMove AI::getBestMove(GameBoard& m_gameboard, GameState copy, int depth, AiMove t_move, int t_alpha, int t_beta)
{
    AiMove bestMove;
    int retv = m_gameboard.victoryCheck(copy);
    if (retv == ai)
    {
        return AiMove(100 - depth);
    }
    else if (retv == player)
    {
        return AiMove(depth + 100);
    }
    else if (retv == 4)
    {
        return AiMove(depth);
    }




   
    if (depth >= maxDepth)
    {
        AiMove newMove;
        newMove.x = t_move.x;
        newMove.y = t_move.y;
        newMove.z = t_move.z;
        newMove.score = evaluation(m_gameboard, newMove, copy);

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
                        move.score = getBestMove(m_gameboard, GameState::AiTurn, depth + 1, move, t_alpha, t_beta).score;
                        if (move.score < t_beta)

                        {
                            t_beta = move.score;
                            bestMove = move;

                        }

                    }
                    if (copy == AiTurn)
                    {

                        m_gameboard.m_boards[z]->setPiece(x, y, sf::Color::Red);
                        move.score = getBestMove(m_gameboard, GameState::playerTurn, depth + 1, move, t_alpha, t_beta).score;
                        if (move.score > t_alpha)

                        {
                            t_alpha = move.score;
                            bestMove = move;
                        }

                    }



                    

                    m_gameboard.m_boards[z]->setPiece(x, y, sf::Color::White);
                    if (t_alpha >= t_beta)
                    {
                        return bestMove;
                    }
                }
            }

        }

    }
    return bestMove;
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
        score +=6;
    }
    for (int x1 = 0,  z1 = 0; x1 < 4; x1++, z1++)//layers + horizontal
    {
       
        if (newMove.x == x1)
        {
            continue;
        }
     
        if (m_gameboard.m_boards[z1]->getPiece(x1, newMove.y).getFillColor() == sf::Color::Yellow)
        {
           
            if (copy == playerTurn)
            {
                score += 2;
            }
            else if (copy == AiTurn)
            {
                score -= 2;
            }
          
        }
        if (m_gameboard.m_boards[z1]->getPiece(x1, newMove.y).getFillColor() == sf::Color::Red)
        {
            if (copy == playerTurn)
            {
                score -= 2;
            }
            else if (copy == AiTurn)
            {
                score += 2;
            }
        
        }
    }
    for (int x2 = 3,z2 = 3; x2 >= 0; x2--,z2--)//layers - horizontal
    {
        if (newMove.x == x2)
        {
            continue;
        }
        if (m_gameboard.m_boards[z2]->getPiece(x2, newMove.y).getFillColor() == sf::Color::Yellow)
        {
            if (copy == playerTurn)
            {
                score += 2;
            }
            else if (copy == AiTurn)
            {
                score -= 2;
            }
           
        }
        if (m_gameboard.m_boards[z2]->getPiece(x2, newMove.y).getFillColor() == sf::Color::Red)
        {
            if (copy == playerTurn)
            {
                score -= 2;
            }
            else if (copy == AiTurn)
            {
                score += 2;
            }
        }
    }
        
        for (int x3 = 0; x3 < 4; x3++)//horizontal
        {
            if (newMove.x == x3)
            {
                continue;
            }
             if (m_gameboard.m_boards[newMove.z]->getPiece(x3, newMove.y).getFillColor() == sf::Color::Yellow)
             {
               

                 if (copy == playerTurn)
                 {
                     score += 2;
                 }
                 else if (copy == AiTurn)
                 {
                     score -= 2;
                 }
             }
             if (m_gameboard.m_boards[newMove.z]->getPiece(x3, newMove.y).getFillColor() == sf::Color::Red)
             {
                 if (copy == playerTurn)
                 {
                     score -= 2;
                 }
                 else if (copy == AiTurn)
                 {
                     score += 2;
                 }
             }
        }


        for (int y4 = 0,z4=0; y4 < 4; y4++,z4++)//layers vertical
        {
            if (newMove.y == y4)
            {
                continue;
            }
            if (m_gameboard.m_boards[z4]->getPiece(newMove.x, y4).getFillColor() == sf::Color::Yellow)
            {
                
                if (copy == playerTurn)
                {
                    score += 2;
                }
                else if (copy == AiTurn)
                {
                    score -= 2;
                }
            }
            if (m_gameboard.m_boards[z4]->getPiece(newMove.x, y4).getFillColor() == sf::Color::Red)
            {
                
                if (copy == playerTurn)
                {
                    score -= 2;
                }
                else if (copy == AiTurn)
                {
                    score += 2;
                }
            }
        }

        for (int y5 = 3, z5 = 3; y5 >= 0; y5--,z5--)//layers vertical
        {
            if (newMove.y == y5)
            {
                continue;
            }
            if (m_gameboard.m_boards[z5]->getPiece(newMove.x, y5).getFillColor() == sf::Color::Yellow)
            {
                
                if (copy == playerTurn)
                {
                    score += 2;
                }
                else if (copy == AiTurn)
                {
                    score -= 2;
                }
            }
            if (m_gameboard.m_boards[z5]->getPiece(newMove.x, y5).getFillColor() == sf::Color::Red)
            {
               
                if (copy == playerTurn)
                {
                    score -= 2;
                }
                else if (copy == AiTurn)
                {
                    score += 2;
                }
            }
        }

        for (int y6 = 0; y6 < 4; y6++)//vertical normal
        {
            if (newMove.y== y6)
            {
                continue;
            }
            if (m_gameboard.m_boards[newMove.z]->getPiece(newMove.x, y6).getFillColor() == sf::Color::Yellow)
            {
                
                if (copy == playerTurn)
                {
                    score += 2;
                }
                else if (copy == AiTurn)
                {
                    score -= 2;
                }
            }
            if (m_gameboard.m_boards[newMove.z]->getPiece(newMove.x, y6).getFillColor() == sf::Color::Red)
            {
                if (copy == playerTurn)
                {
                    score -= 2;
                }
                else if (copy == AiTurn)
                {
                    score += 2;
                }
            }
        }

        for (int z6 = 0; z6 < 4; z6++)//layers
        {
            if (newMove.z == z6)
            {
                continue;
            }
            if (m_gameboard.m_boards[z6]->getPiece(newMove.x, newMove.y).getFillColor() == sf::Color::Yellow)
            {
         
                if (copy == playerTurn)
                {
                    score += 2;
                }
                else if (copy == AiTurn)
                {
                    score -= 2;
                }
            }
            if (m_gameboard.m_boards[z6]->getPiece(newMove.x, newMove.y).getFillColor() == sf::Color::Red)
            {
               
                if (copy == playerTurn)
                {
                    score -= 2;
                }
                else if (copy == AiTurn)
                {
                    score += 2;
                }
            }
        }

         //Layer diagonals 
        for (int x7 = 0, y7 = 0,z7=0; x7 < 4; x7++,y7++,z7++)
        {
            if (newMove.x == x7)
            {
                continue;
            }
            if (m_gameboard.m_boards[z7]->getPiece(x7, y7).getFillColor() == sf::Color::Yellow)
            {
               
                if (copy == playerTurn)
                {
                    score += 2;
                }
                else if (copy == AiTurn)
                {
                    score -= 2;
                }
            }
            if (m_gameboard.m_boards[z7]->getPiece(x7, y7).getFillColor() == sf::Color::Red)
            {
                
                if (copy == playerTurn)
                {
                    score -= 2;
                }
                else if (copy == AiTurn)
                {
                    score += 2;
                }
            }
          
        }
        for (int x8 = 3,y8 = 3, z8=3; x8 >= 0; x8--,y8--,z8--)
        {
            if (newMove.x == x8)
            {
                continue;
            }
            if (m_gameboard.m_boards[z8]->getPiece(x8, y8).getFillColor() == sf::Color::Yellow)
            {
                
                if (copy == playerTurn)
                {
                    score += 2;
                }
                else if (copy == AiTurn)
                {
                    score -= 2;
                }
            }
            if (m_gameboard.m_boards[z8]->getPiece(x8, y8).getFillColor() == sf::Color::Red)
            {
                
                if (copy == playerTurn)
                {
                    score -= 2;
                }
                else if (copy == AiTurn)
                {
                    score += 2;
                }
            }

        }
        //normal diagonals 
        for (int x9 = 3, y9 = 3; x9 >= 0; x9--,y9--)
        {
            if (newMove.x == x9)
            {
                continue;
            }
            if (m_gameboard.m_boards[newMove.z]->getPiece(x9, y9).getFillColor() == sf::Color::Yellow)
            {
                score += 2;
                if (copy == playerTurn)
                {
                
                }
                else if (copy == AiTurn)
                {
                    score -= 2;
                }
            }
            if (m_gameboard.m_boards[newMove.z]->getPiece(x9, y9).getFillColor() == sf::Color::Red)
            {
              
                if (copy == playerTurn)
                {
                    score -= 2;
                }
                else if (copy == AiTurn)
                {
                    score += 2;
                }
            }

        }
        for (int xr = 0, yr = 0; xr < 4; xr++,yr++)
        {
            if (newMove.x == xr)
            {
                continue;
            }
            if (m_gameboard.m_boards[newMove.z]->getPiece(xr, yr).getFillColor() == sf::Color::Yellow)
            {
                
                if (copy == playerTurn)
                {
                    score += 2;
                }
                else if (copy == AiTurn)
                {
                    score -= 2;
                }
            }
            if (m_gameboard.m_boards[newMove.z]->getPiece(xr, yr).getFillColor() == sf::Color::Red)
            {
                
                if (copy == playerTurn)
                {
                    score -= 2;
                }
                else if (copy == AiTurn)
                {
                    score += 2;
                }
            }
          

        }

        if (m_gameboard.m_boards[newMove.z]->getPiece(newMove.x, newMove.y).getFillColor() == sf::Color::White)
        {

            if (copy == playerTurn)
            {
                score -= 0;
            }
            else if (copy == AiTurn)
            {
                score += 0;
            }
        }
       if (maxDepth == 1 && score > 6)
       {
           score = -5;
       }
       
    //evalgroup(m_gameboard, score, copy);
    if (copy == playerTurn)
    {
        score = -score;
    }
    return score;
}


