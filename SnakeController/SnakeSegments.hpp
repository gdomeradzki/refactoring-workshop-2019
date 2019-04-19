#pragma once

#include <list>

#include "SnakeController.hpp"
#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"

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
    
    void updateSegmentsIfSuccessfullMove(Position position, Controller& controller);
    void addHeadSegment(Position position, Controller& controller);
    void removeTailSegmentIfNotScored(Position position, Controller& controller);
    void removeTailSegment(Controller& controller);

private:
    Direction m_headDirection;
    std::list<Position> m_segments;

};

} // namespace Snake
