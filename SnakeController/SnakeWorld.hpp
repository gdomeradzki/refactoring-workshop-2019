#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "SnakeInterface.hpp"
#include "SnakeSegments.hpp"

#include "IEventHandler.hpp"
#include "IPort.hpp"
#include "Event.hpp"
#include "EventT.hpp"



namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;

    void sendPlaceNewFood(Position position, IPort& m_displayPort);
    // void sendClearOldFood(IPort& m_displayPort); //not working yet


private:

    

    Position m_foodPosition;
    Dimension m_dimension;
};

} // namespace Snake
