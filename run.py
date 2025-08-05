import tkinter as tk
from tkinter import ttk, messagebox
import os

DB_NAME = "db_stock.txt"

def baca_data():
    if not os.path.exists(DB_NAME):
        return []
    with open(DB_NAME, "r") as file:
        return file.readlines()[3:]

def simpan_data(baris):
    with open(DB_NAME, "a") as file:
        file.write(baris + "\n")

def tulis_ulang(data_list):
    with open(DB_NAME, "w") as file:
        file.writelines(data_list)

def tampilkan_data():
    for item in tree.get_children():
        tree.delete(item)
    for line in baca_data():
        parts = [p.strip() for p in line.strip().split('|') if p]
        if len(parts) == 6:
            tree.insert('', tk.END, values=parts)

def tambah_barang():
    values = [e.get() for e in entries]
    if any(v == "" for v in values):
        messagebox.showwarning("Peringatan", "Semua field harus diisi!")
        return
    # Cek duplikasi nama
    for line in baca_data():
        if values[2] in line:
            messagebox.showerror("Gagal", "Barang dengan nama tersebut sudah ada.")
            return
    baris = "| {:<10} | {:<10} | {:<20} | {:<10} | {:<10} | {:<10} |".format(*values)
    simpan_data(baris)
    tampilkan_data()
    for e in entries:
        e.delete(0, tk.END)

def cari_barang():
    keyword = entries[2].get()
    for item in tree.get_children():
        tree.delete(item)
    found = False
    for line in baca_data():
        if keyword.lower() in line.lower():
            parts = [p.strip() for p in line.strip().split('|') if p]
            tree.insert('', tk.END, values=parts)
            found = True
    if not found:
        messagebox.showinfo("Hasil", f"Barang dengan nama '{keyword}' tidak ditemukan.")

def hapus_barang():
    keyword = entries[2].get()
    data = baca_data()
    new_data = []
    found = False
    for line in data:
        if keyword.lower() not in line.lower():
            new_data.append(line)
        else:
            found = True
    if found:
        tulis_ulang(new_data)
        tampilkan_data()
        messagebox.showinfo("Sukses", f"Barang '{keyword}' berhasil dihapus.")
    else:
        messagebox.showwarning("Gagal", "Barang tidak ditemukan.")

def edit_barang():
    keyword = entries[2].get()
    data = baca_data()
    new_data = []
    found = False
    for line in data:
        if keyword.lower() in line.lower():
            new_line = "| {:<10} | {:<10} | {:<20} | {:<10} | {:<10} | {:<10} |\n".format(
                *[e.get() for e in entries]
            )
            new_data.append(new_line)
            found = True
        else:
            new_data.append(line)
    if found:
        tulis_ulang(new_data)
        tampilkan_data()
        messagebox.showinfo("Sukses", f"Data barang '{keyword}' berhasil diperbarui.")
    else:
        messagebox.showwarning("Gagal", "Barang tidak ditemukan.")

# =============== GUI ===================

root = tk.Tk()
root.title("Sistem Manajemen Inventaris")
root.geometry("900x500")

labels = ["Kategori", "Merek", "Nama Barang", "ID", "Jumlah", "Harga"]
entries = []

form_frame = tk.Frame(root)
form_frame.pack(pady=10)

for i, label in enumerate(labels):
    tk.Label(form_frame, text=label).grid(row=0, column=i)
    ent = tk.Entry(form_frame)
    ent.grid(row=1, column=i, padx=5)
    entries.append(ent)

btn_frame = tk.Frame(root)
btn_frame.pack(pady=10)

tk.Button(btn_frame, text="Tambah", command=tambah_barang, width=10).grid(row=0, column=0, padx=5)
tk.Button(btn_frame, text="Cari", command=cari_barang, width=10).grid(row=0, column=1, padx=5)
tk.Button(btn_frame, text="Edit", command=edit_barang, width=10).grid(row=0, column=2, padx=5)
tk.Button(btn_frame, text="Hapus", command=hapus_barang, width=10).grid(row=0, column=3, padx=5)
tk.Button(btn_frame, text="Tampilkan Semua", command=tampilkan_data, width=15).grid(row=0, column=4, padx=5)

tree_frame = tk.Frame(root)
tree_frame.pack(pady=10, fill="x")

tree = ttk.Treeview(tree_frame, columns=labels, show="headings")
for col in labels:
    tree.heading(col, text=col)
    tree.column(col, width=130, anchor="center")
tree.pack(fill="x")

tampilkan_data()
root.mainloop()
