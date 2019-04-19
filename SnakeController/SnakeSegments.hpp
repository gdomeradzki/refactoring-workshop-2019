#pragma once

#include <list>
#include <IPort.hpp>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "SnakeWorld.hpp"

namespace Snake
{
class World;
class Segments
{
public:
    Segments(Direction direction,IPort& m_displayPort,IPort& m_scorePort);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
    void updateSegmentsIfSuccessfullMove(Position position, World& world);
    IPort& m_displayPort;
private:
    Direction m_headDirection;
    std::list<Position> m_segments;

    IPort& m_scorePort;
    void removeTailSegment();

    void addHeadSegment(Position position);
    void removeTailSegmentIfNotScored(Position position, World& world);


};

} // namespace Snake
