#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"

class Event;
class IPort;

namespace Snake
{

class Segments
{
public:


    Segments(IPort& displayPort, IPort& foodPort, IPort& scorePort,Direction direction);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;

    void removeTailSegment();
    void addHeadSegment(Position position);
//    void removeTailSegmentIfNotScored(Position position);

private:
    Direction m_headDirection;
    std::list<Position> m_segments;

    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;
};

} // namespace Snake
