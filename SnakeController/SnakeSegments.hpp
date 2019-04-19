#pragma once

#include <list>
#include <IPort.hpp>

#include "SnakeInterface.hpp"
#include "SnakePosition.hpp"

namespace Snake
{

class World;

class Segments
{
public:
    Segments(Direction direction, IPort& displayPort, IPort& foodPort, IPort& scorePort);

    bool isCollision(Position position) const;
    void addSegment(Position position);
    void addHead(Position position);
    Position nextHead() const;
    Position removeTail();
    void updateDirection(Direction newDirection);
    unsigned size() const;

	void updateSegmentsIfSuccessfullMove(Position position, World& world);
	void addHeadSegment(Position position);
	void removeTailSegmentIfNotScored(Position position, World& world);
	void removeTailSegment();
private:
	IPort& m_displayPort;
	IPort& m_foodPort;
	IPort& m_scorePort;

    Direction m_headDirection;
    std::list<Position> m_segments;
};

} // namespace Snake
