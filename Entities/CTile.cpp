/*
 * CTile.cpp
 *
 *  Created on: 22 sept. 2021
 *      Author: salim
 */

#include "CTile.h"


SDL_Texture* CTile::c_pTileAtlas = nullptr;

CTile::CTile(SDL_Point ptTilePos, int iTileType):
	m_ptTilePos(ptTilePos),
	m_iTileType(iTileType),
	m_rTileFrame(SDL_Rect{ptTilePos.x, ptTilePos.y, TILE_DEFAULT_SIZE, TILE_DEFAULT_SIZE})
{

}

CTile::~CTile() {

}

int CTile::Draw(SDL_Renderer* pRenderer, SDL_Rect* pCamera) const{
	if( !(SDL_HasIntersection(pCamera, &m_rTileFrame))||(m_iTileType == TILE_TYPE_NONE))
		return 0;

	SDL_Rect	rFrameAdjusted = {m_ptTilePos.x-pCamera->x,m_ptTilePos.y-pCamera->y,TILE_DEFAULT_SIZE,TILE_DEFAULT_SIZE};
	SDL_Rect	rFrameTile = {0,m_iTileType,TILE_SPRITE_SIZE, TILE_SPRITE_SIZE};
	SDL_RenderCopy(
			pRenderer,
			c_pTileAtlas,
			&rFrameTile,
			&rFrameAdjusted
	);
	return 0;
}

void CTile::InitGraph(SDL_Renderer* pRenderer){
	c_pTileAtlas = IMG_LoadTexture(pRenderer, TILE_ATLAS_PATH);
}

void CTile::ReleaseGraph(){
	SDL_DestroyTexture(c_pTileAtlas);
}

void CTile::DeleteFunc(CTile* pTile){delete pTile;}

int  CTile::DrawingParse(CTile* pTile, s_drawParam*	pDrawParam){return pTile->Draw(pDrawParam->pRenderer, pDrawParam->pCamera);}

int CTile::IntersectParse(CTile* pTile, SDL_Rect* pCharacterHitbox){
	if(pTile->m_iTileType==TILE_TYPE_NONE || pTile->m_iTileType==TILE_TYPE_PLANK_FLOOR)
		return 0;
	return (int)(
			SDL_HasIntersection(
					&pTile->m_rTileFrame,
					pCharacterHitbox
			)
	);
}
