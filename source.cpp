#include<iostream>
#include<string>
using namespace std;
class res
{
	public:
	string name_of_cus[100],tno;
	long int con_no;
	int dd,mm,yy,no_of_seat,i;
	int total_fare;
		void get()
		{
		    cout<<"ENTER TRAIN NUMBER: ";
		    cin>>tno;
			cout<<"ENTER THE NUMBER OF PASSENGERS: ";
			cin>>no_of_seat;
			cout<<"ENTER THE NAME: ";
			for(i=0;i<no_of_seat;i++)
			{
			    cin>>name_of_cus[i];
			}
			cout<<"ENTER THE CONTACT NUMBER: ";
			cin>>con_no;
			cout<<"ENTER THE DATE OF JOURNEY(dd/mm/yy): ";
			cin>>dd>>mm>>yy;
		}

		void calculate()
    {
    		if(tno=="1234")
    		total_fare=1752*no_of_seat;
    		else if(tno=="1235")
    		total_fare=1652*no_of_seat;
    		else if(tno=="1236")
    		total_fare=1345*no_of_seat;
    		else if(tno=="1237")
    		total_fare=1274*no_of_seat;
    		else if(tno=="1238")
    		total_fare=1711*no_of_seat;
		}
	void display_fare(char src[], char dest[])
	{
	    cout<<"\n----------------------------------------------\n-----------------------------------------------\n";
		cout<<"TICKET BOOKED!!!"<<endl;
		cout<<"THE DETAILS OF THE TRAVEL ARE:"<<endl;
	    cout<<"Name:\n";
		for(i=0;i<no_of_seat;i++)
		{
		    cout<<i+1<<" "<<name_of_cus[i]<<endl;
		}
		cout<<"SOURCE: "<<src<<endl;
		cout<<"DESTINATION: "<<dest<<endl;
		cout<<"DATE OF JOURNEY:"<<dd<<"/"<<mm<<"/"<<yy<<endl;
		cout<<"TOTAL FARE: Rs. "<<total_fare<<endl;
		cout<<"TOTAL NUMBER OF SEATS BOOKED: "<<no_of_seat<<endl;
	}
};
class enq: public res  //Will be inherited from Res class
{
public:
    string T[35]={"1234","Mumbai exp","Delhi","Mumbai","15:00","15:05","150","1235","Kota exp","Delhi","Kota","18:00","18:05","180","1236","Howrah mail","Delhi","Kolkata","19:00","19:05","250","1237","Bandra-gaya exp","Mumbai","Gaya","20:00","20:05","190","1238","Bandra spl","Delhi","Mumbai","13:00","13:05","195"};
    char src[10],dest[10];
    void get_eq()
    {
        cout<<"ENTER SOURCE: ";
        cin>>src;
        cout<<"ENTER DESTINATION: ";
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
                res::get();
                res::calculate();
                res::display_fare(src,dest);
                break;
            default:
                cout<<"*Invalid Choice!!*";
            }
        }
        if(flag==0)
        {
            int a;
            cout<<"\n*No Trains Found*\n";
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
	cout<<"WELCOME TO INDIAN RAILWAYS\n\n";
    int choice; enq a; res r;
    cout<<"ENTER 1 FOR ENQUIRY AND RESERVATION\n"<<"ENTER 2 TO CANCEL RESERVATION\n";
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
        cout<<"INVALID RESPONSE!!!\n";
        break;
    }

}
