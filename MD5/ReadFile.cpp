//
//  ReadFile.cpp
//  MD_Code
//
//  Created by 黄宇青 on 6/8/24.
//

#include "ReadFile.hpp"

ReadFile::ReadFile()
{    isOpen = 0;
    activeLine = 0;
    numArgs = 0;
    skipCommentLines = 1;
    skipCommentTest = 0;
    delims = " \t" ;
    commentKey = '#';
}

ReadFile::ReadFile(std::string fName)
{    this->fName = fName;
    fp.open(fName.c_str(), std::ios::in);
    
    if(fp.is_open())
        isOpen = 1;
    activeLine = 0;
    numArgs = 0;
    skipCommentLines = 1;
    skipCommentTest = 0;
    delims = " \t";
    commentKey = '#';
}


ReadFile::~ReadFile()
{
}


void ReadFile::Open(std::string fName)
{    if(isOpen == 1)
    {    printf("Error\n");
    }
    else
    {    this->fName = fName;
        fp.open(fName.c_str(), std::ios::in);
    
        if(fp.is_open())
            isOpen = 1;
    }
}

void ReadFile::EditDelims(std::string delims)
{    this->delims = delims;
}

void ReadFile::EditCommentKey(char commentKey)
{    this->commentKey = commentKey;
}

void ReadFile::Close()
{    if(isOpen == 1)
    {    fp.close();
        isOpen = 0;
        activeLine = 0;
        numArgs = 0;
    }

}

int ReadFile::IsActiveLine()
{    return activeLine;
}

int ReadFile::IsOpen()
{    return isOpen;
}

int ReadFile::IsEof()
{    if(isOpen == 0)
        return 1;
    return fp.eof();
}

void ReadFile::ReadNextLine()
{    activeLine = 0;
    if(isOpen == 1)
    {    if(fp.eof())
            Close();
        else
        {    while(!fp.eof())
            {    std::getline(fp, line);
                if(line.length() != 0)
                {     if(RemoveLeadingTrailingBlankSpaces())
                    {    if((IsComment() == 0) || (skipCommentLines == 0))
                        {    activeLine = 1;
                            break;
                        }
                    }
                
                }
            }
        }
    }
    else
        printf("Error reading next line, file not open \n");
}


int ReadFile::RemoveLeadingTrailingBlankSpaces()
{    int posStart, posEnd, len;

    len = line.length();
    
    posStart = line.find_first_not_of(delims);
    posEnd = line.find_last_not_of(delims);

    if (posStart < 0)
        return 0;

    line = line.substr(posStart, (posEnd - posStart) + 1);
    return 1;
}

//int ReadFile::RemoveLeadingBlankSpaces()
//{    int posStart, len;
//
//    len = temp.length();
//
//    posStart = line.find_first_not_of(delims);
//
//    if (posStart < 0)
//        return 0;
//
//    line = line.substr(posStart, (len - posStart));
//    return 1;
//}

int ReadFile::ExtractWord()
{    int pos, len;
    std::string temp2;

    len = temp.length();

    if (len == 0)
        return -1;

    word.clear();
    pos = temp.find_first_of(delims);

    if (pos < 0)
    {    word = temp;
        return 0;
    }

    word = temp.substr(0, pos);
    temp2 = temp.substr(pos, (len - pos));

    len = temp2.length();
    pos = temp2.find_first_not_of(delims);
    temp.clear();
    temp = temp2.substr(pos, (len - pos));

    return 1;

}

int ReadFile::SplitArguments()
{    numArgs = 0;
    int res;
    
    if (activeLine > 0)
    {    argsList.clear();
        temp = line;
        while(1)
        {    res = ExtractWord();
            if(res > 0)
            {    argsList.push_back(word);
                numArgs++;
            }
            else if (res == 0)
            {    argsList.push_back(word);
                numArgs++;
                break;
            }
            else
                break;
        }
        
    }
    return numArgs;
}

int ReadFile::IsComment(std::string s)
{    if(s[0] == commentKey)
        return 1;
    return 0;
}

int ReadFile::IsComment()
{    return IsComment(line);
}

void ReadFile::SkipComments()
{    skipCommentLines = 1;
}

void ReadFile::IncludeComments()
{    skipCommentLines = 0;
}

int ReadFile::GetNumArgs()
{    return numArgs;
}
