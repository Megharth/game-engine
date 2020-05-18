#ifndef BOMBERMAN_INPUT_COMPONENT
#define BOMBERMAN_INPUT_COMPONENT

#include "base/GenericComponent.hpp"
#include "base/GameObject.hpp"
#include "base/InputManager.hpp"
#include "base/Level.hpp"
#include "base/PhysicsComponent.hpp"

#include "memory"

class BombermanInputComponent : public GenericComponent {
public:
    BombermanInputComponent(GameObject &, float);

    void update(Level &);

private:
    float mSpeed;
    bool left, right, up, down;
};

#endif