//      This program takes any tic-tac-toe type of table and prints who would win
//  if the game went on optimally in each case. For each test case, it returns invalid
//  if the initial board is not achievable throw fair game (only by someone
//  skipping their turn), draw if it would end in a draw, win if the first player wins
//  and lose if the first player loses the game.

#include<cstdio>

using namespace std;

int backtrackingarray[15];
int ans[20000];

//1 = invalid
//2 = draw
//3 = win
//4 = lose

int nr[5], pow3[]={19783,6561,2187,729,243,81,27,9,3,1};

void back1(int k)
{
  int i;
  if(k == 10)
  {
    int nrx = 0, nro = 0, x = 0;
    for(i = 1; i <= 9; ++ i)
    {
      if(backtrackingarray[i] == 1)
        ++ nrx;
      if(backtrackingarray[i] == 2)
        ++ nro;
      x = x * 3 + backtrackingarray[i];
    }
    if(nrx > nro + 1 || nro > nrx)
    {
      ans[x] = 1;
      return ;
    }
    else
    {
      if(backtrackingarray[1] == 1)
      {
        if(backtrackingarray[2] == 1 && backtrackingarray[3] == 1)
        {
          ans[x] = 3;
          return ;
        }
        if(backtrackingarray[5] == 1 && backtrackingarray[9] == 1)
        {
          ans[x] = 3;
          return ;
        }
        if(backtrackingarray[4] == 1 && backtrackingarray[7] == 1)
        {
          ans[x] = 3;
          return ;
        }
      }
      if(backtrackingarray[1] == 2)
      {
        if(backtrackingarray[2] == 2 && backtrackingarray[3] == 2)
        {
          ans[x] = 4;
          return ;
        }
        if(backtrackingarray[5] == 2 && backtrackingarray[9] == 2)
        {
          ans[x] = 4;
          return ;
        }
        if(backtrackingarray[4] == 2 && backtrackingarray[7] == 2)
        {
          ans[x] = 4;
          return ;
        }
      }
      if(backtrackingarray[2] == 1)
      {
        if(backtrackingarray[5] == 1 && backtrackingarray[8] == 1)
        {
          ans[x] = 3;
          return ;
        }
      }
      if(backtrackingarray[2] == 2)
      {
        if(backtrackingarray[5] == 2 && backtrackingarray[8] == 2)
        {
          ans[x] = 4;
          return ;
        }
      }
      if(backtrackingarray[3] == 1)
      {
        if(backtrackingarray[5] == 1 && backtrackingarray[7] == 1)
        {
          ans[x] = 3;
          return ;
        }
        if(backtrackingarray[6] == 1 && backtrackingarray[9] == 1)
        {
          ans[x] = 3;
          return ;
        }
      }
      if(backtrackingarray[3] == 2)
      {
        if(backtrackingarray[5] == 2 && backtrackingarray[7] == 2)
        {
          ans[x] = 4;
          return ;
        }
        if(backtrackingarray[6] == 2 && backtrackingarray[9] == 2)
        {
          ans[x] = 4;
          return ;
        }
      }
      if(backtrackingarray[4] == 1 && backtrackingarray[5] == 1 && backtrackingarray[6] == 1)
      {
        ans[x] = 3;
        return ;
      }
      if(backtrackingarray[4] == 2 && backtrackingarray[5] == 2 && backtrackingarray[6] == 2)
      {
        ans[x] = 4;
        return ;
      }
      if(backtrackingarray[7] == 1 && backtrackingarray[8] == 1 && backtrackingarray[9] == 1)
      {
        ans[x] = 3;
        return ;
      }
      if(backtrackingarray[7] == 2 && backtrackingarray[8] == 2 && backtrackingarray[9] == 2)
      {
        ans[x] = 4;
        return ;
      }
      if(ans[x] == 0)
      {
        if(nrx + nro == 9)
        {
          ans[x] = 2;
          return ;
        }
        else
        {
          nr[3] = 0;
          nr[4] = 0;
          nr[2] = 0;
          if(nrx > nro)
          {
            for(i = 1; i <= 9; ++ i)
              if(backtrackingarray[i] == 0)
                ++ nr[ans[x + pow3[i] + pow3[i]]];
            if(nr[4] > 0)
            {
              ans[x] = 4;
              return ;
            }
            if(nr[2] + nr[4] == 0 && nr[3] > 0)
            {
              ans[x] = 3;
              return ;
            }
            if(ans[x] == 0)
            {
              ans[x] = 2;
              return ;
            }
          }
          else
          {
            for(i = 1; i <= 9; ++ i)
              if(backtrackingarray[i] == 0)
                ++ nr[ans[x + pow3[i]]];
            if(nr[3] > 0)
            {
              ans[x] = 3;
              return ;
            }
            if(nr[3] == 0 && nr[2] == 0 && nr[4] > 0)
            {
              ans[x] = 4;
              return ;
            }
            if(ans[x] == 0)
            {
              ans[x] = 2;
              return ;
            }
          }
        }
      }
    }
  }
  else
  {
    backtrackingarray[k] = 1;
    back1(k + 1);
    backtrackingarray[k] = 2;
    back1(k + 1);
    backtrackingarray[k] = 0;
    back1(k + 1);
  }
}

int main()
{
  freopen("xsizero.in", "r", stdin);
  freopen("xsizero.out", "w", stdout);
  back1(1);
  char initial_matrix[9];
  int given_config, i, test_number = 0;
  while(scanf("%c", &initial_matrix[0]) != EOF)
  {
    scanf("%c%c\n%c%c%c\n%c%c%c\n", &initial_matrix[1], &initial_matrix[2], &initial_matrix[3], &initial_matrix[4], &initial_matrix[5], &initial_matrix[6], &initial_matrix[7], &initial_matrix[8]);
    ++ test_number;
    given_config = 0;
    for(i = 0; i < 9; ++ i)
    {
      if(initial_matrix[i] == '.')
        given_config *= 3;
      if(initial_matrix[i] == 'X')
        given_config = given_config * 3 + 1;
      if(initial_matrix[i] == '0')
        given_config = given_config * 3 + 2;
    }
    printf("Test number #%d: ", test_number);
    if(ans[given_config] == 1)
      printf("invalid\n");
    if(ans[given_config] == 2)
      printf("draw\n");
    if(ans[given_config] == 3)
      printf("win\n");
    if(ans[given_config] == 4)
      printf("lose\n");
  }
  return 0;
}
