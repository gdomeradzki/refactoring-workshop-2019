#include "SnakeWorld.hpp"

namespace Snake
{

World::World(Dimension dimension, Position food, IPort& displayPort, IPort& foodPort, IPort& scorePort)
    : m_foodPosition(food),
      m_dimension(dimension),
      m_displayPort(displayPort),
      m_foodPort(foodPort),
      m_scorePort(scorePort)
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

void World::sendClearOldFood()
{
    auto foodPosition = getFoodPosition();

    DisplayInd clearOldFood;
    clearOldFood.position = foodPosition;
    clearOldFood.value = Cell_FREE;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
}
} // namespace Snake
