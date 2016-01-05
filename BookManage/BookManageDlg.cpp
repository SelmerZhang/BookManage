
// BookManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BookManage.h"
#include "BookManageDlg.h"
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
	m_list.InsertColumn(0,_T("���"),LVCFMT_LEFT,100);
	m_list.InsertColumn(1,_T("����"),LVCFMT_LEFT,100);
	m_list.InsertColumn(2,_T("����"),LVCFMT_LEFT,100);
	m_list.InsertColumn(3,_T("�ִ���"),LVCFMT_LEFT,60);
	m_list.InsertColumn(4,_T("�ܴ���"),LVCFMT_LEFT,60);
	DataType test;
	test.name=_T("c1");
	test.no=1;
	tree.InsertBTree(test);
	test.no=2;
	test.name=_T("c2");
	tree.InsertBTree(test);
	test.no=3;
	test.name=_T("c3");
	tree.InsertBTree(test);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
	
}
