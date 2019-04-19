#pragma once

#include <list>
#include <memory>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "SnakeWorld.hpp"
#include "IPort.hpp"
#include "EventT.hpp"

class Event;
class IPort;

namespace Snake
{
class World;


class Segments
{
public:
    Segments(Direction direction, IPort& displayPort, IPort& foodPort, IPort& scorePort, World& world);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;

    void updateSegmentsIfSuccessfullMove(Position position);
    void addHeadSegment(Position position);
    void removeTailSegmentIfNotScored(Position position);
    void removeTailSegment();

private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    Direction m_headDirection;
    std::list<Position> m_segments;

    World& m_world;
};

} // namespace Snake
