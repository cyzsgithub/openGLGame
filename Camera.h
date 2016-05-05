//�������

#ifndef __CAMERA_H__
#define __CAMERA_H__
#define pai 3.141592654
#include "stdafx.h"
#include "Vector.h"                 /**< ����������ͷ�ļ� */
#include "GLFrame.h"
#include <math.h>

/** ������� */
class Camera
{
public:
	/** ���캯������������ */
	Camera();
	~Camera();
	
	/** ��������״̬���� */
	Vector3 getPosition()   {	return m_Position;		}
	Vector3 getView()	    {	return m_View;			}
	Vector3 getUpVector()   {	return m_UpVector;		}
	float   getSpeed()      {   return m_Speed;         }
	//�õ������ָ��
	static Camera* GetCamera(void) { return m_pCamera;}
	/** �����ٶ� */
	void    setSpeed(float speed)
	{ 
		m_Speed  = speed;
	}
     
	/** �����������λ��, �۲����������� */
	void setCamera(float positionX, float positionY, float positionZ,
			 	   float viewX,     float viewY,     float viewZ,
				   float upVectorX, float upVectorY, float upVectorZ);

	/** ��ת��������� */
	void rotateView(float angle, float X, float Y, float Z);

	/**����ʱ��ת���������**/
	void rotateView1(float angle, float X, float Y, float Z);
	/** �����������������۲췽�� */
	void setViewByMouse(); 
	
    /** ����������ƶ� */
	void yawCamera(float speed);

	/** ǰ���ƶ������ */
	bool moveCamera(float speed);
	
	/** ��������� */
	void setLook();

	//�����ӽ�������������
	void C3TOC1( Camera & m_Camera,Vector3 &len,float angle);

	double distance(Vector3 pointA,Vector3 pointB);

	double angle_Vect(Vector3 V1,Vector3 V2);

	double getangle();

	bool getisleft();
private:
	/** ��������� */
	static Camera  *m_pCamera;      /**< ��ǰȫ�������ָ�� */
	Vector3        m_Position;      /**< λ�� */
	Vector3        m_View;          /**< ���� */
	Vector3        m_UpVector;      /**< �������� */
	float          m_Speed;         /**< �ٶ� */
	bool		   isborder;
	Vector3		   up_point;
	Vector3        down_point;

	double		   the_angle;
	Vector3        shuiping;
	Vector3	       wandao;
	bool           borderisleft;
};

#endif //__CAMERA_H__