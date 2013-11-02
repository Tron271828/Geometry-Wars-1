#pragma once
#include "./Framework/Object2D.h"
class Player2D :
    public Object2D{

public:
    vector<Object2D*> to_be_drawn;

public:
    Player2D();
    Player2D(Point2D,float);
    ~Player2D(void);
};

