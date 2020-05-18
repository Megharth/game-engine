
#include "platformer/Character.hpp"
#include "platformer/InputComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"


Character::Character(Level & level, std::string charName, int x, int y, SDL_Renderer* renderer):GameObject(level, x, y, 100, 72, 1) {
    character_idle_right = ResourceManager::getInstance().load_texture(charName + "-idle-right.png", renderer);
    character_idle_left = ResourceManager::getInstance().load_texture(charName + "-idle-left.png", renderer);
    character_run_right = ResourceManager::getInstance().load_texture(charName + "-run-right.png", renderer);
    character_run_left = ResourceManager::getInstance().load_texture(charName + "-run-left.png", renderer);
    character_jump_right = ResourceManager::getInstance().load_texture(charName + "-jump-right.png", renderer);
    character_jump_left = ResourceManager::getInstance().load_texture(charName + "-jump-left.png", renderer);
    addGenericCompenent(std::make_shared<InputComponent>(*this, 500.0f, 1000.0f, 100000.0f));
    addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, 6));
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));
    setRenderCompenent(std::make_shared<PlayerRenderComponent>(*this, 
        character_idle_right, 
        character_idle_left,
        character_run_right,
        character_run_left,
        character_jump_right,
        character_jump_left, 54, 36, 36));
}

Character::~Character() {
    // destroy all the textures
    character_idle_right = NULL;
    character_idle_left = NULL;
    character_run_right = NULL;
    character_run_left = NULL;
    character_jump_right = NULL;
    character_jump_left = NULL;
}
