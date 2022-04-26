#include <stdio.h>
#define N 100

void calc_eq(double eq[][N+1], int NE, double L, double Q, double A, double lambda){
    for (int i=0; i<NE; i++){
        // K
        double k_abs = lambda * A / L;
        eq[i][i] += k_abs;
        eq[i][i+1] -= k_abs;
        eq[i+1][i] -= k_abs;
        eq[i+1][i+1] += k_abs;
        
        // f
        double f_abs = Q * A * L / 2;
        eq[i][NE+1] += f_abs;
        eq[i+1][NE+1] += f_abs;
    }
}

void solve_equations(double eq[][N+1], int NE){

}

int main(void){
    // 入力
    int NE = 4;
    double L = 1.0;
    double Q = 1.0;
    double A = 1.0;
    double lambda = 1.0;

    double eq[N][N+1] = {0};
    calc_eq(eq, NE, L, Q, A, lambda);
    solve_equations(eq, NE);

    return 0;
}
