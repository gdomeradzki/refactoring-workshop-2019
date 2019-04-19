#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"

#include <functional>

class IPort;
namespace Snake
{
class Segments;
class World
{
public:
    World(Dimension dimension, Position food, IPort& m_foodPort, IPort& m_displayPort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;
    void updateFoodPosition(Position position, const Segments & m_segments );
    void updateFoodPositionWithClearPolicy(Position position, std::function<void()> clearPolicy, const Segments & m_segments);
    bool contains(Position position) const;
    void sendPlaceNewFood(Position position);
    void sendClearOldFood();
private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    Position m_foodPosition;
    Dimension m_dimension;
};

} // namespace Snake
