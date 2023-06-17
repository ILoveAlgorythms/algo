#include <vector>
#include <iostream>
#include <unordered_map>
#include <numeric> 
#include <functional> 
#include <algorithm>
template <class T>
using FilterFunction = std::function<bool(const T&)>;

template <class VType = size_t, class EType = std::pair<VType, VType>>
class IteratorImpl {
  public:
    using iterator = IteratorImpl;
     
    IteratorImpl(
      VType v,
      typename std::vector<VType>::iterator begin, 
      typename std::vector<VType>::iterator end, 
      const FilterFunction<EType> filter
    ) : v_(v), now_(begin), end_(end), filter_(filter) {
      if (now_ != end_) {
        now_edge_ = {v_, *now_};
        if (!filter_(now_edge_)) { ++*this; }
      }
    }
    
    IteratorImpl& operator++() {
      do {
        ++now_;
        if (now_ == end_) {
          return *this;
        }
        now_edge_ = {v_, *now_};
      } while (!filter_(now_edge_) && now_ != end_);
      // }
      return *this;
    }
    
    bool operator==(const IteratorImpl& other) const {
      return now_ == other.now_;
    }

    bool operator!=(const IteratorImpl& other) const {
      return now_ != other.now_;
    }

    IteratorImpl begin() const {
      return *this;
    }

    IteratorImpl end() const {
      return {v_, end_, end_, filter_};
    }

    const EType& operator*() {
      return now_edge_;
    }

  private:
    EType now_edge_;
    VType v_;
    typename std::vector<VType>::iterator now_;
    typename std::vector<VType>::iterator end_;
    const FilterFunction<EType> filter_;
};

template <class VType = size_t, class EType = std::pair<VType, VType>>
class Graph {
public:
  using VertexType = VType;
  using EdgeType = EType;

  virtual size_t EdgeCount() = 0;
  virtual size_t VertexCount() = 0;
  virtual std::vector<VType> Vertexes() = 0;

  virtual typename std::vector<VType>::iterator NeighboursBegin(VType v) = 0;
  virtual typename std::vector<VType>::iterator NeighboursEnd(VType v) = 0;
  virtual IteratorImpl<VType, EType>  NeighboursIt(
    VType v, 
    const FilterFunction<EType>& filter) = 0;

  virtual ~Graph() = default;
  
};

//      PAIN           !      :)
// HAHAHAHAHAHAHAHAHAHAHAAHAHAHA
// UAHAHAHAHAHAHAHAHAHHAHHAHAHAH
// I  WANT TO LIVE             !
template <typename VType = size_t, typename EType = std::pair<VType, VType>>
class MatrixGraph : public Graph<VType, EType> {
 public:
  MatrixGraph(const std::vector<VType>& vertexes, const std::vector<EType>& edges)
      : Graph<VType, EType>(vertexes, edges.size()) {
    for (auto& vertex : vertexes) {
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
  // std::vector<VType> GetNeighbours(VType vert) override {
  //   std::vector<VType> answer;
  //   for (auto& vertex : Graph<VType, EType>::vertecies) {
  //     if (matrix_[vert].contains(vertex)) {
  //       answer.push_back(vertex);
  //     }
  //   }
  //   return answer;
  // // }
  // typename std::vector<VType>::Iterator NeighboursBegin(VType vert) override {
  //   return GetNeighbours(vert).begin();
  // }
  // typename std::vector<VType>::Iterator NeighboursEnd(VType vert) override {
  //   return GetNeighbours(vert).end();
  // }

  // IteratorImpl<VType, EType> NeighboursIt (
  //   VType v, 
  //   const FilterFunction<EType>& filter) {
  //     std::vector<VType> ans;
  //     for (auto& vertex : Graph<VType, EType>::vertex) {
  //       if (matrix_[v].contains(vertex)) {
  //         ans.push_back(vertex);
  //       }
  //     }
  //     return ans;
  //   }

 protected:
  std::unordered_map<VType, std::unordered_map<VType, std::pair<bool, EType>>>
      matrix_;

};


template <class VType = size_t, class EType = std::pair<VType, VType>>
class MatrixGraphNoOrient : public MatrixGraph<VType, EType> {
 public:
  MatrixGraphNoOrient(const std::vector<VType>& verts,
                        const std::vector<EType>& edges)
      : MatrixGraph<VType, EType>(verts, edges) {
    for (auto& edge : edges) {
      MatrixGraph<VType, EType>::matrix_[edge.second][edge.first].first = true;
      MatrixGraph<VType, EType>::matrix_[edge.second][edge.first].second = edge;
    }
  }
};


template <class VType = size_t, class EType = std::pair<VType, VType>>
class ListGraph : public Graph<VType, EType> {
  public:
    ListGraph(
      const std::vector<VType>& vertexes, 
      const std::vector<EType>& edges
    ) : vertexes_(vertexes), num_vertex_(vertexes.size()), num_edges_(edges.size()) {
      for (auto& vertex : vertexes) {
        adjacency_lists_[vertex] = std::vector<VType>();
      }
      for (auto& edge : edges) {
        adjacency_lists_[edge.first].push_back(edge.second);
      }
    }

    size_t EdgeCount() override {
      return num_edges_;
    }

    size_t VertexCount() override {
      return num_edges_;
    }

    typename std::vector<VType>::iterator NeighboursBegin(VType v) override {
      return adjacency_lists_[v].begin();
    }

    typename std::vector<VType>::iterator NeighboursEnd(VType v) override {
      return adjacency_lists_[v].end();
    }

    std::vector<VType> Vertexes() override {
      return vertexes_;
    }
    
    IteratorImpl<VType, EType> NeighboursIt(
      VType v, 
      const FilterFunction<EType>& filter
    ) override {
      return {v, NeighboursBegin(v), NeighboursEnd(v), filter};
    }

  protected:
    std::unordered_map<VType, std::vector<VType> > adjacency_lists_;
    std::vector<VType> vertexes_;
    size_t num_vertex_;
    size_t num_edges_;
};

template <class VType = size_t, class EType = std::pair<VType, VType>> 
class ListGraphNoOrient : public ListGraph<VType, EType> {
  public:
    using ListGraph<VType, EType>::adjacency_lists_;
    ListGraphNoOrient(
      const std::vector<VType>& vertexes, 
      const std::vector<EType>& edges
    ) : ListGraph<VType, EType>(vertexes, edges) {
      for (auto& edge : edges) {
        adjacency_lists_[edge.second].push_back(edge.first);
      }
    }
};

enum Colors {
  white, 
  grey, 
  black
};

template <typename Graph>
void DFS(
  typename Graph::VertexType from, 
  Graph& graph, 
  std::unordered_map<typename Graph::VertexType, char>& colors
) {
  using VType = typename Graph::VertexType;
  using EType = typename Graph::EdgeType;
  colors[from] = grey;
  for (auto edge : graph.NeighboursIt(from, [&colors](const EType& edge) {
    return colors[edge.second] == white;
  })) {
    DFS(edge.second, graph, colors);
  }
  colors[from] = black;
}

template <typename Graph>
size_t CountOfComponents(Graph& graph) {
  using VType = typename Graph::VertexType;
  using Color = char;
  std::unordered_map<VType, Color> colors;
  auto vertexes = graph.Vertexes();
  std::for_each(vertexes.begin(), vertexes.end(), 
          [&](const VType& v) { colors[v] = white; });
  return std::accumulate(vertexes.begin(), vertexes.end(), 0ull, 
         [&colors, &graph](size_t cnt, VType v) {
         return (colors[v] == white ? (DFS(v, graph, colors), 1) : 0) + cnt;
    });
}


template <class Vertex, class Edge>
class BfsVisitor {
 public:
  virtual void Visit(const Edge& e) = 0;
  virtual ~BfsVisitor() = default;
};

template <class VType = size_t,class EType = std::pair<VType, VType>>
class BfsAncestorVisitor :  BfsVisitor<VType, EType> {
 public:
  void Visit(const EType& edge) override { list_[edge.second] = edge.first; }
  std::unordered_map<VType, VType> GetMap() const { return list_; }
  VType GetAncestor(const VType& vert) { return list_[vert]; }
 private:
  std::unordered_map<VType, VType> list_;
};

std::istream& operator>>(std::istream& is, std::vector<std::pair<int, int>>& adjajencylist) {
  for (int i = 0; i < adjajencylist.size(); ++i) {
    int x;
    int y;
    is >> x >> y;
    --x;
    --y;
    adjajencylist[i] = {x, y};
  }
  return is;
}


int main() {
  int n;
  int m;
  std::cin >> n >> m;
  int start;
  int finish;
  std::cin >> start >> finish;
  --start;
  --finish;
  std::vector<std::pair<int, int>> adjajencylist(m);
  std::cin >> adjajencylist;
  if (start == finish) {
    std::cout << "0\n" << start;
    return 0;
  }
  ListGraph
  if (g.FindBestWay(start, finish)) {
    std::cout << -1;
  }
  return 0;
}
