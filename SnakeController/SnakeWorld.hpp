#pragma once
#include "IPort.hpp"
#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include"EventT.hpp"
namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food, IPort& displayPort, IPort& foodPort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;
    void sendClearOldFood();
    void updateFoodPosition(Position position);

    void sendPlaceNewFood(Position position);
    bool contains(Position position) const;
private:
    Position m_foodPosition;
    Dimension m_dimension;
    IPort& m_displayPort;

    IPort& m_foodPort;
};

} // namespace Snake
