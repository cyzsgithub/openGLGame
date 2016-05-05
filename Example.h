//具体实例类

#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__


#include "GLFrame.h"	
#include "Camera.h"
#include "Vector.h"
#include "Terrain.h"
#include "3DSLoader.h"
#include "SkyBox.h"
#include "Track.h"
/**< 包含基本的框架类 */
/** 从GL_Application派生出一个子类 */
class Example : GLApplication								
{
public:
	bool	Init();										/**< 执行所有的初始化工作，如果成功函数返回true */
	void	Uninit();										/**< 执行所有的卸载工作 */
	void	Update(DWORD milliseconds);							/**< 执行所有的更新操作，传入的参数为两次操作经过的时间，以毫秒为单位 */
	void	Draw();												/**< 执行所有的绘制操作 */

	bool Draw_Grid();
	bool UpdateCamera();
	void Show3DS(float x,float z,float scale);
private:
	friend class GLApplication;								/**< 父类为它的一个友元类，可以用来创建程序的实例，见函数GL_Application * GL_Application::Create(const char * class_name) */
	Example(const char * class_name);						/**< 构造函数 */

	Camera m_Camera;						  /**<摄像机类此摄像机跟随小车,表示小车的坐标*/
	Camera m_Camera3;						// 第三视角摄像机
	Camera m_CurrCamera;
	CTerrain   m_Terrain;                     /**< 地形类 */
	C3DSLoader m_3DS;						// 赛车模型类
	CSkyBox m_sky;							//天空盒
	Vector3 vectran;						 /* 获取小车当前坐标*/
	Vector3 vectran3to1;					/*保存两个摄像机的坐标差*/
	bool isborder;
	float speed;
	float m_rota;
	bool isCamera;						//是否第一视角
	CTrack m_Track;

	float Rspeed;
	double the_angle;
};


#endif	// __EXAMPLE_H__