/*
 * CMinimap.h
 *
 *  Created on: 21 sept. 2021
 *      Author: salim
 */

#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define MINIMAP_DEFAULT_DIVIDER			(int)(20)

#define MINIMAP_CAMERA_OUTLINE_COLOR	SDL_Color{0xFF, 0x00, 0x00, 0xFF}
#define MINIMAP_LEVEL_OUTLINE_COLOR		SDL_Color{0xFF, 0xFF, 0xFF, 0xFF}
#define	MINIMAP_CHARA_FILLING_COLOR		SDL_Color{0xFF, 0xFF, 0xFF, 0xFF}

class CMinimap {
private:
	int			m_iPosX, m_iPosY;
	SDL_Rect	m_rFrameLevel;
	SDL_Rect	m_rFrameCamera;
	SDL_Rect	m_rFrameCharacter;

public:
	CMinimap(SDL_Rect rFrameLevel, int iPosX, int iPosY);
	~CMinimap();
	void UpdateRects(SDL_Rect rFrameCamera, SDL_Rect rFrameCharacter);
	void Draw(SDL_Renderer* pRenderer);
};

