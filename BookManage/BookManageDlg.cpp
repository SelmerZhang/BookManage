
// BookManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BookManage.h"
#include "BookManageDlg.h"
#include "InputBookDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBookManageDlg �Ի���




CBookManageDlg::CBookManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookManageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBookManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOK, m_list);
}

BEGIN_MESSAGE_MAP(CBookManageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CBookManageDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_INSERT, &CBookManageDlg::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_REFLASH, &CBookManageDlg::OnBnClickedReflash)
END_MESSAGE_MAP()


// CBookManageDlg ��Ϣ�������

BOOL CBookManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	/*��ʼ��ListView*/
	//����ѡ��+��ʾ������
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,_T("���"),LVCFMT_LEFT,100);
	m_list.InsertColumn(1,_T("����"),LVCFMT_LEFT,110);
	m_list.InsertColumn(2,_T("����"),LVCFMT_LEFT,100);
	m_list.InsertColumn(3,_T("�ִ���"),LVCFMT_LEFT,60);
	m_list.InsertColumn(4,_T("�ܴ���"),LVCFMT_LEFT,60);
	return TRUE;// ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBookManageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBookManageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBookManageDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CBookManageDlg::OnBnClickedInsert()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CInputBookDlg dlg;
	DataType data;
	if(dlg.DoModal()==IDOK)
	{
		data.no=dlg.book_no;
		data.name=dlg.book_name;
		data.author=dlg.book_author;
		data.current_num=data.total_num=dlg.book_num;
		//���뵽B��
		if(tree.InsertBTree(data)==OK)
		{
			//���뵽ListControl
			int row=m_list.GetItemCount();
			CString s;
			s.Format(_T("%d"),data.no);
			m_list.InsertItem(row,s);
			m_list.SetItemText(row,1,data.name);
			m_list.SetItemText(row,2,data.author);
			s.Format(_T("%d"),data.current_num);
			m_list.SetItemText(row,3,s);
			s.Format(_T("%d"),data.total_num);
			m_list.SetItemText(row,4,s);
		}
		else
		{
			AfxMessageBox(_T("������Ѵ���"));
		}
	}
}

void CBookManageDlg::DisplayList(pBTNode T)
{
	int i,row;
	CString s;
	DataType data;
	if(T!=NULL)
	{
		for(i=1;i<=T->keynum;i++)
		{
			data=T->key[i];
			row=m_list.GetItemCount();
			s.Format(_T("%d"),data.no);
			m_list.InsertItem(row,s);
			m_list.SetItemText(row,1,data.name);
			m_list.SetItemText(row,2,data.author);
			s.Format(_T("%d"),data.current_num);
			m_list.SetItemText(row,3,s);
			s.Format(_T("%d"),data.total_num);
			m_list.SetItemText(row,4,s);
		}
		for(i=0;i<=T->keynum;i++)DisplayList(T->ptr[i]);
	}
}


void CBookManageDlg::OnBnClickedReflash()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_list.SetRedraw(FALSE);
	m_list.DeleteAllItems();
	DisplayList(tree.GetRoot());
	m_list.SetRedraw(TRUE);
}
