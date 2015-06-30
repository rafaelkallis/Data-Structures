/*
    exceptions.h
    Created by Rafael Kallis
    Copyright (c) 2015 Rafael Kallis. All rights reserved.
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

/* Used when an ADT is empty */
struct EmptyADTException: public std::exception{
	
};


/* Used when trying to access an element with invalid index */
struct OutofBoundsException:public std::exception{
    
};


/* Used if Memory Reallocation was unsuccesful */
struct ReallocException:public std::exception{
    
};


/* General Exception */
struct UncaughtException:public std::exception{
    
};

#endif /* EXCEPTIONS_H */