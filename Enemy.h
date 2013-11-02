#pragma once
#include <vector>
#include "Framework\Object2D.h"
#include "Framework\Point2D.h"
class Enemy
{
public:
    std::vector<Object2D *> shapes;
    int type;
    Point2D center;
public:
    Enemy();
    ~Enemy();
};

