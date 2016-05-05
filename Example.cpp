

#include "Example.h"											/**< 包含头文件 */

#include <gl\gl.h>												/**< 包含OpenGL头文件 */
#include <gl\glu.h>												
#include <gl\glaux.h>											


#pragma comment(lib, "opengl32.lib")							/**< 包含OpenGL链接库文件 */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							

#define miu		0.0005		//摩擦力
#define max_v	0.3			//最大速度
#define a		0.002		//加速度

/** 创建一个程序的实例 */
GLApplication * GLApplication::Create(const char * class_name)
{
	Example * example = new Example(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** 构造函数 */
Example::Example(const char * class_name) : GLApplication(class_name)
{
  /// 初始化用户自定义的程序变量
	m_rota=0;
	isCamera=true;
	speed=0.0;
	isborder=false;
	Rspeed=0.0;
}

/** 初始化OpenGL */
bool Example::Init()									
{
/** 用户自定义的初始化过程 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);	
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);	  									/**< 改变OpenGL窗口大小，直接调用子类的函数 */
	if(!m_Terrain.init())
	{
		MessageBox(NULL,"初始化地形失败!","错误",MB_OK);
		exit(0);
	}
	if (!m_Track.init())
	{
		MessageBox(NULL,"初始化赛道失败!","错误",MB_OK);
		exit(0);
	}
	if(!m_sky.init())
	{
		MessageBox(NULL,"初始化天空失败!","错误",MB_OK);
		exit(0);
	}
	m_3DS.Init("Car.3DS");
	m_Camera.setCamera(5.0f,high_car, 1.0f, 5.0f, high_car, 0.0f,0.0f, 1.0f, 0.0f);   //改变position的Y值，来变更视角
	m_Camera3.setCamera(5.0f,5.0f, 15.0f, 5.0f, 2.5f, 1.0f,0.0f, 1.0f, 0.0f);
	vectran3to1=m_Camera3.getPosition()-m_Camera.getPosition();
	return true;												/**< 成功返回 */
}

/** 用户自定义的卸载函数 */
void Example::Uninit()									
{
/** 用户自定义的卸载过程 */
///......
///......
}

bool Example::UpdateCamera()
{	
	/** 键盘按键响应 */

	if(m_Keys.IsPressed(VK_SHIFT))                      /**< 按下SHIFT键时加速 */
	{
		m_Camera.setSpeed(speed*2);
	}
	if(!m_Keys.IsPressed(VK_SHIFT))
	{
		m_Camera.setSpeed(speed);
	}
	if(m_Keys.IsPressed(VK_UP) || m_Keys.IsPressed('W'))   /**< 向上方向键或'W'键按下 */
		{
			if(speed<=max_v)
				speed+=a;
			else
				speed=max_v;
		//	m_Camera.moveCamera(m_Camera.getSpeed());  
		//	m_Camera3.C3TOC1(m_Camera,vectran3to1,0); 
		}

	if(m_Keys.IsPressed(VK_DOWN) || m_Keys.IsPressed('S')) /**< 向下方向键或'S'键按下 */
		{
			if(speed>=-max_v)
				speed-=a;
			else
				speed=-max_v;
		//	m_Camera.moveCamera(-m_Camera.getSpeed());  
		//	m_Camera3.C3TOC1(m_Camera,vectran3to1,0); 
		}

	if(m_Keys.IsPressed(VK_LEFT) || m_Keys.IsPressed('A'))/**< 向左方向键或'A'键按下 */
		{
			//m_Camera.yawCamera(-m_Camera.getSpeed()*2);    
			//m_Camera3.C3TOC1(m_Camera,vectran3to1,-m_Camera.getSpeed()*2);
			/*m_rota+=m_Camera.getSpeed()*2;*/
			/*	Rspeed=-1.0;*/
			if(Rspeed>-1.0)
				Rspeed-=0.05;
			else
				Rspeed=-1.0;
		}
	if(m_Keys.IsPressed(VK_RIGHT) || m_Keys.IsPressed('D')) /**< 向右方向键或'D'键按下 */
		{
			//m_Camera.yawCamera(m_Camera.getSpeed()*2); 
			//m_Camera3.C3TOC1(m_Camera,vectran3to1,m_Camera.getSpeed()*2);
			/*m_rota-=m_Camera.getSpeed()*2;*/
			/*	Rspeed=1.0;*/
			if(Rspeed<1.0)
				Rspeed+=0.05;
			else
				Rspeed=1.0;
		}
	if(m_Keys.IsPressed(VK_CONTROL))//按下CTRL 改变视角
	{
		isCamera=!isCamera;
		m_Keys.SetReleased(VK_CONTROL);
	}
	m_rota-=Rspeed*m_Camera.getSpeed()*2;
	isborder=m_Camera.moveCamera(m_Camera.getSpeed());  //前后移动车
	m_Camera3.C3TOC1(m_Camera,vectran3to1,0);			//计算第三人称摄像机
	m_Camera.yawCamera(Rspeed*m_Camera.getSpeed()*2);    
	m_Camera3.C3TOC1(m_Camera,vectran3to1,Rspeed*m_Camera.getSpeed()*2);
	if(speed>0)//速度衰减
		speed=speed-miu;
	if(speed<0)
		speed=speed+miu;
	if(Rspeed>0)
		Rspeed=Rspeed-0.01;
	if(Rspeed<0)
		Rspeed=Rspeed+0.01;
	if(isborder)//边界碰撞
	{
		speed=-(speed*0.5);
		isborder=false;
		//the_angle=m_Camera.getangle();
	}
	if(isCamera)//是否为第一人称视角
	m_CurrCamera=m_Camera;
	else
	m_CurrCamera=m_Camera3;

	return true;
}

/** 程序更新函数 */
void Example::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< 按ESC退出 */
	{
		TerminateApplication();									
	}

	if (m_Keys.IsPressed(VK_F1) == true)						/**< 按F1切换窗口/全屏模式 */
	{
		//ToggleFullscreen();										
	}
/** 用户自定义的更新过程 */
     UpdateCamera();
	 vectran=m_Camera.getPosition(); //获得摄像机当前位置
}
void Example::Show3DS(float x,float z,float scale){
	float y=1.5;
	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(180,0.0f,1.0f,0.0f);
	glRotatef(m_rota,0.0f,1.0f,0.0f);
	glScalef(scale,scale,scale);
	m_3DS.Draw();
	glPopMatrix();
}
/** 绘制函数 */
void Example::Draw()											
{
/** 用户自定义的绘制过程 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();		
	m_CurrCamera.setLook();
	m_Terrain.render();
	m_Track.render();
	m_sky.render();
	Show3DS(vectran.x,vectran.z,0.1);
	glFlush();													/**< 强制执行所有的OpenGL命令 */
}
