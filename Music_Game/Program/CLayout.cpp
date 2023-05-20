
#include "CLayout.h"
#include <list>

#include <fstream>
#include <sstream>
#include "Function.h"

using namespace std;
CLayout::CLayout()
{
	//m_lyt.load_anime = false;
	//m_lyt.load_layout = false;
	//m_lyt.load_texture = false;
	m_lyt.loop_x = false;
	m_lyt.loop_y = false;
	m_lyt.pos.x = 0;
	m_lyt.pos.y = 0;
	m_lyt.rectangle.m_x = 0;
	m_lyt.rectangle.m_y = 0;
	m_lyt.rectangle.m_width = 1;
	m_lyt.rectangle.m_height = 1;
	m_lyt.reference_x = ref_Left;
	m_lyt.reference_y = ref_Top;
	m_lyt.blend_mode = E_BLEND_MODE::NORMAL;
}

void CLayout::LoadData(string entry_name)
{
	list<string> list_str = LoadFile(entry_name + Rimi::FILE_FORMAT_LAYOUT);

	for (auto itr = list_str.begin(); itr != list_str.end(); itr++)
	{
		string str_split;

		if (itr->find("ReferenceX:") != -1)
		{
			str_split = itr->substr(11);

			if (str_split.find("Left") != -1)
			{
				m_lyt.reference_x = ref_Left;
			}
			else if (str_split.find("Right") != -1)
			{
				m_lyt.reference_x = ref_Right;
			}
			else if (str_split.find("Center") != -1)
			{
				m_lyt.reference_x = ref_Center;
			}
		}
		else if (itr->find("ReferenceY:") != -1)
		{
			str_split = itr->substr(11);

			if (str_split.find("Top") != -1)
			{
				m_lyt.reference_y = ref_Top;
			}
			else if (str_split.find("Bottom") != -1)
			{
				m_lyt.reference_y = ref_Bottom;
			}
			else if (str_split.find("Center") != -1)
			{
				m_lyt.reference_y = ref_Center;
			}
		}
		else if (itr->find("SrcX:") != -1)
		{
			str_split = itr->substr(5);
			m_lyt.rectangle.m_x = stoi(str_split);
		}
		else if (itr->find("SrcY:") != -1)
		{
			str_split = itr->substr(5);
			m_lyt.rectangle.m_y = stoi(str_split);
		}
		else if (itr->find("SrcW:") != -1)
		{
			str_split = itr->substr(5);
			m_lyt.rectangle.m_width = stoi(str_split);
		}
		else if (itr->find("SrcH:") != -1)
		{
			str_split = itr->substr(5);
			m_lyt.rectangle.m_height = stoi(str_split);
		}
		else if (itr->find("LoopX:") != -1)
		{
			str_split = itr->substr(6);
			m_lyt.loop_x = stob(str_split);
		}
		//アニメ情報をエントリに追加する
		else if (itr->find("LoopY:") != -1)
		{
			str_split = itr->substr(6);
			m_lyt.loop_y = stob(str_split);
		}
		else if (itr->find("X:") != -1)
		{
			str_split = itr->substr(2);
			m_lyt.pos.x = stoi(str_split);
		}
		else if (itr->find("Y:") != -1)
		{
			str_split = itr->substr(2);
			m_lyt.pos.y = stoi(str_split);
		}
		else if (itr->find("Blend:") != -1)
		{
			str_split = itr->substr(6);

			if (str_split.find("Normal") != -1)
				m_lyt.blend_mode = E_BLEND_MODE::NORMAL;
			else if (str_split.find("AdditionAlpha") != -1)
				m_lyt.blend_mode = E_BLEND_MODE::ADDITIONALPHA;
			else if (str_split.find("Addition") != -1)
				m_lyt.blend_mode = E_BLEND_MODE::ADDITION;
		}
	}
}


//void CLayout::LoadDataGroup(string entry_name)
//{
//	anime.LoadData(entry_name);
//	m_lyt.tex.LoadTexture(entry_name + Rimi::FILE_FORMAT_IMAGE);
//	m_lyt.rectangle.m_lyt.x = 0;
//	m_lyt.rectangle.m_lyt.y = 0;
//	m_lyt.rectangle.m_lyt.width = m_lyt.tex.GetTexSizeW();
//	m_lyt.rectangle.m_lyt.height = m_lyt.tex.GetTexSizeH();
//
//	list<string> list_str = LoadFile(entry_name + Rimi::FILE_FORMAT_LAYOUT);
//
//	for (auto itr = list_str.begin(); itr != list_str.end(); itr++)
//	{
//		string str_split;
//
//		if (itr->find("ReferenceX:") != -1)
//		{
//			str_split = itr->substr(11);
//			
//			if (str_split.find("Left"))
//			{
//				m_lyt.reference_x = ref_Left;
//			}
//			else if (str_split.find("Right"))
//			{
//				m_lyt.reference_x = ref_Right;
//			}
//			else if (str_split.find("Center"))
//			{
//				m_lyt.reference_x = ref_Center;
//			}
//		}
//		else if (itr->find("ReferenceY:") != -1)
//		{
//			str_split = itr->substr(11);
//
//			if (str_split.find("Top"))
//			{
//				m_lyt.reference_y = ref_Top;
//			}
//			else if (str_split.find("Bottom"))
//			{
//				m_lyt.reference_y = ref_Bottom;
//			}
//			else if (str_split.find("Center"))
//			{
//				m_lyt.reference_y = ref_Center;
//			}
//		}
//		else if (itr->find("X:") != -1)
//		{
//			str_split = itr->substr(2);
//			m_lyt.pos.x = stoi(str_split);
//		}
//		else if (itr->find("Y:") != -1)
//		{
//			str_split = itr->substr(2);
//			m_lyt.pos.y = stoi(str_split);
//		}
//		else if (itr->find("SrcX:") != -1)
//		{
//			str_split = itr->substr(5);
//			m_lyt.rectangle.m_lyt.x = stoi(str_split);
//		}
//		else if (itr->find("SrcY:") != -1)
//		{
//			str_split = itr->substr(5);
//			m_lyt.rectangle.m_lyt.x = stoi(str_split);
//		}
//		else if (itr->find("SrcW:") != -1)
//		{
//			str_split = itr->substr(5);
//			m_lyt.rectangle.m_lyt.width = stoi(str_split);
//		}
//		else if (itr->find("SrcH:") != -1)
//		{
//			str_split = itr->substr(5);
//			m_lyt.rectangle.m_lyt.height = stoi(str_split);
//		}
//		else if (itr->find("LoopX:") != -1)
//		{
//			
//		}
//		//アニメ情報をエントリに追加する
//		else if (itr->find("LoopY:") != -1)
//		{
//			
//		}
//	}
//}
void CLayout::Init()
{

}

CLayout::~CLayout()
{

}