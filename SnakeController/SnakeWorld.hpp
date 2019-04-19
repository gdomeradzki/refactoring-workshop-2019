#pragma once

#include "SnakeController.hpp"
#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"

namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;

    void updateFoodPosition(Position position, bool policy, Controller& controller);
    void sendClearOldFood(Controller& controller);
    void sendPlaceNewFood(Position position, Controller& controller);
private:
    Position m_foodPosition;
    Dimension m_dimension;
};

} // namespace Snake
