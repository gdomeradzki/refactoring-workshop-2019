#include "SnakeWorld.hpp"
#include "EventT.hpp"
#include "IPort.hpp"
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
// void World::sendClearOldFood()
// {
//     auto foodPosition =getFoodPosition();

//     DisplayInd clearOldFood;
//     clearOldFood.position = foodPosition;
//     clearOldFood.value = Cell_FREE;

//     m_displayPort.send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
// }
} // namespace Snake
