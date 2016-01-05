
// BookManageDlg.h : ͷ�ļ�
//
#pragma once
#include "afxcmn.h"
#include "BTree.h"

// CBookManageDlg �Ի���
class CBookManageDlg : public CDialogEx
{
public:
	CBookManageDlg(CWnd* pParent = NULL);// ��׼���캯��
	enum { IDD = IDD_BOOKMANAGE_DIALOG };// �Ի�������
	CListCtrl m_list;// ͼ��ListView
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedInsert();
	void DisplayLine(DataType e);
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
private:
	BTree tree;
	void UpdateList();
};
typedef void (CBookManageDlg::*visit)(DataType e);
