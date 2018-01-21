#include <iostream>
#include "city.h"
#include <vector>
#include "action.h"
#include "node.h"
#include "state.h"
#include <queue>
#include <stack>
#include "inicialization.h"
#include <stdlib.h>
#include <ctime>

/*
*   Developed by:
*       - José Robertty de Freitas Costa (graduating computer engineering)
*       - Marianna de Pinho Severo (graduating computer engineering)
*       - Marisa do Carmo Silva (graduating computer engineering)
*/

using namespace std;

#define LINES 20
#define COLUMNS 20


static Node error(State(-1),nullptr,Action(State(-1),State(-1)),-1);

int matriz[LINES][COLUMNS];

void ShowPath(Node no){
    cout << no.getState().getCity() << endl;
    auto NODE = no.father;
    while(NODE != nullptr){
        cout << NODE->getState().getCity() << endl;
        NODE = NODE->father;
    }
}


Node Breadth_First_Search(State state_origin, State state_destination){
    Node *no = (Node*) malloc(sizeof(Node));
    no->setState(state_origin);
    no->setFather(nullptr);
    no->setCost(0);
    if(no->getState() == state_destination)
        return *no;
    queue<Node> edge;
    vector<Node> explored;
    edge.push(*no);
    while(true){
        if(edge.empty())
            return error;
        no = (Node*) malloc(sizeof(Node));
        *no = edge.front();
        edge.pop();
        explored.push_back(*no);
        int line = no->getState().getCity();
        for (int j = 0; j < COLUMNS; j++) {
            if(matriz[line][j] != 0){
                Node new_no(State(j),no,Action(State(line),State(j)),no->getCost() + matriz[line][j]);
                bool flag = true;
                for (int i = 0; i < (int) explored.size(); i++) {
                    if(explored[i].getState().getCity() == j){
                        flag = false;
                        break;
                    }
                }
                if(flag){
                    if(j == state_destination.getCity())
                        return new_no;
                    edge.push(new_no);
                }
            }
        }

    }
    return *no;
}

Node Depth_First_Search(State state_origin, State state_destination){
    Node *no = (Node*) malloc(sizeof(Node));
    no->setState(state_origin);
    no->setFather(nullptr);
    no->setCost(0);
    if(no->getState() == state_destination)
        return *no;
    stack<Node> edge;
    vector<Node> explored;
    edge.push(*no);
    while(true){
        if(edge.empty())
            return error;
        no = (Node*) malloc(sizeof(Node));
        *no = edge.top();
        edge.pop();
        explored.push_back(*no);
        int line = no->getState().getCity();
        for (int j = 0; j < COLUMNS; j++) {
            if(matriz[line][j] != 0){
                Node new_no(State(j),no,Action(State(line),State(j)),no->getCost() + matriz[line][j]);
                bool flag = true;
                for (int i = 0; i < (int) explored.size(); i++) {
                    if(explored[i].getState().getCity() == j){
                        flag = false;
                        break;
                    }
                }
                if(flag){
                    if(j == state_destination.getCity())
                        return new_no;
                    edge.push(new_no);
                }
            }
        }

    }
    return *no;
}

Node Uniform_Cost_Search(State state_origin, State state_destination){
    Node *no = (Node*) malloc(sizeof(Node));
    no->setState(state_origin);
    no->setFather(nullptr);
    no->setCost(0);
    if(no->getState() == state_destination)
        return *no;
    vector<Node> explored;
    priority_queue<Node, vector<Node>, Node::LessThanByAge> edge;
    edge.push(*no);
    while(true){
        if(edge.empty())
            return error;
        no = (Node*) malloc(sizeof(Node));
        *no = edge.top();
        if(no->getState().getCity() == state_destination.getCity())
            return *no;
        edge.pop();
        explored.push_back(*no);
        int line = no->getState().getCity();
        for (int j = 0; j < COLUMNS; j++) {
            if(matriz[line][j] != 0){
                Node new_no(State(j),no,Action(State(line),State(j)),no->getCost() + matriz[line][j]);
                bool flag = true;
                for (int i = 0; i < (int) explored.size(); i++) {
                    if(explored[i].getState().getCity() == j){
                        flag = false;
                        break;
                    }
                }
                if(flag){
                    edge.push(new_no);
                }
            }
        }

    }
    return *no;
}

int main(){

    Inicialization i;
    i.StartMatriz(matriz);
    Node a;
    a = Uniform_Cost_Search(State(i.Arad),State(i.Bucharest));
    ShowPath(a);
    cout << a.getCost() << endl;
    return 0;
}
