import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


db.execute("CREATE TABLE IF NOT EXISTS ownedstocks (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, stock TEXT NOT NULL, numbershares INTEGER NOT NULL, costs REAL NOT NULL, cost_per_share REAL NOT NULL, FOREIGN KEY(user_id) REFERENCES users(id))")
db.execute("CREATE TABLE IF NOT EXISTS total_cash (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, total REAL NOT NULL)")
#db.execute("DROP TABLE history")
db.execute("CREATE TABLE IF NOT EXISTS history (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, action TEXT NOT NULL, stock TEXT NOT NULL, balance REAL NOT NULL, date DATETIME)")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    #db.execute("CREATE TABLE IF NOT EXISTS ownedstocks (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, stock TEXT NOT NULL, numbershares INTEGER NOT NULL, costs INTEGER NOT NULL, FOREIGN ))
    id = session["user_id"]
    id = int(id)
    cash_updated = db.execute("SELECT * FROM ownedstocks WHERE user_id = ?", id)

    row = db.execute("SELECT cash FROM users WHERE id = ?", id)
    cash = row[0]["cash"]
    cash = usd(cash)

    #total_ = db.execute("SELECT total FROM total_cash WHERE user_id = ?", id)
    #total = total_[0]["total"]



    return render_template("index.html", cash_updated = cash_updated, cash = cash)

@app.route("/addcash", methods = ["GET", "POST"])
@login_required
def addcash():
    if request.method == "POST":
        cash_amount = request.form.get("addcash")
        if not cash_amount:
            return apology("must provide cash amount", 400)

        if not cash_amount.isnumeric():
            return apology("invalid", 400)

        cash_amount = int(cash_amount)

        if cash_amount <= 0:
            return apology("invalid", 400)

        #cash_amount = usd(cash_amount)

        id = session["user_id"]

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", cash_amount, id)


        cash_updated = db.execute("SELECT * FROM ownedstocks WHERE user_id = ?", id)


        for row in cash_updated:
            row["costs"] = usd(row["costs"])
            row["cost_per_share"] = usd(row["cost_per_share"])




        baz = db.execute("SELECT cash FROM users WHERE id = ?", id)
        cash = int(baz[0]["cash"])


        diz = db.execute("SELECT SUM(costs) AS total_cash FROM ownedstocks WHERE user_id = ?", id)
        sum_cash_total = float(diz[0]["total_cash"])

        sum_cost = cash + sum_cash_total

        sum_cost = usd(sum_cost)
        cash = usd(cash)

        #second_row = db.execute("SELECT total FROM total_cash WHERE user_id = ?", id)
        #sum_cost = float(second_row[0]["total"])
        #sum_cost = usd(sum_cost)

        return render_template("index.html", cash_updated = cash_updated, cash = cash, sum_cost = sum_cost)
    else:
        return render_template("addcash.html")



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        number_of_shares = request.form.get("shares")

        if not number_of_shares.isnumeric():
            return apology("invalid number of shares", 400)

        #convert into an int
        number_of_shares = int(number_of_shares)

        #check for errors
        if not request.form.get("symbol"):
            return apology("please provide a stock symbol", 400)

        if not request.form.get("shares"):
            return apology("please provide number of shares", 400)

        if number_of_shares < 1:
            return apology("invalid number of shares", 400)

        #if type(number_of_shares) in (float):
            #return apology("input has to be a hole number!", 400)

        #stock symbol has to be valid
        data = lookup(symbol)
        if data is None:
            return apology("stock symbol does not exist", 400)
        else:
            stock_price = data["price"]
            #db.execute("INSERT INTO ownedstocks(cost_per_share) VALUES (?)", stock_price)
            id = session["user_id"]
            id = int(id)

            cash_result = db.execute("SELECT cash FROM users WHERE id = ?", id)
            cash = cash_result[0]["cash"]


            if cash >= (number_of_shares * stock_price):
                #purchase stock
                #update cash of user in users
                cash = cash - (number_of_shares * stock_price)
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, id)
                #cash = usd(cash)
                #keep track of the stocks each user owns
                cost = (number_of_shares* stock_price)

                #balance
                cost_balance = -(cost)
                cost_balance = usd(cost_balance)

                #transaction type
                buy = "buy"

                db.execute("INSERT INTO history (action, stock, balance, user_id, date) VALUES (?,?,?,?, datetime('now'))", buy , symbol, cost_balance, id)
                #cost = usd(cost)

                #stock_price = usd(stock_price)



                #price_per_share = stock_price["price"]
                #price_per_share = float(price_per_share)
                row = db.execute("SELECT * FROM ownedstocks WHERE user_id = ? AND stock = ?", id, symbol)
                if row:
                    db.execute("UPDATE ownedstocks SET numbershares = numbershares + ?, costs = costs + ?, cost_per_share = ? WHERE stock = ? AND user_id = ?", number_of_shares, cost, stock_price, symbol, id)
                else:
                    db.execute("INSERT INTO ownedstocks (user_id, stock, numbershares, costs, cost_per_share) VALUES(?,?,?,?,?)", id, symbol, number_of_shares, cost, stock_price)
                #return apology("valid", 403)
                cash_updated = db.execute("SELECT * FROM ownedstocks WHERE user_id = ?", id)

                #total_price = 0

                #for second_row in cash_updated:
                    #total_price = total_price + int(second_row["costs"])

                #second_cash = db.execute("SELECT cash FROM users WHERE id = ?", id)
                #total_cash = int(second_cash[0]["cash"])

                #total = total_cash + total_price

                #exist = db.execute("SELECT * FROM total_cash WHERE user_id = ?", id)
                #if exist:
                    #db.execute("UPDATE total_cash SET total = ? WHERE user_id = ?", total, id)
                #else:
                    #db.execute("INSERT INTO total_cash (user_id, total) VALUES(?,?)", id, total)

                for row in cash_updated:
                    row["costs"] = usd(row["costs"])
                    row["cost_per_share"] = usd(row["cost_per_share"])

                #total_price = 0

                #for second_row in cash_updated:

                    #total_price = total_price + int(second_row["costs"])

                #second_cash = db.execute("SELECT cash FROM users WHERE id = ?", id)
                #total_cash = second_cash[0]["cash"]

                #total = total_cash + total_price

                #exist = db.execute("SELECT * FROM total_cash WHERE user_id = ?", id)

                #if exist:
                    #db.execute("UPDATE total_cash SET total = ? WHERE user_id = ?", total, id)
                #else:
                    #db.execute("INSERT INTO total_cash (user_id, total) VALUES (?,?)", id, total)

                #cash_updaed = usd(cash_updated)
                #add cash with price of stocks to calculate the total balance
                row = db.execute("SELECT SUM(costs) AS total_cost FROM ownedstocks WHERE user_id = ?", id)
                sum_stock_cost = float(row[0]["total_cost"])

                sum_cost = cash + sum_stock_cost

                db.execute("UPDATE total_cash SET total = ? WHERE user_id = ?", sum_cost, id)

                sum_cost = usd(sum_cost)


                cash = usd(cash)


                return render_template("index.html", cash_updated = cash_updated, cash = cash, cost = cost, sum_cost = sum_cost)
                #return redirect("/")
            else:
                return apology("you don't have enough cash for this purchase", 403)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    id = session["user_id"]
    cash_updated = db.execute("SELECT * FROM history WHERE user_id = ?", id)
    return render_template("history.html", cash_updated = cash_updated)
    #if request.method == "POST":
        #cash_updated = db.execute("SELECT * FROM history WHERE user_id = ?", id)
        #return render_template("history.html", cash_updated = cash_updated)
    #else:
        #return render_template("history.html")

@app.route("/return_main_page", methods = ["POST"])
@login_required
def return_main_page():
    if request.method == "POST":
        id = session["user_id"]
        cash_updated = db.execute("SELECT * FROM ownedstocks WHERE id = ?", id)
        return render_template("index.html", cash_updated = cash_updated)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        stock_symbol = request.form.get("symbol")

        if not request.form.get("symbol"):
            return apology("must provide stock quote", 400)

        data = lookup(stock_symbol)

        if not data:
            return apology("stock symbol does not exist", 400)

        name = data["name"]
        price = data["price"]
        price = usd(price)
        symbol = data["symbol"]
        return render_template("information.html", name = name, price = price, symbol = symbol)

    else:
        return render_template("quote.html")




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        #return apoplogy("TODO")
        if not request.form.get("username"):
            return apology("must provide username", 400)

        if not request.form.get("password"):
            return apology("must provide password", 400)

        username = request.form.get("username")
        if not username:
            return redirect("/")
        username_valid = db.execute("SELECT username FROM users WHERE username = ?", username)

        if not username_valid:



            password = request.form.get("password")
            if not password:
                return redirect("/")

            confirmation = request.form.get("confirmation")

            if password != confirmation:
                return apology("passwords don't match")

        #check if registred name already exist in the data base

            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(request.form.get("password")))

        #figure out users id
            session["user_id"] = db.execute("SELECT id FROM users WHERE username = ?", username)

            return redirect("/login")
        else:
            return apology("username already exists", 400)

    else:
        return render_template("register.html")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        sell_symbol = request.form.get("symbol")
        if not sell_symbol:
            return apology("must provide symbol", 400)

        number_shares = request.form.get("shares")
        if not number_shares:
            return apology("must provide number of shares", 400)

        number_shares = int(number_shares)

        if number_shares < 0:
            return apology("can't sell negative number of shares", 400)

        id = session["user_id"]

        first_row = db.execute("SELECT numbershares FROM ownedstocks WHERE stock = ? AND user_id = ?", sell_symbol, id)
        if first_row:
            number = int(first_row[0]["numbershares"])
            #db.execute("SELECT stock FROM ownedstocks WHERE numbershares = ? AND id = ? ", number, id)
        #else:
            #return apology("stock not found", 400)

        #number_shares = int(number_shares)

            new_number = number - number_shares
            if new_number < 0:
            #user does not have enough shares of this stock
                return apology("you don't have enough shares in your portfolio", 400)
            else:
                #db.execute("UPDATE ownedstocks SET numbershares = ? WHERE stock = ?", new_number, sell_symbol)

        #id = session["user_id"]

                cash_updated = db.execute("SELECT costs FROM ownedstocks WHERE user_id = ? AND stock = ?", id, sell_symbol)
                cost = cash_updated[0]["costs"]
                cost = int(cost)

                data = lookup(sell_symbol)
                price = data["price"]


                new_cost = cost - (price * number_shares)

                cost_balance = + (price * number_shares)
                cost_balance = usd(cost_balance)

                #transaction type
                sell = "sell"

                db.execute("INSERT INTO history (action, stock, balance, user_id, date) VALUES (?,?,?,?, datetime('now'))", sell, sell_symbol, cost_balance, id)

                db.execute("UPDATE ownedstocks SET numbershares = ?, costs = ?, cost_per_share = ? WHERE stock = ? AND user_id = ?",new_number, new_cost, price,  sell_symbol, id)

            row = db.execute("SELECT cash FROM users WHERE id = ?", id)
            if row:
                cash = row[0]["cash"]
            else:
                return apology("invalid", 400)


            cash_updated = db.execute("SELECT * FROM ownedstocks WHERE user_id = ?", id)

            #total_price = 0
            #for second_row in cash_updated:
                #total_price = total_price + int(second_row["costs"])

            #second_cash = db.execute("SELECT cash FROM users WHERE id = ?", id)
            #total_cash = int(second_cash[0]["cash"])

            #total = total_cash + total_price

            #exist = db.execute("SELECT * FROM total_cash WHERE user_id = ?", id)
            #if exist:
                #db.execute("UPDATE total_cash SET total = ? WHERE user_id = ?", total, id)
            #else:
                #db.execute("INSERT INTO total_cash (user_id, total) VALUES (?,?)", id, total)

            for row in cash_updated:
                row["cost_per_share"] = usd(row["cost_per_share"])
                row["costs"] = usd(row["costs"])

            cash = cash + (price * number_shares)

            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, id)

            row = db.execute("SELECT SUM(costs) AS total_cost FROM ownedstocks WHERE user_id = ? ", id)
            sum_stock_cost = float(row[0]["total_cost"])


            sum_cost = cash + sum_stock_cost

            db.execute("UPDATE total_cash SET total = ? WHERE user_id = ?", sum_cost, id)
            sum_cost = usd(sum_cost)

            cash = usd(cash)

            return render_template("index.html", cash_updated = cash_updated, cash = cash, new_cost = new_cost, sum_cost = sum_cost)
            #return redirect("/")
    else:
        id = session["user_id"]
        cash_updated = db.execute("SELECT * FROM ownedstocks WHERE user_id = ?", id)
        return render_template("sell.html", cash_updated = cash_updated)




