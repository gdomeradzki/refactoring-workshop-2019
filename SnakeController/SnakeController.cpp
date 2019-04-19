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

    std::unique_ptr<World> readWorld(std::istream& istr)
    {
        if (not checkControl(istr, 'W')) {
            throw ConfigurationError();
        }

        auto worldDimension = readWorldDimension(istr);
        auto foodPosition = readFoodPosition(istr);
        return std::make_unique<World>(worldDimension, foodPosition);
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

/* ############# CONTROLLER ###########*/

    Controller::Controller(IPort& displayPort, IPort& foodPort, IPort& scorePort, std::string const& initialConfiguration)
        : m_displayPort(displayPort),
        m_foodPort(foodPort),
        m_scorePort(scorePort),
        m_paused(false)
    {
        std::istringstream istr(initialConfiguration);

        m_world = readWorld(istr);
        m_segments = std::make_unique<Segments>(readDirection(istr));

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

    // void Controller::sendPlaceNewFood(Position position)
    // {
    //     m_world->setFoodPosition(position);

    //     DisplayInd placeNewFood;
    //     placeNewFood.position = position;
    //     placeNewFood.value = Cell_FOOD;

    //     m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
    // }

    // void Controller::sendClearOldFood()
    // {
    //     auto foodPosition = m_world->getFoodPosition();

    //     DisplayInd clearOldFood;
    //     clearOldFood.position = foodPosition;
    //     clearOldFood.value = Cell_FREE;

    //     m_displayPort.send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
    // }

    // void Controller::removeTailSegment()
    // {
    //     auto tailPosition = m_segments->removeTail();

    //     DisplayInd clearTail;
    //     clearTail.position = tailPosition;
    //     clearTail.value = Cell_FREE;

    //     m_displayPort.send(std::make_unique<EventT<DisplayInd>>(clearTail));
    // }

    // void Controller::addHeadSegment(Position position)
    // {

    //     m_segments->addHead(position);

    //     DisplayInd placeNewHead;
    //     placeNewHead.position = position;
    //     placeNewHead.value = Cell_SNAKE;

    //     m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewHead));
    // }

    // void Controller::removeTailSegmentIfNotScored(Position position)
    // {
    //     if (position == m_world->getFoodPosition()) {
    //         ScoreInd scoreIndication{m_segments->size() - 1};
    //         m_scorePort.send(std::make_unique<EventT<ScoreInd>>(scoreIndication));
    //         m_foodPort.send(std::make_unique<EventT<FoodReq>>());
    //     } else {
    //         removeTailSegment();
    //     }
    // }

    // void Controller::updateSegmentsIfSuccessfullMove(Position position)
    // {
    //     if (m_segments->isCollision(position) or not m_world->contains(position)) {
    //         m_scorePort.send(std::make_unique<EventT<LooseInd>>());
    //     } else {
    //         addHeadSegment(position);
    //         removeTailSegmentIfNotScored(position);
    //     }
    // }

    void Controller::handleTimeoutInd()
    {
        auto newHead = m_segments->nextHead(); 
        m_segments->updateSegmentsIfSuccessfullMove(newHead, *this);
    }

    void Controller::handleDirectionInd(std::unique_ptr<Event> e)
    {
        m_segments->updateDirection(payload<DirectionInd>(*e).direction);
    }

    // void Controller::updateFoodPosition(Position position, std::function<void()> clearPolicy)
    // {
    //     if (m_segments->isCollision(position) or not m_world->contains(position)) {
    //         m_foodPort.send(std::make_unique<EventT<FoodReq>>());
    //         return;
    //     }

    //     clearPolicy();
    //     sendPlaceNewFood(position);
    // }

    void Controller::handleFoodInd(std::unique_ptr<Event> e)
    {

        m_world->updateFoodPosition(payload<FoodInd>(*e).position, true, *this);
        // std::bind(&World::sendClearOldFood, this)
    }

    void Controller::handleFoodResp(std::unique_ptr<Event> e)
    {
        // static auto noCleanPolicy = []{};
        m_world->updateFoodPosition(payload<FoodResp>(*e).position, false, *this);
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

auto& Controller::get_m_world()
{
    return m_world;
}

auto& Controller::get_m_segments()
{
    return m_segments;
}

auto& Controller::get_m_scorePort()
{
    return m_scorePort;
}

auto& Controller::get_m_displayPort()
{
    return m_displayPort;
}

auto& Controller::get_m_foodPort()
{
    return m_displayPort;
}

/* ############# END CONTROLLER ###########*/

/* ############# SEGMENTS ###########*/

void Segments::updateSegmentsIfSuccessfullMove(Position position, Controller& controller )
    {
        if ( controller.get_m_segments()->isCollision(position) or not controller.get_m_world()->contains(position)) 
        {
            controller.get_m_scorePort().send(std::make_unique<EventT<LooseInd>>());
        } else {
            addHeadSegment(position, controller);
            removeTailSegmentIfNotScored(position, controller);
        }
    }


void Segments::addHeadSegment(Position position, Controller& controller)
    {

        controller.get_m_segments()->addHead(position);

        DisplayInd placeNewHead;
        placeNewHead.position = position;
        placeNewHead.value = Cell_SNAKE;

        controller.get_m_displayPort().send(std::make_unique<EventT<DisplayInd>>(placeNewHead));
    }

void Segments::removeTailSegmentIfNotScored(Position position, Controller& controller)
    {
        if (position == controller.get_m_world()->getFoodPosition()) {
            ScoreInd scoreIndication{controller.get_m_segments()->size() - 1};
            controller.get_m_scorePort().send(std::make_unique<EventT<ScoreInd>>(scoreIndication));
            controller.get_m_foodPort().send(std::make_unique<EventT<FoodReq>>());
        } else {
            removeTailSegment(controller);
        }
    }

void Segments::removeTailSegment(Controller& controller)
    {
        auto tailPosition = controller.get_m_segments()->removeTail();

        DisplayInd clearTail;
        clearTail.position = tailPosition;
        clearTail.value = Cell_FREE;

        controller.get_m_displayPort().send(std::make_unique<EventT<DisplayInd>>(clearTail));
    }
/* ############# END SEGMENTS ###########*/

/* ############# WORLD ###########*/

void World::updateFoodPosition(Position position, bool policy, Controller& controller)
    {
        if (controller.get_m_segments()->isCollision(position) or not controller.get_m_world()->contains(position)) {
            controller.get_m_foodPort().send(std::make_unique<EventT<FoodReq>>());
            return;
        }

        if(policy)
            sendClearOldFood(controller);

        sendPlaceNewFood(position, controller);
    }

void World::sendClearOldFood(Controller& controller)
    {
        auto foodPosition = controller.get_m_world()->getFoodPosition();

        DisplayInd clearOldFood;
        clearOldFood.position = foodPosition;
        clearOldFood.value = Cell_FREE;

        controller.get_m_displayPort().send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
    }

void World::sendPlaceNewFood(Position position, Controller& controller)
    {
        controller.get_m_world()->setFoodPosition(position);

        DisplayInd placeNewFood;
        placeNewFood.position = position;
        placeNewFood.value = Cell_FOOD;

        controller.get_m_displayPort().send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
    }
/* ############# END WORLD ###########*/

} // namespace Snake
