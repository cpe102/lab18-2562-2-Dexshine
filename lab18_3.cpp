#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<iomanip>
using namespace std;

struct student{
	//Define struct student with fours member (name ,id , gender, gpa);
	string name;
	int id;
	string gender;
	double gpa;
};

struct course{
	string name;
	int id;
	vector<string> lecture_list;
	vector<student *> student_list;
};

student * findstudent(vector<student> allstudents,int key){ //Correct this line
	for(unsigned int i = 0; i < allstudents.size(); i++){
		if(allstudents[i].id  == key) return &allstudents[i];
	}
}

void printreport(vector<course> allcourses){
	for(unsigned int i = 0;i < allcourses.size(); i++){
		cout << "-----------------------------------------------------------------------------\n";
		cout << "Course:\t\t" << allcourses[i].name << " ("<< allcourses[i].id << ")\n\n";
		cout << "Lecturers:\t";
		for(unsigned int j = 0; j < allcourses[i].lecture_list.size();j++){
			if(j != 0) cout << ", ";
			cout << allcourses[i].lecture_list[j];
		} 
		cout << "\n\nStudents:\t";
		for(unsigned int j = 0; j < allcourses[i].student_list.size();j++){
			if(j != 0) cout << "\t\t";
			cout << setw(16) << left << allcourses[i].student_list[j]->name << "\t";
			cout << allcourses[i].student_list[j]->id << "\t";
			cout << allcourses[i].student_list[j]->gender << "\t";
			cout << allcourses[i].student_list[j]->gpa << "\n";
		} 
		
	}
	cout << "-----------------------------------------------------------------------------\n";
}

int main(){
	ifstream student_file("students.txt");
	ifstream course_file("courses.txt");
	vector<student> allstudents;
	vector<course> allcourses;
	
	string textline;
	while(getline(student_file,textline)){
		student s;
		string gender;
		string name; 
		double gpa;
		int idx,id;
		//Assign value to the members of struct s;
		//char format1[] = "%[^,] %d,%s,%f";
		//sscanf(textline.c_str(),format1,name,id,gender,gpa);
		idx = textline.find_first_of(",");
		name = textline.substr(0,idx);
		id = atoi(textline.substr(idx+1,4).c_str());
		gender  = textline.substr(idx+6,1);
		gpa = atof(textline.substr(idx+8,4).c_str());
		s = {name,id,gender,gpa};
		allstudents.push_back(s); 
				
	}
	int i = 0,j=0;
	int state = 1;
	while(getline(course_file,textline)){
		if(state == 1){
			course c;
			int loc = textline.find_first_of('(');
			c.name = textline.substr(0,loc-1);
			c.id = atof(textline.substr(loc+1,5).c_str());
			getline(course_file,textline);
			allcourses.push_back(c);
			state = 2;			
		}else if(state == 2){
			if(textline == "> Students"){
				state = 3;
			}else{
				//Append allcourses[ตัวล่าสุด].lecture_list;
				allcourses[i].lecture_list.push_back(textline.c_str());
			}			
		}else{
			if(textline == "---------------------------------------"){
				++i;
				state = 1;
			}else{
				student *p = findstudent(allstudents,atoi(textline.c_str())); //*p = &allstudents[i]
				//Append p ไปที่ allcourses[ตัวล่าสุด].student_list;
				student *x = p;
				allcourses[i].student_list.push_back(x);
			}

		}
	}
	printreport(allcourses);
	student_file.close();
	course_file.close();
	return 0;
}