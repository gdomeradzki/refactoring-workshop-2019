#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "SnakeWorld.hpp"

#include "IEventHandler.hpp"
#include "IPort.hpp"
#include "Event.hpp"
#include "EventT.hpp"

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

    void addHeadSegment(Position position, IPort& m_displayPort);

    void removeTailSegment(IPort& m_displayPort);

    //void removeTailSegmentIfNotScored(Position position,IPort& m_displayPort, IPort& m_foodPort, IPort& m_scorePort, std::unique_ptr<World> &m_world);

    //void updateSegmentsIfSuccessfullMove(Position position, std::unique_ptr<World> &m_world, IPort& m_scorePort, IPort& m_foodPort, IPort& m_displayPort);

private:
    Direction m_headDirection;
    std::list<Position> m_segments;
};

} // namespace Snake
