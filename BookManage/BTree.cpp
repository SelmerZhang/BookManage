// BTree.cpp : ʵ���ļ�
#include "StdAfx.h"
#include "BookManageDlg.cpp"
#include "BTree.h"

BTree::BTree()
{
	root=NULL;//��ʼ������
}

BTree::~BTree()
{
	destroyBTree(root);//����ʱ�ͷ��ڴ�
}

result BTree::SearchBTree(KeyType K)
{
	pBTNode p=root,q=NULL;
	int found=FALSE,i=0;
	result res;
	// ��ʼ����pָ������㣬qָ��p��˫��
	while(p!=NULL&&found==FALSE)
	{
 		i=Search(p,K);
		// �ҵ�����ؼ���
		if (i>0&&p->key[i].no==K)
		{
			found=TRUE;
		}
		else
		{
			q=p;
			p=p->ptr[i];
		}
	}
	res.pt=found?p:q;
	res.i=i;
	res.tag=found;
	return res;
}

Status BTree::InsertBTree(DataType data)
{
	//���������������˫�������б�Ҫ�Ľ����ѵ�����ʹT����m��B����
	pBTNode q=NULL,ap=NULL;
	result res;
	int i,s;
	int finished=FALSE,needNewRoot=FALSE;
	DataType x;
	//��� T ���Ϊ�վ�����һ���µĽ��
	if(root==NULL)
	{
		newRoot(root,NULL,data,NULL);
	}
	else
	{
		//����Ԫ�� k �����е�λ��
		res=SearchBTree(data.no);//���ҵ�����Ԫ�� k �Ľ��
		if(res.tag==TRUE)
		{
			return FALSE;
		}
		else
		{
			q=res.pt;
			i=res.i;
			x=data;
			while(needNewRoot==FALSE&&finished==FALSE)
			{
				Insert(q,i,x,ap);
				if(q->keynum<M)
				{
					finished=TRUE; 
				}
				else
				{
					s=(M+1)/2;
					split(q,s,ap);
					x=q->key[s];
					if(q->parent)
					{
						q=q->parent;
						i=Search(q,x.no);//��˫�׽��*q�в���x�Ĳ���λ��
					}
					else
					{
						needNewRoot=TRUE;
					}
				}
			}
			if(needNewRoot==TRUE)newRoot(root,q,x,ap);//���ɺ���Ϣ(t,x,ap)���½��root
		}
	}
	return OK;
}

void BTree::Traverse(void (CBookManageDlg::*visit)(DataType e))//����
{
	Traverse(root,visit);
}

void BTree::copyData(DataType &to,DataType from)//���ƹؼ��ֵ���Ϣ
{
	to.no=from.no;
	to.name=from.name;
	to.author=from.author;
	to.current_num=from.current_num;
	to.total_num=from.total_num;
}

int BTree::Search(pBTNode p,KeyType K)//������ĳ������е�λ��
{
	if(p==NULL)return -1;
	int i=0;
	for(i=0;i<p->keynum&&p->key[i+1].no<=K;i++);
	return i;
}

void BTree::Insert(pBTNode &q,int i,DataType x,pBTNode ap)//����
{
	int n=q->keynum;
	for(int j=n;j>i;j--)//�ڳ��ռ�
	{
		copyData(q->key[j + 1],q->key[j]);
		q->ptr[j+1]=q->ptr[j];
	}
	copyData(q->key[i+1],x);
	q->ptr[i+1]=ap;
	if(ap)ap->parent=q;
	q->keynum++;
}

void BTree::split(pBTNode &q,int s,pBTNode &ap)//���ѽ��
{
	int i,j,n=q->keynum;
	ap=new BTNode;
	ap->ptr[0]=q->ptr[s];
	for (i = s + 1,j = 1; i <= n; i++,j++)
	{
		copyData(ap->key[j],q->key[i]);
		ap->ptr[j]=q->ptr[i];
	}
	ap->keynum=n-s;
	ap->parent=q->parent;
	for(i=0;i<=n-s;i++)
	{
		if(ap->ptr[i]!=NULL)ap->ptr[i]->parent=ap;
	}   
	q->keynum=s-1;
}

void BTree::newRoot(pBTNode &T,pBTNode p,DataType x,pBTNode ap)//����һ���µĽ��
{
	T=new BTNode;
	T->keynum=1;
	T->ptr[0]=p;//������߽�������
	T->ptr[1]=ap;//�����ұߵ�����
	copyData(T->key[1],x);//�� x Ԫ�صĽ��ֵ���Ƶ� T �ĵ�һ��Ԫ����
	//�����Ӳ��յ�ʱ������õ�ǰ���Ϊ���ӵ�˫��
	if(p!=NULL)p->parent=T;
	if(ap!=NULL)ap->parent=T;
	T->parent=NULL;
}

void Traverse(pBTNode T,void (CBookManageDlg::*visit)(DataType e))//����
{
	int i; 
	if(T!=NULL)
	{
		for(i=1;i<=T->keynum;i++)visit(T->key[i]);
		for(i=0;i<=T->keynum;i++)Traverse(T->ptr[i],visit);
	}
}

void BTree::destroyBTree(pBTNode &T)
{
	int i; 
	pBTNode p;
	if(T!=NULL)
	{
		p=T;
		for(i=0;i<=T->keynum;i++)destroyBTree(T->ptr[i]);
		delete p;
		T=NULL;
	}
}
