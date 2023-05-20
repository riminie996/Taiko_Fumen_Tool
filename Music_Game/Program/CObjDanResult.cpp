#include "CObjDanResult.h"
#include "GameL/Audio.h"
#include "GameL/UserData.h"
#include "GameHead.h"

//初期化
void CObjDanResult::Init()
{
	m_ct_result_dan.Start(0, DANRESULT_SONGPANEL_SLIDE_START_TIME + DANRESULT_SONGPANEL_WAIT_TIME, 1);

	m_result_voice_flag = true;

	m_ct_bgm_loop_delay.Start(0, MusicGame::DanResult::BGM_LOOP_START_DELAY, 1);
	Audio::Start(bgm_IN);
	m_bgm_flag = true;
	for (int i = 0; i < MusicGame::DanResult::FAILURE_TEXT_PATTERN_X; i++)
		m_ani_failure[i].LoadData("Animation/DanResult/FailureAnime");
	m_ani_clear.LoadData("Animation/DanResult/ClearedAnime");

	m_anime_start_flag = false;

	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);

	m_result_status = dan->GetResult();
}
//進行
void CObjDanResult::Action()
{
	CObjSystem* system = (CObjSystem*)Objs::GetObj(OBJ_MAIN);
	m_ct_result_dan.Action();
	m_ct_result_dan2.Action();
	m_ani_danplate.Action();
	m_ct_bgm_loop_delay.Action();
	for (int i = 0; i < MusicGame::DanResult::FAILURE_TEXT_PATTERN_X; i++)
		m_ani_failure[i].Action();
	m_ct_anime_delay.Action();
	m_ani_clear.Action();

	if (m_ct_bgm_loop_delay.GetEndValueReached() && m_bgm_flag == true)
	{
		m_bgm_flag = false;
		Audio::Start(bgm_MUSIC);
	}

	//結果発表ボイス
	if (m_result_voice_flag == true && m_ct_result_dan.NowValue >= MusicGame::DanResult::RESULT_IN_VOICE_DELAY)
	{
		m_result_voice_flag = false;
		Audio::Start(se_DANRESULT_IN);
	}
	//DanPlate
	if (m_ct_result_dan.NowValue >= MusicGame::DanResult::DANPLATE_ANIME_START_DELAY)
	{
		if (!m_ani_danplate.GetStart())
			m_ani_danplate.Start();
	}

	int delay = DANRESULT_SONGPANEL_SLIDE_START_TIME;
	
	//フェーズ1
	if (m_ct_result_dan.NowValue >= delay)
	{
		CObjDanResultSongPanel* song = (CObjDanResultSongPanel*)Objs::GetObj(OBJ_DANRESULT_SONG);
		song->AnimeStart();
	}

	delay = MusicGame::DanResult::NORMAGAUGE_START_DELAY;

	//ステートパネルを生成
	CObjDanResultPanel* statep = (CObjDanResultPanel*)Objs::GetObj(OBJ_DANRESULT_STATE);

	//フェーズ2
	if (m_ct_result_dan2.NowValue >= delay)
	{
		statep->AnimeStart();
	}

	if (m_ct_result_dan.GetEndValueReached() && statep == nullptr)
	{
		CObjDanResultPanel* state = new CObjDanResultPanel();
		Objs::InsertObj(state, OBJ_DANRESULT_STATE, PRIO_DANRESULT_PANEL);
		m_ct_result_dan2.Start(0, MusicGame::DanResult::DANRESULT_STATEPANEL_ACT_TIME, 1);
	}

	//スキップ
	if (m_ct_result_dan.NowValue > DANRESULT_SONGPANEL_SLIDE_START_TIME &&
		(system->GetInput(LEFT_DON,0)) || system->GetInput(RIGHT_DON,0))
	{
		m_ct_result_dan.NowValue = m_ct_result_dan.EndValue;
	}

	//アニメーション開始後
	if (m_anime_start_flag == true)
	{
		for (int i = 0; i < MusicGame::DanResult::FAILURE_TEXT_PATTERN_X; i++)
		{
			if (!m_ani_failure[i].GetStart() && m_ct_anime_delay.NowValue >= i * MusicGame::DanResult::FAILURE_TEXT_DELAY )
			{
				m_ani_failure[i].Start();
			}
		}
	}

	CObjExit* lexit = (CObjExit*)Objs::GetObj(OBJ_EXIT);
	if (lexit == nullptr && m_ct_result_dan2.GetProgress() && m_ct_result_dan2.GetEndValueReached())
	{
		CObjExit* exit = new CObjExit(MusicGame::Exit::E_EXIT_TO::ENTRY);
		Objs::InsertObj(exit, OBJ_EXIT, PRIO_EXIT);
	}
}
//描画
void CObjDanResult::Draw()
{
	//Dan_Plate
	float x = MusicGame::DanResult::DAN_PLATE_POS.x;
	float y = MusicGame::DanResult::DAN_PLATE_POS.y + m_ani_danplate.GetValue().y;
	Draw::CenterDraw(tex_DAN_PLATE, x,y);

	if (m_result_status == RESULT_FAILURE)
	{
		for (int i = 0; i < MusicGame::DanResult::FAILURE_TEXT_PATTERN_Y; i++)
		{
			for (int j = 0; j < MusicGame::DanResult::FAILURE_TEXT_PATTERN_X; j++)
			{
				if (m_ani_failure[j].GetStart())
				{
					float x = MusicGame::DanResult::FAILURE_TEXT_POS.x + j * MusicGame::DanResult::FAILURE_TEXT_OFFSET_X;
					float y = MusicGame::DanResult::FAILURE_TEXT_POS.y + m_ani_failure[j].GetValue().y;
					RECT_F rect = { MusicGame::DanResult::FAILURE_TEXT_WIDTH * j,MusicGame::DanResult::FAILURE_TEXT_HEIGHT * i,MusicGame::DanResult::FAILURE_TEXT_WIDTH ,MusicGame::DanResult::FAILURE_TEXT_HEIGHT };
					Draw::SetOpacity(tex_DANRESULT_FAILED, m_ani_failure[j].GetValue().opacity);
					Draw::Draw(tex_DANRESULT_FAILED, x, y, rect);
				}
			}
		}
	}
	else
	{
		RECT_F rect_back;
		RECT_F rect_clear;

		if (m_result_status == RESULT_CLEARED)
			rect_clear = MusicGame::DanResult::RECT_CLEARED;
		else
			rect_clear = MusicGame::DanResult::RECT_GOLDCLEARED;

		if (m_score.judge[MISS] == 0 &&
			m_score.judge[HIT] == 0)
		{
			rect_back = MusicGame::DanResult::RECT_BACK_RAINBOW;
		}
		else if (m_score.judge[MISS] == 0)
		{
			rect_back = MusicGame::DanResult::RECT_BACK_GOLD;
		}
		else
		{
			rect_back = MusicGame::DanResult::RECT_BACK_SILVER;
		}

		float x = MusicGame::DanResult::CLEAR_POS.x;
		float y = MusicGame::DanResult::CLEAR_POS.y;

		if (m_ani_clear.GetStart())
		{
			Draw::SetScaleX(tex_DANRESULT_CLEAR, m_ani_clear.GetValue().scale_x);
			Draw::SetScaleY(tex_DANRESULT_CLEAR, m_ani_clear.GetValue().scale_x);
			Draw::SetOpacity(tex_DANRESULT_CLEAR, m_ani_clear.GetValue().opacity);
			Draw::CenterDraw(tex_DANRESULT_CLEAR, x, y, rect_back);
			Draw::CenterDraw(tex_DANRESULT_CLEAR, x, y, rect_clear);
		}
	}
}

void CObjDanResult::AnimeStart()
{
	if (m_anime_start_flag == true)return;
	m_anime_start_flag = true;

	switch(m_result_status)
	{
	case RESULT_FAILURE:
		m_ct_anime_delay.Start(0, MusicGame::DanResult::FAILURE_TEXT_DELAY * MusicGame::DanResult::FAILURE_TEXT_PATTERN_X, 1);
		Audio::Start(se_DANRESULT_FAILURE);
		break;
	case RESULT_CLEARED:
		m_ani_clear.Start();
		Audio::Start(se_DANRESULT_CLEAR);
		break;
	case RESULT_GOLDCLEARED:
		m_ani_clear.Start();
		Audio::Start(se_DANRESULT_GOLDCLEAR);
		break;
	}

}