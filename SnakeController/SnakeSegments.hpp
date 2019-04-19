#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "IEventHandler.hpp"
#include "EventT.hpp"
#include "IPort.hpp"
#include "SnakeWorld.hpp"

class IPort;

namespace Snake
{
class World;

class Segments
{
public:
    Segments(Direction direction, IPort& displayPort, IPort& scorePort);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
    void updateSegmentsIfSuccessfullMove(Position position, World& m_world);
private:

    IPort& m_displayPort;
    IPort& m_scorePort;

    Direction m_headDirection;
    std::list<Position> m_segments;

     void removeTailSegment();
     void addHeadSegment(Position position);
     void removeTailSegmentIfNotScored(Position position, World& m_world);
};

} // namespace Snake
