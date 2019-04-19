#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"

class Event;
class IPort;

namespace Snake
{

class World
{
public:
    World(IPort& displayPort, IPort& foodPort, IPort& scorePort,Dimension dimension, Position food);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;

    void sendPlaceNewFood(Position position);
    void sendClearOldFood();
private:
    Position m_foodPosition;
    Dimension m_dimension;

    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;
};

} // namespace Snake
