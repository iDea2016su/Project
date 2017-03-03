#include<iostream>
using namespace std;
int main()
{
	int data,i,m=0,count[5];
	cin>>data;
	for(i=0;i<4;i++)
	{
		count[i] = data/(10^(4-i));
	}
	count[4] = data%1;
	for(i=0;i<5;i++)
	{
		if(count[i]>0)
		m++	;
	}
	cout<<i<<endl;
	for(i=0;i<m;i++)
	{
		data=data-10^(m-1);
		cout<<data<<endl;
	}
	
}
