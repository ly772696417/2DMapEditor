#pragma once 

#include "stdafx.h"
#include "stdlib.h"

template<class T>
class SingletonHolder
{
public:
	static T& Instance();

private:
	SingletonHolder(void) {};	
	~SingletonHolder(void) {};

	static T* s_pInst;
	static void DestroySingleton();
};

// Static variable initialize.
template<class T>
T* SingletonHolder<T>::s_pInst = NULL;

template<class T>
T& SingletonHolder<T>::Instance() 
{
	if ( s_pInst==NULL ) {
		s_pInst = new T();
		// the destructor resgister.
		atexit( SingletonHolder<T>::DestroySingleton );
	}
	return *s_pInst;
}

template<class T>
void SingletonHolder<T>::DestroySingleton()
{
	if ( s_pInst!=NULL ) {
		delete s_pInst;
		s_pInst = NULL;
	}
}