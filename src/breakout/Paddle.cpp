#include "breakout/Paddle.hpp"
#include "breakout/InputComponent.hpp"

Paddle::Paddle(Level & level, std::string fileName, int x, int y, SDL_Renderer* renderer):GameObject(level, x, y, 225, 35, 1) {
    paddle = ResourceManager::getInstance().load_texture(fileName, renderer);
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));
	setRenderCompenent(std::make_shared<BlockRenderComponent>(*this, paddle));
    addGenericCompenent(std::make_shared<BreakoutInputComponent>(*this, 1000.0f));
}

Paddle::~Paddle() {
    paddle = NULL;
}