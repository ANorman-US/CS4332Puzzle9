//Alexander Norman
//CS4332
//9-puzzle problem
//more polished version using IDS
//we want to use IDS or BFS since we want a minimum number of moves. IDS is preferrable since it's easy to set a limit
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

//nodes will contain a vector with the current 3x3, their depth, and another vector recording the previous actions taken to get here
struct Node{
    vector<vector<int>> v;
    int depth;
    vector<string> edgesTaken;
};

bool isGoal(const vector<vector<int>>&);//check if vector is goal
vector<vector<int>> shiftHorizontal(const int&,const vector<vector<int>>&);//returns vector with shift applied
vector<vector<int>> shiftVertical(const int&,const vector<vector<int>>&);//see above

vector<string> IDS(const vector<vector<int>> &);//takes in 2d vector
vector<string> DLS (const vector<vector<int>>&, const int &);//takes in 2d vector and depth

int main()
{
    cout << "Input:\n";
    int firstNum;
    cin >> firstNum;
    while(firstNum != 0)
    {
        vector<vector<int>> vectorPuzzle(3, vector<int> (3));//3x3 vector to read input into
        vectorPuzzle[0][0] = firstNum;
        int num;
        for(int i=1;i<3;i++)//reading in remaining input
        {
            cin >> num;
            vectorPuzzle[0][i] = num;
        }
        for(int i=1;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                cin >> num;
                vectorPuzzle[i][j] = num;
            }
        }

        vector<string> edges = IDS(vectorPuzzle);//perform iterative deepeningsearch
        if(edges.size()==0)
            cout << "Already solved\n";
        else if (edges[0]=="-1")
            cout << "Not solvable\n";
        else
        {
            cout << edges.size() << " ";//print out size of vector, then iterate through and print actions taken
            for(int i=0;i<edges.size();i++)
                cout << edges[i];
            cout << endl;
        }

        cout << "Input:\n";
        cin >> firstNum;
    }

    return 0;
}

vector<string> IDS(const vector<vector<int>> &vectorPuzzle)//calls depth limited search, increases depth with each iteration
{
    vector<string> edges;
    for(int depth=0;depth<8;depth++)//choose arbitrary depth 10 here
    {
        edges = DLS(vectorPuzzle, depth);
        if(edges.size() == 0 || edges[0] != "-1")//if vector size is 0 (already correct) or contains elements but not "-1"
            return edges;
    }
    return edges;//in this case should be a vector with just "-1"
}

vector<string> DLS (const vector<vector<int>> &vectorPuzzle, const int& depth)
{
    stack<Node> frontier;//establish initial node and frontier
    Node nodeStart;
    nodeStart.depth=0;
    nodeStart.v=vectorPuzzle;
    frontier.push(nodeStart);

    while(!frontier.empty())
    {
        Node topNode = frontier.top();
        frontier.pop();
        if(isGoal(topNode.v))
            return topNode.edgesTaken;
        if(topNode.depth>depth)
        {}//if we exceed depth, we do not generate children, instead go to end of function where we return a vector with "-1" pushed.
        //an empty vector signifies the problem didnt need solving. "-1" at [0] signifies not solvable.
        //else if not inLoop(node) maybe add this in later with history tracking
        else//if not at depth and solution not found, we generate children nodes and add to frontier
        {
            //generate horizontal shifts
            for(int i=0;i<3;i++)
            {
                Node newNode = topNode;
                newNode.depth+=1;
                string edge = "H" + to_string(i + 1);//adding h# or v#
                newNode.edgesTaken.push_back(edge);//push back another edge taken
                newNode.v = shiftHorizontal(i, topNode.v);//performs shift
                //note that .v references the Node's 2d vector
                frontier.push(newNode);
            }
            //generate vertical shifts
            for(int i=0;i<3;i++)
            {
                Node newNode = topNode;
                newNode.depth+=1;
                string edge = "V" + to_string(i + 1);//adding h# or v#
                newNode.edgesTaken.push_back(edge);//push back another edge taken
                newNode.v = shiftVertical(i, topNode.v);//performs shift
                //note that .v references the Node's 2d vector
                frontier.push(newNode);
            }
        }
    }
    //return vector with "-1" signifiying not solvable
    vector<string> badVector;
    badVector.push_back("-1");
    return badVector;
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