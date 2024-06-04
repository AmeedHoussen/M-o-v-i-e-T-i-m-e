//
//

#ifndef AVLTREE_H_MOVIE_H
#define AVLTREE_H_MOVIE_H
#include "wet1util.h"

class movie {
private:
    int m_movieID;
    Genre m_genre;
    int m_views;
    bool m_vipOnly;
    double m_rating;
    int m_numrater ;
    double sumrating ;

public:
    static int Comedy_movie;
    static int Drama_movie;
    static int Action_movie;
    static int Fantasy_movie;

    movie() = default;
    movie(int moveid,Genre genre,int views,bool vipOnly);
    movie(const movie &copymovie) ;
    movie &operator=(const movie &copymovie) = default;
    ~movie() = default;

    int getMMovieId() const;

    Genre getMGenre() const;

    int getMViews() const;

    bool isMVipOnly() const;

    void setMRating(int addrate);

    bool operator==(const movie &other) const;

    bool operator!=(const movie &other) const;

    void setMViews(int addviews);

    void update_Genrenum(int num, const Genre &genre);

    bool operator>(const movie &rhs) const;

    bool operator<(const movie &rhs) const;

    friend bool operator>(const movie* movie1, const movie &movie2)  ;


};


#endif //AVLTREE_H_MOVIE_H
