#include "Player.h"
#include "Framework\Transform2D.h"

Player::Player(float centerX, float centerY){

    pl_c = new Circle2D(Point2D(centerX,centerY),0.28,Color(1,0,0),false);
    drill = new Polygon2D(Color(8/255.0,74/255.0,14/255.0),true);
    drill->addPoint(Point2D(centerX+0.3,centerY-0.16));
    drill->addPoint(Point2D(centerX+0.65,centerY));
    drill->addPoint(Point2D(centerX+0.3,centerY+0.16));

    pl_p = new Polygon2D(Color(0,0,1),false);
    pl_p->addPoint(Point2D(centerX+0.15,centerY-0.19));
    pl_p->addPoint(Point2D(centerX+0.15,centerY-0.1));
    pl_p->addPoint(Point2D(centerX-0.1,centerY));
    pl_p->addPoint(Point2D(centerX+0.15,centerY+0.1));
    pl_p->addPoint(Point2D(centerX+0.15,centerY+0.19));
    pl_p->addPoint(Point2D(centerX-0.23,centerY));

}

void Player::transform(float ang, float p_t){
    //Rotire
    Transform2D::loadIdentityMatrix();
    Transform2D::translateMatrix(-live_center->x,-live_center->y);
    Transform2D::rotateMatrix(ang);
    Transform2D::translateMatrix(live_center->x,live_center->y);
    //Miscare
    Transform2D::translateMatrix(p_t*(cos(angle)),p_t*sin(angle));
    //Aplicare pe componente
    Transform2D::applyTransform(pl_c);
    Transform2D::applyTransform(pl_p);
    Transform2D::applyTransform(drill);

}
Player::~Player(void)
{
}
