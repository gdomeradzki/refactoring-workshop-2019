#pragma once

#include <IPort.hpp>
#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"

namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food, IPort& m_displayPort, IPort& m_foodPort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;

	void updateFoodPosition(Position position, bool colisionOrOutOfBonds, std::function<void()> clearPolicy);
	void sendClearOldFood();
	void sendPlaceNewFood(Position position);
private:
	IPort& m_displayPort;
	IPort& m_foodPort;

    Position m_foodPosition;
    Dimension m_dimension;
};

} // namespace Snake
