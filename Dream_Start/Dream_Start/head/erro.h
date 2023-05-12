#pragma once
#include <iostream>
#include <exception>


using namespace std;
class MyClaMyExceptionss: public exception

    

{
public:
    MyClaMyExceptionss();
	~MyClaMyExceptionss();

    const char* toSing() throw()
    {
        return "C++ Exception";
    }
	

private:

};

MyClaMyExceptionss::MyClaMyExceptionss()
{
    
}

MyClaMyExceptionss::~MyClaMyExceptionss()
{
}