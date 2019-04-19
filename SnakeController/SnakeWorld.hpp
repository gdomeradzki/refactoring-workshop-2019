#pragma once

#include <IPort.hpp>
#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"

namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food,IPort& displayPort,IPort& foodPort);


    void setFoodPosition(Position position);
    Position getFoodPosition() const;
    void updateFoodPosition(Position position, std::function<void()> clearPolicy,bool isCollision);
    bool contains(Position position) const;
    void sendClearOldFood();
    void sendPlaceNewFood(Position position);
private:
    Position m_foodPosition;
    Dimension m_dimension;
    IPort& m_displayPort;
    IPort& m_foodPort;

};

} // namespace Snake
