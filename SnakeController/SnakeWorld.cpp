#include "SnakeWorld.hpp"
#include "IPort.hpp"
#include "EventT.hpp"
#include "SnakeSegments.hpp"

namespace Snake
{

World::World(Dimension dimension, Position food, IPort& displayPort, IPort& foodPort)
    : m_foodPosition(food),
      m_dimension(dimension),
      m_displayPort(displayPort),
      m_foodPort(foodPort)
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

void World::updateFoodPosition(Position position, Segments& m_segments)
{
    updateFoodPositionAfterClearPolicy(position, std::bind(&World::sendClearOldFood, this), m_segments);
}

void World::updateFoodPositionAfterClearPolicy(Position position, std::function<void()> clearPolicy, Segments& m_segments)
{
    if (m_segments.isCollision(position) or not contains(position)) {
        m_foodPort.send(std::make_unique<EventT<FoodReq>>());
        return;
    }

    clearPolicy();
    sendPlaceNewFood(position);
}

void World::sendClearOldFood()
{
    auto foodPosition = getFoodPosition();

    DisplayInd clearOldFood;
    clearOldFood.position = foodPosition;
    clearOldFood.value = Cell_FREE;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
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
