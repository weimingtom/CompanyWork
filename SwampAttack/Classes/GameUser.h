//
//  GameUser.h
//  SwampAttack
//
//  Created by oceantech02 on 15/5/8.
//
//

#ifndef __SwampAttack__GameUser__
#define __SwampAttack__GameUser__

#include "BaseCode.h"
#include "GameSubject.h"


#define _G_U GameUser::getInstance()
using namespace std;

class GameUser : public GameSubject,public Node {
private:
    UserDefault * m_user;
    int     m_userHealth;
    int     m_time;
private:
    GameUser();
    ~GameUser();
    void    updateTime(float data);
    
    void    setBoolForKey(string name,bool value);
    void    setIntForKey(string name,int value);
    void    setFloatForKey(string name,float value);
    void    setStringForKey(string name,string value);
    bool    getBoolForKey(string name);
    int     getIntForKey(string name);
    float   getFloatForKey(string name);
    string  getStringForKey(string name);
    //
    double    getTimeSec();
    void    setTimeSec();
public:
    static GameUser * getInstance();
    
    void    enterGame();
    void    exitGame();
    //--- health ----
    int     getUserHealth();
    void    setUserHealth(int health);
    void    setUserGold(int gold);
    int     getUserGold();
    //---  gun ----
    void    unlockGun(string gunId);
    bool    isUnlockGun(string gunId);
    void    setTakeUpGun(string gunId,bool takeUp);
    bool    isTakeUp(string gunId);
    void    setTakeUpIndex(string gunId,int index);
    int     getTakeUpIndex(string gunId);
    void    setGunLevel(string gunId, int level);
    int     getGunLevel(string gunId);
    void    setGunBulletNumber(string gunId,int num);
    int     getGunBulletNumber(string gunId);
    //--- building ---
    void    unlockBuilding(string buildingId);
    bool    isUnlockBuilding(string buildingId);
    void    setBuildingLevel(string buildingId,int level);
    int     getBuildingLevel(string buildingId);
    //--- prop -----
    void    unlockProp(string propId);
    bool    isUnlockProp(string propId);
    void    setPropNum(string propId,int num);
    int     getPropNum(string propId);
    //--- award ----
    
    
};

#endif /* defined(__SwampAttack__GameUser__) */