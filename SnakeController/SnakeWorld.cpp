#include "SnakeWorld.hpp"

#include "IPort.hpp"
#include "EventT.hpp"
#include "SnakeInterface.hpp"
#include "SnakeSegments.hpp"


namespace Snake
{

World::World(IPort& displayPort, IPort& foodPort, Dimension dimension, Position food)
    : m_displayPort(displayPort),
      m_foodPort(foodPort),
      m_foodPosition(food),
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
void World::updateFoodPosition(Position position, Segments& segments)
{
    updateFoodPositionWithPolicy(position, segments, std::bind(&World::sendClearOldFood, this));
}


void World::updateFoodPositionWithPolicy(Position position, Segments& segments, std::function<void ()> clearPolicy)
{
    if (segments.isCollision(position) or not contains(position)) {
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

void World::updateFoodPositionForResp(Position position,Segments& segments)
{
    static auto noCleanPolicy = []{};
    updateFoodPositionWithPolicy(position, segments, noCleanPolicy);
}


} // namespace Snake
