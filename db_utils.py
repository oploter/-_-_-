import mysql.connector
from mysql.connector import errorcode

class DBUtil:
    def __init__(self):
        try:
            self.cnx = mysql.connector.connect(
                user="oploter",
                password="12345",
                host="127.0.0.1",
                database="maiDB"
            )
            if self.cnx and self.cnx.is_connected():
                self.cur = self.cnx.cursor()
        except mysql.connector.Error as err:
            if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
                print("SMTH wrong user/pass")
            elif err.errno == errorcode.ER_BAD_DB_ERROR:
                print("DB does not exist")
            else:
                print(err)
    
    def __del__(self):
        print("Closing db")
        self.cnx.close()
                
    def get_full_contacts(self):
        self.cur.execute("""
            SELECT p.id, nt.val, snt.val, lnt.val, st.val, p.bldn, p.bldn_k, p.aprt, p.phone
            FROM phonebook as p
            JOIN last_name as lnt
            ON lnt.id = p.last_name
            JOIN name_table as nt
            ON nt.id = p.name
            JOIN surname as snt
            ON snt.id = p.surname
            JOIN street as st
            ON st.id = p.street
        """)
        return self.cur.fetchall()
        
    def get_main_table(self, table_name):
        self.cur.execute(f"""
            SELECT * FROM {table_name}
        """)
        return self.cur.fetchall()
    
    def search_main_table(self, table_name, val):
        self.cur.execute(f"SELECT * FROM {table_name} WHERE val='{val}'")
        return self.cur.fetchall()
        
    def delete_from_main_table(self, table_name, row_id):
        self.cur.execute(f"DELETE FROM {table_name} WHERE id='{row_id}'")
        self.cnx.commit()
        
    def insert_into_main_table(self, table_name, val):
        self.cur.execute(f"INSERT INTO {table_name}(val) VALUES ('{val}')")
        self.cnx.commit()
    
    def update_main_table(self, table_name, row_id, new_val):
        self.cur.execute(f"UPDATE {table_name} SET val='{new_val}' WHERE id='{row_id}'")
        self.cnx.commit()
            
    def get_values_from_main_table(self, table_name):
        self.cur.execute(f"""
            SELECT val FROM {table_name}
        """)
        return self.cur.fetchall()
        
    def search_phonebook(self, name=None,
                        surname=None,
                        last_name=None,
                        street=None,
                        bldn=None,
                        bldn_k=None,
                        apartment=None,
                        phone=None):
        query = f"""
            SELECT p.id, nt.val, snt.val, lnt.val, st.val, p.bldn, p.bldn_k, p.aprt, p.phone
            FROM phonebook as p
            JOIN last_name as lnt
            ON lnt.id = p.last_name
            JOIN name_table as nt
            ON nt.id = p.name
            JOIN surname as snt
            ON snt.id = p.surname
            JOIN street as st
            ON st.id = p.street
            WHERE TRUE
        """
        if name is not None:
            query += f"""
                AND nt.val='{name}'
            """
        if surname is not None:
            query += f"""
                AND snt.val='{surname}'
            """
        if last_name is not None:
            query += f"""
                AND lnt.val='{last_name}'
            """
        if street is not None:
            query += f"""
                AND st.val='{street}'
            """
        if bldn is not None:
            query += f"""
                AND p.bldn='{bldn}'
            """
        if bldn_k is not None:
            query += f"""
                AND p.bldn_k='{bldn_k}'
            """
        if apartment is not None:
            query += f"""
                AND p.aprt='{apartment}'
            """
        if phone is not None:
            query += f"""
                AND p.phone='{phone}'
            """
        self.cur.execute(query)
        return self.cur.fetchall()
        
    def insert_into_phonebook(self, name=None,
                        surname=None,
                        last_name=None,
                        street=None,
                        bldn=None,
                        bldn_k=None,
                        apartment=None,
                        phone=None):
        query = f"""
            INSERT INTO phonebook(name, surname, last_name, street, bldn, bldn_k, aprt, phone)
            VALUES(
            (SELECT n.id FROM name_table as n WHERE n.val='{name}'),
            (SELECT s.id FROM surname as s WHERE s.val='{surname}'),
            (SELECT ln.id FROM last_name as ln WHERE ln.val='{last_name}'),
            (SELECT street.id FROM street WHERE street.val='{street}'),
            '{bldn}', '{bldn_k}', '{apartment}', '{phone}'
            )"""
        print("query:", query)
        self.cur.execute(query)
        self.cnx.commit()
        print("query executed\n")
    
    def delete_from_child(self, row_id):
        self.cur.execute(f"""
            DELETE FROM phonebook
            WHERE id='{row_id}'
        """)
    
    def update_phonebook(self, row_id, simple_params_to_upd, foreign_params_to_upd):
        query = f"""
            UPDATE phonebook as p
            SET
        """
        for param in simple_params_to_upd:
            query += f"{param}='{simple_params_to_upd[param]}',"
        for param in foreign_params_to_upd:
            val = foreign_params_to_upd[param]
            query += f"{param}=(SELECT t.id FROM {val[0]} as t WHERE t.val='{val[1]}'),"
        query = query[:-1]
        query += f"""WHERE id='{row_id}'"""
        print("UPDATE QUERY: ", query)
        self.cur.execute(query)
        self.cnx.commit()
        print("UPDATE SUCCESFULL")