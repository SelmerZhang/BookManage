// InputBookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BookManage.h"
#include "InputBookDlg.h"
#include "afxdialogex.h"


// CInputBookDlg �Ի���

IMPLEMENT_DYNAMIC(CInputBookDlg, CDialogEx)

CInputBookDlg::CInputBookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputBookDlg::IDD, pParent)
	, book_no(0)
	, book_name(_T(""))
	, book_author(_T(""))
	, book_num(1)
{

}

CInputBookDlg::~CInputBookDlg()
{
}

void CInputBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOOK_NO, book_no);
	DDV_MinMaxInt(pDX, book_no, 0, INT_MAX);
	DDX_Text(pDX, IDC_BOOK_NAME, book_name);
	DDX_Text(pDX, IDC_BOOK_AUTHOR, book_author);
	DDX_Text(pDX, IDC_BOOK_NUM, book_num);
	DDV_MinMaxInt(pDX, book_num, 1, INT_MAX);
}


BEGIN_MESSAGE_MAP(CInputBookDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputBookDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputBookDlg ��Ϣ�������
void CInputBookDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(book_name.IsEmpty())
	{
		AfxMessageBox(_T("����������"));
		return;
	}
	if(book_author.IsEmpty())
	{
		AfxMessageBox(_T("������������"));
		return;
	}
	CDialogEx::OnOK();
}
