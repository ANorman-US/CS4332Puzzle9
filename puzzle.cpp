//Alexander Norman
//CS4332
//9-puzzle problem
//prototype using BFS
#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

struct Node{
    vector<vector<int>> array;
    int depth;
    vector<string> edgesTaken;
};

bool isGoal(const vector<vector<int>>&);
vector<vector<int>> shiftHorizontal(const int&,const vector<vector<int>>&);
vector<vector<int>> shiftVertical(const int&,const vector<vector<int>>&);
vector<string> BFS(const vector<vector<int>>&);


int main()
{
    cout << "Input:\n";
    int firstNum;
    cin >> firstNum;
    while(firstNum != 0)
    {
        vector<vector<int>> arrayPuzzle(3, vector<int>(3));//read input into 2d vector
        int num;
        arrayPuzzle[0][0]=firstNum;
        for(int i=1;i<3;i++)
        {
            cin >> num;
            arrayPuzzle[0][i] = num;
        }
        for(int i=1;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                cin >> num;
                arrayPuzzle[i][j] = num;
            }
        }
        //perform work on 2d array here
        //when we perform search, we want to return actions performed to reach goal state
        vector<string> edges = BFS(arrayPuzzle);
        if(edges.size()==0)
            cout << "Already solved\n";
        else if (edges[0]=="-1")
            cout << "Not solvable\n";
        else
        {
            cout << edges.size() << " ";
            for(int i=0;i<edges.size();i++)
                cout << edges[i];
            cout << endl;
        }


        cout << "Input:\n";
        cin >> firstNum;
    }

    return 0;
}

vector<string> BFS(const vector<vector<int>>& array)
{
    vector<string> returnVector;//if already solved just return the array
    if(isGoal(array))
        return returnVector;//we detect in main by checking size == 0

    queue<Node> frontier;//frontier
    Node nodeStart;
    nodeStart.array=array;
    nodeStart.depth = 0;

    frontier.push(nodeStart);

    while(!frontier.empty())
    {
        Node currentNode = frontier.front();
        frontier.pop();


        //arbitrary depth limit
        if(currentNode.depth>10)
        {
            returnVector.push_back("-1");
            return returnVector;//if we reach our arbitrary depth we return a vector with just "-1"
        }

        //horizontal shifts
        for(int i=0;i<3;i++)
        {
            Node newNode;
            newNode.depth=currentNode.depth+1;//setting depth
            string edge = "H" + to_string(i + 1);//adding h# or v#
            newNode.edgesTaken=currentNode.edgesTaken;
            newNode.edgesTaken.push_back(edge);//adding h# or v# to vector of edges taken to reach newNode
            newNode.array = shiftHorizontal(i, currentNode.array);//new vector reflects shift
            if(isGoal(newNode.array))//if newNode is goal, we return a vector of the edges taken to newNode
                return newNode.edgesTaken;
            frontier.push(newNode);//otherwise we just add to the stack
        }
        //vertical shifts
        //same notes as above but vertical shift
        for(int i=0;i<3;i++)
        {
            Node newNode;
            newNode.depth=currentNode.depth+1;
            string edge = "V" + to_string(i + 1);
            newNode.edgesTaken=currentNode.edgesTaken;
            newNode.edgesTaken.push_back(edge);
            newNode.array = shiftVertical(i, currentNode.array);
            if(isGoal(newNode.array))
                return newNode.edgesTaken;
            frontier.push(newNode);
        }
    }
    exit(1);
}

vector<vector<int>> shiftHorizontal(const int & row, const vector<vector<int>> &v)
{
    vector<vector<int>> array = v;
    int a = array[row][0];
    array[row][0] = array[row][2];
    array[row][2] = array[row][1];
    array[row][1] = a;
    return array;
}

vector<vector<int>> shiftVertical(const int& col, const vector<vector<int>> &v)
{
    vector<vector<int>> array = v;
    int a = array[0][col];
    array[0][col] = array[1][col];
    array[1][col] = array[2][col];
    array[2][col] = a;
    return array;
}

bool isGoal(const vector<vector<int>>& array)
{
    int num = 1;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(array[i][j] != num)
                return false;
            num++;
        }
    }
    return true;
}