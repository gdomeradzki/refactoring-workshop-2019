#pragma once

#include <list>
#include <memory>

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

private:

    struct Segment
    {
        int x;
        int y;
        int ttl;
    };

    bool checkIfLost(Segment& newHead);
    void displayNewHead(Segment& newHead, DisplayInd& placeNewHead);
    void eraseSegment();
    void moveSnake(Segment& newHead, bool& ifLost);
    void checkIfSnakeAte(FoodInd& receivedFood, bool& requestedFoodCollidedWithSnake);
    void checkIfSnakeAte(FoodResp& receivedFood, bool& requestedFoodCollidedWithSnake);
    void displayFood(bool& requestedFoodCollidedWithSnake, FoodInd& receivedFood);
    void growSnake(FoodResp& requestedFood, bool& ifCollided);

    IPort& m_displayPort;
    IPort& m_foodPort;
    IPort& m_scorePort;

    std::pair<int, int> m_mapDimension;
    std::pair<int, int> m_foodPosition;

    Direction m_currentDirection;
    std::list<Segment> m_segments;
};

} // namespace Snake
