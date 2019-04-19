#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "EventT.hpp"
#include "IPort.hpp"
namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;
   void sendClearOldFood();
       void updateFoodPosition(std::weak_ptr<Segments>przekazane, Position position, std::function<void()> clearPolicy);
private:
    Position m_foodPosition;
    Dimension m_dimension;
};

} // namespace Snake
