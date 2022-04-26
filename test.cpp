#include <CppUTest/CommandLineTestRunner.h>
#include "1dim_fem.h"

double eq[N][N+1]={0};
int NE=2;
int n=3;
double TOLERANCE = 0.0001;

TEST_GROUP(TestFuncGroup){
    TEST_SETUP(){
        eq[0][0]=1;
        eq[0][1]=1;
        eq[0][2]=1;
        eq[0][3]=6;
        eq[1][0]=2;
        eq[1][1]=3;
        eq[1][2]=-1;
        eq[1][3]=5;
        eq[2][0]=3;
        eq[2][1]=-1;
        eq[2][2]=2;
        eq[2][3]=7; 
    }
};

TEST(TestFuncGroup, internal_functions){
    int pivot_i = select_pivot(eq, n, 0);
    CHECK_EQUAL(2, pivot_i);
    swap_row(eq, n, pivot_i, 0);
    DOUBLES_EQUAL(3  ,eq[0][0], TOLERANCE);
    DOUBLES_EQUAL(-1 ,eq[0][1], TOLERANCE);
    DOUBLES_EQUAL(2  ,eq[0][2], TOLERANCE);
    DOUBLES_EQUAL(7  ,eq[0][3], TOLERANCE);
    DOUBLES_EQUAL(2  ,eq[1][0], TOLERANCE);
    DOUBLES_EQUAL(3  ,eq[1][1], TOLERANCE);
    DOUBLES_EQUAL(-1 ,eq[1][2], TOLERANCE);
    DOUBLES_EQUAL(5  ,eq[1][3], TOLERANCE);
    DOUBLES_EQUAL(1  ,eq[2][0], TOLERANCE);
    DOUBLES_EQUAL(1  ,eq[2][1], TOLERANCE);
    DOUBLES_EQUAL(1  ,eq[2][2], TOLERANCE);
    DOUBLES_EQUAL(6  ,eq[2][3], TOLERANCE);
    normalize_row(eq, n, 0);
    DOUBLES_EQUAL(1     ,eq[0][0], TOLERANCE);
    DOUBLES_EQUAL(-1./3 ,eq[0][1], TOLERANCE);
    DOUBLES_EQUAL(2./3  ,eq[0][2], TOLERANCE);
    DOUBLES_EQUAL(7./3  ,eq[0][3], TOLERANCE);
    DOUBLES_EQUAL(2     ,eq[1][0], TOLERANCE);
    DOUBLES_EQUAL(3     ,eq[1][1], TOLERANCE);
    DOUBLES_EQUAL(-1    ,eq[1][2], TOLERANCE);
    DOUBLES_EQUAL(5     ,eq[1][3], TOLERANCE);
    DOUBLES_EQUAL(1     ,eq[2][0], TOLERANCE);
    DOUBLES_EQUAL(1     ,eq[2][1], TOLERANCE);
    DOUBLES_EQUAL(1     ,eq[2][2], TOLERANCE);
    DOUBLES_EQUAL(6     ,eq[2][3], TOLERANCE);  
    subtract_row(eq, n, 0);
    DOUBLES_EQUAL(1     ,eq[0][0], TOLERANCE);
    DOUBLES_EQUAL(-1./3 ,eq[0][1], TOLERANCE);
    DOUBLES_EQUAL(2./3  ,eq[0][2], TOLERANCE);
    DOUBLES_EQUAL(7./3  ,eq[0][3], TOLERANCE);
    DOUBLES_EQUAL(0     ,eq[1][0], TOLERANCE);
    DOUBLES_EQUAL(11./3 ,eq[1][1], TOLERANCE);
    DOUBLES_EQUAL(-7./3 ,eq[1][2], TOLERANCE);
    DOUBLES_EQUAL(1./3  ,eq[1][3], TOLERANCE);
    DOUBLES_EQUAL(0     ,eq[2][0], TOLERANCE);
    DOUBLES_EQUAL(4./3  ,eq[2][1], TOLERANCE);
    DOUBLES_EQUAL(1./3  ,eq[2][2], TOLERANCE);
    DOUBLES_EQUAL(11./3 ,eq[2][3], TOLERANCE);    
}

TEST (TestFuncGroup, solve_equations){
    solve_equations(eq, n);
    DOUBLES_EQUAL(1 ,eq[0][0], TOLERANCE);
    DOUBLES_EQUAL(0 ,eq[0][1], TOLERANCE);
    DOUBLES_EQUAL(0 ,eq[0][2], TOLERANCE);
    DOUBLES_EQUAL(1 ,eq[0][3], TOLERANCE);
    DOUBLES_EQUAL(0 ,eq[1][0], TOLERANCE);
    DOUBLES_EQUAL(1 ,eq[1][1], TOLERANCE);
    DOUBLES_EQUAL(0 ,eq[1][2], TOLERANCE);
    DOUBLES_EQUAL(2 ,eq[1][3], TOLERANCE);
    DOUBLES_EQUAL(0 ,eq[2][0], TOLERANCE);
    DOUBLES_EQUAL(0 ,eq[2][1], TOLERANCE);
    DOUBLES_EQUAL(1 ,eq[2][2], TOLERANCE);
    DOUBLES_EQUAL(3 ,eq[2][3], TOLERANCE);     
}

int main(int ac, char** av){
    return CommandLineTestRunner::RunAllTests(ac, av);
}
