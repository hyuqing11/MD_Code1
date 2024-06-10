
#include "ComputerForce.hpp"
const std::array<std::array<int, 3>, ComputerForce::N_OFFSET> ComputerForce::OFFSET_VALS = {{
    {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}, {-1, 1, 0}, {0, 0, 1}, {1, 0, 1}, {1, 1, 1},
    {0, 1, 1}, {-1, 1, 1}, {-1, 0, 1}, {-1, -1, 1}, {0, -1, 1}, {1, -1, 1}
}};

ComputerForce::ComputerForce(Simulator &nmD1){
    x = nmD1.x;
    a = nmD1.a;
    v = nmD1.v;
    rr = 0;
    dim = 3;
    reg.SetDim(3);
    shift.SetDim(3);
    cells.SetDim(3);
    cc.SetDim(3);
    m1v.SetDim(3);
    m2v.SetDim(3);
    rNebrShell = 0.4;
    rCutOff = 2.5;
    rs.SetDim(3);
    
    
    for (int i = 0; i < 3; i++){
        unitCell[i] = nmD1.unitCell[i];
        reg.val[i] = nmD1.reg.val[i];
        cells.val[i] = reg.val[i]/(rCutOff + rNebrShell);
    }
    rrNebr = pow((rCutOff + rNebrShell),2);
    nbrtabFac = 100;
    nbrtabMax = nbrtabFac * nAtom;
    nbrTab = new int(2*nbrtabMax);
    nAtom = nmD1.nAtom;
    invWid.SetDim(3);
    dr.SetDim(3);
    cellList = new int[cells.VProd() + nAtom];
    
}

void ComputerForce::computer_force(){
    BuildNebrList();
    rrCutOff = rCutOff * rCutOff;
    uSum = 0;
    virSum = 0;
    for (int n = 0; n < nbrtabLen; n++){
        int j1 = nbrTab[2 * n];
        int j2 = nbrTab[2 * n + 1];
        rr = 0;
        for (int dId = 0; dId < dim; dId++){
            dr.val[dId] = ApplyBoundaryCondition(x[dId + j1 * dim]-x[dId + j2 *dim], dId);
            rr += dr.val[dId];
        }
        if (rr < rrCutOff){
            r2Inv = 1./rr;
            r6Inv = pow(r2Inv,3);
            f = 48.0 * r6Inv * (r6Inv - 0.5) * r2Inv;
            for (int dId = 0; dId < dim; dId++){
                a[3 * j1 + dId] += f * dr.val[dId];
                a[3 * j2 + dId] -= f * dr.val[dId];
            }
            uSum += 4 * r6Inv * (r6Inv - 1);
            virSum += f * rr;
            
        }
    }
}

double ComputerForce::ApplyBoundaryCondition(double x, int dimId){
    if(x < -(0.5 * reg.val[dimId]))
        return (x + reg.val[dimId]);
    if (x > (0.5 * reg.val[dimId]))
        return (x - reg.val[dimId]);
    return x;
}

void ComputerForce::ApplyBoundaryCondition(IntVec &vec) {
    for (int i = 0; i < 3; ++i) {
        if (vec.val[i] >= cells.val[i]){
            shift.val[i] = reg.val[i];
            vec.val[i] = 0;
        }
        else if (vec.val[i] < 0){
            vec.val[i] = cells.val[i] -1;
            shift.val[i] -= reg.val[i];
        }
    }
}

void ComputerForce::BuildNebrList(){

    for (int dId = 0; dId< dim; dId ++){
        invWid.val[dId] = double(cells.val[dId]) /reg.val[dId];
    }
    for (n = nAtom; n < nAtom + cells.VProd(); n++) {
        cellList[n] = -1;
    }
    
    for (n = 0; n < nAtom; ++n) {
        
        for (int dId = 0; dId < dim; dId++){
            rs.val[dId] = x[3 * n + dId] + 0.5 * reg.val[dId];
            cc.val[dId] = int(rs.val[dId] * invWid.val[dId]);
        }
        c = cc.VLinear(cells);
        
        cellList[n] = cellList[c];
        cellList[c] = n;
    }
    nbrtabLen = 0;
    for (int m1z =0; m1z < cells.val[2]; ++m1z){
        for (int m1y =0; m1y < cells.val[1]; ++m1y){
            for (int m1x =0; m1x < cells.val[0]; ++m1x){
                
                m1v.SetVal(m1x, m1y, m1z);
                m1 = m1v.VLinear(cells) + nAtom;
                for (int offset = 0; offset < N_OFFSET; ++offset){
                   
                    m2v.val[0] = m1v.val[0] + OFFSET_VALS[offset][0];
                    m2v.val[1] = m1v.val[1] + OFFSET_VALS[offset][1];
                    m2v.val[2] = m1v.val[2] + OFFSET_VALS[offset][2];
                    shift.Zero();
                    ApplyBoundaryCondition(m2v);
                    m2 = m2v.VLinear(cells) + nAtom;
                    for (int j1= cellList[m1]; j1 >=0; j1 = cellList[j1]){
                        for (int j2 = cellList[m2]; j2 >= 0; j2 = cellList[j2]) {
                            if(m1 != m2 || j2 < j1) {
                                for (int dId = 0; dId < 3; dId++){
                                    dr.val[dId] = ApplyBoundaryCondition(x[3 * j1 + dId] - x[3 * j2 + dId],dId);
                                    dr.val[dId] = dr.val[dId] - shift.val[dId];
                                }
                                
                                rr = dr.MagSq();
                                    
                                if (rr<rrNebr){
                                    if (nbrtabLen >= nbrtabMax){
                                        std::cout << "Error: Too many neighbors" << std::endl;
                                        exit(1);
                                    }
                                    nbrTab[2 * nbrtabLen] = j1;
                                    nbrTab[2 * nbrtabLen + 1] = j2;
                                    ++nbrtabLen;
                                    
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }


ComputerForce::~ComputerForce(){
    delete [] cellList;
    delete [] nbrTab;
}


