#include "graph.h"

int main() {
    Graph grafPenerbangan;
    grafPenerbangan.firstVertex = NULL;

    // Data awal
    addVertex(grafPenerbangan, "CGK", "Soekarno-Hatta", 5250);
    addVertex(grafPenerbangan, "SUB", "Juanda", 3129);
    addVertex(grafPenerbangan, "DPS", "Ngurah Rai", 4812);
    addVertex(grafPenerbangan, "BDO", "Husein Sastranegara", 1874);
    addVertex(grafPenerbangan, "YIA", "Yogyakarta International Airport", 3782);

    addEdge(grafPenerbangan, "CGK", "SUB", 600);
    addEdge(grafPenerbangan, "CGK", "YIA", 500);
    addEdge(grafPenerbangan, "CGK", "BDO", 190);

    addEdge(grafPenerbangan, "SUB", "DPS", 300);
    addEdge(grafPenerbangan, "SUB", "CGK", 600);
    addEdge(grafPenerbangan, "SUB", "YIA", 300);

    addEdge(grafPenerbangan, "BDO", "CGK", 190);
    addEdge(grafPenerbangan, "BDO", "YIA", 400);
    addEdge(grafPenerbangan, "BDO", "DPS", 890);

    addEdge(grafPenerbangan, "YIA", "CGK", 500);
    addEdge(grafPenerbangan, "YIA", "BDO", 400);
    addEdge(grafPenerbangan, "YIA", "DPS", 600);
    addEdge(grafPenerbangan, "YIA", "SUB", 300);

    addEdge(grafPenerbangan, "DPS", "YIA", 600);
    addEdge(grafPenerbangan, "DPS", "SUB", 300);
    addEdge(grafPenerbangan, "DPS", "BDO", 890);

    int pilihan;

    do {
        cout << "\nMenu Sistem Rekomendasi Rute Penerbangan" << endl;
        cout << "1.  Tambah Bandara" << endl;
        cout << "2.  Tambah Rute Penerbangan" << endl;
        cout << "3.  Hapus Bandara" << endl;
        cout << "4.  Hapus Rute Penerbangan" << endl;
        cout << "5.  Cari Rute Terpendek (Dijkstra)" << endl;
        cout << "6.  Tampilkan Semua Bandara" << endl;
        cout << "7.  Tampilkan Semua Rute dari Bandara" << endl;
        cout << "8.  Tampilkan Bandara Transit Tersibuk" << endl;
        cout << "9.  Cari Rute Alternatif (Jika Bandara Ditutup)" << endl;
        cout << "0.  Keluar" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;


        switch (pilihan) {
            case 1: {
                string id, nama;
                int jumlahOrang;
                cout << "Masukkan ID Bandara: ";
                cin >> id;
                cout << "Masukkan Nama Bandara: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Perkiraan Jumlah Orang: ";
                cin >> jumlahOrang;
                addVertex(grafPenerbangan, id, nama, jumlahOrang);
                cout << "Bandara berhasil ditambahkan!" << endl;
                break;
            }
            case 2: {
                string asal, tujuan;
                int jarak;
                cout << "Masukkan ID Bandara Asal: ";
                cin >> asal;
                cout << "Masukkan ID Bandara Tujuan: ";
                cin >> tujuan;
                cout << "Masukkan Jarak (km): ";
                cin >> jarak;
                addEdge(grafPenerbangan, asal, tujuan, jarak);
                cout << "Rute penerbangan berhasil ditambahkan!" << endl;
                break;
            }
            case 3: {
                string id;
                cout << "Masukkan ID Bandara yang akan dihapus: ";
                cin >> id;
                // Implementasikan fungsi deleteVertex
                deleteVertex(grafPenerbangan, id);
                break;
            }
            case 4: {
                string asal, tujuan;
                cout << "Masukkan ID Bandara Asal: ";
                cin >> asal;
                cout << "Masukkan ID Bandara Tujuan: ";
                cin >> tujuan;
                // Implementasikan fungsi deleteEdge
                deleteEdge(grafPenerbangan, asal, tujuan);
                break;
            }
            case 5: {
                string asal, tujuan;
                cout << "Masukkan ID Bandara Asal: ";
                cin >> asal;
                cout << "Masukkan ID Bandara Tujuan: ";
                cin >> tujuan;
                dijkstra(grafPenerbangan, asal, tujuan);
                break;
            }
            case 6: {
                cout << "\nDaftar Bandara:" << endl;
                displayVertex(grafPenerbangan);
                break;
            }
            case 7: {
                string id;
                cout << "Masukkan ID Bandara: ";
                cin >> id;
                displayEdge(grafPenerbangan, id);
                break;
            }
            case 8: {
                printMostFrequentTransit(grafPenerbangan);
                break;
            }
            case 9: {
                string asal, tujuan, closed;
                cout << "Masukkan ID Bandara Asal: ";
                cin >> asal;
                cout << "Masukkan ID Bandara Tujuan: ";
                cin >> tujuan;
                cout << "Masukkan ID Bandara yang Ditutup: ";
                cin >> closed;
                findAlternativeRoute(grafPenerbangan, asal, tujuan, closed);
                break;
            }
            case 0:
                cout << "Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
