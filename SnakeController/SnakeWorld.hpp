#pragma once

#include <IPort.hpp>
#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"
#include "SnakeSegments.hpp"
#include <functional>

namespace Snake
{
class Segments;
class World
{
public:
    World(Dimension dimension, Position food,IPort& m_foodPort, IPort& m_displayPort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;
    IPort& m_foodPort;
    IPort& m_displayPort;
    bool contains(Position position) const;
    void updateFoodPosition(Position position,Segments& segment);
    void updateFoodPositionForResp(Position position, std::function<void()> ,Segments& segments);
    void sendClearOldFood();

private:
    Position m_foodPosition;
    Dimension m_dimension;

    void sendPlaceNewFood(Position position,Segments& segment);

};

} // namespace Snake
