#include "SnakeController.hpp"

#include <algorithm>
#include <sstream>

#include "EventT.hpp"
#include "IPort.hpp"

#include "SnakeSegments.hpp"
#include "SnakeWorld.hpp"

namespace Snake
{

ConfigurationError::ConfigurationError()
    : std::logic_error("Bad configuration of Snake::Controller.")
{}

UnexpectedEventException::UnexpectedEventException()
    : std::runtime_error("Unexpected event received!")
{}

bool checkControl(std::istream& istr, char control)
{
    char input;
    istr >> input;
    return input == control;
}

Dimension readWorldDimension(std::istream& istr)
{
    Dimension dimension;
    istr >> dimension.width >> dimension.height;
    return dimension;
}

Position readFoodPosition(std::istream& istr)
{
    if (not checkControl(istr, 'F')) {
        throw ConfigurationError();
    }

    Position position;
    istr >> position.x >> position.y;
    return position;
}

std::unique_ptr<World> readWorld(std::istream& istr, IPort& displayPort, IPort& foodPort, IPort& scorePort)
{
    if (not checkControl(istr, 'W')) {
        throw ConfigurationError();
    }

    auto worldDimension = readWorldDimension(istr);
    auto foodPosition = readFoodPosition(istr);
    return std::make_unique<World>(worldDimension, foodPosition, displayPort, foodPort, scorePort);
}

Direction readDirection(std::istream& istr)
{
    if (not checkControl(istr, 'S')) {
        throw ConfigurationError();
    }

    char direction;
    istr >> direction;
    switch (direction) {
        case 'U':
            return Direction_UP;
        case 'D':
            return Direction_DOWN;
        case 'L':
            return Direction_LEFT;
        case 'R':
            return Direction_RIGHT;
        default:
            throw ConfigurationError();
    }
}

Controller::Controller(IPort& displayPort, IPort& foodPort, IPort& scorePort, std::string const& initialConfiguration)
    : m_displayPort(displayPort),
      m_foodPort(foodPort),
      m_scorePort(scorePort),
      m_paused(false)
{
    std::istringstream istr(initialConfiguration);

    m_world = readWorld(istr, displayPort, foodPort, scorePort);
    snake_segments = std::make_unique<Segments>(readDirection(istr), displayPort, foodPort, scorePort);

    int length;
    istr >> length;

    while (length--) {
        Position position;
        istr >> position.x >> position.y;
        snake_segments->addSegment(position);
    }

    if (length != -1) {
        throw ConfigurationError();
    }
}

Controller::~Controller()
{}

void Controller::sendPlaceNewFood(Position position)
{
    m_world->setFoodPosition(position);

    DisplayInd placeNewFood;
    placeNewFood.position = position;
    placeNewFood.value = Cell_FOOD;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
}

void Controller::removeTailSegmentIfNotScored(Position position)
{
    if (position == m_world->getFoodPosition()) {
        ScoreInd scoreIndication{snake_segments->size() - 1};
        m_scorePort.send(std::make_unique<EventT<ScoreInd>>(scoreIndication));
        m_foodPort.send(std::make_unique<EventT<FoodReq>>());
    } else {
        snake_segments->removeTailSegment();
    }
}

void Controller::updateSegmentsIfSuccessfullMove(Position position)
{
    if (snake_segments->isCollision(position) or not m_world->contains(position)) {
        m_scorePort.send(std::make_unique<EventT<LooseInd>>());
    } else {
        snake_segments->addHeadSegment(position);
        removeTailSegmentIfNotScored(position);
    }
}

void Controller::handleTimeoutInd()
{
    auto newHead = snake_segments->nextHead();
    updateSegmentsIfSuccessfullMove(newHead);
}

void Controller::handleDirectionInd(std::unique_ptr<Event> e)
{
    snake_segments->updateDirection(payload<DirectionInd>(*e).direction);
}

void Controller::updateFoodPosition(Position position)
{
    if (snake_segments->isCollision(position) or not m_world->contains(position)) {
        m_foodPort.send(std::make_unique<EventT<FoodReq>>());
        return;
    }

    m_world->sendClearOldFood();
    m_world->setFoodPosition(position);
    sendPlaceNewFood(position);
}

void Controller::handleFoodInd(std::unique_ptr<Event> e)
{
    updateFoodPosition(payload<FoodInd>(*e).position);
    m_world->sendClearOldFood();
}

void Controller::handleFoodResp(std::unique_ptr<Event> e)
{

    updateFoodPosition(payload<FoodResp>(*e).position);
}

void Controller::handlePauseInd(std::unique_ptr<Event> e)
{
    m_paused = not m_paused;
}

void Controller::receive(std::unique_ptr<Event> e)
{
    switch (e->getMessageId()) {
        case TimeoutInd::MESSAGE_ID:
            if (!m_paused) {
                return handleTimeoutInd();
            }
            return;
        case DirectionInd::MESSAGE_ID:
            if (!m_paused) {
                return handleDirectionInd(std::move(e));
            }
            return;
        case FoodInd::MESSAGE_ID:
            return handleFoodInd(std::move(e));
        case FoodResp::MESSAGE_ID:
            return handleFoodResp(std::move(e));
        case PauseInd::MESSAGE_ID:
            return handlePauseInd(std::move(e));
        default:
            throw UnexpectedEventException();
    }
}

} // namespace Snake
