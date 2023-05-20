#include "CObjDancer.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//初期化
void CObjDancer::Init()
{
	//Commonスキンを使用するときのための変数
	string skin_name = m_dancer_name;
	int common_num = 0;

	if (skin_name == "Common")
	{
		common_num = 4;
}
	string dir = "Graphics/3_Enso/18_Skin/" + skin_name +"/Dancer/" + to_string(common_num) + "/";
	m_dancer.resize(MusicGame::TextureAmountCount(dir,".rmlyt"));
	
	for (int i = 0; i < m_dancer.size(); i++)
	{
		int wait_amount = MusicGame::TextureAmountCount(dir + to_string(i) + "/Wait/", ".png");
		m_dancer[i].wait_texture.resize(wait_amount);
		m_dancer[i].lyt.LoadData(dir + to_string(i) + "/0");
		m_dancer[i].ani_loop.LoadData(dir + to_string(i) + "/Wait/Wait");

		for (int j = 0; j < wait_amount; j++)
			m_dancer[i].wait_texture[j].LoadTexture(dir + to_string(i) + "/Wait/" + to_string(j) + ".png");
	}
}
//進行
void CObjDancer::Action()
{
	CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);
	for (int i = 0; i < m_dancer.size(); i++)
	{
		m_dancer[i].ani_loop.AddLoop(1.0f / (60.0f / enso->m_enso[0].m_now_bpm * 4.0f) / 60.0f);
	}
}
//描画
void CObjDancer::Draw()
{
	for (int i = 0; i < m_dancer.size(); i++)
	{
		CObjEnso* enso = (CObjEnso*)Objs::GetObj(OBJ_ENSO);

		//4体目
		if (i == 3 && enso->m_enso->m_score_data.ct_gauge.NowValue < 40)break;
		//5体目
		if (i == 4 && enso->m_enso->m_score_data.ct_gauge.NowValue < 80)break;


		int ptn = (int)m_dancer[i].ani_loop.GetValue(0).pattern;
		int x = m_dancer[i].lyt.GetData().pos.x;
		int y = m_dancer[i].lyt.GetData().pos.y;
		m_dancer[i].wait_texture[ptn].Draw(x,y , ref_Center, ref_Center);
	}
}
