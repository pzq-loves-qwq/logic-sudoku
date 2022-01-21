#include "board.hpp"

board b;

int main()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            scanf("%d", &b.a[i][j]);
    print_cnf(stdout, enc(b), 9 * 9 * 9);
    return 0;
}
