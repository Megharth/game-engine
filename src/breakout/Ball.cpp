#include "breakout/Ball.hpp"
#include "breakout/BallPatrolComponent.hpp"

Ball::Ball(Level & level, std::string fileName, int x, int y, SDL_Renderer* renderer):GameObject(level, x, y, 35, 35, 2) {
    ball = ResourceManager::getInstance().load_texture(fileName, renderer);
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));
    setRenderCompenent(std::make_shared<BlockRenderComponent>(*this, ball));
    addGenericCompenent(std::make_shared<BallPatrolComponent>(*this, 400.0f));
}

Ball::~Ball() {
    ball = NULL;
}