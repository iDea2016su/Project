 #include <iostream>
 #include <stdlib.h>
 #include <iomanip>
 using namespace std;
 int main()
 {
 	float r,s,v,l,rt=0;
 	char t;
 	while(1)
 	{ 
    	rt=1; 
	 	while(1)
	 	{
		 	cout<<"Please input the radius"<<endl;
	        cin>>r;
	        if(r>=0) break;
	        { cout<<"The radius is positive, please input again!"<<endl;}
	    
		 }
		 system("Cls");
		 cout<<"A: caculate V"<<endl<<endl;
		 cout<<"B: caculate S"<<endl<<endl;
		 cout<<"C: caculate L"<<endl<<endl;
		 while(1)
		 {
			cout<<"Please chose the task"<<endl;
			cin>>t;
			if(t=='A'||t=='B'||t=='C') break;
			else cout<<"Please input the righr number"<<endl;
		 }
		cout<<setiosflags(ios::fixed)<<setprecision(2)<<endl;
		while(rt)
		{
	
		 switch (t)
		 {
			case 'A':cout<<(4/3*3.14*r*r*r)<<endl;rt=0;break;
			case 'B':cout<<(4*3.14*r*r)<<endl;rt=0;break;
			case 'C':cout<<(2*r*3.14)<<endl;rt=0;break; 
			default:break;
	     }
        } 
//	 system("Cls");
	 } 

  } 
