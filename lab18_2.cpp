//Modify function overlap() form lab18_1.cpp by using pointers as input arguments.
#include<iostream>
#include<algorithm>
using namespace std;

struct Rect{
	double x,y,w,h;
};

double overlap(Rect *,Rect *);

int main(){

	double x1,y1,w1,h1,x2,y2,w2,h2;
	cout << "Please input Rect 1 (x y w h): ";
	cin >> x1 >> y1 >> w1 >> h1;
	cout << "Please input Rect 2 (x y w h): ";
	cin >> x2 >> y2 >> w2 >> h2;

	Rect rec1 = {x1,y1,w1,h1};
	Rect rec2 = {x2,y2,w2,h2};	
    Rect *p1 = &rec1;
    Rect *p2 = &rec2;
	
	cout << "Overlap area = " << overlap(p1,p2);	
	return 0;
}

double overlap(Rect *rec1,Rect *rec2){
	bool xlap,ylap;
	double wide,height,area;
	if(max(rec1->x , rec2->x)<min(rec1->x+rec1->w , rec2->x+rec2->w)){
		xlap = 1;
	}else xlap = 0;
	if(min(rec1->y,rec2->y)>min(rec1->y,rec2->y-rec2->h)){
		ylap = 1;
	}else ylap = 0;
	if(xlap&&ylap){
		wide = min(rec1->x+rec1->w,rec2->x+rec2->w) - max(rec1->x,rec2->x);
		height = min(rec1->y,rec2->y) - min(rec1->y,rec2->y-rec2->h);
		area = wide * height;
		return area;
	}else return 0;

}
