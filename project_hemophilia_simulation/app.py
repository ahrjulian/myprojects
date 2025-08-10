import os
import subprocess
import re


from functools import wraps
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///hemophilia.db")

#simulation data will later be stored in the hemophilia_data table
db.execute("CREATE TABLE IF NOT EXISTS hemophilia_data (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, year INTEGER, population_size INTEGER NOT NULL, affected INTEGER NOT NULL)")

#this table includes the user information
db.execute("CREATE TABLE IF NOT EXISTS users (user_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL, password TEXT NOT NULL)")

#if the login_required function is called, the user has to be logged in to be able to visit certain html pages
def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function



@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    return render_template("index.html")

@app.route("/hemophilia")
@login_required
def hemophilia():
    return render_template("hemophilia.html")

@app.route("/login", methods = ["GET", "POST"])
def login():

    if request.method == "POST":

        session.clear()

        username = request.form.get("username")

        if not username:
            return render_template("error.html")

        password = request.form.get("password")

        if not password:
            return render_template("error.html")

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        #check if the password already exists in the users database
        if len(rows) != 1 or not check_password_hash(
            rows[0]["password"], request.form.get("password")
        ):
            return render_template("error.html")

        #keep track of which user is logged in
        session["user_id"] = rows[0]["user_id"]

        return redirect("/")
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    session.clear()

    return redirect("/")


@app.route("/simulation", methods = ["GET", "POST"])
@login_required
def simulation():
    if request.method == "POST":
        try:
            output = subprocess.check_output(["./hemophilia"]).decode("utf-8")

            #store simulation output in variables
            individuals_match = re.findall(r"Number of individuals:(\d+)", output)
            males_match = re.findall(r"Number of male hemophilia A patients: (\d+)", output)
            year_match = re.findall(r"year: (\d+)", output)


            if individuals_match and males_match and  len(individuals_match) == len(males_match):
                    for i in range(len(individuals_match)):
                        population_size = int(individuals_match[i])
                        affected = int(males_match[i])
                        year = int(year_match[i])
                        #insert the simulation data into the hemophilia_data table
                        db.execute("INSERT INTO hemophilia_data (population_size, affected, year) VALUES (?,?,?)", population_size, affected, year)


            simulation_data = db.execute("SELECT * FROM hemophilia_data")

            #return the simulation.html template and display the simulation data
            return render_template("simulation.html", output = output, simulation_data = simulation_data)

        except subprocess.CalledProcessError as e:
            output = f"Error running simulation: {e}"

        return render_template("simulation.html", output = output)
    else:
        simulation_data = db.execute("SELECT * FROM hemophilia_data")
        return render_template("simulation.html", simulation_data = simulation_data)

@app.route("/delete_simulation_data", methods = ["POST"])
@login_required
def delete_simulation_data():
    if request.method == "POST":
        db.execute("DELETE FROM hemophilia_data")


        return render_template("simulation.html")


@app.route("/paper", methods = ["GET"])
@login_required
def paper():
    return render_template("paper.html")


@app.route("/registrieren", methods = ["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return render_template("error.html")

        password = request.form.get("password")
        if not password:
            return render_template("error.html")

        if request.form.get("confirm_password") != password:
            return render_template("error.html")

        row = db.execute("SELECT username FROM users WHERE username = ?", username)

        if not row:

            db.execute("INSERT INTO users (username, password) VALUES (?,?)", username, generate_password_hash(password))

            row = db.execute("SELECT user_id FROM users WHERE username = ?", username)

            return redirect("/login")

        else:
            return render_template("error.html")
    else:
        return render_template("registrieren.html")


