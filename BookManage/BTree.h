#pragma once
// BTree
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define Status int
#define M 3

typedef int KeyType;

typedef struct Book{
	KeyType no;
	CString name;
	CString author;
	int current_num;
	int total_num;
}DataType;

typedef struct BTNode{
	int keynum;
	struct BTNode *parent;
	DataType key[M+1];
	struct BTNode *ptr[M+1];
}BTNode,*pBTNode;

typedef struct{
	BTNode *pt;
 	int i;
	int tag;
}result;

class BTree
{
public:
	BTree();
	virtual ~BTree();
	result SearchBTree(KeyType K);//����
	Status InsertBTree(DataType K);//�������뵽B����
	void Traverse(void (CBookManageDlg::*visit)(DataType e));//����
	//Status DeleteBTree(KeyType k);//ɾ�����,ͨ���ؼ��� k ɾ��
private:
	pBTNode root;//B���ĸ��ڵ�
	void copyData(DataType &to,DataType from);//���ƹؼ��ֵ���Ϣ
	int Search(pBTNode p,KeyType K);//������ĳ������е�λ��	
	void Insert(pBTNode &q,int i,DataType x,pBTNode ap);//����
	void split(pBTNode &q,int s,pBTNode &ap);//���ѽ��
	void newRoot(pBTNode &T,pBTNode p,DataType x,pBTNode ap);//����һ���µĽ��
	void Traverse(pBTNode T,void (CBookManageDlg::*visit)(DataType e));//����
	/*int position(BTree T);//һ�������˫���е�λ��,������λ�� i
	Status fix(BTree &root,BTree p);//�������Ľṹ
	Status combine(BTree &root,BTree &p);//�ϲ����
	void exchange(BTree &T,int i);//���������㽻��*/
	void destroyBTree(pBTNode &T);//����B��
};
