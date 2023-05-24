//g++ assignment1.cpp -lstdc++ -o a.out
//./a.out

#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;


class Graph{
    public:
	//---to take inputs from user----
	// vector<vector<int>> graph;
        // vector<bool> visited;
        // int vertices = 0;
        // int edges = 0;
        // Graph(){
        //     cout << "Enter number of nodes: ";
        //     cin >> vertices;
        //     cout << "Enter number of edges: ";
        //     cin >> edges;
        //     graph.assign(vertices,vector<int>());
        //     for(int i = 0 ; i < edges;i++){
        //         int a,b;
        //         cout << "Enter adjacent nodes: ";
        //         cin >> a >> b;
        //         addEdge(a,b);
        //     }
        // }
        //void addEdge(int a, int b){
        //   graph[a].push_back(b);
        //    graph[b].push_back(a);
        //}


        int vertices = 6;
        int edges = 5;
        vector<vector<int>> graph = {{1},{0,2,3},{1,4,5},{1,4},{2,3},{2}};
        vector<bool> visited;

        void printGraph(){
            for(int i = 0; i < vertices; i++){
                cout << i << " -> ";
                for(auto j = graph[i].begin(); j != graph[i].end();j++){
                    cout << *j << " ";
                }
                cout << endl;
            }
        }

        void initialize_visited(){
            visited.assign(vertices,false);
        }

        void dfs(int i){
            stack<int> s;
            s.push(i);
            visited[i] = true;

            while(s.empty() != true){
                int current = s.top();
                cout << current << " ";
                s.pop();
                for(auto j = graph[current].begin(); j != graph[current].end();j++){
                    if(visited[*j] == false){
                        s.push(*j);
                        visited[*j] = true;
                    }
                }
                
            }
        }

        void parallel_dfs(int i){
            stack<int> s;
            s.push(i);
            visited[i] = true;

            while(s.empty() != true){
                int current = s.top();
                cout << current << " ";
                #pragma omp critical
                    s.pop();
                #pragma omp parallel for
                    for(auto j = graph[current].begin(); j != graph[current].end();j++){
                        if(visited[*j] == false){
                            #pragma omp critical
                            {
                                s.push(*j);
                                visited[*j] = true;
                            }
                        }
                    }
                
            }
        }

        void bfs(int i){
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while(q.empty() != true){
                int current = q.front();
                q.pop();
                cout << current << " ";
                for(auto j = graph[current].begin(); j != graph[current].end();j++){
                    if(visited[*j] == false){
                        q.push(*j);
                        visited[*j] = true;
                    }
                }
            }
        }

        void parallel_bfs(int i){
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while(q.empty() != true){
                
                    int current = q.front();
                    cout << current << " ";
                    #pragma omp critical
                        q.pop();
                    
                #pragma omp parallel for
                    for(auto j = graph[current].begin(); j != graph[current].end();j++){
                        if(visited[*j] == false){
                            #pragma omp critical
                                q.push(*j);
                                visited[*j] = true;
                        }
                    }
                
            }
        }
};

int main()
{
    Graph g;
    cout << "Adjacency List:\n";
    g.printGraph();
    g.initialize_visited();

    cout << "Depth First Search: \n";
    double start = omp_get_wtime();	
    g.dfs(0);
    cout << endl;
    double end = omp_get_wtime();
    cout << "Time taken: " << (end-start)<<endl;

    cout << "Parallel Depth First Search: \n";
    g.initialize_visited();
    start = omp_get_wtime();
    g.parallel_dfs(0);
    cout << endl;
    end = omp_get_wtime();
    cout << "Time taken: "<< (end-start) << endl;
    
    cout << "Breadth First Search: \n";
    g.initialize_visited();
    start = omp_get_wtime();
    g.bfs(0);
    end = omp_get_wtime();
    cout << endl;
    cout << "Time taken: "<< (end - start) << endl;
    
    cout << "Parallel Breadth First Search: \n";
    g.initialize_visited();
    start = omp_get_wtime();
    g.parallel_bfs(0);
    end = omp_get_wtime();
    cout << endl;
    cout << "Time taken: " << (end - start) << endl;

    return 0;
}

