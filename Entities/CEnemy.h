/*
 * CEnemy.h
 *
 *  Created on: 26 sept. 2021
 *      Author: salim
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <drawingParam.h>

#define ENEMY_DEFAULT_SIZE		(48)
#define ENEMY_TEXTURE_PATH		"Resources/Enemy/texture.png"

class CEnemy {
public:
	struct s_damageParams{
		SDL_Rect*	pCamera;
		SDL_Rect*	pRectHitbox;
		int			iDamage;
	};
private:
 	static SDL_Texture* 	c_pTexture;
private:
	SDL_Point				m_ptPosition;
	SDL_Rect				m_rFrame;
	int						m_iHealth;
public:
	CEnemy(int iPosX, int iPosY, int iHealth);
	~CEnemy();
	void Draw(SDL_Renderer* pRenderer, SDL_Rect* pCamera) const;
	int  IsDead() const;
	void TakeDamage(SDL_Rect* pRectHitbox, int iDamage, SDL_Rect*pCamera);
	int  GetHealth() const;
	static void InitGraph(SDL_Renderer* pRenderer);
	static void ReleaseGraph();
	static int	IsDeadParse(CEnemy* pEnemy);
	static void TakeDamageParse(CEnemy* pEnemy, s_damageParams* pDamageParams);
	static void	DrawingParse(CEnemy* pEnemy, s_drawParam* pDrawingParams);
	static void DeleteFunc(CEnemy* pEnemy);
};
