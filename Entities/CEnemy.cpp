/*
 * CEnemy.cpp
 *
 *  Created on: 26 sept. 2021
 *      Author: salim
 */

#include "CEnemy.h"

SDL_Texture* CEnemy::c_pTexture = nullptr;

CEnemy::CEnemy(int iPosX, int iPosY, int iHealth):
	m_ptPosition(SDL_Point{iPosX, iPosY}),
	m_rFrame(SDL_Rect{m_ptPosition.x, m_ptPosition.y, ENEMY_DEFAULT_SIZE,ENEMY_DEFAULT_SIZE}),
	m_iHealth(iHealth)
{

}

CEnemy::~CEnemy() {

}

void CEnemy::Draw(SDL_Renderer* pRenderer, SDL_Rect* pCamera) const{
	SDL_Rect m_rFrameAdjusted = m_rFrame;
	m_rFrameAdjusted.x = m_rFrameAdjusted.x-pCamera->x;
	m_rFrameAdjusted.y = m_rFrameAdjusted.y-pCamera->y;

	if(!c_pTexture){
		SDL_SetRenderDrawColor(pRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(pRenderer, &m_rFrameAdjusted);
	}
	else{
		SDL_RenderCopy(pRenderer, c_pTexture, nullptr, &m_rFrameAdjusted);
	}
}

int  CEnemy::IsDead() const{
	return (m_iHealth<=0);
}

void CEnemy::TakeDamage(SDL_Rect* pRectHitbox, int iDamage, SDL_Rect*pCamera){
	SDL_Rect m_rFrameAdjusted = m_rFrame;
	m_rFrameAdjusted.x -= pCamera->x;
	m_rFrameAdjusted.y -= pCamera->y;
	if(SDL_HasIntersection(&m_rFrameAdjusted, pRectHitbox))
		m_iHealth-=iDamage;
}

int CEnemy::GetHealth() const{
	return m_iHealth;
}

void CEnemy::InitGraph(SDL_Renderer* pRenderer){
	c_pTexture = IMG_LoadTexture(pRenderer, ENEMY_TEXTURE_PATH);
}

void CEnemy::ReleaseGraph(){
	if(c_pTexture)SDL_DestroyTexture(c_pTexture);
}

int	 CEnemy::IsDeadParse(CEnemy* pEnemy){
	return pEnemy->IsDead();
}

void CEnemy::TakeDamageParse(CEnemy* pEnemy, s_damageParams* pDamageParams){
	pEnemy->TakeDamage(pDamageParams->pRectHitbox, pDamageParams->iDamage, pDamageParams->pCamera);
}

void CEnemy::DrawingParse(CEnemy* pEnemy, s_drawParam* pDrawingParams){
	pEnemy->Draw(pDrawingParams->pRenderer, pDrawingParams->pCamera);
}

void CEnemy::DeleteFunc(CEnemy* pEnemy){
	pEnemy->~CEnemy();
}
