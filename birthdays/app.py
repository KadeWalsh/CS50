import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

    # check for blank fields from POST request
        if not name or not month or not day:
    #   if any blank field found, redirect back to home
            return redirect("/")
    # if no blank field found
        else:
            # insert data into table
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
            # redirect back to home
            return redirect("/")


    else:

        birthdays = db.execute("SELECT * FROM birthdays ORDER BY month ASC, day ASC, name ASC")

        return render_template("index.html", birthdays=birthdays)
        # return render_template("index.html")

@app.route("/remove/", methods=["POST"])
def removeBirthday():
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")