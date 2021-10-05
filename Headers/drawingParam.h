/*
 * drawingParam.h
 *
 *  Created on: 26 sept. 2021
 *      Author: salim
 */

#ifndef DRAWINGPARAM_H_
#define DRAWINGPARAM_H_


#include <SDL2/SDL.h>

struct s_drawParam{
	SDL_Renderer*	pRenderer;
	SDL_Rect*		pCamera;
};



#endif /* DRAWINGPARAM_H_ */
