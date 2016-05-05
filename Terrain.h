//地形类
#ifndef __TERRAIN_H__
#define __TERRAIN_H__


#include "stdafx.h"
#include "CBMPLoader.h"
#include "camera.h"

/** 地形类 */
class CTerrain
{
public:
	
	/** 构造函数 */
	CTerrain();

	~CTerrain();

	/** 初始化地形 */
	bool init();

	/** 渲染地形 */
	void render();
	

private:

	/** 设置地形的大小 */
	void setSize(unsigned  int width, unsigned  int cell); 

	/** 装载纹理 */
	bool loadTexture();

	/** 设置纹理坐标 */
	void setTexCoord(float x, float z);

                      
	
public:
	unsigned  int     m_nWidth;          /**< 地形网格数 */
	unsigned  int     m_nCellWidth;      /**< 每一格宽度 */
	CBMPLoader        m_texture;      /**< 地面纹理和细节纹理 */
                                         	
};

#endif //__TERRAIN_H__

