#include <CppUTest/CommandLineTestRunner.h>
#include "define.h"
#include "1dim_fem.h"
#include "utility.h"

double eq[N][N+1]={0};
double ans[N+1]={0};
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
    int pivot_i = _select_pivot(eq, n, 0);
    CHECK_EQUAL(2, pivot_i);
    _swap_row(eq, n, pivot_i, 0);
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
    _normalize_row(eq, n, 0);
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
    _subtract_row(eq, n, 0);
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
    _solve_equations(eq, n, ans);
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

TEST (TestFuncGroup, generate_params_linear){
    int params_count = 2;
    double params_all[SERIES_MAX][PARAMS_MAX] = {0};
    double params_range[][3] = {
        {0, 1, 2},
        {20, 30, 1},
    };
    
    int series_count = generate_params_linear(params_count, params_all, params_range);

    DOUBLES_EQUAL(0.0 ,params_all[0][0], TOLERANCE);    
    DOUBLES_EQUAL(20. ,params_all[0][1], TOLERANCE);
    DOUBLES_EQUAL(0.5 ,params_all[1][0], TOLERANCE);
    DOUBLES_EQUAL(20. ,params_all[1][1], TOLERANCE);
    DOUBLES_EQUAL(1.0 ,params_all[2][0], TOLERANCE);
    DOUBLES_EQUAL(20. ,params_all[2][1], TOLERANCE);
    DOUBLES_EQUAL(0.0 ,params_all[3][0], TOLERANCE);
    DOUBLES_EQUAL(30. ,params_all[3][1], TOLERANCE);
    DOUBLES_EQUAL(0.5 ,params_all[4][0], TOLERANCE);
    DOUBLES_EQUAL(30. ,params_all[4][1], TOLERANCE);
    DOUBLES_EQUAL(1.0 ,params_all[5][0], TOLERANCE);
    DOUBLES_EQUAL(30. ,params_all[5][1], TOLERANCE);
    CHECK_EQUAL(6, series_count);
}

int main(int ac, char** av){
    return CommandLineTestRunner::RunAllTests(ac, av);
}
