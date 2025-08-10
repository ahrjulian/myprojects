# Hemophilia A Simulation for Germany

#### Description:
For my final project I decided to build a program which simulates the future number of hemophilia A cases in Germany over a 40 year period. Additionaly, I created a webapp via Flask on which users can learn more about hemophilia and take a deeper look at the simulation data. The simulation was written in C and models demographics, genetic inheritance, and disease prevelance. My final project was inspired by a scientific paper that I wrote during a school project. In this paper I discussed and designed a hyphothetical simulation model that could determine the heredity of a genetic disease.

## Project Goals
- after I did a lot of research about the disease Hemophilia A itself, I noticed that the current case numbers of Hemophilia A are unclear as different highly trusted sources like the German Ministry of Health cite different estimated case numbers. Since a Hemophilia therapy is expensive and the heredity of Hemophilia A is fairly easy to simulate, I decided to come up with a way to solve this problem. As a result I used some logical concepts from the inheritance problem in week 5 and created my own peace of software that trys to estimate Hemophophilia A case numbers more precisely in the future.

## Features
- simulation of Hemophilia A and demographics in Germany over the next 40 years
- Inheritance modeling based on X-linked resessive gene-patterns
- Use of real world statistics
- CSV file which stores the simulation data
- Flask web application:
    - login and register features
    - users database
    - graphical representation of the simulation results
    - dowload link of my scientific paper
    - educational section explaining basing information about the disease Hmeophilia A itself
    - C simulation gets executed after a button is clicked
    - simulation data is displayed in a table
    - data deletion button

## Technologies used
- main simulation was coded in C for better memory accesibility and scalability
- SQL was used for the users and data databse
- Flask, Python, HTML, and CSS where used to build the front-end of my project
- CSV was used to store my simulation data

## File overview
- style.css - used to style my webapp
- error.html - is displayed whenever the user did something wrong (for example submitting a form withouth filling out all of the required input fields)
- hemophilia.html - this HTML page displays some general informations about Hemophilia A
- index.html
- layout.html - main HTML page
- login.html - this HTML page displays the login fields and a submit button in order to submit your login data to the server
- registrieren.html - this HTML page displays the register fields and a submit button to submit your register data to the server (after your registration was sucessful you will get redirected to the login page)
- paper.html - displays the scientific paper that I wrote, including a download link
- simulation.html - displays two buttons. The first button allows the user to run the simulation (the simulation data is than stored inside of a databse using SQL). The second button allows the user to clear the databse in order to be able to generate new data again. After the user clicked the run simulation button, the simulation data is displayed in the table below.
- app.py - includes the main Flask code of my front-end webapp
- database.py - used to create a database for the simulation data (in order to link the outcome of my back-end simulation with my webapp)
- globals.h - includes some variable declerations for my main simulation
- hemophilia.c - this is the main C simulation program
- hemophilia.db - this databse stores the main simulation data
- probabilities.h - includes probability function which determine the chance of inherting the dysfunctional F8 gene which causes Hemophilia A

## How the Simulation works
### Step 1:
- register via the register form
### Step 2:
- log into the webapp in order to have access to the simulation
### Step 3:
- click the simulation hyperlink to get redirected to the simulation.html page
### Step 4:
- clcik the run simulation button in order to run the simulation
### Step 5:
- delete the simulation data by clicking the button next to the run simulation button



