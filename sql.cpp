#include <bits/stdc++.h>
using namespace std;

#if defined(_WIN32) || defined(_WIN64)
static string clear = "cls";
static string command = "move /Y temp.csv ";
#elif __linux__
static string clear = "clear";
static string command = "mv temp.csv ";
#endif

class sql
{
public:
	sql() { system(clear.c_str()); }
	void create_file(int &, string &);
	bool check_id(int &);
	bool check_id_password(int &, string &, string &);
	vector<string> get_courses(int &);
	void update_student(int &, string &);
	int create_student_record(int &, string &);
	vector<string> get_student_record(int &);
	vector<string> get_instructor(int &);
	~sql() {}
};

class terminal : public sql
{
public:
	terminal() { home(); }
	void home();
	void student();
	void instructor();
	void instructor(int &, string &);
	void admin();
	void display_record(string &, int &);
	void update_record(string &);
	void insert_record(string &, int &);
};

void sql::update_student(int &id, string &details)
{
	int file_code = (id / 10000) + 100;
	string file_name = to_string(file_code) + ".csv";
	fstream file(file_name, std::fstream::in);
	fstream temp("temp.csv", std::fstream::out);
	string line;
	int location = (id % 10000) + 1;
	int line_number = 0;
	while (!file.eof())
	{
		line_number++;
		if (line_number == location)
		{
			getline(file, line);
			temp << "\n"
				 << details;
		}
		else
		{
			getline(file, line);
			if (line == "")
				;
			else if (line_number == 1)
				temp << line;
			else
				temp << "\n"
					 << line;
		}
	}
	temp.close();
	file.close();
	string move = command + file_name;
	system(move.c_str());
}

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

void sql::create_file(int &number, string &details)
{
	int file_code = 100 + number;
	string file_name = to_string(file_code) + ".csv";
	fstream file(file_name, std::fstream::out);
	file << details;
	file.close();
	fstream admin("admin.csv", std::fstream::out);
	admin << (number + 1);
	admin.close();
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
		if (i > 3)
		{
			getline(file, course, ',');
			courses.push_back(course);
		}
		else
			getline(file, course, ',');
	}
	return courses;
}

int sql::create_student_record(int &id, string &details)
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
		 << student_id << ","
		 << details;
	file.close();
	return student_id;
}

void terminal::home()
{
	cout << "\n1. Student Login\n\n2. Instructor Login\n\n3. Admin Login\n\n";
	int option;
	cout << "Please select an option for login[example: 1] ";
	cin >> option;
	switch (option)
	{
	case 2:
		system(clear.c_str());
		instructor();
		break;
	case 3:
		system(clear.c_str());
		admin();
		break;
	default:
		system(clear.c_str());
		student();
		break;
	}
}

void terminal::student()
{
	string password, type = "student";
	int id;
	cout << "\nEnter Student ID:";
	cin >> id;
	cin.ignore();
	cout << "\nEnter Password:";
	getline(cin, password);
	bool verify = check_id_password(id, password, type);
	if (verify == false)
		cout << "\nIncorrect ID or password\n";
	else
	{
		system(clear.c_str());
		display_record(type, id);
	}
	int pause_key = getchar();
	system(clear.c_str());
	home();
}

void terminal::instructor()
{
	string password, type = "instructor";
	int id;
	cout << "\nEnter Instructor ID: ";
	cin >> id;
	cin.ignore();
	cout << "\nEnter Password: ";
	getline(cin, password);
	bool verify = check_id_password(id, password, type);
	if (verify == false)
	{
		cout << "\nIncorrect ID or password\n";
		int pause_key = getchar();
		home();
	}
	else
		instructor(id, type);
}

void terminal::instructor(int &id, string &type)
{
	system(clear.c_str());
	cout << "1. Add Student Record\n\n2. Get Student Records\n\n3. Update Student Records\n\n4. Home\n\nEnter an option number[example: 1]: ";
	int option;
	cin >> option;
	cin.ignore();
	switch (option)
	{
	case 1:
		type = "student";
		system(clear.c_str());
		insert_record(type, id);
		break;
	case 3:
		type = "student";
		system(clear.c_str());
		update_record(type);
		break;
	case 2:
		type = "instructor";
		system(clear.c_str());
		display_record(type, id);
		break;
	default:
		system(clear.c_str());
		home();
		break;
	}
	int pause_key = getchar();
	system(clear.c_str());
	instructor(id, type);
}

void terminal::admin()
{
	cout << "1. Add Instructor\n\n2. Update Instructor\n\nEnter an option number[example: 1]: ";
	int input;
	cin >> input;
	system(clear.c_str());
	string type = "instructor";
	if (input == 1)
	{
		fstream file("admin.csv", std::fstream::in);
		int id;
		file >> id;
		file.close();
		insert_record(type, id);
	}
	else if (input == 2)
	{
		cout << "Enter Instructor's id that is to be updated: ";
		int id;
		cin >> id;
		id -= 100;
		insert_record(type, id);
	}
	int pause_key = getchar();
	system(clear.c_str());
	home();
}

void terminal::display_record(string &type, int &id)
{
	if (type == "student")
	{
		int courses_id = (id / 10000) + 100;
		vector<string> details = get_student_record(id);
		vector<string> courses = get_courses(courses_id);
		cout << "Student Name: " << details[3] << ", " << details[2] << "\n\n";
		for (int i = 0; i < 2 * courses.size(); i++)
		{
			if (i < courses.size())
				cout << "\t" << courses[i] << " |\t";
			else if (i == courses.size())
				cout << "\n\t" << setw(courses[i - 5].length()) << details[i - 1] << " |\t";
			else
				cout << "\t" << setw(courses[i - 5].length()) << details[i - 1] << " |\t";
		}
	}
	else if (type == "instructor")
	{
		vector<string> instructor_details = get_instructor(id);
		cout << "Instructor: " << instructor_details[3] << ", " << instructor_details[2] << "\n\n\tStudent Name |\t";
		for (int i = 0; i < 5; i++)
		{
			cout << "\t" << instructor_details[i + 4] << " |\t";
		}
		string dashes(120, '-');
		cout << "\n"
			 << dashes;
		id = (id - 100) * 10000 + 1;
		vector<string> student_details = get_student_record(id);
		while (true)
		{
			if (student_details[0] == "NULL" | student_details[0] == "")
				break;
			else
			{
				string name = student_details[2] + " " + student_details[3];
				name = name.substr(0, 12);
				cout << "\n\t" << name << " |\t";
				for (int i = 0; i < 5; i++)
				{
					cout << "\t" << setw(instructor_details[i + 4].length()) << student_details[i + 4] << " |\t";
				}
				id++;
				student_details = get_student_record(id);
			}
		}
	}
}

void terminal::insert_record(string &type, int &id)
{
	if (type == "student")
	{
		string details, input;
		vector<string> courses = get_courses(id);
		cout << "\nEnter login password for student: ";
		getline(cin, input);
		details = input;
		details.append(",");
		cout << "\nEnter first name of student: ";
		getline(cin, input);
		details += input;
		details.append(",");
		cout << "\nEnter last name of student: ";
		getline(cin, input);
		details += input;
		details.append(",");
		for (int i = 0; i < courses.size(); i++)
		{
			cout << "\nEnter marks obtained in " << courses[i] << ": ";
			getline(cin, input);
			details += input;
			details.append(",");
		}
		int generate_id = create_student_record(id, details);
		system(clear.c_str());
		cout << "Student Id is: " << generate_id << "\n";
		display_record(type, generate_id);
	}
	else if (type == "instructor")
	{
		cin.ignore();
		string details = to_string(id), input;
		details.append(",");
		cout << "Enter login password for instructor: ";
		getline(cin, input);
		details += input;
		details.append(",");
		cout << "\nEnter first name of instructor: ";
		getline(cin, input);
		details += input;
		details.append(",");
		cout << "\nEnter last name of instructor: ";
		getline(cin, input);
		details += input;
		details.append(",");
		for (int i = 0; i < 5; i++)
		{
			cout << "\nName of Subject " << i + 1 << ": ";
			getline(cin, input);
			details += input;
			details.append(",");
		}
		create_file(id, details);
		cout << "\nInstructor Id is: " << 100 + id << "\n";
	}
}

void terminal::update_record(string &type)
{
	if (type == "student")
	{
		cout << "Enter ID of the student: ";
		int id;
		cin >> id;
		cin.ignore();
		string details = to_string(id), input;
		details.append(",");
		int courses_id = (id / 10000) + 100;
		vector<string> courses = get_courses(courses_id);
		system(clear.c_str());
		cout << "Enter login password for student: ";
		getline(cin, input);
		details += input;
		details.append(",");
		cout << "\nEnter first name of student: ";
		getline(cin, input);
		details += input;
		details.append(",");
		cout << "\nEnter last name of student: ";
		getline(cin, input);
		details += input;
		details.append(",");
		for (int i = 0; i < courses.size(); i++)
		{
			cout << "\nEnter marks obtained in " << courses[i] << ": ";
			getline(cin, input);
			details += input;
			details.append(",");
		}
		update_student(id, details);
		system(clear.c_str());
		display_record(type, id);
	}
}

int main()
{
	terminal start;
	return 0;
}
