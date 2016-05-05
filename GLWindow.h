//������
#ifndef	__GLWINDOW_H__
#define	__GLWINDOW_H__

#include <windows.h>                                             /**< ����windows.hͷ�ļ� */

#pragma warning(disable: 4311)                                  /**< ��ֹ��������������ת���ľ��� */
#pragma warning(disable: 4312)
#pragma warning(disable: 4244)

/** windows������ */
class GLWindow															
{
public:
/** ��Ҫ�Ĵ��ں���  */
	
	/** ���캯�� */
	GLWindow();
	/** ����windows���� */
	bool	Create(const char * window_title, const char * class_name, HINSTANCE h_instance, LPVOID lpParam);
	/** ɾ��OpenGL���� */
	void	Destroy();
	/** �ı䴰�ڵ���ʾ���� */
	bool	ChangeScreenSetting();
	/** �����ڴ�С�ı�ʱ��֪ͨOpenGL������С */
	void	ReshapeGL();
	/** Swap Buffers (Double Buffering) */
	void	SwapBuffers() { ::SwapBuffers(m_hDC); }

/** ���溯��Ϊ����/���ش���������� */
	
	/** ���ô������Ͻǵ�λ�� */
	void	SetPosX(int x);
	void	SetPosX(unsigned short x) { SetPosX((signed short)x); }		
	void	SetPosY(int y);
	void	SetPosY(unsigned short y) { SetPosY((signed short)y); }		
	/** ���ش��ڵĴ�С */
	int		GetWidth();
	int		GetHeight();
	/** ���ô��ڵĴ�С */
	void	SetWidth(int width);
	void	SetHeight(int height);
	/** ���ش������Ͻǵ�λ�� */
	int		GetPosX();
	int		GetPosY();
	/** ���ô��ڵ���ɫλ�� */
	void	SetHiColor()	{ m_BitsPerPixel = 16; }
	void	SetTrueColor()	{ m_BitsPerPixel = 32; }
	void	SetFullScreen(bool mode)	{ m_IsFullScreen = mode; }
	bool	GetFullScreen()	{ return m_IsFullScreen; }
	/** �����������������GL_Window m_Window�������m_Window��Ϊ���ھ��ʹ�� */
	operator HWND() { return m_hWnd; }

private:
	HWND	m_hWnd;														/**< ���ھ�� */
	HDC		m_hDC;														/**< �豸������ */
	HGLRC	m_hRC;														/**< OpenGL��Ⱦ������ */

	int		m_WindowPosX;												/**< ���ڵ����Ͻǵ�Xλ�� */
	int		m_WindowPosY;												/**< ���ڵ����Ͻǵ�Yλ�� */
	int		m_WindowWidth;												/**< ���ڵĿ�� */
	int		m_WindowHeight;												/**< ���ڵĸ߶� */
	int		m_ScreenWidth;												/**< ȫ���Ŀ�� */
	int		m_ScreenHeight;												/**< ȫ���ĸ߶� */
	int		m_BitsPerPixel;												/**< ��ɫλ�� */
	bool	m_IsFullScreen;												/**< �Ƿ�ȫ�� */
};

#endif	// __GLWINDOW_H__