#include "base/InputManager.hpp"
#include <algorithm>

InputManager &
InputManager::getInstance()
{
  static InputManager * instance = new InputManager();
  return *instance;
}

void
InputManager::startUp()
{
}

void
InputManager::shutDown()
{
}

void
InputManager::resetForFrame()
{
  mKeysPressed.clear();
}

void
InputManager::handleEvent(const SDL_Event & e)
{
  if (e.type == SDL_KEYDOWN) {
    auto elem = mKeysDown.find(e.key.keysym.sym);
    if (elem == mKeysDown.end()) {
      mKeysPressed.insert(e.key.keysym.sym);
    }
    mKeysDown.insert(e.key.keysym.sym);
  } else if (e.type == SDL_KEYUP) {
    mKeysDown.erase(e.key.keysym.sym);
    auto b = mKeysBlocked.find(e.key.keysym.sym);
    if(b != mKeysBlocked.end()) {
      mKeysBlocked.erase(e.key.keysym.sym);
    }
  }
}

void InputManager::blockKey(SDL_Keycode k) {
  auto elem = mKeysBlocked.find(k);
  if(elem == mKeysBlocked.end()) {
    mKeysBlocked.insert(k);
  }
}

bool
InputManager::isKeyDown(SDL_Keycode k) const
{
  return mKeysDown.find(k) != mKeysDown.end();
}

bool
InputManager::isKeyPressed(SDL_Keycode k) const
{
  return mKeysPressed.find(k) != mKeysPressed.end();
}

bool
InputManager::isKeyBlocked(SDL_Keycode k) const {
  return mKeysBlocked.find(k) != mKeysBlocked.end();
}
