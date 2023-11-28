#include <iostream>
#include <queue>
#include <vector>
using namespace std;
void dijkstras(vector<vector<int>> graph, int start, int noOfRouters)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distances(noOfRouters, INT_MAX);
    vector<int> isVisited(noOfRouters, false);
    distances[start] = 0;
    pq.push({0, start});
    pair<int, int> present;
    while (!pq.empty())
    {
        present = pq.top();
        pq.pop();
        if (isVisited[present.second])
        {
            continue;
        }
        isVisited[present.second] = true;
        for (int i = 0; i < noOfRouters; i++)
        {
            if (!isVisited[i] && graph[present.second][i] && distances[present.second] != INT_MAX && distances[present.second] + graph[present.second][i] < distances[i])
            {
                distances[i] = distances[present.second] + graph[present.second][i];
                pq.push({distances[i], i});
            }
        }
    }
    cout << "Distances of the routers from the starting router " << start << endl;
    for (int i = 0; i < noOfRouters; i++)
    {
        cout << i << "->" << distances[i] << endl;
    }
}
int main()
{
    int noOfRouters;
    cout << "Enter the no of Routers: ";
    cin >> noOfRouters;
    cout << "Enter the values: " << endl;
    vector<vector<int>> graph(noOfRouters, vector<int>(noOfRouters, 0));
    for (int i = 0; i < noOfRouters; i++)
    {
        for (int j = 0; j < noOfRouters; j++)
        {
            cin >> graph[i][j];
        }
    }
    int startNode;
    cout << "Enter the starting Router number: ";
    cin >> startNode;
    dijkstras(graph, startNode, noOfRouters);
}