#ifndef __PZQ__BOARD_HPP
#define __PZQ__BOARD_HPP

#include <stdio.h>
#include <string.h>
#include "cnf.hpp"

const int ROWS = 9, COLS = 9, VALS = 9, BOXS = 9;

inline var encode(int r, int c, int v)
{
    return r * COLS * VALS + c * VALS + v + 1;
}

struct board
{
    int a[9][9];
};

inline cnf enc(const board& b)
{
    cnf X;

    for (int r = 0; r < ROWS; r++)
        for (int v = 0; v < VALS; v++)
        {
            clause t;
            for (int c = 0; c < COLS; c++)
                t.push_back(encode(r, c, v));
            exactly_one(X, t);
        }

    for (int c = 0; c < COLS; c++)
        for (int v = 0; v < VALS; v++)
        {
            clause t;
            for (int r = 0; r < ROWS; r++)
                t.push_back(encode(r, c, v));
            exactly_one(X, t);
        }
    
    for (int r = 0; r < 9; r += 3)
        for (int c = 0; c < 9; c += 3)
            for (int v = 0; v < VALS; v++)
            {
                clause t;
                for (int rr = 0; rr < 3; rr++)
                    for (int cc = 0; cc < 3; cc++)
                        t.push_back(encode(r + rr, c + cc, v));
                exactly_one(X, t);
            }

    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
        {
            clause t;
            for (int v = 0; v < VALS; v++)
                t.push_back(encode(r, c, v));
            exactly_one(X, t);
        }

    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            if (b.a[r][c] != 0)
            {
                clause t = {encode(r, c, b.a[r][c])};
                X.push_back(t);
            }

    return X;
}

#endif
