#include "SnakeWorld.hpp"

namespace Snake
{

World::World(Dimension dimension, Position food)
    : m_foodPosition(food),
      m_dimension(dimension)
{}

//void World::sendPlaceNewFood(Position position)
//{
//    m_world->setFoodPosition(position);

//    DisplayInd placeNewFood;
//    placeNewFood.position = position;
//    placeNewFood.value = Cell_FOOD;

//    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
//}



//void World::updateFoodPosition(Position position, std::function<void()> clearPolicy)
//{
//    if (m_segments->isCollision(position) or not m_world->contains(position)) {
//        m_foodPort.send(std::make_unique<EventT<FoodReq>>());
//        return;
//    }

//    clearPolicy();
//    sendPlaceNewFood(position);
//}

//void World::sendClearOldFood()
//{
//    auto foodPosition = getFoodPosition();

//    DisplayInd clearOldFood;
//    clearOldFood.position = foodPosition;
//    clearOldFood.value = Cell_FREE;

//    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
//}

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
} // namespace Snake
