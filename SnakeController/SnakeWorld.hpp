#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "IPort.hpp"
#include "SnakeSegments.hpp"
#include <functional>

namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food, IPort& displayPort, IPort& foodPort);


    void setFoodPosition(Position position);    
    Position getFoodPosition() const;

    void sendPlaceNewFood(Position position);
    void sendClearOldFood();
    void updateFoodPosition(Position position, Segments& segments);
    void updateFoodPosition(Position position, Segments& segments, std::function<void()> noClearPolicy);

    bool contains(Position position) const;
private:
    Position m_foodPosition;
    Dimension m_dimension;
    IPort& m_displayPort;
    IPort& m_foodPort;
};

}
