#pragma once

#include <IPort.hpp>
#include "SnakePosition.hpp"
#include "SnakeDimension.hpp"

namespace Snake
{

class World
{
public:
    World(Dimension dimension, Position food, IPort& displayPort, IPort& foodPort, IPort& scorePort);

    void setFoodPosition(Position position);
    Position getFoodPosition() const;

    bool contains(Position position) const;

	void updateFoodPosition(Position position, bool colisionOrOutOfBonds, bool clearNeeded);
	void sendClearOldFood();
	void sendPlaceNewFood(Position position);
private:
	IPort& m_displayPort;
	IPort& m_foodPort;
	IPort& m_scorePort;

    Position m_foodPosition;
    Dimension m_dimension;
};

} // namespace Snake
