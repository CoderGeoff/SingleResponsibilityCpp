#pragma once
#include <utility>
#include <memory>

class TurnOutcome
{
private:
    int m_NumberOfSquaresMoved;
    int m_SquareAtEndOfTurn;
    std::unique_ptr<std::pair<int, int>> m_Snake;
public:
    explicit TurnOutcome(int numberOfSquaresMoved, int squareAtEndOfTurn);
    TurnOutcome(int numberOfSquaresMoved, std::pair<int, int> snake);
    int NumberOfSquaresMoved() const;
    bool SnakeHit(std::pair<int, int>& snake) const;
    int SquareAtEndOfTurn() const;
};

