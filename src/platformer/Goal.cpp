
#include "platformer/Goal.hpp"

Goal::Goal(Level & level, std::string fileName, int x, int y, SDL_Renderer* renderer):GameObject(level, x, y, 128, 128, 3) {
    texture = ResourceManager::getInstance().load_texture(fileName, renderer);
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
	setRenderCompenent(std::make_shared<BlockRenderComponent>(*this, texture));
    addGenericCompenent(std::make_shared<GoalCollide>(*this, 1, renderer));
}

Goal::~Goal() {}
