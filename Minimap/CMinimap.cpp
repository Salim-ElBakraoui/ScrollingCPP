

#include "CMinimap.h"

CMinimap::CMinimap(SDL_Rect rFrameLevel, int iPosX, int iPosY):
	m_iPosX(iPosX),
	m_iPosY(iPosY),
	m_rFrameLevel(SDL_Rect{0,0,0,0}),
	m_rFrameCamera(SDL_Rect{0,0,0,0}),
	m_rFrameCharacter(SDL_Rect{0,0,0,0})
{
	//The level frame is not going to change anyways, so lets just set it first
	m_rFrameLevel.x=m_iPosX+rFrameLevel.x/MINIMAP_DEFAULT_DIVIDER;
	m_rFrameLevel.y=m_iPosY+rFrameLevel.y/MINIMAP_DEFAULT_DIVIDER;
	m_rFrameLevel.w=rFrameLevel.w/MINIMAP_DEFAULT_DIVIDER;
	m_rFrameLevel.h=rFrameLevel.h/MINIMAP_DEFAULT_DIVIDER;

}

void CMinimap::UpdateRects(SDL_Rect rFrameCamera, SDL_Rect rFrameCharacter){
	//Here, values are going to change so that's important to update them
	m_rFrameCamera=SDL_Rect{
		m_iPosX+rFrameCamera.x/MINIMAP_DEFAULT_DIVIDER,
		m_iPosY+rFrameCamera.y/MINIMAP_DEFAULT_DIVIDER,
		rFrameCamera.w/MINIMAP_DEFAULT_DIVIDER,
		rFrameCamera.h/MINIMAP_DEFAULT_DIVIDER};

	m_rFrameCharacter=SDL_Rect{
		m_iPosX+rFrameCharacter.x/MINIMAP_DEFAULT_DIVIDER,
		m_iPosY+rFrameCharacter.y/MINIMAP_DEFAULT_DIVIDER,
		rFrameCharacter.w/MINIMAP_DEFAULT_DIVIDER,
		rFrameCharacter.h/MINIMAP_DEFAULT_DIVIDER};

}

CMinimap::~CMinimap() {

}

void CMinimap::Draw(SDL_Renderer* pRenderer){

	SDL_SetRenderDrawColor(
			pRenderer,
			MINIMAP_CAMERA_OUTLINE_COLOR.r,
			MINIMAP_CAMERA_OUTLINE_COLOR.g,
			MINIMAP_CAMERA_OUTLINE_COLOR.b,
			MINIMAP_CAMERA_OUTLINE_COLOR.a
	);

	SDL_RenderDrawRect(pRenderer, &m_rFrameCamera);

	SDL_SetRenderDrawColor(
			pRenderer,
			MINIMAP_CHARA_FILLING_COLOR.r,
			MINIMAP_CHARA_FILLING_COLOR.g,
			MINIMAP_CHARA_FILLING_COLOR.b,
			MINIMAP_CHARA_FILLING_COLOR.a
	);

	SDL_RenderFillRect(pRenderer, &m_rFrameCharacter);

	SDL_SetRenderDrawColor(
			pRenderer,
			MINIMAP_LEVEL_OUTLINE_COLOR.r,
			MINIMAP_LEVEL_OUTLINE_COLOR.g,
			MINIMAP_LEVEL_OUTLINE_COLOR.b,
			MINIMAP_LEVEL_OUTLINE_COLOR.a
	);

	SDL_RenderDrawRect(pRenderer, &m_rFrameLevel);
}
