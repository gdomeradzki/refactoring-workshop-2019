#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "SnakeSegments.cpp"
#include "IPort.hpp"
#include <functional>
namespace Snake
{

class World
{
public:
    World(IPort& displayPort, IPort& foodPort, Dimension dimension, Position food);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;
    void updateFoodPosition(Position position, std::function<void()> clearPolicy);
    bool contains(Position position) const;
    void sendClearOldFood();
    void sendPlaceNewFood(Position position);

private:
    Position m_foodPosition;
    Dimension m_dimension;
    IPort& m_displayPort;
    IPort& foodPort;
    
};

} // namespace Snake
