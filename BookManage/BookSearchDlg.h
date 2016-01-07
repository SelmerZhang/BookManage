#pragma once
#include "afxcmn.h"


// CBookSearchDlg �Ի���

class CBookSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookSearchDlg)
public:
	CBookSearchDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBookSearchDlg();
	enum { IDD = IDD_BOOKSEARCHDLG };// �Ի�������
	BTree *tree;
	CMap<CString,LPCTSTR,pBookList,pBookList> *map;
	afx_msg void OnBnClickedSearch();
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
private:
	CString m_author;
	CListCtrl m_list;
};
