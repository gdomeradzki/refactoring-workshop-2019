#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "SnakeWorld.hpp"
#include "SnakeController.hpp"
#include "EventT.hpp"
#include "IPort.hpp"

namespace Snake
{

class Segments
{
public:
    Segments(Direction direction, World& world, IPort& scorePort, IPort& displayPort, IPort& foodPort);


    void addHeadSegment(Position position);
    void removeTailSegmentIfNotScored(Position position);
    void removeTailSegment();
    void updateSegmentsIfSuccessfullMove(Position position) ;


    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
private:
    Direction m_headDirection;
    std::list<Position> m_segments;
    World& m_world;
    IPort& m_scorePort;
    IPort& m_displayPort;
    IPort& m_foodPort;

};

} // namespace Snake
