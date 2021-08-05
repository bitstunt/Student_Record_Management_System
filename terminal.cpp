#include<bits/stdc++.h>
using namespace std;

class terminal
{
	public:
		terminal (vector<string> &options ) 
		{
			system("clear");
			cout << "How do you want to login? \n \n";
			for (int i = 0; i < options.size(); i++)
			{
				cout << i+1 << ". " << options.at(i) << "\n \n";
			}
			cout << "Enter a valid option number[deault: 1]:";
		}
		int get_option()
		{
			int option_number;
			cin >> option_number;
			return option_number;
		}
		~terminal ( ) { }
};

class home
{
	vector<string> options{"Student Login", "Instructor Login", "Admin Login"};
	public:
	home ( )
	{
		terminal home(options);
		Invoke(home.get_option());
	}
	void Invoke(int option);
	~ home ( ) { }
};

class login_shell
{
	public:
		login_shell (string& type) { }
		~login_shell ( ) { }
		// void get_id();
		// void get_password();
		// void check_id();
		// void check_password();
		// void display_record();

};


class Student_Login
{
	public:
		Student_Login ( ) 
		{
			system("clear");
			cout << "Enter Student ID: ";
			int input; 
			cin >> input;
			cout << "\nEnter Password: ";
			cin >> input;
		}
				~Student_Login ( ) { }
};

void home::Invoke (int option)
{
	switch(option){
		case 1:
			Student_Login student;
			/* case 2:
			   Instructor_Login instructor;
			   case 3:
			   Admin_Login admin; 
			   default:
			   Student_Login student; */
	}
}

int main()
{
	home invoke;
	return 0;
}

