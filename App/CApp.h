/*
 * CApp.h
 *
 *  Created on: 20 sept. 2021
 *      Author: salim
 */
#include <iostream>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <macros.h>

#include <drawingParam.h>
#include <CCharacter.h>
#include <CMinimap.h>
#include "../Container/CContainer.h"

#include <CEnemy.h>
#include <CTile.h>

#define	APP_DEFAULT_TICKRATE	(int)(1000/180)
#define APP_FRAMERATE_PERIOD	(int)(1000/144)
#define APP_ANIMATING_PERIOD	(int)(1000/6)

#define APP_DEFAULT_BACKGROUND_PATH	"Resources/Background/bg.jpg"
#define APP_DEFAULT_LEVEL_PATH		"Resources/Levels/second.map"
#define APP_LEVEL_WIDTH 			(1920)
#define APP_LEVEL_HEIGHT			(1080)

#define APP_TOT_TILES				( (APP_LEVEL_WIDTH/TILE_DEFAULT_SIZE)*(APP_LEVEL_HEIGHT/TILE_DEFAULT_SIZE) )
class CApp {
private:
	SDL_Window*			m_pWindow;
	SDL_Renderer*		m_pRenderer;
	SDL_Texture*		m_pBackground;

	CCharacter*			m_pCharacter;
	CMinimap*			m_pMinimap;
	CContainer*			m_pTiles;
	CContainer*			m_pEnemies;

	int					m_iWidth, m_iHeight;
	SDL_Rect			m_rCamera;

	unsigned int		m_uStatus;

	SDL_TimerID			m_iTimerRendering;
	SDL_TimerID			m_iTimerAnimate;
	SDL_TimerID			m_iTimerInput;
public:
	CApp(int iWidth, int iHeight);
	~CApp();
	void Run();
	static Uint32 _AppCallbackRender(Uint32 interval, CApp* pApp);
	static Uint32 _AppCallbackAnimate(Uint32 interval, CApp* pApp);
	static Uint32 _AppCallbackProcessInputs(Uint32 interval, CApp* pApp);
};
