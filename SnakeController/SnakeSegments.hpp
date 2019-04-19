#pragma once

#include <list>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"

#include <functional>
#include <memory>
#include "EventT.hpp"
#include "IPort.hpp"
#include "SnakeSegments.hpp"

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

    void addHeadSegment(Position position, std::unique_ptr<Segments>& m_segments, IPort& m_displayPort);
private:
    Direction m_headDirection;
    std::list<Position> m_segments;
};

} // namespace Snake
