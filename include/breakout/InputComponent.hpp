#ifndef BREAKOUT_INPUT_COMPONENT_HPP
#define BREAKOUT_INPUT_COMPONENT_HPP

#include "base/GenericComponent.hpp"
#include "base/GameObject.hpp"
#include "base/InputManager.hpp"
#include "base/Level.hpp"
#include "base/PhysicsComponent.hpp"

#include "memory"
//! \brief Input component for the paddle movement
class BreakoutInputComponent : public GenericComponent{
private:
    float mSpeed;
    bool left;
    bool right;
    
public:
    BreakoutInputComponent(GameObject &, float);

    void update(Level &);

};

#endif
