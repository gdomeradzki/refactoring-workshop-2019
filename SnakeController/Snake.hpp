//
// Created by a19stude on 4/18/19.
//

#ifndef REFACTORINGWORKSHOP_SNAKE_HPP
#define REFACTORINGWORKSHOP_SNAKE_HPP

namespace Snake {

class SnakeObj {
public:
	SnakeObj(std::istringstream& istr);

private:
	struct Segment
	{
		int x;
		int y;
	};

	std::list<Segment> m_segments;
	Direction m_currentDirection;

	bool isSegmentAtPosition(int x, int y) const;
	Segment calculateNewHead() const;
	void updateSegmentsIfSuccessfullMove(Segment const& newHead);
	void addHeadSegment(Segment const& newHead);
	void removeTailSegmentIfNotScored(Segment const& newHead);
	void removeTailSegment();
};

}
#endif //REFACTORINGWORKSHOP_SNAKE_HPP
