#pragma once
#include "Object.h"
#include "StateMachine.h"
#include "State.h"

class Door : public df::Object {
public:
    Door();
    int eventHandler(const df::Event* p_e) override;
    int draw() override;

private:
    class StateClosed : public df::State {
    public:
        void Enter(df::Object* owner) override;
        void Execute(df::Object* owner) override; 
        void Exit(df::Object* owner) override; 
    };

    class StateOpen : public df::State {
    public:
        void Enter(df::Object* owner) override;
        void Execute(df::Object* owner) override; 
        void Exit(df::Object* owner) override;
    };

    df::StateMachine fsm_;
    StateClosed st_closed_;
    StateOpen   st_open_;
};
