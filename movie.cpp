//

//

#include "movie.h"

int movie::Comedy_movie = 0 ;
int movie::Drama_movie = 0 ;
int movie::Action_movie = 0 ;
int movie::Fantasy_movie = 0 ;

movie::movie(int moveid , Genre genre ,int views ,bool vipOnly):
    m_movieID(moveid) , m_genre(genre) , m_views(views) , m_vipOnly(vipOnly) , m_rating(0) ,
    m_numrater(0) , sumrating(0){
}

movie::movie(const movie &copymovie) :
        m_movieID(copymovie.m_movieID) , m_genre(copymovie.m_genre) , m_views(copymovie.m_views) ,
        m_vipOnly(copymovie.m_vipOnly) , m_rating(copymovie.m_rating) , m_numrater(copymovie.m_numrater),
        sumrating(copymovie.sumrating){
}

int movie::getMMovieId() const {
    return m_movieID;
}

Genre movie::getMGenre() const {
    return m_genre;
}

int movie::getMViews() const {
    return m_views;
}

bool movie::isMVipOnly() const {
    return m_vipOnly;
}

void movie::setMRating(int addrate) {
    sumrating += addrate;
    m_numrater ++ ;
    m_rating = sumrating/m_numrater ;
}

bool movie::operator==(const movie& other) const {
    return m_movieID == other.m_movieID &&
        m_genre == other.m_genre &&
        m_vipOnly == other.m_vipOnly ;
}

bool movie::operator!=(const movie& other) const {
    return !(other == *this);
}

void movie::setMViews(int addviews) {
    m_views += addviews;
}

void movie::update_Genrenum(int num , const Genre &genre) {
    if(genre == Genre::COMEDY){
        Comedy_movie += num ;
    }
    if(genre == Genre::DRAMA){
        Drama_movie += num ;
    }
    if(genre == Genre::ACTION){
        Action_movie += num ;
    }
    if(genre == Genre::FANTASY){
        Fantasy_movie += num ;
    }
}

bool movie::operator>(const movie& other) const {
    if(m_rating < other.m_rating){
        return true ;
    }
    if(m_rating == other.m_rating){
        if(m_views < other.m_views){
            return true ;
        }
        if(m_views == other.m_views){
            if (m_movieID > other.m_movieID){
                return true ;
            }
            return false;
        }
        return false ;
    }
    return false ;
}

bool movie::operator<(const movie& rhs) const{
    if(rhs.m_rating < m_rating){
        return true ;
    }
    if(m_rating == rhs.m_rating){
        if(rhs.m_views < m_views){
            return true ;
        }
        if(m_views == rhs.m_views){
            if (rhs.m_movieID > m_movieID){
                return true ;
            }
            return false;
        }
        return false ;
    }
    return false ;
}

bool operator>(const movie* movie1, const movie& movie2) {
    if (movie1->m_rating < movie2.m_rating) {
        return true;
    }
    if (movie1->m_rating == movie2.m_rating) {
        if (movie1->m_views < movie2.m_views) {
            return true;
        }
        if (movie1->m_views == movie2.m_views) {
            if (movie1->m_movieID > movie2.m_movieID) {
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

