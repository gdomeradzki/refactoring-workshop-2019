#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"

class IPort;

namespace Snake
{

class World;

class Segments
{
public:
    Segments(IPort& displayPort, IPort& scorePort, Direction direction);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;

    void updateSegmentsIfSuccessfullMove(Position position, World& world);
    void addHeadSegment(Position position);
    void removeTailSegmentIfNotScored(Position position, World& world);
    void removeTailSegment();

    void next(World& world);
private:
    IPort& m_displayPort;
    IPort& m_scorePort;
    Direction m_headDirection;
    std::list<Position> m_segments;
};

} // namespace Snake
