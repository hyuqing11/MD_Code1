
#include "IntVec.hpp"
IntVec::IntVec(){
    dim = 0;
    val = NULL;
}

IntVec::IntVec(int n){
    if (n <= 0){
        std::cout << "Vector dimension has to be positive" <<std::endl;
    }
    else{
        dim = n;
        val = new int[dim];
        for (int i = 0; i<dim; i++){
            val[i] = 0;
        }
    }
        
}

IntVec::~IntVec()
{    delete[] val;
}

double IntVec::Mag()
{    double m=0.0;
    for(int i=0;i<dim;i++)
        m+=double(val[i]*val[i]);
    return sqrt(m);
}

int IntVec::VProd(){
    int product = val[0];
    for (int i=1; i<dim;i++){
        product *= val[i];
    }
    return product;
}

void IntVec::SetDim(int n)
{    if(n<=0)
    {    printf("Vector dimension has to be positive\n");
        exit(0);
    }
    else if(dim>0)
    {    printf("Vector dimension can't be altered\n");
        exit(0);
    }
    else
    {   dim = n;
        val = new int[dim];
        for(int i=0;i<dim;i++)
            val[i]=0;
    }
}
int IntVec::VLinear(IntVec &v){
    if (dim != 3 || v.dim != 3) {
        std::cerr << "Both vectors must have dimension 3 for VLinear." << std::endl;
        return -1; // Indicate an error
        }
    int c;
    //c = (v.val[2] * val[1] + v.val[1]) * val[0] + v.val[0];
    c = (val[2] * v.val[1] + val[1]) * v.val[0] + val[0];
    return c;
}
int IntVec::GetDim() const
{    return dim;
}

void IntVec::Add(IntVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal int vector addition\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=val[i]+v.val[i];
    }
}

void IntVec::Sub(IntVec &v)
{    if(v.GetDim()!=dim)
    {    printf("Illegal int vector subtraction\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=val[i]-v.val[i];
    }
}

/*RealVec IntVec::Div(RealVec &v){
    RealVec c(dim);
    for (int i = 0; i<dim; i++){
        c.val[i] = double (val[i])/v.val[i];
    }
    return c;
}*/

void IntVec::SetVal(int r)
{    if(dim<=0)
    {    printf("Can't set an empty vector\n");
        exit(0);
    }
    else
    {    for(int i=0;i<dim;i++)
            val[i]=r;
    }
}

void IntVec::SetVal(int x, int y, int z)
{    if(dim<=0)
    {    printf("Can't set an empty vector\n");
        exit(0);
    }
    else
    {    val[0] = x;
        val[1] = y;
        val[2] = z;
    }
}

void IntVec::Zero()
{    SetVal(0);
}

void IntVec::Add(int r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]+r;
}

void IntVec::Sub(int r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]-r;
}

void IntVec::Mul(int r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]*r;
}

void IntVec::Div(int r)
{    for(int i=0;i<dim;i++)
            val[i]=val[i]/r;
}

