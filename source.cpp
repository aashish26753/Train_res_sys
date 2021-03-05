#include<iostream>
#include<string>
using namespace std;
class res
{

};
class enq  //Will be inherited from Res class
{
public:
    string T[35]={"1234","Mumbai exp","Delhi","Mumbai","15:00","15:05","150","1235","Kota exp","Delhi","Kota","18:00","18:05","180","1236","Howrah mail","Delhi","Kolkata","19:00","19:05","250","1237","Bandra-gaya exp","Mumbai","Gaya","20:00","20:05","190","1238","Bandra spl","Delhi","Mumbai","13:00","13:05","195"};
    char src[10],dest[10];
    int Tno;
    void get_eq()
    {
        cout<<"Enter Source: ";
        cin>>src;
        cout<<"Enter Destination: ";
        cin>>dest;
    }
    void show_eq()
    {  int flag=0;
        cout<<"Train no.\t"<<"Train name\t"<<"SRC\t"<<"Dest\t"<<"Arr Time\t"<<"Dep Time\t"<<"Avl Seats(3A)\n";
        cout<<"---------\t"<<"----------\t"<<"---\t"<<"----\t"<<"--------\t"<<"--------\t"<<"-------------\n";
        for(int i=0; i<30; i+=7)
        {
            if(src==T[2+i] && dest==T[3+i])
                {
                    cout<<T[i]<<"\t\t"<<T[i+1]<<"\t"<<T[i+2]<<"\t"<<T[i+3]<<"\t"<<T[i+4]<<"\t\t"<<T[i+5]<<"\t\t"<<T[i+6]<<"\n";
                    flag=1;
                }
        }
        if(flag==1)
        {
            int n;
            cout<<"\n*Enter 1 for Booking\n"<<"*Enter 0 to search again\n";
            cin>>n;
            switch(n)
            {
            case 0:
                get_eq();
                show_eq();
                break;
            case 1:
                //Res::get();
                break;
            default:
                cout<<"***Invalid Choice!!***";
            }
        }
        if(flag==0)
        {
            int a;
            cout<<"\n*****No Trains Found*****\n";
            cout<<"----Enter 0 to search again----\n";
            cin>>a;
                if(a==0)
                {
                    get_eq();
                    show_eq();
                }
        }
    }

};
int main()
{
	cout<<"****WELCOME TO INDIAN RAILWAYS****\n\n";
    int choice; enq a;
    cout<<"Enter 1 for Enquiry and Reservation\n"<<"Enter 2 for Cancel Reservation\n";
    cin>>choice;
    switch(choice)
    {
    case 1:
        a.get_eq();
        a.show_eq();
        break;
    case 2:
        break;
    default:
        cout<<"Invalid Response!!!\n";
        break;
    }

}
