#ifndef BASE_GAME_OBJECT
#define BASE_GAME_OBJECT

#include "base/GenericComponent.hpp"
#include "base/PhysicsComponent.hpp"
#include "base/RenderComponent.hpp"
#include "base/PatrolComponent.hpp"
#include <memory>
#include <vector>
#include "iostream"

class Level;

//! \brief Represents an object in the game.  Has some essential
//! properties (position and size), a tag (identifying the general
//! category of object), and a collection of components, including any
//! number of generic components and optionally a physics component
//! and a render component.
class GameObject : public std::enable_shared_from_this<GameObject> {
public:
  int TAG_PLAYER = 1;
  int TAG_ENEMY = 2;
  int TAG_GOAL = 3;
  int TAG_BLOCK = 4;
  bool blast = false;

  GameObject(Level & level, float x, float y, float w, float h, int tag);
  virtual ~GameObject();

  inline int tag() const { return mTag; }

  void setblast(bool b){blast = b;}
    
  inline void setX(float x) { mX = x; }
  inline void setY(float y) { mY = y; }
  inline void setW(float w) { mW = w; }
  inline void setH(float h) { mH = h; }

  inline float x() const { return mX; }
  inline float y() const { return mY; }
  inline float w() const { return mW; }
  inline float h() const { return mH; }
  inline float tag() { return mTag; }
  inline void addGenericCompenent(std::shared_ptr<GenericComponent> comp) { mGenericComponents.push_back(comp); }
  inline void setPhysicsCompenent(std::shared_ptr<PhysicsComponent> comp) { mPhysicsComponent = comp; }
  inline void setRenderCompenent(std::shared_ptr<RenderComponent> comp) { mRenderComponent = comp; }
  inline void setPatrolComponent(std::shared_ptr<PatrolComponent> comp) { mPatrolComponent = comp; }
  
  inline bool left() { return mLeft; }
  inline bool right() { return mRight; }
  inline bool up() { return mUp; }
  inline bool down() { return mDown; }
  inline bool running() { return mRun; }


  inline void setLeft(bool val) { mLeft = val; }
  inline void setRight(bool val) { mRight = val; }
  inline void setUp(bool val) { mUp = val; }
  inline void setDown(bool val) { mDown = val; }
  inline void setRun(bool val) { mRun = val; }

  inline bool isStrong() { return strong; }
  inline void setStrong(bool val) { strong = val; }

  inline bool isCollectibleVisible() { return collectibleVisibility; }
  inline void setCollectibleVisibility(bool val) { collectibleVisibility = val; }

  inline std::vector<std::shared_ptr<GenericComponent>> genericComponents() { return mGenericComponents; }
  inline std::shared_ptr<PhysicsComponent> physicsComponent() { return mPhysicsComponent; }
  inline std::shared_ptr<RenderComponent> renderComponent() { return mRenderComponent; }
  inline std::shared_ptr<PatrolComponent> patrolComponent() { return mPatrolComponent; }
  
  void update(); //!< Update the object.
  void collision(std::shared_ptr<GameObject> obj); //!< Handle collisions with another object.
  void postStep(); //!< After the physics step for the object.
  void render(SDL_Renderer * renderer); //!< Render the object.
  
  bool isColliding(const GameObject & obj) const; //!< Determine if this object is colliding with another.
  bool isColliding(float px, float py) const; //!< Determine if this object is colliding with a point.

private:

  GameObject(const GameObject &) = delete;
  void operator=(GameObject const&) = delete;

  Level & mLevel;
  float mX, mY, mW, mH;
  int mTag;
  bool 
    mLeft{false},
    mRight{true},
    mUp{false},
    mDown{true},
    mRun;

  bool strong{false}, collectibleVisibility{false};
  std::vector<std::shared_ptr<GenericComponent>> mGenericComponents;
  std::shared_ptr<PhysicsComponent> mPhysicsComponent;
  std::shared_ptr<RenderComponent> mRenderComponent;
  std::shared_ptr<PatrolComponent> mPatrolComponent;

};

#endif
