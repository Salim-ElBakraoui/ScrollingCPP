/*
 * CCharacter.h
 *
 *  Created on: 20 sept. 2021
 *      Author: salim
 */

#include <iostream>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define CHARACTER_DEFAULT_SIZE		(48)
#define CHARACTER_DEFAULT_COLOR		SDL_Color{0x50, 0x50, 0x50, 0xFF}
#define CHARACTER_DEFAULT_SPEED		(1)
#define CHARACTER_DEFAULT_DAMAGE	(25)

#define CHARACTER_TEXTURE_PATH			"Resources/Character/character_atlas.png"

#define CHARACTER_SIZE_POINT			SDL_Point{32, 32}
#define CHARACTER_ANIMATION_OFFSET		(32)

#define CHARACTER_UP_OFFSET				(32)
#define CHARACTER_LEFT_OFFSET			(96)
#define CHARACTER_RIGHT_OFFSET			(128)
#define CHARACTER_DOWN_OFFSET			(192)

enum e_direction{
	DIR_UP 			= 0b00001000,
	DIR_LEFT 		= 0b00000010,
	DIR_RIGHT 		= 0b00000001,
	DIR_DOWN 		= 0b00000100,
};


class CCharacter {

private:
	SDL_Rect			m_rFrame;
	SDL_Rect			m_rFrameAttack;
	SDL_Point			m_ptSpeed;
	SDL_Color			m_colCharacter;
	SDL_Texture*		m_pTextureChara;

	int					m_iLevelWidth, m_iLevelHeight;
	unsigned int		m_uDirection;
	int					m_iIsMoving, m_iAnimationStep, m_iIsAttacking;

public:
	CCharacter(SDL_Renderer* pRenderer, int iX, int iY, int iLevelWidth, int iLevelHeight);
	~CCharacter();
	void 		Draw(SDL_Renderer* pRenderer, int iCameraX, int iCameraY) const;
	void 		Move(int iDirection);

	void 		SetMoving();
	void		UnsetMoving();

	void		SetAttacking();
	void		UnsetAttacking();

	void		ChangeAnimStep();

	SDL_Point 	GetCoords() const;
	SDL_Point 	GetSize() 	const;
	SDL_Rect 	GetFrame() 	const;
	int			GetDirection() const;
	int			GetAttacking() const;
	SDL_Rect	Attack(SDL_Rect* pCamera);
};
