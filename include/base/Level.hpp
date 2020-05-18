#ifndef BASE_LEVEL
#define BASE_LEVEL

#include "base/GameObject.hpp"
#include "base/TextComponent.hpp"
#include "base/Score.hpp"
#include "base/Lives.hpp"
#include <SDL.h>
#include <memory>
#include <vector>

//! \brief A level in the game.  Essentially mannages a collection of game
//! objects, and does some collision detection.
class Level {
public:

  Level(int, int);
  virtual ~Level();
  int score_count{0};
  bool blast = false;
  void finalize();

  inline int h() { return mh; }
  inline int w() { return mw; }

  inline bool levelComplete() { return complete; }
  inline void setComplete(bool val) { complete = val; }

  void setblast(bool b){blast = b;}
  bool getblast(){return blast;}

  inline bool isPaused() { return paused; }
  inline void setPaused(bool val) { paused = val; }

  inline bool started() { return start; }
  inline void setStart(bool val) { start = val; }
  void addObject(std::shared_ptr<GameObject> object); //!< Set an object to be added.
  void removeObject(std::shared_ptr<GameObject> object); //!< Set an object to be removed.

  void update(); //!< Update the objects in the level.
  void render(SDL_Renderer * renderer); //!< Render the level.
  bool getscorecount();
  void setdeath(bool val);
  bool getdeath();

  bool hasObject(std::shared_ptr<GameObject> object) const;

  void inline setRenderer(SDL_Renderer* r) { renderer = r; };
  inline SDL_Renderer* getRenderer() { return renderer; }
  void inline incrementScore(int inc) { mScore.incrementScore(inc); }
  int inline getScore() { return mScore.getScore(); }
  void inline resetScore() { mScore.init(); }


  int inline getLives() { return mLives.getLives(); }
  void inline decrementLife() { mLives.decrementLife(); }
  void inline setLife(int c) { mLives.setLife(c); }

  std::vector<std::shared_ptr<GameObject>> inline getObjects() { return mObjects; }

  bool goalRemoved;

private:
  
  Level(const Level &) = delete;
  void operator=(Level const&) = delete;
  int mh, mw;

  std::vector<std::shared_ptr<GameObject>> mObjects;
  bool complete{false};
  bool paused{false};
  bool start{false};
  bool lost{false};
  std::vector<std::shared_ptr<GameObject>> mObjectsToAdd;
  std::vector<std::shared_ptr<GameObject>> mObjectsToRemove;
  Score mScore;
  Lives mLives;
  SDL_Renderer* renderer;
};

#endif
