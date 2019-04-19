#pragma once

#include <list>
#include <memory>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"

class Event;
class IPort;

namespace Snake
{

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

    // void updateSegmentsIfSuccessfullMove(Position position, IPort& m_displayPort, IPort& m_foodPort, IPort& m_scorePort);
    void addHeadSegment(Position position);
    void removeTailSegment(IPort& m_displayPort);


private:
    Direction m_headDirection;
    std::list<Position> m_segments;

    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;
};

} // namespace Snake
