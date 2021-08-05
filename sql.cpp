#include <bits/stdc++.h>
using namespace std;

class sql
{
public:
	sql() { system("cls"); }
	void create_file(int &, string &, string &, vector<string> &, string &);
	void add_instructor(int &);
	bool check_id(int &);
	bool check_id_password(int &, string &, string &);
	vector<string> get_courses(int &);
	void add_student();
	int create_student_record(int &, string &, string &, string &, vector<int> &);
	vector<string> get_student_record(int &);
	vector<string> get_instructor(int &);
	~sql() {}
};

bool sql::check_id_password(int &id, string &password, string &type)
{
	if (type == "student")
	{
		int instructor_id = (id / 10000) + 100;
		string file_name = to_string(instructor_id) + ".csv";
		if (check_id(instructor_id))
		{
			int location = (id % 10000);
			int line_number = 0;
			fstream file(file_name, std::fstream::in);
			string check_password;
			while (!file.eof())
			{
				line_number++;
				getline(file, check_password);
				if (line_number == location)
					break;
			}
			getline(file, check_password, ',');
			getline(file, check_password, ',');
			if (check_password == password)
				return true;
		}
	}
	else if (type == "instructor")
	{
		string file_name = to_string(id) + ".csv";
		if (check_id(id))
		{
			fstream file(file_name, std::fstream::in);
			string check_password;
			getline(file, check_password, ',');
			getline(file, check_password, ',');
			if (check_password == password)
				return true;
		}
	}
	return false;
}

vector<string> sql::get_instructor(int &id)
{
	string file_name = to_string(id) + ".csv";
	fstream file(file_name, std::fstream::in);
	vector<string> details(9, "NULL");
	for (int i = 0; i < 9; i++)
	{
		getline(file, details.at(i), ',');
	}
	file.close();
	return details;
}

vector<string> sql::get_student_record(int &id)
{
	int file_code = (id / 10000) + 100;
	string file_name = to_string(file_code) + ".csv";
	fstream file(file_name, std::fstream::in);
	int location = (id % 10000) + 1;
	string line;
	vector<string> details(9, "NULL");
	for (int i = 0; i < location - 1; i++)
	{
		getline(file, line);
	}
	for (int i = 0; i < 9; i++)
	{
		getline(file, details.at(i), ',');
	}
	file.close();
	return details;
}

void sql::create_file(int &number, string &fname, string &lname, vector<string> &courses, string &password)
{
	int file_code = 100 + number;
	string file_name = to_string(file_code) + ".csv";
	fstream file(file_name, std::fstream::out);
	file << setw(5) << file_code << "," << password << "," << fname << "," << lname << ",";
	for (int i = 0; i < 5; i++)
	{
		file << courses.at(i) << ",";
	}
	file.close();
}

void sql::add_instructor(int &number)
{
	string First_name, Last_name, password;
	vector<string> courses(5, "NULL");
	cout << "Enter first name of the instructor: ";
	getline(cin, First_name);
	cout << "\nEnter last name of the instructor: ";
	getline(cin, Last_name);
	for (int i = 0; i < 5; i++)
	{
		cout << "\n Enter " << i + 1;
		switch (i)
		{
		case 0:
			cout << "st course under the instructor: ";
			break;
		case 1:
			cout << "nd course under the instructor: ";
			break;
		case 2:
			cout << "rd course under the instructor: ";
			break;
		default:
			cout << "th course under the instructor: ";
			break;
		}
		string course;
		getline(cin, courses.at(i));
	}
	cout << "\nCreate password: ";
	getline(cin, password);
	create_file(number, First_name, Last_name, courses, password);
}

bool sql::check_id(int &id)
{
	string file_name = to_string(id) + ".csv";
	fstream file(file_name, std::fstream::in);
	if (file.is_open())
	{
		file.close();
		return true;
	}
	else
		return false;
}

vector<string> sql::get_courses(int &id)
{
	vector<string> courses;
	string file_name = to_string(id) + ".csv";
	fstream file(file_name, std::fstream::in);
	string course;
	for (int i = 0; i < 9; i++)
	{
		switch (i)
		{
		case 0:
			getline(file, course, ',');
			break;
		case 1:
			getline(file, course, ',');
			break;
		case 2:
			getline(file, course, ',');
			break;
		case 3:
			getline(file, course, ',');
			break;
		default:
			getline(file, course, ',');
			courses.push_back(course);
			break;
		}
	}
	return courses;
}

int sql::create_student_record(int &id, string &password, string &fname, string &lname, vector<int> &marks)
{
	string file_name = to_string(id) + ".csv";
	fstream file(file_name, std::fstream::in);
	string litter;
	int student_id = 0;
	while (!file.eof())
	{
		getline(file, litter);
		student_id++;
	}
	file.close();
	student_id = (id - 100) * 10000 + student_id;
	file.open(file_name, std::fstream::app);
	file << "\n"
		 << student_id << "," << password << "," << fname << "," << lname << ",";
	for (int i = 0; i < 5; i++)
	{
		file << marks.at(i) << ",";
	}
	file.close();
	return student_id;
}

void sql::add_student()
{
	int id;
	string fname, lname, password;
	vector<int> marks(5, 0);
	cout << "Enter instructor's id of the student: ";
	cin >> id;
	if (check_id(id))
	{
		cout << "\nEnter first name of student: ";
		cin >> fname;
		cout << "\nEnter last name of student: ";
		cin >> lname;
		vector<string> courses = get_courses(id);
		for (int i = 0; i < 5; i++)
		{
			cout << "\n Enter marks obtained in " << courses.at(i) << ": ";
			int mark;
			cin >> marks.at(i);
		}
		cout << "\nCreate password for student: ";
		cin >> password;
		int student_id = create_student_record(id, password, fname, lname, marks);
		system("cls");
		cout << "\nStudent Id is : " << student_id << "\n\n";
		cout << "Password is : " << password << "\n\n";
	}
	else
	{
		cout << "Instructor not available! \n";
	}
	system("pause");
}

int main()
{
	cout << "Hello";
	sql test;
	int x = 10001, y = 1;
	string password = "123-345", type = "student";
	test.add_student();
	bool result = test.check_id_password(x, password, type);
	cout << result << "\n";
	result = true;
	cout << result << "\n";
	/*test.add_instructor(x);
	test.add_student();
	fstream file("101.csv", std::fstream::in | std::fstream::app );
	string line;
	getline(file, line);
	cout << line.length();
	file << "\nHi";*/

	return 0;
}
