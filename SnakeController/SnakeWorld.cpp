#include "SnakeWorld.hpp"

namespace Snake
{

World::World(Dimension dimension, Position food, std::unique_ptr<World>& segment, IPort& displayPort, IPort& foodPort)
    : m_foodPosition(food),
      m_dimension(dimension),
      w_segments(segment),
      w_displayPort(displayPort),
      w_foodPort(foodPort)
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

    w_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
}

void World::sendClearOldFood()
{
    auto foodPosition = getFoodPosition();

    DisplayInd clearOldFood;
    clearOldFood.position = foodPosition;
    clearOldFood.value = Cell_FREE;

    w_displayPort.send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
}

void World::updateFoodPosition(Position position, std::function<void()> clearPolicy)
{
    if (w_segments->isCollision(position) or not contains(position)) {
        w_foodPort.send(std::make_unique<EventT<FoodReq>>());
        return;
    }

    clearPolicy();
    sendPlaceNewFood(position);
}

} // namespace Snake
