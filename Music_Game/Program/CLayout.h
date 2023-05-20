#pragma once
//STLデバッグ機能をOFFにする
#define _HAS_ITERATOR_DEBUGGING	(0)

#include "CFileFormat.h"
#include "CTimeCounter.h"
#include "Function.h"
#include "GameL\DrawTexture.h"

class CLayout : CFileFormat
{
public:
	CLayout();
	~CLayout();
	void Init();
	void LoadData(std::string entry_name);
	void Draw();
	ST_LAYOUT GetData(){return  m_lyt; }
//	ST_LAYOUT *GetData(){return m_lyt; }
	Point GetPos()			{ return m_lyt.pos; }
	RECT_N GetSource()		{ return m_lyt.rectangle; }
	E_REFERENCE GetRefX()	{ return m_lyt.reference_x; }
	E_REFERENCE GetRefY()	{ return m_lyt.reference_y; }
	bool GetLoopX()			{ return m_lyt.loop_x; }
	bool GetLoopY()			{ return m_lyt.loop_y; }
	E_BLEND_MODE GetBlend() { return m_lyt.blend_mode; }

private:

	ST_LAYOUT m_lyt;
	bool m_load_layout;
	std::string m_str_name;
};