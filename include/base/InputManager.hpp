#include <SDL.h>
#include <set>

//! \brief Class for managing (keyboard) input.
class InputManager {
private:

  InputManager() = default; // Private Singleton
  InputManager(InputManager const&) = delete; // Avoid copy constructor.
  void operator=(InputManager const&) = delete; // Don't allow copy assignment.
  std::set<SDL_Keycode> mKeysDown;
  std::set<SDL_Keycode> mKeysPressed;
  std::set<SDL_Keycode> mKeysBlocked;
  bool blocked{false};
  
public:

  static InputManager &getInstance(); //!< Get the instance.

  void startUp();
  void shutDown();

  void resetForFrame(); //!< Reset key state for a new frame.
  void handleEvent(const SDL_Event & e); //!< Update key state based on an event.
  void blockKey(SDL_Keycode k);
  bool isKeyDown(SDL_Keycode k) const; //!< Get if a key is currently down.
  bool isKeyPressed(SDL_Keycode k) const; //!< Get if a key was pressed this frame.
  bool isKeyBlocked(SDL_Keycode k) const;
  inline bool isBlocked() { return blocked; }
  inline void setBlock(bool val) { blocked = val; }

};
