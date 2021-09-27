/*
 * CCharacter.cpp
 *
 *  Created on: 20 sept. 2021
 *      Author: salim
 */

#include <macros.h>

#include "CCharacter.h"


CCharacter::CCharacter(SDL_Renderer* pRenderer, int iX, int iY, int iLevelWidth, int iLevelHeight):
	m_rFrame(SDL_Rect{iX, iY, CHARACTER_DEFAULT_SIZE, CHARACTER_DEFAULT_SIZE}),
	m_ptSpeed(SDL_Point{CHARACTER_DEFAULT_SPEED, CHARACTER_DEFAULT_SPEED}),
	m_colCharacter(CHARACTER_DEFAULT_COLOR),
	m_pTextureChara(IMG_LoadTexture(pRenderer, CHARACTER_TEXTURE_PATH)),
	m_iLevelWidth(iLevelWidth),
	m_iLevelHeight(iLevelHeight),
	m_uDirection(DIR_DOWN),
	m_iIsMoving(0),
	m_iAnimationStep(1),
	m_iIsAttacking(0)
{

}

CCharacter::~CCharacter() {
	if(m_pTextureChara)SDL_DestroyTexture(m_pTextureChara);
}

void CCharacter::Draw(SDL_Renderer* pRenderer, int iCameraX, int iCameraY) const{
	SDL_Rect m_rFrameAdjusted = m_rFrame;
	m_rFrameAdjusted.x -= iCameraX;
	m_rFrameAdjusted.y -= iCameraY;
	int	iSpriteOffset = m_iIsMoving*CHARACTER_ANIMATION_OFFSET*m_iAnimationStep;

	/*	The +4 and -8 you see are meant to compensate for the padding present on the sprite, that made it look smaller and added invisible borders
		to its hitbox */

	switch(m_uDirection){
	case DIR_RIGHT:
		SDL_RenderCopyEx(
			pRenderer,
			m_pTextureChara,
			&SDL_Rect{iSpriteOffset+4, CHARACTER_LEFT_OFFSET+4, CHARACTER_SIZE_POINT.x-8, CHARACTER_SIZE_POINT.y-8},
			&m_rFrameAdjusted,
			0,
			nullptr,
			(SDL_RendererFlip)SDL_FLIP_HORIZONTAL
		);
		break;
	case DIR_LEFT:
		SDL_RenderCopy(
			pRenderer,
			m_pTextureChara,
			&SDL_Rect{iSpriteOffset+4, CHARACTER_LEFT_OFFSET+4, CHARACTER_SIZE_POINT.x-8, CHARACTER_SIZE_POINT.y-8},
			&m_rFrameAdjusted
		);
		break;
	case DIR_DOWN:
		SDL_RenderCopy(
			pRenderer,
			m_pTextureChara,
			&SDL_Rect{iSpriteOffset+4, CHARACTER_DOWN_OFFSET+4, CHARACTER_SIZE_POINT.x-8, CHARACTER_SIZE_POINT.y-8},
			&m_rFrameAdjusted
		);
		break;
	case DIR_UP:
		SDL_RenderCopy(
			pRenderer,
			m_pTextureChara,
			&SDL_Rect{iSpriteOffset+4, CHARACTER_UP_OFFSET+4, CHARACTER_SIZE_POINT.x-8, CHARACTER_SIZE_POINT.y-8},
			&m_rFrameAdjusted
		);
		break;
	default:
		break;
	}
	if(m_iIsAttacking){
		SDL_SetRenderDrawColor(pRenderer, 0xFF, 0x55, 0x55, 0x7F);
		SDL_RenderFillRect(pRenderer, &m_rFrameAttack);
	}
}

void CCharacter::Move(int iDirection){
	switch(iDirection){
	case DIR_RIGHT:
		if(m_rFrame.x+m_rFrame.w>m_iLevelWidth) break;
		m_rFrame.x+=m_ptSpeed.x;
		m_uDirection = DIR_RIGHT;
		break;
	case DIR_LEFT:
		if(m_rFrame.x<0) break;
		m_rFrame.x-=m_ptSpeed.x;
		m_uDirection = DIR_LEFT;
		break;
	case DIR_DOWN:
		if(m_rFrame.y+m_rFrame.h>m_iLevelHeight) break;
		m_rFrame.y+=m_ptSpeed.y;
		m_uDirection = DIR_DOWN;
		break;
	case DIR_UP:
		if(m_rFrame.y<0) break;
		m_rFrame.y-=m_ptSpeed.y;
		m_uDirection = DIR_UP;
		break;
	default:
		break;
	}

	//Blocks our character at the level's boundaries
}

SDL_Point CCharacter::GetCoords() const{
	return SDL_Point{m_rFrame.x, m_rFrame.y};
}

SDL_Point CCharacter::GetSize() const{
	return SDL_Point{m_rFrame.w, m_rFrame.h};
}

SDL_Rect CCharacter::Attack(SDL_Rect* pCamera){
	m_rFrameAttack = m_rFrame;
	m_rFrameAttack.x -= pCamera->x;
	m_rFrameAttack.y -= pCamera->y;
	switch(m_uDirection){
	case DIR_RIGHT:
		m_rFrameAttack.x+=m_rFrame.w;
		break;
	case DIR_LEFT:
		m_rFrameAttack.x-=m_rFrame.w;
		break;
	case DIR_DOWN:
		m_rFrameAttack.y+=m_rFrame.h;
		break;
	case DIR_UP:
		m_rFrameAttack.y-=m_rFrame.h;
		break;
	default:
		break;
	}
	return m_rFrameAttack;
}
SDL_Rect CCharacter::GetFrame() const{
	return m_rFrame;
}

void CCharacter::SetMoving(){if(!m_iIsMoving)m_iIsMoving=1;}

void CCharacter::UnsetMoving(){if(m_iIsMoving)m_iIsMoving=0;}

void CCharacter::SetAttacking(){if(!m_iIsAttacking)m_iIsAttacking=1;}

void CCharacter::UnsetAttacking(){if(m_iIsAttacking)m_iIsAttacking=0;}


void CCharacter::ChangeAnimStep(){
	if (!m_iIsMoving)
		return;

	static int iSwitch=0;

	if(!iSwitch)
		m_iAnimationStep++;
	else
		m_iAnimationStep--;
	if(m_iAnimationStep==3)
		iSwitch=1;
	if(m_iAnimationStep==1)
		iSwitch=0;
}

int	CCharacter::GetDirection() const{return m_uDirection;}


int CCharacter::GetAttacking() const{
	return m_iIsAttacking;
}
