#include"graphics2.h"
#include<cmath>

class NrComplex
{
public:
    float real,imaginar;
    NrComplex(float r=0,float i=0)
    {
        real=r;
        imaginar=i;
    }
    NrComplex operator+(NrComplex const &obiect)
    {
        NrComplex rezultat;
        rezultat.real=real+obiect.real;
        rezultat.imaginar=imaginar+obiect.imaginar;
        return rezultat;
    }
    NrComplex operator-(NrComplex const &obiect)
    {
        NrComplex rezultat;
        rezultat.real=real-obiect.real;
        rezultat.imaginar=imaginar-obiect.imaginar;
        return rezultat;
    }
    NrComplex operator*(NrComplex const &obiect)
    {
        NrComplex rezultat;
        rezultat.real=real*obiect.real-imaginar*obiect.imaginar;
        rezultat.imaginar=real*obiect.imaginar+imaginar*obiect.real;
        return rezultat;
    }
    NrComplex operator/(NrComplex const &obiect)
    {
        NrComplex rezultat;
        rezultat.real=(real*obiect.real+imaginar*obiect.imaginar)/(obiect.real*obiect.real+obiect.imaginar*obiect.imaginar);
        rezultat.imaginar=(-real*obiect.imaginar+imaginar*obiect.real)/(obiect.real*obiect.real+obiect.imaginar*obiect.imaginar);
        return rezultat;
    }
};
float modulul(NrComplex z)
{
    return sqrt(z.real*z.real+z.imaginar*z.imaginar);
}
NrComplex pow(NrComplex z,int n)
{
    int i;
    NrComplex z1=NrComplex(1,0);
    for(i=0;i<n;i++)
        z1=z1*z;
    return z1;
}
NrComplex f(NrComplex z) //functia
{
    return pow(z,3)-1;
}
NrComplex df(NrComplex z) //derivata functiei de mai sus: f'(z)=(z^3-1)'=3z^2
{
    return z*z*3;
}
void fractal_newton(double dist);
int comparare(NrComplex z);
int iter=100,variatieculoare=2,gd,gm;
int i,j,k;
int X=600,Y=600;
NrComplex z;
NrComplex sol[4] =
{
    NrComplex(0,0),
    NrComplex(-0.5,-sqrt(3)/2),
    NrComplex(-0.5,sqrt(3)/2),
    NrComplex(1,0)
};
int main()
{
    initgraph(&gd,&gm,"",2*X+5,Y);
    fractal_newton(2);
    closegraph();
    return 0;
}
void fractal_newton(double dist)
{
    int culoare;
    setcolor(BLACK);
    setbkcolor(BLACK);
    bar(0,0,2*X+5,Y);
    for(i=0;i<=X;i++)
    {
        for(j=0;j<=Y;j++)
        {
            z=NrComplex(i*2.0*dist/X-dist,-j*2.0*dist/Y+dist);
            for(k=0;k<iter;k++)
            {
                z=z-f(z)/df(z);
                culoare=comparare(z);
                if(culoare)
                    break;
            }
            if(k!=iter)
            {
                putpixel(i,j,5+culoare);
                putpixel(i+5+X,j,1+(k+variatieculoare)%14);
            }
        }
    }
    if(getch())
        fractal_newton(dist/2.0);
}
int comparare(NrComplex z)
{
    int i;
    float precizie=0.0001;
    for(i=1;i<=3;i++)
    {
        NrComplex difereta=z-sol[i];
        if(modulul(difereta)<precizie)
            return i;
    }
    return 0;
}
