
#include "GLWindow.h"													/**< ����GLwindows.hͷ�ļ� */

#include <gl/gl.h>														/**< ����OpenGLͷ�ļ� */
#include <gl/glu.h>														


/** ���캯�� */
GLWindow::GLWindow()													
{
	m_WindowPosX	= 0;												/**< ���ڵ����Ͻǵ�Xλ�� */
	m_WindowPosY	= 0;												/**< ���ڵ����Ͻǵ�Yλ�� */
	m_WindowWidth	= 640;												/**< ���ڵĿ�� */
	m_WindowHeight	= 480;												/**< ���ڵĸ߶� */
	m_ScreenWidth	= 1024;												/**< ȫ���Ŀ�� */
	m_ScreenHeight	= 768;												/**< ȫ���ĸ߶� */
	m_BitsPerPixel	= 16;												/**< ��ɫλ�� */
	m_IsFullScreen	= false;											/**< ��ʹ��ȫ�� */

	m_hWnd = 0;
	m_hDC = 0;
	m_hRC = 0;
}

/** ���ش��ڵĴ�С */
int GLWindow::GetWidth()
{
	if (m_IsFullScreen == true)
	{
		return m_ScreenWidth;
	}
	else
	{
		return m_WindowWidth;
	}
}
int GLWindow::GetHeight()
{
	if (m_IsFullScreen == true)
	{
		return m_ScreenHeight;
	}
	else
	{
		return m_WindowHeight;
	}
}

/** ���ô��ڵĴ�С */
void GLWindow::SetWidth(int width)
{
	if (m_IsFullScreen == true)
	{
		m_ScreenWidth = width;
	}
	else
	{
		m_WindowWidth = width;
	}
}
void GLWindow::SetHeight(int height)
{
	if (m_IsFullScreen == true)
	{
		m_ScreenHeight = height;
	}
	else
	{
		m_WindowHeight = height;
	}
}

/** ���ش������Ͻǵ�λ�� */
int GLWindow::GetPosX()
{
	if (m_IsFullScreen == false)
	{
		return m_WindowPosX;
	}
	return 0;
}
int GLWindow::GetPosY()
{
	if (m_IsFullScreen == false)
	{
		return m_WindowPosY;
	}
	return 0;
}

/** ���ô������Ͻǵ�λ�� */
void GLWindow::SetPosX(int x)
{
	if (m_IsFullScreen == false)
	{
		m_WindowPosX = x;
	}
}
void GLWindow::SetPosY(int y)
{
	if (m_IsFullScreen == false)
	{
		m_WindowPosY = y;
	}
}

/** �����ڴ�С�ı�ʱ��֪ͨOpenGL������С */
void GLWindow::ReshapeGL()
{
	GLsizei width = GetWidth();
	GLsizei height = GetHeight();
	glViewport(0, 0, width, height);									/**< ���������ӿ� */
	glMatrixMode(GL_PROJECTION);									
	glLoadIdentity();													
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 4000.0f);	
	//gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 200.0f);	
	glMatrixMode(GL_MODELVIEW);											
	glLoadIdentity();													
}

/** �ı䴰�ڵ���ʾ���� */
bool GLWindow::ChangeScreenSetting()
{
	DEVMODE dmScreenSettings;											/**< �豸ģʽ */
	ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));						/**< ����ṹ */
	dmScreenSettings.dmSize			= sizeof(DEVMODE);					/**< �ṹ��С */
	dmScreenSettings.dmPelsWidth	= GetWidth();						/**< ���ÿ�� */
	dmScreenSettings.dmPelsHeight	= GetHeight();						/**< ���ø߶� */
	dmScreenSettings.dmBitsPerPel	= m_BitsPerPixel;					/**< ����λ��� */
	//dmScreenSettings.dmDisplayFrequency = 75;                           /**< ������Ļˢ���� */
	dmScreenSettings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT ;//| DM_DISPLAYFREQUENCY;

	/// �ı���ʾģʽ
	if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		return false;													/**< ���ʧ�ܣ�����false */
	}
	return true;														/**< �ɹ����� */
}

/** ����windows���� */
bool GLWindow::Create(const char * window_title,const char * class_name, HINSTANCE h_instance, LPVOID lpParam)
{
	int nX=0;
	int nY=0;
	PIXELFORMATDESCRIPTOR pfd =											/**< �������������ṹ */
	{
		sizeof(PIXELFORMATDESCRIPTOR),									/**< ���������ṹ�Ĵ�С */ 
		1,																/**< �汾�� */
		PFD_DRAW_TO_WINDOW	|											/**< �������������ʾ��һ�������� */
		PFD_SUPPORT_OPENGL	|											/**< ������֧��OpenGL��ͼ */
		PFD_STEREO			|											/**< ��ɫ�����������建�� */
		PFD_DOUBLEBUFFER,												/**< ��ɫ��������˫���� */
		PFD_TYPE_RGBA,													/**< ʹ��RGBA��ɫ��ʽ */
		m_BitsPerPixel,													/**< ��ɫ����������ɫֵ��ռ��λ�� */
		0, 0, 0, 0, 0, 0,												/**< ʹ��Ĭ�ϵ���ɫ���� */
		0,																/**< ��Alpha���� */
		0,																/**< ��ɫ��������alpha�ɷֵ���λ���� */
		0,																/**< ���ۼƻ����� */
		0, 0, 0, 0,														/**< �ۼƻ���������λ */
		32,																/**< 32λ��Ȼ��� */
		0,																/**< ���ɰ滺�� */
		0,																/**< �޸��������� */
		PFD_MAIN_PLANE,													/**< ����ΪPFD_MAIN_PLANE������Ϊ����ͼ�� */
		0,																/**< ��ʾOpenGLʵ����֧�ֵ��ϲ���²�ƽ������� */
		0, 0, 0															/**< ��ʱ���Ѳ���ʹ�� */
	};

	DWORD windowStyle = WS_TILEDWINDOW  ;							/**< �������Ǵ������ͣ�ʹ�ó����趨 */
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;						

	if (m_IsFullScreen == true)											/**< ���Ϊȫ��ģʽ������ת��Ϊȫ��ģʽ */
	{
		if (ChangeScreenSetting() == false)
		{																/**< ȫ��ģʽת��ʧ�ܣ������Ի�����ʾ�������Դ���ģʽ */
			MessageBox(HWND_DESKTOP, "ģʽת��ʧ��.\n�ڴ���ģʽ������.", "Error", MB_OK | MB_ICONEXCLAMATION);
			m_IsFullScreen = false;										/**< ����Ϊ����ģʽ */
		}
		else															/**< ���Ϊ����ģʽ */
		{
			ShowCursor(false);											/**< ������� */
			windowStyle = WS_POPUP;										/**< ���ô���ģʽΪ���㴰�� */
			windowExtendedStyle |= WS_EX_TOPMOST;						
		}																
	}

	/// �������Ǵ��ڵĴ�С��ʹ��ͻ����Ĵ�СΪ�������õĴ�С
	RECT windowRect = {GetPosX(), GetPosY(), GetPosX() + GetWidth(), GetPosY() + GetHeight()};
	if (m_IsFullScreen == false)										/**< �ڴ���ģʽ��ʹ�� */
	{	
		windowExtendedStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	/**< ʹ���ھ���3D��� */
		int wid = GetSystemMetrics(SM_CXSCREEN);		/**< ��ȡ��ǰ��Ļ�� */
		int hei = GetSystemMetrics(SM_CYSCREEN);		/**< ��ȡ��ǰ��Ļ�� */
		nX = (wid - GetWidth()) / 2;                    /**< ���㴰�ھ����� */
		nY = (hei - GetHeight()) / 2;			
		/// �������Ǵ��ڵĴ�С��ʹ��ͻ����Ĵ�СΪ�������õĴ�С
		AdjustWindowRectEx(&windowRect, windowStyle, 0, windowExtendedStyle);
		/// �жϴ��ڵ����Ͻ��Ƿ�������������
		if (windowRect.left < 0)										/**< �������X����Ϊ�����ƶ����굽0�������������ڵ�λ�� */
		{
			windowRect.right -= windowRect.left;						
			windowRect.left = 0;										
		}
		if (windowRect.top < 0)											/**< �������Y����Ϊ�����ƶ����굽0�������������ڵ�λ�� */
		{
			windowRect.bottom -= windowRect.top;						
			windowRect.top = 0;											
		}
	}

	/// ��������
	m_hWnd = CreateWindowEx(windowExtendedStyle,						/**< ���ڵ���չ��� */
							class_name,									/**< ���ڵ����� */
							window_title,								/**< ���ڱ��� */
							windowStyle,								/**< ���ڵķ�� */
							nX,nY,                                      /**< ���ڵ����Ͻ�λ�� */
							windowRect.right - windowRect.left,			/**< ���ڵĿ�� */
							windowRect.bottom - windowRect.top,			/**< ���ڵĸ߶� */
                            HWND_DESKTOP,								/**< ���ڵĸ�����Ϊ���� */
							0,											/**< �޲˵� */
							h_instance,									/**< ���봰�ڵ�ʵ����� */
							lpParam);									/**< ������������ */

	while (m_hWnd != 0)													/**< �����Ƿ񴴽��ɹ� */
	{
		m_hDC = GetDC(m_hWnd);											/**< ���ش��ڵ��豸������ */
		if (m_hDC == 0)													/**< ���Ϊ�� */
		{																/**< ʧ�� */
			break;														
		}

		GLuint PixelFormat = ChoosePixelFormat(m_hDC, &pfd);			/**< ����һ�����ݵ����ظ�ʽ */
		if (PixelFormat == 0)											/**< ���û�ҵ� */
		{																/**< ʧ�� */
			break;														
		}
		if (SetPixelFormat(m_hDC, PixelFormat, &pfd) == false)			/**< �������ظ�ʽ */
		{																/**< ʧ�� */
			break;														
		}
		m_hRC = wglCreateContext(m_hDC);								/**< ����OpenGL����Ⱦ������ */
		if (m_hRC == 0)													/**< ���Ϊ�� */
		{																/**< ʧ�� */
			break;														
		}
		if (wglMakeCurrent(m_hDC, m_hRC) == false)						/**< ���õ�ǰ��OpenGL����Ⱦ����Ϊ��ǰ�Ĵ��� */
		{																/**< ʧ�� */
			break;														
		}
        
		ShowWindow(m_hWnd, SW_NORMAL);									/**< ��ʾ���� */
		ReshapeGL();													/**< ����OpenGL�������ڴ�С */
		return true;													/**< �ɹ����� */
	}																	

	Destroy();															/**< �ͷ���Դ */
	return false;														/**< ����ʧ�� */
}

/** ɾ��OpenGL���� */
void GLWindow::Destroy()									
{
	if (m_hWnd != 0)										/**< ���ھ���Ƿ���� */
	{
		if (m_hDC != 0)										/**< �����豸�������Ƿ���� */
		{
			wglMakeCurrent(m_hDC, 0);						/**< ���õ�ǰ��OpenGL����Ⱦ����Ϊ��NULL */
			if (m_hRC != 0)									/**< OpenGL����Ⱦ�������Ƿ���� */
			{
				wglDeleteContext(m_hRC);					/**< �ͷ�OpenGL����Ⱦ������ */
				m_hRC = 0;									/**< ����OpenGL����Ⱦ������Ϊ0 */
			}
			ReleaseDC(m_hWnd, m_hDC);						/**< �ͷŴ��ڵ��豸������ */
			m_hDC = 0;										/**< ���ô��ڵ��豸������Ϊ0 */
		}
		DestroyWindow(m_hWnd);								/**< ɾ������ */
		m_hWnd = 0;											/**< ���ô��ھ��Ϊ0 */
	}

	if (m_IsFullScreen)										/**< ���Ϊȫ��ģʽ���ڳ�������󣬱任������ģʽ������ʾ��� */
	{
		ChangeDisplaySettings(NULL, 0);						/**< �任������ģʽ */
		ShowCursor(true);									/**< ��ʾ��� */
	}
}
