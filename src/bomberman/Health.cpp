#include "bomberman/Health.hpp"
#include "base/BlockRenderComponent.hpp"
BombermanHealth::BombermanHealth(Level & level, std::string fileName, int x, int y, SDL_Renderer* renderer):GameObject(level, x, y, 64, 36, 6) {
    texture = ResourceManager::getInstance().load_texture(fileName, renderer);
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SOLID));
    setRenderCompenent(std::make_shared<BlockRenderComponent>(*this, texture));
}

BombermanHealth::~BombermanHealth() {
    texture = NULL;
}