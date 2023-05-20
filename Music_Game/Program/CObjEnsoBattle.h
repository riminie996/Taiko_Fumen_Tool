#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
#include "CObjBattleEndEffect.h"
using namespace GameL;

class CObjEnsoBattle : public CObj
{
public:
	CObjEnsoBattle(string dir);
	~CObjEnsoBattle() {}
	void Init();
	void Action();
	void Draw();
	int GetLife() { return ((float)m_life / (float)LIFE_INIT) * 50; }
	void SubLife(int val) { m_life -= val; if (m_life < 0)m_life = 0; }
	void EffectStart(int number);
	void EffectEnd();
	int GetResult();
	void BattleEnd();
	bool GetBattleEnd() { return m_end_flag; }
private:

	const int LIFE_INIT = 20;

	string m_str_boss_name;
	int m_life;





	struct ST_BATTLE_EFFECT
	{
		CAnime3 ani_in;
		CAnime3 ani_wait;
		CAnime3 ani_out;
		CLayout2 lyt;
		CTexture tex;
		bool effect_end ;

		void Start()
		{
			ani_in.Start();
			ani_wait.Start();
			ani_wait.End();
			ani_out.Start();
			ani_out.End();
			effect_end = false;
		}
		void End()
		{
			ani_out.Start();
			effect_end = true;
		}

		void Action()
		{
			ani_in.Action();
			ani_wait.ActionLoop();
			ani_out.Action();

			if (effect_end == true)
			{

			}
			else if (ani_in.GetStart() && ani_in.GetEnd())
			{
				if (!ani_wait.GetStart())
					ani_wait.Start();
			}
			else if (!ani_in.GetStart())
			{
				;
			}
		}
		void Draw()
		{
			if (!ani_in.GetStart() || (ani_out.GetStart() && ani_out.GetEnd()))return;

			for (int i = 0; i < lyt.GetData().size(); i++)
			{
				ST_LAYOUT lyt_temp = lyt.GetData(i);
				float x = 0; 
				float y = 0;

				//Yの切り取り開始位置をパターンで変更する
				RECT_N rect = lyt_temp.rectangle;
				tex.m_scale_x = lyt_temp.scale_x;
				tex.m_scale_y = lyt_temp.scale_y;

				if (!ani_in.GetEnd())
				{
					x = (float)lyt_temp.pos.x + ani_in.GetValue(i).x;
					y = (float)lyt_temp.pos.y + ani_in.GetValue(i).y;
					tex.m_opacity = ani_in.GetValue(i).opacity;
					tex.m_scale_x *= ani_in.GetValue(i).scale_x;
					tex.m_scale_y *= ani_in.GetValue(i).scale_y;
					rect.m_y = (int)ani_in.GetValue(i).pattern * rect.m_height;
				}
				else if (ani_out.GetStart())
				{
					x = (float)lyt_temp.pos.x + ani_out.GetValue(i).x;
					y = (float)lyt_temp.pos.y + ani_out.GetValue(i).y;
					tex.m_opacity = ani_out.GetValue(i).opacity;
					tex.m_scale_x *= ani_out.GetValue(i).scale_x;
					tex.m_scale_y *= ani_out.GetValue(i).scale_y;
					rect.m_y = (int)ani_out.GetValue(i).pattern * rect.m_height;
				}
				else
				{
					x = (float)lyt_temp.pos.x + ani_wait.GetValue(i).x;
					y = (float)lyt_temp.pos.y + ani_wait.GetValue(i).y;
					tex.m_opacity = ani_wait.GetValue(i).opacity;
					tex.m_scale_x *=  ani_wait.GetValue(i).scale_x;
					tex.m_scale_y *=  ani_wait.GetValue(i).scale_y;
					rect.m_y = (int)ani_wait.GetValue(i).pattern * rect.m_height;

				}


				tex.m_blend = lyt_temp.blend_mode;
				tex.m_flip_x = lyt_temp.flip_x;
				tex.m_flip_y = lyt_temp.flip_y;
				tex.m_rotation_z = lyt_temp.rotate_z;


				//ループ
				do
				{
					do
					{
						tex.Draw(x, y, rect, lyt_temp.reference_x, lyt_temp.reference_y);
						x += rect.m_width;

					} while (x < WINDOW_SIZE_W && lyt_temp.loop_x == true);

					y += rect.m_height;

				} while (y < WINDOW_SIZE_H && lyt_temp.loop_y == true);
			}
		}

		//void Load(string dir)
		//{
		//	ani_in.LoadData(dir + "In/" + to_string(i));
		//	ani_wait.LoadData(dir + "Wait/" + to_string(i));
		//	ani_out.LoadData(dir + "Out/" + to_string(i));
		//	lyt.LoadData(dir + to_string(i));
		//	tex.LoadTexture(dir +lyt.GetTexName());
		//}

	};

	vector<ST_BATTLE_EFFECT>m_vec_effect;

	bool m_end_flag;
};
