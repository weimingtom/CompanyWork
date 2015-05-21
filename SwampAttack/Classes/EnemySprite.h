//
//  EnemySprite.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/26.
//
//

#ifndef __SwampAttack__EnemySprite__
#define __SwampAttack__EnemySprite__

#include "BaseCode.h"
#include "Enemy.h"
#include "ProgressBar.h"
#include "EnemyInfo.h"


enum ActionStatus
{
    normal,
    isMoving,
    isHurting,
    isAttacking,
    isDieing,
};
class EnemySprite :public Sprite {
protected:
    Enemy * m_model = NULL;
    ActionStatus    actionStatus = normal;
    std::map<std::string, Action *> m_map;
    ProgressBar *   healthBar;
    Sprite      *   armorSprite;
    bool            isHaveArmor;
    
protected:
    virtual void    move();
    virtual void    attack();
    virtual void    die();
    virtual void    hurt();
    
    void    attackCall();
    void    dieCall();
    void    hurtCall();
public:
    EnemySprite(Enemy * model);
    virtual     ~EnemySprite();
    
public:
    

    
};

#endif /* defined(__SwampAttack__EnemySprite__) */
