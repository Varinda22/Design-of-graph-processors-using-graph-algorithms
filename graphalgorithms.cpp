/*

Cellular Automata Machines for Graph Theoretic Problems

Implementetion of Celluler Automata to find spanning tree of a given planner graph

*/




#include<bits/stdc++.h>

#include <algorithm>

using namespace std;




/*

This is the given planner graph -

 

      2 # 4 # #

      #   #   #

      #   #   5 # #

      #   #   #   #

      1 # 3 # #   6 # #

          #       #   #

          # # # # #   #

                      #

                  8 # 7 # 9

                  #   #

        # # 12 # 10 # #

        #   #    #

        #   13 # 11

        #        #

        # # #  # #



        The given edges are - 

        (1,2), (1,3), (2, 4), (3,4), (3, 5), (3, 6), (4, 5), (5, 6), (6, 7), (7, 8), (7, 9), (7, 10), (8, 10), (10, 11), (10, 12), (11, 12),

        (11, 13), (12, 13)

        here, as this is a undirected graph, the reverse of (x, y) which is (y, x) is also treated as en edge 



*/    







const int N = 13;//number of edges;

bool g=false;

vector<vector<int>> grid(20, vector<int> (20, -1));

vector<vector<string>> states(20, vector<string> (20));

queue<pair<int, int>> qu;

// we formed a 2-D grid of size 20*20 , and filled it with -1

// here -1 represents a blank cell, 0 will represent a edge cell and positive numbers like 1,2,3,... will represent node cells with the specific

//node number as the given positive value




vector<string> fi{"in", "d1", "d2", "d3", "d4", "et"};

vector<string> si{"in", "d1", "d2", "d3", "d4"};







void printGrid(){

    for(int i=0; i<20; i++){

        for(int j=0; j<20; j++){

            if(states[i][j]=="b"){

              cout<< "   ";

              continue;

            }

            cout<<states[i][j]<<" ";

            if(states[i][j].length()==1)

            cout<<' ';

        }

        cout<<endl;

    }

}




void showGraph(){

   for(int i=0; i<20; i++){

        for(int j=0; j<20; j++){

            if(grid[i][j]==-1){

              cout<< "   ";

              continue;

            }

            else

            if(grid[i][j]>0){

             cout<<grid[i][j]<<' ';

             if(grid[i][j]<10)

             cout<<' ';

            }

            else

            if(grid[i][j]==0){

              if(states[i][j]=="e" || states[i][j]=="et")

              cout<<"#  ";

              else

              cout<< "   ";

            }







        }

        cout<<endl;

    }

}




void addStraightLineEdge(int x1, int y1, int x2, int y2){

//this function will fill edge cells with 0, that falls in a straight line as per our blue-print

      if(x1==x2){

          for(int i=y1; i<=y2; i++){

             if(grid[x1][i]==-1)

             grid[x1][i]=0;

          }

      }

      else

      if(y1==y2){

        for(int i=x1; i<=x2; i++){

             if(grid[i][y1]==-1)

             grid[i][y1]=0;

          }  

      }

}

void Nodes(){

  //we will assign the values of nodes to the specific cells as per our blue-print

    grid[4][0]=1;

    grid[0][0]=2;

    grid[4][2]=3;

    grid[0][2]=4;

    grid[2][4]=5;

    grid[4][6]=6;

    grid[8][8]=7;

    grid[8][6]=8;

    grid[8][10]=9;

    grid[10][6]=10;

    grid[12][6]=11;

    grid[10][4]=12;

    grid[12][4]=13;

}

void Edges(){

    addStraightLineEdge(0, 0, 4, 0);

    addStraightLineEdge(0, 0, 0, 2);

    addStraightLineEdge(4, 0, 4, 2);

    addStraightLineEdge(0, 2, 4, 2);

    addStraightLineEdge(4, 2, 4, 4);

    addStraightLineEdge(2, 4, 4, 4);

    addStraightLineEdge(0, 2, 0, 4);

    addStraightLineEdge(0, 4, 2, 4);

    addStraightLineEdge(4, 2, 6, 2);

    addStraightLineEdge(6, 2, 6, 6);

    addStraightLineEdge(4, 6, 6, 6);

    addStraightLineEdge(2, 4, 2, 6);

    addStraightLineEdge(2, 6, 4, 6);

    addStraightLineEdge(4, 6, 4, 8);

    addStraightLineEdge(4, 8, 8, 8);

    addStraightLineEdge(8, 8, 8, 10);

    addStraightLineEdge(8, 6, 8, 8);

    addStraightLineEdge(8, 6, 10, 6);

    addStraightLineEdge(8, 8, 10, 8);

    addStraightLineEdge(10, 6, 10, 8);

    addStraightLineEdge(10, 6, 12, 6);

    addStraightLineEdge(10, 4, 10, 6);

    addStraightLineEdge(10, 4,12, 4);

    addStraightLineEdge(12, 4, 12, 6);

    addStraightLineEdge(10, 2,10, 4);

    addStraightLineEdge(10, 2,14, 2);

    addStraightLineEdge(14, 2,14, 6);

    addStraightLineEdge(12, 6,14, 6);

}

void TravelEdge(int x, int y){

    while(true){

        if(x<0 || y<0 || states[x][y]=="b")

        break;

        string s1, s2;

            int ok=0;

            if(y>0 && states[x][y-1]!="b")

            s1=states[x][y-1], ok=1;

            if(x>0 && states[x-1][y]!="b"){

                if(ok)

                s2=states[x-1][y];

                else

                s1=states[x-1][y],ok=1;

            }

             if(states[x][y+1]!="b"){

                if(ok)

                s2=states[x][y+1];

                else

                s1=states[x][y+1],ok=1;

            }

            if(states[x+1][y]!="b"){

                if(ok)

                s2=states[x+1][y];

                else

                s1=states[x+1][y],ok=1;

            }




        if(states[x][y]=="e"){

          if(find(fi.begin(), fi.end(), s1)!=fi.end() && find(fi.begin(), fi.end(), s2)!=fi.end()){

          states[x][y]="ec";

            if(y>0 && states[x][y-1]=="et")

             y--;

            else

            if(x>0 && states[x-1][y]=="et"){

             x--;

            }

            else

             if(states[x][y+1]=="et"){

                y++;

            }

            else

            if(states[x+1][y]=="et"){

              x++;

            }

            else

            return;

          }

          else{

          states[x][y]="et";

            if(y>0 && (states[x][y-1]=="e" || states[x][y-1]=="u"))

             y--;

            else

            if(x>0 && (states[x-1][y]=="e" || states[x-1][y]=="u") ){

             x--;

            }

            else

             if(states[x][y+1]=="e" || states[x][y+1]=="u") {

                y++;

            }

            else

            if(states[x+1][y]=="e" || states[x+1][y]=="u"){

              x++;

            }

            else

            return;

          }

        }

        else

        if(states[x][y]=="et"){

           if(s1=="ec" || s2=="ec" ){

            states[x][y]="ec";

            if(y>0 && states[x][y-1]=="et")

             y--;

            else

            if(x>0 && states[x-1][y]=="et"){

             x--;

            }

            else

             if(states[x][y+1]=="et"){

             y++;

            }

            else

            if(states[x+1][y]=="et"){

              x++;

            }

            else

            return;

           }

           else

           return;

        }

        else

        if(states[x][y]=="u"){

            qu.push({x, y});

            if(y>0 && states[x][y-1]=="et")

            states[x][y]="d1";

            else

            if(x>0 && states[x-1][y]=="et"){

             states[x][y]="d2";

            }

            else

             if(states[x][y+1]=="et"){

                 states[x][y]="d3";

            }

            if(states[x+1][y]=="et"){

               states[x][y]="d4";

            }

        }

        else

        if(states[x][y]=="d1" || states[x][y]=="d2" || states[x][y]=="d3" || states[x][y]=="d4" || states[x][y]=="in" || states[x][y]=="ec")

        break;

     }

}




void BFS(int x, int y){

  qu.push({x, y});

  while(!qu.empty()){

    int a=qu.front().first, b=qu.front().second;

    qu.pop();

    TravelEdge(a-1, b);

    TravelEdge(a, b-1);

    TravelEdge(a+1, b); 

    TravelEdge(a, b+1);

    cout<<"Do you want to see the current state of the grid after exploring node no "<< grid[a][b] <<" ? if yes then enter 'y' :";

    char cc;

    cin >> cc;

    cout<<'\n';

    if(cc=='y')

    printGrid();

  }

}

int main(){

//initialise the nodes and edges in the cell

Nodes();

Edges();







//it will keep track of the state of all the cells 







/*

The different symbols to represent the state of the nodes are given below -



in = initial node in the spanning tree or the root node

u = undiscovered node

d1 = discovered node from left cell

d2 = discovered node from upper cell

d3 = discovered node from right cell

d4 = discovered node from lower cell

e = edge (initial)

et = edge (during evolution) belong to spanning tree

ej = edge checking state

ec = edge, does not belong to spanning tree

b = blank cell

*/




// Setting up the initial states




states[0][0]="in";// (0, 0) or node number 2 is initial node in the spanning tree

for(int i=0; i<20; i++){

    for(int j=0; j<20; j++){

       if(i==0 && j==0)

       continue;

       else

       {

           if(grid[i][j]==-1)

           states[i][j]="b";

           else

           if(grid[i][j]==0)

           states[i][j]="e";

           else

           states[i][j]="u";

       }

    }

}







cout<<"The initial planner graph is : \n\n";

showGraph();

cout<<"The initial grid cell states are : \n\n";

printGrid();




 // Now we will update the states of the cells to form the spanning tree 

 // We will use bfs to travarse through different nodes along the egdes of the graph

BFS(0, 0);




cout<<"The final spanning tree is : \n\n";

 showGraph();







 return 0;

}