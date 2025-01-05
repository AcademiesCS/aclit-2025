#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define endll '\n'

#define deg2Rad (3.141592653589/180.0)

int main()
{
    srand(time(0));

    for(int j = 0; j < 12; j++)
    {
        int v, theta, x, y, t; 
        v = rand() % 100 + 1, theta = rand() % 90, x = rand() % 100 + 1, y = rand() % 100 + 1;
        
        bool ok = false;
        for(int i = 0; i < 100; i++)
        {
            t = rand() % 100;

            double viy = v * sin(deg2Rad*(double)theta);
            double g = 9.80665;

            double yf = -1*(g/2.0)*(t*(double)t) + viy*(double)t + (double)y;

            if(yf >= 0)
            {
                ok = true;
                break;
            }
        }

        if(!ok) continue;

        FILE* f = freopen((string("test") + to_string(j) + string(".in")).c_str(), "w", stdout);

        cout << v << ' ' << theta << ' ' << x << ' ' << y << ' ' << t << endll;

        fclose(f);
    }
    

}