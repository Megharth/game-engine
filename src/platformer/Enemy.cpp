/*SDL_Ren
 * Enemy.cpp
 *
 *  Created on: Mar 22, 2020
 *      Author: trive
 */

#include "platformer/Enemy.hpp"
#include "base/PatrolComponent.hpp"
#include "base/RemoveOnCollideComponent.hpp"

Enemy::Enemy(Level & level, std::string name, int x, int y, SDL_Renderer* renderer):GameObject(level, x, y, 72, 72, 2){

	 enemy_idle_right = ResourceManager::getInstance().load_texture(name + "-idle-right.png", renderer);
	 enemy_idle_left = ResourceManager::getInstance().load_texture(name + "-idle-left.png", renderer);
	 enemy_run_right = ResourceManager::getInstance().load_texture(name + "-run-right.png", renderer);
	 enemy_run_left = ResourceManager::getInstance().load_texture(name + "-run-left.png", renderer);
	 enemy_jump_right = ResourceManager::getInstance().load_texture(name + "-jump-right.png", renderer);
	 enemy_jump_left = ResourceManager::getInstance().load_texture(name + "-jump-left.png", renderer);
	 std::shared_ptr<PhysicsComponent> pc = std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::DYNAMIC_SOLID);
	 pc->addFy(100000.0f);
	 setPhysicsCompenent(pc);
	 addGenericCompenent(std::make_shared<RemoveOnCollideComponent>(*this, TAG_PLAYER));
	 std::shared_ptr<PatrolComponent> patComp = std::make_shared<PatrolComponent>(*this, 100 , 0 , 50.0f);
	 addGenericCompenent(patComp);
	 setPatrolComponent(patComp);
	 setRenderCompenent(std::make_shared<EnemyRenderComponent>(*this,
	       enemy_idle_right,
		   enemy_idle_left,
	       enemy_run_right,
	       enemy_run_left,
	       enemy_jump_right,
	       enemy_jump_left, 54, 36, 36));



}

Enemy::~Enemy() {

    enemy_idle_right = NULL;
    enemy_idle_left = NULL;
    enemy_run_right = NULL;
    enemy_run_left = NULL;
    enemy_jump_right = NULL;
    enemy_jump_left = NULL;
}



