import csv
import sqlite3

conn = sqlite3.connect('hemophilia.db')
cursor = conn.cursor

cursor.execute = ("CREATE TABLE hemophilia (population_size INTEGER NOT NULL, affected INTEGER NOT NULL)")

with open('hemophilia.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        curser.execute("INSERT INTO hemophilia (population_size, affected) VALUES (?,?)", row["population_size"], row["affected"])

conn.commit()
conn.close()
