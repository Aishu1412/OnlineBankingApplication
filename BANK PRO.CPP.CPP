/*----------------------------------------------------------------------
	HEADER FILES USED
----------------------------------------------------------------------*/
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
#include<ctype.h>
#include<string.h>
#include<iomanip.h>
/*----------------------------------------------------------------------
Declaration of functions to be used in the account and derived classes
----------------------------------------------------------------------*/
int get_next_txnacc(); // Function to return the next account number to be used for a new transaction account
int get_next_loanacc(); // Function to return the next account number to be used for a new loan account

/*----------------------------------------------------------------------
Definition of class: account
Type of Class: Base Class
Description: This class hold the basic account details like:
Account number, name, nominee, type, contact number, active status.
----------------------------------------------------------------------*/
class account
{
public:
	char acc_name[30];
	int acc_no;
	int is_active;
	char contact_no[11];
};

/*----------------------------------------------------------------------
Definition of class: txn_account
Type of Class: Derived Class; privately inherited
Inherited from the calss: account
Description: This class is privately inherited from account base class.
Holds the saving or current account details and related functions
----------------------------------------------------------------------*/
class txn_account:private account
{
private:
	int deposit;
	char acc_type;
	char nominee[30];
public:
	void create_account();
	void modify_account();
	void deposit_amount(int);
	int withdraw_amount(int);
	void show_acc_details();
	int get_acc_number();
	void get_acc_name(char *);
	char get_type ();
	int acc_active ();
	int get_balance();
	void disable_account();
};

/*----------------------------------------------------------------------
Definition of class: loan_account
Type of Class: Derived Class; privately inherited
Inherited from the class: account
Description: This class is privately inherited from account base class.
Holds the loan account details and related functions
----------------------------------------------------------------------*/
class loan_account:private account
{
private:
	int loan_balance;
	char guarantor[30];

public:
	void create_account();
	void modify_account();
	void reduce_loan_balance (int);
	void increase_loan_balance (int);
	void show_acc_details();
	int get_acc_number();
	void get_acc_name(char *);
	char get_type ();
	int acc_active ();
	int get_balance();
	void disable_account();
};

/*----------------------------------------------------------------------
Definition of functions of the class: txn_account
----------------------------------------------------------------------*/
//FUNCTION TO POPULATE THE TRANSACTION ACCOUNT DETAILS
void txn_account::create_account()
{
	//Assign account number automatically
	acc_no = get_next_txnacc();
	//The account is set to active by default
	is_active = 1;
	// Get the name and nominee details
	cout<<"\nENTER THE ACCOUNT HOLDER NAME: ";
	cin.ignore();
	cin.getline(acc_name,30);
	cout<<"\nENTER THE NOMINEE FOR THE ACCOUNT: ";
	cin.clear();
	cin.getline(nominee,30);
	//Get the contact numner and validate that it is all digits
	int contact_ok = 0;
	char tmp_contact[10];
	while (contact_ok== 0)
	{
		cout<<"\nENTER CONTACT PHONE NUMBER (10 digits): ";
		cin.clear();
		cin >> tmp_contact; 
		contact_ok = 1;
		for (int i=0; i < 10; i++)
		{
			if(!(isdigit(tmp_contact[i] )))
			{
				cout << "PLEASE ENTER A VALID PHONE NUMBER - ONLY DIGITS 0 to 9!" << endl;
				contact_ok = 0;
				break;
			}
		}
	}
	strcpy(contact_no, tmp_contact);
	contact_no[10] = '\0';
	//Get the account type - Saving or Current
	acc_type = 'x';
	while (acc_type != 'S' && acc_type != 'C')
	{
		cout<<"\nENTER THE ACCOUNT TYPE(S=SAVING; C=CURRENT):";
		cin >> acc_type;
		acc_type = toupper(acc_type);
	}
	//Get the initial deposit amount based on account type
	if (acc_type == 'S')
	{
		deposit = 0;
		while ( deposit < 500)
		{
			cout<<"ENTER THE INITIAL DEPOSIT AMOUNT(Min Rs. 500): ";
			cin >> deposit;
		}
	}
	else
	{
		deposit = 0;
		while ( deposit < 1000)
		{
			cout<<"ENTER THE INITIAL DEPOSIT AMOUNT(Min Rs. 1000): ";
			cin >> deposit;
		}

	}
}
//FUNCTION TO MODIFY TRANSACTION ACCOUNT DETAILS
void txn_account::modify_account()
{
	char option;
	while(option !='1' && option !='2' && option !='3' )
	{
		clrscr();
		cout<<"\nOPTIONS TO MODIFY THE ACCOUNT:";
		cout<<"\n1.CHANGE ACCOUNT HOLDER NAME";
		cout<<"\n2.CHANGE NOMINEE NAME";
		cout<<"\n3.CHANGE CONTACT NUMBER";
		cout<<"\nENTER OPTION:";
		cin>>option;
	}
	switch(option)
	{
		case '1':
			cout<<"CURRENT NAME OF THE ACCOUNT HOLDER: " << acc_name;
			cout<<"\nENTER THE UPDATED NAME: ";
			cin.ignore();
			cin.getline(acc_name,30);
			break;
		case '2':
			cout<<"CURRENT NAME OF THE NOMINEE: " << nominee;
			cout<<"\nENTER THE UPDATED NOMINEE: ";
			cin.ignore();
			cin.getline(nominee,30);
			break;
		case '3':
			cout<<"CURRENT CONTACT NUMBER: " << contact_no;
			int contact_ok = 0;
			char tmp_contact[10];
			while (contact_ok== 0)
			{
				cout<<"\nENTER CONTACT PHONE NUMBER (10 digits): ";
				cin.clear();
				cin >> tmp_contact; 
				contact_ok = 1;
				for (int i=0; i < 10; i++)
				{
					if(!(isdigit(tmp_contact[i] )))
					{
						cout << "PLEASE ENTER A VALID PHONE NUMBER - ONLY DIGITS 0 to 9!" << endl;
						contact_ok = 0;
						break;
					}
				}
			}
			strcpy(contact_no, tmp_contact);
			contact_no[10] = '\0';
			break;
	}
}
//FUNCTION TO DISPLAY THE ACCOUNT DETAILS
void txn_account::show_acc_details()
{
	cout<<"\nNAME OF THE ACCOUNT HOLDER:"<<acc_name<<endl;
	cout<<"NAME OF THE NOMINEE:"<<nominee<<endl;
	cout<<"ACCOUNT HOLDER CONTACT NUMBER:"<<contact_no;
	if (is_active)
	{
		cout<<"\nACCOUNT STATUS: ACTIVE\n";
	}
	else
	{
		cout<<"\nACCOUNT STATUS: INACTIVE\n";
	}
	if (acc_type == 'S')
	{
		cout<<"ACCOUNT TYPE: SAVING ACCOUNT";
	}
	else
	{
		cout<<"ACCOUNT TYPE: CURRENT ACCOUNT";
	}
	cout<<"\nACCOUNT BALANCE: "<<deposit<<endl;
}
//FUNCTION TO RETURN ACCOUNT NUMBER
int txn_account::get_acc_number()
{
	return acc_no;
}
//FUNCTION TO RETURN ACCOUNT NAME
void txn_account::get_acc_name(char *name)
{
	strcpy (name,acc_name);
}
//FUNCTION TO RETURN ACCOUNT TYPE
char txn_account::get_type()
{
	return acc_type;
}
//FUNCTION TO RETURN ACCOUNT STATUS; 1 = Active; 0 = Inactive
int txn_account::acc_active()
{
	return is_active;
}
//FUNCTION TO RETURN ACCOUNT BALANCE
int txn_account::get_balance()
{
	return deposit;
}
//FUNCTION TO ADD DEPOSIT AMOUNT
void txn_account::deposit_amount(int amount)
{
	deposit += amount;
}
//FUNCTION TO WITHDRAW AMOUNT
int txn_account::withdraw_amount(int amount)
{
	int reduced_flag = 0;
	//Check for account type and minimum balance to allow withdrawal
	if (acc_type == 'S')
	{
		if ( (deposit - amount) < 500 )
		{
			cout << "\nCANNOT WITHDRAW THIS AMOUNT AS THE MINIMUM BALANCE REQUIRED IS Rs. 500";
		}
		else
		{
			deposit -= amount;
			reduced_flag = 1;
		}
	}
	else
	{
		if ( (deposit - amount) < 1000 )
		{
			cout << "\nCANNOT WITHDRAW THIS AMOUNT AS THE MINIMUM BALANCE REQUIRED IS Rs. 1000";
		}
		else
		{
			deposit -= amount;
			reduced_flag = 1;
		}
	}
	return reduced_flag;
}
//FUNCTION TO DISABLE THE ACCOUNT
void txn_account::disable_account()
{
	is_active = 0;
}

/*----------------------------------------------------------------------
Definition of functions of the class: loan_account
----------------------------------------------------------------------*/
//FUNCTION TO POPULATE THE LOAN ACCOUNT DETAILS
void loan_account::create_account()
{
	//Assign account number automatically
	acc_no = get_next_loanacc();
	//The account is set to active by default
	is_active = 1;
	cout<<"\nENTER THE LOAN ACCOUNT HOLDER NAME: ";
	cin.ignore();
	cin.getline(acc_name,30);
	cout<<"\nENTER THE GUARANTOR FOR THE ACCOUNT: ";
	cin.clear();
	cin.getline(guarantor,30);
	//Get the contact number and validate that it is all digits
	int contact_ok = 0;
	char tmp_contact[10];
	while (contact_ok== 0)
	{
		cout<<"\nENTER CONTACT PHONE NUMBER (10 digits): ";
		cin.clear();
		cin >> tmp_contact; 
		contact_ok = 1;
		for (int i=0; i < 10; i++)
		{
			if(!(isdigit(tmp_contact[i] )))
			{
				cout << "PLEASE ENTER A VALID PHONE NUMBER - ONLY DIGITS 0 to 9!" << endl;
				contact_ok = 0;
				break;
			}
		}
	}
	strcpy(contact_no, tmp_contact);
	contact_no[10] = '\0';
	//Get the initial loan amount; minimum amount is Rs. 10,000
	loan_balance = 0;
	while ( loan_balance < 10000)
	{
			cout<<"ENTER THE SANCTIONED LOAN AMOUNT (Min Rs. 10,000): ";
			cin >> loan_balance;
	}
}
//FUNCTION TO MODIFY LOAN ACCOUNT DETAILS
void loan_account::modify_account()
{
	char option;
	while(option !='1' && option !='2' && option !='3' )
	{
		clrscr();
		cout<<"\nOPTIONS TO MODIFY THE ACCOUNT DETAILS:";
		cout<<"\n1.CHANGE LOAN ACCOUNT HOLDER NAME";
		cout<<"\n2.CHANGE LOAN GUARANTOR NAME";
		cout<<"\n3.CHANGE CONTACT NUMBER";
		cout<<"\nENTER OPTION:";
		cin>>option;
	}
	switch(option)
	{
		case '1':
			cout<<"CURRENT NAME OF THE LOAN ACCOUNT HOLDER: " << acc_name;
			cout<<"\nENTER THE UPDATED NAME: ";
			cin.ignore();
			cin.getline(acc_name,30);
			break;
		case '2':
			cout<<"CURRENT NAME OF THE GUARANTOR: " << guarantor;
			cout<<"\nENTER THE UPDATED GUARANTOR: ";
			cin.ignore();
			cin.getline(guarantor,30);
			break;
		case '3':
			cout<<"CURRENT CONTACT NUMBER: " << contact_no;
			int contact_ok = 0;
			char tmp_contact[10];
			while (contact_ok== 0)
			{
				cout<<"\nENTER CONTACT PHONE NUMBER (10 digits): ";
				cin.clear();
				cin >> tmp_contact; 
				contact_ok = 1;
				for (int i=0; i < 10; i++)
				{
					if(!(isdigit(tmp_contact[i] )))
					{
						cout << "PLEASE ENTER A VALID PHONE NUMBER - ONLY DIGITS 0 to 9!" << endl;
						contact_ok = 0;
						break;
					}
				}
			}
			strcpy(contact_no, tmp_contact);
			contact_no[10] = '\0';
			break;		
	}
}

//FUNCTION TO DISPLAY THE LOAN ACCOUNT DETAILS
void loan_account::show_acc_details()
{
	cout<<"\nNAME OF THE LOAN ACCOUNT HOLDER:" << acc_name<<endl;
	cout<<"NAME OF THE GUARANTOR:" << guarantor << endl;
	cout<<"LOAN ACCOUNT HOLDER CONTACT NUMBER:"<<contact_no << endl;
	if (is_active)
	{
		cout<<"LOAN ACCOUNT STATUS: ACTIVE";
	}
	else
	{
		cout<<"LOAN ACCOUNT STATUS: CLOSED";
	}
	cout<<"\nLOAN BALANCE: "<<loan_balance<<endl;
}
//FUNCTION TO RETURN LOAN ACCOUNT NUMBER
int loan_account::get_acc_number()
{
	return acc_no;
}
//FUNCTION TO RETURN ACCOUNT NAME
void loan_account::get_acc_name(char *name)
{
	strcpy (name,acc_name);
}
//FUNCTION TO RETURN ACCOUNT STATUS
int loan_account::acc_active()
{
	return is_active;
}
//FUNCTION TO RETURN LOAN ACCOUNT BALANCE
int loan_account::get_balance()
{
	return loan_balance;
}
//FUNCTION TO REDUCE LOAN BALANCE
void loan_account::reduce_loan_balance (int amount)
{
	loan_balance -= amount;
}
//FUNCTION TO ADD/INCREASE LOAN AMOUNT
void loan_account::increase_loan_balance(int amount)
{
	loan_balance += amount;
}
//FUNCTION TO DISABLE THE ACCOUNT
void loan_account::disable_account()
{
	is_active = 0;
}

/*----------------------------------------------------------------------
Declaration of the functions
----------------------------------------------------------------------*/
void welcome (); // Function to display welcome screen
void create_new_account(); // Function to create a new account
void deposit_amount(); // Function to add deposit amount
void withdraw_amount(); // Function to withdraw amount
void repay_loan(); //Function to repay loan amount
void add_loan_amount(); // Function to add loan amount
void modify_account(); // Function to modify account details
void display_account_details(); //Function to call display account functions
void display_txn_account(int); //Function to search and display transaction account
void display_loan_account (int);//Function to search and display Loan account
void display_all_accounts(); //Function to display the details of all accounts
void close_account(); //Function to disable/close an account
void write_txn_account(txn_account); // Function to write a transaction account to file
void write_loan_account(loan_account); // Function to write a loan account to file

/*----------------------------------------------------------------------
Main Function
----------------------------------------------------------------------*/
int main()
{
	char option;
	//Call the function to display the welcome screen
	welcome();
	//Display the options and capture the option selected by user
	while(option!= 'X')
	{
		clrscr();
		cout<<"\n\t\t\tBANK ACCOUNT MANAGEMENT AND TRANSACTION OPTIONS";
		cout<<"\n1.CREATE AN ACCOUNT";
		cout<<"\n2.SAVINGS/CURRENT ACCOUNT: DEPOSIT AMOUNT";
		cout<<"\n3.SAVINGS/CURRENT ACCOUNT: WITHDRAW AMOUNT";
		cout<<"\n4.LOAN ACCOUNT: REPAY LOAN";
		cout<<"\n5.LOAN ACCOUNT: ADD ADDITIONAL LOAN AMOUNT";
		cout<<"\n6.MODIFY ACCOUNT DETAILS";
		cout<<"\n7.SHOW ACCOUNT DETAILS";
		cout<<"\n8.DISPLAY ALL ACCOUNT HOLDERS LIST";
		cout<<"\n9.CLOSE AN ACCOUNT";
		cout<<"\nX.EXIT";
		cout<<"\nENTER OPTION:";
		cin>>option;
		option = toupper(option);
		switch(option)
		{
			case '1':
				//Call the function to create a new account
				create_new_account();
				break;
			case '2':
				//Call the function to deposit amount in a savings/current account
				deposit_amount();
				break;
			case '3':
				//Call the function to withdraw amount from a savings/current account
				withdraw_amount();
				break;
			case '4':
				//Call the function to repay loan amount
				repay_loan();
				break;
			case '5':
				//Call the function to add loan amount
				add_loan_amount();
				break;
			case '6':
				//Call the function to modify account details for transaction/loan account
				modify_account();
				break;
			case '7':
				//Call the function to display the details of a specific account
				display_account_details();
				break;
			case '8':
				//Call the function to display the details of all accounts
				display_all_accounts();
				break;
			case '9':
				//Call the function to close/disable an account
				close_account();
				break;
			case 'X':
				//Exit the program
				cout<<"EXITING........";
				break;
			default:
				break;
		}
	}
	return 0;
}

/*----------------------------------------------------------------------
Definition of the functions used in the program
----------------------------------------------------------------------*/
// Function to return the next Transaction account number to be used for a new account
int get_next_txnacc()
{
	ifstream t_file;
	txn_account t_account;
	int tmp_acc_num = 0;
	t_file.open("txn_account.dat",ios::binary);
	if (t_file.fail())
	{
		//There is no account file; hence return the initial account number
		return 1000;
	}
	while (t_file.read((char *)&t_account, sizeof(txn_account)))
	{
		tmp_acc_num = t_account.get_acc_number();
	}
	t_file.close();
	// Assign a default starting value for the account, if this is the first account
	if (tmp_acc_num == 0)
	{
		tmp_acc_num = 1000;
	}
	else // Increment the account number and return
	{
		tmp_acc_num++;
	}
	return tmp_acc_num;
}

// Function to return the next Loan account number to be used for a new account
int get_next_loanacc()
{
	ifstream l_file;
	loan_account l_account;
	int tmp_acc_num = 0;
	l_file.open("loan_account.dat",ios::binary);
	if (l_file.fail())
	{
		//There is no account file; hence return the initial account number
		return 5000;
	}
	while (l_file.read((char *)&l_account, sizeof(loan_account)))
	{
		tmp_acc_num = l_account.get_acc_number();
	}
	l_file.close();
	// Assign a default starting value for the account, if this is the first account
	if (tmp_acc_num == 0)
	{
		tmp_acc_num = 5000;
	}
	else // Increment the account number and return
	{
		tmp_acc_num++;
	}
	return tmp_acc_num;
}

// Function to display the welcome message
void welcome ()
{
	clrscr();
	cout<<"\n\n\n";
	cout<<"\t\t******************************************\n";
	cout<<"\n";
	cout<<"\t\t\t\tFINANCIAL\n\t\t\tACCOUNT MANAGEMENT SYSTEM\n";
	cout<<"\n";
	cout<<"\t\t*******************************************\n";
	cout<<"\n\n";
	cout<<"\t\tDONE BY:";
	cout<<"\n\t\tAISHWARYA AND SAHITHYA";
	cout<<"\n\n\n\t\tPRESS ENTER TO CONTINUE...";
	getch();
	clrscr();
}

//Function to create a new account
void create_new_account()
{
	char type;

	//Get the account type - Transaction or Loan
	while (type != 'T' && type != 'L')
	{
		cout<<"\nENTER THE ACCOUNT TYPE(T=TRANSACTION; L=LOAN):";
		cin >> type;
		type = toupper(type);
	}
	// Create a Transaction account
	if ( type == 'T')
	{
		txn_account t_account;
		t_account.create_account(); // Populate the class object with account details
		write_txn_account(t_account); // write the account object to the file
	}
	else
	{
		loan_account l_account;
		l_account.create_account(); // Populate the class object with account details
		write_loan_account(l_account); // write the account object to the file
	}
}

//Function to write transaction account details to file
void write_txn_account(txn_account t_account)
{
	ofstream t_file;
	t_file.open("txn_account.dat",ios::binary|ios::app);
	if (t_file.fail())
	{
		cout <<"Error: The file txn_account.dat could not be opened";
		return;
	}
	t_file.write((char *)&t_account, sizeof(t_account));
	t_file.close();
	cout <<"NEW TRANSACTION ACCOUNT: " << t_account.get_acc_number() << " SUCCESSFULLY CREATED\n";
	t_file.close();
	cout<<"\nPRESS ENTER TO CONTINUE...";
	getch();
}
//Function to write loan account details to file
void write_loan_account(loan_account l_account)
{
	ofstream l_file;
	l_file.open("loan_account.dat",ios::binary|ios::app);
	if (l_file.fail())
	{
		cout <<"Error: The file loan_account.dat could not be opened";
		return;
	}
	l_file.write((char *)&l_account, sizeof(loan_account));
	l_file.close();
	cout <<"NEW LOAN ACCOUNT: " << l_account.get_acc_number() << " SUCCESSFULLY CREATED\n";
	l_file.close();	
	cout<<"PRESS ENTER TO CONTINUE...";
	getch();

}
//Function to get the requirements to display account details and call respective functions
void display_account_details()
{
	char type;
	//Get the account type - Transaction or Loan
	while (type != 'T' && type != 'L')
	{
		cout<<"\nENTER THE TYPE OF ACCOUNT TO DISPLAY (T=TRANSACTION; L=LOAN):";
		cin >> type;
		type = toupper(type);
	}
	// Retrieve and Display the account details
	if ( type == 'T')
	{
		int t_acc_num;
		cout<<"\nENTER THE TRANSACTION ACCOUNT NUMBER TO SEARCH AND DISPLAY:";
		cin >> t_acc_num;
		display_txn_account(t_acc_num);
	}
	else
	{
		int l_acc_num;
		cout<<"\nENTER THE LOAN ACCOUNT NUMBER TO SEARCH AND DISPLAY:";
		cin >> l_acc_num;
		display_loan_account(l_acc_num);
	}
	cout << "PRESS ENTER TO CONTINUE...";
	getch();	
}
//Function to search for transaction account from file and display
void display_txn_account (int acc_num)
{
	ifstream t_file;
	txn_account t_account;
	int found = 0;
	
	t_file.open("txn_account.dat",ios::binary);
	if (t_file.fail())
	{
		cout << "Error: The file txn_account.dat could not be opened!";
		return;
	}
	while ((t_file.read((char *)&t_account, sizeof(txn_account))) && (found == 0))
	{
		if (acc_num == t_account.get_acc_number())
		{
			found = 1;
			cout << "\n--------------------------------------------------------------------------\n";
			t_account.show_acc_details();
			cout << "\n--------------------------------------------------------------------------\n";
		}
	}
	if (found == 0)
	{
		cout << " THE SPECIFIED ACCOUNT IS NOT FOUND!";
	}
	t_file.close();
}
//Function to search for Loan account from file and display
void display_loan_account (int acc_num)
{
	ifstream l_file;
	loan_account l_account;
	int found = 0;
	
	l_file.open("loan_account.dat",ios::binary);
	if (l_file.fail())
	{
		cout << "Error: The file loan_account.dat could not be opened!";
		return;
	}
	while ((l_file.read((char *)&l_account, sizeof(loan_account))) && (found == 0))
	{
		if (acc_num == l_account.get_acc_number())
		{
			found = 1;
			cout << "\n--------------------------------------------------------------------------\n";
			l_account.show_acc_details();
			cout << "\n--------------------------------------------------------------------------\n";
		}
	}
	if (found == 0)
	{
		cout << " THE SPECIFIED LOAN ACCOUNT IS NOT FOUND!";
	}
	l_file.close();
}
void display_all_accounts()
{
	char type;
	//Get the account type option to display accounts
	while (type != 'T' && type != 'L' && type != 'B')
	{
		cout<<"\nENTER THE TYPE OF ACCOUNTS TO DISPLAY (T=TRANSACTION; L=LOAN; B=BOTH):";
		cin >> type;
		type = toupper(type);
	}
	// Retrieve and Display the account details for Transaction accounts
	if ( type == 'T' || type == 'B')
	{
		ifstream t_file;
		txn_account t_account;
		char tmp_acc_name[30];
		t_file.open("txn_account.dat",ios::binary);
		if (t_file.fail())
		{
			cout << "THERE ARE NO TRANSACTION ACCOUNTS FOUND!"<<endl;
		}
		else
		{
			// Display the header for the report
			cout << "DETAILS OF TRANSACTION ACCOUNTS:\n";
			cout<<"_______________________________________________________________________________\n";
			cout<<setw(10)<<"ACC NO" << setw(30)<< " ACC HOLDER NAME" << setw(10) << " TYPE "<< setw(10) << " STATUS" << setw(10) << "     ACC_BALANCE\n" << setw(10);
			cout<<"_______________________________________________________________________________\n";
			// Read the records and display details 
			while (t_file.read((char *)&t_account, sizeof(txn_account)))
			{
				{
					t_account.get_acc_name(tmp_acc_name);
					cout << setw(10)<<t_account.get_acc_number();
					cout << setw(30)<<tmp_acc_name;
					if (t_account.get_type() == 'S')
					{
						cout << setw(10)<<"SAVING";
					}
					else
					{
						cout << setw(10)<<"CURRENT";
					}
					if (t_account.acc_active())
					{
						cout <<setw(10)<<"ACTIVE";
					} 
					else
					{
						cout <<setw(10)<<"INACTIVE";
					}
					cout << setw(10)<<t_account.get_balance()<<"\n";
				}
			}
		}
	}
	// Retrieve and Display the account details for Loan accounts
	if ( type == 'L' || type == 'B')
	{
		ifstream l_file;
		loan_account l_account;
		char tmp_acc_name[30];
		l_file.open("loan_account.dat",ios::binary);
		if (l_file.fail())
		{
			cout << "\nTHERE ARE NO LOAN ACCOUNTS FOUND!"<<endl;
		}
		else
		{
			// Display the header for the report
			cout << "\nDETAILS OF LOAN ACCOUNTS:\n";
			cout<<"_______________________________________________________________________________\n";
			cout<<setw(10)<<"ACC NO" << setw(30)<< " ACC HOLDER NAME" << setw(10) << " STATUS" << setw(10) << "     LOAN_BALANCE\n" << setw(10);
			cout<<"_______________________________________________________________________________\n";
			// Read the records and display details 
			while (l_file.read((char *)&l_account, sizeof(loan_account)))
			{
				{
					l_account.get_acc_name(tmp_acc_name);
					cout << setw(10) << l_account.get_acc_number() ;
					cout << setw(30) << tmp_acc_name;
					if (l_account.acc_active())
					{
						cout << setw(10) <<"OPEN" ;
					} 
					else
					{
						cout << setw(10) <<"CLOSED" ;
					}
					cout << setw(10) << l_account.get_balance() <<"\n";
				}
			}
		}
	}
	cout << "PRESS ENTER TO CONTINUE...";
	getch();
}
//Function to disable/close an account
void close_account()
{
	char type;
	int found = 0;
	int tmp_acc_num;
	txn_account t_account;
	fstream t_file;
	loan_account l_account;
	fstream l_file;
	//Get the account type to close - Transaction or Loan
	while (type != 'T' && type != 'L')
	{
		cout<<"\nENTER THE TYPE OF ACCOUNT TO CLOSE (T=TRANSACTION; L=LOAN):";
		cin >> type;
		type = toupper(type);
	}
	// Get the account number to be closed
	cout<<"\nENTER THE ACCOUNT NUMBER TO BE CLOSED:";
	cin.clear();
	cin >> tmp_acc_num;
	// Close a a Transaction account
	if ( type == 'T')
	{
		t_file.open("txn_account.dat", ios::in | ios::out | ios::binary);
		if (t_file.fail())
		{
			cout << "Error: The file txn_account.dat could not be opened!";
			cout << "\nPRESS ENTER TO CONTINUE...";
			getch();	
			return;
		}
		while ((!t_file.eof()) && (found == 0))
		{	
			t_file.read((char *)&t_account, sizeof(t_account));
			if (tmp_acc_num == t_account.get_acc_number())
			{
				found = 1;
				t_account.show_acc_details();
				t_account.disable_account();
				t_file.seekg(0,ios::cur);
				t_file.seekp(t_file.tellg() - sizeof(t_account));
				t_file.write((char*)&t_account,sizeof(t_account));
				cout << "\n ACCOUNT IS DISABLED";
				cout << "\nPRESS ENTER TO CONTINUE...";
				getch();
			}
		}
		if (found == 0)
		{
			cout << "\nTHE SPECIFIED ACCOUNT IS NOT FOUND!";
			cout << "\nPRESS ENTER TO CONTINUE...";
			getch();
		}
		t_file.close();
	}
	else
	{
		l_file.open("loan_account.dat", ios::in | ios::out | ios::binary);
		if (l_file.fail())
		{
			cout << "Error: The file txn_account.dat could not be opened!";
			cout << "\nPRESS ENTER TO CONTINUE...";
			getch();
			return;
		}
		while ((l_file.read((char *)&l_account, sizeof(loan_account))) && (found == 0))
		{
			if (tmp_acc_num == l_account.get_acc_number())
			{
				found = 1;
				l_account.show_acc_details();
				l_account.disable_account();
				l_file.seekg(0,ios::cur);
				l_file.seekp(l_file.tellg() - sizeof(l_account));
				l_file.write((char*)&l_account,sizeof(loan_account));
				cout << "\n THE LOAN ACCOUNT IS CLOSED";
				cout << "\nPRESS ENTER TO CONTINUE...";
				getch();
			}
		}
		if (found == 0)
		{
			cout << "\nTHE SPECIFIED LOAN ACCOUNT IS NOT FOUND!";
			cout << "\nPRESS ENTER TO CONTINUE...";
			getch();
		}
		l_file.close();
	}
}
//Function to deposit amount into Savings/Current account
void deposit_amount()
{
	// Get the account number to deposit amount
	int tmp_acc_num;
	int dep_amount = 0;
	cout<<"\nENTER THE ACCOUNT NUMBER TO DEPOSIT AMOUNT:";
	cin >> tmp_acc_num;
	txn_account t_account;
	fstream t_file;
	int found = 0;
	t_file.open("txn_account.dat", ios::in | ios::out | ios::binary);
	if (t_file.fail())
	{
		cout << "Error: The file txn_account.dat could not be opened!";
		cout << "\nPRESS ENTER TO CONTINUE...";
		getch();
		return;
	}
	while ((t_file.read((char *)&t_account, sizeof(txn_account))) && (found == 0))
	{
		if (tmp_acc_num == t_account.get_acc_number())
		{
			found = 1;
			t_account.show_acc_details();
			if (!t_account.acc_active()) //Inactive account; can not transact
			{
				cout << "\nTHE ACCOUNT IS INACTIVE; NO TRANSACTIONS ALLOWED";
			}
			else
			{
				while (dep_amount <= 0)
				{
					cout<<"\nENTER THE AMOUNT TO BE DEPOSITED (GREATER THAN 0):";
					cin >> dep_amount;
				}
				t_account.deposit_amount(dep_amount);
				t_file.seekg(0,ios::cur);
				t_file.seekp(t_file.tellg() - sizeof(t_account));
				t_file.write((char*)&t_account,sizeof(txn_account));
				cout << "\nDEPOSIT AMOUNT ADDED TO THE ACCOUNT";
			}
			cout << "\nPRESS ENTER TO CONTINUE...";
			getch();
		}
	}
	if (found == 0)
	{
		cout << "\nTHE SPECIFIED ACCOUNT IS NOT FOUND!";
		cout << "\nPRESS ENTER TO CONTINUE...";
		getch();
	}
	t_file.close();
}
//Function to withdraw amount from Savings/Current account
void withdraw_amount()
{
	// Get the account number to deposit amount
	int tmp_acc_num;
	int withdraw_amount = 0;
	int reduced_flag = 0;
	cout<<"\nENTER THE ACCOUNT NUMBER TO WITHDRAW AMOUNT:";
	cin >> tmp_acc_num;
	txn_account t_account;
	fstream t_file;
	int found = 0;
	t_file.open("txn_account.dat", ios::in | ios::out | ios::binary);
	if (t_file.fail())
	{
		cout << "Error: The file txn_account.dat could not be opened!";
		cout << "\nPRESS ENTER TO CONTINUE...";
		getch();
		return;
	}
	while ((t_file.read((char *)&t_account, sizeof(txn_account))) && (found == 0))
	{
		if (tmp_acc_num == t_account.get_acc_number())
		{
			found = 1;
			t_account.show_acc_details();
			if (!t_account.acc_active()) //Inactive account; can not transact
			{
				cout << "\nTHE ACCOUNT IS INACTIVE; NO TRANSACTIONS ALLOWED";
			}
			else
			{
					while (withdraw_amount <= 0)
					{
						cout<<"\nENTER THE AMOUNT TO BE WITHDRAW (GREATER THAN 0):";
						cin >> withdraw_amount;
					}
				reduced_flag = t_account.withdraw_amount(withdraw_amount);
				if (reduced_flag == 1)
				{
					t_file.seekg(0,ios::cur);
					t_file.seekp(t_file.tellg() - sizeof(t_account));
					t_file.write((char*)&t_account,sizeof(txn_account));
					cout << "\nAMOUNT WITHDRAWN FROM THE ACCOUNT";
				}
				else
				{
					cout << "\nAMOUNT NOT WITHDRAWN FROM THE ACCOUNT";
				}
			}
		}
	}
	if (found == 0)
	{
		cout << "\nTHE SPECIFIED ACCOUNT IS NOT FOUND!";
	}
	t_file.close();
	cout << "\nPRESS ENTER TO CONTINUE...";
	getch();

}
//Function to repay and reduce the loan balance amount
void repay_loan()
{
	// Get the account number to reduce loan balance
	int tmp_acc_num;
	int reduce_amount = 0;
	cout<<"\nENTER THE ACCOUNT NUMBER TO REDUCE LOAN BALANCE:";
	cin >> tmp_acc_num;
	loan_account l_account;
	fstream l_file;
	int found = 0;
	l_file.open("loan_account.dat", ios::in | ios::out | ios::binary);
	if (l_file.fail())
	{
		cout << "Error: The file loan_account.dat could not be opened!";
		cout << "\nPRESS ENTER TO CONTINUE...";
		getch();
		return;
	}
	while ((l_file.read((char *)&l_account, sizeof(loan_account))) && (found == 0))
	{
		if (tmp_acc_num == l_account.get_acc_number())
		{
			found = 1;
			l_account.show_acc_details();
			if (!l_account.acc_active()) //Inactive account; can not transact
			{
				cout << "\nTHE ACCOUNT IS CLOSED; NO TRANSACTIONS ALLOWED";
			}
			else
			{
				while (reduce_amount <= 0)
				{
					cout<<"\nENTER THE AMOUNT TO BE REDUCED FROM LOAN BALANCE(GREATER THAN 0):";
					cin >> reduce_amount;
				}

				l_account.reduce_loan_balance(reduce_amount);
				l_file.seekg(0,ios::cur);
				l_file.seekp(l_file.tellg() - sizeof(l_account));
				l_file.write((char*)&l_account,sizeof(loan_account));
				cout << "\nLOAN AMOUNT REDUCED FROM THE ACCOUNT";
			}
		}
	}
	if (found == 0)
	{
		cout << "\nTHE SPECIFIED ACCOUNT IS NOT FOUND!";
	}
	l_file.close();
	cout << "\nPRESS ENTER TO CONTINUE...";
	getch();
}
//Function to add loan amount to an existing loan account
void add_loan_amount()
{
	// Get the account number to deposit amount
	int tmp_acc_num;
	int add_amount = 0;
	cout<<"\nENTER THE ACCOUNT NUMBER TO ADD LOAN AMOUNT:";
	cin >> tmp_acc_num;
	loan_account l_account;
	fstream l_file;
	int found = 0;
	l_file.open("loan_account.dat", ios::in | ios::out | ios::binary);
	if (l_file.fail())
	{
		cout << "Error: The file loan_account.dat could not be opened!";
		cout << "\nPRESS ENTER TO CONTINUE...";
		getch();
		return;
	}
	while ((l_file.read((char *)&l_account, sizeof(loan_account))) && (found == 0))
	{
		if (tmp_acc_num == l_account.get_acc_number())
		{
			found = 1;
			l_account.show_acc_details();
			if (!l_account.acc_active()) //Inactive account; can not transact
			{
				cout << "\nTHE ACCOUNT IS CLOSED; NO TRANSACTIONS ALLOWED";
			}
			else
			{
				while (add_amount <= 0)
				{
					cout<<"\nENTER THE LOAN AMOUNT TO BE ADDED (GREATER THAN 0):";
					cin >> add_amount;
				}
				l_account.increase_loan_balance(add_amount);
				l_file.seekg(0,ios::cur);
				l_file.seekp(l_file.tellg() - sizeof(l_account));
				l_file.write((char*)&l_account,sizeof(loan_account));
				cout << "\nLOAN AMOUNT ADDED TO THE LOAN ACCOUNT";
			}
		}
	}
	if (found == 0)
	{
		cout << "\nTHE SPECIFIED ACCOUNT IS NOT FOUND!";
	}
	l_file.close();	
	cout << "\nPRESS ENTER TO CONTINUE...";
	getch();	
}
//Function to Modify Transaction or Loan account details
void modify_account()
{
	char type = 'X';
	//Get the account type to modify - Transaction or Loan
	while (type != 'T' && type != 'L')
	{
		cout<<"\nENTER THE TYPE OF ACCOUNT TO MODIFY (T=TRANSACTION; L=LOAN):";
		cin >> type;
		type = toupper(type);
	}
	// Get the account number to be closed
	int tmp_acc_num;
	cout<<"\nENTER THE ACCOUNT NUMBER TO BE MODIFIED:";
	cin >> tmp_acc_num;
	// Update the Transaction account
	if ( type == 'T')
	{
		txn_account t_account;
		fstream t_file;
		int found = 0;
		t_file.open("txn_account.dat", ios::in | ios::out | ios::binary);
		if (t_file.fail())
		{
			cout << "Error: The file txn_account.dat could not be opened!";
			cout << "\nPRESS ENTER TO CONTINUE...";
			getch();	
			return;
		}
		while ((t_file.read((char *)&t_account, sizeof(txn_account))) && (found == 0))
		{	
			if (tmp_acc_num == t_account.get_acc_number())
			{
				found = 1;
				if (!t_account.acc_active()) //Inactive account; can not change
				{
					cout << "\nTHE ACCOUNT IS INACTIVE; NO UPDATES ALLOWED";
				}
				else
				{
					t_account.modify_account();
					t_file.seekg(0,ios::cur);
					t_file.seekp(t_file.tellg() - sizeof(t_account));
					t_file.write((char*)&t_account,sizeof(txn_account));
					cout << "\nACCOUNT DETAILS MODIFICATION COMPLETED";
				}
			}
		}
		if (found == 0)
		{
			cout << "\nTHE SPECIFIED ACCOUNT IS NOT FOUND!";
		}
		t_file.close();	
			cout << "\nPRESS ENTER TO CONTINUE...";
			getch();	
	}
	else
	{
		loan_account l_account;
		fstream l_file;
		int found = 0;
		l_file.open("loan_account.dat", ios::in | ios::out | ios::binary);
		if (l_file.fail())
		{
			cout << "Error: The file txn_account.dat could not be opened!";
			cout << "\nPRESS ENTER TO CONTINUE...";
			getch();	
			return;
		}
		while ((l_file.read((char *)&l_account, sizeof(loan_account))) && (found == 0))
		{	
			if (tmp_acc_num == l_account.get_acc_number())
			{
				found = 1;
				if (!l_account.acc_active()) //Inactive account; can not change
				{
					cout << "\nTHE ACCOUNT IS CLOSED; NO UPDATES ALLOWED";
				}
				else
				{
					l_account.modify_account();
					l_file.seekg(0,ios::cur);
					l_file.seekp(l_file.tellg() - sizeof(l_account));
					l_file.write((char*)&l_account,sizeof(loan_account));
					cout << "\n THE LOAN ACCOUNT DETAILS MODIFICATION COMPLETED";
				}
			}
		}
		if (found == 0)
		{
			cout << "\nTHE SPECIFIED LOAN ACCOUNT IS NOT FOUND!";
		}
		l_file.close();		
		cout << "\nPRESS ENTER TO CONTINUE...";
		getch();	
	}
}

