// BookRevertDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "BTree.h"
#include "BookManage.h"
#include "BookRevertDlg.h"
#include "afxdialogex.h"
// CBookRevertDlg �Ի���
IMPLEMENT_DYNAMIC(CBookRevertDlg, CDialogEx)

CBookRevertDlg::CBookRevertDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookRevertDlg::IDD, pParent)
	, m_no(0)
	, m_name(_T(""))
{

}

CBookRevertDlg::CBookRevertDlg(DataType *data):CDialogEx(CBookRevertDlg::IDD,NULL),m_no(0),m_name(_T(""))
{
	book=data;
}

CBookRevertDlg::~CBookRevertDlg()
{
}

void CBookRevertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BORROW_NO, m_no);
	DDV_MinMaxUInt(pDX, m_no, 0, UINT_MAX);
	DDX_Text(pDX, IDC_BOOK_NAME, m_name);
}

BOOL CBookRevertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_name=(*book).name;
	m_no=0;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BEGIN_MESSAGE_MAP(CBookRevertDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBookRevertDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CBookRevertDlg ��Ϣ�������
void CBookRevertDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL flag=FALSE;
	UpdateData();
	if(m_no==0)
	{
		AfxMessageBox(_T("�������Ķ�֤��"));
		return;
	}
	for(vector<Borrow>::iterator it=(*book).borrow.begin();it!=(*book).borrow.end();)
	{
		if((*it).no==m_no)
		{
			(*book).borrow.erase(it);
			(*book).current_num++;
			flag=TRUE;
			break;
		}
		else
		{
			it++;
		}
	}
	if(flag)
	{
		AfxMessageBox(_T("�黹�ɹ�"));
		CDialogEx::OnOK();
	}
	else
	{
		AfxMessageBox(_T("����û�н���"));
	}
}
