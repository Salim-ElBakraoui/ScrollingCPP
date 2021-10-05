/*
 * CTile.h
 *
 *  Created on: 22 sept. 2021
 *      Author: salim
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <drawingParam.h>

#define TILE_DEFAULT_SIZE		(60)
#define TILE_SPRITE_SIZE		(40)
#define TILE_ATLAS_PATH			"Resources/LevelTiles/tiles.png"

enum e_tileType{
	TILE_TYPE_NONE  		= 3,
	TILE_TYPE_PLANK_FLOOR	= 0,
	TILE_TYPE_GLASS			= 40,
	TILE_TYPE_STONE 		= 80
};


class CTile {
private:
	static SDL_Texture*		c_pTileAtlas;
private:
	SDL_Point				m_ptTilePos;
	int						m_iTileType;
	SDL_Rect				m_rTileFrame;
public:
	CTile(SDL_Point ptTilePos, int iTileType);
	~CTile();
	int Draw(SDL_Renderer* pRenderer, SDL_Rect* pCamera) const;

public:
	static void InitGraph(SDL_Renderer* pRenderer);
	static void ReleaseGraph();
	static void DeleteFunc(CTile* pTile);
	static int  DrawingParse(CTile* pTile, s_drawParam*	pDrawParam);
	static int  IntersectParse(CTile* pTile, SDL_Rect* pCharacterHitbox);
};
