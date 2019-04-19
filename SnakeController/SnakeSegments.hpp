#pragma once

#include <list>
#include "IPort.hpp"
#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"

namespace Snake
{

class Segments
{
public:
    Segments(IPort& displayPort, IPort& scorePort, Direction direction);

    void updateSegmentsIfSuccessfullMove(Position position);
    void addHeadSegment(Position position);
    void removeTailSegmentIfNotScored(Position position);
    void removeTailSegment();

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
private:
    IPort& m_displayPort;
    IPort& m_scorePort;
    Direction m_headDirection;
    std::list<Position> m_position;
};

} // namespace Snake
