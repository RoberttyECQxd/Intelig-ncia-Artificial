#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

/*
*   Developed by:
*       - José Robertty de Freitas Costa (graduating computer engineering)
*       - Marianna de Pinho Severo (graduating computer engineering)
*       - Marisa do Carmo Silva (graduating computer engineering)
*/

int main(){

    string problem;

    int N;
    cin >> problem;
    cin >> N;

    if(problem != "nrainhas")
        return 0;

    FILE *txt;
    string route = "/home/robertty/Documentos/InstanciaSAT_"+ std::to_string(N) +".txt";
    txt = fopen(route.c_str(), "a+");

    list<list<int>> solution;
    list<int> solutionPartial;

    for(int i = 0; i < N * N; i += N){
        for(int j = i; j < i + N; j++){
            solutionPartial.push_back(j + 1);
        }
        solution.push_back(solutionPartial);
        solutionPartial.erase(solutionPartial.begin(), solutionPartial.end());
    }


    for(int i = 0; i < N ; i++){
        for(int j = i; j < N * N; j += N){
            solutionPartial.push_back(j + 1);
        }
        solution.push_back(solutionPartial);
        solutionPartial.erase(solutionPartial.begin(), solutionPartial.end());
    }


    for (int i = 0; i < N * N; i++) {
        int line = (i / N) * N;
        int column = i % N;
        int mainDiagonal = i - (N + 1) * (i - line);
        int secondaryDiagonal = i - (N - 1) * (N - i % N - 1);

        for (int j = 0; j < N; j++) {
            if(line + j != i){
                solutionPartial.push_back(-1 * (i + 1));
                solutionPartial.push_back(-1 * (line + j + 1));
                solution.push_back(solutionPartial);
                solutionPartial.erase(solutionPartial.begin(), solutionPartial.end());
            }
        }


        for (int j = 0; j < N; j++) {
            if(column + j * N != i){
                solutionPartial.push_back(-1 * (i + 1));
                solutionPartial.push_back(-1 * (column + j * N + 1));
                solution.push_back(solutionPartial);
                solutionPartial.erase(solutionPartial.begin(), solutionPartial.end());
            }
        }

        for (int j = 0; j < N; j++) {
            if(mainDiagonal + j * (N + 1) >= N * N || mainDiagonal + j * (N + 1) < 0)
                continue;
            if(mainDiagonal + j * (N + 1) != i){
                solutionPartial.push_back(-1 * (i + 1));
                solutionPartial.push_back(-1 * (mainDiagonal + j * (N + 1) + 1));
                solution.push_back(solutionPartial);
                solutionPartial.erase(solutionPartial.begin(), solutionPartial.end());
            }
        }

        for (int j = 0; j < N; j++) {
            if(secondaryDiagonal + j * (N - 1) >= N * N || secondaryDiagonal + j * (N - 1) < 0)
                continue;
            if(secondaryDiagonal + j * (N - 1) != i){
                solutionPartial.push_back(-1 * (i + 1));
                solutionPartial.push_back(-1 * (secondaryDiagonal + j * (N - 1) + 1));
                solution.push_back(solutionPartial);
                solutionPartial.erase(solutionPartial.begin(), solutionPartial.end());
            }
        }
    }

    fprintf(txt, "p cnf %d %d \n", N * N, solution.size());

    while(!solution.empty()){
        solutionPartial = solution.front();
        solution.pop_front();
        while(!solutionPartial.empty()){
            fprintf(txt, "%d ", solutionPartial.front());
            solutionPartial.pop_front();
        }
        fprintf(txt, "0\n");
    }

    fclose(txt);
    return 0;
}
