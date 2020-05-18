#include "bomberman/Enemy.hpp"
#include "base/PatrolComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"


BombermanEnemy::BombermanEnemy(Level & level, std::string name, int x, int y, SDL_Renderer* renderer):GameObject(level, x, y, 54, 54, 2) {
    left = ResourceManager::getInstance().load_texture(name + "-left-walk.png", renderer);
    right = ResourceManager::getInstance().load_texture(name + "-right-walk.png", renderer);
    front = ResourceManager::getInstance().load_texture(name + "-front-walk.png", renderer);
    back = ResourceManager::getInstance().load_texture(name + "-back-walk.png", renderer);

    std::shared_ptr<PhysicsComponent> pc = std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID);
    pc->addFy(0);
    setPhysicsCompenent(pc);
    addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, 1));
    std::shared_ptr<PatrolComponent> patComp = std::make_shared<PatrolComponent>(*this, 100 , 0 , 50.0f);
    addGenericCompenent(patComp);
    setPatrolComponent(patComp);
    setRenderCompenent(std::make_shared<BombermanRenderComponent>(*this, 
        left, right, front, back,
        left, right, front, back,
        left, right, front, back,
        0, 60, 0));
    
}

BombermanEnemy::~BombermanEnemy() {
    left = NULL;
    right = NULL;
    front = NULL;
    back = NULL;
}