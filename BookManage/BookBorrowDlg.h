#pragma once
// CBookBorrowDlg �Ի���
class CBookBorrowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookBorrowDlg)
public:
	CBookBorrowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CBookBorrowDlg(DataType *data);
	virtual ~CBookBorrowDlg();
	enum { IDD = IDD_BOOKBORROW };// �Ի�������
	afx_msg void OnBnClickedOk();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
private:
	DataType *book;
	CString m_name;
	CString m_num;
	UINT m_no;
	UINT m_date;
	UINT now_time;
};
