#include "UsingListboxDlg.h"

UsingListboxDlg* UsingListboxDlg::ptr = NULL;

UsingListboxDlg::UsingListboxDlg(void)
{
	ptr = this;
}

void UsingListboxDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL UsingListboxDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	// ������� ����������� ��������� ����������
	hList1 = GetDlgItem(hwnd, IDC_LIST1);
	hList2 = GetDlgItem(hwnd, IDC_LIST2);
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);

	// ������� 8 ��������� � ������ � ��������� �������
	SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("����� ������")));
	SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("��������� ������")));
	SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("������� ��������")));
	SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("��������� �������")));
	SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("������� ������")));
	SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("���� �������")));
	SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("����� ������")));
	SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("���� �������")));

	// ��������� ������ ������� ��� ������ � ������������� �������
	SendMessage(hList2, LB_SETCOLUMNWIDTH, 170, 0);

	// ������� 8 ��������� � ������ � ������������� �������
	SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("���� ������")));
	SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("��������� ������� ������")));
	SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("������ ��������")));
	SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("�������� �������")));
	SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("����� ������")));
	SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("������� �������")));
	SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("������� ������")));
	SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("�������� �������")));
	return TRUE;
}

void UsingListboxDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
	case IDC_ADD: 
		{
			// ��������� ����� ������ (�������� �����), ��������� � ��������� ����
			int length = SendMessage(hEdit1, WM_GETTEXTLENGTH, 0, 0);
			// ������� ������ ������������ �������
			TCHAR *pBuffer = new TCHAR[length + 1];
			// � ���������� ������ ��������� �����, �������� � �������� ����
			GetWindowText(hEdit1, pBuffer, length + 1);
			if(lstrlen(pBuffer))
			{
				// �������, ������� �� ��� � ������ �������� �������� ����� 
				int index = SendMessage(hList1, LB_FINDSTRINGEXACT, -1, LPARAM(pBuffer));
				if(index == LB_ERR)
					// ������� �������� ����� � ������
					SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(pBuffer));
				else
					MessageBox(hwnd, TEXT("����� ���� ��� ����������!"), TEXT("���������� �����"), MB_OK | MB_ICONSTOP);
			}
			delete[] pBuffer;
		}
		break;
	case IDC_DEL:
		{
			// ������� ������ ���������� �������� ������
			int index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
			if(index != LB_ERR) // ������ �� ������� ������?
			{
				// ��������� ����� �������� ���������� �����
				int length = SendMessage(hList1, LB_GETTEXTLEN, index, 0);
				// ������� ������ ������������ �������
				TCHAR *pBuffer = new TCHAR[length + 1];
				// ��������� �������� ����� � ���������� ������
				SendMessage(hList1, LB_GETTEXT, index, LPARAM(pBuffer));
				MessageBox(hwnd, pBuffer, TEXT("�������� �����"), MB_OK | MB_ICONINFORMATION);
				// ������ ������ �� ������
				SendMessage(hList1, LB_DELETESTRING, index, 0);
				delete[] pBuffer;
			}
			else
				MessageBox(hwnd, TEXT("���� �� ������!"), TEXT("�������� �����"), MB_OK | MB_ICONSTOP);
		}
		break;
	case IDC_FIND:
		{
			// ��������� ����� �������� ��������, ��������� � ��������� ����
			int length = SendMessage(hEdit2, WM_GETTEXTLENGTH, 0, 0);
			// ������� ������ ������������ �������
			TCHAR *pBuffer = new TCHAR[length + 1];
			// ��������� �������� ����� � ���������� ������
			GetWindowText(hEdit2, pBuffer, length + 1);
			if(lstrlen(pBuffer))
			{
				// ���������, ������� �� � ������ ������� �������� �����
				int index = SendMessage(hList1, LB_SELECTSTRING, -1, LPARAM(pBuffer));
				if(index == LB_ERR)
					MessageBox(hwnd, TEXT("���� �� ������!"), TEXT("����� �����"), MB_OK | MB_ICONSTOP);
			}
			delete[] pBuffer;
		}
		break;
	case IDC_DELALL:
		// ������� ���������� ������
		SendMessage(hList1, LB_RESETCONTENT, 0, 0);
		break;
	case IDC_DELALL2:
	{
		int index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
		if (index != LB_ERR) // ������ �� ������� ������?
		{
			// ��������� ����� �������� ���������� �����
			int length = SendMessage(hList1, LB_GETTEXTLEN, index, 0);
			int newlength = GetWindowTextLength(hEdit3);
			// ������� ������ ������������ �������
			TCHAR* pBuffer = new TCHAR[length + 1];
			TCHAR* newpBuffer = new TCHAR[newlength + 1];
			// ��������� �������� ����� � ���������� ������
			SendMessage(hList1, LB_GETTEXT, index, LPARAM(pBuffer));
			GetWindowText(hEdit3, newpBuffer, newlength + 1);
			SetWindowText(hEdit3, L"");
			SendMessage(hList1, LB_DELETESTRING, index, 0); // �������� ������� ������
			SendMessage(hList1, LB_INSERTSTRING, index, (LPARAM)newpBuffer); // ������� ������ ������
			MessageBox(hwnd, newpBuffer, pBuffer, MB_OK | MB_ICONINFORMATION);
			delete[] pBuffer;
			delete[] newpBuffer;
		}
		else
			MessageBox(hwnd, TEXT("���� �� ������!"), TEXT(""), MB_OK | MB_ICONSTOP);
		break;
	}
	case IDC_GETSELITEMS:
		{
			// ��������� ���������� ��������� ��������� � ������ � ������������� �������
			int nCount = SendMessage(hList2, LB_GETSELCOUNT, 0, 0);
			// ������� ������ ������������ ������� ��� �������� �������� ��������� ��������� ������
			int *p = new int[nCount];
			// �������� ������������ ������ ��������� ���������� ��������� ������ 
			SendMessage(hList2, LB_GETSELITEMS, nCount, LPARAM(p));
			for(int i = 0; i < nCount; i++)
			{
				// ��������� ������ ������ �������� ������
				int length = SendMessage(hList2, LB_GETTEXTLEN, p[i], 0);
				// ������� ������ ������������ �������
				TCHAR *pBuffer = new TCHAR[length + 1];
				// � ���������� ������ ��������� ����� ���������� �������� ������
				SendMessage(hList2, LB_GETTEXT, p[i], LPARAM(pBuffer));
				MessageBox(hwnd, pBuffer, TEXT("������ � ������������� �������"), MB_OK | MB_ICONINFORMATION);
				delete[] pBuffer;
			}
		}
	}
	// � ������ � ��������� ������� ������� ����� ��� �������
	if(id == IDC_LIST1 && codeNotify == LBN_SELCHANGE)
	{
		// ������� ������ ���������� �������� ������
		int index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
		if(index != LB_ERR) // ������ �� ������� ������?
		{
			// ��������� ����� �������� �����
			int length = SendMessage(hList1, LB_GETTEXTLEN, index, 0);
			// ������� ������ ������������ �������
			TCHAR *pBuffer = new TCHAR[length + 1];
			// � ���������� ������ ��������� ����� ���������� �������� ������
			SendMessage(hList1, LB_GETTEXT, index, LPARAM(pBuffer));
			// ��������� ����� � ��������� �������� ����
			SetWindowText(hwnd, pBuffer);
			SetWindowText(hEdit3, pBuffer);
			delete[] pBuffer;
		}
	}
}

BOOL CALLBACK UsingListboxDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}