#include "graph.h"
void addVertex(Graph& G, string id, string nama, int jumlahOrang) {
    Vertex* newVertex = new Vertex;
    newVertex->idBandara = id;
    newVertex->namaBandara = nama;
    newVertex->jumlahOrang = jumlahOrang;
    newVertex->nextVertex = NULL;
    newVertex->firstEdge = NULL;
    if (G.firstVertex == NULL) {
        G.firstVertex = newVertex;
    } else {
        Vertex* curr = G.firstVertex;
        while (curr->nextVertex != NULL) {
            curr = curr->nextVertex;
        }
        curr->nextVertex = newVertex;
    }
}
void addEdge(Graph& G, string asal, string tujuan, int jarak) {
    Vertex* asalVertex = G.firstVertex;
    while (asalVertex != NULL && asalVertex->idBandara != asal) {
        asalVertex = asalVertex->nextVertex;
    }
    if (asalVertex == NULL) {
        cout << "Bandara asal tidak ditemukan!" << endl;
        return;
    }
    Edge* newEdge = new Edge;
    newEdge->destVertexId = tujuan;
    newEdge->jarak = jarak;
    newEdge->nextEdge = NULL;

    if (asalVertex->firstEdge == NULL) {
        asalVertex->firstEdge = newEdge;
    } else {
        Edge* curr = asalVertex->firstEdge;
        while (curr->nextEdge != NULL) {
            curr = curr->nextEdge;
        }
        curr->nextEdge = newEdge;
    }
}
Vertex* searchVertex(Graph G, string id) {
    Vertex* curr = G.firstVertex;
    while (curr != NULL && curr->idBandara != id) {
        curr = curr->nextVertex;
    }
    return curr;
}
void displayVertex(Graph G) {
    Vertex* curr = G.firstVertex;
    while (curr != NULL) {
        cout << curr->idBandara << " - " << curr->namaBandara << endl;
        curr = curr->nextVertex;
    }
}
void displayEdge(Graph G, string idBandara) {
    Vertex* currVertex = searchVertex(G, idBandara);
    if (currVertex == NULL) {
        cout << "Bandara tidak ditemukan!" << endl;
        return;
    }
    Edge* currEdge = currVertex->firstEdge;
    while (currEdge != NULL) {
        cout << currVertex->idBandara << " -> " << currEdge->destVertexId
             << " (" << currEdge->jarak << " km)" << endl;
        currEdge = currEdge->nextEdge;
    }
}
void dijkstra(Graph G, string idAsal, string idTujuan) {
    // 1. Inisialisasi
    map<string, int> distances;
    map<string, string> previous;
    map<string, bool> visited;

    for (Vertex* v = G.firstVertex; v != NULL; v = v->nextVertex) {
        distances[v->idBandara] = INT_MAX;
        previous[v->idBandara] = "";
        visited[v->idBandara] = false;
    }

    distances[idAsal] = 0;

    // 2. Cari vertex dengan jarak minimum yang belum dikunjungi
    for (int count = 0; count < jumlahVertex(G) - 1; count++) {
        int minDist = INT_MAX;
        string u;

        for (Vertex* v = G.firstVertex; v != NULL; v = v->nextVertex) {
            if (!visited[v->idBandara] && distances[v->idBandara] <= minDist) {
                minDist = distances[v->idBandara];
                u = v->idBandara;
            }
        }
        //Jika tidak ditemukan lagi vertex yang terhubung
        if(minDist == INT_MAX) break;

        visited[u] = true;

        // 3. Update jarak vertex yang bertetangga dengan u
        Vertex* uVertex = searchVertex(G, u);
        for (Edge* e = uVertex->firstEdge; e != NULL; e = e->nextEdge) {
            Vertex* vVertex = searchVertex(G, e->destVertexId);
            if (!visited[vVertex->idBandara] && distances[u] != INT_MAX && distances[u] + e->jarak < distances[vVertex->idBandara]) {
                distances[vVertex->idBandara] = distances[u] + e->jarak;
                previous[vVertex->idBandara] = u;
            }
        }
    }

    // 4. Cetak jalur terpendek
    if (distances[idTujuan] == INT_MAX) {
        cout << "Tidak ada rute yang tersedia dari " << idAsal << " ke " << idTujuan << endl;
    } else {
        cout << "Jarak terpendek dari " << idAsal << " ke " << idTujuan << ": " << distances[idTujuan] << " km" << endl;
        cout << "Rute: ";
        string curr = idTujuan;
        string path;
        while (curr != "") {
            path = curr + " " + path;
            curr = previous[curr];
        }
        cout << path << endl;
    }
}

//Fungsi untuk menghitung jumlah vertex
int jumlahVertex(Graph G){
    int count = 0;
    Vertex* curr = G.firstVertex;
    while(curr != NULL){
        count++;
        curr = curr->nextVertex;
    }
    return count;
}
map<string, int> findMostFrequentTransit(Graph G) {
    map<string, int> transitCounts;

    for (Vertex* v = G.firstVertex; v != NULL; v = v->nextVertex) {
        for (Edge* e = v->firstEdge; e != NULL; e = e->nextEdge) {
            // Tambahkan hitungan untuk bandara asal dan tujuan
            transitCounts[v->idBandara]++;
            transitCounts[e->destVertexId]++;
        }
    }

    return transitCounts;
}
void printMostFrequentTransit(Graph G) {
    map<string, int> transitCounts = findMostFrequentTransit(G);

    int maxTransit = 0;
    string busiestTransit = "";

    for (auto const& [airport, count] : transitCounts) {
        if (count > maxTransit) {
            maxTransit = count;
            busiestTransit = airport;
        }
    }
    cout << "Bandara transit tersibuk: " << busiestTransit << " dengan " << maxTransit << " penerbangan" << endl;
}
void findAlternativeRoute(Graph G, string idAsal, string idTujuan, string closedAirport) {
    // Buat graf sementara yang tidak menyertakan bandara yang ditutup
    Graph tempGraph;
    tempGraph.firstVertex = NULL;

    // Salin vertex dan edge ke graf sementara, kecuali yang melibatkan closedAirport
    for (Vertex* v = G.firstVertex; v != NULL; v = v->nextVertex) {
        if (v->idBandara != closedAirport) {
            addVertex(tempGraph, v->idBandara, v->namaBandara, v->jumlahOrang);
        }
    }

    for (Vertex* v = G.firstVertex; v != NULL; v = v->nextVertex) {
        if (v->idBandara != closedAirport) {
            for (Edge* e = v->firstEdge; e != NULL; e = e->nextEdge) {
                if (e->destVertexId != closedAirport) {
                    addEdge(tempGraph, v->idBandara, e->destVertexId, e->jarak);
                }
            }
        }
    }

    // Jalankan Dijkstra pada graf sementara
    dijkstra(tempGraph, idAsal, idTujuan);
}
void deleteVertex(Graph& G, string id) {
    Vertex* curr = G.firstVertex;
    Vertex* prev = NULL;

    // Cari vertex yang akan dihapus
    while (curr != NULL && curr->idBandara != id) {
        prev = curr;
        curr = curr->nextVertex;
    }

    if (curr == NULL) {
        cout << "Bandara tidak ditemukan!" << endl;
        return;
    }
    // Hapus semua edge yang terhubung ke vertex lain dari vertex ini
    for (Vertex* v = G.firstVertex; v != NULL; v = v->nextVertex) {
        if (v->idBandara != id) {
            deleteEdge(G, v->idBandara, id);
        }
    }

    // Hapus semua edge yang terhubung ke vertex ini
    Edge* edge = curr->firstEdge;
    while (edge != NULL) {
        Edge* tempEdge = edge;
        edge = edge->nextEdge;
        delete tempEdge;
    }

    // Hapus vertex dari linked list
    if (prev == NULL) {
        G.firstVertex = curr->nextVertex;
    } else {
        prev->nextVertex = curr->nextVertex;
    }

    delete curr;
    cout << "Bandara berhasil dihapus!" << endl;
}
void deleteEdge(Graph& G, string asal, string tujuan) {
    Vertex* asalVertex = searchVertex(G, asal);

    if (asalVertex == NULL) {
        cout << "Bandara asal tidak ditemukan!" << endl;
        return;
    }

    Edge* curr = asalVertex->firstEdge;
    Edge* prev = NULL;

    // Cari edge yang akan dihapus
    while (curr != NULL && curr->destVertexId != tujuan) {
        prev = curr;
        curr = curr->nextEdge;
    }

    if (curr == NULL) {
        cout << "Rute penerbangan tidak ditemukan!" << endl;
        return;
    }

    // Hapus edge dari linked list
    if (prev == NULL) {
        asalVertex->firstEdge = curr->nextEdge;
    } else {
        prev->nextEdge = curr->nextEdge;
    }

    delete curr;
    cout << "Rute penerbangan berhasil dihapus!" << endl;
}

