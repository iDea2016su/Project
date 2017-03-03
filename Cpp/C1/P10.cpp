#include<iostream>
using namespace std;
int main()
{
	int a,b,c;
	void sort(int* x,int* y,int* z);
	cin>>a>>b>>c;
	sort(&a,&b,&c);
	cout<<a<<b<<c<<endl;
	return 0;
}
void sort(int* x,int* y,int* z)
{
	int temp;
	if(*x>=*y) { temp = *x; *x = *y;*y = temp;}
	if(*y>=*z) { temp = *y; *y = *z;*z = temp;}
	if(*x>=*y) { temp = *x; *x = *y;*y = temp;}
	
} 
