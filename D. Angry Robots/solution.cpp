#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endll '\n'

#define deg2Rad (3.141592653589/180.0)

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    double v, theta, x, y, t; 
    cin >> v >> theta >> x >> y >> t;

    double viy = v * sin(deg2Rad*theta), vix = v * cos(deg2Rad*theta);
    double g = 9.80665;

    double yf = -1*(g/2)*(t*t) + viy*t + y;
    double xf = vix*t + x;
    cout << xf << ' ' << yf << endll;
}
