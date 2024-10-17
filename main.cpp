#include "r.h"
#include <time.h>
#define N 10 //number of strings
#define NN 1000 //number of tests

void test_insert(int i)
{
	int j,k;
	srand(time(NULL)+i);
	CTree a;
	char **str = new char*[N];
	int *length = new int[N];
	for (j=0;j<N;j++)
	{
		length[j] = rand()%i + 1;
		str[j] = new char[length[j]+1];
	}
	for(j=0;j<N;j++)
	{
		for(k=0;k<length[j];k++)
			str[j][k]=rand()%26+97;
		str[j][length[j]] = '\0';
	}
	for(j=0;j<N-1;j++)
		a.insert(str[j]);
	if(i == 10)
	{
		cout<<"Tree before inserting "<<str[N-1]<<"."<<endl;
		a.Print(a.root,0);
		a.insert(str[N-1]);
		cout<<"Tree after inserting "<<str[N-1]<<"."<<endl;
		a.Print(a.root,0);
	}
	for(j=0;j<N;j++)
		free(str[j]);
	free(str);
	free(length);
}
void test_remove(int i)
{
	int j,k;
	srand(time(NULL)+i+NN);
	CTree a;
	char **str = new char*[N];
	int *length = new int[N];
	for (j=0;j<N;j++)
	{
		length[j] = rand()%i + 1;
		str[j] = new char[length[j]+1];
	}
	for(j=0;j<N;j++)
	{
		for(k=0;k<length[j];k++)
			str[j][k]=rand()%26+97;
		str[j][length[j]] = '\0';
	}
	for(j=0;j<N;j++)
		a.insert(str[j]);
	if(i == 10)
	{
		int t = rand()%N;
		cout<<"Tree before removing "<<str[t]<<"."<<endl;
		a.Print(a.root,0);
		a.remove(a.search(str[t]));
		cout<<"Tree after removing "<<str[t]<<"."<<endl;
		a.Print(a.root,0);
	}
	for(j=0;j<N;j++)
		free(str[j]);
	free(str);
	free(length);
	/*for(j=0;j<N;j++)
		if(a.search(str[j])==NULL)
		{
			for(j=0;j<N;j++)
				free(str[j]);
			free(str);
			free(length);
			return -1;
		}
		else
		{
			a.remove(a.search(str[j]));
			if(a.search(str[j])!=NULL)
			{
				for(j=0;j<N;j++)
					free(str[j]);
				free(str);
				free(length);
				return -1;
			}
		}
	for(j=0;j<N;j++)
		free(str[j]);
	free(str);
	free(length);
	return 0;*/
}
int test_getsize()
{
	int j;
	CTree a;
	char** str = new char*[26];
	for (j=0;j<26;j++)
	{
		str[j] = new char[2];
		str[j][0]=97+j;
		str[j][1]='\0';
	}
	for (j=0;j<26;j++)
	{
		if(a.GetSize()!=j)
		{
			for(j=0;j<N;j++)
				free(str[j]);
			free(str);
			return -1;
		}
		a.insert(str[j]);
	}
	for(j=0;j<N;j++)
		free(str[j]);
	free(str);
	return 0;
}
void test_iterator()
{
	int j,k;
	srand(time(NULL)+2*NN);
	CTree a;
	char **str = new char*[10];
	int *length = new int[10];
	for (j=0;j<10;j++)
	{
		length[j] = rand()%5 + 1;
		str[j] = new char[length[j]+1];
	}
	for(j=0;j<10;j++)
	{
		for(k=0;k<length[j];k++)
			str[j][k]=rand()%26+97;
		str[j][length[j]] = '\0';
	}
	for(j=0;j<10;j++)
		a.insert(str[j]);
	int ind = rand()%10;
	auto itr = a.cur(str[ind]);
	cout<<"\nTree from "<<str[ind]<<" to end:"<<endl;
	for(auto it = itr;it!=a.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<'\n';
	cout<<"\nTree from begin to "<<str[ind]<<" :"<<endl;
	for(auto it = a.begin();it!=itr;++it)
	{
		cout<<*it<<" ";
	}
	cout<<'\n';
	cout<<"\nFull tree:"<<endl;
	for (auto it = a.begin();it!=a.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<'\n';
	for(j=0;j<10;j++)
		free(str[j]);
	free(str);
	free(length);
}
void test_minpath(int i)
{
	int j,k;
	srand(time(NULL)+3*NN+i);
	CTree a;
	char **str = new char*[10];
	int *length = new int[10];
	for (j=0;j<10;j++)
	{
		length[j] = rand()%7 + 1;
		str[j] = new char[length[j]+1];
	}
	for(j=0;j<10;j++)
	{
		for(k=0;k<length[j];k++)
			str[j][k]=rand()%26+97;
		str[j][length[j]] = '\0';
	}
	for(j=0;j<10;j++)
		a.insert(str[j]);
	cout<<"\nTree #"<<i+1<<":"<<endl;
	a.Print(a.root,0);
	cout<<a.minPath()<<endl;
	for(j=0;j<10;j++)
		free(str[j]);
	free(str);
	free(length);
}

/*void time_insert(int n)
{
	int j,k;
	srand(time(NULL)+3*NN);
	CTree a;
	char **str = new char*[n];
	int *length = new int[n];
	for (j=0;j<n;j++)
	{
		length[j] = rand()%24 + 1;
		str[j] = new char[length[j]+1];
	}
	for(j=0;j<n;j++)
	{
		for(k=0;k<length[j];k++)
			str[j][k]=rand()%26+97;
		str[j][length[j]] = '\0';
	}
	for(j=0;j<n;j++)
		a.insert(str[j]);

	clock_t start,stop;
	char* p = new char[26];
	for(k=0;k<26;k++)
		p[k]=rand()%26+97;
	p[26] = '\0';
	start = clock();
	a.insert(p);
	stop = clock();
	for(j=0;j<n;j++)
		free(str[j]);
	free(str);
	free(length);
	free(p);
	printf("%ld ",(stop-start));
}*/

int main()
{
	int i;
	cout<<"~~~~~~~~~~~~~~~~~~~~~~TEST INSERT~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	for(i=1;i<=NN;i++)
		test_insert(i);
	cout<<"\ntest_insert is over.\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~TEST REMOVE~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	for(i=1;i<=NN;i++)
		test_remove(i);
	cout<<"\ntest_remove is over.\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~TEST GETSIZE~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	if(test_getsize()!=0)
		cout<<"\ntest_getsize is not ok.\n";
	else
		cout<<"\ntest_getsize is ok.\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~TEST ITERATOR~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	test_iterator();
	cout<<"\ntest_iterator is over.\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~TEST MINPATH~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	for(i=0;i<4;i++)
		test_minpath(i);
	cout<<"\ntest_minpath is over.\n\n";
	return 0;
}