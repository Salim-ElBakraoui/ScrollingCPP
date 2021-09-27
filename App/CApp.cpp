/*
 * CApp.cpp
 *
 *  Created on: 20 sept. 2021
 *      Author: salim
 */
#include <ctime>
#include <fstream>

#include "CApp.h"
enum e_status{
	ST_APP_ALL_CLEARED		=	0x00000000,
	ST_APP_SDL_INITIATED	=	0x00000001,
	ST_APP_INIT_FAILED		=	0x00008000,
};

Uint32 CApp::_AppCallbackProcessInputs(Uint32 interval, CApp* pApp){
    const Uint8* pKeystate = SDL_GetKeyboardState((int*)NULL);

    if(
	!(pKeystate[SDL_SCANCODE_UP] 		&& pKeystate[SDL_SCANCODE_DOWN]) 	&&
		!(pKeystate[SDL_SCANCODE_LEFT] 	&& pKeystate[SDL_SCANCODE_RIGHT]) 	&&
    	(pKeystate[SDL_SCANCODE_LEFT] 	||
		pKeystate[SDL_SCANCODE_RIGHT] 	||
		pKeystate[SDL_SCANCODE_UP]		||
		pKeystate[SDL_SCANCODE_DOWN])
	)pApp->m_pCharacter->SetMoving();

    SDL_Rect rFutureMovement = {0,0,0,0};
    if(pKeystate[SDL_SCANCODE_LEFT])
    {
    	rFutureMovement = pApp->m_pCharacter->GetFrame();
    	rFutureMovement.x--;
    	if(!pApp->m_pTiles->Parse((t_ptfVV)CTile::IntersectParse, &rFutureMovement))
    		pApp->m_pCharacter->Move(DIR_LEFT);
    }
    if(pKeystate[SDL_SCANCODE_RIGHT])
    {
    	rFutureMovement = pApp->m_pCharacter->GetFrame();
    	    	rFutureMovement.x++;
    	    	if(!pApp->m_pTiles->Parse((t_ptfVV)CTile::IntersectParse, &rFutureMovement))
    	    		pApp->m_pCharacter->Move(DIR_RIGHT);
    }
    if(pKeystate[SDL_SCANCODE_UP])
    {
    	rFutureMovement = pApp->m_pCharacter->GetFrame();
    	    	rFutureMovement.y--;
    	    	if(!pApp->m_pTiles->Parse((t_ptfVV)CTile::IntersectParse, &rFutureMovement))
    	    		pApp->m_pCharacter->Move(DIR_UP);
    }
    if(pKeystate[SDL_SCANCODE_DOWN])
    {
    	rFutureMovement = pApp->m_pCharacter->GetFrame();
    	    	rFutureMovement.y++;
    	    	if(!pApp->m_pTiles->Parse((t_ptfVV)CTile::IntersectParse, &rFutureMovement))
    	    		pApp->m_pCharacter->Move(DIR_DOWN);
    }


    //This scans for continuous inputs and moves our character accordingly.

    return interval;
}

Uint32 CApp::_AppCallbackAnimate(Uint32 interval, CApp* pApp){
	pApp->m_pCharacter->ChangeAnimStep();
	CEnemy::s_damageParams sDamageParams;
	if(pApp->m_pCharacter->GetAttacking()){
		sDamageParams = {&pApp->m_rCamera, &pApp->m_pCharacter->Attack(&pApp->m_rCamera), CHARACTER_DEFAULT_DAMAGE};
		pApp->m_pEnemies->Parse((t_ptfVV)CEnemy::TakeDamageParse, &sDamageParams);
	}
	return interval;
}

Uint32 CApp::_AppCallbackRender(Uint32 interval, CApp* pApp){
	pApp->m_rCamera.x = ( pApp->m_pCharacter->GetCoords().x + pApp->m_pCharacter->GetSize().x / 2 ) - pApp->m_iWidth / 2;
	// We center the camera by getting the center of our character in x coordinates and by subtracting half the width of our screen
	pApp->m_rCamera.y = ( pApp->m_pCharacter->GetCoords().y + pApp->m_pCharacter->GetSize().y / 2 ) - pApp->m_iHeight / 2;
	/*Then we center the y coordinate by getting the center
	 * of our character in y coordinates and by subtracting half
	 * the height of our screen
	 */

	if(pApp->m_rCamera.x<0)
		pApp->m_rCamera.x = 0; //Checks to lock the camera in place if it goes too far in all 4 directions

	if(pApp->m_rCamera.y<0)
		pApp->m_rCamera.y = 0;

	if(pApp->m_rCamera.x > APP_LEVEL_WIDTH - pApp->m_rCamera.w)
		pApp->m_rCamera.x = APP_LEVEL_WIDTH - pApp->m_rCamera.w;

	if(pApp->m_rCamera.y > APP_LEVEL_HEIGHT - pApp->m_rCamera.h)
		pApp->m_rCamera.y = APP_LEVEL_HEIGHT - pApp->m_rCamera.h;


	SDL_RenderCopy(
		pApp->m_pRenderer,
		pApp->m_pBackground,
		&pApp->m_rCamera,
		nullptr);
	/*
	 *Here we set our camera as the source rectangle
	 *(we cut a piece from our background that matches the location of our rectangle)
	 */

	s_drawParam sParams{pApp->m_pRenderer, &pApp->m_rCamera};
	pApp->m_pTiles->Parse((t_ptfVV)CTile::DrawingParse, &sParams);
	pApp->m_pEnemies->Parse((t_ptfVV)CEnemy::DrawingParse, &sParams);
	pApp->m_pCharacter->Draw(pApp->m_pRenderer, pApp->m_rCamera.x, pApp->m_rCamera.y);
	pApp->m_pMinimap->UpdateRects(
			pApp->m_rCamera,
			pApp->m_pCharacter->GetFrame());
	pApp->m_pMinimap->Draw(pApp->m_pRenderer);
	pApp->m_pEnemies->ParseDelIf((t_ptfVV)CEnemy::IsDeadParse, nullptr);
	/*
	 * This code sends the updated coordinates of our level and camera, and draw the minimap accordingly
	 */

	SDL_RenderPresent(pApp->m_pRenderer);
	return interval;
}

CApp::CApp(int iWidth, int iHeight):
	m_pWindow(nullptr),
	m_pRenderer(nullptr),
	m_pBackground(nullptr),
	m_pTiles(nullptr),
	m_pEnemies(nullptr),
	m_iWidth(iWidth),
	m_iHeight(iHeight),
	m_rCamera(SDL_Rect{0,0,m_iWidth, m_iHeight}),
	m_uStatus(ST_APP_ALL_CLEARED)
{
	srand((unsigned int)time(nullptr));
	SDL_Init(SDL_INIT_VIDEO);

	m_pWindow = SDL_CreateWindow
	(
		"Scrolling C++ Project",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_iWidth,
		m_iHeight,
		0
	);
	if(!m_pWindow){
		cerr <<"SDL_CreateWindow Failed: " << SDL_GetError() << endl;
		mBitsSet(m_uStatus, ST_APP_INIT_FAILED);
		return;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(!m_pRenderer){
		cerr << "SDL_CreateRenderer HW Failed, resorting to SW: " << SDL_GetError() << endl;
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
		if(!m_pRenderer){
			cerr << "SDL_CreateRenderer SW Failed: " << SDL_GetError() << endl;
			mBitsSet(m_uStatus, ST_APP_INIT_FAILED);
			return;
		}
	}
	m_pBackground = IMG_LoadTexture(m_pRenderer, APP_DEFAULT_BACKGROUND_PATH);

	CTile::InitGraph(m_pRenderer);
	CEnemy::InitGraph(m_pRenderer);

	SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

	mBitsSet(m_uStatus, ST_APP_SDL_INITIATED);
	Run();
}

CApp::~CApp() {
	SDL_RemoveTimer(m_iTimerInput);
	SDL_RemoveTimer(m_iTimerAnimate);
	SDL_RemoveTimer(m_iTimerRendering);


	if(m_pEnemies)		delete m_pEnemies;
	if(m_pTiles) 		delete m_pTiles;
	if(m_pMinimap) 		delete m_pMinimap;
	if(m_pCharacter) 	delete m_pCharacter;

	CEnemy::ReleaseGraph();
	CTile::ReleaseGraph();

	if(m_pBackground)	SDL_DestroyTexture(m_pBackground);
	if(m_pRenderer)		SDL_DestroyRenderer(m_pRenderer);
	if(m_pWindow)		SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void CApp::Run(){
	if(!mIsBitsSet(m_uStatus, ST_APP_SDL_INITIATED))
		return;
	int quit = 0;
	SDL_Event event;

	m_pEnemies = new CContainer((t_ptfV)CEnemy::DeleteFunc);
	m_pTiles = new CContainer((t_ptfV)CTile::DeleteFunc);
	m_pCharacter = new CCharacter(m_pRenderer, APP_LEVEL_WIDTH/2, APP_LEVEL_HEIGHT/2, APP_LEVEL_WIDTH, APP_LEVEL_HEIGHT);
	m_pMinimap = new CMinimap(
		SDL_Rect{0,0,APP_LEVEL_WIDTH,APP_LEVEL_HEIGHT},
		m_iWidth-APP_LEVEL_WIDTH/MINIMAP_DEFAULT_DIVIDER-5,
		m_iHeight-APP_LEVEL_HEIGHT/MINIMAP_DEFAULT_DIVIDER-5
	);

	int iTileType = 0;
	ifstream ifMap(APP_DEFAULT_LEVEL_PATH);

	for(int k=0; k<APP_LEVEL_HEIGHT/TILE_DEFAULT_SIZE;k++){
		for(int m=0; m<APP_LEVEL_WIDTH/TILE_DEFAULT_SIZE;m++){
			ifMap >> iTileType;
			m_pTiles->Pushback(new CTile(SDL_Point{m*TILE_DEFAULT_SIZE, k*TILE_DEFAULT_SIZE},iTileType ));
		}
	}

	for(int k=0; k<3; k++)
		m_pEnemies->Pushback(new CEnemy(TILE_DEFAULT_SIZE*(15+k), TILE_DEFAULT_SIZE*(10+k), 100));

	m_iTimerRendering 	= SDL_AddTimer(APP_FRAMERATE_PERIOD, (SDL_TimerCallback)_AppCallbackRender, this);
	m_iTimerInput 		= SDL_AddTimer(APP_DEFAULT_TICKRATE, (SDL_TimerCallback)_AppCallbackProcessInputs, this);
	m_iTimerAnimate		= SDL_AddTimer(APP_ANIMATING_PERIOD, (SDL_TimerCallback)_AppCallbackAnimate, this);


	while(!quit){
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
				case SDLK_ESCAPE:
					quit = 1;
					break;
				case SDLK_SPACE:
					m_pCharacter->SetAttacking();
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym){
				case SDLK_UP:
				case SDLK_LEFT:
				case SDLK_DOWN:
				case SDLK_RIGHT:
					m_pCharacter->UnsetMoving();
					break;
				case SDLK_SPACE:
					m_pCharacter->UnsetAttacking();
					break;
				default:
					break;
				}
				break;
			case SDL_WINDOWEVENT:
				switch(event.window.event){
				case SDL_WINDOWEVENT_CLOSE:
					quit=1;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}

