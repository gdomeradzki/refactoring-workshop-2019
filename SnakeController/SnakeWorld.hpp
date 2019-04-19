#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include <functional>
#include <memory>
#include "EventT.hpp"
#include "IPort.hpp"
#include "SnakeSegments.hpp"

namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food);
    void sendPlaceNewFood(Position position, IPort& m_displayPort);
    void updateFoodPosition(Position position, std::function<void()> clearPolicy, std::unique_ptr<Segments>& m_segments, IPort& m_foodPort, IPort& m_displayPort);
    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;
private:
    Position m_foodPosition;
    Dimension m_dimension;
   
};

} // namespace Snake
