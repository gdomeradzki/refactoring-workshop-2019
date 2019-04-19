#include "SnakeWorld.hpp"
#include "SnakeSegments.hpp"
#include "IPort.hpp"
namespace Snake
{

World::World(Dimension dimension, Position food, IPort& m_foodPort, IPort& m_displayPort)
    : m_foodPosition(food),
      m_dimension(dimension),
      m_foodPort(m_foodPort),
      m_displayPort(m_displayPort)
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


void World::updateFoodPosition(Position position, const Segments & m_segments )
{
    updateFoodPositionWithClearPolicy( position, std::bind(&World::sendClearOldFood, this), m_segments );
}

void World::updateFoodPositionWithClearPolicy(Position position, std::function<void()> clearPolicy, const Segments & m_segments)
{
    if (m_segments.isCollision(position) or not contains(position)) {
        m_foodPort.send(std::make_unique<EventT<FoodReq>>());
        return;
    }
    clearPolicy();
    sendPlaceNewFood(position);
}

void World::sendPlaceNewFood(Position position)
{
    setFoodPosition(position);

    DisplayInd placeNewFood;
    placeNewFood.position = position;
    placeNewFood.value = Cell_FOOD;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
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


