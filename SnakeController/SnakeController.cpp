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
    : m_paused(false)
{
    std::istringstream istr(initialConfiguration);

    m_world = readWorld(istr, displayPort, foodPort, scorePort);
    m_segments = std::make_unique<Segments>(readDirection(istr), displayPort, foodPort, scorePort);

    int length;
    istr >> length;

    while (length--) {
        Position position;
        istr >> position.x >> position.y;
        m_segments->addSegment(position);
    }

    if (length != -1) {
        throw ConfigurationError();
    }
}

Controller::~Controller()
{}

void Controller::handleTimeoutInd()
{
    auto newHead = m_segments->nextHead();
    m_segments->updateSegmentsIfSuccessfullMove(newHead, checkIfPositionCollideOrOutOfBonds(newHead), m_world->getFoodPosition());
}

void Controller::handleDirectionInd(std::unique_ptr<Event> e)
{
    m_segments->updateDirection(payload<DirectionInd>(*e).direction);
}

void Controller::handleFoodInd(std::unique_ptr<Event> e)
{
    auto position = payload<FoodInd>(*e).position;
    m_world->updateFoodPosition(position, checkIfPositionCollideOrOutOfBonds(position), true);
}

void Controller::handleFoodResp(std::unique_ptr<Event> e)
{
    auto position = payload<FoodResp>(*e).position;

    m_world->updateFoodPosition(position, checkIfPositionCollideOrOutOfBonds(position), false);
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

bool Controller::checkIfPositionCollideOrOutOfBonds(Position position) {
    return m_segments->isCollision(position) or not m_world->contains(position);
}

} // namespace Snake
