#include "StreamingDBa1.h"

streaming_database::streaming_database(): tree_movies() , tree_users(),tree_group(), Comedy_movies() ,
    recommend_ComedyID(-1) , Drama_movies() , recommend_DramaID(-1) , Action_movies() ,
    recommend_ActionID(-1) , Fantasy_movies() , recommend_FantasyID(-1), all_movies(){
}

streaming_database::~streaming_database(){
}

StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId<=0 || genre == Genre::NONE || views < 0){
        return StatusType::INVALID_INPUT;
    }
    if(tree_movies.find(movieId) != nullptr) {
        return StatusType::FAILURE;
    }
    if(genre == Genre::COMEDY){
        int prev_tree_size = Comedy_movies.AVLTree_size ;
        Comedy_movies.insert(movie(movieId, genre, views, vipOnly), movieId) ;
        if(Comedy_movies.AVLTree_size == prev_tree_size){
            return StatusType::ALLOCATION_ERROR ;
        }
    }
    if(genre == Genre::DRAMA){
        int prev_tree_size = Drama_movies.AVLTree_size ;
        Drama_movies.insert(movie(movieId, genre, views, vipOnly),movieId) ;
        if(Drama_movies.AVLTree_size == prev_tree_size){
            return StatusType::ALLOCATION_ERROR ;
        }
    }
    if(genre == Genre::ACTION){
        int prev_tree_size = Action_movies.AVLTree_size ;
        Action_movies.insert(movie(movieId, genre, views, vipOnly),movieId) ;
        if(Action_movies.AVLTree_size == prev_tree_size){
            return StatusType::ALLOCATION_ERROR ;
        }
    }
    if(genre == Genre::FANTASY){
        int prev_tree_size = Fantasy_movies.AVLTree_size ;
        Fantasy_movies.insert(movie(movieId, genre, views, vipOnly),movieId) ;
        if(Fantasy_movies.AVLTree_size == prev_tree_size){
            return StatusType::ALLOCATION_ERROR ;
        }
    }
    int prev_tree_size = tree_movies.AVLTree_size ;
    tree_movies.insert(movieId, movie(movieId, genre, views, vipOnly)) ;
    if(tree_movies.AVLTree_size == prev_tree_size){
        return StatusType::ALLOCATION_ERROR ;
    }
    all_movies.insert(movie(movieId, genre, views, vipOnly), movieId) ;
    tree_movies.find(movieId)->data->update_Genrenum(1,genre) ;
    recommend_ComedyID = Comedy_movies.findMaxRightmostLeaf(Comedy_movies.tree_root) ;
    recommend_DramaID = Drama_movies.findMaxRightmostLeaf(Drama_movies.tree_root) ;
    recommend_ActionID = Action_movies.findMaxRightmostLeaf(Action_movies.tree_root) ;
    recommend_FantasyID = Fantasy_movies.findMaxRightmostLeaf(Fantasy_movies.tree_root) ;
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
	if(movieId<=ZERO){
        return StatusType::INVALID_INPUT ;
    }
    if(tree_movies.find(movieId) == nullptr) {
        return StatusType::FAILURE ;
    }
    int prev_tree_size = tree_movies.AVLTree_size ;
    movie* delete_moive =tree_movies.find(movieId)->data ;
    Comedy_movies.remove(*delete_moive) ;
    Drama_movies.remove(*delete_moive) ;
    Action_movies.remove(*delete_moive) ;
    Fantasy_movies.remove(*delete_moive) ;
    all_movies.remove(*delete_moive) ;
    delete_moive->update_Genrenum(-1 , delete_moive->getMGenre()) ;
    tree_movies.remove(movieId) ;
    if(tree_movies.AVLTree_size == prev_tree_size){
        return StatusType::ALLOCATION_ERROR ;
    }
    if(Comedy_movies.AVLTree_size > 0) {
        recommend_ComedyID = Comedy_movies.findMaxRightmostLeaf(Comedy_movies.tree_root);
    } else{
        recommend_ComedyID = -1 ;
    }
    if(Drama_movies.AVLTree_size > 0) {
        recommend_DramaID = Drama_movies.findMaxRightmostLeaf(Drama_movies.tree_root);
    }else{
        recommend_DramaID = -1 ;
    }
    if(Action_movies.AVLTree_size > 0) {
        recommend_ActionID = Action_movies.findMaxRightmostLeaf(Action_movies.tree_root);
    } else{
        recommend_ActionID = -1 ;
    }
    if(Fantasy_movies.AVLTree_size > 0) {
        recommend_FantasyID = Fantasy_movies.findMaxRightmostLeaf(Fantasy_movies.tree_root);
    } else{
        recommend_FantasyID = -1 ;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
	if(userId<=ZERO){
        return StatusType::INVALID_INPUT ;
    }
    if(tree_users.find(userId) != nullptr){
        return StatusType::FAILURE ;
    }
    int prev_tree_size = tree_users.AVLTree_size ;
    tree_users.insert(userId,user(userId,isVip)) ;
    if(tree_users.AVLTree_size == prev_tree_size){
        return StatusType::ALLOCATION_ERROR ;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
	if(userId<= ZERO) {
        return StatusType::INVALID_INPUT ;
    }
    if(tree_users.find(userId) == nullptr){
        return StatusType::FAILURE ;
    }
    user* curruser = tree_users.find(userId)->data ;
    //curruser->decreased() ;
    if(curruser->getBelongGroupId() != -1) {
        if(curruser->getBelonggroup()->isGroupVip() && curruser->isMIsVip()){
            curruser->getBelonggroup()->updateISvip() ;
        }
        curruser->getBelonggroup()->freedemUser(userId);
        curruser->decreased() ;
    }
    int prev_tree_size = tree_users.AVLTree_size ;
    tree_users.remove(userId) ;
    if(tree_users.AVLTree_size == prev_tree_size) {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId<=ZERO){
        return StatusType::INVALID_INPUT ;
    }
    if(tree_group.find(groupId) != nullptr){
        return StatusType::FAILURE ;
    }
    int prev_tree_size = tree_group.AVLTree_size ;
    tree_group.insert(groupId, group(groupId)) ;
    if(tree_group.AVLTree_size == prev_tree_size){
        return StatusType::ALLOCATION_ERROR ;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
	if(groupId <= ZERO){
        return StatusType::INVALID_INPUT ;
    }
    if(tree_group.find(groupId) == nullptr){
        return StatusType::FAILURE ;
    }
    int prev_tree_size = tree_group.AVLTree_size ;
    int numusers = tree_group.find(groupId)->data->getMSize() ;
    user* array = new user[numusers] ;
    tree_group.find(groupId)->data->freedemTousers(array) ;
    for(int  j = 0 ; j < numusers ; j++  ){
        tree_users.find(array[j].getMUserId())->data->incgroup() ;
        tree_users.find(array[j].getMUserId())->data->setBelongGroupId(-1) ;
    }
    delete[] array ;
    tree_group.remove(groupId) ;
    if(tree_group.AVLTree_size == prev_tree_size){
        return StatusType::ALLOCATION_ERROR ;
    }
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
	if(userId <= ZERO || groupId <= ZERO){
        return StatusType::INVALID_INPUT ;
    }
    if(tree_group.find(groupId) == nullptr || tree_users.find(userId) == nullptr){
        return StatusType::FAILURE ;
    }
    if(tree_users.find(userId)->data->getBelongGroupId() != -1 ){
        return StatusType::FAILURE ;
    }
    group* temp_group = tree_group.find(groupId)->data;
    int size_prevusers = temp_group->getMSize() ;
    user* curruser = tree_users.find(userId)->data ;
    temp_group->setMUsers(curruser) ;
    if(temp_group->getMSize() == size_prevusers){
        return StatusType::ALLOCATION_ERROR ;
    }
    curruser->setprev_watchGroup(*temp_group) ;
    curruser->setBelonggroup(temp_group) ;
    curruser->inc();
    //curruser->setAssoiceretToGroup() ;
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
	if(userId <= ZERO || movieId <= ZERO){
        return  StatusType::INVALID_INPUT ;
    }
    if(tree_users.find(userId) == nullptr || tree_movies.find(movieId) == nullptr){
        return StatusType::FAILURE ;
    }
    movie* currmovie = tree_movies.find(movieId)->data ;
    user* curruser = tree_users.find(userId)->data ;
    if(currmovie->isMVipOnly()){
        if(!curruser->isMIsVip()){
            return StatusType::FAILURE ;
        }
    }
    all_movies.remove(*currmovie) ;
    if(currmovie->getMGenre() == Genre::COMEDY ){
        Comedy_movies.remove(*currmovie) ;
        currmovie->setMViews(1) ;
        Comedy_movies.insert(*currmovie,currmovie->getMMovieId()) ;
    }
    if(currmovie->getMGenre() == Genre::DRAMA ){
        Drama_movies.remove(*currmovie) ;
        currmovie->setMViews(1) ;
        Drama_movies.insert(*currmovie,currmovie->getMMovieId()) ;
    }
    if(currmovie->getMGenre() == Genre::ACTION ){
        Action_movies.remove(*currmovie) ;
        currmovie->setMViews(1) ;
        Action_movies.insert(*currmovie,currmovie->getMMovieId()) ;
    }
    if(currmovie->getMGenre() == Genre::FANTASY ){
        Fantasy_movies.remove(*currmovie) ;
        currmovie->setMViews(1) ;
        Fantasy_movies.insert(*currmovie,currmovie->getMMovieId()) ;
    }
    all_movies.insert(*currmovie,currmovie->getMMovieId()) ;
    curruser->change_numview(currmovie->getMGenre()) ;
    if (curruser->getBelongGroupId() !=-1){
        curruser->getBelonggroup()->increasetotal(currmovie->getMGenre());
       // curruser->increasedAssoicetedToGroup(currmovie->getMGenre());
    }
    recommend_ComedyID = Comedy_movies.findMaxRightmostLeaf(Comedy_movies.tree_root) ;
    recommend_DramaID = Drama_movies.findMaxRightmostLeaf(Drama_movies.tree_root) ;
    recommend_ActionID = Action_movies.findMaxRightmostLeaf(Action_movies.tree_root) ;
    recommend_FantasyID = Fantasy_movies.findMaxRightmostLeaf(Fantasy_movies.tree_root) ;
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if(groupId <= ZERO || movieId <= ZERO){
        return StatusType::INVALID_INPUT ;
    }
    if(tree_group.find(groupId) == nullptr || tree_movies.find(movieId) == nullptr){
        return StatusType::FAILURE ;
    }
    group* currgroup = tree_group.find(groupId)->data ;
    movie* currmovie = tree_movies.find(movieId)->data ;
    if(currgroup->getMSize() == ZERO || (currmovie->isMVipOnly() && !currgroup->isGroupVip()) ){
        return StatusType::FAILURE ;
    }
    all_movies.remove(*currmovie) ;
    if(currmovie->getMGenre() == Genre::COMEDY ){
        Comedy_movies.remove(*currmovie) ;
        currmovie->setMViews(currgroup->getMSize()) ;
        currgroup->increaseviews(currmovie->getMGenre()) ;
        Comedy_movies.insert(*currmovie,currmovie->getMMovieId()) ;
    }
    if(currmovie->getMGenre() == Genre::DRAMA ){
        Drama_movies.remove(*currmovie) ;
        currmovie->setMViews(currgroup->getMSize()) ;
        currgroup->increaseviews(currmovie->getMGenre()) ;
        Drama_movies.insert(*currmovie,currmovie->getMMovieId()) ;
    }
    if(currmovie->getMGenre() == Genre::ACTION ){
        Action_movies.remove(*currmovie) ;
        currmovie->setMViews(currgroup->getMSize()) ;
        currgroup->increaseviews(currmovie->getMGenre()) ;
        Action_movies.insert(*currmovie,currmovie->getMMovieId()) ;
    }
    if(currmovie->getMGenre() == Genre::FANTASY ){
        Fantasy_movies.remove(*currmovie) ;
        currmovie->setMViews(currgroup->getMSize()) ;
        currgroup->increaseviews(currmovie->getMGenre()) ;
        Fantasy_movies.insert(*currmovie,currmovie->getMMovieId()) ;
    }
    all_movies.insert(*currmovie,currmovie->getMMovieId()) ;
    recommend_ComedyID = Comedy_movies.findMaxRightmostLeaf(Comedy_movies.tree_root) ;
    recommend_DramaID = Drama_movies.findMaxRightmostLeaf(Drama_movies.tree_root) ;
    recommend_ActionID = Action_movies.findMaxRightmostLeaf(Action_movies.tree_root) ;
    recommend_FantasyID = Fantasy_movies.findMaxRightmostLeaf(Fantasy_movies.tree_root) ;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    int num = 0;
    if(genre == Genre::NONE){
        num = movie::Comedy_movie + movie::Drama_movie + movie::Action_movie + movie::Fantasy_movie ;
        return output_t<int>(num) ;
    }
    if(genre == Genre::COMEDY){
        num = movie::Comedy_movie ;
        return output_t<int>(num) ;
    }
    if(genre == Genre::DRAMA){
        num = movie::Drama_movie ;
        return output_t<int>(num) ;
    }
    if(genre == Genre::ACTION){
        num = movie::Action_movie ;
        return output_t<int>(num) ;
    }
    if(genre == Genre::FANTASY){
        num = movie::Fantasy_movie ;
        return output_t<int>(num) ;
    }
    return output_t<int>(num);
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if(output == nullptr){
        return StatusType::INVALID_INPUT ;
    }
    if(genre == Genre::NONE && all_movies.AVLTree_size == 0){
        return StatusType::FAILURE ;
    }
    if(genre == Genre::COMEDY && movie::Comedy_movie==0){
        return StatusType::FAILURE ;
    }
    if(genre == Genre::DRAMA && movie::Drama_movie==0){
        return StatusType::FAILURE ;
    }
    if(genre == Genre::ACTION && movie::Action_movie==0){
        return StatusType::FAILURE ;
    }
    if(genre == Genre::FANTASY && movie::Fantasy_movie==0){
        return StatusType::FAILURE ;
    }
    //int i = 0 ;
    if(genre == Genre::COMEDY){
        //Comedy_movies.inorder(Comedy_movies.tree_root ,output , i) ;
        movie* array = new movie[movie::Comedy_movie] ;
        Comedy_movies.inorder(Comedy_movies.tree_root ,array) ;
        for(int j=0 ; j<movie::Comedy_movie ; j++){
            output[movie::Comedy_movie-j-1]=(*(array-1)).getMMovieId() ;
            array-- ;
        }
        delete[] array ;
        return StatusType::SUCCESS;
    }
    if(genre == Genre::DRAMA){
        //Drama_movies.inorder(Drama_movies.tree_root ,output , i) ;
        movie* array = new movie[movie::Drama_movie] ;
        Drama_movies.inorder(Drama_movies.tree_root ,array) ;
        for(int j=0 ; j<movie::Drama_movie ; j++){
            output[movie::Drama_movie-j-1]=(*(array-1)).getMMovieId() ;
            array-- ;
        }
        delete[] array ;
        return StatusType::SUCCESS;
    }
    if(genre == Genre::ACTION){
      //  Action_movies.inorder(Action_movies.tree_root ,output , i) ;
        movie* array = new movie[movie::Action_movie] ;
        Action_movies.inorder(Action_movies.tree_root ,array) ;
        for(int j=0 ; j<movie::Action_movie ; j++){
            output[movie::Action_movie-j-1]=(*(array-1)).getMMovieId() ;
            array-- ;
        }
        delete[] array ;
        return StatusType::SUCCESS;
    }
    if(genre == Genre::FANTASY){
        //Fantasy_movies.inorder(Fantasy_movies.tree_root ,output , i) ;
        movie* array = new movie[movie::Fantasy_movie] ;
        Fantasy_movies.inorder(Fantasy_movies.tree_root ,array) ;
        for(int j=0 ; j<movie::Fantasy_movie ; j++){
            output[movie::Fantasy_movie-j-1]=(*(array-1)).getMMovieId() ;
            array-- ;
        }
        delete[] array ;
        return StatusType::SUCCESS;
    }
   // tree_movies.inorder2(tree_movies.tree_root,output,i) ;
   int size = get_all_movies_count(Genre::NONE).ans() ;
    movie* array = new movie[size] ;
    all_movies.inorder(all_movies.tree_root ,array) ;
    for(int j=0 ; j<size ; j++){
        output[size-j-1]=(*(array-1)).getMMovieId() ;
        array-- ;
    }
    delete[] array ;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    if(userId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT) ;
    }
    if(tree_users.find(userId) == nullptr){
        return output_t<int>(StatusType::FAILURE) ;
    }
    user* ouruser = tree_users.find(userId)->data ;
    return output_t<int>(ouruser->numview(genre)) ;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if(userId <= 0 || movieId <= 0 || rating < 0 || rating > 100){
        return StatusType::INVALID_INPUT ;
    }
    if(tree_users.find(userId) == nullptr || tree_movies.find(movieId) == nullptr){
        return StatusType::FAILURE ;
    }
    user* curuser = tree_users.find(userId)->data ;
    movie* curmovie = tree_movies.find(movieId)->data ;
    if(!curuser->isMIsVip() && curmovie->isMVipOnly()){
        return StatusType::FAILURE ;
    }
    all_movies.remove(*curmovie) ;
    if(curmovie->getMGenre() == Genre::COMEDY ){
        Comedy_movies.remove(*curmovie) ;
        curmovie->setMRating(rating) ;
        Comedy_movies.insert(*curmovie,curmovie->getMMovieId()) ;
    }
    if(curmovie->getMGenre() == Genre::DRAMA ){
        Drama_movies.remove(*curmovie) ;
        curmovie->setMRating(rating) ;
        Drama_movies.insert(*curmovie,curmovie->getMMovieId()) ;
    }
    if(curmovie->getMGenre() == Genre::ACTION ){
        Action_movies.remove(*curmovie) ;
        curmovie->setMRating(rating) ;
        Action_movies.insert(*curmovie,curmovie->getMMovieId()) ;
    }
    if(curmovie->getMGenre() == Genre::FANTASY ){
        Fantasy_movies.remove(*curmovie) ;
        curmovie->setMRating(rating) ;
        Fantasy_movies.insert(*curmovie,curmovie->getMMovieId()) ;
    }
    all_movies.insert(*curmovie,curmovie->getMMovieId()) ;
    recommend_ComedyID = Comedy_movies.findMaxRightmostLeaf(Comedy_movies.tree_root) ;
    recommend_DramaID = Drama_movies.findMaxRightmostLeaf(Drama_movies.tree_root) ;
    recommend_ActionID = Action_movies.findMaxRightmostLeaf(Action_movies.tree_root) ;
    recommend_FantasyID = Fantasy_movies.findMaxRightmostLeaf(Fantasy_movies.tree_root) ;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    if(groupId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT) ;
    }
    if(tree_group.find(groupId) == nullptr){
        return output_t<int>(StatusType::FAILURE) ;
    }
    group* curgroup = tree_group.find(groupId)->data ;
    if(curgroup->getMSize() == 0 ) {
        return output_t<int>(StatusType::FAILURE);
    }
    if(curgroup->rcommend()==Genre::COMEDY && movie::Comedy_movie == 0){
        return output_t<int>(StatusType::FAILURE);
    }
    if(curgroup->rcommend()==Genre::DRAMA && movie::Drama_movie == 0){
        return output_t<int>(StatusType::FAILURE);
    }
    if(curgroup->rcommend()==Genre::ACTION && movie::Action_movie == 0){
        return output_t<int>(StatusType::FAILURE);
    }
    if(curgroup->rcommend()==Genre::FANTASY && movie::Fantasy_movie == 0){
        return output_t<int>(StatusType::FAILURE);
    }
    if(curgroup->rcommend() == Genre::COMEDY){
        return output_t<int>(recommend_ComedyID) ;
    }
    if(curgroup->rcommend() == Genre::DRAMA){
        return output_t<int>(recommend_DramaID) ;
    }
    if(curgroup->rcommend() == Genre::ACTION){
        return output_t<int>(recommend_ActionID) ;
    }
    if(curgroup->rcommend() == Genre::FANTASY){
        return output_t<int>(recommend_FantasyID) ;
    }
    return output_t<int>(StatusType::FAILURE);
}


