#include <algorithm>
#include <cmath>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <vector>

template <typename VType = size_t, typename EType = std::pair<VType, VType>>
class Graph {
 protected:
  size_t vcount_;
  size_t ecount_;
  std::vector<VType> vertices_;
  virtual ~Graph() = default;
  Graph(const std::vector<VType>& verts, const size_t& edges)
      : vcount_(verts.size()), ecount_(edges), vertices_(verts) {}

 public:
  using VertexType = VType;
  using EdgeType = EType;
  size_t VerticesCount() { return vcount_; }
  size_t EdgeCount() { return ecount_; }
  virtual std::vector<VType> Getvertices() = 0;
  virtual std::vector<VType> GetNeighbours(VType vert) = 0;
  virtual typename std::vector<VType>::iterator NeighboursBegin(
      VType vert) = 0;
  virtual typename std::vector<VType>::iterator NeighboursEnd(VType vert) = 0;
};

template <typename VType = size_t, typename EType = std::pair<VType, VType>>
class ListGraph : public Graph<VType, EType> {
 protected:
  std::unordered_map<VType, std::vector<VType>> adjlist_;

 public:
  ListGraph(const std::vector<VType>& verts, const std::vector<EType>& edges)
      : Graph<VType, EType>(verts, edges.size()) {
    for (auto& vertex : verts) {
      adjlist_[vertex] = std::vector<VType>();
    }
    for (auto& edge : edges) {
      adjlist_[edge.first].push_back(edge.second);
    }
  }
  std::vector<VType> Getvertices() override {
    return Graph<VType, EType>::vertices_;
  }
  std::vector<VType> GetNeighbours(VType vert) override {
    return adjlist_[vert];
  }
  typename std::vector<VType>::iterator NeighboursBegin(VType vert) override {
    return adjlist_[vert].begin();
  }
  typename std::vector<VType>::iterator NeighboursEnd(VType vert) override {
    return adjlist_[vert].end();
  }
};

template <typename VType = size_t, typename EType = std::pair<VType, VType>>
class MatrixGraph : public Graph<VType, EType> {
 protected:
  std::unordered_map<VType, std::unordered_map<VType, std::pair<bool, EType>>>
      matrix_;

 public:
  MatrixGraph(const std::vector<VType>& verts, const std::vector<EType>& edges)
      : Graph<VType, EType>(verts, edges.size()) {
    for (auto& vertex : verts) {
      matrix_[vertex] = std::unordered_map<VType, EType>();
    }
    for (auto& edge : edges) {
      matrix_[edge.first][edge.second].first = true;
      matrix_[edge.first][edge.second].second = edge;
    }
  }
  std::vector<VType> Getvertices() override {
    return Graph<VType, EType>::vertices_;
  }
  std::vector<VType> GetNeighbours(VType vert) override {
    std::vector<VType> answer;
    for (auto& vertex : Graph<VType, EType>::vertecies) {
      if (matrix_[vert].contains(vertex)) {
        answer.push_back(vertex);
      }
    }
    return answer;
  }
  typename std::vector<VType>::Iterator NeighboursBegin(VType vert) override {
    return GetNeighbours(vert).begin();
  }
  typename std::vector<VType>::Iterator NeighboursEnd(VType vert) override {
    return GetNeighbours(vert).end();
  }
};

template <typename VType = size_t, typename EType = std::pair<VType, VType>>
class UnorientedListGraph : public ListGraph<VType, EType> {
 public:
  UnorientedListGraph(const std::vector<VType>& verts,
                      const std::vector<EType>& edges)
      : ListGraph<VType, EType>(verts, edges) {
    for (auto& edge : edges) {
      ListGraph<VType, EType>::adjlist_[edge.second].push_back(edge.first);
    }
  }
};
template <typename VType = size_t, typename EType = std::pair<VType, VType>>
class UnorientedMatrixGraph : public MatrixGraph<VType, EType> {
 public:
  UnorientedMatrixGraph(const std::vector<VType>& verts,
                        const std::vector<EType>& edges)
      : MatrixGraph<VType, EType>(verts, edges) {
    for (auto& edge : edges) {
      MatrixGraph<VType, EType>::matrix_[edge.second][edge.first].first = true;
      MatrixGraph<VType, EType>::matrix_[edge.second][edge.first].second = edge;
    }
  }
};

template <typename VType = size_t, typename EType = std::pair<VType, VType>>
class Visitor { 
 private:
  std::unordered_map<VType, VType> ancestor_;

 public:
  void Add(const EType& edge) { ancestor_[edge.second] = edge.first; }
  VType GetAncestor(VType child) { return ancestor_[child]; }
};

template <typename VType = size_t, typename EType = std::pair<VType, VType>>
std::vector<VType> BFS(ListGraph<VType, EType> graph,
                        Visitor<VType, EType>& visited, VType start,
                        VType finish) {
  std::vector<VType> answer;
  std::vector<bool> used(graph.Getvertices().size() + 1, false);
  if (start == finish) {
    return {start};
  }
  std::queue<VType> queue;
  queue.push(start);
  used[start] = true;
  while ((!queue.empty()) && !used[finish]) {
    VType frnt = queue.front();
    queue.pop();
    for (auto& neighbour : graph.GetNeighbours(frnt)) {
      if (!used[neighbour]) {
        visited.Add({frnt, neighbour});
        used[neighbour] = true;
        queue.push(neighbour);
      }
    }
  }
  if (!used[finish]) {
    return {};
  }
  while (finish != start) {
    answer.push_back(finish);
    finish = visited.GetAncestor(finish);
  }
  answer.push_back(finish);
  return answer;
}

void Input(uint& start, uint& finish, std::vector<uint>& vertices,
           std::vector<std::pair<uint, uint>>& edges) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  uint planets;
  uint paths;
  std::cin >> planets >> paths;
  std::cin >> start >> finish;
  vertices.resize(planets);
  edges.resize(paths);
  for (size_t i = 0; i < planets; ++i) {
    vertices[i] = i + 1;
  }
  for (size_t i = 0; i < paths; ++i) {
    uint tmp1;
    uint tmp2;
    std::cin >> tmp1 >> tmp2;
    edges[i] = {tmp1, tmp2};
  }
}

void Output(const std::vector<uint>& answer) {
  uint answer_size = answer.size();
  std::cout << int(answer_size) - 1 << "\n";
  for (int i = answer_size - 1; i >= 0; --i) {
    std::cout << answer[i] << " ";
  }
}

int main() {
  uint start;
  uint finish;
  std::vector<uint> vertices;
  std::vector<std::pair<uint, uint>> edges;
  Input(start, finish, vertices, edges);
  Visitor<uint, std::pair<uint, uint>> visited;
  UnorientedListGraph<uint, std::pair<uint, uint>> graph(vertices, edges);
  Output(BFS<uint, std::pair<uint, uint>>(graph, visited, start, finish));
}