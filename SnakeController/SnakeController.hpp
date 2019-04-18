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

class Controller : public IEventHandler
{
public:
    Controller(IPort& p_displayPort, IPort& p_foodPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

    struct Segment
    {
        int x;
        int y;
    };
private:
    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    void handleTimeoutInd();
    void handleDirectionInd(std::unique_ptr<Event>);
    void handleFoodInd(std::unique_ptr<Event>);
    void handleFoodResp(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);

    Board board;
};

class Board
{
public:
    Board(int width, int height, int foodX, int foodY, int snakeLen, Direction snakeDir);
    void updateSegmentsIfSuccessfullMove(Segment const& newHead);
    bool isSegmentAtPosition(int x, int y) const;
    bool isPositionOutsideMap(int x, int y) const;
    void updateFoodPosition(int x, int y, std::function<void()> clearPolicy);
    void sendClearOldFood();
    void sendPlaceNewFood(int x, int y);
private:
    bool m_paused;
    Snake m_snake;
    std::pair<int, int> m_snakeHeadPosition;
    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;
};

class Snake
{
public:
    Snake(Direction, int length);
    Controller::Segment calculateNewHead() const;
    void addHeadSegment(Segment const& newHead);
    void removeTailSegmentIfNotScored(Segment const& newHead);
    void removeTailSegment();
private:
    std::list<Segment> m_segments;
    Direction m_currentDirection;
};


} // namespace Snake
