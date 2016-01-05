#pragma once
#include "afxcmn.h"
// CBookInfoDlg �Ի���
class CBookInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookInfoDlg)
public:
	CBookInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CBookInfoDlg(DataType *data);
	virtual ~CBookInfoDlg();
	enum { IDD = IDD_BOOKINFODLG };// �Ի�������
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
private:
	DataType *book;
	int m_no;
	CString m_name;
	CString m_author;
	int m_current_num;
	int m_total_num;
	CListCtrl m_list;
	CString m_ids;
};
