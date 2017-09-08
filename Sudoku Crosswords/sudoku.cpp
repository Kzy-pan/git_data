#include<iostream>
#include<fstream>
#include<sstream>
#include <cstdlib>
#include<ctime>
#include<cstring>
using namespace std;
struct Nod
{
	struct Nod* next[9];
};
ofstream outfile("sudoku.txt",ios::out);//����������ļ��� 
int main(int argc, char** argv)
{	
	void ShuffleArray_Fisher_Yates(char* arr, int len);//���������ַ���������� 
	void print_shudo(char arr[][9]);//�����ɵ��������̴����ļ��� 
	void generator_shudo(struct Nod* r);//���������������� 
	bool isNum(string str);//�ж��Ƿ�Ϊ�����֣����ڲ�������
	bool check(char arr[][3],struct Nod* r,char ch[4]);
	int tmp;
	int j=0;
	struct Nod* root =new struct Nod;
	for(int i =0;i<9;i++)
		root->next[i]=NULL;
	if(!outfile)
	{//�ļ���ʧ���Լ���ʾ 
		cerr<<"open error!"<<endl;
		exit(1);
	}
	srand(time(0));//����������� 
	if(argv[1]&&argc<=3) 
	{
		if(!strcmp(argv[1],"-c"))//���ڲ�����ʽ���ж� 
		{
			string str=argv[2];
			if(isNum(str))
			{
				j=atoi(str.c_str());	
				for(int i=0;i<j;i++)
				{
					generator_shudo(root);
				}
			}
			else cerr<<"bad input"<<endl;
		}
		else
			cerr<<"need '-c'"<<endl;
	}
	else
		cerr<<"The wrong format"<<endl;
	outfile.close();
	cout<<"finish"<<endl;
	return 0; 
}
void ShuffleArray_Fisher_Yates(char* arr, int len) 
{ 
	int i = len, j; 
	char temp; 
	
	if ( i == 0 ) return; 
	while ( --i ) { 
	j = rand() % (i+1); 
	temp = arr[i]; 
	arr[i] = arr[j]; 
	arr[j] = temp; 
	} 
}
void print_shudo(char arr[][9])
{
	int i,j;
	for(i=0;i<9;i++)
	{	
		for(j=0;j<9;j++)
		{
			//cout<<arr[i][j]<<' ';
			outfile<<arr[i][j]<<' ';
		}
		//cout<<endl;
		outfile<<endl;
	}
	outfile<<endl;
}
bool check(char arr[][3],struct Nod* r,char ch[4])
{
	struct Nod* p=r;
	bool jd=0;
	for(int i=1;i<9;i++)
	{
		int j=arr[i/3][i%3]-'0'; 
		if(p->next[j-1])
			p=p->next[j-1];
		else
		{
			jd=1;
			struct Nod* q=new struct Nod;
			for(int i =0;i<9;i++)
				q->next[i]=NULL;
			p->next[j-1]=q;
			p=q;
		}
	}
	for(int i=0;i<4;i++)
	{
		int j=ch[i];
		if(p->next[j])
			p=p->next[j];
		else
		{
			jd=1;
			struct Nod* q=new struct Nod;
			for(int i =0;i<9;i++)
				q->next[i]=NULL;
			p->next[j]=q;
			p=q;
		}
	}
	return jd;
}
void generator_shudo(struct Nod* r)
{
	char ch[4];
	char shudo[9][9];
	char mini[3][3];
	for(int i=0;i<9;i++)	
		for(int j=0;j<9;j++)
			shudo[i][j]='0';
	shudo[0][0]='2';
	mini[0][0]='2';//��ʼ�� 
	char a[8]={'1','3','4','5','6','7','8','9'};
	while(1)
	{
	a[0]='1';a[1]='3';a[2]='4';a[3]='5';a[4]='6';a[5]='7';a[6]='8';a[7]='9';		
	ShuffleArray_Fisher_Yates(a,8);//�õ�������������һ�� 
	for(int i=1;i<9;i++)
	{
		mini[i/3][i%3]=a[i-1];
		shudo[i/3][i%3]=a[i-1];
	}//����һ������������mini 

	for(int i=3;i<9;i++)
	{
		shudo[0][i]=mini[i/3][i%3];
		shudo[1][i]=mini[(i/3+1>2)?0:i/3+1][i%3];
		shudo[2][i]=mini[i/3-1][i%3];
		shudo[i][0]=mini[i%3][i/3];
		shudo[i][1]=mini[i%3][(i/3+1>2)?0:i/3+1];
		shudo[i][2]=mini[i%3][i/3-1];
	}//����mini���ڶ����������� �����Ĺ��Լ����߹� 
	for(int i=0;i<9;i++)
	{
		mini[i/3][i%3]=shudo[i/3+3][i%3];
	}//�����Ĺ������ָ��µ�mini�� 
	for(int i=3;i<9;i++)
	{
		shudo[3][i]=mini[i/3][i%3];
		shudo[4][i]=mini[(i/3+1>2)?0:i/3+1][i%3];
		shudo[5][i]=mini[i/3-1][i%3];
	}//����mini�����幬��������
	for(int i=0;i<9;i++)
	{
		mini[i/3][i%3]=shudo[i/3+6][i%3];
	}//�����߹������ָ��µ�mini�� 
	for(int i=3;i<9;i++)
	{
		shudo[6][i]=mini[i/3][i%3];
		shudo[7][i]=mini[(i/3+1>2)?0:i/3+1][i%3];
		shudo[8][i]=mini[i/3-1][i%3];
	}//����mini���ڰ˹����ھŹ�
	for(int j=1;j<3;j++)
	{
		int jd=rand()%4;
		ch[j-1]=jd;
		if(jd)
			for(int i=0;i<9;i++)
			{
				char tmp=shudo[jd-1+j*3][i];
				shudo[jd-1+j*3][i]=shudo[(jd>2?0:jd)+j*3][i];
				shudo[(jd>2?0:jd)+j*3][i]=tmp;
			}
	}//���ڵ�4-6�У���7-9�н��жԵ� 
	for(int j=1;j<3;j++)
	{
		int jd=rand()%4;
		ch[j+1]=jd;
		if(jd)
			for(int i=0;i<9;i++)
			{
				char tmp=shudo[i][jd-1+j*3];
				shudo[i][jd-1+j*3]=shudo[i][(jd>2?0:jd)+j*3];
				shudo[i][(jd>2?0:jd)+j*3]=tmp;
			}
	}//���ڵ�4-6�У���7-9�н��жԵ�
	if(check(mini,r,ch)) break;
	}
	print_shudo(shudo);
}
bool isNum(string str)  
{  
    stringstream sin(str);  
    double d;  
    char c;  
    if(!(sin >> d))  
        return false;  
    if (sin >> c)  
        return false;  
    return true;  
}

