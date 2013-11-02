#include "Enemy.h"
#include "Framework\Object2D.h"
#include "Framework\Circle2D.h"
#include "Framework\Polygon2D.h"
#include "Framework\Line2D.h"
#include <vector>
#include <random>
#include <ctime>
#include <cmath>

#define PI 3.14159265358979323846
#define inf 1000000

Enemy::Enemy(){
    //Setting random center
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist(1,9);
    rng.seed(clock());
    center.x = dist(rng);
    rng.seed(clock()+center.x);
    center.y = dist(rng);
    while(center.x == center.y && center.x == 5){
        rng.seed(clock());
        center.x = dist(rng);
        rng.seed(clock()+center.x);
        center.y = dist(rng);
    }
    //Setting random type for the enemy
    rng.seed(clock());
    std::uniform_int_distribution<int> dist2(1,5);
    type = dist2(rng);
    //Generating the enemy's shapes
    if (type == 1){

        shapes.push_back(new Circle2D(center,0.3,Color(1,0,0),false));
        //Middle circle
        Circle2D *mc = new Circle2D(Point2D(center.x,center.y),0.08,Color(1,0,0),true);
        shapes.push_back(mc);
        //Main lines
        Line2D *l1 = new Line2D(Point2D(center.x,center.y+0.3),Point2D(center.x,center.y-0.3));
        Line2D *l2 = new Line2D(Point2D(center.x-0.3,center.y),Point2D(center.x+0.3,center.y));
        shapes.push_back(l1);
        shapes.push_back(l2);
        //Main diamond
        Polygon2D *d = new Polygon2D(Color(0,0.5,0),true);
        d->addPoint(Point2D(center.x,center.y+0.3));
        d->addPoint(Point2D(center.x-0.3,center.y));
        d->addPoint(Point2D(center.x,center.y-0.3));
        d->addPoint(Point2D(center.x+0.3,center.y));
        shapes.push_back(d);

    } else if (type == 2){

        shapes.push_back(new Circle2D(center,0.35,Color(0,1,0),false));
        //Middle circle
        Circle2D *mc = new Circle2D(center,0.09,Color(205.0/255,201.0/255,201.0/255),true);
        shapes.push_back(mc);
        //Straight diamond
        Polygon2D *d1 = new Polygon2D(Color(0.5,0,0.5),true);
        d1->addPoint(Point2D(center.x,center.y+0.35));
        d1->addPoint(Point2D(center.x+(0.35/2),center.y));
        d1->addPoint(Point2D(center.x,center.y-0.35));
        d1->addPoint(Point2D(center.x-(0.35/2),center.y));
        shapes.push_back(d1);
        //Horizontal diamond
        Polygon2D *d2 = new Polygon2D(Color(0.5,0,0.5),true);
        d2->addPoint(Point2D(center.x+0.35,center.y));
        d2->addPoint(Point2D(center.x,center.y-(0.35/2)));
        d2->addPoint(Point2D(center.x-0.35,center.y));
        d2->addPoint(Point2D(center.x,center.y+(0.35/2)));
        shapes.push_back(d2);

    } else if (type == 3){

        shapes.push_back(new Circle2D(center,0.4,Color(0,0,1),false));
        //Patrat mijloc
        Polygon2D *c1 = new Polygon2D(Color(0,1,0),false);
        c1->addPoint(Point2D(center.x+(0.4*cos((45*PI)/180))/2,center.y+(0.4*cos((45*PI)/180))/2));
        c1->addPoint(Point2D(center.x+(0.4*cos((45*PI)/180))/2,center.y-(0.4*cos((45*PI)/180))/2));
        c1->addPoint(Point2D(center.x-(0.4*cos((45*PI)/180))/2,center.y-(0.4*cos((45*PI)/180))/2));
        c1->addPoint(Point2D(center.x-(0.4*cos((45*PI)/180))/2,center.y+(0.4*cos((45*PI)/180))/2));
        shapes.push_back(c1);
        //Patrat mare
        Polygon2D *c2 = new Polygon2D(Color(0,1,0),false);
        c2->addPoint(Point2D(center.x+0.4*cos((45*PI)/180),center.y+0.4*cos((45*PI)/180)));
        c2->addPoint(Point2D(center.x+0.4*cos((45*PI)/180),center.y-0.4*cos((45*PI)/180)));
        c2->addPoint(Point2D(center.x-0.4*cos((45*PI)/180),center.y-0.4*cos((45*PI)/180)));
        c2->addPoint(Point2D(center.x-0.4*cos((45*PI)/180),center.y+0.4*cos((45*PI)/180)));
        shapes.push_back(c2);
        //Linii dreapta
        /*
        Polygon2D *l1 = new Polygon2D(Color(1,0,0),false);
        l1->addPoint(Point2D(center.x+(0.4*cos((45*PI)/180))/2,center.y+(0.4*cos((45*PI)/180))/2));
        l1->addPoint(Point2D(center.x+0.4*cos((45*PI)/180),center.y+0.4*cos((45*PI)/180)));
        l1->addPoint(Point2D(center.x+0.4*cos((45*PI)/180),center.y-0.4*cos((45*PI)/180)));
        l1->addPoint(Point2D(center.x+(0.4*cos((45*PI)/180))/2,center.y-(0.4*cos((45*PI)/180))/2));
        shapes.push_back(l1);
        */
        Line2D *l1 = new Line2D(Point2D(center.x+(0.4*cos((45*PI)/180))/2,center.y+(0.4*cos((45*PI)/180))/2),
            Point2D(center.x+0.4*cos((45*PI)/180),center.y+0.4*cos((45*PI)/180)),Color(1,0,0));
        Line2D *l2 = new Line2D(Point2D(center.x+0.4*cos((45*PI)/180),center.y-0.4*cos((45*PI)/180)),
            Point2D(center.x+(0.4*cos((45*PI)/180))/2,center.y-(0.4*cos((45*PI)/180))/2), Color(1,0,0));
        shapes.push_back(l1);
        shapes.push_back(l2);
        //Linii stanga
        Line2D *l3 = new Line2D(Point2D(center.x-(0.4*cos((45*PI)/180))/2,center.y+(0.4*cos((45*PI)/180))/2),
            Point2D(center.x-0.4*cos((45*PI)/180),center.y+0.4*cos((45*PI)/180)),Color(1,0,0));
        Line2D *l4 = new Line2D(Point2D(center.x-0.4*cos((45*PI)/180),center.y-0.4*cos((45*PI)/180)),
            Point2D(center.x-(0.4*cos((45*PI)/180))/2,center.y-(0.4*cos((45*PI)/180))/2), Color(1,0,0));
        shapes.push_back(l3);
        shapes.push_back(l4);

    } else if (type == 4){

        shapes.push_back(new Circle2D(center,0.45,Color(1,1,0),false));
        Polygon2D *c1 = new Polygon2D(Color(1,0,0),false);
        //Patrat stanga jos
        c1->addPoint(center);
        c1->addPoint(Point2D(center.x,center.y-(0.45/2)));
        c1->addPoint(Point2D(center.x-(0.45/2),center.y-(0.45/2)));
        c1->addPoint(Point2D(center.x-(0.45/2),center.y));
        shapes.push_back(c1);
        //Patrat dreapta sus
        Polygon2D *c2 = new Polygon2D(Color(1,0,0),false);
        c2->addPoint(center);
        c2->addPoint(Point2D(center.x+(0.45/2),center.y));
        c2->addPoint(Point2D(center.x+(0.45/2),center.y+(0.45/2)));
        c2->addPoint(Point2D(center.x,center.y+(0.45/2)));
        shapes.push_back(c2);
        //Patrat stanga sus
        Polygon2D *c3 = new Polygon2D(Color(0,0,1),false);
        c3->addPoint(center);
        c3->addPoint(Point2D(center.x,center.y+(0.45/2)));
        c3->addPoint(Point2D(center.x-(0.45/2),center.y+(0.45/2)));
        c3->addPoint(Point2D(center.x-(0.45/2),center.y));
        shapes.push_back(c3);
        //Patrat dreapta jos;
        Polygon2D *c4 = new Polygon2D(Color(0,0,1),false);
        c4->addPoint(center);
        c4->addPoint(Point2D(center.x+(0.45/2),center.y));
        c4->addPoint(Point2D(center.x+(0.45/2),center.y-(0.45/2)));
        c4->addPoint(Point2D(center.x,center.y-(0.45/2)));
        shapes.push_back(c4);
        //Triunghi sus
        Polygon2D *tri1 = new Polygon2D(Color(0,0,0),false);
        tri1->addPoint(Point2D(center.x-(0.45/2),center.y+(0.45/2)));
        tri1->addPoint(Point2D(center.x,center.y+0.45));
        tri1->addPoint(Point2D(center.x+(0.45/2),center.y+(0.45/2)));
        shapes.push_back(tri1);
        //Triunghi jos
        Polygon2D *tri2 = new Polygon2D(Color(0,0,0),false);
        tri2->addPoint(Point2D(center.x-(0.45/2),center.y-(0.45/2)));
        tri2->addPoint(Point2D(center.x,center.y-0.45));
        tri2->addPoint(Point2D(center.x+(0.45/2),center.y-(0.45/2)));
        shapes.push_back(tri2);
        //Triunghi stanga
        Polygon2D *tri3 = new Polygon2D(Color(0,0,0),false);
        tri3->addPoint(Point2D(center.x-(0.45/2),center.y+(0.45/2)));
        tri3->addPoint(Point2D(center.x-0.45,center.y));
        tri3->addPoint(Point2D(center.x-(0.45/2),center.y-(0.45/2)));
        shapes.push_back(tri3);
        //Triunghi dreapta
        Polygon2D *tri4 = new Polygon2D(Color(0,0,0),false);
        tri4->addPoint(Point2D(center.x+(0.45/2),center.y+(0.45/2)));
        tri4->addPoint(Point2D(center.x+0.45,center.y));
        tri4->addPoint(Point2D(center.x+(0.45/2),center.y-(0.45/2)));
        shapes.push_back(tri4);
        //delete c1,c2,c3,c4,tri1,tri2,tri3,tri4;
    } else {

        shapes.push_back(new Circle2D(center,0.5,Color(1,0,1),false));
        //Triunghi dreapta
        Polygon2D *tri1 = new Polygon2D();
        tri1->addPoint(center);
        tri1->addPoint(Point2D(center.x+(0.5*cos(45)),center.y+(0.5*sin(45))));
        tri1->addPoint(Point2D(center.x+(0.5*cos(45)),center.y-(0.5*sin(45))));
        shapes.push_back(tri1);
        //Triunghi stanga
        Polygon2D *tri2 = new Polygon2D();
        tri2->addPoint(center);
        tri2->addPoint(Point2D(center.x-(0.5*cos(45)),center.y+(0.5*sin(45))));
        tri2->addPoint(Point2D(center.x-(0.5*cos(45)),center.y-(0.5*sin(45))));
        shapes.push_back(tri2);
        //Varf sus
        Polygon2D *tri3 = new Polygon2D();
        tri3->addPoint(Point2D(center.x-(0.5*cos(45))/2.0,center.y+(0.5*sin(45))/2.0));
        tri3->addPoint(Point2D(center.x,center.y+0.5));
        tri3->addPoint(Point2D(center.x+(0.5*cos(45))/2.0,center.y+(0.5*sin(45))/2.0));
        tri3->addPoint(center);
        shapes.push_back(tri3);
        //Varf jos
        Polygon2D *tri4 = new Polygon2D();
        tri4->addPoint(Point2D(center.x-(0.5*cos(45))/2.0,center.y-(0.5*sin(45))/2.0));
        tri4->addPoint(Point2D(center.x,center.y-0.5));
        tri4->addPoint(Point2D(center.x+(0.5*cos(45))/2.0,center.y-(0.5*sin(45))/2.0));
        tri4->addPoint(center);
        shapes.push_back(tri4);
        //delete tri1,tri2,tri3,tri4;
    }
}

Enemy::~Enemy(){}
