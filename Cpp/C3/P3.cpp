#include<iostream>
#include <iomanip>
using namespace std;
int main()
{
	float c,f;
	cout<<"please input the temputure"<<endl;
	cin>>f;
	cout<<setiosflags(ios::fixed)<<setpreci sion(2)<<endl;
	c=(f-32)*5/9;
	cout<<c<<endl;
	return 0;
}
