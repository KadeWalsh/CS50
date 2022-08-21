-- Look for police reports on day of theft
SELECT description
FROM crime_scene_reports
WHERE month = 7
    AND day = 28
    AND year = 2021
    AND street = "Humphrey Street";
-- Theft occurred at 10:15h, at Humphrey St Bakery.
-- 3 witnesses interviewed.  Check interview transcripts for dat of theft


-- Search for interview transcripts re theft
SELECT transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2021;
-- Suspect made a call, of under 60 seconds, after theft.
    -- Spoke about booking flight out of town following day, on earliest flight possible.
-- Suspect used ATM on Leggett Street to withdraw money on day of theft.
-- Suspect got drove car out of Bakery parking lot after theft.
    -- Between 10:15 and 10:25am


-- Find ATM transactions withdrawing money on day of theft, at Leggett Street ATM location
SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions on bank_accounts.account_number = atm_transactions.account_number
WHERE day = 28
    AND month = 7
    AND year = 2021
    AND atm_location = "Leggett Street"
    AND transaction_type = "withdraw";
-- 8 possible suspects returned
    -- Bruce
    -- Diana
    -- Brooke
    -- Kenny
    -- Iman
    -- Luca
    -- Taylor
    -- Benista


--  Check phone calls log for < 60 second calls from any of suspects
SELECT DISTINCT name
FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions on bank_accounts.account_number = atm_transactions.account_number
WHERE phone_calls.day = 28
    AND phone_calls.month = 7
    AND phone_calls.year = 2021
    AND atm_location = "Leggett Street"
    AND transaction_type = "withdraw"
    AND phone_calls.duration < 60
    AND atm_transactions.day = 28
    AND atm_transactions.month = 7
    AND atm_transactions.year = 2021;
-- 5 possible suspects returned
    -- Kenny
    -- Taylor
    -- Bruce
    -- Benista
    -- Diana


-- Check suspects against bakery security logs
SELECT name
FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
JOIN phone_calls ON phone_calls.caller = people.phone_number
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions on bank_accounts.account_number = atm_transactions.account_number
WHERE phone_calls.day = 28
    AND phone_calls.month = 7
    AND phone_calls.year = 2021
    AND atm_location = "Leggett Street"
    AND transaction_type = "withdraw"
    AND phone_calls.duration < 60
    AND atm_transactions.day = 28
    AND atm_transactions.month = 7
    AND atm_transactions.year = 2021
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.year = 2021
    AND bakery_security_logs.activity = "exit"
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute BETWEEN 15 AND 25;

-- 2 Suspects retured
    -- Bruce
    -- Diana



-- find airport code for Fiftyville from airports table
SELECT full_name, id FROM airports WHERE city LIKE "fiftyville";
-- Fiftyville airport ID = 8

-- Find earliest flight departing July 29 from Fiftyville
SELECT id AS "flight #", destination_airport_id AS destination
FROM flights
WHERE day = 29
    AND month = 7
    AND year = 2021
    AND origin_airport_id = (
        SELECT id FROM airports WHERE city LIKE "fiftyville"
        )
ORDER BY hour ASC, minute ASC LIMIT 1;
-- returns flight ID 36, destination airport ID 4.


-- find destination airport from airport id
SELECT city
FROM airports
WHERE id = 4;
-- Thief fled to New York City (ID 4)


-- Check if suspects on flight to New York City
SELECT DISTINCT name
FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.destination_airport_id
WHERE flights.id = 36
    AND (name = "Bruce"
        OR name = "Diana");
-- Only Bruce was on flight to New York City, therefore Bruce is the thief.


-- revisit phone call log to see who accomplice is
SELECT name
FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE phone_calls.day = 28
    AND phone_calls.month = 7
    AND phone_calls.year = 2021
    AND phone_calls.duration < 60
    AND phone_calls.caller = (SELECT phone_number FROM people WHERE name ="Bruce");
-- Bruce called Robin therefore Robin is Bruce's accomplice.


