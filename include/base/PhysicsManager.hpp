#include <Box2D/Box2D.h>
#include <vector>

class GameObject;

//! \brief Class for managing physics.
class PhysicsManager {
private:

  PhysicsManager() = default; // Private Singleton
  PhysicsManager(PhysicsManager const&) = delete; // Avoid copy constructor.
  void operator=(PhysicsManager const&) = delete; // Don't allow copy assignment.
  
public:

  static PhysicsManager &getInstance(); //!< Get the instance.

  static constexpr float GAME_TO_PHYSICS_SCALE = 0.1f; //!< scaling from game units to physics units

  void startUp();
  void shutDown();

  void step(); //!< Step physics.

  bool getCollisions(float rx, float ry, float rw, float rh, std::vector<std::shared_ptr<GameObject>> & objects) const; //!< Get objects colliding with a given rect. Returns true if there were any objects.

  inline b2World *getWorld() { return mWorld; } //!< Get the world.
  inline const b2World *getWorld() const { return mWorld; } //!< Get the world.
  
private:

  b2World *mWorld;

};