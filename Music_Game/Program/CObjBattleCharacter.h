#pragma once
#include "GameL\SceneObjManager.h"
#include "GameHead.h"
using namespace GameL;

class CObjBattleCharacter : public CObj
{
public:
	CObjBattleCharacter(string dir);
	~CObjBattleCharacter() {}
	void Init();
	void Action();
	void Draw();
	void Lose();

private:

	struct ST_BATTLE_CHARA
	{
		CAnime3 ani;
		CLayout2 lyt;
		CTexture tex;

		void Draw()
		{

			for (int i = 0; i < lyt.GetData().size(); i++)
			{
				ST_LAYOUT lyt_temp = lyt.GetData(i);
				float x = (float)lyt_temp.pos.x + ani.GetValue(i).x;
				float y = (float)lyt_temp.pos.y + ani.GetValue(i).y;

				//Yの切り取り開始位置をパターンで変更する
				RECT_N rect = lyt_temp.rectangle;

				tex.m_opacity = ani.GetValue(i).opacity;
				tex.m_scale_x = ani.GetValue(i).scale_x;
				tex.m_scale_y = ani.GetValue(i).scale_y;
				rect.m_y = (int)ani.GetValue(i).pattern * rect.m_height;



				tex.m_blend = lyt_temp.blend_mode;


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

		void Load(string dir)
		{
			ani.LoadData(dir);
			lyt.LoadData(dir);
			tex.LoadTexture(dir + ".png"/* + lyt.GetTexName()*/);
		}
	};

	bool m_end_flag;
	vector<ST_BATTLE_CHARA> m_vec_chara_pinch20;
	vector<ST_BATTLE_CHARA> m_vec_chara_pinch40;
	vector<ST_BATTLE_CHARA> m_vec_chara_wait;
	vector<ST_BATTLE_CHARA> m_vec_chara_lose;
};
