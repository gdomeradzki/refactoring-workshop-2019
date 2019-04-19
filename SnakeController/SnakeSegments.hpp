#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "IEventHandler.hpp"
#include <memory>
#include "IPort.hpp"
#include "EventT.hpp"
namespace Snake
{

class Segments
{
public:
    Segments(Direction direction, IPort& displayPort, IPort& foodPort, IPort& scorePort);
    void addHeadSegment(Position position);
    void removeTailSegmentIfNotScored(Position position, Position foodPosition);
    void removeTailSegment();
    void updateSegmentsIfSuccessfullMove(Position position, bool notContains, Position foodPosition);
    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
private:
    Direction m_headDirection;
    std::list<Position> m_segments;
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;
};

} // namespace Snake
