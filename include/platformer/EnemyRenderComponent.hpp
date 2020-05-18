/*
 * EnemyRender.hpp
 *
 *  Created on: Mar 23, 2020
 *      Author: trive
 */

#ifndef ENEMYRENDERCOMPONENT_HPP
#define	ENEMYRENDERCOMPONENT_HPP

#include "base/RenderComponent.hpp"
#include "base/GameObject.hpp"
#include "SDL.h"
//! \brief used to render enemy component
class EnemyRenderComponent : public RenderComponent {
public:
    EnemyRenderComponent(GameObject&,
        SDL_Texture*,
        SDL_Texture*,
        SDL_Texture*,
        SDL_Texture*,
        SDL_Texture*,
        SDL_Texture*,
        int, int, int);
    /**
     * render the enemy character from spritesheet
     */
    virtual void render(SDL_Renderer * renderer) override;
    /**
     * Update the enemy character from spritesheet
     */
    void update(int);

private:
    SDL_Texture
        *idle_right,
        *idle_left,
        *run_right,
        *run_left,
        *jump_right,
        *jump_left;
    int currentFrame{0};
    int
        idle_frames,
        run_frames,
        jump_frames
    ;

    int currentRow{0};
    SDL_Rect src;
    SDL_Rect dest;
    std::shared_ptr<PatrolComponent> pc;
};



#endif
