
#include "ReadInput.hpp"

ReadInput::ReadInput(const char Fname[])
{
    std::strcpy(inpFname, Fname);
    nAtomsSA = 0;
    nTypesSA = 0;
    dtSA = 0.0f;
    nAtoms = 0;
    dim = 0;
    massSA = NULL;
    density = 0.;
    temp = 0.;
    nLimit = 0;
}

// Implement other member functions here
void ReadInput::SetEvalParameters(int nEval, int nLimit){
    if(nEval<=0)
        {    printf("Error: projection evaluation step frequency has to be positive\n");
            exit(0);
        }
        else
            this->nEval = nEval;

        if(nLimit<=0)
        {    printf("Error: time step limit has to be positvie\n");
            exit(0);
        }
        else
            this->nLimit = nLimit;
    }

void ReadInput::ReadParameterFile(){
    rf.Open(inpFname);
    if (!rf.IsOpen())
    {
        std::cerr << "Error: The input file was not found." << std::endl;
        exit(1);
    }
    std::cout << "*********************nput File**********************" << std::endl;
    GetNextLine(2, "Num_Atom");
    nAtomsSA = atoi(rf.argsList[1].c_str());
    std::cout << "Number of atoms: " <<nAtomsSA << std::endl;
    
    GetNextLine(2, "Atom_Types");
    nTypesSA = atoi(rf.argsList[1].c_str());
    std::cout << "Number of atom types: " <<nTypesSA << std::endl;
    
    GetNextLine(2, "delta_t");
    dtSA = atof(rf.argsList[1].c_str());
    std::cout << "Delta t: " <<dtSA << std::endl;
    
    massSA = new double[nTypesSA];
    GetNextLine(nTypesSA + 1, "Mass");
    printf("Masses: ");
    for(int i = 0; i < nTypesSA; i++)
    {    massSA[i] = atof(rf.argsList[i + 1].c_str());
        std::cout <<"Type " << i + 1 << massSA[i] << " ";
    }
    std::cout<<std::endl;
    
    GetNextLine(2, "Total_Step_Limit");
    nLimit = atoi(rf.argsList[1].c_str());
    printf("Total step limit: %d \n", nLimit);
    
    GetNextLine(2, "Evaluation_Frequency");
    nEval = atoi(rf.argsList[1].c_str());
    printf("Evaluation frequency set at: %d \n", nEval);
    
    GetNextLine(2, "density");
    density = atof(rf.argsList[1].c_str());
    printf("Density of the system : %f \n", density);
    GetNextLine(2, "temperature");
    temp = atof(rf.argsList[1].c_str());
    printf("Temperature: %f \n", temp);
    GetNextLine(2, "dimension");
    dim = atoi(rf.argsList[1].c_str());
}

void ReadInput::GetNextLine(int numArgs, std::string keyWord){
    GetNextLine(numArgs);
    if (rf.argsList[0] != keyWord)
    {
        std::cerr << "Incorrect format for input file: Expected Key Word: " << keyWord << std::endl;
        exit(1);
    }
}

void ReadInput::GetNextLine(int numArgs)
{    GetNextLine();
    if (numArgs != rf.SplitArguments())
    {
        std::cerr << "Incorrect format for input file: " << numArgs << " input arguments expected." << std::endl;
        exit(1);
    }
}

void ReadInput::GetNextLine()
{    rf.ReadNextLine();
    if (!rf.IsActiveLine())
    {
        std::cerr << "Error: Not enough information in normal mode input file!" << std::endl;
        exit(1);
    }
}

int ReadInput::GetNAtoms()
{    return nAtoms;
}

int ReadInput::GetNAtomsSA()
{    return nAtomsSA;
}

int ReadInput::GetNTypesSA()
{    return nTypesSA;
}

double ReadInput::GetMassSA(int id)
{    return massSA[id];
}

int ReadInput::GetDim()
{    return dim;
}

double ReadInput::GetdtSA()
{    return dtSA;
}

double ReadInput::Gettemp(){
    return temp;
}

int ReadInput::GetNLimit(){
    return nLimit;
}

double ReadInput::Getdensity(){
    return density;
}
