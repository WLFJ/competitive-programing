#define dcmp(x) (fabs(x) < eps? 0:((x) <0?-1:1))
struct Point{
    double x,y;
    Point(double _x=0,double _y=0):x(_x),y(_y){}
};
typedef Point Vector;

Vector operator + (Vector A,Vector  B){return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (Vector A,Vector B){return Vector(A.x-B.x,A.y-B.y);}
Vector operator * (Vector A,double a){return Vector(a*A.x,a*A.y);}
Vector operator / (Vector A,double p){return A*(1/p);}
bool operator < (const Point  A,const Point  B){return mp(A.x,A.y) < mp(B.x,B.y);}
bool operator == (const Point A,const Point  B){return !dcmp(A.x-B.x) && !dcmp(A.y-B.y);}
double Dot(Vector A, Vector B){return A.x*B.x+A.y*B.y;}
double Length(Vector & A){return sqrt(Dot(A,A));}
double Angle(Vector &A,Vector & B){return acos(Dot(A,B)/Length(A)/Length(B));}
Vector Rotate(Vector &A,double rad){return Vector(A.x*cos(rad)-sin(rad)*A.y,A.x*sin(rad)+A.y*cos(rad));}
Vector Normal(Vector A){//A 的单位法向量
    double L = Length(A);
    return Vector(-A.y/L,A.x/L);
}
double Cross(Vector A,Vector B){return A.x*B.y-A.y*B.x;}
double Area2(Point A,Point B,Point C){return Cross(B-A,C-A);}

Point GetLineIntersection(Point &P,Vector & v, Point & Q,Vector w){
    //计算交点,当v,w平行时无效
    Point u = P-Q;
    double t = Cross(v,u) / Cross(v,w);
    return Q+w*t;
}
double Dis2Line(Point &P,Point & A,Point & B){
    //点p到Ａ,B的距离
    Vector u1 = P-A;
    Vector u2 = B-A;
    return abs(Cross(u1,u2)/Length(u2));
}
Point GetLineProjection(Point &P,Point &A,Point & B){
    //the projection Point Q of P to Line A,B;
    Vector v = B-A;
    return A+ v*(Dot(v,P-A)/Dot(v,v));
}
bool SegInsertion(Point &A1,Point &A2,Point &B1,Point &B2){
    double c1 = Cross(A2-A1,B1-A1),c2 = Cross(A2-A1,B2-A1);
    double c3 = Cross(B2-B1,A1-B1),c4 = Cross(B2-B1,A2-B1);
    return dcmp(c1)*dcmp(c2) <0 && dcmp(c3)*dcmp(c4) <0;
}
bool onSegment(Point & P,Point &A,Point &B){
    return dcmp(Cross(A-P,B-P))==0 && dcmp(Dot(A-P,B-P)) <0;
}

//多边形

double polygonArea(Point *p,int n){
    double area =0;
    for(int i=1 ; i<n-1 ; ++i)
        area += Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}