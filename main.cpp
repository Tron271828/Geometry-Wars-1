#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Text.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <cmath>


#define PI 3.14159265358979323846
#define inf 1000000
using namespace std;

Visual2D *v2d1, *v2d2;
Polygon2D *pl_p, *drill;
Circle2D *pl_c;
Text *score_text, *lives_text;
Point2D *center,*live_center;
float p_r, p_t, angle, where_toX, where_toY;
int score, lives = 3, enemy_nr = 7, enemy_count = 0;
bool haveWeapon = false, moveCenterF = false, moveCenterS = false, actCenter = false;


//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(0,0,10,10,0,0,DrawingWindow::width,DrawingWindow::height);
    v2d2 = new Visual2D(0,0,70,10,0,0,DrawingWindow::width,100);
    addVisual2D(v2d2);
	v2d1->tipTran(true);
	addVisual2D(v2d1);

    score_text = new Text(std::string("Score: "),
        Point2D(8,4),Color(0,170.0/255,0),BITMAP_TIMES_ROMAN_24);
    lives_text = new Text(std::string("Lives: "),
        Point2D(50,4),Color(0,170.0/255,0),BITMAP_TIMES_ROMAN_24);

    Player *player = new Player();
    
    pl_c = new Circle2D(Point2D(5,5),0.28,Color(1,0,0),false);
    center = new Point2D(5.0,5.0);
    live_center = new Point2D(5.0,5.0);

    pl_p = new Polygon2D(Color(0,0,1),false);
    pl_p->addPoint(Point2D(5.15,4.81));
    pl_p->addPoint(Point2D(5.15,4.9));
    pl_p->addPoint(Point2D(4.9,5));
    pl_p->addPoint(Point2D(5.15,5.1));
    pl_p->addPoint(Point2D(5.15,5.19));
    pl_p->addPoint(Point2D(4.77,5));

    addObject2D_to_Visual2D(pl_p,v2d1);
    addObject2D_to_Visual2D(pl_c,v2d1);

    drill = new Polygon2D(Color(8/255.0,74/255.0,14/255.0),true);
    drill->addPoint(Point2D(5.3,4.84));
    drill->addPoint(Point2D(5.65,5));
    drill->addPoint(Point2D(5.3,5.16));
    
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch(key)
	{
    case KEY_SPACE: 
        if(haveWeapon){
            std::cout<<"Arma inactiva\n";
            removeObject2D_from_Visual2D(drill,v2d1);
            haveWeapon = false;
            break;
        } else {
            std::cout<<"Arma activa\n";
            addObject2D_to_Visual2D(drill,v2d1);
            haveWeapon = true;
            break;
        }
    case KEY_RIGHT:
        if(haveWeapon){
            p_r-=2.0;
        } else {
            p_r-=3.0;
        }
        actCenter = true;
        break;
    case KEY_LEFT:
        if(haveWeapon){
            p_r+=2.0;
        } else {
            p_r+=3.0;
        }
        actCenter = true;
        break;
    case KEY_UP:
        where_toX = live_center->x + (p_t+0.08)*(cos(angle)) + 0.65;
        where_toY = live_center->y + (p_t+0.08)*(sin(angle)) + 0.65;
        if((where_toX < 10.0) && (where_toX > 1.0) &&
                (where_toY < 10.0) && (where_toY > 1.0)){
            if(haveWeapon){
                p_t+=0.05;
                moveCenterS = true;
            } else {
                p_t+=0.08;
                moveCenterF = true;
            }
        }
        break;
    case 'a':
        std::cout<<angle<<"\n";
        std::cout<<"Cos("<<angle<<"): "<<cos(angle)<<"\n";
        std::cout<<"Sin("<<angle<<"): "<<sin(angle)<<"\n";
    
    case 'q':
        std::cout<<where_toX<<" : "<<where_toY<<"\n";
    }
}


//functia care permite animatia
void DrawingWindow::onIdle()
{ 
    //score & lives display
    if (score_text->getText() != std::string("Score: ")+std::to_string(score)){
        score_text->setText(std::string("Score: ")+std::to_string(score));
        removeText_from_Visual2D(score_text,v2d2);
        addText_to_Visual2D(score_text,v2d2);
    }
    if (lives_text->getText() != std::string("Lives: ")+std::to_string(lives)){
        lives_text->setText(std::string("Lives: ")+std::to_string(lives));
        if (lives >= 3){
            lives_text->setColor(Color(0,170.0/255,0));
        } else if (lives == 2){
            lives_text->setColor(Color(1,0.7,0));
        } else if (lives == 1){
            lives_text->setColor(Color(1,0,0));
        } else {
            lives_text->setColor(Color(0,0,0));
        }
        removeText_from_Visual2D(lives_text,v2d2);
        addText_to_Visual2D(lives_text,v2d2);
    }
    //Add enemies on the field
    /*
    while(enemy_count < enemy_nr){
        Enemy e = Enemy();
        for(int i = 0; i < e.shapes.size(); i++){
            if(i != 0 || e.type == 3)
                addObject2D_to_Visual2D(e.shapes[i],v2d1);
        }
        std::cout<<"Spawned enemy at: "<<e.center.x<<" "<<e.center.y<<" of type "<<e.type<<"\n";
        enemy_count++;
    }
    */
    //Player movements & rotation


    angle = (p_r*PI)/180.0;
    if (angle > 2 * PI){
        angle = 0.0;
        p_r = 0.0;
    } else if (angle < (-2)*PI){
        angle = 0.0;
        p_r = 0;
    } 
    if (angle < 0 )
        angle = 2*PI + angle;
    //Actualizare obiecte player
    if(actCenter){
        live_center->x = center->x;
        live_center->y = center->y;
        removeObject2D_from_Visual2D(pl_c,v2d1);
        removeObject2D_from_Visual2D(pl_p,v2d1);
        removeObject2D_from_Visual2D(drill,v2d1);
        delete pl_c,pl_p,drill;
        pl_c = new Circle2D(Point2D(live_center->x,live_center->y),0.28,Color(1,0,0),false);
        drill = new Polygon2D(Color(8/255.0,74/255.0,14/255.0),true);
        drill->addPoint(Point2D(live_center->x+0.3,live_center->y-0.16));
        drill->addPoint(Point2D(live_center->x+0.65,live_center->y));
        drill->addPoint(Point2D(live_center->x+0.3,live_center->y+0.16));

        pl_p = new Polygon2D(Color(0,0,1),false);
        pl_p->addPoint(Point2D(live_center->x+0.15,live_center->y-0.19));
        pl_p->addPoint(Point2D(live_center->x+0.15,live_center->y-0.1));
        pl_p->addPoint(Point2D(live_center->x-0.1,live_center->y));
        pl_p->addPoint(Point2D(live_center->x+0.15,live_center->y+0.1));
        pl_p->addPoint(Point2D(live_center->x+0.15,live_center->y+0.19));
        pl_p->addPoint(Point2D(live_center->x-0.23,live_center->y));
        if(haveWeapon == true){
            addObject2D_to_Visual2D(drill,v2d1);
        }
        addObject2D_to_Visual2D(pl_c,v2d1);
        addObject2D_to_Visual2D(pl_p,v2d1);

        p_t = 0.0;
        actCenter = false;
    }
    //Rotire player
    Transform2D::loadIdentityMatrix();
    Transform2D::translateMatrix(-live_center->x,-live_center->y);
    Transform2D::rotateMatrix(angle);
    Transform2D::translateMatrix(live_center->x,live_center->y);
    //Miscare player
    Transform2D::translateMatrix(p_t*(cos(angle)),p_t*sin(angle));
    //Aplicare matrici
    Transform2D::applyTransform(pl_c);
    Transform2D::applyTransform(pl_p);
    Transform2D::applyTransform(drill);
    //Recalculare centru player
    if (moveCenterF){
        center->x += 0.08*(cos(angle));
        center->y += 0.08*(sin(angle));
        moveCenterF = false;
    }
    if (moveCenterS){
        center->x += 0.05*(cos(angle));
        center->y += 0.05*(sin(angle));
        moveCenterS = false;
    }

}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	
	v2d1->poarta(0,0,width,height); 
	

}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	

}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 700, 700, 300, 20, "Laborator EGC");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}