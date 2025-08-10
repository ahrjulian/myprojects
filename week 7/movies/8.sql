
SELECT name FROM people
Join stars ON people.id = stars.person_id
WHERE movie_id = (SELECT id FROM movies WHERE title = 'Toy Story');


