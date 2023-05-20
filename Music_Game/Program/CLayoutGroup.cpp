
#include "CLayoutGroup.h"
#include <list>

#include <fstream>
#include <sstream>
#include "Function.h"

using namespace std;
CLayoutGroup::CLayoutGroup()
{

}

void CLayoutGroup::LoadData(string path)
{
	lyt.LoadData(path);
	ani.LoadData(path);
	tex.LoadTexture(path);
}



CLayoutGroup::~CLayoutGroup()
{

}

void CLayoutGroup::Init()
{

}

void CLayoutGroup::Draw()
{
	float x = lyt.GetPos().x + ani.GetValue().x;
	float y = lyt.GetPos().y + ani.GetValue().y;
	tex.m_scale_x = ani.GetValue().scale_x;
	tex.m_scale_y = ani.GetValue().scale_y;
	tex.m_rotation_z = ani.GetValue().rotate_z;
	tex.m_opacity = ani.GetValue().opacity;
	tex.m_color.r = ani.GetValue().r;
	tex.m_color.g = ani.GetValue().g;
	tex.m_color.b = ani.GetValue().b;

	//ÉãÅ[ÉvÇçló∂ÇµÇƒ
	do
	{
		do
		{
			tex.Draw(x, y, lyt.GetSource(), lyt.GetRefX(), lyt.GetRefY());
			x += lyt.GetSource().m_width;

		} while (x < WINDOW_SIZE_W && lyt.GetLoopX() == true);

		y += lyt.GetSource().m_height;

	} while (y < WINDOW_SIZE_H && lyt.GetLoopY() == true);
}