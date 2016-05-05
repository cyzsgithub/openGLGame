

#include "Example.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>											


#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							

#define miu		0.0005		//Ħ����
#define max_v	0.3			//����ٶ�
#define a		0.002		//���ٶ�

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Example * example = new Example(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** ���캯�� */
Example::Example(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_rota=0;
	isCamera=true;
	speed=0.0;
	isborder=false;
	Rspeed=0.0;
}

/** ��ʼ��OpenGL */
bool Example::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);	
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);	  									/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	if(!m_Terrain.init())
	{
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);
		exit(0);
	}
	if (!m_Track.init())
	{
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);
		exit(0);
	}
	if(!m_sky.init())
	{
		MessageBox(NULL,"��ʼ�����ʧ��!","����",MB_OK);
		exit(0);
	}
	m_3DS.Init("Car.3DS");
	m_Camera.setCamera(5.0f,high_car, 1.0f, 5.0f, high_car, 0.0f,0.0f, 1.0f, 0.0f);   //�ı�position��Yֵ��������ӽ�
	m_Camera3.setCamera(5.0f,5.0f, 15.0f, 5.0f, 2.5f, 1.0f,0.0f, 1.0f, 0.0f);
	vectran3to1=m_Camera3.getPosition()-m_Camera.getPosition();
	return true;												/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Example::Uninit()									
{
/** �û��Զ����ж�ع��� */
///......
///......
}

bool Example::UpdateCamera()
{	
	/** ���̰�����Ӧ */

	if(m_Keys.IsPressed(VK_SHIFT))                      /**< ����SHIFT��ʱ���� */
	{
		m_Camera.setSpeed(speed*2);
	}
	if(!m_Keys.IsPressed(VK_SHIFT))
	{
		m_Camera.setSpeed(speed);
	}
	if(m_Keys.IsPressed(VK_UP) || m_Keys.IsPressed('W'))   /**< ���Ϸ������'W'������ */
		{
			if(speed<=max_v)
				speed+=a;
			else
				speed=max_v;
		//	m_Camera.moveCamera(m_Camera.getSpeed());  
		//	m_Camera3.C3TOC1(m_Camera,vectran3to1,0); 
		}

	if(m_Keys.IsPressed(VK_DOWN) || m_Keys.IsPressed('S')) /**< ���·������'S'������ */
		{
			if(speed>=-max_v)
				speed-=a;
			else
				speed=-max_v;
		//	m_Camera.moveCamera(-m_Camera.getSpeed());  
		//	m_Camera3.C3TOC1(m_Camera,vectran3to1,0); 
		}

	if(m_Keys.IsPressed(VK_LEFT) || m_Keys.IsPressed('A'))/**< ���������'A'������ */
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
	if(m_Keys.IsPressed(VK_RIGHT) || m_Keys.IsPressed('D')) /**< ���ҷ������'D'������ */
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
	if(m_Keys.IsPressed(VK_CONTROL))//����CTRL �ı��ӽ�
	{
		isCamera=!isCamera;
		m_Keys.SetReleased(VK_CONTROL);
	}
	m_rota-=Rspeed*m_Camera.getSpeed()*2;
	isborder=m_Camera.moveCamera(m_Camera.getSpeed());  //ǰ���ƶ���
	m_Camera3.C3TOC1(m_Camera,vectran3to1,0);			//��������˳������
	m_Camera.yawCamera(Rspeed*m_Camera.getSpeed()*2);    
	m_Camera3.C3TOC1(m_Camera,vectran3to1,Rspeed*m_Camera.getSpeed()*2);
	if(speed>0)//�ٶ�˥��
		speed=speed-miu;
	if(speed<0)
		speed=speed+miu;
	if(Rspeed>0)
		Rspeed=Rspeed-0.01;
	if(Rspeed<0)
		Rspeed=Rspeed+0.01;
	if(isborder)//�߽���ײ
	{
		speed=-(speed*0.5);
		isborder=false;
		//the_angle=m_Camera.getangle();
	}
	if(isCamera)//�Ƿ�Ϊ��һ�˳��ӽ�
	m_CurrCamera=m_Camera;
	else
	m_CurrCamera=m_Camera3;

	return true;
}

/** ������º��� */
void Example::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

	if (m_Keys.IsPressed(VK_F1) == true)						/**< ��F1�л�����/ȫ��ģʽ */
	{
		//ToggleFullscreen();										
	}
/** �û��Զ���ĸ��¹��� */
     UpdateCamera();
	 vectran=m_Camera.getPosition(); //����������ǰλ��
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
/** ���ƺ��� */
void Example::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();		
	m_CurrCamera.setLook();
	m_Terrain.render();
	m_Track.render();
	m_sky.render();
	Show3DS(vectran.x,vectran.z,0.1);
	glFlush();													/**< ǿ��ִ�����е�OpenGL���� */
}
