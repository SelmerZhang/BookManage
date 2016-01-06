// BookManageDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "BookManage.h"
#include "BookManageDlg.h"
#include "InputBookDlg.h"
#include "ShowStructDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBookManageDlg �Ի���
CBookManageDlg::CBookManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBookManageDlg::IDD, pParent)
	, m_timer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBookManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOK, m_list);
	DDX_Text(pDX, IDC_TIMER, m_timer);
}

BEGIN_MESSAGE_MAP(CBookManageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CBookManageDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_INSERT, &CBookManageDlg::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_REFLASH, &CBookManageDlg::OnBnClickedReflash)
	ON_BN_CLICKED(IDC_DELETE, &CBookManageDlg::OnBnClickedDelete)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SHOW_STRUCT, &CBookManageDlg::OnBnClickedShowStruct)
END_MESSAGE_MAP()
// CBookManageDlg ��Ϣ�������
BOOL CBookManageDlg::OnInitDialog()
{
	CFile file;
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
	/*�����¼*/
	tree=new BTree();
	if(file.Open(_T("record.dat"),CFile::modeRead|CFile::modeNoTruncate|CFile::modeCreate)==TRUE)
	{
		file.SeekToBegin();
		CArchive loader(&file,CArchive::load);
		tree=((BTree*)loader.ReadObject((*tree).GetRuntimeClass()));
		loader.Close();
		OnBnClickedReflash();
	}
	/*��ʼ����־�ļ�д��ָ��*/
	log_file.Open(_T("log.txt"),CFile::modeNoTruncate|CFile::modeWrite);
	log_file.SeekToEnd();
	WriteLog(_T("ϵͳ����"));
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
		WriteLog(_T("����ͼ��")+data.name);
		//���뵽B��
		RunTimer timer;
		if((*tree).InsertBTree(data)==OK)
		{
			//���뵽ListControl
			EndTime(timer);
			CString s;
			int row=m_list.GetItemCount();
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
			result res=(*tree).SearchBTree(data.no);
			res.pt->key[res.i].current_num+=data.current_num;
			res.pt->key[res.i].total_num+=data.total_num;
			AfxMessageBox(_T("����������"));
			OnBnClickedReflash();
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
	RunTimer timer;
	DisplayList((*tree).GetRoot());
	EndTime(timer);
	m_list.SetRedraw(TRUE);
}

void CBookManageDlg::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos=m_list.GetFirstSelectedItemPosition();
	int row;
	KeyType key;
	if(pos!=NULL)
	{
		row=(int)m_list.GetNextSelectedItem(pos);
		if(row>=0&&AfxMessageBox(_T("��ȷ��Ҫɾ��")+m_list.GetItemText(row,1)+_T("��?"),MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
		{
			key=_ttoi(m_list.GetItemText(row,0));
			RunTimer timer;
			if((*tree).DeleteBTree(key)==OK)
			{
				EndTime(timer);
				WriteLog(_T("ɾ��ͼ��")+m_list.GetItemText(row,1));
				m_list.DeleteItem(row);
				AfxMessageBox(_T("ɾ���ɹ�!"));
			}
			else
			{
				AfxMessageBox(_T("ɾ��ʧ��"));
			}
		}
	}
}

void CBookManageDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
	/*�����м�¼����*/
	WriteLog(_T("ϵͳ�ر�"));
	CFile file(_T("record.dat"),CFile::modeCreate|CFile::modeReadWrite);
	CArchive store(&file,CArchive::store);
	store.WriteObject(tree);
	store.Flush();
	store.Close();
	delete tree;
	log_file.Flush();
	log_file.Close();
}

void CBookManageDlg::EndTime(RunTimer &timer)
{
	timer.end();
	CString s;
	timer.get_str_time(s);
	m_timer=s;
	UpdateData(FALSE);
}

void CBookManageDlg::OnBnClickedShowStruct()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CShowStructDlg dlg((*tree).GetRoot());
	dlg.DoModal();
}

void CBookManageDlg::WriteLog(LPCTSTR msg)
{
	SYSTEMTIME sys_time;
	CString str;
	GetLocalTime(&sys_time);
	str.Format(_T("%4d��%2d��%2d�� %2d:%2d:%2d %s\r\n"),sys_time.wYear,sys_time.wMonth,sys_time.wDay,sys_time.wHour,sys_time.wMinute,sys_time.wSecond,msg);
	log_file.Write(str,str.GetLength()*sizeof(wchar_t));
}
