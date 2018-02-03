/*************************************************************************
	> File Name: temp.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年12月05日 星期二 15时13分04秒
 ************************************************************************/

#include<iostream>
using namespace std;

int extendEuclidean(long int a,long int p);

typedef struct p{
    long int x;
    long int y;
}P;

P add(P *p1,P *p2,long int p)
{
    P pr;
    int deltax,
        deltay,
        lambda,
        tmpvar;

    if (p1->y + p2->y == 0) {
        pr.x = pr.y =0;    
    }
    else if (p1->y - p2->y == 0) {
        tmpvar = extendEuclidean(2*p1->y,p);
        lambda = (((3*(p1->x*p1->x) + 3) * tmpvar) % p + p) % p;
        pr.x = ((lambda*lambda  - p1->x - p2->x) % p + p) % p;
        pr.y = ((lambda*(p1->x-pr.x) - p1->y) % p + p) % p;
    }
    else {
        deltax = p2->x - p1->x;
        deltay = p2->y - p1->y;
        tmpvar = extendEuclidean(deltax,p);
        lambda = ((deltay * tmpvar) % p + p) % p;
        pr.x = ((lambda*lambda - p1->x - p2->x) % p + p) % p;
        pr.y = ((lambda*(p1->x-pr.x) - p1->y) % p + p) % p;
    }
    return pr;
}

P multiplyK(P *p1,long int k,long int p)
{
    P pr,tmpvar;
    tmpvar = *p1;
    pr.x = pr.y = 0;
    while(k != 0) {
        if (k&1) {
            if (pr.x==0&&pr.y==0) {
                pr = tmpvar;
            }
            else {
                pr = add(&pr,&tmpvar,p);
            }
        }
        tmpvar = add(&tmpvar,&tmpvar,p);
        k = k >> 1;
    }
    return pr;
}

int main(int argv,char *args[])
{
    long int p = 2017,k;
    P p1,p2,pr,tmpvar;
    cout << "➤椭圆曲线简单求解" << endl;
    cout << "➤输入点p1的x,y;p2的x,y,求p3=p1+p2" << endl;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    pr = add(&p1,&p2,p);
    cout << pr.x << " " << pr.y << endl;
    
    cout << "➤输入点p1的x,y,以及乘法次数k,求k*p1" << endl;
    cin >> p1.x >> p1.y >> k ;
    pr = multiplyK(&p1,k,p);
    cout << pr.x << " " << pr.y << endl;

    return 0;
}

