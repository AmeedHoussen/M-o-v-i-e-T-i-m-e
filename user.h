//
// 
//

#ifndef AVLTREE_H_USER_H
#define AVLTREE_H_USER_H
#include "wet1util.h"
#include "AVLTree.h"
class group;
class user {
private:
    int m_userId ;
    bool m_isVip ;
    int belong_groupId ;
    int Comedy_views ;
    int Drama_views ;
    int Action_views ;
    int Fantasy_views ;
    int pregroup_Cmdyview ;
    int pregroup_Drmaview ;
    int pregroup_Actionview ;
    int pregroup_Fntsyview ;
    group* belonggroup ;


public:
    user() = default ;
    user(const int userId ,const bool isVip , int belong_groupId = -1 , group* grp = nullptr) ;
    //user(const user& copyuser) = default ;
    //user& operator=(const user& copyuser) = default ;
    ~user();
    int getMUserId() const;
    bool isMIsVip() const;

    int getBelongGroupId() const;
    void setBelongGroupId(int belongGroupId);

    group *getBelonggroup() const;

    void setBelonggroup(group *belonggroup);

    void change_numview(const Genre& genre) ;
    int numview(const Genre& genre) ;
    void setprev_watchGroup(const group& group) ;

    bool operator==(const user &rhs) const;
    bool operator!=(const user &rhs) const;
    bool operator<(const user &rhs) const;
    bool operator>(const user &rhs) const;
    bool operator<=(const user &rhs) const;
    bool operator>=(const user &rhs) const;

    void decreased();
    void inc();

    void incgroup() ;
    };
//------------------------------------------------------------------------------------------------------------
class group {
private:
    int m_groupId ;
    //int m_size ;
    AVLTree<int,user> m_groupUsers ;
    //user* m_users ;
    bool isGroupVIP ;
    int Comedy_views ;
    int Drama_views ;
    int Action_views ;
    int Fantasy_views ;
    int total_Comedy ;
    int total_Drama ;
    int total_Action ;
    int total_Fantasy ;
    int m_numuservip ;

public:
    group() = default ;
    group(const int mGroupId);
    //group(const group& copygroup)  ;
    //group& operator=(const group& copygroup) ;
    ~group();

    //user *getMUsers() const;
    void setMUsers(user* adduser);
    int getMSize() const;
    bool isGroupVip() const;

    int getComedyViews() const;
    int getDramaViews() const ;
    int getActionViews() const;
    int getFantasyViews() const;
    void increaseviews(const Genre& genre) ;
    void increasetotal(const Genre& genre) ;

    Genre rcommend() const ;

    void freedemTousers(user* dataArray);

    void freedemUser(int userId) ;

    void decresedviews(const Genre& genre , int num) ;

    void updateISvip() ;

    };

#endif //AVLTREE_H_USER_H
