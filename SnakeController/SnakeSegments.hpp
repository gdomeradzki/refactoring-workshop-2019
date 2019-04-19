#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "SnakeController.hpp"

namespace Snake
{

class Segments
{
public:
    Segments(Direction direction,IPort& displayPort, IPort& foodPort, IPort& scorePort);


    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
    void updateSegmentsIfSuccessfullMove(Position position,bool contains,Position FoodPosition);
    void addHeadSegment(Position position);
    void removeTailSegmentIfNotScored(Position position,Position FoodPosition);
    void removeTailSegment();
private:
    Direction m_headDirection;
    std::list<Position> m_segments;
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;


};

} // namespace Snake
