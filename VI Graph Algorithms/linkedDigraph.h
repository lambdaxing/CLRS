// linked adjacency list representation of a digraph

#ifndef linkedDigraph_
#define linkedDigraph_

#include <iostream>
#include <sstream>

#include "graph.h"
#include "graphChain.h"
#include "myExceptions.h"
#include "unweightedEdge.h"
#include "vertexIterator.h"

class linkedDigraph : public graph<bool> {
 protected:
  int n;                   // number of vertices
  int e;                   // number of edges
  graphChain<int>* aList;  // adjacency lists

 public:
  linkedDigraph(int numberOfVertices = 0) {  // Constructor.
    if (numberOfVertices < 0)
      throw illegalParameterValue("number of vertices must be >= 0");
    n = numberOfVertices;
    e = 0;
    aList = new graphChain<int>[n + 1];
  }

  ~linkedDigraph() { delete[] aList; }

  int numberOfVertices() const { return n; }

  int numberOfEdges() const { return e; }

  bool directed() const { return true; }

  bool weighted() const { return false; }

  bool existsEdge(int i, int j) const {  // Return true iff (i,j) is an edge.
    if (i < 1 || j < 1 || i > n || j > n || aList[i].indexOf(j) == -1)
      return false;
    else
      return true;
  }

  void insertEdge(edge<bool>* theEdge) {  // Insert an edge.
    int v1 = theEdge->vertex1();
    int v2 = theEdge->vertex2();
    if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2) {
      std::ostringstream s;
      s << "(" << v1 << "," << v2 << ") is not a permissible edge";
      throw illegalParameterValue(s.str());
    }

    if (aList[v1].indexOf(v2) == -1) {  // new edge
      aList[v1].insert(0, v2);
      e++;
    }
  }

  void insertEdgeNoCheck(
      edge<bool>* theEdge) {  // Insert an edge. No validation checks performed.
    aList[theEdge->vertex1()].insert(0, theEdge->vertex2());
    e++;
  }

  void eraseEdge(int i, int j) {
    if (i >= 1 && j >= 1 && i <= n && j <= n) {
      int* v = aList[i].eraseElement(j);
      if (v != nullptr)  // edge (i,j) did exist
        e--;
    }
  }

  void checkVertex(int theVertex) const {  // Verify that i is a valid vertex.
    if (theVertex < 1 || theVertex > n) {
      std::ostringstream s;
      s << "no vertex " << theVertex;
      throw illegalParameterValue(s.str());
    }
  }

  int degree(int theVertex) const {
    throw undefinedMethod("degree() undefined");
  }

  int outDegree(
      int theVertex) const {  // Return out-degree of vertex theVertex.
    checkVertex(theVertex);
    return aList[theVertex].size();
  }

  int inDegree(int theVertex) const {
    checkVertex(theVertex);

    // count in-edges at vertex theVertex
    int sum = 0;
    for (int j = 1; j <= n; j++)
      if (aList[j].indexOf(theVertex) != -1) sum++;

    return sum;
  }

  class myIterator : public vertexIterator<bool> {
   public:
    myIterator(chainNode<int>* theNode) { currentNode = theNode; }

    ~myIterator() {}

    int next() {  // Return next vertex if any. Return 0 if no next vertex.
                  // find next adjacent vertex
      if (currentNode == nullptr) return 0;
      int nextVertex = currentNode->element;
      currentNode = currentNode->next;
      return nextVertex;
    }

    int next(bool& theWeight) {  // Return next vertex if any. Return 0 if no
                                 // next vertex. Set theWeight = edge weight.
                                 // find next adjacent vertex
      if (currentNode == nullptr) return 0;
      int nextVertex = currentNode->element;
      currentNode = currentNode->next;
      theWeight = true;
      return nextVertex;
    }

   protected:
    chainNode<int>* currentNode;
  };

  myIterator* iterator(
      int theVertex) {  // Return iterator for vertex theVertex.
    checkVertex(theVertex);
    return new myIterator(aList[theVertex].firstNode);
  }

  void output(std::ostream& out) const {  // Output the adjacency matrix.
    for (int i = 1; i <= n; i++) out << aList[i] << std::endl;
  }

  void input(std::istream& in) {
    in >> n >> e;
    delete[] aList;
    aList = new graphChain<int>[n + 1];

    for (int i = 0; i < e; i++) {
      int v1, v2;
      in >> v1 >> v2;

      if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2) {
        std::ostringstream s;
        s << "(" << v1 << "," << v2 << ") is not a permissible edge";
        throw illegalParameterValue(s.str());
      }

      if (aList[v1].indexOf(v2) == -1) {  // new edge
        aList[v1].insert(0, v2);
      }
    }
  }

  void bfs(int v, int reach[],
           int label) {  // Breadth-first search. reach[i] is set to label for
                         // all vertices reachable from vertex v.
    std::queue<int> q;
    reach[v] = label;
    q.push(v);
    while (!q.empty()) {
      // remove a labeled vertex from the queue
      int w = q.front();
      q.pop();

      // mark all unreached vertices adjacent from w
      for (chainNode<int>* u = aList[w].firstNode; u != nullptr; u = u->next)
        // visit an adjacent vertex of w
        if (reach[u->element] == 0) {  // u->element is an unreached vertex
          q.push(u->element);
          reach[u->element] = label;  // mark reached
        }
    }
  }

  void dfs(int v, int reach[],
           int label) {  // Depth-first search. reach[i] is set to label for all
                         // vertices reachable from vertex v
    graph<bool>::reach = reach;
    graph<bool>::label = label;
    rDfs(v);
  }

 protected:
  void rDfs(int v) {
    graph<bool>::reach[v] = graph<bool>::label;
    for (auto u = aList[v].begin(); u != aList[v].end(); ++u)
      if (graph<bool>::reach[*u] == 0) rDfs(*u);
  }
};

// overload <<
std::ostream& operator<<(std::ostream& out, const linkedDigraph& x) {
  x.output(out);
  return out;
}
// overload >>
std::istream& operator>>(std::istream& in, linkedDigraph& x) {
  x.input(in);
  return in;
}
#endif