#include <iostream>
#include <map>
// vertex = Bandara
// edge = Rute
using namespace std;
struct Vertex {
    string idBandara;
    string namaBandara;
    int jumlahOrang;
    Vertex* nextVertex;
    struct Edge* firstEdge;
};
struct Edge {
    string destVertexId;
    int jarak;
    struct Edge* nextEdge;
};
struct Graph {
    Vertex* firstVertex;
};

void addVertex(Graph& G, string id, string nama, int jumlahOrang);
void addEdge(Graph& G, string asal, string tujuan, int jarak);
Vertex* searchVertex(Graph G, string id);
void displayVertex(Graph G);
void displayEdge(Graph G, string idBandara);
void dijkstra(Graph G, string idAsal, string idTujuan);
int jumlahVertex(Graph G);
map<string, int> findMostFrequentTransit(Graph G);
void printMostFrequentTransit(Graph G);
void findAlternativeRoute(Graph G, string idAsal, string idTujuan, string closedAirport);
void deleteVertex(Graph& G, string id);
void deleteEdge(Graph& G, string asal, string tujuan);
