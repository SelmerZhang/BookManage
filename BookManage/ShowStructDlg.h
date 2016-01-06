#pragma once
#include "afxcmn.h"


// CShowStructDlg �Ի���

class CShowStructDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowStructDlg)
public:
	CShowStructDlg(CWnd* pParent = NULL);// ��׼���캯��
	CShowStructDlg(pBTNode T);
	virtual ~CShowStructDlg();
	enum { IDD = IDD_SHOWSTRUCT };// �Ի�������
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
private:
	pBTNode root;
	CTreeCtrl m_tree;
	void DisplayLine(pBTNode p,HTREEITEM list);
};
