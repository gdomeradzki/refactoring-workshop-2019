#pragma once

#include <list>
#include <memory>
#include <functional>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"

class Event;
class IPort;

namespace Snake
{
struct ConfigurationError : std::logic_error
{
    ConfigurationError();
};

struct UnexpectedEventException : std::runtime_error
{
    UnexpectedEventException();
};

class World
{
public:
    std::pair<int, int> getMapDimension() const {return m_mapDimension;}
    std::pair<int, int> getFoodPosition() const {return m_foodPosition;}

    void setMapDimension(std::pair<int, int> mapDim) {m_mapDimension = mapDim;}
    void setFoodPosition(std::pair<int, int> foodPos) {m_foodPosition = foodPos;}

private:
    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;
};
struct Segment
{
    int x;
    int y;
};
class Snake
{

private:

    std::list<Segment> m_segments;
    Direction m_currentDirection;
public:
    std::list<Segment> getSegments() const {return m_segments;}
    Direction getCurrentDirection() const {return m_currentDirection;}


    void addSegments(Segment newSegment) {m_segments.push_back(newSegment);}
    void addSegmentsFront(Segment newSegment) {m_segments.push_front(newSegment);}

    void setDirection(Direction newDirection) {m_currentDirection = newDirection;}

};


class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    World m_world;
    Snake m_snake;
   // std::pair<int, int> m_mapDimension;
   // std::pair<int, int> m_foodPosition;



//    std::list<Segment> m_segments;
//    Direction m_currentDirection;

    void handleTimeoutInd();
    void handleDirectionInd(std::unique_ptr<Event>);
    void handleFoodInd(std::unique_ptr<Event>);
    void handleFoodResp(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);

    bool isSegmentAtPosition(int x, int y) const;
    Segment calculateNewHead() const;
    void updateSegmentsIfSuccessfullMove(Segment const& newHead);
    void addHeadSegment(Segment const& newHead);
    void removeTailSegmentIfNotScored(Segment const& newHead);
    void removeTailSegment();

    bool isPositionOutsideMap(int x, int y) const;

    void updateFoodPosition(int x, int y, std::function<void()> clearPolicy);
    void sendClearOldFood();
    void sendPlaceNewFood(int x, int y);

    bool m_paused;
};

} // namespace Snake
