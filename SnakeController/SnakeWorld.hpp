#pragma once

#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"

#include "IPort.hpp"

namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food, std::unique_ptr<World>& segment, IPort& displayPort, IPort& foodPort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    void updateFoodPosition(Position position, std::function<void()> clearPolicy);
    void sendClearOldFood();
    void sendPlaceNewFood(Position position);

    bool contains(Position position) const;
private:
    Position m_foodPosition;
    Dimension m_dimension;

    std::unique_ptr<Segments>& w_segment;

    IPort& w_displayPort;
    IPort& w_foodPort;
};

} // namespace Snake
