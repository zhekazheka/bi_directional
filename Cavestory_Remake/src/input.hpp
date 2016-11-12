//
//  input.hpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/5/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef input_hpp
#define input_hpp

#include <SDL2/SDL.h>
#include <map>

class Input
{
public:
    void beginNewFrame();
    void keyUpEvent(const SDL_Event &event);
    void keyDownEvent(const SDL_Event &event);
    
    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyRelease(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);
    
private:
    std::map<SDL_Scancode, bool> _heldKeys;
    std::map<SDL_Scancode, bool> _pressedKeys;
    std::map<SDL_Scancode, bool> _releaseKeys;
};

#endif /* input_hpp */
