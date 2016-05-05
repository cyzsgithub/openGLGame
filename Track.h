//�ܵ���
#pragma once
#include "stdafx.h"
#include"CBMPLoader.h"
#define PI 3.1415926
class CTrack
{
public:
	CTrack(void);
	~CTrack(void);

	/** ��ʼ������ */
	bool init();
	/** ��Ⱦ���� */
	void render();

private:

	/** ���õ��εĴ�С */
	void setSize(unsigned  int width, unsigned  int cell); 
	/** װ������ */
	bool loadTexture();

public:
	unsigned  int     m_nWidth;          /**< ���������� */
	unsigned  int     m_nCellWidth;      /**< ÿһ���� */
	CBMPLoader        m_texture;      /**< ���������ϸ������ */
};

