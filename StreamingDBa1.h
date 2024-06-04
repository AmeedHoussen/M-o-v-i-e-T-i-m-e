
// 

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_
#include "wet1util.h"
#include "AVLTree.h"
#include "movie.h"
#include "user.h"

class streaming_database {
private:
    AVLTree<int,movie> tree_movies ;
    AVLTree<int,user> tree_users ;
    AVLTree<int,group> tree_group ;
    AVLTree<movie,int> Comedy_movies ;
    int recommend_ComedyID ;
    AVLTree<movie,int> Drama_movies ;
    int recommend_DramaID ;
    AVLTree<movie,int> Action_movies ;
    int recommend_ActionID ;
    AVLTree<movie,int> Fantasy_movies ;
    int recommend_FantasyID ;
    AVLTree<movie,int> all_movies ;


public:
	// <DO-NOT-MODIFY> {
	
	streaming_database();

	virtual ~streaming_database();
	
	StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);
	
	StatusType remove_movie(int movieId);
	
	StatusType add_user(int userId, bool isVip);
	
	StatusType remove_user(int userId);
	
	StatusType add_group(int groupId);
	
	StatusType remove_group(int groupId);

	StatusType add_user_to_group(int userId, int groupId);
	
	StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);
	
	output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);
	
	output_t<int> get_group_recommendation(int groupId);
	
	// } </DO-NOT-MODIFY>
};

#endif // STREAMINGDBA1_H_
