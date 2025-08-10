-- Keep a log of any SQL queries you execute as you solve the mystery.
--get a closer description of the theft
SELECT description FROM crime_scene_reports
WHERE month = '7' AND day = '28' AND street = 'Humphrey Street';

-- took place at 10:15 am at the Humphrey bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- each of their transcripts mentions the bakery
-- littering took place at 16:36. No known witnesses

-- now Im going to take a further look into the transcripts
SELECT transcripts FROM interviews WHERE year = 2024 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';
-- Sometimes within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot
-- in that time frame |check

-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money |check

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard
-- the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked
-- the person on the other end of the phone to purchase the flight ticket

--next im going to investigate the security footage from the bakery parking lot
SELECT license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15
AND minute < 25;

--5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55

-- next im going to take a look on was withdrawing money at the atm
-- i want to find out the amount that the thief withdrew
SELECT amount FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';
-- 48,20,60,50,80,20,30,35

-- now im able to find out the account number
SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Streer'
AND transaction_type = 'withdraw';
--28500762, 28296815, 76054385, 49610011 (Bruce), 16153065, 25506511, 81061156, 26013199

SELECT receiver FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration > 1;
SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration > 1;

-- find the airport id of fiftyville
SELECT id FROM airports WHERE city = 'Fiftyville';
-- Fifftyville's id is 8

-- now i should be able to figure out the destination airport
SELECT destination_airport_id, hour FROM flights WHERE origin_airport_id = 8 AND year = 2024 AND month = 7 AND day = 29
ORDER BY hour ASC LIMIT 1;
-- destination airport has the id 4

-- now im going to figure out the name of the destination airport
SELECT city FROM airports WHERE id = 4;
--New York City

--now we can combine the people table with the license_plate query to find some suspects
SELECT name FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE people.license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2024 AND day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25);
--join phone_calls on people.name = phone_calls.caller
--suspects: Bruce, Kelsey, Diana, Sofia, Luca, Iman, Barry, Vanessa

-- now we can combine everything with the phone number of the caller
SELECT distinct(name) FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
JOIN phone_calls ON bakery_security_logs.month = phone_calls.month
WHERE people.phone_number IN (SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration > 1)
AND people.license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2024 AND day = 28 AND month = 7 AND hour = 10 AND minute > 15 AND minute < 25);
--suspects left: Vanessa, Barry, Sofia, Diana, Kelsey, Bruce

-- Next i will find of the flight id
SELECT id, hour FROM flights WHERE origin_airport_id = 8 AND year = 2024 AND month = 7 AND day = 29 ORDER BY hour ASC LIMIT 1;
--the flight_id = 36

-- NOw im going to take a look at the passenger list and combine the passenger table with the people table to find the passport_number
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id = 36;
-- Doris, Sofia, Bruce, Edward, Kelsey, Taylor, Kenny, Luca

-- This means that the current suspects are: Sofia, Bruce, Kelsey

-- now i will try to find out if any bank_accounts that i have listed before match with the people id of the suspects
SELECT name FROM people
JOIN bank_accounts on people.id = bank_accounts.person_id
WHERE people.id In(
SELECT person_id FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2024
AND day = 28 AND month = 7 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street'));
--Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista

-- this means that the current suspects are: Bruce -> Bruce is the thief

-- now im going to find out the phone number of bruce so I can find out who he called after the theft
SELECT phone_number FROM people WHERE name = 'Bruce';
--(357) 555-5533
-- now i should be able to find the receiver of the call
SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533';
--looks like he called a lot of other people
--lets see if any of those people took the same flight

SELECT passengers.passport_number FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
Where passengers.flight_id = 36;

SELECT passengers.passport_number FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE passengers.passport_number IN (SELECT passport_number FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE people.phone_number IN (SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533'));
--seems like whoever helped him wdid not take the same flight

SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND year = 2024 AND month = 7 AND day = 28 AND duration > 1;
-- those are the 4 phone numbers of the suspects

-- now we should be able to find out who they are
SELECT distinct(name) FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE people.phone_number IN (SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND year = 2024
AND month = 7 AND day = 28 AND duration > 1);
--suspects:Gregory, Carl, Robin, Deborah

SELECT id FROM people
WHERE people.passport_number IN(
SELECT distinct(passport_number) FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE people.phone_number IN (SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND year = 2024 AND month = 7 AND day = 28 AND duration > 1));
-- seems like whoever helped him did nit take the same flight
-- ids: 315221, 652398, 985497

-- lets see who withdrew money on that day since the accomplice was supposed to pay for the flight
SELECT amount, account_number FROM atm_transactions WHERE year = 2024
AND month = 7 AND day = 28 AND transaction_type = 'withdraw';

-- now im going ti figure out if any of those people withdrew money on that specific day
SELECT distinct(people.id) FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2024 AND month = 7
AND day = 28 AND transaction_type = 'withdraw');

--now im going to find out the ids of our suspects
SELECT id,passport_number FROM people WHERE name = 'Carl';--652398 , 7771405611
SELECT id,passport_number FROM people WHERE name = 'Gregory';--315221 , 3355598951
SELECT id, passport_number FROM people WHERE name = 'Robin';--864400 , NULL (he does not have a passport)
SELECT id,passport_number FROM people WHERE name = 'Deborah';--985497 , 8714200946
--since carl, gregory and deborah where not registered for the flight the only suspect thats left is robin
--thats why robin is the accomplice

SELECT passport_number FROM people WHERE name = 'Bruce'; --5773159633
--lets see which flights the suspects took
SELECT flight_id FROM passengers WHERE passport_number = 7771405611;--10, 19, 47
SELECT flight_id FROM passengers WHERE passport_number = 3355598951;--4, 28, 41
SELECT flight_id FROM passengers WHERE passport_number = 8714200946;--22

SELECT destination_airport_id FROM flights WHERE id = 10; --New York City
--lets see when he took the flight
SELECT year, month, day, hour FROM flights WHERE id = 10;
--2024, 7, 30, 13 (carl)
-- Robin has to be the accomplice!
