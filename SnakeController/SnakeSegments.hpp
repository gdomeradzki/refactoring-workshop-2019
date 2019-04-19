#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "IPort.hpp"

namespace Snake
{
class World;
class Segments
{
public:
    Segments(Direction direction);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void removeTailSegment(IPort& displayPort);
    void removeTailSegmentIfNotScored(Position position, IPort& displayPort, World& world,
                                        IPort& scorePort, IPort& foodPort);
    void addHead(Position position);
    void addHeadSegment(Position position, IPort& displayPort);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
private:
    Direction m_headDirection;
    std::list<Position> m_segments;
};

} // namespace Snake
