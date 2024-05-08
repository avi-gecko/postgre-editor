#ifndef MODEL_INTERFACE_HPP
#define MODEL_INTERFACE_HPP


class ModelInterface
{
public:
    virtual bool init(const char* from) = 0;
    virtual void add(const char* what, const char* to, const char* table) = 0;
    virtual void edit(const char* what, const char* to, const char* table) = 0;
    virtual void remove(const char* what, const char* table) = 0;
    virtual const char* get(const char* what, const char* table) = 0;

    virtual ~ModelInterface() {}
};


#endif
