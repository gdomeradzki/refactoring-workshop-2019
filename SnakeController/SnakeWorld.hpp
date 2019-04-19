#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "IPort.hpp"
#include "SnakeSegments.hpp"

namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;
    void sendPlaceNewFood(Position position, IPort& display);
    void sendClearOldFood(IPort& displayPort);
    void updateFoodPosition(Position position, Segments& segments, bool clearPolicy, IPort& displayPort, IPort& foodPort);

    bool contains(Position position) const;
private:
    Position m_foodPosition;
    Dimension m_dimension;
};

} // namespace Snake
