#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "SnakeWorld.hpp"
#include "IPort.hpp"
#include "EventT.hpp"

namespace Snake
{

class Segments
{
public:
    Segments(Direction direction, World& world, IPort& foodPort, IPort& scorePort, IPort& m_displayPort);

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
    void removeTailSegment(IPort& displayPort);
private:
    Direction m_headDirection;
    std::list<Position> m_segments;
    World& m_world;
    IPort& m_foodPort;
    IPort& m_scorePort;
    IPort& m_displayPort;

};

} // namespace Snake
