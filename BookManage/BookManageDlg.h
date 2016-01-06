
// BookManageDlg.h : ͷ�ļ�
//
#pragma once
#include "afxcmn.h"
#include "RunTimer.h"
#include "BTree.h"

// CBookManageDlg �Ի���
class CBookManageDlg : public CDialogEx
{
public:
	CBookManageDlg(CWnd* pParent = NULL);// ��׼���캯��
	enum { IDD = IDD_BOOKMANAGE_DIALOG };// �Ի�������
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedInsert();
	afx_msg void OnBnClickedReflash();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedShowStruct();
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
private:
	BTree *tree;
	CListCtrl m_list;//ͼ��ListView
	CString m_timer;//��ʱ
	void DisplayList(pBTNode T);
	void EndTime(RunTimer &timer);
};
