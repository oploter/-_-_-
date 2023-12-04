import mysql.connector
from mysql.connector import errorcode
from db_utils import get_full_contacts, get_main_table

try:
    cnx = mysql.connector.connect(
        user="oploter",
        password="12345",
        host="127.0.0.1",
        database="maiDB"
    )
    if cnx and cnx.is_connected():
        with cnx.cursor() as cur:
            result = cur.execute("select * from name_table")
            rows = cur.fetchall()
            for row in rows:
                print(row)
            res = get_full_contacts(cur)
            print("++++++")
            print(res)
            print("++++++")
            print(get_main_table(cur, "last_name"))
            print("++++")
            print(get_main_table(cur, "name_table"))
            print("++++")
            print(get_main_table(cur, "street"))
            print("++++")
            print(get_main_table(cur, "surname"))
            print("++++")
except mysql.connector.Error as err:
    if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
        print("SMTH wrong user/pass")
    elif err.errno == errorcode.ER_BAD_DB_ERROR:
        print("DB does not exist")
    else:
        print(err)
else:
    cnx.close()
    
    
    

'''
    name_frame = ttk.Frame(
        master=window)
    name_frame.grid(row=0, column=0, padx=5, pady=5)
    selected_name = tk.StringVar()
    name_combo = ttk.Combobox(window, master=name_frame, textvariable=selected_name)
    name_combo['state'] = 'readonly'
    name_combo.pack()
    
    surname_frame = ttk.Frame(
        master=window)
    surname_frame.grid(row=0, column=1, padx=5, pady=5)
    selected_surname = tk.StringVar()
    surname_combo = ttk.Combobox(window, master=surname_frame, textvariable=selected_surname)
    surname_combo['state'] = 'readonly'
    surname_combo.pack()
 '''
 
 
'''
    table_frame = ttk.Frame(master=window)
    columns = ("#1", "#2", "#3", "#4", "#5", "#6", "#7", "#8", "#9")
    table = ttk.Treeview(master=window, show="headings", columns=columns)
    table.heading("#1", text="id")
    table.heading("#2", text="Имя")
    table.heading("#3", text="Фамилия")
    table.heading("#4", text="Отчество")
    table.heading("#5", text="Улица")
    table.heading("#6", text="Дом")
    table.heading("#7", text="Корпус")
    table.heading("#8", text="Квартира")
    table.heading("#9", text="Телефон")
    
    for row in db.get_full_contacts():
        print("row: ", row)
        table.insert("", tk.END, values=row)
    #table.bind("<<TreeviewSelect>>", print_selection)
    table.grid(row=1, column=0)
'''
 
 
 # mysql -u oploter -p
 # use maiDB