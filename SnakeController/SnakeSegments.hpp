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
    Position nextHead() const;
    void updateDirection(Direction newDirection);
	void updateSegmentsIfSuccessfullMove(Position position, World& world);

private:
	void addHead(Position position);
	unsigned size() const;
	Position removeTail();

	void addHeadSegment(Position position);
	void removeTailSegmentIfNotScored(Position position, World& world);
	void removeTailSegment();

	IPort& m_displayPort;
	IPort& m_foodPort;
	IPort& m_scorePort;

    Direction m_headDirection;
    std::list<Position> m_segments;
};

} // namespace Snake
