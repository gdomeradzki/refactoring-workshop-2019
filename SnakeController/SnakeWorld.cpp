#include "SnakeWorld.hpp"
#include "IPort.hpp"
#include "EventT.hpp"
#include "SnakeInterface.hpp"
#include "SnakeSegments.hpp"

namespace Snake
{
/*
World::World(IPort& displayPort, IPort& foodPort, Dimension dimension, Position food)
    : m_displayPort(displayPort),
      m_foodPort(foodPort),
      m_foodPosition(food),
      m_dimension(dimension)
{}
*/
World::World(Dimension dimension, Position food, IPort& displayPort)
    : m_foodPosition(food),
      m_dimension(dimension),
      m_displayPort(displayPort)
{}

void World::setFoodPosition(Position position)
{
    m_foodPosition = position;
}


void World::sendPlaceNewFood(Position position)
{
    m_foodPosition = position;

    DisplayInd placeNewFood;
    placeNewFood.position = position;
    placeNewFood.value = Cell_FOOD;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
}


Position World::getFoodPosition() const
{
    return m_foodPosition;
}

bool World::contains(Position position) const
{
    return m_dimension.isInside(position);
}
} // namespace Snake
