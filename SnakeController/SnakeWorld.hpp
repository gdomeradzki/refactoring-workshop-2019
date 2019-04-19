#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "IPort.hpp"

namespace Snake
{

class World
{
public:
    //World(Dimension dimension, Position food, IPort& displayPort);
    World(Dimension dimension, Position food, IPort& displayPort);


    void setFoodPosition(Position position);    
    Position getFoodPosition() const;
    void sendPlaceNewFood(Position position);

    bool contains(Position position) const;
private:
    Position m_foodPosition;
    Dimension m_dimension;
    IPort& m_displayPort;
    //IPort& m_foodPort;
};

} // namespace Snake
