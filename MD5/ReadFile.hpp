

#ifndef ReadFile_hpp
#define ReadFile_hpp

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

class ReadFile
{    private:
    std::ifstream fp;
    int isOpen, activeLine, numArgs, skipCommentLines, skipCommentTest;
    std::string fName, delims;
    char commentKey;

    int RemoveLeadingTrailingBlankSpaces();
    //int RemoveLeadingBlankSpaces();
    int ExtractWord();
    int IsComment(std::string s);
    
    

    public:

    
    std::vector<std::string> argsList;
    std::string line, word, temp;
    
    


    ReadFile();
    ReadFile(std::string fName);
    
    ~ReadFile();
    
    
    void ReadNextLine();
    int SplitArguments();
    void Open(std::string fName);
    void EditDelims(std::string delims);
    void EditCommentKey(char commentKey);
    void Close();
    void SkipComments();
    void IncludeComments();

    int IsActiveLine();
    int IsOpen();
    int IsEof();
    int IsComment();
    int GetNumArgs();
    
    
    
};

#endif /* ReadFile_hpp */
