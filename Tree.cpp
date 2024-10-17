#include "r.h"

CTree::CNode::CNode()
{
	par = left = right = NULL;
	b = 0;
}
CTree::CNode::CNode(char* v,CNode *par)
{
	this->par = par;
	left = right = NULL;
	b = 0;
	this->v = v;
	this->v[strlen(v)] = '\0';
}
CTree::CNode::~CNode()
{
	delete[] this->v;
}
bool CTree::CNode::IsLeft()const
{
	return par !=NULL && par->left == this;
}
bool CTree::CNode::IsRight()const
{
	return par != NULL && par->right == this;
}
//-------------------------------------------
CTree::CTree()
{
	SetZero();
}
void CTree::SetZero()
{
	root = NULL;
	n = 0;
}
CTree::~CTree()
{
	Clean();
}
int CTree::IsEmpty()
{
	return root==NULL;
}
void CTree::Clean()
{
	while(remove(this->root));
}
bool CTree::insert(char *v)
{
	if(root == NULL)
	{
		root = new CNode(v, NULL);
		this->n++;
		return true;
	}
	CNode *cur = root;
	while(1)
	{
		if(strcmp(cur->v, v) == 0)
			return false;
		else
			if(strcmp(cur->v, v)<0)
			{
				if(cur->right == NULL)
				{
					cur->right = new CNode(v, cur);
					this->n++;
					cur->b--;//cout<<" right "<<cur->v<<" "<<cur->right->v<<" "<<cur->b<<" right ";
					//cout<<"..."<<cur->v<<" "<<cur->b--<<"..,";
					while(cur!=root)
					{
						if(cur->b == 0)
							return true;
						else if(cur->b == -1 || cur->b == 1)
						{
							if(cur->IsLeft())
								cur->par->b++;
							else
								cur->par->b--;
							cur = cur->par;
						}
						else
						{
							balance(cur);
							return true;
						}
					}
					balance(cur);
					return true;
				}
				cur = cur->right;
			}
			else
			{
				if(cur->left == NULL)
				{
					cur->left = new CNode(v,cur);
					this->n++;
					cur->b++;//cout<<" left "<<cur->v<<" "<<cur->left->v<<" "<<cur->b<<" left ";
					while(cur!=root)
					{
						if(cur->b == 0)
							return true;
						else if(cur->b == 1 || cur->b == -1)
						{
							if(cur->IsLeft())
								cur->par->b++;
							else
								cur->par->b--;
							cur = cur->par;
						}
						else
						{
							balance(cur);
							return true;
						}
					}
					balance(root);
					return true;
				}
				cur = cur->left;
			}
	}
	/*while(1)
	{
		if(cur->b == 0)
			return true;
		if(cur->b == 1 || cur->b == -1)
		{
			if(strcmp(cur->v,cur->par->v)>0)
				cur->par->b--;
			else
				cur->par->b++;
			cur = cur->par;
		}
		else
		{
			balance(cur);
			return true;
		}
		if(cur == root)
			if(cur->b==-2 || cur->b==2)
			{
				balance(cur);
				return true;
			}
	}*/
}
bool CTree::remove(char *v)
{
	return(remove(search(v)));
}
bool CTree::remove(CNode *cur)
{
	if(cur == NULL || root == NULL)
	{
		return false;
	}
	if(cur->left == NULL && cur->right == NULL)
	{
		//cout<<"che1"<<endl;
		if(cur->IsLeft())
		{
			//cout<<"che11"<<endl;
			cur->par->b--;
			CNode *t = cur->par;
			t->left = NULL;
			while(t!=root)
			{
				if(t->b == -1 || t->b == 1)
					break;
				if(t->b == 0)
				{
					if(t->IsLeft())
						t->par->b--;
					else
						t->par->b++;
				}
				else
					balance(t);
				t = t->par;
			}
			if(root->b == 2 || root->b == -2)
				balance (root);
			//fullbalance(t);
		}
		else if(cur->IsRight())
		{
			//cout<<"che12"<<endl;
			cur->par->b++;
			CNode *t = cur->par;
			t->right = NULL;
			while(t!=root)
			{
				if(t->b == -1 || t->b == 1)
					break;
				if(t->b == 0)
				{
					if(t->IsLeft())
						t->par->b--;
					else
						t->par->b++;
				}
				else
					balance(t);
				t = t->par;
			}
			if(root->b == 2 || root->b == -2)
				balance (root);

			//fullbalance(t);
		}
		else 
		{
			//cout<<"che13"<<endl;
			root = NULL;
		}
		delete cur;
		this->n--;
		return true;
	}
	if(cur->left == NULL)
	{
		//cout<<"che2"<<endl;
		if(cur->IsLeft())
		{
			//cout<<"che21"<<endl;
			cur->par->left = cur->right;
			cur->right->par = cur->par;
			cur->par->b--;
			CNode *t = cur->par;
			while(t!=root)
			{
				if(t->b == -1 || t->b == 1)
					break;
				if(t->b == 0)
				{
					if(t->IsLeft())
						t->par->b--;
					else
						t->par->b++;
				}
				else
					balance(t);
				t = t->par;
			}
			if(root->b == 2 || root->b == -2)
				balance (root);
			/*if(t->b==-2 || t->b==2)
				fullbalance(t);*/
		}
		else if(cur->IsRight())
		{
			//cout<<"che22"<<endl;
			cur->par->right = cur->right;
			cur->par->b++;
			cur->right->par = cur->par;
			CNode *t = cur->par;
			while(t!=root)
			{
				if(t->b == -1 || t->b == 1)
					break;
				if(t->b == 0)
				{
					if(t->IsLeft())
						t->par->b--;
					else
						t->par->b++;
				}
				else
					balance(t);
				t = t->par;
			}
			if(root->b == 2 || root->b == -2)
				balance (root);
			/*if(t->b==-2 || t->b==2)
				fullbalance(t);*/
		}
		else 
		{
			//cout<<"che23"<<endl;
			root = cur->right;
			root->par = NULL;
		}
		delete cur;
		this->n--;
		return true;
	}
	if(cur->right == NULL)
	{
		//cout<<"che3"<<endl;
		if(cur->IsLeft())
		{
			//cout<<"che31"<<endl;
			cur->par->left = cur->left;
			cur->left->par = cur->par;
			cur->par->b--;
			CNode *t = cur->par;
			while(t!=root)
			{
				if(t->b == -1 || t->b == 1)
					break;
				if(t->b == 0)
				{
					if(t->IsLeft())
						t->par->b--;
					else
						t->par->b++;
				}
				else
					balance(t);
				t = t->par;
			}
			if(root->b == 2 || root->b == -2)
				balance (root);
			/*if(t->b==-2 || t->b==2)
				fullbalance(t);*/
		}
		else if(cur->IsRight())
		{
			//cout<<"che32"<<endl;
			cur->par->right = cur->left;
			cur->par->b++;
			cur->left->par = cur->par;
			CNode *t = cur->par;
			while(t!=root)
			{
				if(t->b == -1 || t->b == 1)
					break;
				if(t->b == 0)
				{
					if(t->IsLeft())
						t->par->b--;
					else
						t->par->b++;
				}
				else
				{
					balance(t);
				}
				t = t->par;
			}
			if(root->b == 2 || root->b == -2)
				balance (root);
			/*if(t->b==-2 || t->b==2)
				fullbalance(t);*/
		}
		else 
		{
			//cout<<"che33"<<endl;
			root = cur->left;
			root->par = NULL;
		}
		delete cur;
		this->n--;
		return true;
	}
	CNode *t = searchMin(cur->right);
	free(cur->v);
	cur->v = strdup(t->v);
	remove(t);
	//fullbalance(t1);
	this->n--;
	return true;
}
CTree::CNode* CTree::search(char *v)
{
	CNode *t;
	for(t = root; t != NULL;)
		if(strcmp(t->v,v)<0)
			t = t->right;
		else if(strcmp(t->v,v)>0)
			t = t->left;
		else return t;
	return NULL;
}
CTree::CNode* CTree::searchMin(CNode *cur)
{
	if(root == NULL)
		return NULL;
	CNode *t;
	for(t = cur;t->left != NULL; t = t->left);
	return t;
}
CTree::CNode* CTree::searchMax(CNode *cur)
{
	if(root == NULL)
		return NULL;
	CNode *t;
	for(t = cur;t->right != NULL; t = t->right);
	return t;
}
CTree::CNode* CTree::Next(CNode* cur)
{
	if(root == NULL)
		return NULL;
	if(cur->right != NULL)
		return searchMin(cur->right);
	for(;cur->par;cur = cur->par)
		if(cur->IsLeft())
			return cur->par;
	return NULL;
}
CTree::CNode* CTree::Prev(CNode *cur)
{
	if(root == NULL)
		return NULL;
	if(cur->left != NULL)
		return searchMax(cur->left);
	for(;cur->par;cur = cur->par)
		if(cur->IsRight())
			return cur->par;
	return NULL;
}
int CTree::GetSize()
{
	return n;
}

void CTree::balance(CNode *cur)
{
	
	if(cur->b == 2)
	{
		//cout<<endl<<"balancing of (right) "<<cur->v<<".";
		if(cur->left->b>=0)
		{
			cur->b = (cur->left->b == 0 ? 1 : 0);
			cur->left->b = (cur->left->b == 0 ? -1 : 0);
			smallRightRotate(cur);
		}
		else
			bigRightRotate(cur);
	}
	else if(cur->b == -2)
	{
		//cout<<endl<<"balancing of (left) "<<cur->v<<".";
		if(cur->right->b<=0)
		{
			cur->b = (cur->right->b == 0 ? -1 : 0);
			cur->right->b = (cur->right->b == 0 ? 1 : 0);
			smallLeftRotate(cur);
		}
		else
			bigLeftRotate(cur);
	}
}
void CTree::fullbalance(CNode *cur)
{
	if(cur==NULL)
		return;
	while(cur!=root)
	{
		if(cur->b==-1 || cur->b==1)
			return;
		balance(cur);
		cur = cur->par;
	}
	balance(cur);
}
void CTree::smallRightRotate(CNode *cur)
{
	CNode *t = cur->left;
	cur->left = t->right;
	if(cur->left!=NULL)
		cur->left->par = cur;
	if(cur->IsLeft())
	{
		cur->par->left = t;
		t->par = cur->par;
	}
	else if(cur->IsRight())
	{
		cur->par->right = t;
		t->par = cur->par;
	}
	else
	{
		root = t;
		root->par = NULL;
	}
	cur->par = t;
	t->right = cur;
	
}
void CTree::smallLeftRotate(CNode *cur)
{
	CNode *t = cur->right;
	cur->right = t->left;
	if(cur->right!=NULL)
		cur->right->par = cur;
	if(cur->IsLeft())
	{
		cur->par->left = t;
		t->par = cur->par;
	}
	else if(cur->IsRight())
	{
		cur->par->right = t;
		t->par = cur->par;
	}
	else
	{
		root = t;
		root->par = NULL;
	}
	cur->par = t;
	t->left = cur;
}
void CTree::bigLeftRotate(CNode *cur)
{
	//cout<<" bigleft ";	
	if(cur->right->left->b>=0)
	{
		cur->b = 0;
		if(cur->right->left->b == 0)
			cur->right->b = 0;
		else
			cur->right->b = -1;
	}
	else
	{
		cur->right->b = 0;
		cur->b = 1;
	}
	cur->right->left->b = 0;
	smallRightRotate(cur->right);
	smallLeftRotate(cur);
}
void CTree::bigRightRotate(CNode *cur)
{
	//cout<<" bigright ";
	if(cur->left->right->b<=0)
	{
		cur->b = 0;
		if(cur->left->right->b == 0)
			cur->left->b = 0;
		else
			cur->left->b = 1;
	}
	else
	{
		cur->left->b = 0;
		cur->b = -1;
	}
	cur->left->right->b = 0;
	smallLeftRotate(cur->left);
	smallRightRotate(cur);
}

CTree::Iterator::Iterator(CNode *n,CTree *t)
{
	this->n = n;
	this->t = t;
}
CTree::Iterator::Iterator(const Iterator &b)
{
	this->n = b.n;
	this->t = b.t;
}
const char* CTree::Iterator::operator*()
{
	return n->v;
}
void CTree::Iterator::operator++()
{
	n = t->Next(n);
}
void CTree::Iterator::operator++(int)
{
	n = t->Next(n);
}
void CTree::Iterator::operator--()
{
	n = t->Prev(n);
}
void CTree::Iterator::operator--(int)
{
	n = t->Prev(n);
}
int CTree::Iterator::operator==(const Iterator &b)
{
	return n == b.n;
}
int CTree::Iterator::operator!=(const Iterator &b)
{
	return n != b.n;
}
CTree::Iterator CTree::begin()
{
	return Iterator(searchMin(this->root),this);
}
CTree::Iterator CTree::cur(char* v)
{
	return Iterator(search(v),this);
}
CTree::Iterator CTree::end()
{
	return Iterator(NULL,this);
}

//not required function of "neat" output

void CTree::Print(CNode* cur, int n)
{
	if(cur)
	{
		Print(cur->right,n+5);
		for(int i = 0; i < n ; i++)
			printf(" ");
		cout << " " << cur->v << endl;
		Print(cur->left, n+5);
	}
}
CTree::CNode* CTree::NextLeaf(CNode *cur)
{
	if(cur->right == NULL && cur->left == NULL)
	{
		CNode *t = cur;
		Iterator it(t,this);
		while(1)
		{
			++it;
			if(it.n == NULL)
				return NULL;
			if(it.n->left == NULL && it.n->right == NULL)
				return it.n;
		}
	}
	else return NULL;
}
int CTree::pathLen(CNode *cur)
{
	int length=0;
	CNode *t = cur;
	while(t != root)
	{
		length += strlen(t->v);
		t = t->par;
	}
	length += strlen(t->v);
	return length;
}
int CTree::minPath()
{
	if(root == NULL)
		return -1;
	CNode *cur = searchMin(root),*cur_0;
	if(cur->right != NULL)
		cur = cur->right;
	cur_0 = cur;
	int minp = pathLen(cur),len;
	while(1)
	{
		cur = NextLeaf(cur);
		if(cur == NULL)
			break;
		len = pathLen(cur);
		if(len < minp)
		{
			minp = len;
			cur_0 = cur;
		}
	}
	cout<<"Required path: ";
	while(cur_0 != root)
	{
		cout<<cur_0->v<<"<--";
		cur_0 = cur_0->par;
	}
	cout<<cur_0->v<<endl;
	cout<<"Minimal path = ";
	return minp;
}