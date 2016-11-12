//
//  animatedsprite.hpp
//  Cavestory_Remake
//
//  Created by zhekazheka on 9/29/16.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef animatedsprite_hpp
#define animatedsprite_hpp

#include <map>
#include <vector>
#include <string>

#include "sprite.hpp"
#include "globals.h"

class Graphics;

class AnimatedSprite : public Sprite
{
public:
    AnimatedSprite();
    AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
                   float posX, float posY, float timeToUpdate);
    
    /* void playAnimation
     * Play the animation provided animation if it's not already playing
     */
    void playAnimation(std::string animation, bool once = false);
    
    /* void update
     * Update the animatied sprite (timer)
     */
    void update(int elapsedTime);
    
    /* void draw
     * Draws the sprite to the screen
     */
    void draw(Graphics &graphics, int x, int y);
    
protected:
    /* void setupAnimations
     * A required function which setup all animations for sprite
     */
    virtual void setupAnimations() = 0;
    
    /* void animationDone
     * Logic tha happens when the animation ends
     */
    virtual void animationDone(std::string currentAnimation) = 0;
    
    /* void addAnimation
     * Add an animation to the map of the sprite
     */
    void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);
    
    /* void resetAnimation
     * Reset all animation associated with this sprite
     */
    void resetAnimation();
    
    /* void stopAnimation
     * Stop a current animation
     */
    void stopAnimation();
    
    /* void setVisible
     * Set the visibility of this sprite
     */
    void setVisible(bool visible);
    
    double _timeToUpdate;
    std::string _currentAnimation;
    bool _currentAnimationOnce;
    
private:
    std::map<std::string, std::vector<SDL_Rect>> _animations;
    std::map<std::string, Vector2> _offsets;
    
    double _timeElapsed;
    int _frameIndex;
    bool _isVisible;
};

#endif /* animatedsprite_hpp */
