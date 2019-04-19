#pragma once

#include <functional>

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"

class Event;
class IPort;

namespace Snake
{

class Segments;
class World
{
public:
    World(Dimension dimension, Position food, IPort& displayPort, IPort& foodPort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;

    // void updateFoodPosition(Position position, std::function<void()> clearPolicy, Segments& m_segments);
    void updateFoodPosition(Position position, Segments& m_segments);
    void updateFoodPositionAfterClearPolicy(Position position, std::function<void()> clearPolicy, Segments& m_segments);
    void sendClearOldFood();
    void sendPlaceNewFood(Position position);


private:
    Position m_foodPosition;
    Dimension m_dimension;

    IPort& m_displayPort;
    IPort& m_foodPort;
};

} // namespace Snake
