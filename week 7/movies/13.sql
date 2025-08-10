SELECT name FROM people
WHERE id IN (SELECT person_id FROM stars
JOIN people on people.id = stars.person_id
WHERE stars.movie_id IN (SELECT movie_id FROM stars JOIN people ON people.id = stars.person_id WHERE people.name = (SELECT name FROM people WHERE (name = 'Kevin Bacon' AND birth LIKE '%1958'))))
AND people.name <> 'Kevin Bacon';






SELECT name FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = 'Toy Story'



SELECT birth FROM people
WHERE name IN (
SELECT name FROM people
JOIN stars on people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.title = 'Toy Story');
-- 
