#pragma once

#include <list>
#include "EventT.hpp"
#include "IPort.hpp"
#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "SnakeWorld.hpp"
namespace Snake
{


class Segments
{
public:
    Segments(Direction direction, IPort& m_displayPort, IPort& m_scorePort, IPort& m_foodPort);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    // void updateSegmentsIfSuccessfullMove(Position position);
    void updateDirection(Direction newDirection);
    unsigned size() const;

    void addHeadSegment( Position position );
    void removeTailSegment();
    void removeTailSegmentIfNotScored(Position position, const World &);
    void updateSegmentsIfSuccessfullMove( Position position, const World & m_world );
private:
    IPort& m_displayPort;
    IPort& m_scorePort;
    IPort& m_foodPort;
    Direction m_headDirection;
    std::list<Position> m_segments;
};

} // namespace Snake
