#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>

using namespace std;

// Преобразование матрицы инцидентности в матрицу смежности
vector<vector<int>> incidenceToAdjacency(const vector<vector<int>>& incidenceMatrix) {
    int vertices = incidenceMatrix.size();
    int edges = incidenceMatrix[0].size();

    vector<vector<int>> adjacencyMatrix(vertices, vector<int>(vertices, 0));

    for (int j = 0; j < edges; ++j) {
        int u = -1, v = -1;
        for (int i = 0; i < vertices; ++i) {
            if (incidenceMatrix[i][j] == 1) {
                if (u == -1) {
                    u = i;
                }
                else {
                    v = i;
                    break;
                }
            }
        }
        if (u != -1 && v != -1) {
            adjacencyMatrix[u][v] = 1;
            adjacencyMatrix[v][u] = 1;
        }
    }

    return adjacencyMatrix;
}

// Поиск всех циклов в графе с использованием поиска в глубину (DFS)
void dfs(int v, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& path, unordered_set<int>& pathSet, vector<vector<int>>& cycles) {
    visited[v] = true;
    path.push_back(v);
    pathSet.insert(v);

    for (int neighbor : graph[v]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, path, pathSet, cycles);
        }
        else if (pathSet.find(neighbor) != pathSet.end()) {
            vector<int> cycle;
            auto it = find(path.begin(), path.end(), neighbor);
            for (; it != path.end(); ++it) {
                cycle.push_back(*it);
            }
            cycles.push_back(cycle);
        }
    }

    path.pop_back();
    pathSet.erase(v);
    visited[v] = false;
}

// Нахождение всех циклов в графе
vector<vector<int>> findCycles(const vector<vector<int>>& adjacencyMatrix) {
    vector<vector<int>> cycles;
    vector<vector<int>> graph(adjacencyMatrix.size());

    for (size_t i = 0; i < adjacencyMatrix.size(); i++) {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[i][j] == 1) {
                graph[i].push_back(j);
            }
        }
    }

    vector<bool> visited(graph.size(), false);
    vector<int> path;
    unordered_set<int> pathSet;

    for (size_t i = 0; i < graph.size(); i++) {
        dfs(i, graph, visited, path, pathSet, cycles);
    }

    for (auto& cycle : cycles) {
        if (cycle.size() < 3) {
            cycle.clear();
        }
    }

    cycles.erase(remove_if(cycles.begin(), cycles.end(), [](const vector<int>& v) { return v.empty(); }), cycles.end());
    return cycles;
}

// Удаление дубликатов из списка пар
vector<pair<int, int>> removeDuplicates(vector<pair<int, int>>& pairs) {
    set<pair<int, int>> uniquePairs;
    for (const auto& p : pairs) {
        if (p.first < p.second) {
            uniquePairs.insert(p);
        }
        else {
            uniquePairs.insert({ p.second, p.first });
        }
    }
    return vector<pair<int, int>>(uniquePairs.begin(), uniquePairs.end());
}

// Подсчет количества хорд в графе
int findChords(vector<vector<int>> cycles, vector<vector<int>>& graph) {
    vector<pair<int, int>> result;
    vector<pair<int, int>> chords;
    for (const auto& cycle : cycles) {
        if (cycle.size() > 3) {
            for (size_t j = 0; j < cycle.size(); j++) {
                if (j >= 1 && j < cycle.size() - 1) {
                    for (size_t k = 0; k < j - 1; k++) {
                        if (find(graph[cycle[j]].begin(), graph[cycle[j]].end(), cycle[k]) != graph[cycle[j]].end()) {
                            result.push_back(make_pair(cycle[j], cycle[k]));
                        }
                    }
                    for (size_t k = j + 2; k < cycle.size(); k++) {
                        if (find(graph[cycle[j]].begin(), graph[cycle[j]].end(), cycle[k]) != graph[cycle[j]].end()) {
                            result.push_back(make_pair(cycle[j], cycle[k]));
                        }
                    }
                }
                else if (j == cycle.size() - 1) {
                    for (size_t k = 1; k < j - 1; k++) {
                        if (find(graph[cycle[j]].begin(), graph[cycle[j]].end(), cycle[k]) != graph[cycle[j]].end()) {
                            result.push_back(make_pair(cycle[j], cycle[k]));
                        }
                    }
                }
                else {
                    for (size_t k = j + 2; k < cycle.size() - 1; k++) {
                        if (find(graph[cycle[j]].begin(), graph[cycle[j]].end(), cycle[k]) != graph[cycle[j]].end()) {
                            result.push_back(make_pair(cycle[j], cycle[k]));
                        }
                    }
                }
            }
        }
    }
    chords = removeDuplicates(result);
    return chords.size();
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<vector<int>> incidenceMatrix =
    { { 1, 1, 0, 0, 0},
      { 1, 0, 1, 1, 0},
      { 0, 0, 0, 1, 1},
      { 0, 1, 1, 0, 1} };



    vector<vector<int>> adjacencyMatrix = incidenceToAdjacency(incidenceMatrix);
    vector<vector<int>> cycles = findCycles(adjacencyMatrix);

    cout << "Найденные циклы:" << endl;
    for (const auto& cycle : cycles) {
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;
    }

    int chordCount = findChords(cycles, adjacencyMatrix);
    cout << "Количество хорд в графе: " << chordCount << endl;

    return 0;
}
