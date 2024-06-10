
#include "RealVec.hpp"
RealVec::RealVec()
{    dim = 0;
    val = NULL;
}
RealVec::RealVec(int n)
{    if(n<=0)
    {    printf("Vector dimension has to be positive\n");
        exit(0);
    }
    else
    {    dim = n;
        val = new double[dim];
        for(int i=0;i<dim;i++)
            val[i]=0.0;
    }
}

RealVec::~RealVec()
{    delete [] val;
}

void RealVec::SetDim(int n)
{    if(n<=0)
    {    printf("Vector dimension has to be positive\n");
        exit(0);
    }
    else if(dim>0)
    {    printf("Vector dimension can't be altered\n");
        exit(0);
    }
    else
    {    dim = n;
        val = new double[dim];
        for(int i=0;i<dim;i++)
            val[i]=0.0;
    }
}

int RealVec::GetDim() const
{    return dim;
}

double RealVec::Mag()
{    double m=0.0;
    for(int i=0;i<dim;i++)
        m+=val[i]*val[i];
    return sqrt(m);
}

double RealVec::MagSq()
{    double m=0.0;
    for(int i=0;i<dim;i++)
        m+=val[i]*val[i];
    return m;
}

double RealVec::Dot(RealVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector dot product\n");
        exit(0);
    }
    else
    {    double m=0.0;
        for(int i=0;i<dim;i++)
            m+=val[i]*v.val[i];
        return m;
    }
}

double RealVec::Dot(IntVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector dot product\n");
        exit(0);
    }
    else
    {    double m=0.0;
        for(int i=0;i<dim;i++)
            m+=val[i]*double(v.val[i]);
        return m;
    }
}

void RealVec::Copy(RealVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector copy\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=v.val[i];
    }
}

void RealVec::Copy(IntVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector copy\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=double(v.val[i]);
    }
}

void RealVec::SetVal(double r)
{    if(dim<=0)
    {    printf("Can't set an empty vector\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=r;
    }
}

void RealVec::SetVal(int r)
{    if(dim<=0)
    {    printf("Can't set an empty vector\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=double(r);
    }
}

void RealVec::Zero()
{    SetVal(0.0);
}

void RealVec::Normalize()
{    double m = Mag();
    for(int i=0;i<dim;i++)
        val[i]=val[i]/m;
}


void RealVec::Add(RealVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector addition\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=val[i]+v.val[i];
    }
}

void RealVec::Sub(RealVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector subtraction\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=val[i]-v.val[i];
    }
}

void RealVec::MulComps(RealVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector component multiplication\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=val[i]*v.val[i];
    }
}

void RealVec::DivComps(RealVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector component division\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=val[i]/v.val[i];
    }
}

void RealVec::Add(IntVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector addition\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=val[i]+double(v.val[i]);
    }
}

void RealVec::Sub(IntVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector subtraction\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=val[i]-double(v.val[i]);
    }
}

void RealVec::MulComps(IntVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector component multiplication\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=val[i]*double(v.val[i]);
    }
}

void RealVec::DivComps(IntVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal real vector component division\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=val[i]/double(v.val[i]);
    }
}

void RealVec::Add(double r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]+r;
}

void RealVec::Sub(double r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]-r;
}

void RealVec::Mul(double r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]*r;
}

void RealVec::Div(double r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]/r;
}

void RealVec::Add(int r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]+double(r);
}

void RealVec::Sub(int r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]-double(r);
}

void RealVec::Mul(int r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]*double(r);
}

void RealVec::Div(int r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]/double(r);
}

IntVec RealVec::Mul(RealVec &v){
    IntVec c(dim);
    for (int i = 0; i<dim; i++){
        c.val[i] = int(val[i] * v.val[i]);
     }
    return c;
}
