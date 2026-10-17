#pragma once

#include <any>
#include <memory>
#include <vector>

#include "defines.hpp"

namespace NEX::Core
{
    struct StateManager;

    struct IState
    {
        IState(StateManager& sm) : state_manager(sm) {}

        StateManager& state_manager;
        virtual ~IState() = default;
        virtual void draw(int, int) = 0;
        virtual void update(double) = 0;
        virtual void event(SDL_Event&) = 0;
    };

    struct StateManager
    {
        void draw(int, int);
        void update(double);
        void send(SDL_Event&);

        std::vector<std::shared_ptr<IState>> states;

        template <typename T> void set_userdata(T&& data)
        { userdata = std::make_shared<std::any>(std::forward<T>(data)); }

        template <typename T> T& get_userdata(void)
        { return std::any_cast<T&>(*userdata); }

      private:
        std::shared_ptr<std::any> userdata;
    };
}; // namespace NEX::Core

#define PUSH_STATE(sm, state, ...) sm.states.push_back(std::make_shared<state>(sm, ##__VA_ARGS__))
#define GET_TOP_STATE_AS(sm, type) std::dynamic_pointer_cast<type>((sm).states.empty() ? nullptr : (sm).states.back())
