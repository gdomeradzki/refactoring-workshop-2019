#pragma once
#include "SnakeSegments.hpp"
#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "IPort.hpp"
#include <functional>


namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food, IPort& m_foodPort, IPort& m_displayPort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;
    void updateFoodPosition(Position position, std::function<void()> clearPolicy, Segments & m_segments);
    bool contains(Position position) const;
    void sendPlaceNewFood(Position position);
private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    Position m_foodPosition;
    Dimension m_dimension;
};

} // namespace Snake
