#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "EventT.hpp"
#include "SnakeInterface.hpp"
#include "SnakeSegments.hpp"
#include "IPort.hpp"

namespace Snake
{

class World
{
public:
   // World(Dimension dimension, Position food);
   World(Dimension dimension, Position food, IPort& displayPort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;
    void sendPlaceNewFood(Position position);
private:
    Position m_foodPosition;
    Dimension m_dimension;
    IPort& m_displayPort;

};

} // namespace Snake
