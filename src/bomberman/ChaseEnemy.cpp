#include "bomberman/ChaseEnemy.hpp"
#include "base/PatrolComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"


BombermanChaseEnemy::BombermanChaseEnemy(Level & level, std::string name, int x, int y, SDL_Renderer* renderer,std::weak_ptr<GameObject> player ):GameObject(level, x, y, 54, 54, 2) {
    left = ResourceManager::getInstance().load_texture(name + "-left-walk.png", renderer);
    right = ResourceManager::getInstance().load_texture(name + "-right-walk.png", renderer);
    front = ResourceManager::getInstance().load_texture(name + "-front-walk.png", renderer);
    back = ResourceManager::getInstance().load_texture(name + "-back-walk.png", renderer);


    std::shared_ptr<StateComponent::State> patrolState = std::make_shared<PatrolState>(10.f, x, y, x + 30.f, y);
    std::shared_ptr<StateComponent::State> chaseState = std::make_shared<ChaseState>(6.0f, player);
    std::shared_ptr<StateComponent::State> returnState = std::make_shared<MoveState>(4.0f, x, y);

    std::shared_ptr<StateComponent> sc = std::make_shared<StateComponent>(*this);
    sc->setStartState(patrolState);
    sc->addTransition(patrolState, chaseState, std::make_shared<ObjectProximityTransition>(player, 10.0f));
    sc->addTransition(returnState, chaseState, std::make_shared<ObjectProximityTransition>(player, 5.f));
    sc->addTransition(chaseState, returnState, std::make_shared<TimedTransition>(60));
    sc->addTransition(returnState, patrolState, std::make_shared<PointProximityTransition>(x, y, 0.5f));
    addGenericCompenent(sc);



    std::shared_ptr<PhysicsComponent> pc = std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID);
    pc->addFy(0);
    setPhysicsCompenent(pc);
    addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, 1));
    //std::shared_ptr<PatrolComponent> patComp = std::make_shared<PatrolComponent>(*this, 100 , 0 , 50.0f);
    //addGenericCompenent(patComp);
    //setPatrolComponent(patComp);
    setRenderCompenent(std::make_shared<BombermanRenderComponent>(*this,
        left, right, front, back,
        left, right, front, back,
        left, right, front, back,
        0, 60, 0));

}

BombermanChaseEnemy::~BombermanChaseEnemy() {
    left = NULL;
    right = NULL;
    front = NULL;
    back = NULL;
}
