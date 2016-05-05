//对话框类
#ifndef	__SCREENDLG_H__
#define	__SCREENDLG_H__

#include "GLWindow.h"											/**< 包含GLWindow.h头文件 */

/** 定义模式选择对话框类 */
class ScreenDlg
{
public:
	ScreenDlg(void);   /**< 构造函数 */
	~ScreenDlg(void);  /**< 析构函数 */

	void SetupWindow(GLWindow *pWindow); /**< 配置窗口，并弹出对话框 */
    
	///对话框消息处理回调函数
	static LRESULT CALLBACK ScreenDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static GLWindow *m_pWindow; /**< 全局窗口类 */
};
#endif //__SCREENDLG_H__