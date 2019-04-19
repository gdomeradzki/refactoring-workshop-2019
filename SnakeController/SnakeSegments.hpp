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
    Segments(Direction direction);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
    void updateSegmentsIfSuccessfullMove(Position position, World m_world , IPort& m_scorePort,IPort&  m_foodPort, IPort& m_displayPort);
    void addHeadSegment(Position position, IPort& m_displayPort);
    void removeTailSegmentIfNotScored(Position position, World world ,IPort& m_scorePort,IPort&  m_foodPort, IPort& m_displayPort);
    void removeTailSegment(IPort& m_displayPort);
private:
    Direction m_headDirection;
    std::list<Position> m_segments;
};

} // namespace Snake
