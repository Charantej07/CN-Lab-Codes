#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Graph
{
public:
    int n;
    vector<vector<int>> adj;
    vector<vector<int>> routing_table;

    Graph(int x) : n(x), adj(n, vector<int>(n)), routing_table(n, vector<int>(n, INT_MAX))
    {
        for (int i = 0; i < n; i++)
        {
            routing_table[i][i] = 0;
        }
    }

    void create()
    {
        cout << "Enter adjacency matrix:\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int x;
                cin >> x;
                adj[i][j] = x;
            }
        }
    }

    void display()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }

    void create_routing_table()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adj[i][j] != 0)
                {
                    routing_table[i][j] = adj[i][j];
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            cout << "\nDistance vector of router " << i << endl;
            for (int j = 0; j < n; j++)
            {
                cout << routing_table[i][j] << " ";
            }
            cout << "\n";
        }

        cout << "\n\n\n";
    }

    void distance_vector()
    {
        while (true)
        {
            int flag = 1;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (adj[i][j] != 0)
                    {
                        for (int k = 0; k < n; k++)
                        {
                            if (routing_table[i][j] == INT_MAX || routing_table[j][k] == INT_MAX)
                            {
                                continue;
                            }
                            if (routing_table[i][k] > routing_table[j][k] + routing_table[j][i])
                            {
                                routing_table[i][k] = routing_table[j][k] + routing_table[j][i];
                                flag = 0;
                            }
                        }
                    }
                }

                cout << "\n\n\n";
                for (int z = 0; z < n; z++)
                {
                    cout << "\nDistance vector of router " << i << endl;
                    for (int d = 0; d < n; d++)
                    {
                        cout << routing_table[z][d] << " ";
                    }
                    cout << "\n";
                }
            }

            if (flag == 1)
            {
                break;
            }
        }

        cout << "\n\n\n";
        for (int i = 0; i < n; i++)
        {
            cout << "\nDistance vector of router " << i << endl;
            for (int j = 0; j < n; j++)
            {
                cout << routing_table[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

int main()
{
    cout << "Enter the number of routers: ";
    int n;
    cin >> n;
    Graph g(n);
    g.create();
    g.display();
    g.create_routing_table();
    g.distance_vector();
    return 0;
}
