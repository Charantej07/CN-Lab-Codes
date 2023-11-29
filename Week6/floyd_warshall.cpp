#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> floyd_warshall(vector<vector<int>> &adj, int n)
{
    vector<vector<int>> cost(n, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                cost[i][j] = 0;
            }
            else if (adj[i][j] != 0)
            {
                cost[i][j] = adj[i][j];
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (cost[i][k] != INT_MAX && cost[k][j] != INT_MAX)
                    cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
            }
        }
    }

    return cost;
}

int main()
{
    int n, k;
    cout << "Enter the total number of vertices in the graph: \n";
    cin >> n;

    vector<vector<int>> adj;
    cout << "\nEnter the adjacency matrix of the graph" << endl;

    for (int i = 0; i < n; i++)
    {
        adj.push_back(vector<int>());
        for (int j = 0; j < n; j++)
        {
            cin >> k;
            adj[i].push_back(k);
        }
    }

    vector<vector<int>> shortest_distances = floyd_warshall(adj, n);

    cout << "\nShortest distances between all pairs of vertices:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (shortest_distances[i][j] == INT_MAX)
                cout << "INF ";
            else
                cout << shortest_distances[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
