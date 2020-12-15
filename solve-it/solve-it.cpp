/*!< UVA 10341 */
/*!< Divisao e Conquista */

#include <iostream>
using namespace std;
#include <vector>
#include <cmath>

#define EPSLON 1e-9
#define MIN 0
#define MAX 1

int p, q, r, s, t, u;

double f(const double x) {
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * (x*x) + u; 
}

void solve_it() {
    double fx;
    if(f(MIN) * f(MAX) > 0) {
        cout << "No solution" << endl;
    } else {
        double max = MAX;
        double min = MIN;
        while(fabs(max-min) > EPSLON) { 
            double middle = (max + min)/2;
            fx = f(middle);
            if(fx > 0)
                min = middle;
            else
                max = middle;
        }
        printf("%.4lf\n", min);
    }
}

int main(void) {
    while(cin>>p>>q>>r>>s>>t>>u)
        solve_it();
    return 0;
}
