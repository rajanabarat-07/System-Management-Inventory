# 📦 System Management Inventory (C Language)

Aplikasi berbasis terminal untuk mengelola data inventaris barang, ditulis menggunakan bahasa pemrograman C. Data disimpan secara lokal dalam file teks (`db_stock.txt`), sehingga ringan dan portabel.

## 🧠 Fitur Utama

- 📋 Menampilkan daftar barang dari file `db_stock.txt`
- ➕ Menambahkan barang baru ke inventaris
- ❌ Menghapus barang berdasarkan nama
- 📝 Mengedit detail barang
- 🔍 Mencari barang berdasarkan nama atau ID

## 📂 Struktur Data

Semua data barang disimpan dalam format teks seperti berikut:

```
| Kategori   | Merek     | Nama Barang         | ID Barang | Jumlah Barang | Harga Barang |
```

Contoh:
```
| Elektronik | Samsung   | TV LED 32 Inch      | TV001     | 10            | 3000000       |
```

## ▶️ Cara Menjalankan

1. **Pastikan kamu sudah menginstal compiler C** (contoh: GCC).
2. **Compile program:**

   ```bash
   gcc -o inventory main.c
   ```

3. **Jalankan program:**

   ```bash
   ./inventory
   ```

4. File `db_stock.txt` akan dibuat secara otomatis jika belum ada.

## 🛠️ Navigasi Menu

```
1. Tambahkan barang
2. Hapus barang
3. Perbarui data barang
4. Cari barang
5. Keluar
```

## ⚠️ Catatan Teknis

- Program ini berjalan sepenuhnya di CLI (Command Line Interface).
- File `db_stock.txt` berfungsi sebagai database lokal.
- Tidak mendukung multiuser atau transaksi paralel (belum cocok untuk skala besar).

## 📄 Lisensi

Lisensi penggunaan telah disediakan dalam file terpisah (PDF).
