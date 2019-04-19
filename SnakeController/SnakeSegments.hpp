#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "IPort.hpp"

namespace Snake
{

class Segments
{
public:
    Segments(Direction direction);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void removeTailSegment(IPort& displayPort);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
private:
    Direction m_headDirection;
    std::list<Position> m_segments;
};

} // namespace Snake
