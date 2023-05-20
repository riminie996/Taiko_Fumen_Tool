#include "CObjEnsoBattle.h"
#include "GameHead.h"
#include "GameL\UserData.h"
#include "GameL/Audio.h"
//‰Šú‰»
CObjEnsoBattle::CObjEnsoBattle(string dir)
{



	string str_chara = dir + "Attack1/";
	int count = MusicGame::TextureAmountCount(str_chara, ".rmlyt");
	m_vec_effect.resize(count);
	for (int i = 0; i < m_vec_effect.size(); i++)
	{
		m_vec_effect[i].ani_in.LoadData(str_chara+"In/" + to_string(i));
		m_vec_effect[i].ani_wait.LoadData(str_chara + "Wait/" + to_string(i));
		m_vec_effect[i].ani_out.LoadData(str_chara + "Out/" + to_string(i));
		m_vec_effect[i].lyt.LoadData(str_chara + to_string(i));
		m_vec_effect[i].tex.LoadTexture(str_chara + m_vec_effect[i].lyt.GetTexName());
	}
	string aud_dir = dir + "Attack1.ogg";
	Audio::LoadAudio2(se_EFFECT1, aud_dir.c_str(), EFFECT);
}

void CObjEnsoBattle::Init()
{
	m_life = LIFE_INIT;
	m_end_flag = false;
}
//is
void CObjEnsoBattle::Action()
{

	for (int i = 0; i < m_vec_effect.size(); i++)
	{
		m_vec_effect[i].Action();
	}
}
//•`‰æ
void CObjEnsoBattle::Draw()
{
	for (int i = 0; i < m_vec_effect.size(); i++)
	{
		m_vec_effect[i].Draw();
	}
}

void CObjEnsoBattle::EffectStart(int number)
{
	for (int i = 0; i < m_vec_effect.size(); i++)
	{
		m_vec_effect[i].Start();
	}
	Audio::Start(se_EFFECT1);
}
void CObjEnsoBattle::EffectEnd()
{
	for (int i = 0; i < m_vec_effect.size(); i++)
	{
		m_vec_effect[i].End();
	}
	Audio::Stop(se_EFFECT1);
}

int CObjEnsoBattle::GetResult()
{
	CObjBattleGauge* gauge = (CObjBattleGauge*)Objs::GetObj(OBJ_BATTLE_GAUGE);
	int boss_life = (1.0f - gauge->GetGaugePercent()) * 50.0f;
	
	if ((int)(((float)m_life / (float)LIFE_INIT) * 50) >= boss_life)
	{
		return E_BATTLE_RESULT::VICTORY;
	}
	return E_BATTLE_RESULT::LOSE;
}

void CObjEnsoBattle::BattleEnd()
{
	m_end_flag = true;
	CObjBattleCharacter* chara = (CObjBattleCharacter*)Objs::GetObj(OBJ_BATTLE_CHARA);
	chara->Lose();

}