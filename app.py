import tkinter as tk
import tkinter.ttk as ttk
from db_utils import DBUtil
import mysql.connector
from mysql.connector import errorcode

class App:
    
    def __init__(self):
        self.db = DBUtil()
        
        self.window = tk.Tk()
        
        self.name_frame = ttk.Frame(master=self.window)
        self.name_frame.grid(row=0, column=0, padx=5, pady=5)
        self.name_combo = ttk.Combobox(self.name_frame,
        values=[""] + self.db.get_values_from_main_table("name_table"))
        self.name_combo['state'] = 'readonly'
        name_label = tk.Label(self.name_frame, text="Имя")
        name_label.pack()
        more_name_button = tk.Button(self.name_frame,
                            text="...",
                            width=2,
                            height=1,
                            command=lambda: SecondaryWindow("name_table", self.db))
        more_name_button.pack(side=tk.RIGHT)
        self.name_combo.pack()
        
        self.surname_frame = ttk.Frame(master=self.window)
        self.surname_frame.grid(row=0, column=1, padx=5, pady=5)
        self.surname_combo = ttk.Combobox(self.surname_frame,
        values=[""] + self.db.get_values_from_main_table("surname"))
        self.surname_combo['state'] = 'readonly'
        surname_label = tk.Label(self.surname_frame, text="Отчество")
        surname_label.pack()
        more_surname_button = tk.Button(self.surname_frame,
                            text="...",
                            width=2,
                            height=1,
                            command=lambda: SecondaryWindow("surname", self.db))
        more_surname_button.pack(side=tk.RIGHT)
        self.surname_combo.pack()
        
        self.last_name_frame = ttk.Frame(master=self.window)
        self.last_name_frame.grid(row=0, column=2, padx=5, pady=5)
        self.last_name_combo = ttk.Combobox(self.last_name_frame,
        values=[""] + self.db.get_values_from_main_table("last_name"))
        self.last_name_combo['state'] = 'readonly'
        last_name_label = tk.Label(self.last_name_frame, text="Фамилия")
        last_name_label.pack()
        more_last_name_button = tk.Button(self.last_name_frame,
                            text="...",
                            width=2,
                            height=1,
                            command=lambda: SecondaryWindow("last_name", self.db))
        more_last_name_button.pack(side=tk.RIGHT)
        self.last_name_combo.pack()
        
        self.street_frame = ttk.Frame(master=self.window)
        self.street_frame.grid(row=0, column=3, padx=5, pady=5)
        self.street_combo = ttk.Combobox(self.street_frame,
        values=[""] + self.db.get_values_from_main_table("street"))
        self.street_combo['state'] = 'readonly'
        street_label = tk.Label(self.street_frame, text="Улица")
        street_label.pack()
        more_street_button = tk.Button(self.street_frame,
                            text="...",
                            width=2,
                            height=1,
                            command=lambda: SecondaryWindow("street", self.db))
        more_street_button.pack(side=tk.RIGHT)
        self.street_combo.pack()
        
        self.building_frame = ttk.Frame(master=self.window)
        self.building_frame.grid(row=1, column=0)
        building_label = tk.Label(self.building_frame, text="Дом")
        building_label.pack()
        self.building_inp = ttk.Entry(self.building_frame)
        self.building_inp.pack(padx=5, pady=5)
        
        self.building_k_frame = ttk.Frame(master=self.window)
        self.building_k_frame.grid(row=1, column=1)
        building_k_label = tk.Label(self.building_k_frame, text="Корпус")
        building_k_label.pack()
        self.building_k_inp = ttk.Entry(self.building_k_frame)
        self.building_k_inp.pack(padx=5, pady=5)
        
        self.apartment_frame = ttk.Frame(master=self.window)
        self.apartment_frame.grid(row=1, column=2)
        apartment_label = tk.Label(self.apartment_frame, text="Квартира")
        apartment_label.pack()
        self.apartment_inp = ttk.Entry(self.apartment_frame)
        self.apartment_inp.pack(padx=5, pady=5)
        
        self.phone_frame = ttk.Frame(master=self.window)
        self.phone_frame.grid(row=1, column=3)
        phone_label = tk.Label(self.phone_frame, text="Телефон")
        phone_label.pack()
        self.phone_inp = ttk.Entry(self.phone_frame)
        self.phone_inp.pack(padx=5, pady=5)
        
        self.search_btn = ttk.Button(self.window, command=self.search, text="Поиск")
        self.search_btn.grid(row=2, column=0, padx=5, pady=5)
        self.insert_btn = ttk.Button(self.window, command=self.insert, text="Добавить")
        self.insert_btn.grid(row=2, column=1, padx=5, pady=5)
        self.drop_btn = ttk.Button(self.window, command=self.delete, text="Удалить")
        self.drop_btn.grid(row=2, column=2, padx=5, pady=5)
        self.update_btn = ttk.Button(self.window, command=self.update, text="Изменить")
        self.update_btn.grid(row=2, column=3, padx=5, pady=5)
        
        columns = ("#1", "#2", "#3", "#4", "#5", "#6", "#7", "#8", "#9")
        self.table = ttk.Treeview(master=self.window, show="headings", columns=columns)
        self.table.heading("#1", text="id")
        self.table.column("#1", minwidth=0, width=40)
        self.table.heading("#2", text="Имя")
        self.table.heading("#3", text="Отчество")
        self.table.heading("#4", text="Фамилия")
        self.table.heading("#5", text="Улица")
        self.table.heading("#6", text="Дом")
        self.table.column("#6", minwidth=0, width=100)
        self.table.heading("#7", text="Корпус")
        self.table.column("#7", minwidth=0, width=100)
        self.table.heading("#8", text="Квартира")
        self.table.column("#8", minwidth=0, width=100)
        self.table.heading("#9", text="Телефон")
        
        self.set_table_rows(self.db.get_full_contacts())    
        #table.bind("<<TreeviewSelect>>", print_selection)
        self.table.grid(row=3, column=0, columnspan=5, padx=5, pady=5)
        #self.table.tag_bind('cb', '<1>', self.cb)    
            
        self.window.mainloop()
    
    def open_secondary_window(self, table_name):
        SecondaryWindow(table_name, self.db)
        if table_name == "name_table":
            
        elif table_name == "surname":
            pass
        elif table_name == "last_name":
            pass
        elif table_name == "street":
            
        
        
    def set_table_rows(self, rows = None):
        if rows is None:
            rows = self.db.get_full_contacts()
        self.table.delete(*self.table.get_children())
        for row in rows:
            self.table.insert("", tk.END, values=row, tags=('cb'))
    
    def search(self):
        search_args = {}
        if self.name_combo.get() != "":
            search_args["name"] = self.name_combo.get()
        if self.last_name_combo.get() != "":
            search_args["last_name"] = self.last_name_combo.get()
        if self.surname_combo.get() != "":
            search_args["surname"] = self.surname_combo.get()
        if self.street_combo.get() != "":
            search_args["street"] = self.street_combo.get()
        if self.building_inp.get() != "":
            search_args["bldn"] = self.building_inp.get()
        if self.building_k_inp.get() != "":
            search_args["bldn_k"] = self.building_k_inp.get()
        if self.apartment_inp.get() != "":
            search_args["apartment"] = self.apartment_inp.get()
        if self.phone_inp.get() != "":
            search_args["phone"] = self.phone_inp.get()
        print(search_args)
    
        self.set_table_rows(self.db.search_phonebook(**search_args))
        #if()
        #return self.db.search_phonebook

    def insert(self):
        search_args = {}
        if self.name_combo.get() != "":
            search_args["name"] = self.name_combo.get()
        if self.last_name_combo.get() != "":
            search_args["last_name"] = self.last_name_combo.get()
        if self.surname_combo.get() != "":
            search_args["surname"] = self.surname_combo.get()
        if self.street_combo.get() != "":
            search_args["street"] = self.street_combo.get()
        if self.building_inp.get() != "":
            search_args["bldn"] = self.building_inp.get()
        if self.building_k_inp.get() != "":
            search_args["bldn_k"] = self.building_k_inp.get()
        if self.apartment_inp.get() != "":
            search_args["apartment"] = self.apartment_inp.get()
        if self.phone_inp.get() != "":
            search_args["phone"] = self.phone_inp.get()
        print("insert: ", search_args)
    
        self.db.insert_into_phonebook(**search_args)
        self.set_table_rows()
        
    def update(self):
        row_id = self.table.item(self.table.focus())['values'][0]
        simple_params_to_upd = {}
        foreign_params_to_upd = {}
        
        if self.name_combo.get() != "":
            foreign_params_to_upd["name"] = ("name_table", self.name_combo.get())
        if self.last_name_combo.get() != "":
            foreign_params_to_upd["last_name"] = ("last_name", self.last_name_combo.get())
        if self.surname_combo.get() != "":
            foreign_params_to_upd["surname"] = ("surname", self.surname_combo.get())
        if self.street_combo.get() != "":
            foreign_params_to_upd["street"] = ("street", self.street_combo.get())
        if self.building_inp.get() != "":
            simple_params_to_upd["bldn"] = self.building_inp.get()
        if self.building_k_inp.get() != "":
            simple_params_to_upd["bldn_k"] = self.building_k_inp.get()
        if self.apartment_inp.get() != "":
            simple_params_to_upd["aprt"] = self.apartment_inp.get()
        if self.phone_inp.get() != "":
            simple_params_to_upd["phone"] = self.phone_inp.get()
        self.db.update_phonebook(row_id, simple_params_to_upd, foreign_params_to_upd)
        self.set_table_rows()
    
    def delete(self):
        row_id = self.table.item(self.table.focus())['values'][0]
        print("TO DELETE: ", row_id)
        self.db.delete_from_child(row_id)
        self.set_table_rows()
        
secondary_window_params = {
    "name_table" : ("Имя"),
    "surname" : ("Отчество"),
    "last_name" : ("Фамилия"),
    "street" : ("Улица")
}
    
class SecondaryWindow:
    def  __init__(self, table_name, db):
        self.table_name = table_name
        self.db = db
        self.window = tk.Toplevel()
        columns = ("#1", "#2")
        self.table = ttk.Treeview(master=self.window, show="headings", columns=columns)
        self.table.heading("#1", text="id")
        self.table.column("#1", minwidth=2, width=40)
        self.table.heading("#2", text=secondary_window_params[table_name])
        self.set_table_rows()
        self.table.grid(row=0, column=0, rowspan=5, padx=5, pady=5)
        
        self.inp = ttk.Entry(self.window)
        self.inp.grid(row=0, column=2, padx=5, pady=5)
        
        self.search_btn = ttk.Button(self.window, command=self.search, text="Поиск")
        self.search_btn.grid(row=1, column=2, padx=5, pady=5)
        self.insert_btn = ttk.Button(self.window, command=self.insert, text="Добавить")
        self.insert_btn.grid(row=2, column=2, padx=5, pady=5)
        self.drop_btn = ttk.Button(self.window, command=self.delete, text="Удалить")
        self.drop_btn.grid(row=3, column=2, padx=5, pady=5)
        self.update_btn = ttk.Button(self.window, command=self.update, text="Изменить")
        self.update_btn.grid(row=4, column=2, padx=5, pady=5)
    
    def set_table_rows(self, rows=None):
        if rows is None:
            rows = self.db.get_main_table(self.table_name)
        self.table.delete(*self.table.get_children())
        for row in rows:
            self.table.insert("", tk.END, values=row, tags=('cb'))
    
        
    def delete(self):
        row_id = self.table.item(self.table.focus())['values'][0]
        self.db.delete_from_main_table(self.table_name, row_id)
        self.set_table_rows()
        
    def update(self):
        row_id = self.table.item(self.table.focus())['values'][0]
        new_val = self.inp.get()
        print("new val:", new_val)
        self.db.update_main_table(self.table_name, row_id, new_val)
        self.set_table_rows()
        
    def insert(self):
        self.db.insert_into_main_table(self.table_name, self.inp.get())
        self.set_table_rows()
    
    def search(self):
        self.set_table_rows(self.db.search_main_table(self.table_name, self.inp.get()))
        
    
if __name__ == "__main__":
    App()