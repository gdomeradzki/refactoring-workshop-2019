#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "SnakeInterface.hpp"
#include "SnakeSegments.hpp"
#include "IPort.hpp"
#include "EventT.hpp"
#include <functional>
#include <memory>

namespace Snake
{
class Segments;

class World
{
public:
    World(Dimension dimension, Position food);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;

    void updateFoodPosition(Position position, std::function<void()> clearPolicy, IPort& m_displayPort, IPort& foodPort, Segments& m_segments);
    void sendPlaceNewFood(Position position, IPort& m_displayPort);
private:
    Position m_foodPosition;
    Dimension m_dimension;
};

} // namespace Snake
