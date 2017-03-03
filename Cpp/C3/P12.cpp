#include<iostream>
#include <cmath>
using namespace std;
int main()
{
	int data,i,m=0,count[5];
	int temp;
	cin>>data;
	temp = data;
	for(i=0;i<4;i++)
	{
		count[i] = data;
		data = data/(10^(i));
		if(data>0) 
		{
			m++;
		}
	}
	cout<<m+1<<endl;
	for(i=0;i<=m;i++)
    count[i] = (int)(temp/pow(10,i))%10;
	for(i=0;i<=m;i++)
	{
		cout<<count[i]<<endl;
	}
	return 0;
	
}
