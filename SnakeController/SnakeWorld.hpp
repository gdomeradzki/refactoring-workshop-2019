#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "IEventHandler.hpp"
#include "IPort.hpp"
#include "EventT.hpp"
#include "SnakeInterface.hpp"

class Event;
class IPort;

namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food, IPort& displayPort, IPort& foodPort, IPort& scorePort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;

    void sendClearOldFood();
private:
    Position m_foodPosition;
    Dimension m_dimension;
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

};

} // namespace Snake
