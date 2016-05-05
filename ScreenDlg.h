//�Ի�����
#ifndef	__SCREENDLG_H__
#define	__SCREENDLG_H__

#include "GLWindow.h"											/**< ����GLWindow.hͷ�ļ� */

/** ����ģʽѡ��Ի����� */
class ScreenDlg
{
public:
	ScreenDlg(void);   /**< ���캯�� */
	~ScreenDlg(void);  /**< �������� */

	void SetupWindow(GLWindow *pWindow); /**< ���ô��ڣ��������Ի��� */
    
	///�Ի�����Ϣ����ص�����
	static LRESULT CALLBACK ScreenDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static GLWindow *m_pWindow; /**< ȫ�ִ����� */
};
#endif //__SCREENDLG_H__