#ifndef __PZQ__CNF_HPP
#define __PZQ__CNF_HPP

#include <stdio.h>
#include <stdint.h>
#include <vector>

typedef int32_t var;
typedef std::vector<var> clause;
typedef std::vector<clause> cnf;

inline var negate(const var& x)
{
    return -x;
}

inline void exactly_one(cnf& X, const clause& c)
{
    int n = c.size();
    X.push_back(c);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            clause t = {negate(c[i]), negate(c[j])};
            X.push_back(t);
        }
}

inline void print_cnf(FILE *out, const cnf& X, int vars)
{
    fprintf(out, "c CNF generated by logic-sudoku. \n");
    fprintf(out, "c by pzq-loves-qwq\n");
    fprintf(out, "p cnf %d %d\n", vars, X.size());
    for (auto& c : X)
    {
        for (auto& x : c)
            fprintf(out, "%d ", x);
        fprintf(out, "\n");
    }
}

#endif
