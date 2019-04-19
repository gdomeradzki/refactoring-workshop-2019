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
    World(IPort& displayPort, IPort& foodPort, Dimension dimension, Position food);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;

    void updateFoodPositionWithPolicy(Position position, Segments& segments, std::function<void()> clearPolicy);
    void updateFoodPosition(Position position, Segments& segments);
    void sendClearOldFood();
    void sendPlaceNewFood(Position position);

    void updateFoodPositionForResp(Position position,Segments& segments);
private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    Position m_foodPosition;
    Dimension m_dimension;
};

} // namespace Snake
