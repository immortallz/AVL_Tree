#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class CTree
{
public:
	class CNode
	{
	public:
		char *v;
		int b;
		CNode *par,*left,*right;
		CNode();
		CNode(char* v,CNode *par);
		~CNode();
		bool IsLeft()const;
		bool IsRight()const;
		friend class CTree;
	};
	class Iterator
	{
	public:
		CNode *n;
		CTree *t;
	public:
		Iterator(CNode *n,CTree *t);
		Iterator(const Iterator &b);
		const char* operator*();
		void operator++();
		void operator++(int);
		void operator--();
		void operator--(int);
		int operator==(const Iterator &b);
		int operator!=(const Iterator &b);
		friend class CTree;
	};
public:
	CNode *root;
	int n;
public:
	CTree();
	void SetZero();
	~CTree();
	Iterator begin();
	Iterator end();
	Iterator cur(char* v);
	void Clean();
	int IsEmpty();
	bool insert(char *v);
	bool remove(char *v);
	bool remove(CNode *cur);
	CNode* search(char *v);
	CNode* searchMin(CNode *cur);
	CNode* searchMax(CNode *cur);
	int GetSize();
	CNode* Next(CNode *cur);
	CNode* Prev(CNode *cur);
	void balance(CNode *cur);
	void fullbalance(CNode *cur);
	void smallLeftRotate(CNode *cur);
	void smallRightRotate(CNode *cur);
	void bigLeftRotate(CNode *cur);
	void bigRightRotate(CNode *cur);
	void Print(CNode* cur, int n);
	CNode* NextLeaf(CNode *cur);
	int pathLen(CNode *cur);
	int minPath();
};
