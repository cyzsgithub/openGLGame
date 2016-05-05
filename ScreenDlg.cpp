
#include "ScreenDlg.h"
#include "resource.h"

GLWindow *ScreenDlg::m_pWindow = 0; /**< 初始化全局窗口对象 */

ScreenDlg::ScreenDlg(void)
{
}

ScreenDlg::~ScreenDlg(void)
{
}

/** 配置窗口 */
void ScreenDlg::SetupWindow(GLWindow *pWindow)
{
	m_pWindow = pWindow;
	///创建一个模式对话框
	DialogBox(	GetModuleHandle(NULL), 
				MAKEINTRESOURCE(IDD_SCREENDLG), 
				HWND_DESKTOP,
				(DLGPROC)ScreenDlgProc); 
}

///对话框消息处理回调函数
LRESULT CALLBACK ScreenDlg::ScreenDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
    switch (message) 
    { 
    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
			case IDOK: 
				/// 设置全屏模式
                if(!IsDlgButtonChecked(hwndDlg, IDC_FULLSCREEN))
					m_pWindow->SetFullScreen(false);		/**< 如果未选中，则在窗口模式中运行 */ 
				else
					m_pWindow->SetFullScreen(true);         /** 否则，全屏运行 */
				/// 设置颜色位数
				if(IsDlgButtonChecked(hwndDlg, IDC_16BPP))
					m_pWindow->SetHiColor();					/**< 设置位深为16位 */				
				else
					m_pWindow->SetTrueColor();					/**< 设置位深为32位 */	
				
				if(m_pWindow->GetFullScreen() == false)
				{	/// 设置像素分辨率
					if(IsDlgButtonChecked(hwndDlg, IDC_640_480))
					{
						m_pWindow->SetWidth( 640 );					    /**< 宽度 */
						m_pWindow->SetHeight( 480 );					/**< 高度 */
					}
					else if(IsDlgButtonChecked(hwndDlg, IDC_800_600))
					{
						m_pWindow->SetWidth( 800 );					/**< 宽度 */
						m_pWindow->SetHeight( 600 );				/**< 高度 */
					}
					else
					{
						m_pWindow->SetWidth( 1024 );					/**< 宽度 */
						m_pWindow->SetHeight( 768 );					/**< 高度 */
					}
				}
				EndDialog(hwndDlg, wParam); /**< 结束对话框 */
                return TRUE; 
			case IDCANCEL:
				EndDialog(hwndDlg,false);
				exit(0);   
				
        }
	    switch (HIWORD(wParam))
		{
		case BN_CLICKED:
            CheckDlgButton(hwndDlg, lParam, BST_CHECKED);
   		    break;
		}
		break;
    ///初始化对话框组件,在显示对话框之前处理
	case WM_INITDIALOG: 
        {
			CheckDlgButton(hwndDlg,IDC_FULLSCREEN, BST_UNCHECKED);           /**< 设置全屏标志框状态为未选中 */
			CheckRadioButton(hwndDlg,IDC_640_480, IDC_1024_768, IDC_640_480);/**<  设置一组单选框（屏幕分辨率），并设定初始状态为640x480 */
			CheckRadioButton(hwndDlg,IDC_16BPP, IDC_32BPP, IDC_32BPP);       /**<  设置一组单选框（位深），并设定初始状态为32位 */
			
		}
    } 
    return FALSE; 
} 
