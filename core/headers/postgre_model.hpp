#ifndef POSTGRE_MODEL_HPP
#define POSTGRE_MODEL_HPP

#include "../headers/model_interface.hpp"


class PostgreModel: public ModelInterface
{
public:
  bool init(const char* from) override;
  void add(const char* what, const char* to, const char* table) override;
  void edit(const char* what, const char* to, const char* table) override;
  void remove(const char* what, const char* table) override;
  const char* get(const char* what, const char* table) override;

};


#endif
