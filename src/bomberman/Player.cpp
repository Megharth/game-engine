#include "bomberman/Player.hpp"
#include "bomberman/InputComponent.hpp"

Player::Player(Level & level, std::string name, int x, int y, SDL_Renderer* renderer):GameObject(level, x, y, 86, 86, 1) {
    idle_back = ResourceManager::getInstance().load_texture(name + "-back-idle.png", renderer);
    run_back = ResourceManager::getInstance().load_texture(name + "-back-run.png", renderer);
    die_back = ResourceManager::getInstance().load_texture(name + "-back-dead.png", renderer);
    idle_front = ResourceManager::getInstance().load_texture(name + "-front-idle.png", renderer);
    run_front = ResourceManager::getInstance().load_texture(name + "-front-run.png", renderer);
    die_front = ResourceManager::getInstance().load_texture(name + "-front-dead.png", renderer);
    idle_left = ResourceManager::getInstance().load_texture(name + "-left-idle.png", renderer);
    run_left = ResourceManager::getInstance().load_texture(name + "-left-run.png", renderer);
    die_left = ResourceManager::getInstance().load_texture(name + "-left-dead.png", renderer);
    idle_right = ResourceManager::getInstance().load_texture(name + "-right-idle.png", renderer);
    run_right = ResourceManager::getInstance().load_texture(name + "-right-run.png", renderer);
    die_right = ResourceManager::getInstance().load_texture(name + "-right-dead.png", renderer);

    addGenericCompenent(std::make_shared<BombermanInputComponent>(*this, 200.0f));
    setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID));
    setRenderCompenent(std::make_shared<BombermanRenderComponent>(*this, 
        idle_left, idle_right, idle_front, idle_back,
        run_left, run_right, run_front, run_back,
        die_left, die_right, die_front, die_back, 60, 60, 60));
}

Player::~Player() {
    idle_back = NULL;
    run_back = NULL;
    die_back = NULL;
    idle_front = NULL;
    run_front = NULL;
    die_front = NULL;
    idle_left = NULL;
    run_left = NULL;
    die_left = NULL;
    idle_right = NULL;
    run_right = NULL;
    die_right = NULL;
}