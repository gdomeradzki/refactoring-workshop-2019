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

void World::updateFoodPosition(Position position, bool isColl, bool x)
{
    if (isColl or not contains(position)) {
        m_foodPort.send(std::make_unique<EventT<FoodReq>>());
        return;
    }

    if (x) sendClearOldFood();
    sendPlaceNewFood(position);
}

} // namespace Snake
