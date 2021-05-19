#include<iostream>
#include<string>
#include<cstdlib> //for rand() fn (generates random int).
#include<unistd.h>
#include<fstream>
using namespace std;
class Train
{
protected:
    string T[1000];
    int k=0;
    ofstream fout;
    ifstream fin;
public:
    //For loading Trains data in the string array from file at the starting of program.
    void load()
    {
        short loop=0;
        string line;
        string data;
        int i=0;
        ifstream myfile("Train_list.txt");
        if (myfile.is_open())
        {
            while(!myfile.eof())
        {
            getline(myfile,line);
            data=line;
            T[i]=data;
            i++;
            loop++;
        }
            k=i;
            myfile.close();
    }
    else cout<<"can't open the file";
    system("PAUSE");
    }

    //Function adds new trains in the database in administrator mode
    void add()
    {
        int i,j;
        string d[7];
        fout.open("Train_list.txt",ios::app);
        if(!fout)
        {
            cout<<"ERROR IN OPENING OF FILE\n";
        }
        cout<<"Enter Train no: ";
        cin>>d[0];
        fout<<d[0]<<"\n";
        cout<<"Enter Train name:";
        cin>>d[1];
        fout<<d[1]<<"\n";
        cout<<"Enter Source:";
        cin>>d[2];
        fout<<d[2]<<"\n";
        cout<<"Enter Destination:";
        cin>>d[3];
        fout<<d[3]<<"\n";
        cout<<"Enter Arrival time: ";
        cin>>d[4];
        fout<<d[4]<<"\n";
        cout<<"Enter Departure time: ";
        cin>>d[5];
        fout<<d[5]<<"\n";
        cout<<"Enter Avl seats: ";
        cin>>d[6];
        fout<<d[6]<<"\n";

        for(i=k,j=0;i<k+7,j<7;i++,j++)
        {
            T[i]=d[j];
        }
        k=i;
        fout.close();
    }

    //Function shows the train list stored in the database
    void show()
    {
        int i;
        cout<<"Train no.\t"<<"Train name\t"<<"Boarding\t"<<"Dest\t"<<"Arr Time\t"<<"Dep Time\t"<<"Avl Seats(3A)\n";
        cout<<"---------\t"<<"----------\t"<<"--------\t"<<"----\t"<<"--------\t"<<"--------\t"<<"-------------\n";
        for(int i=0; i<k+7; i+=7)
        {
                cout<<T[i]<<"\t\t"<<T[i+1]<<"\t"<<T[i+2]<<"\t\t"<<T[i+3]<<"\t"<<T[i+4]<<"\t\t"<<T[i+5]<<"\t\t"<<T[i+6]<<endl;
        }
    }
};
class res: virtual public Train
{
	public:
	string name_of_cus[13],tno;
	long long int con_no;
	int dd,mm,yy,no_of_seat,i,total_fare;

	//Function gets user details for reservation
		void get()
		{
		    cout<<"ENTER TRAIN NUMBER: ";
		    cin>>tno;
			cout<<"ENTER THE NUMBER OF PASSENGERS: ";
			cin>>no_of_seat;
			cout<<"ENTER THE FIRST_NAME and LAST NAME: ";
			for(i=0;i<no_of_seat;i++)
			{
			    cin>>name_of_cus[i];
			    cin>>name_of_cus[i+no_of_seat];
			}
			con:cout<<"ENTER THE CONTACT NUMBER: ";
			cin>>con_no;
			if(con_no<10)
            {
                cout<<"Enter valid contact number";
                goto con;
            }
			cout<<"ENTER THE DATE OF JOURNEY(dd/mm/yy): ";
			cin>>dd>>mm>>yy;
		}

        //Function calculates total fare based on number of passengers
		void calculate()
        {
            int tno_int,i;
            tno_int=stoi(tno);
            tno_int=tno_int/10000;
            if(tno_int==1)
                total_fare=1550*no_of_seat;
            else if(tno_int==0)
                total_fare=2025*no_of_seat;
		}

		//Function displays all the relevant data to the user before proceeding to payment
	void display_fare(string src, string dest)
	{
	    fout.open("Res.txt",ios::app);
	    if(!fout)
        {
            cout<<"\nCan't Open File\n";
        }
	    long long int pnr=4238507112+rand();
	    cout<<"\n----------------------------------------------\n-----------------------------------------------\n";
		cout<<"THE DETAILS OF THE TRAVEL ARE:"<<endl;
		cout<<"PNR: "<<pnr<<endl;
		fout<<pnr<<endl;
		cout<<"Train no.: "<<tno<<endl;
		fout<<tno<<endl;
	    cout<<"Name of passengers:\n";
		for(i=0;i<no_of_seat;i++)
		{
		    cout<<i+1<<" "<<name_of_cus[i]<<" "<<name_of_cus[i+no_of_seat]<<endl;
		    fout<<i+1<<" "<<name_of_cus[i]<<" "<<name_of_cus[i+no_of_seat]<<endl;
		}
		cout<<"SOURCE: "<<src<<endl;
		fout<<src<<endl;
		cout<<"DESTINATION: "<<dest<<endl;
		fout<<dest<<endl;
		cout<<"DATE OF JOURNEY:"<<dd<<"/"<<mm<<"/"<<yy<<endl;
		fout<<dd<<"/"<<mm<<"/"<<yy<<endl;
		cout<<"TOTAL NUMBER OF SEATS BOOKED: "<<no_of_seat<<endl;
		fout<<no_of_seat<<endl;
		cout<<"TOTAL FARE: Rs. "<<total_fare<<endl;
		fout.close();
	}

	//Function updates seats in the database after reservation of seats.
	void updated_seats_after_res()
	{
	    int i,cseats,useats;  //cseats:current seats, useats=updated seats;
	    for(i=0;i<k+7;i+=7)
        {
            if(T[i]==tno)
            {
                cseats=stoi(T[i+6]);   //stoi fn converts string to int.
                useats=cseats-no_of_seat;
                T[i+6]=to_string(useats);
            }
        }
        fout.open("Train_list.txt");
            if(!fout)
                cout<<"\nCan't Open File\n";
            for(i=0;i<k+7;i++)
            {
                fout<<T[i]<<endl;           //Storing updated data
            }
            fout.close();
	}
};
class payment:virtual public res
{
public:
    //Function to get details from user, how he/she wants to pay? and completing the transaction
    void get()
    {
    cout<<"\n-----------------------------------\nWELCOME TO PAYMENT GATEWAY\n-----------------------------------\n";
    cout<<"Total amount to be paid: Rs."<<total_fare;
    int choice,exp,cvv,otp;
    long long int crd_no;
    string upi;
    cout<<"\n********You want to pay through?********\n";
    cout<<" 1. Debit card \n 2. Credit Card \n 3. UPI \n";
    cin>>choice;
    switch(choice)
    {
    case 1:
    case 2:
        cout<<"\nCard no.: ";
        cin>>crd_no;
        cout<<"Expiry (mmyy): ";
        cin>>exp;
        cout<<"CVV: ";
        cin>>cvv;
        cout<<"Connecting to payment gateway";
        for(int i=0; i<5; i++)
        {
            sleep(1);
            cout<<".";
        }
        cout<<"\nEnter OTP: ";
        cin>>otp;
        cout<<"Connecting to the Bank Server";
        for(int i=0; i<6; i++)
        {
            sleep(1);
            cout<<".";
        }
        cout<<"\n\n--------------------------------\n|    Transaction Successful    |\n--------------------------------\n";
        break;
    case 3:
        cout<<"\nUPI id: ";
        cin>>upi;
        cout<<"Check your UPI payment gateway and authorise payment\n";
        cout<<"Connecting to the Bank Server";
        for(int i=0; i<10; i++)
        {
            sleep(1);
            cout<<".";
        }
        cout<<"\n\n--------------------------------\n|    Transaction Successful    |\n--------------------------------\n";
        break;
    }
    }
};
class can: virtual public res
{
public:
    int i;
    string pnr_new,trno;
    //Function gets details of ticket that user wants to cancel and cancels the ticket
    void cancel()
    {
        string remove1,fetch;
        int p,n,flag=0;
        string line,line2;
        ifstream fin,tin;
        tin.open("Res.txt");
        ofstream temp;
        temp.open("temp.txt");
        cout<<"ENTER THE PNR NUMBER: ";
        cin>>pnr_new;
        cout<<"Enter No. of passengers: ";
        cin>>n;
        p=5+n;
        while (getline(tin,line2))
        {
            if(flag==1)
                {
                    trno=fetch;
                    break;
                }
            if (line2 == pnr_new)
            {
                getline(tin,fetch);
                flag=1;
                continue;
            }
        }
        tin.close();
        fin.open("Res.txt");
        while (getline(fin,line))
        {
            if (line == pnr_new)
            {
                while(p--)
                {
                    getline(fin,remove1);
                }
            }
            else
                temp << line << endl;
        }
        temp.close();
        fin.close();
        remove("Res.txt");
        rename("temp.txt","Res.txt");
        cout<<"\n\n---------------------------\n|    TICKET CANCELLED    |\n---------------------------\n";
    }

    //Function updates seats in the database after cancellation of tickets
    void updated_seats_after_can()
	{
	    int i,cseats,useats;  //cseats:current seats, useats=updated seats;
	    for(i=0;i<k+7;i+=7)
        {
            if(T[i]==trno)
            {
                cseats=stoi(T[i+6]);   //stoi fn converts string to int.
                useats=cseats+no_of_seat;
                T[i+6]=to_string(useats);
            }
        }
        fout.open("Train_list.txt");
            if(!fout)
                cout<<"\nCan't Open File\n";
            for(i=0;i<k+7;i++)
            {
                fout<<T[i]<<endl;           //Storing updated data
            }
            fout.close();
	}
};
class enq:virtual public Train
{
public:
    string src,dest;
    //Function get the details from users about from where to where they want to book train
    void get_eq()
    {
        cout<<"ENTER BOARDING STATION: ";
        cin>>src;
        cout<<"ENTER DESTINATION: ";
        cin>>dest;
    }

    //Function shows all the trains on that route
    int show_eq()
    {  int flag=0;
        cout<<"Train no.\t"<<"Train name\t"<<"Boarding\t"<<"Dest\t"<<"Arr Time\t"<<"Dep Time\t"<<"Avl Seats(3A)\n";
        cout<<"---------\t"<<"----------\t"<<"--------\t"<<"----\t"<<"--------\t"<<"--------\t"<<"-------------\n";
        for(int i=0; i<k+7; i+=7)
        {
            if(src==T[2+i] && dest==T[3+i])
                {
                    cout<<T[i]<<"\t\t"<<T[i+1]<<"\t"<<T[i+2]<<"\t\t"<<T[i+3]<<"\t"<<T[i+4]<<"\t\t"<<T[i+5]<<"\t\t"<<T[i+6]<<"\n";
                    flag=1;
                }
        }
        return flag;
    }
};

//This class allows users to book food on their seats using their PNR no.
class irctcfood
{
public:
    double AmountOfSaleSamosa = 0;
    double AmountOfSaleChowmin = 0;
    double AmountOfSaleChicken = 0;

    double AmountOfSaleCoke = 0;
    double AmountOfSaleIt = 0;
    double AmountOfSaleTea= 0;
    double AmountOfSaleCoffee= 0;

    void food()
    {

    long long int PNR;
    int meal;
    int meal_Quantity;
    int drinks;
    int drinks_Quantity;

    double Samosa = 25.00;
    double Chowmin = 100.00;
    double Chicken = 150.00;

    double coke = 40.00;
    double it = 20.00;
    double Tea = 20.00;
    double Coffee = 20.00;

    cout<<"\n\tIRCTC E-Catering\t\n\n"<<endl<<"Get restaurant food delivered right at your Seat"<<endl;
    cout<<"An unofficial program of Indian Railways and IRCTC to book food on Trains.\n"<<endl;
    cout<<"Because of a network error,We are not accepting Online Payments. \nYour Inconvenience is deeply Regretted.\n\n"<<endl;

    cout<<"Enter Your PNR Number"<<endl;
    cin>>PNR;
    cout<<"Get Good Food Delivery in Train\n\n\n\n"<<endl;
    cout<<"\t\t *MEAL* \t\n";
    cout<<" [1] Samosa..............Rs 25.00\n"
          " [2] Chowmin.............Rs 100.00\n"
          " [3] Chicken Biryani.....Rs 150.00\n\n";
    cout<<"What is your meal (Choose any one): ";
    cin>>meal;
    cout<<"How many pieces ?: ";
    cin>>meal_Quantity;
    cout<<"\n\n\t\t *DRINKS* \t\t\n";
    cout<<" [1] Coke......................Rs 40.00\n"
          " [2] Packaged Water............Rs 20.00\n"
          " [3] Tea.......................Rs 20.00\n"
          " [4] Coffee....................Rs 20.00\n\n";
    cout<<"What is your drinks: ";
    cin>>drinks; cout<<"How many pieces?: ";
    cin>>drinks_Quantity;
    cout<<"\n\t *Item Ordered*\t\t\n\n";
    switch (meal)
        {
            case 1:
                cout<<" Samosa..............Rs 25.00 X "<<meal_Quantity<<" = "<<meal_Quantity * Samosa<<"\n";
                AmountOfSaleSamosa = meal_Quantity * Samosa;
            break;
            case 2:
                cout<<" Chowmin...........Rs 100.00 X "<<meal_Quantity<<" = "<<meal_Quantity * Chowmin<<"\n";
                AmountOfSaleChowmin = meal_Quantity * Chowmin;
            break;
            case 3:
                cout<<" Chicken Biryani.....Rs 150.00 X "<<meal_Quantity<<" = "<<meal_Quantity * Chicken<<"\n";
                AmountOfSaleChicken = meal_Quantity * Chicken;
            break;
        }
        {
             switch (drinks)
                {
                case 1:
                    cout<<" Coke................Rs 40.00 X "<<drinks_Quantity<<" = "<<drinks_Quantity * coke<<"\n\n";
                    AmountOfSaleCoke = drinks_Quantity * coke;
                    break;


                case 2:
                    cout<<" Packaged Water............Rs 20.00 X "<<drinks_Quantity<<" = "<<drinks_Quantity * it<<"\n\n";
                    AmountOfSaleIt = drinks_Quantity * it;
                    break;

                case 3:
                    cout<<" Tea............Rs 20.00 X "<<drinks_Quantity<<" = "<<drinks_Quantity * Tea<<"\n\n";
                    AmountOfSaleTea = drinks_Quantity * Tea;
                    break;

                case 4:
                    cout<<" Coffee............Rs 20.00 X "<<drinks_Quantity<<" = "<<drinks_Quantity * Coffee<<"\n\n";
                    AmountOfSaleCoffee = drinks_Quantity * Coffee;
                    break;
                }
        }
    }
           void total()
           {
               double cash;
               double total1=0;
               total1 = total1 + AmountOfSaleSamosa + AmountOfSaleChowmin + AmountOfSaleChicken + AmountOfSaleCoke + AmountOfSaleIt+ AmountOfSaleTea+AmountOfSaleCoffee;

            cout<<"Total Amount to be paid : "<<total1<<"\n";
            cout<<"Because of a network error,We are not accepting Online Payments so Kindly use Cash"<<endl;
            cout<<"How much amount you are giving in cash: ";
            cin>>cash;
            cout<<"Change: "<< cash - total1<<"\n\n";
            cout<<"ENJOY YOUR FOODS\n\n\n";
            cout<<"\n\n\t-----------------------\n";
            cout<<"\t  Have a Safe Journey";
            cout<<"\n\t-----------------------\n";
           }
};

//This class is used to drive the whole program
class driver:public payment, public enq, public can, public irctcfood
{
    public:
    //This function handles all the driving operations of the program
    void drive()
    {
    Train::load();
    cout<<"WELCOME TO INDIAN RAILWAYS\n\n";
    int choice,cont,f,admode,n;
    string pass="abcd",pa;
   mm: cout<<"\nEnter 1 for Administrator mode\nEnter 2 for Customer mode\nEnter 0 to exit\n";
    cin>>admode;
    switch(admode)
    {
    case 0:
        break;
    case 1:
        cout<<"\nEnter Administrator password: ";
        cin>>pa;
        if(pa==pass)
            {
                cout<<"\nEnter 1 to add trains\nEnter 2 to show trains\nEnter 0 to exit\n";
                cin>>n;
                switch(n)
                {
                case 1:
                    cout<<"\nEnter how many trains you want to add: ";
                    int t;
                    cin>>t;
                    while(t--)
                    {
                        Train::add();
                    }
                    cout<<"\nEnter 9 to show trains\nEnter 0 to return to main menu\n";
                    int mm;
                    cin>>mm;
                    if(mm==0)
                        goto mm;
                    else if(mm==9)
                        goto s;
                    break;
                case 2:
                    s: Train::show();
                    goto mm;
                    break;
                default:
                    goto mm;
                    break;
            }}
            else
            {
                cout<<"\n****Wrong password****\n";
                goto mm;
            }
            break;
    case 2:
again: cout<<"ENTER 1 FOR ENQUIRY AND RESERVATION\nENTER 2 TO CANCEL RESERVATION\nENTER 3 TO BOOK FOOD\n";
       cin>>choice;

    switch(choice)
    {
    case 1:
                enq::get_eq();
                f=enq::show_eq();
                if(f==1)
        {
            int n,cont;
      book: cout<<"\n*Enter 1 for Booking\n"<<"*Enter 0 to search again\n*Enter 9 to EXIT\n";
            cin>>n;
            switch(n)
            {
            case 0:
                enq::get_eq();
                f=enq::show_eq();
                if(f==1)
                    goto book;
                break;
            case 1:
                res::get();
                res::calculate();
                res::display_fare(enq::src,enq::dest);
                payment::get();
                res::updated_seats_after_res();
                break;
            case 9:
                break;
            default:
                cout<<"*Invalid Choice!!*";
                goto book;
                break;
            }
        }
        if(f==0)
        {
            int b;
            cout<<"\n*No Trains Found*\n";
            cout<<"----Enter 0 to search again----\n";
            cin>>b;
                if(b==0)
                {
                    enq::get_eq();
                    f=enq::show_eq();
                    if(f==1)
                        goto book;
                }
        }
            cout<<"\n\n-----Do u want to Book/Enquire more?-----\n*Enter 1 to CONTINUE\n*Enter 0 to EXIT\n";
            cin>>cont;
            if(cont==1)
                goto again;
            else
                break;
        break;
    case 2:
        can::cancel();
        can::updated_seats_after_can();
        break;
    case 3:
        irctcfood::food();
        irctcfood::total();
        break;
    default:
        cout<<"INVALID RESPONSE!!!\n";
        goto again;
        break;
    }
    default:
        goto mm;
        break;
    }
    }
};

int main()
{
    driver dr1;
    dr1.drive();
}
