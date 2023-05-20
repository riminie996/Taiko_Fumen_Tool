#pragma once
#include <Windows.h>
#include <D3D11.h>
#include <d3dCompiler.h>

//メモリ解放マクロ
//メモリ開放マクロ-----------------------
#define SAFE_DELETE(p)		{if(p)	{delete(p);		(p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p){if(p)	{delete[](p);	(p)=nullptr;}}
#define SAFE_RELEASE(p)		{if(p)	{(p)->Release();(p)=nullptr;}}

//構造体---------------------------------
//頂点レイアウト構造体(頂点が持つ情報)
struct POINT_LAYOUT
{
	float pos[3];//[X,Y,Z] 頂点
	float color[4];//[r,g,b,a]色
	float UV[2];//[U-V] //テクスチャ位置
};

//コンスタントバッファ構造体
struct POLYGON_BUFFER
{
	float color[4];//RGBA ポリゴンカラー
	float pos[4];//ポリゴンの位置情報
	float scale[4];//拡大縮小倍率
	float rotation[4];//回転
	float texsize[4];//表示するイメージのサイズHW
};

typedef class CDraw2DPolygon
{
public:
	CDraw2DPolygon() {};
	~CDraw2DPolygon() {};

	/// <summary>
/// テクスチャ付き四角ポリゴン描画。
/// </summary>
	static void Draw2D(int id,float x, float y) { Draw2D(id, x, y, 1.0f, 1.0f, 0.0f); }
	static void Draw2D(int id, float x, float y, float r) { Draw2D(id, x, y, 1.0f, 1.0f, r); }
	static void Draw2D(int id, float x, float y, float scaleX, float scaleY) { Draw2D(id, x, y, scaleX, scaleY, 0.0f); }
	static void Draw2D(int id, float x,float y,float scaleX,float scaleY,float r);


	//文字描画
	static void  Draw2DChar(ID3D11ShaderResourceView* resurec_view, float x, float y, float s, float rgba[4]);


	static HRESULT InitPolygonRender();//ポリゴン表示環境の初期化
	static void DeletePolygonRender();//ポリゴン表示環境の破棄

	static void LoadImage(int id,const wchar_t* img_name);//イメージ情報読み込み
	
private:


	//ポリゴン表示で必要な変数------------
	//GPU側で扱うよう
	static ID3D11VertexShader* m_pVertexShader;//バーデックスシェーダー
	static ID3D11PixelShader* m_pPixelShader;//ピクセルシェーダ
	static ID3D11InputLayout* m_pVertexLayout;//頂点入力レイアウト
	static ID3D11Buffer* m_pConstantBuffer;//コンスタントバッファ
	//ポリゴン情報登録用バッファ
	static ID3D11Buffer* m_pVertexBuffer;//バーティクスバッファ
	static ID3D11Buffer* m_pIndexBuffer;//インデックスバッファ

	//テクスチャの必要なもの
	static ID3D11SamplerState* m_pSampleLinear; //テクスチャサンプラー
	static ID3D11ShaderResourceView* m_pTexture[32];//テクスチャリソース
	static float m_width[32];//テクスチャの横幅
	static float m_height[32];//テクスチャの縦幅
}Draw;