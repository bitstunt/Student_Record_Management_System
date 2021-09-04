# Student_Record_Management_System
This a free and open code to build a raw student record management system. The ownership is claimed by *bitstunt*. This program is meant to help university/college students who want a quick reference for their term projects.
## Details:
The program builds a console based application to manage student records. This record management program is divided in two parts namely, *frontend* and *backend*. *frontend* is named as *terminal* class in the code which is a derived class of *backend* which is named as *sql* class in the code. This partition is inspired from web-development process.
## Working:
Student records are recorded under the instructor's details. The code is hard coded to accept 5 subjects under one instructor. Cloner may consider to modify it for dynamic number of subjects as it would only require some changes in functions of *terminal* class. The sql class is hard coded to generate the ids and file names in a specific format. This can be also modified as per programmers choice.
    The management system provides three modes of login.<br />
    1. Admin Login <br />
    2. Instructor Login <br />
    3. Student Login <br />
Student and Instructor Login requires password and id generated at the time of creation of their respective records. Admin Login doesn't require any password. This also provides a scope of modification in the code. <br />
All records are stored in seperate _.csv_  files for each instructor. The _.csv_  files can be converted in excel sheets and columns' name can be further modified to represent some meaningful data.
### Admin Login:
It has two options: <br />
1. Update Instructor: _It will delete all the records under the specified instructor and just add the new instructor with recently provided details. It is the worst thing to be selected unless you want a new instructor with the existing id._ <br />
2. Add Instructor: _Name is enough to explain its functions._ <br />
### Instructor Login:
It has four options: <br />
1. Add Student Records <br />
2. Get Student Records <br />
3. Update Student Records <br />
4. Home <br />
_Precautions:_ Please, select option two only once per login as any number of selection of the option would lead to NULL output.
### Student Login:
It just displays student's record.
