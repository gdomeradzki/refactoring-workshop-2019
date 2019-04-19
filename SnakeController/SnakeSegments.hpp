#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "IPort.hpp"
namespace Snake
{

class Segments
{
public:
    Segments(IPort& displayPort, IPort& scorePort,Direction direction);

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
    Direction m_headDirection;
    std::list<Position> m_segments;
    IPort& displayPort;
    IPort& scorePort;
    
};

} // namespace Snake
