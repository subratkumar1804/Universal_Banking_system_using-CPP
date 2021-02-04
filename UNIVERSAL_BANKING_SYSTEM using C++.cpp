/* UNIVERSAL BANKING SYSTEM Using C++ */

/* Made By: SUBRAT KUMAR */

/*This project is based is based on basic banking activities all over the world such as creating account, adding balance, withdrawing, deleting or modifying account and much more.*/
/* This project in C++ is based on the concept of object oriented programming(OOPs) and file handling system in C++*/

/*Coding*/

//header files

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<time.h>

using namespace std;

//basic functions definitions

void delay(int number_of_seconds){
	int milli_seconds = 1000 * number_of_seconds; 
    clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds) 
        ; 
}

void introduction(){
	cout<<"\t\t\t\t-----------------------------------"<<endl;
	cout<<"\t\t\t\tWELCOME TO UNIVERSAL BANKING SYSTEM"<<endl;
	cout<<"\t\t\t\t-----------------------------------"<<endl<<endl;
	cout<<"\tMade By: SUBRAT KUMAR";
	cout<<endl<<endl;
	cout<<"\tPRESS ENTER TO CONTINUE: ";
	cin.get();
}

//Bank class

class Bank{
	//Data Members
	private:
		int acno;
		char name[500];
		char type;
		int deposit;
	//Member functions
	public:
		void create_account();
		void show_account() const;
		void modify();
		void dep(int);
		void draw(int);
		void report() const;
		int retacno() const;
		int retdeposit() const;
		char rettype() const;
};

/*Member function definition*/
void Bank::create_account(){
	cout<<"\n\nEnter Account No.: ";
	cin>>acno;
	cout<<"\n\nEnter Account Holder's name: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\nEnter Account Type (Current(C)/Saving(S)): ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\nCreating Account.......";
	delay(1);
	cout<<"\n\nAccount Created...";
	cout<<"\n\nPress Enter to return to Main Menu... ";
}
void Bank::show_account() const{
	cout<<"\n\nAccount No.: "<<acno;
	cout<<"\n\nAccount Holder's Name: ";
	cout<<name;
	cout<<"\n\nAccount Type: "<<type;
	cout<<"\n\nBalance Amount: "<<deposit;
}
void Bank::modify(){
	cout<<"\n\nAccount No.: "<<acno;
	cout<<"\n\n\nModify Account Holder's Name: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\nModify Account Type: ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\nModify Balance Amount: ";
	cin>>deposit;
	cout<<"\n\nModifying......";
	delay(1);
}
void Bank::dep(int temp2){
	deposit = deposit+temp2;
}
void Bank::draw(int temp2){
	deposit = deposit-temp2;
}
void Bank::report() const{
	cout<<acno<<"\t\t\t\t"<<name<<"\t\t\t\t"<<type<<"\t\t\t\t"<<deposit<<endl;
}
int Bank::retacno() const{
	return acno;
}
int Bank::retdeposit() const{
	return deposit;
}
char Bank::rettype() const{
	return type;
}

/*file function definitions*/

//funtion to write in file

void write_acc(){
	Bank obj;
	ofstream f;
	f.open("account.dat",ios::binary|ios::app);
	obj.create_account();
	f.write(reinterpret_cast<char *> (&obj), sizeof(Bank));
	f.close();
}

//function to modify data in file

void modify_acc(int temp){
	int flag=0;
	Bank obj;
	fstream f;
	f.open("account.dat",ios::binary|ios::in|ios::out);
	if(!f){
		cout<<"File could not be open!! Press Enter to continue.....";
		return;
	}
	while(!f.eof() && flag==0){
		f.read(reinterpret_cast<char *> (&obj), sizeof(Bank));
		if(obj.retacno()==temp){
			obj.show_account();
			cout<<"\n\n\n\t\t\tENTER NEW DETAILS OF THE ACCOUNT:"<<endl;
			obj.modify();
			int position = (-1)*static_cast<int>(sizeof(Bank));
			f.seekp(position,ios::cur);
			f.write(reinterpret_cast<char *> (&obj), sizeof(Bank));
			cout<<"\n\nUpdating......";
			delay(2);
			cout<<"\n\n\t Record Updated.";
			cout<<"\n\nPress Enter to return to Main Menu... ";
			flag=1;
		}
	}
	f.close();
	if(flag==0){
		cout<<"\n\n Record not found!!!";
		cout<<"\n\nPress Enter to return to Main Menu... ";
	}
	
}

//function to deposit/withdraw amount

void deposit_withdraw(int temp, int choice){
	int amount;
	int flag = 0;
	Bank obj;
	fstream f;
	f.open("account.dat",ios::binary|ios::in|ios::out);
	if(!f){
		cout<<"File could not be open!! Press Enter to continue.....";
		return;
	}
	while(!f.eof() && flag==0){
		f.read(reinterpret_cast<char *> (&obj), sizeof(Bank));
		if(obj.retacno()==temp){
			obj.show_account();
			if(choice==1){
				cout<<"\n\t\t\t\t\t-----------------"<<endl;
		    	cout<<"\t\t\t\t\tTO DEPOSIT AMOUNT"<<endl;
		    	cout<<"\t\t\t\t\t-----------------"<<endl;
				cout<<"\n\nEnter The amount to be deposited:"<<endl;
				cin>>amount;
				delay(1);
				cout<<"\n\nProcess Successful.";
				obj.dep(amount);
			}
			if(choice==2){
				cout<<"\n\t\t\t\t\t------------------"<<endl;
		    	cout<<"\t\t\t\t\tTO WITHDRAW AMOUNT"<<endl;
		    	cout<<"\t\t\t\t\t------------------"<<endl;
				cout<<"\n\nEnter the amount to be withdrawn:"<<endl;
				cin>>amount;
				int balance = obj.retdeposit()-amount;
				if((balance<500 && obj.rettype()=='S') || (balance<1000 && obj.rettype()=='C')){
					cout<<"Insufficient Balance!!";
				}
				else{
					delay(1);
					cout<<"\n\nProcess Successful.";
					obj.draw(amount);
				}
			}
			int position=(-1)*static_cast<int>(sizeof(obj));
			f.seekp(position,ios::cur);
			f.write(reinterpret_cast<char *> (&obj), sizeof(Bank));
			cout<<"\n\nUpdating Records.......";
			delay(1);
			cout<<"\n\n\tRecords Updated.";
			cout<<"\n\nPress Enter to return to Main Menu...";
			flag=1;
		}
	}
	f.close();
	if(flag==0){
		cout<<"\n\n\tRecord not found!!";
		cout<<"\n\nPress Enter to return to Main Menu..."; 
	}
}

//function to delete account

void delete_acc(int temp){
	Bank obj;
	ifstream f1;
	ofstream f2;
	f1.open("account.dat",ios::binary);
	if(!f1){
		cout<<"File could not be open!! Press Enter to continue.....";
		return;
	}
	f2.open("Temp.dat",ios::binary);
	f1.seekg(0,ios::beg);
	while(f1.read(reinterpret_cast<char *> (&obj), sizeof(Bank))){
		if(obj.retacno()!=temp){
			f2.write(reinterpret_cast<char *> (&obj), sizeof(Bank));
		}
	}
	f1.close();
	f2.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\nDeleting Records.....";
	delay(1);
	cout<<"\n\n\tRecords Deleted.";
	cout<<"\n\nPress Enter to return to Main Menu...";
}

//function to view particular account

void display_sp(int temp){
	Bank obj;
	int flag = 0;
	ifstream f;
	f.open("account.dat",ios::binary);
	if(!f){
		cout<<"File could not be open!! Press Enter to continue.....";
		return;
	}
	cout<<"\n\t\t\t\t\t---------------"<<endl;
	cout<<"\t\t\t\t\tBALANCE DETAILS"<<endl;
	cout<<"\t\t\t\t\t---------------"<<endl;
	while(f.read(reinterpret_cast<char *> (&obj), sizeof(Bank))){
		if(obj.retacno()==temp){
			obj.show_account();
			cout<<"\n\nPress Enter to return to Main Menu...";
			flag=1;
		}
	}
	f.close();
	if(flag==0){
		cout<<"\n\nAccount Number does not exist.";
	}
}

//function to view all records in file

void display_all(){
	Bank obj;
	ifstream f;
	f.open("account.dat",ios::binary);
	if(!f){
		cout<<"File could not be open!! Press Enter to continue.....";
		return;
	}
	cout<<"\t\t\t\t\t----------------------"<<endl;
	cout<<"\t\t\t\t\t ACCOUNT HOLDERS LIST"<<endl;
	cout<<"\t\t\t\t\t----------------------"<<endl;
	cout<<"=======================================================================================================\n";
	cout<<"A/c no.\t\t\t\tNAME\t\t\t\tType\t\t\t\tBalance\n";
	cout<<"=======================================================================================================\n";
	while(f.read(reinterpret_cast<char *> (&obj), sizeof(Bank))){
		obj.report();
	}
	f.close();
}

//Main Function

int main(){
	int choice;
	int num;
	introduction();
	cout<<"\n\nLoading system.........";
	delay(1);
	do{
		system("cls");
		cout<<"\n\n";
		cout<<"\t\t\t\t\t-----------"<<endl;
		cout<<"\t\t\t\t\t MAIN MENU"<<endl;
		cout<<"\t\t\t\t\t-----------"<<endl;
	    cout<<"\n\n\n\tPRESS 1: TO CREATE NEW ACCOUNT\t\t\t"<<endl<<endl;
		cout<<"\tPRESS 2: TO DEPOSIT AMOUNT IN EXISTING ACCOUNT\t\t\t"<<endl<<endl;
		cout<<"\tPRESS 3: TO WITHDRAW AMOUNT FROM EXISTING ACCOUNT\t\t\t"<<endl<<endl;
		cout<<"\tPRESS 4: FOR BALANCE ENQUIRY\t\t\t"<<endl<<endl;
		cout<<"\tPRESS 5: TO CHECK ALL ACCOUNT HOLDERS LIST\t\t\t"<<endl<<endl;
		cout<<"\tPRESS 6: TO CLOSE AN ACCOUNT\t\t\t"<<endl<<endl;
		cout<<"\tPRESS 7: TO MODIFY AN ACCOUNT\t\t\t"<<endl<<endl;
		cout<<"\tPRESS 8: EXIT"<<endl<<endl;
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		switch(choice){
		case 1:
			cout<<"\n\nLoading.....";
			delay(1);
			system("cls");
			write_acc();
			break;
		case 2:
			cout<<"\n\nLoading.....";
		    delay(1);
		    system("cls");
			cout<<"\n\nEnter Account No. : "; 
			cin>>num;
			deposit_withdraw(num, 1);
			break;
		case 3:
			cout<<"\n\nLoading.....";
			delay(1);
			system("cls");
			cout<<"\n\nEnter Account No. : "; 
			cin>>num;
			deposit_withdraw(num, 2);
			break;
		case 4:
		    cout<<"\n\nLoading.....";
			delay(1);
			system("cls"); 
			cout<<"\n\nEnter Account No. : "; 
			cin>>num;
			display_sp(num);
			break;
		case 5:
			cout<<"\n\nLoading.....";
			delay(1);
			system("cls");
			display_all();
			break;
		case 6:
			cout<<"\n\nLoading.....";
			delay(1);
			system("cls");
			cout<<"\n\nEnter Account No. : "; 
			cin>>num;
			delete_acc(num);
			break;
		 case 7:
		 	cout<<"\n\nLoading.....";
			delay(1);
			system("cls");
			cout<<"\n\nEnter Account No. : "; 
			cin>>num;
			modify_acc(num);
			break;
		 case 8:
			cout<<"\n\n\t\tTHANK YOU FOR USING UNIVERSAL BANKING SYSTEM.....";
			cout<<"\n\nPRESS ENTER TO EXIT";
			delay(1);
			break;
		 default :
		 cout<<"\nTry Again!! Choose the correct input.";
		 cout<<"\n\nPRESS ENTER TO TRY AGAIN ";           
		}
		cin.ignore();
		cin.get();
    }while(choice!=8);
	return 0;
}

