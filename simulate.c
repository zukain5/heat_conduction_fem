#include "1dim_fem.h"
#include "utility.h"

int main(void){
    fem_parameter fem;
    fem.NE = 300;
    fem.length = 4.0;
    fem.A = 1.0;
    fem.lambda = 1.0;

    double Q[N+1] = {0};

    // 境界条件
    boundary_condition bound;
    bound.type_min = 0; // 0が基本・1が自然
    bound.type_max = 1; // 0が基本・1が自然
    bound.value_min = 0;
    bound.value_max = 0;

    double x[N+1] = {0};
    for (int i=0; i<=fem.NE; i++){
        x[i] = fem.length / fem.NE * i;
    }

    double params[] = {1};
    calc_Q_from_fucntion(Q_linear, fem.NE, Q, x, params);

    fem.Q = &Q;

    double ans[N+1] = {0};
    fem_solver(ans, fem, bound);

    visualize(x, ans, fem.NE+1);

    return 0;
}
