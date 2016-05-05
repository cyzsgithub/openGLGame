//跑道类
#pragma once
#include "stdafx.h"
#include"CBMPLoader.h"
#define PI 3.1415926
class CTrack
{
public:
	CTrack(void);
	~CTrack(void);

	/** 初始化地形 */
	bool init();
	/** 渲染地形 */
	void render();

private:

	/** 设置地形的大小 */
	void setSize(unsigned  int width, unsigned  int cell); 
	/** 装载纹理 */
	bool loadTexture();

public:
	unsigned  int     m_nWidth;          /**< 地形网格数 */
	unsigned  int     m_nCellWidth;      /**< 每一格宽度 */
	CBMPLoader        m_texture;      /**< 地面纹理和细节纹理 */
};

