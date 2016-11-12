//
//  input.cpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/5/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#include "input.hpp"

void Input::beginNewFrame()
{
    this->_pressedKeys.clear();
    this->_releaseKeys.clear();
}

void Input::keyDownEvent(const SDL_Event &event)
{
    this->_pressedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event &event)
{
    this->_releaseKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = false;
}

bool Input::wasKeyPressed(SDL_Scancode key)
{
    return this->_pressedKeys[key];
}

bool Input::wasKeyRelease(SDL_Scancode key)
{
    return this->_releaseKeys[key];
}

bool Input::isKeyHeld(SDL_Scancode key)
{
    return this->_heldKeys[key];
}