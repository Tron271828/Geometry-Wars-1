#pragma once
#include "Framework\Circle2D.h"
#include "Framework\Point2D.h"
#include "Framework\Polygon2D.h"

class Player{

public:
    Circle2D *pl_c;
    Polygon2D *pl_p;
    Polygon2D *drill;
    Point2D *center, *live_center;
    float angle;
public:
    Player(float centerX, float centerY);
    void transform(float ang, float p_t);
    ~Player(void);
};

