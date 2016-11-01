#

/*
**    Geometric WorkBench
**
**    Copyright (c) 1988
**    Martti Mantyla, Helsinki University of Technology
**
**    This software is NOT released to public domain, but a
**    permission is granted to inspect the code and use it, or
**    portions of it for research or educational purposes, provided
**    that this notice is not removed or modified.  Commercial
**    exploitation is disallowed.
**
**    THE SOFTWARE IS PROVIDED "AS IS" WITH NO WARRANTY OF ANY KIND.
**    THE AUTHOR SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED
**    WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE AND ANY WARRANTY
**    OF MERCHANTABILITY.
*/

# include "gwb.h"

void   matident(m)
matrix m;
{
       m[0][0] = 1.0;  m[0][1] = 0.0;  m[0][2] = 0.0;  m[0][3] = 0.0;
       m[1][0] = 0.0;  m[1][1] = 1.0;  m[1][2] = 0.0;  m[1][3] = 0.0;
       m[2][0] = 0.0;  m[2][1] = 0.0;  m[2][2] = 1.0;  m[2][3] = 0.0;
       m[3][0] = 0.0;  m[3][1] = 0.0;  m[3][2] = 0.0;  m[3][3] = 1.0;
}

void   mattrans(m, tx, ty, tz)
matrix m;
float  tx, ty, tz;
{
       matrix  mt;

       maketrans(mt, tx, ty, tz);
       matmult(m, m, mt);
}

void   matrotat(m, rx, ry, rz)
matrix m;
float  rx, ry, rz;
{
       matrix  mr;

       makerotat(mr, rx, ry, rz);
       matmult(m, m, mr);
}

void   matmult(m, m1, m2)
matrix m, m1, m2;
{
       int     i, j, k;
       matrix  res;

       for(i=0; i<4; i++)
               for(j=0; j<4; j++)
               {
                       res[i][j] = 0.0;
                       for(k=0; k<4; k++)
                               res[i][j] += m1[i][k] * m2[k][j];
               }
       for(i=0; i<4; i++)
               for(j=0; j<4; j++)
                       m[i][j] = res[i][j];
}

void   vecmult(v1, v2, m)
vector v1, v2;
matrix m;
{
       int     i, j;
       vector  res;

       for(i=0; i<4; i++)
       {
               res[i] = 0.0;
               for(j=0; j<4; j++)
                       res[i] += v2[j] * m[i][j];
       }
       for(i=0; i<4; i++)
               v1[i] = res[i];
}

double dot(v1, v2)
vector v1, v2;
{
       return(v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]);
}

void   cross(v1, v2, v3)
vector v1, v2, v3;
{
       vector  res;

       res[0] = v2[1]*v3[2] - v2[2]*v3[1];
       res[1] = v2[2]*v3[0] - v2[0]*v3[2];
       res[2] = v2[0]*v3[1] - v2[1]*v3[0];
       v1[0] = res[0];
       v1[1] = res[1];
       v1[2] = res[2];
}

double normalize(v)
vector v;
{
       double  l;

       l = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
       v[0] /= l;
       v[1] /= l;
       v[2] /= l;
       return(l);
}

void   veccopy(v1, v2)
vector v1, v2;
{
       v1[0] = v2[0];
       v1[1] = v2[1];
       v1[2] = v2[2];
}

void   vecplus(res, v1, v2)
vector res, v1, v2;
{
       res[0] = v1[0] + v2[0];
       res[1] = v1[1] + v2[1];
       res[2] = v1[2] + v2[2];
}

void   vecminus(res, v1, v2)
vector res, v1, v2;
{
       res[0] = v1[0] - v2[0];
       res[1] = v1[1] - v2[1];
       res[2] = v1[2] - v2[2];
}

void   vecnull(v, tol)
vector v;
double tol;
{
       if(comp(v[0], 0.0, tol) == 0 &&
          comp(v[1], 0.0, tol) == 0 &&
          comp(v[2], 0.0, tol) == 0)
               return(1);
       return(0);
}

int    vecequal(v1, v2, tol)
vector v1, v2;
double tol;
{
       vector  tmp;

       vecminus(tmp, v1, v2);
       return(vecnull(tmp, tol));
}

int    comp(a, b, tol)
double a, b, tol;
{
       double  delta;

       delta = fabs(a - b);
       if(delta < tol)         return(0);
       else if(a > b)          return(1);
       else                    return(-1);
}

int    dropcoord(v)
vector v;
{
       double  x, y, z;

       x = fabs(v[0]);
       y = fabs(v[1]);
       z = fabs(v[2]);
       if(x > y)
               if(x > z)
                       return(X);
               else    return(Z);
       else
               if(y > z)
                       return(Y);
               else    return(Z);
}

void   vecprint(v)
vector v;
{
       printf("%f %f %f %f\n", v[0], v[1], v[2], v[3]);
}

void   matprint(m)
matrix m;
{
       printf("%f %f %f %f\n", m[0][0], m[0][1], m[0][2], m[0][3]);
       printf("%f %f %f %f\n", m[1][0], m[1][1], m[1][2], m[1][3]);
       printf("%f %f %f %f\n", m[2][0], m[2][1], m[2][2], m[2][3]);
       printf("%f %f %f %f\n", m[3][0], m[3][1], m[3][2], m[3][3]);
}

void   maketrans(m, tx, ty, tz)
matrix m;
double tx, ty, tz;
{
       matident(m);
       m[3][0] = tx;
       m[3][1] = ty;
       m[3][2] = tz;
}

void   makerotat(m, rx, ry, rz)
matrix m;
float  rx, ry, rz;
{
       matrix  mx, my, mz;

       matident(m);
       makexrotat(mx, rx);
       makeyrotat(my, ry);
       makezrotat(mz, rz);
       matmult(m, m, mx);
       matmult(m, m, my);
       matmult(m, m, mz);
}

void   makezrotat(m, rz)
matrix m;
float  rz;
{
       double  co, si, cos(), sin();

       co = cos(rz/180.0*PI);
       si = sin(rz/180.0*PI);
       matident(m);
       m[0][0] = co;
       m[0][1] = si;
       m[1][0] = -si;
       m[1][1] = co;
}

void   makexrotat(m, rx)
matrix m;
float  rx;
{
       double  co, si, cos(), sin();

       co = cos(rx/180.0*PI);
       si = sin(rx/180.0*PI);
       matident(m);
       m[1][1] = co;
       m[1][2] = si;
       m[2][1] = -si;
       m[2][2] = co;
}

void   makeyrotat(m, ry)
matrix m;
float  ry;
{
       double  co, si, cos(), sin();

       co = cos(ry/180.0*PI);
       si = sin(ry/180.0*PI);
       matident(m);
       m[2][2] = co;
       m[2][0] = si;
       m[0][2] = -si;
       m[0][0] = co;
}
