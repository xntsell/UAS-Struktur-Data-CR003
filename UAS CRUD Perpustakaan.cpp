#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Mahasiswa {
    string nama;
    string NIM;
    string fakultas;
    string jurusan;
    string password;
};

struct Buku {
    string judul;
    string pengarang;
    string penerbit;
    string tahun_terbit;
};

vector<Buku> buku_list;

bool login(string nama, string NIM, string jurusan, string password) {
    if (nama == "Chrisella Natasia Tanujaya" && NIM == "20230803002" && jurusan == "Sistem Informasi" && password == "univesaunggul") {
        return true;
    }
    return false;
}

void loadBukuData() {
    ifstream file("buku.txt");
    if (file.is_open()) {
        Buku buku;
        while (file >> buku.judul >> buku.pengarang >> buku.penerbit >> buku.tahun_terbit) {
            buku_list.push_back(buku);
        }
        file.close();
    }
}

void saveBukuData() {
    ofstream file("buku.txt");
    if (file.is_open()) {
        for (const auto& buku : buku_list) {
            file << buku.judul << " " << buku.pengarang << " " << buku.penerbit << " " << buku.tahun_terbit << endl;
        }
        file.close();
    }
}

void createBuku() {
    Buku buku;
    cout << "Masukkan judul buku: ";
    cin >> buku.judul;
    cout << "Masukkan pengarang buku: ";
    cin >> buku.pengarang;
    cout << "Masukkan penerbit buku: ";
    cin >> buku.penerbit;
    cout << "Masukkan tahun terbit buku: ";
    cin >> buku.tahun_terbit;
    buku_list.push_back(buku);
    saveBukuData();
}

void readBuku() {
    cout << left << setw(20) << "Judul" << setw(20) << "Pengarang" << setw(20) << "Penerbit" << setw(20) << "Tahun Terbit" << endl;
    for (const auto& buku : buku_list) {
        cout << left << setw(20) << buku.judul << setw(20) << buku.pengarang << setw(20) << buku.penerbit << setw(20) << buku.tahun_terbit << endl;
    }
}

void updateBuku() {
    string judul;
    cout << "Masukkan judul buku yang akan diupdate: ";
    cin >> judul;
    for (auto& buku : buku_list) {
        if (buku.judul == judul) {
            cout << "Masukkan pengarang baru: ";
            cin >> buku.pengarang;
            cout << "Masukkan penerbit baru: ";
            cin >> buku.penerbit;
            cout << "Masukkan tahun terbit baru: ";
            cin >> buku.tahun_terbit;
            saveBukuData();
            return;
        }
    }
    cout << "Buku tidak ditemukan." << endl;
}

void deleteBuku() {
    string judul;
    cout << "Masukkan judul buku yang akan dihapus: ";
    cin >> judul;
    for (auto it = buku_list.begin(); it != buku_list.end(); ++it) {
        if (it->judul == judul) {
            buku_list.erase(it);
            saveBukuData();
            return;
        }
    }
    cout << "Buku tidak ditemukan." << endl;
}

int main() {
    loadBukuData();
    
    string nama, NIM, jurusan, password;
    cout << "Masukkan Nama: ";
    getline(cin, nama);
    cout << "Masukkan NIM: ";
    getline(cin, NIM);
    cout << "Masukkan Jurusan: ";
    getline(cin, jurusan);
    cout << "Masukkan password: ";
    getline(cin, password);

    if (!login(nama, NIM, jurusan, password)) {
        cout << "Login gagal." << endl;
        return 1;
    }

    int pilihan;
    do {
        cout << "\n1. Tambah Buku\n2. Tampilkan Buku\n3. Update Buku\n4. Hapus Buku\n5. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                createBuku();
                break;
            case 2:
                readBuku();
                break;
            case 3:
                updateBuku();
                break;
            case 4:
                deleteBuku();
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 5);

    return 0;
}
