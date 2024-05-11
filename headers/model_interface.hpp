#ifndef MODEL_INTERFACE_HPP
#define MODEL_INTERFACE_HPP

#include "view_interface.hpp"

class ModelInterface
{
public:
    virtual bool init(const char* from) = 0;
    virtual void add(const char* what, const char* to, const char* table) = 0;
    virtual void edit(const char* what, const char* to, const char* table) = 0;
    virtual bool remove(const char* what, const char* table) = 0;
    virtual const char* get(const char* what, const char* table) = 0;

    virtual ~ModelInterface() {}
};


#endif
