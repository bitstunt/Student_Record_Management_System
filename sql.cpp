#include <bits/stdc++.h>
using namespace std;

#if defined(_WIN32) || defined(_WIN64)
	string clear = "cls";
#elif __linux__
	string clear = "clear";
#endif

class sql
{
	public:
		sql() {system(clear.c_str()); }
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

void sql::update_student(int &id, string &details)
{
	int file_code = (id / 10000) + 100;
	string file_name = to_string(file_code) + ".csv";
	fstream file(file_name, std::fstream::in);
	fstream temp("temp.csv", std::fstream::out);
	string line;
	int location = (id % 10000) + 1;
	int line_number = 0;
	while(!file.eof())	
	{
		line_number++;
		if (line_number == location)
		{
			getline(file, line);
			temp << details << "\n";
		}
		else
		{
			getline(file, line);
			if( line == "");
			else
			{
				temp << line << "\n";
			}
		}
	}
	temp.close();
	file.close();
	string command = "mv temp.csv " + file_name;
	system(command.c_str());
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
	file << "\n" << details;
	file.close();
	return student_id;
}

int main()
{

	cout << "Hello";
	sql test;
	int x = 10001, y = 1;
	string details = "10001,123-5555456,Mukta,Kumari,100,100,100,100,100,";
	test.update_student(x, details);

	return 0;
}
