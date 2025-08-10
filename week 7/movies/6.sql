SELECT AVG(rating) FROM movies INNER JOIN ratings on id = movie_id WHERE year = '2012';
