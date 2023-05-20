#include "CObjBattleCharacter.h"
#include "GameHead.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

CObjBattleCharacter::CObjBattleCharacter(string dir)
{
	string str_chara = dir + "Chara/Wait/";
	int count = MusicGame::TextureAmountCount(str_chara, ".rmlyt");
	m_vec_chara_wait.resize(count);
	for (int i = 0; i < m_vec_chara_wait.size(); i++)
	{
		m_vec_chara_wait[i].ani.LoadData(str_chara + to_string(i));
		m_vec_chara_wait[i].lyt.LoadData(str_chara + to_string(i));
		m_vec_chara_wait[i].tex.LoadTexture(str_chara + m_vec_chara_wait[i].lyt.GetTexName());
	}
	str_chara = dir + "Chara/Pinch_40/";
	count = MusicGame::TextureAmountCount(str_chara, ".rmlyt");
	m_vec_chara_pinch40.resize(count);
	for (int i = 0; i < m_vec_chara_pinch40.size(); i++)
	{
		m_vec_chara_pinch40[i].ani.LoadData(str_chara + to_string(i));
		m_vec_chara_pinch40[i].lyt.LoadData(str_chara + to_string(i));
		m_vec_chara_pinch40[i].tex.LoadTexture(str_chara + m_vec_chara_pinch40[i].lyt.GetTexName());
	}

	str_chara = dir + "Chara/Pinch_20/";
	count = MusicGame::TextureAmountCount(str_chara, ".rmlyt");
	m_vec_chara_pinch20.resize(count);
	for (int i = 0; i < m_vec_chara_pinch20.size(); i++)
	{
		m_vec_chara_pinch20[i].ani.LoadData(str_chara + to_string(i));
		m_vec_chara_pinch20[i].lyt.LoadData(str_chara + to_string(i));
		m_vec_chara_pinch20[i].tex.LoadTexture(str_chara + m_vec_chara_pinch20[i].lyt.GetTexName());
	}

	str_chara = dir + "Chara/Lose/";
	count = MusicGame::TextureAmountCount(str_chara, ".rmlyt");
	m_vec_chara_lose.resize(count);
	for (int i = 0; i < m_vec_chara_lose.size(); i++)
	{
		m_vec_chara_lose[i].ani.LoadData(str_chara + to_string(i));
		m_vec_chara_lose[i].lyt.LoadData(str_chara + to_string(i));
		m_vec_chara_lose[i].tex.LoadTexture(str_chara + m_vec_chara_lose[i].lyt.GetTexName());
	}
}

//‰Šú‰»
void CObjBattleCharacter::Init()
{
	m_end_flag = false;
}
//is
void CObjBattleCharacter::Action()
{
	for (int i = 0; i < m_vec_chara_wait.size(); i++)
	{
		if (!m_vec_chara_wait[i].ani.GetStart())
			m_vec_chara_wait[i].ani.Start();

		m_vec_chara_wait[i].ani.ActionLoop();
	}
	for (int i = 0; i < m_vec_chara_pinch40.size(); i++)
	{
		if (!m_vec_chara_pinch40[i].ani.GetStart())
			m_vec_chara_pinch40[i].ani.Start();

		m_vec_chara_pinch40[i].ani.ActionLoop();
	}
	for (int i = 0; i < m_vec_chara_pinch20.size(); i++)
	{
		if (!m_vec_chara_pinch20[i].ani.GetStart())
			m_vec_chara_pinch20[i].ani.Start();

		m_vec_chara_pinch20[i].ani.ActionLoop();
	}
	for (int i = 0; i < m_vec_chara_lose.size(); i++)
	{
		m_vec_chara_lose[i].ani.Action();
	}
}
//•`‰æ
void CObjBattleCharacter::Draw()
{
	CObjBattleGauge* gauge = (CObjBattleGauge*)Objs::GetObj(OBJ_BATTLE_GAUGE);

	if (m_end_flag == true && m_vec_chara_lose.size() > 0)
	{
		for (int i = 0; i < m_vec_chara_lose.size(); i++)
		{
			if (m_vec_chara_lose[i].ani.GetStart())

				m_vec_chara_lose[i].Draw();
		}
	}
	else if (1.0f - gauge->GetGaugePercent() < 0.2f && m_vec_chara_pinch20.size() > 0)
	{
		for (int i = 0; i < m_vec_chara_pinch20.size(); i++)
		{
			m_vec_chara_pinch20[i].Draw();
		}
	}
	else if (1.0f - gauge->GetGaugePercent() < 0.4f && m_vec_chara_pinch40.size() > 0)
	{
		for (int i = 0; i < m_vec_chara_pinch40.size(); i++)
		{
			m_vec_chara_pinch40[i].Draw();
		}
	}
	else
	{
		for (int i = 0; i < m_vec_chara_wait.size(); i++)
		{
			m_vec_chara_wait[i].Draw();
		}
	}
}

void CObjBattleCharacter::Lose()
{
	CObjEnsoBattle* battle = (CObjEnsoBattle*)Objs::GetObj(OBJ_BATTLE);
	m_end_flag = true; 
	if (battle->GetResult() == E_BATTLE_RESULT::VICTORY)
	{
		for (int i = 0; i < m_vec_chara_lose.size(); i++)
		{
			m_vec_chara_lose[i].ani.Start();
		}
	}
}