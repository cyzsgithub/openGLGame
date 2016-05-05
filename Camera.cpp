

#include <windows.h>
#include<gl/glu.h>                     /**< 包含gl头文件 */

#include "Camera.h"                    /**< 包含摄像机头文件 */
#include "Vector.h"                    /**< 包含向量类 */

/** 构造函数 */
Camera* Camera::m_pCamera = NULL;
Camera::Camera()
{
	/** 初始化向量值 */
	Vector3 zero = Vector3(0.0, 0.0, 0.0);		
	Vector3 view = Vector3(0.0, 1.0, 0.5);		
	Vector3 up   = Vector3(0.0, 0.0, 1.0);		
    
	/** 初始化摄像机 */
	m_Position	= zero;					
	m_View		= view;				
	m_UpVector	= up;	
	m_Speed     = 0.2f;
	m_pCamera   = this;
	isborder    = false;
	up_point    = Vector3(-50,high_car,100);
	down_point  = Vector3(-50,high_car,-100);

	shuiping    = Vector3(1,high_car,0);
	the_angle   = 0.0;
	borderisleft= false;
}


Camera::~Camera()
{
}

/** 设置摄像机的位置,朝向和向上向量 */
void Camera::setCamera( float positionX, float positionY, float positionZ,
				  		float viewX,     float viewY,     float viewZ,
						float upVectorX, float upVectorY, float upVectorZ)
{
	/** 构造向量 */
	Vector3 Position	= Vector3(positionX, positionY, positionZ);
	Vector3 View		= Vector3(viewX, viewY, viewZ);
	Vector3 UpVector	= Vector3(upVectorX, upVectorY, upVectorZ);

	/** 设置摄像机 */
	m_Position = Position;	
	m_View     = View;			
	m_UpVector = UpVector;	
}

/**  旋转摄像机方向  */
void Camera::rotateView1(float angle, float x, float y, float z)
{
	Vector3 newView;

	/** 计算方向向量 */
	Vector3 view = m_View - m_Position;		
	angle*=pai/180;
	/** 计算 sin 和cos值 */
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	/** 计算旋转向量的x值 */
	//newView.x = view.x*cosTheta+view.z*sinTheta;
	newView.x = view.x*cosTheta-view.z*sinTheta;
	/** 计算旋转向量的y值 */
	newView.y = view.y;

	/** 计算旋转向量的z值 */
	//newView.z = view.z*cosTheta-view.x*sinTheta;
	newView.z = view.z*cosTheta+view.x*sinTheta;
	/** 更新摄像机的方向 */
	m_View = m_Position + newView;
}
/** 左右移动摄像机 */
void Camera::yawCamera(float speed)
{
	Vector3 cross = m_View - m_Position;
	cross = cross.crossProduct(m_UpVector);
	Vector3 oldPos,oldView;
	oldPos = m_Position;
	oldView = m_View;

	// Add the strafe vector to our view
	rotateView1(speed, 0, 1, 0);
}

/** 前后移动摄像机 */
bool Camera::moveCamera(float speed)
{
	/** 计算方向向量 */
	Vector3 vector = m_View - m_Position;
	vector = vector.normalize();         /**< 单位化 */
	Vector3 oldPos,oldView;
	isborder=false;
	oldPos = m_Position;
	oldView = m_View;
	/** 更新摄像机 */
	m_Position.x += vector.x * speed;    /**< 根据速度更新位置 */
	m_Position.z += vector.z * speed;		
	m_View.x += vector.x * speed;		 /**< 根据速度更新方向 */	
	m_View.z += vector.z * speed;
	if((m_Position.x>8.0||m_Position.x<-109.0&&m_Position.z<100&&m_Position.z>-100)||(m_Position.x<2.0&&m_Position.x>-101&&m_Position.z<100&&m_Position.z>-100))
	{
		//m_Position.x=oldPos.x;
		//m_View.x=oldView.x;
		m_Position=oldPos;
		m_View=oldView;
		isborder=true;
		//the_angle=90-angle_Vect(m_Position-m_View,shuiping);
		//if(m_Position.x>5||(m_Position.x>-102&&m_Position.x<-100))
		//	borderisleft=true;
		//else
		//	borderisleft=false;

	}
	if((distance(m_Position,up_point)<52*52||distance(m_Position,up_point)>59*59&&m_Position.z>100)||(distance(m_Position,down_point)<52*52||distance(m_Position,down_point)>59*59&&m_Position.z<-100))
	{
		//m_Position.z=oldPos.z;
		//m_View.z=oldView.z;
		m_Position=oldPos;
		m_View=oldView;
		isborder=true;
	}
	return isborder;
}
void Camera::C3TOC1(Camera & m_Camera,Vector3 &len,float angle){
	Vector3 newLenP;
	angle*=pai/180;
	/** 计算 sin 和cos值 */
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);
	/** 计算旋转向量的x值 */
	newLenP.x = len.x*cosTheta-len.z*sinTheta;
	/** 计算旋转向量的y值 */
	newLenP.y = len.y;
	/** 计算旋转向量的z值 */
	newLenP.z = len.z*cosTheta+len.x*sinTheta;

	m_Position=m_Camera.getPosition()+newLenP;			//计算摄像机的坐标
	m_View=m_Camera.getPosition();						//看向车子
	m_UpVector=m_Camera.getUpVector();					
	m_Speed=m_Camera.getSpeed();
	len=newLenP;										//更新两个摄像机的向量
}

/** 设置视点 */
void Camera::setLook()
{
	/** 设置视口 */
	gluLookAt(m_Position.x, m_Position.y, m_Position.z,	
			  m_View.x,	 m_View.y,     m_View.z,	
			  m_UpVector.x, m_UpVector.y, m_UpVector.z);
}

double Camera::distance(Vector3 pointA,Vector3 pointB)
{
	float length=0;
	Vector3 temp=pointA-pointB;
	length=temp.length();
	return length;
}


double Camera::angle_Vect(Vector3 V1,Vector3 V2)
{
	double len_V1=sqrt(V1.x*V1.x+V1.z*V1.z);
	double len_V2=sqrt(V2.x*V2.x+V2.z*V2.z);
	double V1_V2=V1.x*V2.x+V1.z*V2.z;
	double Vect_cos = V1_V2/(len_V1*len_V2);
	if(Vect_cos<0)
		Vect_cos=-Vect_cos;
	Vect_cos=acos(Vect_cos)*180/pai;
	return Vect_cos;
}

double Camera::getangle()
{
	return the_angle;
}

bool Camera::getisleft()
{
	return borderisleft;
}