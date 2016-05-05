
#include "ScreenDlg.h"
#include "resource.h"

GLWindow *ScreenDlg::m_pWindow = 0; /**< ��ʼ��ȫ�ִ��ڶ��� */

ScreenDlg::ScreenDlg(void)
{
}

ScreenDlg::~ScreenDlg(void)
{
}

/** ���ô��� */
void ScreenDlg::SetupWindow(GLWindow *pWindow)
{
	m_pWindow = pWindow;
	///����һ��ģʽ�Ի���
	DialogBox(	GetModuleHandle(NULL), 
				MAKEINTRESOURCE(IDD_SCREENDLG), 
				HWND_DESKTOP,
				(DLGPROC)ScreenDlgProc); 
}

///�Ի�����Ϣ����ص�����
LRESULT CALLBACK ScreenDlg::ScreenDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
    switch (message) 
    { 
    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
			case IDOK: 
				/// ����ȫ��ģʽ
                if(!IsDlgButtonChecked(hwndDlg, IDC_FULLSCREEN))
					m_pWindow->SetFullScreen(false);		/**< ���δѡ�У����ڴ���ģʽ������ */ 
				else
					m_pWindow->SetFullScreen(true);         /** ����ȫ������ */
				/// ������ɫλ��
				if(IsDlgButtonChecked(hwndDlg, IDC_16BPP))
					m_pWindow->SetHiColor();					/**< ����λ��Ϊ16λ */				
				else
					m_pWindow->SetTrueColor();					/**< ����λ��Ϊ32λ */	
				
				if(m_pWindow->GetFullScreen() == false)
				{	/// �������طֱ���
					if(IsDlgButtonChecked(hwndDlg, IDC_640_480))
					{
						m_pWindow->SetWidth( 640 );					    /**< ��� */
						m_pWindow->SetHeight( 480 );					/**< �߶� */
					}
					else if(IsDlgButtonChecked(hwndDlg, IDC_800_600))
					{
						m_pWindow->SetWidth( 800 );					/**< ��� */
						m_pWindow->SetHeight( 600 );				/**< �߶� */
					}
					else
					{
						m_pWindow->SetWidth( 1024 );					/**< ��� */
						m_pWindow->SetHeight( 768 );					/**< �߶� */
					}
				}
				EndDialog(hwndDlg, wParam); /**< �����Ի��� */
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
    ///��ʼ���Ի������,����ʾ�Ի���֮ǰ����
	case WM_INITDIALOG: 
        {
			CheckDlgButton(hwndDlg,IDC_FULLSCREEN, BST_UNCHECKED);           /**< ����ȫ����־��״̬Ϊδѡ�� */
			CheckRadioButton(hwndDlg,IDC_640_480, IDC_1024_768, IDC_640_480);/**<  ����һ�鵥ѡ����Ļ�ֱ��ʣ������趨��ʼ״̬Ϊ640x480 */
			CheckRadioButton(hwndDlg,IDC_16BPP, IDC_32BPP, IDC_32BPP);       /**<  ����һ�鵥ѡ��λ������趨��ʼ״̬Ϊ32λ */
			
		}
    } 
    return FALSE; 
} 
