#pragma once
// CBookRevertDlg �Ի���
class CBookRevertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookRevertDlg)
public:
	CBookRevertDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CBookRevertDlg(DataType *data);
	virtual ~CBookRevertDlg();
	enum { IDD = IDD_BOOKREVERTDLG };// �Ի�������
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
private:
	DataType *book;
	CString m_name;
	UINT m_no;
};
