#include "SnakeWorld.hpp"

namespace Snake
{

World::World(Dimension dimension, Position food, IPort& displayPort)
    : m_foodPosition(food),
      m_dimension(dimension),m_displayPort(displayPort)
{}


void World::setFoodPosition(Position position)
{
    m_foodPosition = position;
}

Position World::getFoodPosition() const
{
    return m_foodPosition;
}

bool World::contains(Position position) const
{
    return m_dimension.isInside(position);
}

void World::sendPlaceNewFood(Position position)
{
    setFoodPosition(position);

    DisplayInd placeNewFood;
    placeNewFood.position = position;
    placeNewFood.value = Cell_FOOD;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
}


} // namespace Snake
