#pragma once


// CInputBookDlg �Ի���

class CInputBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputBookDlg)

public:
	CInputBookDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputBookDlg();

// �Ի�������
	enum { IDD = IDD_INPUT_BOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int book_no;
	CString book_name;
	CString book_author;
	int book_num;
	afx_msg void OnBnClickedOk();
};
