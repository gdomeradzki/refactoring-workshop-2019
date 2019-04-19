#include "SnakeWorld.hpp"

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

bool World::contains(Position position) const
{
    return m_dimension.isInside(position);
}

void World::updateFoodPosition(Position position, std::function<void()> clearPolicy, IPort& m_displayPort, IPort& foodPort, Segments& m_segments)
{
    if (m_segments.isCollision(position) or not contains(position)) {
        foodPort.send(std::make_unique<EventT<FoodReq>>());
        return;
    }

    clearPolicy();
    sendPlaceNewFood(position, m_displayPort);
}

void  World::sendPlaceNewFood(Position position, IPort& m_displayPort)
{
    setFoodPosition(position);

    DisplayInd placeNewFood;
    placeNewFood.position = position;
    placeNewFood.value = Cell_FOOD;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
}

} // namespace Snake
