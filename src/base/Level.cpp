#include "base/Level.hpp"
#include "base/PhysicsManager.hpp"
#include <algorithm>

using namespace std;

Level::Level(int width, int height):mh(height), mw(width)
{
  mScore.init();
	goalRemoved = false;
}

Level::~Level()
{
}

void
Level::finalize()
{
  mObjects.clear();
  mObjectsToAdd.clear();
  mObjectsToRemove.clear();
}

void
Level::addObject(std::shared_ptr<GameObject> object)
{
  mObjectsToAdd.push_back(object);
}

void
Level::removeObject(std::shared_ptr<GameObject> object)
{
  mObjectsToRemove.push_back(object);
  if (object->tag() == 5)
  {
	  goalRemoved = true;
  }
}

bool
Level::hasObject(std::shared_ptr<GameObject> object) const
{
  return std::find(mObjects.begin(), mObjects.end(), object) != mObjects.end();
}


void
Level::update()
{
	score_count = 0;
  for (auto obj: mObjectsToAdd) {
    mObjects.push_back(obj);
  }
  mObjectsToAdd.clear();
  
  for (auto gameObject: mObjects) {
	  if(gameObject->tag() == 4 && blast){
		  gameObject->setblast(true);
		  gameObject->update();

	  }
	  else
         gameObject->update();
  }

  PhysicsManager::getInstance().step();
  for (auto gameObject: mObjects) {
    gameObject->postStep();
  }

  for (auto obj: mObjectsToRemove) {
	  if(obj->tag() == 6)
	  {
		  score_count++;
	  }
	  if(obj->tag() == 4)
	  {
		  setblast(false);
	  }
    auto elem = std::find(mObjects.begin(), mObjects.end(), obj);
    if (elem != mObjects.end()) {
      mObjects.erase(elem);
    }
  }
  mObjectsToRemove.clear();
}

void
Level::render(SDL_Renderer * renderer)
{
  for (auto gameObject: mObjects) {
	  //std::cout << "blast in level: "<< blast << "\n";
	  //if(blast)
	    // std::cout << "blast variable: "<< blast << "\n";
	  if(gameObject->tag() == 4 && blast){
		//std::cout << "set blast in render: " << blast<<"\n";
	  	gameObject->setblast(true);
	  	gameObject->render(renderer);

	  }
	  else
        gameObject->render(renderer);
  }

}

bool Level::getscorecount(){
	return score_count;
}

void Level::setdeath(bool val){
	 lost = val;
}

bool Level::getdeath(){
	return lost;
}


