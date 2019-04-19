#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "EventT.hpp"
#include "IPort.hpp"
namespace Snake
{

class Segments
{
public:
    Segments(IPort& m_displayPort_,IPort& m_scorePort_,IPort& m_foodPort_,Direction direction);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
    void addHeadSegment(Position position);
    void updateSegmentsIfSuccessfullMove(Position position,Position FoodPosition);
    void removeTailSegmentIfNotScored(Position position,Position m_world);
    void removeTailSegment();
private:
    Direction m_headDirection;
    std::list<Position> m_segments;
    IPort& m_displayPort;
    IPort& m_scorePort;
    IPort& m_foodPort;
};

} // namespace Snake
