//      Problem statement: http://codeforces.com/gym/100513/problem/D

//      Short version: There are n servers, each with a capacity and a power
//  consumption (1 for low voltage and 0 for high voltage).you need to find
//  the minimum number of servers from n given ones that add up to at least
//  m "petabytes" of memory. If there is more than one way, then we shall
//  choose a configuration that will also have a maximum number of low
//  voltage servers. We are given n, m and the n servers and we shall come
//  up with the minimum number of servers used for the m "petabytes", the
//  number of low voltage servers included in those and the server indexes.


#include<cstdio>
#include<algorithm>

using namespace std;

struct str
{
    int ind;
    long long v;
};

str lowvoltage[200005], highvoltage[200005];
long long final_solution_servers[200005];

bool cmp(str a, str b)
{
    if(a.v < b.v)
        return 1;
    else
        return 0;
}

int main()
{

    int n, dimlowvoltage = 0, dimhighvoltage = 0, startlowvoltage, starthighvoltage, i, tip, minimum_number_of_servers = 0, nrc = 0, nrservinsol = 0;
    long long m, sum = 0;
    scanf("%d %I64d", &n, &m);
    for(i = 1; i <= n; ++ i)
    {
        scanf("%I64d %d", &final_solution_servers[i], &tip);
        if(tip == 1)
        {
            ++ dimlowvoltage;
            lowvoltage[dimlowvoltage].ind = i;
            lowvoltage[dimlowvoltage].v = final_solution_servers[i];
        }
        else
        {
            ++ dimhighvoltage;
            highvoltage[dimhighvoltage].ind = i;
            highvoltage[dimhighvoltage].v = final_solution_servers[i];
        }
    }
    sort(final_solution_servers, final_solution_servers + n + 1);
    sort(lowvoltage, lowvoltage + dimlowvoltage + 1, cmp);
    sort(highvoltage, highvoltage + dimhighvoltage + 1, cmp);
    sum = 0;
    for(i = n; i >= 1; -- i)
    {
        sum = sum + final_solution_servers[i];
        if(sum >= m)
            break;
    }
    startlowvoltage = dimlowvoltage + 1;
    starthighvoltage = dimhighvoltage + 1;
    minimum_number_of_servers = n - i + 1;
    sum = 0;
    while(minimum_number_of_servers > nrc && startlowvoltage != 1)
    {
        -- startlowvoltage;
        sum = sum + lowvoltage[startlowvoltage].v;
        ++ nrc;
    }
    while(minimum_number_of_servers > nrc)
    {
        -- starthighvoltage;
        sum = sum + highvoltage[starthighvoltage].v;
        ++ nrc;
    }
    while(sum < m)
    {
        -- starthighvoltage;
        sum = sum + highvoltage[starthighvoltage].v - lowvoltage[startlowvoltage].v;
        ++ startlowvoltage;
    }
    printf("%d %d\n", minimum_number_of_servers, dimlowvoltage - startlowvoltage + 1);
    for(i = startlowvoltage; i <= dimlowvoltage; ++ i)
        final_solution_servers[++ nrservinsol] = lowvoltage[i].ind;
    for(i = starthighvoltage; i <= dimhighvoltage; ++ i)
        final_solution_servers[++ nrservinsol] = highvoltage[i].ind;
    sort(final_solution_servers, final_solution_servers + minimum_number_of_servers + 1);
    for(i = 1; i <= minimum_number_of_servers; ++ i)
        printf("%I64d ", final_solution_servers[i]);
    printf("\n");
    return 0;
}
