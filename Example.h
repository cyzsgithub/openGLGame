//����ʵ����

#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__


#include "GLFrame.h"	
#include "Camera.h"
#include "Vector.h"
#include "Terrain.h"
#include "3DSLoader.h"
#include "SkyBox.h"
#include "Track.h"
/**< ���������Ŀ���� */
/** ��GL_Application������һ������ */
class Example : GLApplication								
{
public:
	bool	Init();										/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();										/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);							/**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();												/**< ִ�����еĻ��Ʋ��� */

	bool Draw_Grid();
	bool UpdateCamera();
	void Show3DS(float x,float z,float scale);
private:
	friend class GLApplication;								/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Example(const char * class_name);						/**< ���캯�� */

	Camera m_Camera;						  /**<�����������������С��,��ʾС��������*/
	Camera m_Camera3;						// �����ӽ������
	Camera m_CurrCamera;
	CTerrain   m_Terrain;                     /**< ������ */
	C3DSLoader m_3DS;						// ����ģ����
	CSkyBox m_sky;							//��պ�
	Vector3 vectran;						 /* ��ȡС����ǰ����*/
	Vector3 vectran3to1;					/*��������������������*/
	bool isborder;
	float speed;
	float m_rota;
	bool isCamera;						//�Ƿ��һ�ӽ�
	CTrack m_Track;

	float Rspeed;
	double the_angle;
};


#endif	// __EXAMPLE_H__