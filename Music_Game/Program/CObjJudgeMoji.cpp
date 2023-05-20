#include "CObjJudgeMoji.h"
#include "GameL\UserData.h"

//初期化
void CObjJudgeMoji::Init()
{
	m_ani_moji.ani.LoadData("Animation/Enso/JudgeMoji");
	m_ani_exp.ani.LoadData("Animation/Enso/Effect/HitExplosion");
	m_ani_exp_big.ani.LoadData("Animation/Enso/Effect/HitExplosionBig");

	if (((UserData*)Save::GetData())->m_judge_sec_showimg == false)
	{
		Draw::LoadImageW(L"Graphics/3_Enso/Judge.png", tex_JUDGE, TEX_SIZE_64);
	}
	else
	{
		Draw::LoadImageW(L"Graphics/3_Enso/JudgeTime.png", tex_JUDGE, TEX_SIZE_64);
		for (int i = 0; i < ARRAY_LENGTH(m_num_judge); i++)
		{
			m_num_judge[i].SetTex(tex_JUDGE, RECT_NUMBER[i].m_width, RECT_NUMBER[i].m_height, RECT_NUMBER[i].m_x, RECT_NUMBER[i].m_y);
			m_num_judge[i].SetCommaRect(RECT_COMMA[i], 3);
		}
	}

	Draw::SetBlend(tex_HIT_EXPLOSION, E_BLEND_MODE::ADDITIONALPHA);
	Draw::SetBlend(tex_HIT_EXPLOSION_BIG, E_BLEND_MODE::ADDITIONALPHA);
}
//進行
void CObjJudgeMoji::Action()
{
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{


		for (auto itr = m_list_ani_explosion[i].begin(); itr != m_list_ani_explosion[i].end();)
		{
			itr->ani.Action();
			itr->moji.ani.Action();
			if (itr->ani.GetEnd() && itr->moji.ani.GetEnd())
			{
				itr = m_list_ani_explosion[i].erase(itr);
			}
			else
			{
				itr++;
			}


		}
	}

}
//描画
void CObjJudgeMoji::Draw()
{
	for (int i = 0; i < ((UserData*)Save::GetData())->m_player_amount; i++)
	{

		CObjLane* lane = (CObjLane*)Objs::GetObj(OBJ_LANE);
		int judge_x = lane->GetJudgePosX(i);
		int judge_y = lane->GetJudgePosY(i);
		int explosion_x = judge_x + EXPLOSION_POS.x;
		int explosion_y = judge_y + EXPLOSION_POS.y;

		for (auto itr = m_list_ani_explosion[i].begin(); itr != m_list_ani_explosion[i].end(); itr++)
		{
			RECT_F rect_explosion =
			{ (int)itr->ani.GetValue("Explosion").pattern * RECT_EXPLOSION.m_width,(int)itr->effect_type * RECT_EXPLOSION.m_height,
			RECT_EXPLOSION.m_width, RECT_EXPLOSION.m_height };


			
				Draw::SetOpacity(tex_HIT_EXPLOSION, itr->ani.GetValue("Explosion").opacity);
			Draw::CenterDraw(tex_HIT_EXPLOSION, explosion_x, explosion_y, rect_explosion);

			if (itr->effect_type == E_EXPLOSION_TYPE::GREAT_BIG || itr->effect_type == E_EXPLOSION_TYPE::GOOD_BIG)
			{
				rect_explosion = RECT_EXPLOSION;
				rect_explosion.m_x = itr->effect_type == E_EXPLOSION_TYPE::GREAT_BIG ? 0.0f : 256.0f;

				Draw::SetOpacity(tex_HIT_EXPLOSION_BIG, itr->ani.GetValue("ExplosionBIG").opacity);
				Draw::SetScaleX(tex_HIT_EXPLOSION_BIG, itr->ani.GetValue("ExplosionBIG").scale_x);
				Draw::SetScaleY(tex_HIT_EXPLOSION_BIG, itr->ani.GetValue("ExplosionBIG").scale_x);
				Draw::CenterDraw(tex_HIT_EXPLOSION_BIG, explosion_x, explosion_y , rect_explosion);

				Draw::SetOpacity(tex_HIT_EXPLOSION_BIG, itr->ani.GetValue("ExplosionBIG2").opacity);
				Draw::SetScaleX(tex_HIT_EXPLOSION_BIG, itr->ani.GetValue("ExplosionBIG2").scale_x);
				Draw::SetScaleY(tex_HIT_EXPLOSION_BIG, itr->ani.GetValue("ExplosionBIG2").scale_x);
				Draw::CenterDraw(tex_HIT_EXPLOSION_BIG, explosion_x, explosion_y , rect_explosion);
			}

			//文字
			float x = judge_x + JUDGE_OFFSET.x;
			float y = judge_y + JUDGE_OFFSET.y;
			//		float opacity = itr->ct_fade_out.NowValue;



			if (((UserData*)Save::GetData())->m_judge_sec_showimg == false)
			{
				y += itr->moji.ani.GetValue().y;
				Draw::SetOpacity(tex_JUDGE, itr->moji.ani.GetValue().opacity);
				Draw::Draw(tex_JUDGE, x, y, RECT_JUDGE[itr->moji.judge]);
			}
			else
			{
				int offset_x = (5.0f * NUMBER_PADDING);
				m_num_judge[itr->moji.judge].Draw(abs(itr->moji.time), x + offset_x, y, NUMBER_PADDING);

				RECT_F rect_plus;
				if (itr->moji.time < 0.0f)
				{
					rect_plus = RECT_MINUS;
				}
				else if (itr->moji.time > 0.0f)
				{
					rect_plus = RECT_PLUS;
				}
				else
				{
					rect_plus = RECT_PLUS_MINUS;
				}
				rect_plus.m_y = (int)itr->moji.judge * rect_plus.m_height;
				Draw::Draw(tex_JUDGE, x, y, rect_plus);
			}
		}

		//for (auto itr = m_list_judge[i].begin(); itr != m_list_judge[i].end(); itr++)
		//{
		//
		//}
	}

}

/// <summary>
/// 
/// </summary>
/// <param name="judge"></param>
/// <param name="big">花火アニメ用に追加。</param>
void CObjJudgeMoji::Add(E_JUDGE judge,bool big,int player,float time)
{

	//JudgeMoji jm = m_ani_moji;
	//jm.judge = judge;
	//jm.ani.Start();
	//jm.time = time;

	//if (((UserData*)Save::GetData())->m_judge_sec_showimg == true)
	//{
	//	m_list_judge[player].clear();
	//}

	//m_list_judge[player].push_back(jm);

	stExplosion exp = big == true ? m_ani_exp_big : m_ani_exp;
	exp.moji = m_ani_moji;
	exp.moji.judge = judge;
	exp.moji.ani.Start();
	exp.moji.time = time;
	if (judge == JUST)
	{
		exp.effect_type = big == true ? E_EXPLOSION_TYPE::GREAT_BIG : E_EXPLOSION_TYPE::GREAT;

	}
	else if(judge == HIT)
	{
		exp.effect_type = big == true ? E_EXPLOSION_TYPE::GOOD_BIG : E_EXPLOSION_TYPE::GOOD;
	}
	else if (judge == MISS)
	{
		return;
	}

	exp.ani.Start();
	m_list_ani_explosion[player].push_back(exp);
}