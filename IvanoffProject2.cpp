// Written by Nicholas A. Ivanoff
// CS450 Spring 2019
// 03.20.2019

#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<unistd.h>
#include<thread>

const int TOTAL_POINTS = 10000000;
int cirl1 = 0;
int cirl2 = 0;
int cirl3 = 0;
int cirl4 = 0;

struct Point {
    Point(double xx, double yy): x{xx}, y{yy} {}

    void print() { std::cout << "(" << x << ", " << y << ")\n"; }
    double x, y;
};

double nextRand() {
    // return a value in the range (-1, 1)
    return (rand() / double(RAND_MAX)) * 2 - 1;
} // end nextRand().

void printPointsInQuadrants(const std::vector<Point> &points) {
    // Counts and prints the number of points in each quadrant.

    int one = 0, two = 0, three = 0, four = 0; 
    for( auto iter = points.begin(); iter != points.end(); iter++ ) {
	if( iter->x > 0 && iter->y > 0 )
	    one++;
	else if( iter->x > 0 && iter->y < 0 )
	    two++;
	else if( iter->x < 0 && iter->y < 0 )
	    three++;
	else // if( iter->x < 0 && iter->y > 0 )
	    four++;
    }
    std::cout << one << " " << two << " " << three << " " << four << std::endl;
    std::cout << "Total = " << one + two + three + four << std::endl;
} // end printPoints...

int countInCircle(const std::vector<Point> &points, int c) {
    
	if (c == 1){
    for( auto iter = points.begin(); iter != points.end(); iter++ ){
	    if( iter -> x >= 0 && iter -> y >= 0){
		if( sqrt( iter->x * iter->x + iter->y * iter->y ) <= 1.0 )
	    		cirl1++;
	   		 } // end if
		}// end for 
	}// end c1

	if (c == 2){
		for( auto iter = points.begin(); iter != points.end(); iter++ ){
            if( iter -> x >= 0 && iter -> y >= 0){
                if( sqrt( iter->x * iter->x + iter->y * iter->y ) <= 1.0 )
                        cirl2++;
	    		} // end if
		} // end for
	} // end c2
	
	if (c == 3){
		for( auto iter = points.begin(); iter != points.end(); iter++ ){
            if( iter -> x >= 0 && iter -> y >= 0){
                if( sqrt( iter->x * iter->x + iter->y * iter->y ) <= 1.0 )
                        cirl3++;
	   		 }	
		}
	} // end c3

	if (c == 4){
		for( auto iter = points.begin(); iter != points.end(); iter++ ){
            if( iter -> x >= 0 && iter -> y >= 0){
                if( sqrt( iter->x * iter->x + iter->y * iter->y ) <= 1.0 )
                        cirl4++;
	    		}
		}
	} // end c4

} // end countInCircle

void generatePoints(std::vector<Point> &points) {
    // Generates TOTAL_POINTS points.

    for( int i = 0; i < TOTAL_POINTS; i++ ) { 
	points.push_back(Point(nextRand(), nextRand()));
    }
} // end genPoints()

int main() {
    srand(getpid());
    std::vector<Point> points;
    int q1 = 1, q2 = 2, q3 = 3, q4 =4; // four sections of circle/graph
    generatePoints(points);
    printPointsInQuadrants(points);
    std:: thread a [4]; // four threads
    int inCircleA[4];
    for (int i = 0; i < 4; i++){
	a[i] = std::thread(countInCircle, points, i+1); // gets all four threads
    }
    for (int i = 0; i < 4; i++){
	a[i].join(); // joins threads
    }
    int inCircleThread = 0;
    inCircleThread = cirl1 + cirl2 + cirl3 + cirl4; // adds all points
    std::cout << "PI = " << double(inCircleThread) * double(4.0) / double(TOTAL_POINTS) << std::endl; // math stuff
    return 0;
} // end main()
