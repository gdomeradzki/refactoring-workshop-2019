#pragma once

#include <list>
#include "IPort.hpp"
#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "SnakeWorld.hpp"
namespace Snake
{

class Segments
{
public:
    Segments(IPort& displayPort,IPort& foodPort, IPort& scorePort,  Direction direction);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
    void updateSegmentsIfSuccessfullMove(Position position, World& world);

private:
    IPort& m_displayPort;
    IPort& m_scorePort;
    IPort& m_foodPort;
    Direction m_headDirection;
    std::list<Position> m_segments;

    void addHeadSegment(Position position);

    void removeTailSegmentIfNotScored(Position position, World& world);
    void removeTailSegment();
};

} // namespace Snake
