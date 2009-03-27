#pragma once

template<class C>
class Singleton
{
private: 
    // Static current instance
    static C* CurrentInstance;
 
public:
    // Current instance getter
    static C* Current()
    {
        if(Singleton<C>::CurrentInstance == NULL)
        {
            Singleton<C>::CurrentInstance = new C;
        }
        return Singleton<C>::CurrentInstance;
    }
 
    // Delete current instance
    static void DeleteCurrent()
    {
        if(Singleton<C>::CurrentInstance != NULL)
        {
            delete Singleton<C>::CurrentInstance;
            Singleton<C>::CurrentInstance = NULL;
        }
    }
};
 
// Initialize the static member CurrentInstance
template< class C >
C* Singleton<C>::CurrentInstance = NULL;

