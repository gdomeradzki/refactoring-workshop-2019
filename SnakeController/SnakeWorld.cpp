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

void World::sendClearOldFood(IPort& displayPort)
{
    auto foodPosition = getFoodPosition();

    DisplayInd clearOldFood;
    clearOldFood.position = foodPosition;
    clearOldFood.value = Cell_FREE;

    displayPort.send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
}

void World::updateFoodPosition(Position position, Segments& segments, bool clearPolicy, IPort& displayPort, IPort& foodPort)
{
    if (segments.isCollision(position) or not contains(position)) {
        foodPort.send(std::make_unique<EventT<FoodReq>>());
        return;
    }
    if(clearPolicy)
        sendClearOldFood(displayPort);
    sendPlaceNewFood(position, displayPort);
}

bool World::contains(Position position) const
{
    return m_dimension.isInside(position);
}
} // namespace Snake
