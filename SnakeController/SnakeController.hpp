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
    class Segments;
    class World;

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
        Controller(IPort& displayPort, IPort& foodPort, IPort& scorePort, std::string const& config);
        ~Controller() override;

        Controller(Controller const& p_rhs) = delete;
        Controller& operator=(Controller const& p_rhs) = delete;

        void receive(std::unique_ptr<Event> e) override;

        auto& get_m_world();
        auto& get_m_segments();
        auto& get_m_scorePort();
        auto& get_m_displayPort();
        auto& get_m_foodPort();

    private:
        IPort& m_displayPort;
        IPort& m_foodPort;
        IPort& m_scorePort;

        std::unique_ptr<World> m_world;
        std::unique_ptr<Segments> m_segments;

        void handleTimeoutInd();
        void handleDirectionInd(std::unique_ptr<Event>);
        void handleFoodInd(std::unique_ptr<Event>);
        void handleFoodResp(std::unique_ptr<Event>);
        void handlePauseInd(std::unique_ptr<Event>);

        // void updateSegmentsIfSuccessfullMove(Position position); // Segments
        // void addHeadSegment(Position position); // Segments
        // void removeTailSegmentIfNotScored(Position position); // Segments
        // void removeTailSegment(); // Segments

        //void updateFoodPosition(Position position, std::function<void()> clearPolicy); // World
        // void sendClearOldFood(); // World
        // void sendPlaceNewFood(Position position); // World

        bool m_paused;
    };

} // namespace Snake
