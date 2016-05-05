//������
#ifndef __TERRAIN_H__
#define __TERRAIN_H__


#include "stdafx.h"
#include "CBMPLoader.h"
#include "camera.h"

/** ������ */
class CTerrain
{
public:
	
	/** ���캯�� */
	CTerrain();

	~CTerrain();

	/** ��ʼ������ */
	bool init();

	/** ��Ⱦ���� */
	void render();
	

private:

	/** ���õ��εĴ�С */
	void setSize(unsigned  int width, unsigned  int cell); 

	/** װ������ */
	bool loadTexture();

	/** ������������ */
	void setTexCoord(float x, float z);

                      
	
public:
	unsigned  int     m_nWidth;          /**< ���������� */
	unsigned  int     m_nCellWidth;      /**< ÿһ���� */
	CBMPLoader        m_texture;      /**< ���������ϸ������ */
                                         	
};

#endif //__TERRAIN_H__

