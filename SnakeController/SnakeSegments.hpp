#pragma once

#include <list>
#include <memory>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "SnakeWorld.hpp"

#include "IPort.hpp"
#include "IEventHandler.hpp"
#include "EventT.hpp"

class Event;
class IPort;

namespace Snake
{

class Segments
{
public:
    Segments(std::unique_ptr<World>& world, IPort& displayPort, IPort& foodPort, IPort& scorePort, Direction direction);

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

    IPort& s_displayPort;
    IPort& s_foodPort;
    IPort& s_scorePort;

    std::unique_ptr<World>& s_world;
};

} // namespace Snake
