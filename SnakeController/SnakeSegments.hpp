#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"
#include "IPort.hpp"
#include "SnakeController.hpp"

namespace Snake
{
class World;
class Segments
{
public:
    Segments(Direction direction, Controller::Ports& ports);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void removeTailSegment();
    void removeTailSegmentIfNotScored(Position position, World& world);
    void addHead(Position position);
    void addHeadSegment(Position position);
    void updateSegmentsIfSuccessfullMove(Position position, World& world);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;
private:
    Direction m_headDirection;
    Controller::Ports& m_ports; 
    
    std::list<Position> m_segments;
};

} // namespace Snake
