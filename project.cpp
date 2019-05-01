#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>

using namespace std;
/*
jygjhgb
hhhhhhhhhhhhhhh
jjjjjjjjjjjjjjjjjjj
kkkkkkkkkkkkkkkkkkkkkkk
lllllllllllllllllllll
nnnnnnnnnnnnnnnnnnn
mmmmmmmmmmmmmmmmmmm



*/
//global variable declaration
COORD coord = {0, 0};

int k = 7;
int r = 0;
int flag = 0;

void main_page();

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{
    int mm;
	int dd;
	int yy;
};

ofstream fout;
ifstream fin;

class item
{
    int itemno;
    char name[25];
    date d;
	public:
    	void add()
    	{
    	    cout<<"\n\n\tItem No: ";
    	    cin>>itemno;
			ifstream ip("data.csv");
	
	  		if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
	
	  		string ItemNo;
	  		string Model;
	  		string Quantity;
	  		string M[100];
	  		int t[100];
	  		int q[100];
			int i = 0;
			int j = 0;
			int x = 1;
			
			
  			while(ip.good())
  			{
    			getline(ip,ItemNo,',');
    			getline(ip,Model,',');
    			getline(ip,Quantity,'\n');
			
				M[i] = Model;
				t[i]= atoi(ItemNo.c_str());
    			q[j] = atoi(Quantity.c_str());
    		
			
    			i++;
    			j++;
    			x++;
  			}
  			
  			int b = 0;
  			ofstream dip;
  			dip.open("data.csv");
  			
  			for(int a = 0; a < x-2; a++)
			{
				if(t[a] == itemno)
    			{
    				b = a;
    				dip << t[a] << "," << M[a] << "," << q[a] - 1 << endl;
    			
				}
				else
				{
					dip << t[a] << "," << M[a] << "," << q[a] << endl;
				}
			}
			
			char yn;
			if(t[b] == itemno && q[b] != 0)
			{
				std::cout<<"\n\n\tMobile exists"<<'\n';
			}
			else if (t[b] == itemno && q[b] == 0)
			{
				cout << "\n\t Mobiles of all this model have been sold already" << endl ;
				cout <<"Do you want to continue (y/n)? ";
				cin >> yn;
				if((yn=='Y')||(yn=='y'))
        		{
            		main_page();
            	}
            	else
        		{
            		exit(0);
        		}
			}
			else
			{
				cout << "\n\tMobile does not exists in this shop" << endl ;
			  	cout <<"Do you want to continue (y/n)? ";
				cin >> yn;
				if((yn=='Y')||(yn=='y'))
        		{
            		main_page();
            	}
            	else
        		{
            		exit(0);
        		}
			} 
		
  			ip.close();
  			cout<<"\n\n\tName of the item: ";
        	cin>>name;
        	cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
        	cin>>d.mm>>d.dd>>d.yy;
  				
    	}
		
		void show()
    	{
    		cout<<"\n\tItem No: ";
        	cout<<itemno;
      		cout<<"\n\n\tName of the item: ";
        	cout<<name;
        	cout<<"\n\n\tDate : ";
        	cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
    	}	
		void report()
    	{
    	    gotoxy(3,k);
    	    cout<<itemno;
    	    gotoxy(13,k);
    	    puts(name);
    	}
    	int retno()
    	{
    	    return(itemno);
	
	    }
};

class amount: public item
{
	
	float price;
    float qty = 1.;
	float dis;
	float netamt;
	public:
		void add();
    	void show();
    	void report();
    	void calculate();
    	void pay();
    	float retnetamt()
    	{
    	    return(netamt);
    	}
    
} amt;

void amount::add()
{
    item::add();
    cout << "\n\n\tPrice: ";
    cin >> price;
    cout << "\n\n\tDiscount percent: ";
    cin >> dis;
    calculate();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::calculate()
{
    netamt =  (price - (price * (dis/100)));
}
void amount::show()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    item::show();
    cout << "\n\n\tNet amount: ";
    cout << netamt;
    fin.close();
}

void amount::report()
{
    item::report();
    
    gotoxy(23,k);
    cout << price;
    gotoxy(33,k);
    cout << qty;
    gotoxy(44,k);
    cout << dis;
    gotoxy(52,k);
    cout << netamt;
    
    k = k + 1;
    
    if (k == 50)
    {
        gotoxy(25,50);
        cout << "PRESS ANY KEY TO CONTINUE...";
        getch();
        k = 7 ;
        system("cls");
        gotoxy(30,3);
        cout << " ITEM DETAILS ";
        gotoxy(3,5);
        cout << "NUMBER";
        gotoxy(13,5);
        cout << "NAME";
        gotoxy(23,5);
        cout << "PRICE";
        gotoxy(33,5);
        cout << "QUANTITY";
        gotoxy(44,5);
		cout << "DEDUCTION";
        gotoxy(52,5);
        cout << "NET AMOUNT";

    }
}

void amount::pay()
{
    show();
    cout << "\n\n\n\t\t*********************************************";
    cout << "\n\t\t                 DETAILS                  ";
    
    cout << "\n\t\tPRICE                     :"<<price;
    cout << "\n\t\tQUANTITY                  :"<<1;
    cout << "\n\t\tDISCOUNT PERCENTAGE         :"<<dis;
    cout << "\n\t\tNET AMOUNT              :Rs."<<netamt;
    cout << "\n\t\t*********************************************";
}

void main_page()
{
	cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    system("cls");
    gotoxy(25,2);
    cout << "Mobile Shop ";
    gotoxy(25,3);
    cout << "===========================\n\n";
    cout << "\n\t\t1.Show data\n\n";
    cout << "\t\t2.Add or Remove Mobile\n\n";
    cout << "\t\t3.Exit\n\n";
    cout << "\t\tPlease Enter Required Option: ";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        system("cls");
        gotoxy(25,2);
        cout<<"Mobile Details";
        gotoxy(25,3);
        cout<<"================\n\n";
        cout<<"\n\t\t1.All Items\n\n";
        cout<<"\t\t2.Back to Main menu\n\n";
        cout<<"\t\tPlease Enter Required Option: ";
        int cho;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" Mobile DETAILS ";
            gotoxy(3,5);
            cout<<"ITEM NO";
            gotoxy(13,5);
            cout<<"NAME";
            gotoxy(23,5);
            cout<<"PRICE";
            gotoxy(33,5);
            cout<<"QUANTITY";
            gotoxy(44,5);
            cout<<"DISCOUNT %";
            gotoxy(52,5);
            cout<<"NET AMOUNT";
            
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
            	cout<< endl;
            	cout<< endl;
                cout<<"File Not Found  ";
                goto menu;
            }
            fin.seekg(0);
            
            gtotal = 0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report();
                    gtotal+=amt.retnetamt();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            
            gotoxy(17,k);
            cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
            getch();
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:
db:
        system("cls");
        gotoxy(25,2);
        cout<<"ADD or Remove";
        gotoxy(25,3);
        cout<<"=================\n\n";
        cout<<"\n\t\t1.Add Mobile Details\n\n";
        cout<<"\t\t2.Edit Mobile Details\n\n";
        cout<<"\t\t3.Delete Mobile Details\n\n";
        cout<<"\t\t4.Back to Main Menu ";
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add();
            cout<<"\n\t\tMobile Added Successfully!";
            getch();
            goto db;

        case 2:
            int ino;
            flag=0;
            cout<<"\n\n\tEnter Mobile Number(Item No) to be Edited :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            fout.open("itemstore.dat",ios::binary|ios::app);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            r=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    int x=amt.item::retno();
                    if(x==ino)
                    {
                        flag=1;
                        fout.seekp(r*sizeof(amt));
                        system("cls");
                        cout<<"\n\t\tCurrent Details are\n";
                        amt.show();
                        cout<<"\n\n\t\tEnter New Details\n";
                        amt.add();
                        cout<<"\n\t\tMobile Details editted";
                    }
                }
                r++;
            }
            if(flag==0)
            {
                cout<<"\n\t\tMobile No does not exist...Please Retry!";
                getch();
                goto db;
            }
            fin.close();
            getch();
            goto db;

        case 3:
            flag = 0;
            cout<<"\n\n\tEnter Mobile (Item number) to be deleted :";
            cin>>ino;
            
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found ";
                goto menu;
            }

            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x = amt.item::retno();
                if(x != ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                	ifstream ip("data.csv");

  					if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
					
					string M[100];
	  				int t[100];
	  				int q[100];
  					string ItemNo;
  					string Model;
  					string Quantity;
  					int i = 0;
					int j = 0;
					int x = 1;
  
  					string a = "2";

  					while(ip.good())
  					{
    					getline(ip,ItemNo,',');
    					getline(ip,Model,',');
    					getline(ip,Quantity,'\n');
    					M[i] = Model;
						t[i]= atoi(ItemNo.c_str());
    					q[j] = atoi(Quantity.c_str());
    					i++;
    					j++;
    					x++;
                    }
                    
                    int b = 0;
  					ofstream dip;
  					dip.open("data.csv");
  				
  					for(int a = 0; a < x-2; a++)
					{
						if(t[a] == ino)
    					{
    						b = a;
    						dip << t[a] << "," << M[a] << "," << q[a] + 1 << endl;
    					
						}
						else
						{
							dip << t[a] << "," << M[a] << "," << q[a] << endl;
						}
					}
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Error in File";
                goto db;
            }
            
            while(tmp.read((char*)&amt,sizeof(amt)))
            {
            	fout.write((char*)&amt,sizeof(amt));	
			}
			
            tmp.close();
            fout.close();
            if(flag==1)
            {
            	cout<<"\n\t\tMobile Succesfully Deleted";
			}
            else if (flag==0)
            {
            	cout<<"\n\t\tMobile does not Exist! Please Retry";
			}
            getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"\n\n\t\tWrong Choice!!! Retry";
            getch();
            goto db;
        }
    case 3:
        system("cls");
        gotoxy(12,6);
        cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            gotoxy(12,20);
            system("cls");
            gotoxy(12,6);
            cout<<"************ THANKS YOU ***************";
            getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
        {
        	goto menu;
		}
        
        else
        {
            goto menu;
        }
    default:
    	cout<< endl;
    	cout<< endl;
        cout<<"\t\t....Please Retry.....!";
        getch();
        goto menu;
    }
}

int main()
{
    main_page();
    return 0;
}
