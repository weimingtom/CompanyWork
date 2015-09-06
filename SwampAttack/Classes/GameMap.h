//
//  GameMap.h
//  SwampAttack
//
//  Created by oceantech02 on 15/3/30.
//
//

#ifndef __SwampAttack__GameMap__
#define __SwampAttack__GameMap__

#include "BaseCode.h"

class GameMap {
    
public:
    
    int enemy_start_upline = 100;
    Vec2 enemy_start_buttomPoint = {m_visibleOrigin.x + m_visibleSize.width + 70, m_visibleOrigin.y + 50};
    int enemy_target_upline = 60;
    Vec2 enemy_target_buttomPoint = {m_visibleOrigin.x + 255, m_visibleOrigin.y + 50};
    
    int flyEnemy_start_upline = 100;
    Vec2 flyEnemy_start_buttomPoint = {m_visibleOrigin.x + m_visibleSize.width + 70, m_visibleOrigin.y + 250};
    
    int flyEnemy_target_upLine = 250;
    int flyEnemy_target_rightLine = 150;
    Vec2 flyEnemy_target_buttomPoint = {m_visibleOrigin.x + 30, m_visibleOrigin.y + 80};
    
    
    Vec2 m_BulletStartPoint = {m_visibleOrigin.x + 290, m_visibleOrigin.y + 270};
    
    
    Vec2 fightScene_human_Point = {m_visibleOrigin.x + 240, m_visibleOrigin.y + 180};
    Vec2 fightScene_gangpao_Point = {m_visibleOrigin.x + 110,m_visibleOrigin.y + 385};
    Vec2 gangpao_BulletStartPoint = {m_visibleOrigin.x + 170, m_visibleOrigin.y + 370};
    
    Vec2 fightScene_zhalan_point1 = {m_visibleOrigin.x + 320,m_visibleOrigin.y + 70};
    Vec2 fightScene_zhalan_point2 = {m_visibleOrigin.x + 340,m_visibleOrigin.y + 150};
    float fightScene_zhalan_line = m_visibleOrigin.x + 330;
    
    Vec2 fightScene_tieban_point1 = {m_visibleOrigin.x + 170,m_visibleOrigin.y + 145};
    Vec2 fightScene_tieban_point2 = {m_visibleOrigin.x + 245,m_visibleOrigin.y + 155};
    
    Vec2 fightScene_shadai_point = {m_visibleOrigin.x + 450,m_visibleOrigin.y + 130};
    
    Vec2 fightScene_tengman_point = {m_visibleOrigin.x + 320,m_visibleOrigin.y + 130};
    
    Vec2 fightScene_HouseDeng_Position = {m_visibleOrigin.x + 171 ,m_visibleOrigin.y + 296};
    Vec2 fightScene_HouseSprite_Position = {m_visibleOrigin.x + 155 ,m_visibleOrigin.y + 275};
    Vec2 fightScene_HouseBar_Position = {m_visibleOrigin.x + 300 ,m_visibleOrigin.y + m_visibleSize.height - 50};
    Vec2 fightScene_Gold_Position = {m_visibleOrigin.x + 40 ,m_visibleOrigin.y + m_visibleSize.height - 130};
    Vec2 fightScene_EnemyBar_Position = {m_visibleOrigin.x + m_visibleSize.width - 230 , m_visibleOrigin.y + m_visibleSize.height - 50};
    
    Vec2 fightScene_Bullet_Position = {m_visibleOrigin.x +510 ,m_visibleOrigin.y + m_visibleSize.height - 100};
    Vec2 fightScene_gunIcon_Position = {m_visibleOrigin.x +50 ,m_visibleOrigin.y + 50};
    
    Vec2 fightScene_PropIcon_Position = {m_visibleOrigin.x + m_visibleSize.width -60,m_visibleOrigin.y + m_visibleSize.height - 120};
    
    float fightScene_PropArrve_line = m_visibleOrigin.y + 120;
    
    Vec2 enemy_tanfei_targetPoint = {m_visibleOrigin.x + 1156, m_visibleOrigin.y + 0};
    
    Vec2 welcomeJiangbeiPoint_flash = {m_visibleOrigin.x + 110, m_visibleOrigin.y + 125};
    Vec2 welcomeDengleftPoint_flash = {m_visibleOrigin.x + 172, m_visibleOrigin.y + 480};
    Vec2 welcomeDengrightPoint_flash = {m_visibleOrigin.x + 946, m_visibleOrigin.y + 480};
    Vec2 welcomeDanyanSmokePoint_flash = {m_visibleOrigin.x + 700, m_visibleOrigin.y + 512};
    Vec2 welcomeQiangSmokepoint_flash = {m_visibleOrigin.x + 750, m_visibleOrigin.y + 435};
    Vec2 welcomeZuiSmokePoint_flash = {m_visibleOrigin.x + 897, m_visibleOrigin.y + 248};
    Vec2 welcomeQiangXingSmokePoint_flash = {m_visibleOrigin.x + 768, m_visibleOrigin.y + 230};
    
};

#endif /* defined(__SwampAttack__GameMap__) */
