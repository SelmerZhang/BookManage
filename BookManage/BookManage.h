
// BookManage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

typedef struct BookList{
	int no;
	struct BookList *next;
}*pBookList;

// CBookManageApp:
// �йش����ʵ�֣������ BookManage.cpp
//

class CBookManageApp : public CWinApp
{
public:
	CBookManageApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBookManageApp theApp;