// BTree.cpp : ʵ���ļ�
#include "StdAfx.h"
#include "BTree.h"

IMPLEMENT_SERIAL(BTree,CObject,VERSIONABLE_SCHEMA|2)

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

pBTNode BTree::GetRoot()//��ȡ�����
{
	return root;
}

Status BTree::DeleteBTree(KeyType k)//ɾ�����,ͨ���ؼ���kɾ��
{
	pBTNode p;
	int i;
	result res;
	if(root==NULL)
	{
		return ERROR;
	}
	else
	{
		res=SearchBTree(k);
		if(res.tag==FALSE)
		{
			return ERROR;
		}
		else
		{
			p=res.pt;
			i=res.i;
			exchange(p,i);
			if(p->keynum>=(M+1)/2-1)
			{
				return OK;
			}
			if(p==root)//ֻ��һ�����ڵ� 
			{
				delete root;
				root=NULL;
				return OK;
			}
			else
			{
				while(p)
				{
					if(p==root||p->keynum>=(M+1)/2-1||p->parent==NULL)
					{
						return OK;
					}
					else
					{
						if(fix(p->parent,p)==OK)
						{
							return OK;
						}
					}
					combine(p->parent,p);
					p=p->parent;
					if((p==root||p->parent==NULL)&&p->keynum==0)
					{
						root=p->ptr[0];
						delete p;
						p=root;
						root->parent=NULL;
						return OK;
					}
				}
				return OK;
			}
		}
	}
}

void BTree::Serialize(CArchive& ar)//���л�
{
	int size,i,j,k;
	Borrow borrow;
	CObject::Serialize(ar);
	if(ar.IsStoring())//���л�
	{
		CArray<DataType> arr;
		addToArr(root,arr);
		size=arr.GetSize();
		ar<<size;
		for(i=0;i<size;i++)
		{
			DataType data;
			data=arr.GetAt(i);
			j=data.borrow.size();
			ar<<data.no<<data.name<<data.author<<data.current_num<<data.total_num<<j;
			for(k=0;k<j;k++)
			{
				ar<<data.borrow[k].no<<data.borrow[k].start_time<<data.borrow[k].end_time;
			}
		}
	}
	else//�����л�
	{
		ar>>size;
		for(i=0;i<size;i++)
		{
			DataType data;
			ar>>data.no>>data.name>>data.author>>data.current_num>>data.total_num>>j;
			for(k=0;k<j;k++)
			{
				ar>>borrow.no>>borrow.start_time>>borrow.end_time;
				data.borrow.push_back(borrow);
			}
			InsertBTree(data);
		}
	}
}

void BTree::copyData(DataType &to,DataType from)//���ƹؼ��ֵ���Ϣ
{
	to.no=from.no;
	to.name=from.name;
	to.author=from.author;
	to.current_num=from.current_num;
	to.total_num=from.total_num;
	to.borrow=from.borrow;
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

int BTree::position(pBTNode T)//һ�������˫���е�λ��,������λ�� i
{
	int i=0;
	if(T==NULL)return 0;
	if(T->parent!=NULL)
	{
		while(i<=T->parent->keynum)
		{
			if(T==T->parent->ptr[i])return i;
			i++;
		}
	}
	return -1;
}

Status BTree::fix(pBTNode &T,pBTNode p)//�������Ľṹ
{
	int i=position(p);//ȡ��p ��˫���е�λ��
	int mid=(M+1)/2-1;//Ҫ�������ٽ��
	pBTNode temp;
	int k;
	if(i>0&&T->ptr[i-1]->keynum>mid)//����� 
	{
		temp=T->ptr[i-1];//���Լ�С���ֵܽ��
		p->keynum++;
		for(k=p->keynum;k>1;k--)
		{
			copyData(p->key[k],p->key[k-1]);//��ǰ��Ľ�����һλ
		}
		if(p->ptr[0]!=NULL)
		{
			for(k=p->keynum;k>=1;k--)
			{
				p->ptr[k]=p->ptr[k-1];//��Ҫ�ƶ��Ľ����ӽ������ƶ�
			}
		}
		copyData(p->key[1],T->key[i]);//��˫�׵Ľ�㸴�Ƶ���
		copyData(T->key[i],temp->key[temp->keynum]);//��С�ֵܽ��������Ǹ��ƶ���˫����
		if(temp->ptr[temp->keynum]!=NULL)//���ֵܽ����ӽ��Ҳ���ƹ���
		{
			p->ptr[0] = temp->ptr[temp->keynum];
			temp->ptr[temp->keynum]->parent=p; //�޸�ָ��˫�׵Ľ��
			temp->ptr[temp->keynum]=NULL;
		}
		temp->keynum--;
		return OK;
	}
	else if(i<T->keynum&&T->ptr[i+1]->keynum>mid)//���ҽ� 
	{
		temp=T->ptr[i+1];
		p->keynum++;
		copyData(p->key[p->keynum],T->key[i+1]);
		copyData(T->key[i+1],temp->key[1]);
		for(k=1;k<temp->keynum;k++)
		{
			copyData(temp->key[k],temp->key[k+1]);
		}
		if(temp->ptr[0]!=NULL)
		{
			p->ptr[p->keynum]=temp->ptr[0];
			temp->ptr[0]->parent=p;
			for(k=0;k<temp->keynum;k++)
			{
				temp->ptr[k]=temp->ptr[k+1];
			}
			temp->ptr[k+1]=NULL;
		}
		temp->keynum--;
		return OK;
	}
	else
	{
		return ERROR;
	}
}

Status BTree::combine(pBTNode &T,pBTNode &p)//�ϲ����
{
	int k,i=position(p);//ȡ��p ��˫���е�λ��
	int mid=(M+1)/2-1;//����������
	pBTNode p2;
	if(i==0)//����ǵ�һ��λ��
	{
		i=1;
		p2=T->ptr[i];
		p->keynum++;//����һ�����
		copyData(p->key[p->keynum],root->key[i]);//��˫�׵Ľ�㸴������
		if(p2->ptr[0]!=NULL)
		{
			p->ptr[p->keynum]=p2->ptr[0]; //���ֵܵ��ӽ��Ҳ���ƹ���
			p2->ptr[0]->parent=p; //�޸�˫��
		}		
		for(k=i;k<root->keynum;k++)
		{//��˫�׵Ľ����ǰ�ƶ�һλ
			copyData(T->key[k],T->key[k+1]);
		}
		p->keynum++;
		p->key[p->keynum]=p2->key[1];
		if(p2->ptr[1]!=NULL)
		{
			p->ptr[p->keynum]=p2->ptr[1];//���ֵܵ��ӽ��Ҳ���ƹ���
			p2->ptr[1]->parent=p;//�޸�ָ��˫�׵Ľ��
		}
		T->keynum--;
		delete p2;
		p2=NULL;
		for(k=1;k<=T->keynum;k++)
		{
			T->ptr[k]=T->ptr[k+1];//��˫�׽���ӽ����ǰ�ƶ�
		}
		T->ptr[k+1]=NULL;
	}
	else if(i>0)
	{
		p2=T->ptr[i-1];
		p2->keynum++;
		copyData(p2->key[p2->keynum],T->key[i]);//���Ƹ�����ֵ���ӽ����
		if(p->ptr[0]!=NULL)
		{
			p2->ptr[p2->keynum]=p->ptr[0];
			p->ptr[0]->parent=p2;//�޸�ָ��˫�׵Ľ��
		}				
		for(k=i;k<T->keynum;k++)
		{
			copyData(T->key[k],T->key[k+1]);//�����ǰ��
			T->ptr[k]=T->ptr[k+1];//���ӽ��ǰ��
		}
		T->ptr[k+1]=NULL;
		T->keynum--;
		delete p;
		p=p2;
	}
	return OK;
}

void BTree::exchange(pBTNode &T,int i)//���������㽻��
{
	pBTNode p=T;
	if(p->ptr[i]!=NULL)
	{
		p=p->ptr[i];
		while(p->ptr[0])
		{
			p=p->ptr[0];
		}
		copyData(T->key[i],p->key[1]);//��������
	}
	while(i<p->keynum)//���ý���������ݺ���
	{
		copyData(p->key[i],p->key[i+1]);//����һ�����ݸ��Ƶ�ǰһ������
		i++;
	}
	p->keynum--;//ɾ�����
	T=p;
}

void BTree::Traverse(pBTNode T,void (BTree::*visit)(DataType e))//����
{
	int i; 
	if(T!=NULL)
	{
		for(i=1;i<=T->keynum;i++)(this->*visit)(T->key[i]);
		for(i=0;i<=T->keynum;i++)Traverse(T->ptr[i],visit);
	}
}

void BTree::addToArr(pBTNode T,CArray<DataType> &arr)//�����㵽����arr��
{
	int i; 
	if(T!=NULL)
	{
		for(i=1;i<=T->keynum;i++)arr.Add(T->key[i]);
		for(i=0;i<=T->keynum;i++)addToArr(T->ptr[i],arr);
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
