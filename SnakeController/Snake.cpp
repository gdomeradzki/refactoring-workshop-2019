//
// Created by a19stude on 4/18/19.
//

#include <sstream>
#include <algorithm>
#include "Snake.hpp"
#include "SnakeInterface.hpp"

namespace Snake {

SnakeObj::SnakeObj(std::istringstream& istr) {
	char d;
	int length;

	istr >> d;
	switch (d) {
		case 'U':
			m_currentDirection = Direction_UP;
			break;
		case 'D':
			m_currentDirection = Direction_DOWN;
			break;
		case 'L':
			m_currentDirection = Direction_LEFT;
			break;
		case 'R':
			m_currentDirection = Direction_RIGHT;
			break;
		default:
			throw ConfigurationError();
	}
	istr >> length;

	while (length--) {
		Segment seg;
		istr >> seg.x >> seg.y;
		m_segments.push_back(seg);
	}
}

bool SnakeObj::isSegmentAtPosition(int x, int y) const
{
	return m_segments.end() !=  std::find_if(m_segments.cbegin(), m_segments.cend(),
	                                         [x, y](auto const& segment){ return segment.x == x and segment.y == y; });
}

	SnakeObj::Segment SnakeObj::calculateNewHead() const
	{
		Segment const& currentHead = m_segments.front();

		Segment newHead;
		newHead.x = currentHead.x + (isHorizontal(m_currentDirection) ? isPositive(m_currentDirection) ? 1 : -1 : 0);
		newHead.y = currentHead.y + (isVertical(m_currentDirection) ? isPositive(m_currentDirection) ? 1 : -1 : 0);

		return newHead;
	}

	void SnakeObj::removeTailSegment()
	{
		auto tail = m_segments.back();

		DisplayInd l_evt;
		l_evt.x = tail.x;
		l_evt.y = tail.y;
		l_evt.value = Cell_FREE;
		m_displayPort.send(std::make_unique<EventT<DisplayInd>>(l_evt));

		m_segments.pop_back();
	}

	void SnakeObj::addHeadSegment(Segment const& newHead)
	{
		m_segments.push_front(newHead);

		DisplayInd placeNewHead;
		placeNewHead.x = newHead.x;
		placeNewHead.y = newHead.y;
		placeNewHead.value = Cell_SNAKE;

		m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewHead));
	}



	void SnakeObj::removeTailSegmentIfNotScored(Segment const& newHead)
	{
		if (std::make_pair(newHead.x, newHead.y) == m_foodPosition) {
			m_scorePort.send(std::make_unique<EventT<ScoreInd>>());
			m_foodPort.send(std::make_unique<EventT<FoodReq>>());
		} else {
			removeTailSegment();
		}
	}

	void SnakeObj::updateSegmentsIfSuccessfullMove(Segment const& newHead)
	{
		if (isSegmentAtPosition(newHead.x, newHead.y) or isPositionOutsideMap(newHead.x, newHead.y)) {
			m_scorePort.send(std::make_unique<EventT<LooseInd>>());
		} else {
			addHeadSegment(newHead);
			removeTailSegmentIfNotScored(newHead);
		}
	}

}
