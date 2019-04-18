#pragma once

#include <list>
#include <memory>
#include <functional>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"

class Event;
class IPort;
class SnakeHandler;
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

class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:


    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;


    Direction m_currentDirection;

    void handleTimeoutInd();
    void handleDirectionInd(std::unique_ptr<Event>);
    void handleFoodInd(std::unique_ptr<Event>);
    void handleFoodResp(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);



    bool isPositionOutsideMap(int x, int y) const;



    bool m_paused;

};

class Segment{
    int x;
    int y;

};
class SnakeHandler{

        std::list<Segment> m_segments;
        IPort& m_displayPort;
        IPort& m_foodPort;
        IPort& m_scorePort;
    public:
        SnakeHandler(IPort& m_displayPort, IPort& m_foodPort, IPort& m_scorePort, Segment& segment):m_displayPort(m_displayPort), m_foodPort(m_foodPort),m_scorePort(m_scorePort){}
        bool isSegmentAtPosition(int x, int y) const;
        Segment calculateNewHead() const;
        void updateSegmentsIfSuccessfullMove(Segment const& newHead);
        void addHeadSegment(Segment const& newHead);
        void removeTailSegmentIfNotScored(Segment const& newHead);
        void removeTailSegment();
    };

class FoodHandler{
    public:
        FoodHandler(IPort& m_foodPort):m_foodPort(m_foodPort){}
        void updateFoodPosition(int x, int y, std::function<void()> clearPolicy);
        void sendClearOldFood();
        void sendPlaceNewFood(int x, int y);

    private:
        IPort& m_foodPort;

    };
} // namespace Snake
