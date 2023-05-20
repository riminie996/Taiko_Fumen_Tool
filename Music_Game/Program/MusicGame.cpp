#include "MusicGame.h"
#include "GameL\SceneObjManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
//LoadDirectory
#include <filesystem>
//\\を/に置き換え
#include <regex>

vector<CTexture> MusicGame::g_tex_normal;
vector<CTexture> MusicGame::g_tex_10combo;
vector<CTexture> MusicGame::g_tex_10combo_max;
vector<CTexture> MusicGame::g_tex_clear;
vector<CTexture> MusicGame::g_tex_clear_in;
vector<CTexture> MusicGame::g_tex_gogostart;
vector<CTexture> MusicGame::g_tex_gogo;
vector<CTexture> MusicGame::g_tex_soulin;
vector<CTexture> MusicGame::g_tex_balloon_broke;
vector<CTexture> MusicGame::g_tex_balloon_miss;
vector<CTexture> MusicGame::g_tex_balloon_break;
string MusicGame::g_now_select_songtitle;
vector<MusicGame::SongSelect::ST_BAR_INFO> MusicGame::SongSelect::g_vec_all_fumen_bar;
vector<MusicGame::SongSelect::ST_BAR_INFO> MusicGame::SongSelect::g_vec_folder_bar;
vector<vector<int>> MusicGame::SongSelect::g_vec_folder_fumen;
vector<CTexture> MusicGame::SongSelect::g_tex_chara_start;
vector<CTexture> MusicGame::SongSelect::g_tex_chara_select;
vector<CTexture> MusicGame::SongSelect::g_tex_chara_loop;
int MusicGame::SongSelect::g_close_id;
CTexture MusicGame::SongSelect::g_tex_box_overlay;
CTexture MusicGame::g_tex_title;
CTexture MusicGame::g_tex_controll_guide;
CTexture MusicGame::g_tex_lane;
CTexture MusicGame::g_tex_lane_left;
CTexture MusicGame::g_tex_taiko;
CTexture MusicGame::g_tex_score_bg;
CTexture MusicGame::g_tex_gauge_base;
CTexture MusicGame::g_tex_gauge_line;
CTexture MusicGame::g_tex_gauge_rainbow;
CTexture MusicGame::g_tex_gauge_base_dan;
CTexture MusicGame::g_tex_gauge_line_dan;
CTexture MusicGame::g_tex_gauge_rainbow_dan;
CTexture MusicGame::g_tex_soul;
CTexture MusicGame::g_tex_soul_fire;
CTexture MusicGame::g_tex_balloon;
CTexture MusicGame::g_tex_balloon_fukidashi;
CTexture MusicGame::g_tex_balloon_number;
CTexture MusicGame::g_tex_kusudama;
CTexture MusicGame::g_tex_concentration_line;
CTexture MusicGame::g_tex_kusudama_renda;
int MusicGame::g_confirm_song_id;
E_GAME_MODE MusicGame::g_mode;
MusicGame::ST_STATUS_PANEL MusicGame::g_player_status;

int MusicGame::TextureAmountCount(string path,string find_str)
{
	int count = 0;
	using std::filesystem::recursive_directory_iterator;
	for (const auto& file : recursive_directory_iterator {path,
		std::filesystem::directory_options::skip_permission_denied})
	{
		if (file.path().string().find(find_str) != -1)
		{
			count++;
		}
	}
	return count;
}

void MusicGame::CommonTextureLoader()
{

	int count = 0;

	if (((UserData*)Save::GetData())->m_better_performance[MusicGame::E_BETTER_PERFORMANCE::bp_CHARA] == true)
	{
		//キャラクターノーマル
		count = TextureAmountCount("Graphics/Character/Normal/", ".png");
		g_tex_normal.resize(count);
		for (int i = 0; i < g_tex_normal.size(); i++)
		{
			g_tex_normal[i].LoadTexture("Graphics/Character/Normal/" + to_string(i) + ".png");
		}

		//キャラクター10コンボ
		count = TextureAmountCount("Graphics/Character/10combo/", ".png");
		g_tex_10combo.resize(count);
		for (int i = 0; i < g_tex_10combo.size(); i++)
		{
			g_tex_10combo[i].LoadTexture("Graphics/Character/10combo/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/10combo_Max/", ".png");
		g_tex_10combo_max.resize(count);
		for (int i = 0; i < g_tex_10combo_max.size(); i++)
		{
			g_tex_10combo_max[i].LoadTexture("Graphics/Character/10combo_Max/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/Clear/", ".png");
		g_tex_clear.resize(count);
		for (int i = 0; i < g_tex_clear.size(); i++)
		{
			g_tex_clear[i].LoadTexture("Graphics/Character/Clear/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/Clearin/", ".png");
		g_tex_clear_in.resize(count);
		for (int i = 0; i < g_tex_clear_in.size(); i++)
		{
			g_tex_clear_in[i].LoadTexture("Graphics/Character/Clearin/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/GoGoStart/", ".png");
		g_tex_gogostart.resize(count);
		for (int i = 0; i < g_tex_gogostart.size(); i++)
		{
			g_tex_gogostart[i].LoadTexture("Graphics/Character/GoGoStart/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/GoGo/", ".png");
		g_tex_gogo.resize(count);
		for (int i = 0; i < g_tex_gogo.size(); i++)
		{
			g_tex_gogo[i].LoadTexture("Graphics/Character/GoGo/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/Soulin/", ".png");
		g_tex_soulin.resize(count);
		for (int i = 0; i < g_tex_soulin.size(); i++)
		{
			g_tex_soulin[i].LoadTexture("Graphics/Character/Soulin/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/Balloon_Broke/", ".png");
		g_tex_balloon_broke.resize(count);
		for (int i = 0; i < g_tex_balloon_broke.size(); i++)
		{
			g_tex_balloon_broke[i].LoadTexture("Graphics/Character/Balloon_Broke/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/Balloon_Miss/", ".png");
		g_tex_balloon_miss.resize(count);
		for (int i = 0; i < g_tex_balloon_miss.size(); i++)
		{
			g_tex_balloon_miss[i].LoadTexture("Graphics/Character/Balloon_Miss/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/Balloon_Breaking/", ".png");
		g_tex_balloon_break.resize(count);
		for (int i = 0; i < g_tex_balloon_break.size(); i++)
		{
			g_tex_balloon_break[i].LoadTexture("Graphics/Character/Balloon_Breaking/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/SongSelect/Start/", ".png");
		SongSelect::g_tex_chara_start.resize(count);
		for (int i = 0; i < SongSelect::g_tex_chara_start.size(); i++)
		{
			SongSelect::g_tex_chara_start[i].LoadTexture("Graphics/Character/SongSelect/Start/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/SongSelect/Select/", ".png");
		SongSelect::g_tex_chara_select.resize(count);
		for (int i = 0; i < SongSelect::g_tex_chara_select.size(); i++)
		{
			SongSelect::g_tex_chara_select[i].LoadTexture("Graphics/Character/SongSelect/Select/" + to_string(i) + ".png");
		}

		count = TextureAmountCount("Graphics/Character/SongSelect/Loop/", ".png");
		SongSelect::g_tex_chara_loop.resize(count);
		for (int i = 0; i < SongSelect::g_tex_chara_loop.size(); i++)
		{
			SongSelect::g_tex_chara_loop[i].LoadTexture("Graphics/Character/SongSelect/Loop/" + to_string(i) + ".png");
		}
	}

	SongSelect::g_tex_box_overlay.LoadTexture("Graphics/2_SongSelect/Bar_Box/Bar_Box_OverLay.png");
	g_tex_title.LoadTexture("Graphics/0_Title/TitleSozai.png");
	g_tex_controll_guide.LoadTexture("Graphics/ControllGuide.png");
	g_tex_lane.LoadTexture("Graphics/3_Enso/12_Lane/Lane.png");
	g_tex_taiko.LoadTexture("Graphics/3_Enso/6_Taiko/Taiko.png");
	g_tex_lane_left.LoadTexture("Graphics/3_Enso/12_Lane/Lane_Left.png");
	g_tex_score_bg.LoadTexture("Graphics/3_Enso/6_Taiko/Score_bg.png");
	g_tex_gauge_base.LoadTexture("Graphics/3_Enso/7_Gauge/1P_Base.png");
	g_tex_gauge_line.LoadTexture("Graphics/3_Enso/7_Gauge/1P_Line.png");
	g_tex_gauge_rainbow.LoadTexture("Graphics/3_Enso/7_Gauge/1P_Rainbow.png");
	g_tex_gauge_base_dan.LoadTexture("Graphics/3_Enso/7_Gauge/1P_Base_Dan.png");
	g_tex_gauge_line_dan.LoadTexture("Graphics/3_Enso/7_Gauge/1P_Line_Dan.png");
	g_tex_gauge_rainbow_dan.LoadTexture("Graphics/3_Enso/7_Gauge/Rainbow_Dan.png");
	g_tex_soul.LoadTexture("Graphics/3_Enso/7_Gauge/Soul.png");
	g_tex_soul_fire.LoadTexture("Graphics/3_Enso/7_Gauge/Fire.png");
	g_tex_balloon.LoadTexture("Graphics/3_Enso/11_Balloon/Balloon/Balloon.png");
	g_tex_balloon_fukidashi.LoadTexture("Graphics/3_Enso/11_Balloon/Balloon/Fukidashi.png");
	g_tex_balloon_number.LoadTexture("Graphics/3_Enso/11_Balloon/Balloon/Number.png");
	g_tex_kusudama.LoadTexture("Graphics/3_Enso/11_Balloon/Kusudama/kusudama.png");
	g_tex_concentration_line.LoadTexture("Graphics/3_Enso/11_Balloon/Kusudama/ConcentrationLine.png");
	g_tex_kusudama_renda.LoadTexture("Graphics/3_Enso/11_Balloon/Kusudama/text.png");
	//SongSelect

	for (int i = 0; i <= GENRE_Count; i++)
	{
		wchar_t wcr[64];
		swprintf_s(wcr, L"Graphics/2_SongSelect/Bar_Box/Bar_Box_%d.png", i);
		Draw::LoadImageW(wcr, tex_BOX_NONE + i, TEX_SIZE_64);

		swprintf_s(wcr, L"Graphics/2_SongSelect/Difficulty_Box/Difficulty_Back_%d.png", i);
		Draw::LoadImageW(wcr, tex_DIFFCULTY_BOX_NONE + i, TEX_SIZE_64);

		swprintf_s(wcr, L"Graphics/2_SongSelect/Genre_Background/GenreBackground_%d.png", i);
		Draw::LoadImageW(wcr, tex_BACKGROUND_NONE + i, TEX_SIZE_64);

	}

	Draw::LoadImageW(L"Graphics/2_SongSelect/Bar_Box/Bar_Box_Close.png", tex_BOX_CLOSE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/Bar_Box/Bar_Box_Close_Text.png", tex_BOX_CLOSE_TEXT, TEX_SIZE_64);
	//	Draw::LoadImageW(L"Graphics/2_SongSelect/Bar_Box/Bar_Box_OverLay.png", tex_BOX_OVERLAY, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/Diffculty.png", tex_BOX_DIFFCULTY, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/Diffculty_Number.png", tex_BOX_DIFFCULTY_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Difficulty_Bar.png", tex_DIFFCULTY_BAR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Small_Icon.png", tex_DIFFCULTY_ICON, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Cursor_1P.png", tex_DIFFCULTY_CURSOR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/CourseSymbol.png", tex_DIFFCULTY_COURSESYMBOL, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/4_SongLoading/Fade.png", tex_LOADING_FADE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/4_SongLoading/Bg.png", tex_LOADING_BG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/4_SongLoading/Bg_wait.png", tex_LOADING_WAIT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/4_SongLoading/Plate.png", tex_LOADING_PLATE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/4_SongLoading/Chara.png", tex_LOADING_CHARA, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/Cursor_yellow.png", tex_SONGSELECT_CURSOR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Cursor_Yellow.png", tex_DIFFCULTY_CURSOR2, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Oni_Appear.png", tex_DIFFCULTY_ONI_APPEAR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Number.png", tex_DIFFCULTY_NUM, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Star.png", tex_DIFFCULTY_STAR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/DiffcultySelect/Text.png", tex_DIFFCULTY_TEXT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/2_SongSelect/Branch_Text.png", tex_DIFFCULTY_BRANCH, TEX_SIZE_64);

	//Enso
	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Combo.png", tex_NUMBER, TEX_SIZE_64);

	Draw::LoadImageW(L"Graphics/3_Enso/12_Lane/LaneFlush.png", tex_LANE_FLUSH, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/12_Lane/Background_Gogo.png", tex_LANE_GOGO, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/12_Lane/Background_Branch.png", tex_BRANCH_LANE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/12_Lane/Text.png", tex_BRANCH_TEXT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/Bar.png", tex_LINE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/Bar_Branch.png", tex_LINE_YELLOW, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/Notes.png", tex_NOTES, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Combo.png", tex_COMBO, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Combo_Silver.png", tex_COMBO_SILVER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Combo_Gold.png", tex_COMBO_GOLD, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Combo_Text.png", tex_COMBO_TEXT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Score.png", tex_SCORE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Score_1P.png", tex_SCORE_1P, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/Soul.png", tex_SOUL, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/GaugeUpdate.png", tex_GAUGE_UPDATE, TEX_SIZE_64);

	Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/Fire.png", tex_SOUL_FIRE, TEX_SIZE_64);

	Draw::LoadImageW(L"Graphics/3_Enso/10_Effects/Hit/Hit.png", tex_HIT_EFFECT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/10_Effects/Hit/Explosion.png", tex_HIT_EXPLOSION, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/10_Effects/Hit/Explosion_Big.png", tex_HIT_EXPLOSION_BIG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/10_Effects/Fire.png", tex_FIRE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/11_Balloon/Balloon/fukidashi.png", tex_BALLOON_FUKIDASHI, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/11_Balloon/Number_Roll.png", tex_ROLL_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/11_Balloon/balloon/number.png", tex_BALLOON_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/11_Balloon/kusudama/number.png", tex_KUSUDAMA_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/11_Balloon/Roll.png", tex_ROLL, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/ScoreRank.png", tex_SCORE_RANK, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/Diffculty.png", tex_DIFFCULTY, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Explosion.png", tex_GAUGE_EXPLOSION, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/10_Effects/NotesEffects.png", tex_NOTES_EFFECT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/11_Balloon/Combo_1P.png", tex_COMBOBALLOON, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/11_Balloon/Number_Combo.png", tex_COMBOBALLOON_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/11_Balloon/Balloon/Balloon.png", tex_BALLOON_FRAME, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Combo_Effect.png", tex_COMBO_EFFECT, TEX_SIZE_64);

	Draw::LoadImageW(L"Graphics/3_Enso/Genre.png", tex_GENRE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/SongNumber.png", tex_SONG_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/10_Effects/Hit/Firework.png", tex_NOTES_FIREWORK, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/10_Effects/Spark.png", tex_SPARK, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/0_Chara/Effect.png", tex_CHARACTER_EFFECT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/9_End/Paper_In.png", tex_PAPER_IN, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/9_End/Paper_Loop.png", tex_PAPER_LOOP, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/SENotes.png", tex_SE_NOTES, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/Score_Effect.png", tex_SCORE_EFFECT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/6_Taiko/BestScore.png", tex_ENSO_BESTSCORE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/Judge_Panel.png", tex_JUDGE_PANEL, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/Judge_Number.png", tex_JUDGE_PANEL_NUMBER, TEX_SIZE_64);

	//Dan
	Draw::LoadImageW(L"Graphics/6_DanEnso/Background.png", tex_DAN_BACKGROUND, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Base.png", tex_DAN_GAUGE_BASE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Gauge.png", tex_DAN_GAUGE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Gauge_Triple.png", tex_DAN_GAUGE_TRIPLE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Number.png", tex_DAN_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/ExamType.png", tex_DAN_EXAM_TYPE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/ExamRange.png", tex_DAN_EXAM_RANGE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Small_Number.png", tex_DAN_EXAM_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Gauge_Assignment.png", tex_DAN_GAUGE_NORMA, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Failed.png", tex_DAN_FAILED, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Small_Number.png", tex_DAN_SMALL_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Gauge_Assignment.png", tex_DAN_GAUGE_ASSIGNMENT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Screen.png", tex_DAN_SCREEN, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Gauge_Mini.png", tex_DAN_GAUGE_MINI, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/MiniNumber.png", tex_DAN_NUMBER_MINI, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/SmallBase.png", tex_DAN_GAUGE_BASE_MINI, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/6_DanEnso/Gauge_Rainbow.png", tex_DAN_RAINBOW, TEX_SIZE_64);

	//Result
	Draw::LoadImageW(L"Graphics/4_Result/Background.png", tex_RESULT_BG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/Background_Mountain_Red.png", tex_RESULT_YAMA, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/Background_Clear.png", tex_RESULT_CLEAR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/Background_Mountain_Clear.png", tex_RESULT_CLEAR_YAMA, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/Header.png", tex_RESULT_HEADER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/Panel.png", tex_RESULT_PANEL, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/Result_Diff.png", tex_RESULT_PANEL_DIFFCULTY, TEX_SIZE_64);


	Draw::LoadImageW(L"Graphics/4_Result/Number.png", tex_RESULT_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/CrownEffect.png", tex_RESULT_CROWN, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/Score_Number.png", tex_RESULT_SCORE_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/ScoreRankEffect.png", tex_RESULT_RANK, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/Soul_Text.png", tex_RESULT_SOUL, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/Result_Soul_Fire.png", tex_RESULT_FIRE, TEX_SIZE_64);

	//DanResult
	Draw::LoadImageW(L"Graphics/7_DanResult/Background.png", tex_DANRESULT_BG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/Gauge_Base.png", tex_DANRESULT_GAUGE_BG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/Dan_Base_Single.png", tex_DANRESULT_GAUGE_BASE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/Dan_Base_Triple.png", tex_DANRESULT_GAUGE_BASE_TRIPLE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/SongPanel.png", tex_DANRESULT_SONGPANEL, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/StatePanel.png", tex_DANRESULT_STATEPANEL, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/SongPanel_Background.png", tex_DANRESULT_SONGPANEL_BG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/StatePanel_Background.png", tex_DANRESULT_STATEPANEL_BG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/ResultNumber.png", tex_DANRESULT_SONGPANEL_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/ResultNumber.png", tex_DANRESULT_STATEPANEL_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/Result_Dan_Failured.png", tex_DANRESULT_FAILED, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/Result_Dan.png", tex_DANRESULT_CLEAR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/Rank_Effect.png", tex_DANRESULT_EFFECT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/NormaGauge_Back.png", tex_DANRESULT_NORMAGAUGE_BG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/Gauge_Triple.png", tex_DANRESULT_GAUGE_TRIPLE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Base_Dan.png", tex_DANRESULT_NORMAGAUGE_BASE, TEX_SIZE_64);
	//	Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Base_Dan_Yellow.png", tex_DAN_1P_GAUGE_BASE_YELLOW, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Dan.png", tex_DANRESULT_NORMAGAUGE, TEX_SIZE_64);
	//	Draw::LoadImageW(L"Graphics/3_Enso/7_Gauge/1P_Dan_Yellow.png", tex_DAN_1P_GAUGE_YELLOW, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/4_Result/Score_Number.png", tex_DANRESULT_SCORE_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/Percent.png", tex_DANRESULT_PERCENT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/Exam_Number.png", tex_DANRESULT_EXAMNUMBER_TRIPLE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/Exam_Range.png", tex_DANRESULT_EXAMRANGE_TRIPLE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/7_DanResult/UnReached.png", tex_DANRESULT_NOTREACH, TEX_SIZE_64);

	//DanSelect
	Draw::LoadImageW(L"Graphics/5_DanSelect/Back.png", tex_DANSELECT_BG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/In.png", tex_DANSELECT_FUSUMA, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Text.png", tex_DANSELECT_TEXT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Bar.png", tex_DANSELECT_BAR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Info/Panel.png", tex_DANSELECT_INFO_BACK, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Info/Info.png", tex_DANSELECT_INFO_INFO, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Info/Song.png", tex_DANSELECT_INFO_SONG, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Info/Gauge_Info.png", tex_DANSELECT_INFO_GAUGE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Info/Gauge_Number.png", tex_DANSELECT_INFO_GAUGE_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Info/Gauge_Range.png", tex_DANSELECT_INFO_GAUGE_RANGE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Info/Number.png", tex_DANSELECT_INFO_EXAM_NUMBER, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Info/Percent.png", tex_DANSELECT_INFO_PERCENT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Info/Range.png", tex_DANSELECT_INFO_EXAM_RANGE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Info/Type.png", tex_DANSELECT_INFO_EXAM_TYPE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Confirm/Window.png", tex_DANSELECT_CONFIRM_WINDOW, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Confirm/Icon.png", tex_DANSELECT_CONFIRM_ICON, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/5_DanSelect/Confirm/Cursor_Effect.png", tex_DANSELECT_CONFIRM_CURSOR, TEX_SIZE_64);

	//Entry
	Draw::LoadImageW(L"Graphics/1_Entry/Background.png", tex_ENTRY_BACKGROUND, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/1_Entry/Background_Boke.png", tex_ENTRY_BG_BOKE, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/1_Entry/Background_Boke_B.png", tex_ENTRY_BG_BOKE_B, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/1_Entry/Entry.png", tex_ENTRY_ENTRY, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/1_Entry/Fireworks.png", tex_ENTRY_FIREWORKS, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/1_Entry/Light.png", tex_ENTRY_LIGHT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/1_Entry/Enso/enso_bar.png", tex_ENTRY_ENSO_BAR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/1_Entry/Enso/enso_chara.png", tex_ENTRY_ENSO_CHARA, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/1_Entry/Enso/enso_moji.png", tex_ENTRY_ENSO_TEXT, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/1_Entry/Enso/cursor.png", tex_ENTRY_ENSO_CURSOR, TEX_SIZE_64);
	Draw::LoadImageW(L"Graphics/1_Entry/Enso/Overlay.png", tex_ENTRY_MODESELECT_OVERLAY, TEX_SIZE_64);


	Draw::LoadImageW(L"Graphics/9_Heya/Background.png", tex_HEYA_BG, TEX_SIZE_64);
}	
E_DIFFCULTY MusicGame::StrToDiffculty(string str)
{

	//こことE_DIFFCULTY定数の順番はそろえる。
	string diffcult[DIFF_Count][4] =
	{
		{
			"EASY",
			"Easy",
			"easy",
			"0",
		},
		{
			"NORMAL",
			"Normal",
			"normal",
			"1",
		},
		{
			"Hard",
			"HARD",
			"hard",
			"2",
		},
		{
			"Oni",
			"ONI",
			"oni",
			"3",
		},
		{
			"Edit",
			"EDIT",
			"edit",
			"4",
		},
		{
		},
		{
			"Dan",
			"DAN",
			"dan",
			"6",
		},
	};
	for (int i = 0; i < ARRAY_LENGTH(diffcult); i++)
	{
		for (int j = 0; j < ARRAY_LENGTH(diffcult[i]); j++)
		{
			if (diffcult[i][j] == str)
			{
				return (E_DIFFCULTY)i;//EASY,NORMAL,HARD
			}
		}
	}
	return DIFF_EASY;
}

E_GENRE MusicGame::StrToGenre(string str)
{
	//	POPS,
	//	ANIME,
	//	VOCALOID,
	//	GAMEMUSIC,
	//	VARIETY,
	//	CLASSIC,
	//	NAMCOORIGINAL,
	//	KIDS,
#define STRING_EQUAL(str2) if(str == str2)

	STRING_EQUAL("ポップス")			return GENRE_POPS;
	STRING_EQUAL("J-POP")				return GENRE_POPS;
	STRING_EQUAL("アニメ")				return GENRE_ANIME;
	STRING_EQUAL("VOCALOID")			return GENRE_VOCALOID;
	STRING_EQUAL("ボーカロイド")		return GENRE_VOCALOID;
	STRING_EQUAL("ゲームミュージック")	return GENRE_GAMEMUSIC;
	STRING_EQUAL("バラエティ")			return GENRE_VARIETY;
	STRING_EQUAL("クラシック")			return GENRE_CLASSIC;
	STRING_EQUAL("ナムコオリジナル")	return GENRE_NAMCOORIGINAL;
	STRING_EQUAL("キッズ")				return GENRE_KIDS;
	STRING_EQUAL("どうよう")			return GENRE_KIDS;
	STRING_EQUAL("段位道場")			return GENRE_DAN;

	return GENRE_NONE;

}

std::wstring MusicGame::StringToWString(std::string oString)
{
	// SJIS → wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str()
		, -1, (wchar_t*)NULL, 0);

	// バッファの取得
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	// SJIS → wstring
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2
		, iBufferSize);

	// stringの生成
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	// バッファの破棄
	delete[] cpUCS2;

	// 変換結果を返す
	return(oRet);
}

void MusicGame::SongSelect::LoadDirectory(list<string>& fumen_path_list, list<string>& folder_path_list, string path)
{

	using std::filesystem::recursive_directory_iterator;



	for (const auto& file : recursive_directory_iterator(path))
	{
		//tjaファイルのみリスインする
		if (file.path().string().find(".tjascore") != -1)
		{
			//何もしない
		}
		else if (file.path().string().find(".tja") != -1 ||
			file.path().string().find(".tjs") != -1)
		{
			fumen_path_list.push_back(file.path().string());
		}
		else if (file.path().string().find("box.def") != -1)
		{
			folder_path_list.push_back(file.path().string());
		}

	}


	//譜面バーIDカウント用
	int count = 0;

	//フォルダバーを作成
	for (auto itr = folder_path_list.begin(); itr != folder_path_list.end(); itr++)
	{

		ST_BAR_INFO bar;

		bar.folder_path = itr->erase(itr->find("box.def"));
		bar.bar_type = BAR_FOLDER;
		bar.id = count;

		string str_folder_command;
		list<string> str_split_folder_command;

		//ファイルを開く
		ifstream ifs(bar.folder_path + "box.def");
		if (!ifs)
		{
			//	MessageBox(NULL, TEXT("やりなおしてください"),
			//		TEXT("譜面ファイル読み込み失敗"), MB_OK);
			ifs.close();
			continue;
		}

		while (getline(ifs, str_folder_command))
		{
			if (str_folder_command.find("#GENRE:") != -1)
			{
				str_folder_command = str_folder_command.substr(7);
				bar.genre = MusicGame::StrToGenre(str_folder_command);
			}
			else if (str_folder_command.find("#TITLE:") != -1)
			{
				bar.title = str_folder_command.substr(7);
			}
		}

		//バー情報を登録
		g_vec_folder_bar.push_back(bar);
		g_vec_all_fumen_bar.push_back(bar);
		count++;
	}

	//最後に未分類フォルダを作成。
	ST_BAR_INFO folder;
	folder.genre = GENRE_NONE;
	folder.title = "未分類";
	folder.bar_type = BAR_FOLDER;
	int folder_none_id = count;
	folder.id = folder_none_id;
	g_vec_folder_bar.push_back(folder);
	g_vec_all_fumen_bar.push_back(folder);
	count++;

	folder.genre = GENRE_HISTORY;
	folder.title = "最近あそんだ曲";
	folder.bar_type = BAR_FOLDER;
	folder.id = count;
	g_vec_folder_bar.push_back(folder);
	g_vec_all_fumen_bar.push_back(folder);
	count++;

	folder.genre = GENRE_FAVOLITE;
	folder.title = "お気に入り";
	folder.bar_type = BAR_FOLDER;
	folder.id = count;
	g_vec_folder_bar.push_back(folder);
	g_vec_all_fumen_bar.push_back(folder);
	count++;

	//譜面バーを作成。
	for (auto itr = fumen_path_list.begin(); itr != fumen_path_list.end(); itr++)
	{
		//tjsの場合バーリストには追加しない
		if (itr->find(".tja") == -1)continue;

		ST_FUMEN_DATA fumen;

		string str_fumen_command;
		list<string> str_split_fumen_command;

		string fumen_path = *itr;

		//ファイルを開く
		ifstream ifs(fumen_path);
		if (!ifs)
		{
			wstring wstr = MusicGame::StringToWString(fumen_path);
			MessageBox(NULL, (wstr.c_str()),
				TEXT("譜面ファイル読み込み失敗"), MB_OK);
			ifs.close();
			continue;
		}


		fumen.fumen_path = fumen_path;



		while (getline(ifs, str_fumen_command))
		{
			str_split_fumen_command.push_back(str_fumen_command);
		}

		//ヘッダの読み込み。
		for (auto itr = str_split_fumen_command.begin(); itr != str_split_fumen_command.end(); itr++)
		{
			fumen.FumenHeaderLoad(*itr);
		}

		//バーを作成
		ST_BAR_INFO bar = FumenBarCreate(fumen);

		bar.id = count;

		//バー情報を登録
		g_vec_all_fumen_bar.push_back(bar);
		count++;
	}
}
//フォルダIDを指定してください。
MusicGame::SongSelect::ST_BAR_INFO MusicGame::SongSelect::FumenBarCreate(ST_FUMEN_DATA fumen)
{
	MusicGame::SongSelect::ST_BAR_INFO bar;
	bar.bar_type = MusicGame::SongSelect::BAR_FUMEN;
	bar.folder_path = fumen.fumen_path;
	bar.genre = fumen.genre;
	bar.id = 0;
	for (int k = 0; k < DIFF_Count; k++)
	{
		bar.level[k] = fumen.level[k];
		bar.branch[k] = fumen.is_branch[k];
	}
	bar.subtitle = fumen.sub_title;
	bar.title = fumen.title;
	bar.wave_file = fumen.wave_file;
	bar.demo_start = fumen.demo_start;
	bar.show_score.crown_color = E_CROWN::CROWN_NONE;
	bar.show_score.crown_diff = DIFF_EASY;
	bar.show_score.rank_color = E_SCORE_RANK::RANK_NONE;
	bar.show_score.rank_diff = DIFF_EASY;

	for (int i = DIFF_EASY; i < DIFF_Count; i++)
	{
		bar.bestscore[i] = 0;
		bar.crown[i] = E_CROWN::CROWN_NONE;
		bar.rank[i] = E_SCORE_RANK::RANK_NONE;
	}

	ST_SCORE_DATA score[DIFF_Count];
	MusicGame::ScoreDataImport(score, fumen.fumen_path + SCOREFILE_STR);

	for (int i = DIFF_EASY; i < DIFF_Count; i++)
	{
		bar.bestscore[i] = score[i].score;
		bar.crown[i] = score[i].crown;
		bar.rank[i] = score[i].score_rank;
	}

	for (int i = DIFF_EASY; i < DIFF_Count; i++)
	{
		if (bar.crown[i] > E_CROWN::CROWN_NONE)
		{
			bar.show_score.crown_color = bar.crown[i];
			bar.show_score.crown_diff = (E_DIFFCULTY)i;
		}
		if (bar.rank[i] > E_SCORE_RANK::RANK_NONE)
		{
			bar.show_score.rank_color = bar.rank[i];
			bar.show_score.rank_diff = (E_DIFFCULTY)i;
		}
	}
	return bar;
}


void MusicGame::SongSelect::FumenListCreate(list<string> fumen_path_list)
{
	//とじるバーを作成
	ST_BAR_INFO bar_close;
	bar_close.bar_type = BAR_CLOSE;
	g_close_id = g_vec_all_fumen_bar.size();
	g_vec_all_fumen_bar.push_back(bar_close);


	g_vec_folder_fumen.resize(g_vec_folder_bar.size());


	//譜面リストを作成
	for (auto itr = fumen_path_list.begin(); itr != fumen_path_list.end(); itr++)
	{
		string str_fumen_command;
		list<string> str_split_fumen_command;

		string file_path = *itr;
		string fumen_path = file_path;

		if (file_path.find(".tjs") != -1)
		{
			//ファイルを開く
			ifstream ifs(file_path);
			if (!ifs)
			{
				wstring wstr = MusicGame::StringToWString(file_path);
				MessageBox(NULL, (wstr.c_str()),
					TEXT("譜面ファイル読み込み失敗"), MB_OK);
				ifs.close();
				continue;
			}
			else if (getline(ifs, str_fumen_command))
			{
				fumen_path = str_fumen_command;
			}
		}

		//文字列とパスを一致させる必要がるため、
		//スラッシュを\\に変換する
		file_path = regex_replace(file_path, regex("/"), "\\");

		bool bar_insert = false;
		int id = -1;


		for (int i = 0; i < g_vec_folder_bar.size(); i++)
		{

			//譜面パスにフォルダパスが含まれているか検索する。
			if (itr->find(g_vec_folder_bar[i].folder_path) != -1)
			{
				for (int j = 0; j < g_vec_all_fumen_bar.size(); j++)
				{
					//読み込んだ譜面パスと曲バーの譜面パスが一致したら登録！！
					if (file_path == g_vec_all_fumen_bar[j].folder_path)
					{
						//tjsの場合ジャンルは置き換えない
						if (file_path.find(".tjs") != -1)
						{

						}
						else
						{
							g_vec_all_fumen_bar[j].genre = g_vec_folder_bar[i].genre;

							for (int k = 0; k < (int)E_DIFFCULTY::DIFF_Count; k++)
							{
								if (g_vec_all_fumen_bar[j].crown[k] > E_CROWN::CROWN_NONE)
								MusicGame::g_player_status.crown_count[k][(int)g_vec_all_fumen_bar[j].crown[k]]++;

								if (g_vec_all_fumen_bar[j].rank[k] > E_SCORE_RANK::RANK_NONE)
								MusicGame::g_player_status.rank_count[k][(int)g_vec_all_fumen_bar[j].rank[k]]++;

							}
						}


						//バー情報を登録
						g_vec_folder_fumen[i].push_back(j);
						bar_insert = true;

						break;
					}
				}

				if (bar_insert == true)break;
			}
		}

		if (bar_insert == false)
		{
			for (int j = 0; j < g_vec_all_fumen_bar.size(); j++)
			{
				//読み込んだ譜面パスと曲バーの譜面パスが一致したら登録！！
				if (*itr == g_vec_all_fumen_bar[j].folder_path)
				{
					//バー情報を登録
					g_vec_folder_fumen[13].push_back(j);
					bar_insert = true;
					break;
				}
			}
		}

	}

}

void MusicGame::SongSelect::CloseBoxInsert(vector<int>& folder_fumen)
{
	for (int i = 0; i < folder_fumen.size(); i += CLOSE_BOX_INTERVAL)
	{
		folder_fumen.insert(folder_fumen.begin() + i, g_close_id);
	}
}

//wchar_t* MusicGame::StrToWcr(string str)
//{
//
//}
void MusicGame::SongSelect::ST_BAR_INFO::ScoreSet(ST_SCORE_DATA score,E_DIFFCULTY diffculty)
{
	int diff = diffculty;


	bestscore[diff] = score.score;
	crown[diff] = score.crown;
	rank[diff] = score.score_rank;

	for (int i = DIFF_EASY; i < DIFF_Count; i++)
	{
		if (crown[i] > E_CROWN::CROWN_NONE)
		{
			show_score.crown_color = crown[i];
			show_score.crown_diff = (E_DIFFCULTY)i;
		}
		if (rank[i] > E_SCORE_RANK::RANK_NONE)
		{
			show_score.rank_color = rank[i];
			show_score.rank_diff = (E_DIFFCULTY)i;
		}
	}
};

MusicGame::DanC::DanC()
{
	m_type = TYPE_GAUGE;
	for (int i = 0; i < DAN_MAX_SONG; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_norma[i][j] = -1;
			m_value[i] = 0;
		}
		m_status[i] = DANC_REACH;
	}
	m_song_count = 0;
	m_failed = false;
	m_common = true;

}
void MusicGame::DanC::SetDanC(E_DAN_TYPE type, int red, int gold)
{
	int song = m_common == true ? 0 : m_song_count;

	m_type = type;
	
	m_norma[song][0] = red;
	m_norma[song][1] = gold;

	m_song_count++;
}
int MusicGame::DanC::GetValue()
{
	return m_value[m_song_count];

}
bool MusicGame::DanC::Update(int value,int song_num)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);


	bool is_changed = false;

	//n未満ですでに不合格している場合falseを返す
	if (m_range == E_DAN_RANGE::RANGE_LESS && m_status[song_num] == DANC_FAILED)return false;
	
	if (m_value[song_num] != value)
	{
		m_value[song_num] = value;
		is_changed = true;
	}
	
	
	
	SetCleared(song_num);
	SetReached(song_num);

	return is_changed;
}
void MusicGame::DanC::SetStatus(E_DAN_STATUS status,int song)
{
	m_status[song] = status;
}
MusicGame::DanC::E_DAN_STATUS MusicGame::DanC::GetStatus(int song)
{
	return m_status[song];
}

void MusicGame::DanC::SetCleared(int song)
{
	if (m_status[song] == E_DAN_STATUS::DANC_FAILED)return;

	E_DAN_STATUS status = m_status[song];

	//以上
	if (m_range == RANGE_MORE)
	{
		if (m_value[song] >= m_norma[song][1])
			status = DANC_GOLD;
		else if (m_value[song] >= m_norma[song][0])
			status = DANC_CLEAR;
		else
			status = DANC_REACH;
	}
	//未満
	else
	{
		if (m_value[song] < m_norma[song][1])
			status = DANC_GOLD;
		else if (m_value[song] < m_norma[song][0])
			status = DANC_CLEAR;
	}

	//条件[以上]の場合、ピンチかつ条件に達していない場合は更新しない。
	if (m_status[song] == E_DAN_STATUS::DANC_PINCH && status == DANC_REACH)
		return;

		m_status[song] = status;

}
void MusicGame::DanC::SetReached(int song)
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);
	E_DAN_STATUS status = GetStatus(song);

	//一度不合格になった場合戻らないことにする
	if (status == E_DAN_STATUS::DANC_FAILED)return;

	int notes_count = m_common == true ? enso->m_enso[0].m_fumen.notes_count[BRANCH_NONE] : dan->GetNowSong().notes_count[BRANCH_NONE];

	int notes_remain = m_common == true ? 
		enso->m_enso[0].m_fumen.notes_count[BRANCH_NONE] -
		enso->m_enso[0].m_score_data.judge[JUST] -
		enso->m_enso[0].m_score_data.judge[HIT] -
		enso->m_enso[0].m_score_data.judge[MISS] :
		
		dan->GetNowSong().notes_count[BRANCH_NONE] -
		dan->GetSongJudge(JUST) -
		dan->GetSongJudge(HIT) -
		dan->GetSongJudge(MISS);
	int roll_remain = m_common == true ? enso->GetRollRemain() : dan->GetNowSong().roll_remain;
	float roll_time = m_common == true ? enso->m_enso[0].m_roll_time : dan->GetRollTime();
	//以上
	if (m_range == RANGE_MORE)
	{
		if (m_status[song] == DANC_CLEAR || m_status[song] == DANC_GOLD)return;

		//残り連打数が0になったとき
		if (roll_remain <= 0 && m_type == E_DAN_TYPE::TYPE_ROLL)
		{
			if (m_value[song] < m_norma[song][0])
				status = DANC_FAILED;
		}
		//残り音符数が0になったときに判定されるやつ
		else if (notes_remain <= 0 && roll_remain <= 0)
		{
			switch (m_type)
			{
			case E_DAN_TYPE::TYPE_GAUGE:
			case E_DAN_TYPE::TYPE_SCORE:
			case E_DAN_TYPE::TYPE_HIT:
				if (m_value[song] < m_norma[song][0])
					status = DANC_FAILED;
				break;
	
			}
		}

		//常に監視されるやつ
		else
		{
			switch (m_type)
			{
			case E_DAN_TYPE::TYPE_GREAT:
			case E_DAN_TYPE::TYPE_GOOD:
			case E_DAN_TYPE::TYPE_MISS:
				//残り音符数
				if (notes_remain + m_value[song] < m_norma[song][0])
					status = DANC_FAILED;
				else if (m_norma[song][0] + (notes_count - m_norma[song][0]) * 0.05f >= notes_remain + m_value[song])
					status = DANC_PINCH;
				break;
			case E_DAN_TYPE::TYPE_COMBO:
				if (notes_remain + enso->m_enso[0].m_score_data.combo < m_norma[song][0] &&
					m_value[song] < m_norma[song][0])
					status = DANC_FAILED;
				else if (notes_remain + enso->m_enso[0].m_score_data.combo < m_norma[song][0] * 1.1f &&
					m_value[song] < m_norma[song][0])
					status = DANC_PINCH;
				break;
			case E_DAN_TYPE::TYPE_SCORE:
				//今後、曲ごとのアッドスコアを取得して曲ごとのノーツカウントも換算して決める
				if (m_value[song] + (notes_remain * enso->m_enso[0].m_score_add) < m_norma[song][0])status = DANC_PINCH;
				break;
			case E_DAN_TYPE::TYPE_ROLL:
				//現在の値 + 連打秒数(秒速17打)より少ない場合
				if(m_value[song] + roll_time * 17.0f < m_norma[song][0])status = DANC_PINCH;
				break;
			case E_DAN_TYPE::TYPE_HIT:
				if (m_value[song] + notes_remain + dan->GetRollTime() * 17.0f < m_norma[song][0])status = DANC_PINCH;
				break;
			}
		}
	}
	//未満
	else
	{
		if (m_value[song] >= m_norma[song][0])
			status = DANC_FAILED;
	}

	if (status == DANC_FAILED && m_status[song] != DANC_FAILED)
		Audio::Start(se_DAN_FAILED);

	m_status[song] = status;

}
float MusicGame::DanC::GetValueToPercent(int song)
{
	if (m_norma[song][0] == 0)return 0;

		
	float val = (float)m_value[song] / (float)m_norma[song][0];
	
	if (val < 0.0f)val = 0.0f;
	if (val > 1.0f) val = 1.0f;
	return val;
}
bool MusicGame::DanC::GetReached()
{
	CObjDanC* dan = (CObjDanC*)Objs::GetObj(OBJ_DANC);

	int song = m_common == true ? 0: dan->GetSongNumber();
	
	return m_status[song] == DANC_FAILED;
}

void MusicGame::ScoreDataImport(ST_SCORE_DATA score[DIFF_Count],string file_path)
{
	string str_score;
	list<string> list_str_score_command;

	//ファイルを開く
	ifstream ifs(file_path);
	if (!ifs)
	{
		ifs.close();
		return;
	}

	for (int i = 0; i < DIFF_Count; i++)
	{
		for (int j = 0; j < MusicGame::Result::SCORE_Count; j++)
		{
			getline(ifs, str_score);

			switch (j)
			{
			case MusicGame::Result::SCORE_SCORE:
				score[i].score = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_CROWN:
				score[i].crown = (E_CROWN)atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_RANK:
				score[i].score_rank = (E_SCORE_RANK)atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_GREAT:
				score[i].judge[JUST] = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_GOOD:
				score[i].judge[HIT] = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_MISS:
				score[i].judge[MISS] = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_ROLL:
				score[i].judge[ROLL] = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_MAXCOMBO:
				score[i].max_combo = atoi(str_score.c_str());
				break;
			case MusicGame::Result::SCORE_PLAYCOUNT:
				score[i].playcount = atoi(str_score.c_str());
				break;
			default:
				break;
			}
		}
	}
}