#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

enum E_BATTLE_RESULT
{
	VICTORY,
	LOSE,
};

class CObjBattleEndEffect : public CObj
{
public:
	CObjBattleEndEffect(E_BATTLE_RESULT res) { m_result = res; }
	~CObjBattleEndEffect() {}
	void Init();
	void Action();
	void Draw();

private:
	E_BATTLE_RESULT m_result;

	CTexture m_tex_result;
	CAnime3 m_ani_result;
};
