
```markdown
# Desain Algoritma

Dokumen ini menjelaskan desain algoritma yang digunakan dalam program Sistem Rekomendasi Rute Penerbangan.

## Struktur Data

Program ini menggunakan struktur data **Graph** untuk merepresentasikan jaringan penerbangan. Berikut adalah definisi struktur data yang digunakan:


struct Vertex {
    string idBandara;       // ID unik bandara (misal: CGK)
    string namaBandara;     // Nama lengkap bandara (misal: Soekarno-Hatta)
    int jumlahOrang;       // Perkiraan jumlah orang di bandara
    Vertex* nextVertex;     // Pointer ke vertex (bandara) berikutnya dalam adjacency list
    struct Edge* firstEdge; // Pointer ke edge (rute) pertama yang keluar dari vertex ini
};

struct Edge {
    string destVertexId;    // ID bandara tujuan rute ini
    int jarak;             // Jarak penerbangan dalam kilometer
    struct Edge* nextEdge;  // Pointer ke edge (rute) berikutnya dalam adjacency list
};

struct Graph {
    Vertex* firstVertex;    // Pointer ke vertex (bandara) pertama dalam graph
};
```

*   **Vertex (Simpul):** Merepresentasikan bandara.
*   **Edge (Sisi):** Merepresentasikan rute penerbangan antara dua bandara.
*   **Graph:** Merepresentasikan keseluruhan jaringan penerbangan.

## Algoritma Dijkstra

Algoritma Dijkstra digunakan untuk menemukan jalur terpendek dari satu bandara asal ke semua bandara lain dalam graf. Berikut adalah langkah-langkah algoritma Dijkstra yang diimplementasikan dalam fungsi `dijkstra`:

**`int dijkstra(Graph G, string idAsal, string idTujuan)`**

**Input:**

*   `Graph G`: Graf yang merepresentasikan jaringan penerbangan.
*   `string idAsal`: ID bandara asal.
*   `string idTujuan`: ID bandara tujuan.

**Output:**

*   Jarak terpendek dari `idAsal` ke `idTujuan` berupa `int`. Jika tidak ada jalur mengembalikan -1.
*   (Efek Samping) Mencetak jarak terpendek dan jalur yang dilalui dari `idAsal` ke `idTujuan`.

**Langkah-langkah:**

1.  **Inisialisasi:**
    *   Buat map `distances` untuk menyimpan jarak terpendek dari `idAsal` ke setiap bandara. Inisialisasi jarak ke semua bandara dengan infinity (diwakili oleh `INT_MAX`), kecuali bandara asal yang jaraknya 0.
    *   Buat map `previous` untuk menyimpan *predecessor* (bandara sebelumnya) dari setiap bandara pada jalur terpendek. Inisialisasi semua *predecessor* dengan string kosong ("").
    *   Buat map `visited` untuk menandai apakah suatu bandara sudah dikunjungi atau belum. Inisialisasi semua bandara dengan `false`.

    ```c++
    map<string, int> distances;
    map<string, string> previous;
    map<string, bool> visited;

    for (Vertex* v = G.firstVertex; v != NULL; v = v->nextVertex) {
        distances[v->idBandara] = INT_MAX;
        previous[v->idBandara] = "";
        visited[v->idBandara] = false;
    }

    distances[idAsal] = 0;
    ```

2.  **Iterasi:**
    *   Ulangi langkah-langkah berikut hingga semua bandara dikunjungi atau tidak ada lagi jalur yang bisa di optimalkan.

    ```c++
    for (int count = 0; count < jumlahVertex(G) - 1; count++) {
        // ... (Langkah 2.a, 2.b, dan 2.c) ...
    }
    ```

    *   **a. Temukan Bandara Belum Dikunjungi dengan Jarak Minimum:**
        *   Cari bandara `u` yang belum dikunjungi (`visited[u] == false`) dan memiliki jarak terpendek minimum dari `idAsal` (berdasarkan `distances`).

        ```c++
        int minDist = INT_MAX;
        string u;

        for (Vertex* v = G.firstVertex; v != NULL; v = v->nextVertex) {
            if (!visited[v->idBandara] && distances[v->idBandara] <= minDist) {
                minDist = distances[v->idBandara];
                u = v->idBandara;
            }
        }

        if(minDist == INT_MAX) break;
        ```

    *   **b. Tandai Bandara Terpilih sebagai Dikunjungi:**
        *   Tandai bandara `u` yang terpilih sebagai dikunjungi (`visited[u] = true`).

        ```c++
        visited[u] = true;
        ```

    *   **c. Perbarui Jarak Bandara Tetangga:**
        *   Untuk setiap bandara tetangga `v` dari `u` (yang terhubung dengan edge dari `u`):
            *   Hitung `jarakAlternatif` dari `idAsal` ke `v` melalui `u` (`distances[u] + jarak(u, v)`).
            *   Jika `jarakAlternatif` lebih kecil dari `distances[v]` saat ini, perbarui `distances[v]` dengan `jarakAlternatif` dan atur `previous[v]` menjadi `u`.

        ```c++
        Vertex* uVertex = searchVertex(G, u);
        for (Edge* e = uVertex->firstEdge; e != NULL; e = e->nextEdge) {
            Vertex* vVertex = searchVertex(G, e->destVertexId);
            if (!visited[vVertex->idBandara] && distances[u] != INT_MAX && distances[u] + e->jarak < distances[vVertex->idBandara]) {
                distances[vVertex->idBandara] = distances[u] + e->jarak;
                previous[vVertex->idBandara] = u;
            }
        }
        ```

3.  **Cetak Jalur Terpendek (dan Kembalikan Jarak):**
    *   Jika `distances[idTujuan]` masih `INT_MAX`, berarti tidak ada jalur yang tersedia dari `idAsal` ke `idTujuan`. Cetak pesan yang sesuai dan kembalikan -1.
    *   Jika tidak, cetak jarak terpendek (`distances[idTujuan]`).
    *   Rekonstruksi jalur terpendek dari `idTujuan` kembali ke `idAsal` dengan menelusuri `previous` dan cetak jalur tersebut dan kembalikan `distances[idTujuan]`.

    ```c++
    if (distances[idTujuan] == INT_MAX) {
        cout << "Tidak ada rute yang tersedia dari " << idAsal << " ke " << idTujuan << endl;
        return -1;
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
        return distances[idTujuan];
    }
    ```

## Algoritma findMostFrequentTransit

Algoritma ini digunakan untuk mencari bandara transit tersibuk.

**`map<string, int> findMostFrequentTransit(Graph G)`**

**Input:**

*   `Graph G`: Graf yang merepresentasikan jaringan penerbangan.

**Output:**

*   `map<string, int> transitCounts`: Map yang berisi jumlah transit untuk setiap bandara.

**Langkah-langkah:**

1.  **Inisialisasi:**
    *   Buat map `transitCounts` untuk menyimpan jumlah transit untuk setiap bandara.

    ```c++
    map<string, int> transitCounts;
    ```

2.  **Iterasi:**
    *   Iterasi melalui setiap bandara (vertex) dalam graf.
    *   Untuk setiap bandara, iterasi melalui semua rute penerbangan (edge) yang keluar dari bandara tersebut.
    *   Untuk setiap rute, tambahkan 1 ke `transitCounts` untuk bandara asal dan bandara tujuan.

    ```c++
    for (Vertex* v = G.firstVertex; v != NULL; v = v->nextVertex) {
        for (Edge* e = v->firstEdge; e != NULL; e = e->nextEdge) {
            // Tambahkan hitungan untuk bandara asal dan tujuan
            transitCounts[v->idBandara]++;
            transitCounts[e->destVertexId]++;
        }
    }
    ```

3.  **Kembalikan Hasil:**
    *   Kembalikan `transitCounts`.

**`void printMostFrequentTransit(Graph G)`**

**Input:**

*   `Graph G`: Graf yang merepresentasikan jaringan penerbangan.

**Output:**

*   (Efek Samping) Mencetak bandara transit tersibuk dan jumlah transitnya.

**Langkah-langkah:**

1.  **Hitung Jumlah Transit:**
    *   Panggil `findMostFrequentTransit(G)` untuk mendapatkan jumlah transit untuk setiap bandara.

    ```c++
    map<string, int> transitCounts = findMostFrequentTransit(G);
    ```

2.  **Cari Transit Maksimum:**
    *   Inisialisasi `maxTransit` dengan 0 dan `busiestTransit` dengan string kosong.
    *   Iterasi melalui `transitCounts`.
    *   Untuk setiap bandara, jika jumlah transitnya lebih besar dari `maxTransit`, perbarui `maxTransit` dan `busiestTransit`.

    ```c++
    int maxTransit = 0;
    string busiestTransit = "";

    for (auto const& [airport, count] : transitCounts) {
        if (count > maxTransit) {
            maxTransit = count;
            busiestTransit = airport;
        }
    }
    ```

3.  **Cetak Hasil:**
    *   Cetak `busiestTransit` dan `maxTransit`.

    ```c++
    cout << "Bandara transit tersibuk: " << busiestTransit << " dengan " << maxTransit << " penerbangan" << endl;
    ```

## Algoritma findAlternativeRoute

Algoritma ini digunakan untuk mencari rute alternatif jika suatu bandara ditutup.

**`void findAlternativeRoute(Graph G, string idAsal, string idTujuan, string closedAirport)`**

**Input:**

*   `Graph G`: Graf yang merepresentasikan jaringan penerbangan.
*   `string idAsal`: ID bandara asal.
*   `string idTujuan`: ID bandara tujuan.
*   `string closedAirport`: ID bandara yang ditutup.

**Output:**

*   (Efek Samping) Mencetak rute alternatif terpendek dan jaraknya jika bandara `closedAirport` ditutup.

**Langkah-langkah:**

1.  **Buat Graf Sementara:**
    *   Buat graf baru `tempGraph` yang merupakan salinan dari `G`, tetapi tanpa bandara `closedAirport` dan semua rute yang terhubung dengannya.

    ```c++
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
    ```

2.  **Jalankan Dijkstra:**
    *   Panggil fungsi `dijkstra` pada `tempGraph` dengan `idAsal` dan `idTujuan` untuk mencari jalur terpendek di graf sementara.

    ```c++
    int shortestDistance = dijkstra(tempGraph, idAsal, idTujuan);
    if(shortestDistance == -1){
        cout << "Tidak ada rute alternatif yang tersedia jika bandara " << closedAirport << " ditutup." << endl;
    }
    ```

## Algoritma deleteVertex

Algoritma ini digunakan untuk menghapus vertex atau bandara beserta seluruh edge yang berhubungan dengannya

**`void deleteVertex(Graph& G, string id)`**

**Input:**

*   `Graph G`: Graf yang merepresentasikan jaringan penerbangan.
*   `string id`: ID bandara yang akan dihapus.

**Output:**

*   (Efek Samping) Menghapus vertex dengan `id` yang sesuai beserta edge yang bersangkutan dan mencetak pemberitahuan keberhasilan penghapusan.

**Langkah-langkah:**

1.  **Cari vertex yang akan dihapus:**
    *   Lakukan perulangan pada setiap vertex pada `Graph G` dengan pointer `curr` dan `prev` untuk menunjuk vertex sebelumnya.
    *   Jika `id` vertex sama dengan `id` yang dicari, maka hentikan perulangan

    ```c++
    Vertex* curr = G.firstVertex;
    Vertex* prev = NULL;

    // Cari vertex yang akan dihapus
    while (curr != NULL && curr->idBandara != id) {
        prev = curr;
        curr = curr->nextVertex;
    }
    ```

2.  **Hapus semua edge yang terhubung ke vertex lain dari vertex ini:**
    *   Lakukan perulangan pada setiap vertex pada `Graph G`.
    *   Jika `id` vertex tidak sama dengan `id` yang ingin dihapus maka panggil `deleteEdge` untuk menghapus edge yang mengarah ke vertex yang akan dihapus.

    ```c++
    for (Vertex* v = G.firstVertex; v != NULL; v = v->nextVertex) {
        if (v->idBandara != id) {
            deleteEdge(G, v->idBandara, id);
        }
    }
    ```

3.  **Hapus semua edge yang terhubung ke vertex ini:**
    *   Lakukan perulangan untuk menghapus setiap edge pada `firstEdge` dari vertex yang ingin dihapus.

    ```c++
    Edge* edge = curr->firstEdge;
    while (edge != NULL) {
        Edge* tempEdge = edge;
        edge = edge->nextEdge;
        delete tempEdge;
    }
    ```

4.  **Hapus vertex dari linked list:**
    *   Jika `prev` sama dengan `NULL`, maka vertex yang dihapus adalah vertex pertama.
    *   Jika `prev` tidak sama dengan `NULL`, maka vertex yang dihapus bukan vertex pertama.

    ```c++
    if (prev == NULL) {
        G.firstVertex = curr->nextVertex;
    } else {
        prev->nextVertex = curr->nextVertex;
    }
    ```

5.  **Hapus vertex:**
    *   Hapus vertex yang sudah tidak terhubung dengan vertex lain dan mencetak pemberitahuan keberhasilan

    ```c++
    delete curr;
    cout << "Bandara berhasil dihapus!" << endl;
    ```

## Algoritma deleteEdge

Algoritma ini digunakan untuk menghapus edge atau rute penerbangan.

**`void deleteEdge(Graph& G, string asal, string tujuan)`**

**Input:**

*   `Graph G`: Graf yang merepresentasikan jaringan penerbangan.
*   `string asal`: ID bandara asal.
*   `string tujuan`: ID bandara tujuan.

**Output:**

*   (Efek Samping) Menghapus edge dengan `id` asal dan tujuan yang sesuai dan mencetak pemberitahuan keberhasilan penghapusan.

**Langkah-langkah:**

1.  **Cari vertex asal:**
    *   Cari vertex asal dengan `id` yang sesuai dengan `id` yang dicari dengan memanggil fungsi `searchVertex`.

    ```c++
    Vertex* asalVertex = searchVertex(G, asal);
    ```

2.  **Cari edge yang akan dihapus:**
    *   Lakukan perulangan pada setiap edge pada `firstEdge` dari `asalVertex` dengan pointer `curr` dan `prev` untuk menunjuk edge sebelumnya.
    *   Jika `destVertexId` edge sama dengan `tujuan` yang dicari, maka hentikan perulangan

    ```c++
    Edge* curr = asalVertex->firstEdge;
    Edge* prev = NULL;

    // Cari edge yang akan dihapus
    while (curr != NULL && curr->destVertexId != tujuan) {
        prev = curr;
        curr = curr->nextEdge;
    }
    ```

3.  **Hapus edge dari linked list:**
    *   Jika `prev` sama dengan `NULL`, maka edge yang dihapus adalah edge pertama.
    *   Jika `prev` tidak sama dengan `NULL`, maka edge yang dihapus bukan edge pertama.

    ```c++
    if (prev == NULL) {
        asalVertex->firstEdge = curr->nextEdge;
    } else {
        prev->nextEdge = curr->nextEdge;
    }
    ```
4.  **Hapus edge:**
    *   Hapus edge yang sudah tidak terhubung dengan edge lain dan mencetak pemberitahuan keberhasilan

    ```c++
    delete curr;
    cout << "Rute penerbangan berhasil dihapus!" << endl;
    ```
## Algoritma Lainnya

*   **`addVertex(Graph& G, string id, string nama, int jumlahOrang)`:** Menambahkan bandara (vertex) baru ke dalam graf.
*   **`addEdge(Graph& G, string asal, string tujuan, int jarak)`:** Menambahkan rute penerbangan (edge) baru ke dalam graf.
*   **`searchVertex(Graph G, string id)`:** Mencari bandara (vertex) berdasarkan ID-nya.
*   **`displayVertex(Graph G)`:** Menampilkan semua bandara (vertex) dalam graf.
*   **`displayEdge(Graph G, string idBandara)`:** Menampilkan semua rute penerbangan (edge) yang keluar dari bandara tertentu.
*   **`jumlahVertex(Graph G)`:** Menghitung jumlah bandara (vertex) dalam graf.

## Catatan

*   Kode program di atas hanya merupakan ilustrasi dan mungkin perlu dimodifikasi agar sesuai dengan implementasi yang sebenarnya.
*   Penanganan error yang lebih robus, seperti validasi input, dapat ditambahkan ke dalam fungsi-fungsi di atas.

## Kesimpulan

*   Dokumen ini telah menjelaskan desain algoritma yang digunakan dalam program Sistem Rekomendasi Rute Penerbangan, termasuk algoritma Dijkstra, algoritma untuk mencari bandara transit tersibuk, dan algoritma untuk mencari rute alternatif.

**Penjelasan Tambahan:**

*   **Algoritma `addVertex`:**
    1.  Membuat `Vertex` baru dengan data yang diberikan (ID, nama, jumlah orang).
    2.  Jika graf kosong (`G.firstVertex == NULL`), jadikan `Vertex` baru sebagai `firstVertex`.
    3.  Jika tidak, telusuri graf hingga akhir (menggunakan `curr->nextVertex`) dan tambahkan `Vertex` baru di akhir.

*   **Algoritma `addEdge`:**
    1.  Cari `Vertex` asal menggunakan `searchVertex`.
    2.  Jika `Vertex` asal tidak ditemukan, cetak pesan error dan kembali.
    3.  Buat `Edge` baru dengan data yang diberikan (ID tujuan, jarak).
    4.  Jika `Vertex` asal belum memiliki `Edge` (`asalVertex->firstEdge == NULL`), jadikan `Edge` baru sebagai `firstEdge`.
    5.  Jika tidak, telusuri daftar `Edge` hingga akhir (menggunakan `curr->nextEdge`) dan tambahkan `Edge` baru di akhir.

*   **Algoritma `searchVertex`:**
    1.  Telusuri graf dari `firstVertex` hingga menemukan `Vertex` dengan ID yang sesuai atau hingga akhir graf.
    2.  Kembalikan `Vertex` yang ditemukan, atau `NULL` jika tidak ditemukan.

*   **Algoritma `displayVertex`:**
    1.  Telusuri graf dari `firstVertex`.
    2.  Untuk setiap `Vertex`, cetak ID dan nama bandara.

*   **Algoritma `displayEdge`:**
    1.  Cari `Vertex` asal menggunakan `searchVertex`.
    2.  Jika `Vertex` asal tidak ditemukan, cetak pesan error dan kembali.
    3.  Telusuri daftar `Edge` dari `firstEdge` milik `Vertex` asal.
    4.  Untuk setiap `Edge`, cetak ID bandara asal, ID bandara tujuan, dan jarak.

*   **Algoritma `jumlahVertex`:**
    1.  Inisialisasi `count` dengan 0.
    2.  Telusuri graf dari `firstVertex`.
    3.  Untuk setiap `Vertex`, tambahkan 1 ke `count`.
    4.  Kembalikan `count`.
