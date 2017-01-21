//      This program uses a treap to find the find standings of a ski contest where contenders know
//  their intermediary standing - the i-th perso knows where he was placed among the first i contestants,
//  for all i from 1 to n (where n and the intermediary spots in the standings are given in the schi.in file)
//  The final standing is printed in the schi.out file

#include<cstdio>
#include<ctime>
#include<cstdlib>

using namespace std;

struct treap
{
    short key, nr, priority;
    treap *son1, *son2;
    treap()
    {
        key = 0;
        priority = 0;
        nr = 0;
    }
    treap(short newkey, short newprio, treap *leftson, treap *rightson)
    {
        key = newkey;
        priority = newprio;
        son1 = leftson;
        son2 = rightson;
        nr = 1;
    }
};

treap *maintreap, *nil;
int n;

void recalc(treap* &r)
{
    if(r != nil)
        r->nr = 1 + r->son1->nr + r->son2->nr;
}

void Rightrotation(treap* &optreap)
{
    treap *temp = optreap->son2;
    optreap->son2 = temp->son1;
    temp->son1 = optreap;
    optreap = temp;
}

void Leftrotation(treap* &optreap)
{
    treap *temp = optreap->son1;
    optreap->son1 = temp->son2;
    temp->son2 = optreap;
    optreap = temp;
}

void balance(treap* &optreap)
{
    if(optreap->son2->priority > optreap->priority)
        Rightrotation(optreap);
    if(optreap->son1->priority > optreap->priority)
        Leftrotation(optreap);
    recalc(optreap->son1);
    recalc(optreap->son2);
    recalc(optreap);
}

void update(treap* &optreap, short newkey, short newval, short newpriority)
{
    if(optreap == nil)
    {
        optreap = new treap(newkey, newpriority, nil, nil);
        return;
    }
    if(optreap->son1->nr < newval)
        update(optreap->son2, newkey, newval - (optreap->son1->nr) - 1, newpriority);
    else
        update(optreap->son1, newkey, newval, newpriority);
    balance(optreap);
}

void print(treap* &optreap)
{
    if(optreap == nil)
        return;
    print(optreap->son1);
    printf("%d\n", optreap->key);
    print(optreap->son2);
}

int main()
{
    freopen("schi.in", "r", stdin);
    freopen("schi.out", "w", stdout);
    int i, x;
    scanf("%d", &n);
    srand(777);
    nil = new treap;
    maintreap = new treap;
    nil->son1 = nil->son2 = nil;
    scanf("%d", &x);
    maintreap->son1 = nil;
    maintreap->son2 = nil;
    maintreap->nr = 1;
    maintreap->key = 1;
    maintreap->priority = rand() % 31666 + 1;
    for(i = 2; i <= n; ++ i)
    {
        scanf("%d", &x);
        update(maintreap, i, x - 1, rand() % 31666 + 1);
    }
    print(maintreap);
    return 0;
}

