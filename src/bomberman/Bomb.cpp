#include "bomberman/Bomb.hpp"

Bomb::Bomb(Level & level, std::string fileName, int x, int y, SDL_Renderer* renderer):GameObject(level, x, y, 54, 54, 4) {
    bomb = ResourceManager::getInstance().load_texture(fileName, renderer);
    explosion = ResourceManager::getInstance().load_texture("bomberman/explosion.png", renderer);
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
    setRenderCompenent(std::make_shared<BombRenderComponent>(*this, bomb, explosion, 3000.0));
    addGenericCompenent(std::make_shared<ExplosionComponent>(*this, 3000.0, false));
}

Bomb::~Bomb() {
    bomb = NULL;
    explosion = NULL;
}
