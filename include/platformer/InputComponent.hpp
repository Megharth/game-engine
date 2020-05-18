#ifndef INPUT_COMPONENT
#define INPUT_COMPONENT

#include "base/GenericComponent.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include "base/InputManager.hpp"
#include "base/PhysicsComponent.hpp"
#include <memory>
//! \brief Input component of player character
class InputComponent : public GenericComponent {
public:
    InputComponent(GameObject& , float, float, float);
    void update(Level&);

private:
    float mSpeed, mJump, mGravity;
    bool left, right, jump;
};

#endif
