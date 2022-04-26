#define N 100
#ifdef __cplusplus
extern "C" {
    extern int select_pivot(double eq[][N+1], int n, int j);
    extern void swap_row(double eq[][N+1], int n, int pivot_i, int diagonal_i);
    extern void normalize_row(double eq[][N+1], int n, int diagonal_i);
    extern void subtract_row(double eq[][N+1], int n, int diagnoal_i);
    extern void solve_equations(double eq[][N+1], int n);
}
#endif  // __cplusplus
