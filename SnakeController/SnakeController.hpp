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
struct Segment
{
    int x;
    int y;
};

struct ConfigurationError : std::logic_error
{
    ConfigurationError();
};

struct UnexpectedEventException : std::runtime_error
{
    UnexpectedEventException();
};

class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:
    SnakeBody snake;
    World world;
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;



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



    void handleTimeoutInd();
    void handleDirectionInd(std::unique_ptr<Event>);
    void handleFoodInd(std::unique_ptr<Event>);
    void handleFoodResp(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);




    bool m_paused;
};

class SnakeBody {


    std::list<Segment> m_segments;
    Direction m_currentDirection;


public:
    Direction getCurrentDirection()const{
        return m_currentDirection;
    };

    std::list<Segment> getSegments()const{
        return m_segments;
    }

};

class World{



    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;

public:
    std::pair<int, int> getMapDimension()const{
        return m_mapDimension;
    }
    std::pair<int, int> getFoodPosition()const{
        return m_foodPosition;
    }


};





} // namespace Snake
