//
// 
//

#include "user.h"
user::user(const int userId,const bool isVip , int belong_groupId , group* grp ) :
    m_userId(userId) , m_isVip(isVip) ,belong_groupId(belong_groupId) ,Comedy_views(0) , Drama_views(0),
    Action_views(0) , Fantasy_views(0) , pregroup_Cmdyview(0) , pregroup_Drmaview(0) ,
    pregroup_Actionview(0) , pregroup_Fntsyview(0) , belonggroup(grp) {
}

user::~user() {
    //delete belonggroup ;
}

int user::getMUserId() const {
    return m_userId;
}

bool user::isMIsVip() const {
    return m_isVip;
}

int user::getBelongGroupId() const {
    return belong_groupId;
}

void user::setBelongGroupId(int belongGroupId) {
    belong_groupId = belongGroupId;
}

void user::change_numview(const Genre& genre) {
    if(genre == Genre::COMEDY){
        Comedy_views++ ;
    }
    if(genre == Genre::DRAMA){
        Drama_views ++ ;
    }
    if(genre == Genre::ACTION){
        Action_views ++ ;
    }
    if(genre == Genre::FANTASY){
        Fantasy_views ++ ;
    }
}

int user::numview(const Genre &genre) {
    if(belong_groupId != -1) {
        if (genre == Genre::COMEDY) {
            return Comedy_views + belonggroup->getComedyViews() - pregroup_Cmdyview;
        }
        if (genre == Genre::DRAMA) {
            return Drama_views + belonggroup->getDramaViews() - pregroup_Drmaview;
        }
        if (genre == Genre::ACTION) {
            return Action_views + belonggroup->getActionViews() - pregroup_Actionview;
        }
        if (genre == Genre::FANTASY) {
            return Fantasy_views + belonggroup->getFantasyViews() - pregroup_Fntsyview;
        }
        if (genre == Genre::NONE) {
            int alone_views = Comedy_views + Drama_views + Action_views + Fantasy_views;
            int watched_withgroup = belonggroup->getComedyViews() - pregroup_Cmdyview +
                                    belonggroup->getDramaViews() - pregroup_Drmaview +
                                    belonggroup->getActionViews() - pregroup_Actionview +
                                    belonggroup->getFantasyViews() - pregroup_Fntsyview;
            return alone_views + watched_withgroup;
        }
    }
    if (genre == Genre::COMEDY) {
        return Comedy_views ;
    }
    if (genre == Genre::DRAMA) {
        return Drama_views ;
    }
    if (genre == Genre::ACTION) {
        return Action_views ;
    }
    if (genre == Genre::FANTASY) {
        return Fantasy_views ;
    }
    if (genre == Genre::NONE) {
        return Comedy_views + Drama_views + Action_views + Fantasy_views;
    }
    return -1;
}

void user::setprev_watchGroup(const group& group){
    pregroup_Cmdyview = group.getComedyViews() ;
    pregroup_Drmaview = group.getDramaViews() ;
    pregroup_Actionview = group.getActionViews() ;
    pregroup_Fntsyview = group.getFantasyViews() ;
}

group *user::getBelonggroup() const {
    return belonggroup;
}

void user::setBelonggroup(group *belonggroup) {
    user::belonggroup = belonggroup;
}

bool user::operator==(const user &rhs) const {
    return m_userId == rhs.m_userId ;
          // m_isVip == rhs.m_isVip;
}

bool user::operator!=(const user &rhs) const {
    return !(rhs == *this);
}

bool user::operator<(const user &rhs) const {
    if (m_userId < rhs.m_userId)
        return true;
    if (rhs.m_userId < m_userId)
        return false;
    return m_isVip < rhs.m_isVip;
}

bool user::operator>(const user &rhs) const {
    return rhs < *this;
}

bool user::operator<=(const user &rhs) const {
    return !(rhs < *this);
}

bool user::operator>=(const user &rhs) const {
    return !(*this < rhs);
}

void user::decreased(){
    belonggroup->decresedviews(Genre::COMEDY,Comedy_views + belonggroup->getComedyViews() - pregroup_Cmdyview) ;
    belonggroup->decresedviews(Genre::DRAMA,Drama_views + belonggroup->getDramaViews() - pregroup_Drmaview) ;
    belonggroup->decresedviews(Genre::ACTION,Action_views + belonggroup->getActionViews() - pregroup_Actionview) ;
    belonggroup->decresedviews(Genre::FANTASY,Fantasy_views + belonggroup->getFantasyViews() - pregroup_Fntsyview) ;
}
void user::inc(){
        belonggroup->decresedviews(Genre::COMEDY,-Comedy_views) ;
        belonggroup->decresedviews(Genre::DRAMA,-Drama_views) ;
        belonggroup->decresedviews(Genre::ACTION,-Action_views) ;
        belonggroup->decresedviews(Genre::FANTASY,-Fantasy_views) ;
}

void user::incgroup() {
    Comedy_views += belonggroup->getComedyViews() - pregroup_Cmdyview ;
    Drama_views += belonggroup->getDramaViews() - pregroup_Drmaview ;
    Action_views += belonggroup->getActionViews() - pregroup_Actionview ;
    Fantasy_views += belonggroup->getFantasyViews() - pregroup_Fntsyview ;
}

//--------------------------------------------------------------------------------------------------------------


group::group(const int mGroupId)  : m_groupId(mGroupId), m_groupUsers() ,isGroupVIP(false) , Comedy_views(0) ,
                                    Drama_views(0) ,Action_views(0),Fantasy_views(0) , total_Comedy(0) , total_Drama(0)
                                    , total_Action(0) ,total_Fantasy(0) , m_numuservip(0){
}

/*group::group(const group &copygroup) :m_groupId(copygroup.m_groupId), m_groupUsers(copygroup.m_groupUsers) ,
                                      isGroupVIP(copygroup.isGroupVIP){
    for(int i=0 ; i<m_size ; i++) {
        m_users[i] = copygroup.m_users[i];
    }
}

group& group::operator=(const group& copygroup) {
    if(this == &copygroup)
        return *this ;
    user* temp_users = new user[copygroup.m_size] ;
    for(int i=0 ; i<m_size ; i++){
        temp_users[i] = copygroup.m_users[i] ;
    }
    delete[] m_users ;
    this-> m_users = temp_users ;
    //copy tree ;
    //this->m_size = copygroup.m_size ;
    this->isGroupVIP = copygroup.isGroupVIP ;
    return *this ;
}
*/
group::~group() {
}

/*
user* group::getMUsers() const {
    return m_users;
}
*/

void group::setMUsers(user* adduser) {
    if(m_groupUsers.find(adduser->getMUserId()) != nullptr){
        return ;
    }
    m_groupUsers.insert(adduser->getMUserId(),*adduser) ;
    /*if(m_users != nullptr) {
        for(int i=0 ; i<m_size ; i++){
            if(m_users[i].getMUserId() == adduser->getMUserId() )
                return;
        }
    }*/
    /* user* temp_users = new user[m_size + 1] ;
     if(temp_users == nullptr){
         return;
     }
     this->m_size ++ ;
     for(int i=0 ; i<m_size-1 ; i++){
         temp_users[i] = m_users[i] ;
     }
     temp_users[m_size-1] = *adduser ;
     delete[] m_users ;
     this-> m_users = temp_users ;*/
    //m_users[m_size-1].setBelongGroupId(m_groupId) ;
    adduser->setBelongGroupId(m_groupId);
    if(!isGroupVIP){
        isGroupVIP = adduser->isMIsVip() ;
    }
    if(adduser->isMIsVip()) {
        m_numuservip++;
    }
}

int group::getMSize() const {
    return m_groupUsers.AVLTree_size;
}

bool group::isGroupVip() const {
    return isGroupVIP;
}

int group::getComedyViews() const {
    return Comedy_views;
}

int group::getDramaViews() const {
    return Drama_views;
}

int group::getActionViews() const {
    return Action_views;
}

int group::getFantasyViews() const {
    return Fantasy_views;
}

void group::increaseviews(const Genre& genre) {
    if(genre == Genre::COMEDY){
        Comedy_views++ ;
        total_Comedy += m_groupUsers.AVLTree_size ;
    }
    if(genre == Genre::DRAMA){
        Drama_views ++ ;
        total_Drama += m_groupUsers.AVLTree_size ;
    }
    if(genre == Genre::ACTION){
        Action_views ++ ;
        total_Action += m_groupUsers.AVLTree_size ;
    }
    if(genre == Genre::FANTASY){
        Fantasy_views ++ ;
        total_Fantasy += m_groupUsers.AVLTree_size ;
    }
}

void group::increasetotal(const Genre &genre) {
    if(genre == Genre::COMEDY){
        total_Comedy ++ ;
    }
    if(genre == Genre::DRAMA){
        total_Drama ++ ;
    }
    if(genre == Genre::ACTION){
        total_Action ++ ;
    }
    if(genre == Genre::FANTASY){
        total_Fantasy ++ ;
    }
}

Genre group::rcommend() const{
    int max1 = std::max(total_Comedy , total_Drama) ;
    int max2 = std::max(total_Action, total_Fantasy) ;
    int finalmax = std::max(max1,max2) ;
    if(finalmax == total_Comedy){
        return Genre::COMEDY ;
    }
    if(finalmax == total_Drama){
        return Genre::DRAMA ;
    }
    if(finalmax == total_Action){
        return Genre::ACTION ;
    }
    if(finalmax == total_Fantasy){
        return Genre::FANTASY ;
    }
    return Genre::NONE;
}

void group::freedemTousers(user* array){
    //user* array = new user[m_groupUsers.AVLTree_size] ;
    m_groupUsers.getAllNode(m_groupUsers.tree_root,array) ;
    /*for (int i = 0 ; i <= m_groupUsers.AVLTree_size ; i++){
        array[i].setBelongGroupId(-1) ;
    }*/
}

void group::freedemUser(int userId) {
    m_groupUsers.remove(userId) ;
}

void group::decresedviews(const Genre& genre , int num) {
    if(genre == Genre::COMEDY){
        total_Comedy -= num ;
    }
    if(genre == Genre::DRAMA){
        total_Drama -= num ;
    }
    if(genre == Genre::ACTION){
        total_Action -= num ;
    }
    if(genre == Genre::FANTASY){
        total_Fantasy -= num ;
    }
}

void group::updateISvip(){
    m_numuservip -- ;
    if(m_numuservip == 0 ){
        isGroupVIP = false ;
    }
}
