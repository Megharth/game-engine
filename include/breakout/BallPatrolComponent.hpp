#ifndef BALL_PATROL_COMPONENT
#define BALL_PATROL_COMPONENT

#include "base/GenericComponent.hpp"
#include "base/GameObject.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/Level.hpp"
//! The movement of the ball is defined in this class
class BallPatrolComponent : public GenericComponent{
private:
    bool up{false}, 
        left{false},
        collision{false};
    int mSpeed;
    std::shared_ptr<PhysicsComponent> pc;

public: 
    BallPatrolComponent(GameObject &, float);
    /**
     * It contains the change of position code for the ball after every frame
     */
    virtual void update(Level & level);
    /**
     * Returns true if the direction movement of the ball is up
     * else it returns false
     */
    inline bool isUp() { return up; }
    /**
     * Returns true if the direction movement of the ball is left
     * else it returns false
     */
    inline bool isLeft() { return left; }
};

#endif
