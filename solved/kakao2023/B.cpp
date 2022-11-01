#include <string>
#include <vector>
#include <iostream>
using namespace std;

long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long answer = 0;
    long long picksum = 0;
    long long deliveriesum = 0;
    while(1)
    {
        while(!deliveries.empty() && deliveries.back() == 0)
            deliveries.pop_back();
        while(!pickups.empty() && pickups.back() == 0)
            pickups.pop_back();
        if(deliveries.empty() && pickups.empty())
            break;
        int here = cap;
        answer += max(deliveries.size(), pickups.size()) * 2;
        while(!deliveries.empty() && here > 0)
        {
            if(here - deliveries.back() >= 0)
                {
                    here -= deliveries.back();
                    deliveries.pop_back();
                }
            else
            {
                deliveries.back() -= here;
                here = 0;
            }
        }
        here = cap;
        while(!pickups.empty() && here > 0)
        {
            if(here - pickups.back() >= 0)
                {
                    here -= pickups.back();
                    pickups.pop_back();
                }
            else
            {
                pickups.back() -= here;
                here = 0;
            }
        }
        //cout<<answer<<endl;
    }
    return answer;
}