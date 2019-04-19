#include "SnakeWorld.hpp"
#include "IPort.hpp"
#include "EventT.hpp"
#include "SnakeInterface.hpp"

namespace Snake
{

World::World(Dimension dimension, Position food)
    : m_foodPosition(food),
      m_dimension(dimension)
{}

void World::setFoodPosition(Position position)
{
    m_foodPosition = position;
}

Position World::getFoodPosition() const
{
    return m_foodPosition;
}

void World::sendPlaceNewFood(Position position, IPort& displayPort)
{
    setFoodPosition(position);

    DisplayInd placeNewFood;
    placeNewFood.position = position;
    placeNewFood.value = Cell_FOOD;

    displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
}

bool World::contains(Position position) const
{
    return m_dimension.isInside(position);
}
} // namespace Snake
