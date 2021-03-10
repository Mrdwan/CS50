SELECT title from movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON stars.person_id = people.id
    WHERE people.name IN ("Johnny Depp", "Helena Bonham Carter")
    GROUP BY stars.movie_id
    HAVING count(stars.movie_id) > 1

