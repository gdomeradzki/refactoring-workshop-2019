#pragma once

#include <list>
#include <memory>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"

class Event;
class IPort;

namespace Snake
{
class World;
class Segments
{
public:
    Segments(Direction direction, IPort& displayPort, IPort& foodPort, IPort& scorePort);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;

    void updateSegmentsIfSuccessfullMove(Position position, World& m_world);
    void addHeadSegment(Position position);
    void removeTailSegmentIfNotScored(Position position, World& m_world);
    void removeTailSegment();

private:
    Direction m_headDirection;
    std::list<Position> m_segments;

    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;
};

} // namespace Snake
