#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "SnakeWorld.hpp"
#include "EventT.hpp"
#include "IPort.hpp"

namespace Snake
{

class Segments
{
public:
    Segments(Direction direction,IPort& _m_displayPort,
    IPort& _m_foodPort,
    IPort& _m_scorePort,
    World& _m_world
    );

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
    void removeTailSegment();
        void removeTailSegmentIfNotScored(Position position);
          void updateSegmentsIfSuccessfullMove(Position position);
            void addHeadSegment(Position position);
           
private:
    Direction m_headDirection;
    std::list<Position> m_segments;

    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;
    World& m_world;
};

} // namespace Snake
