#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "EventT.hpp"
#include "SnakeInterface.hpp"
#include "SnakeSegments.hpp"
#include "IPort.hpp"
#include <functional>

namespace Snake
{

class World
{
public:
   // World(Dimension dimension, Position food);
   World(Dimension dimension, Position food, IPort& displayPort, IPort& foodPort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;


    bool contains(Position position) const;

    void sendPlaceNewFood(Position position);
    void sendClearOldFood();
    void updateFoodPosition(Position position,Segments & m_segments);
    void updateFoodPosition(Position position,Segments & m_segments, std::function<void()> clearPolicy);

    Position m_foodPosition;
    Dimension m_dimension;
    IPort& m_displayPort;
    IPort& m_foodPort;


};

} // namespace Snake
