#pragma once

#include "Sprite.h"
#include "Easing.h"

typedef struct
{
    Easing::EasingFunction Function;
    double X;
    double Y;
    double Z;
    double Extra1;
    double Extra2;
    double Extra3;
    double Wait;
    double Now;
    double Duration;
} Mover;

class SpriteManager final
{

private:
    std::list<std::tuple<std::shared_ptr<Sprite>, Mover*, std::function<bool(std::shared_ptr<Sprite>, Mover&, double)>>> movers;
    static std::unordered_map<std::string, std::function<bool(std::shared_ptr<Sprite>, Mover&, double)>> actions;
    
    static boost::xpressive::sregex srmove;
    static boost::xpressive::sregex srparam;

public:
    SpriteManager();
    void AddMove(std::shared_ptr<Sprite> sprite, std::string move);
    

    void Tick(double delta);

    //delta > 0 : 動作
    //delta == 0 : Mover初期化
    //delta == -1 : 終了(位置確定などにどうぞ)
    //true返せば逸でも中段できる

    static bool ActionMoveTo(std::shared_ptr<Sprite> target, Mover &mover, double delta);
    static bool ActionMoveBy(std::shared_ptr<Sprite> target, Mover &mover, double delta);
    static bool ActionAlpha(std::shared_ptr<Sprite> target, Mover &mover, double delta);

    //Script版でも使用
    static std::unordered_map <std::string, Easing::EasingFunction> easings;
    static std::string ParseMover(Mover* mover, std::string move);
    static std::tuple<std::string, std::vector<std::tuple<std::string, std::string>>> ParseRaw(const std::string &move);
    static bool CheckPattern(std::string move);
};

