#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll a, b, res;
int main()
{
    srand(time(0)+817);
    cin >> a >> b;
    while(1)
    {
        if(res==a+b)
            break;
        else if(a + b <= 0 && res > a + b)
            res-=rand()%1000000;
        else if(a + b <= 0 && res < a + b)
            res+=rand()%1000000;
        else if(a + b >= 0 && res > a + b)
            res-=rand()%1000000;
        else if(a + b >= 0 && res < a + b)
            res+=rand()%1000000;
    }
    cout << res << endl;
    return 0;
}
