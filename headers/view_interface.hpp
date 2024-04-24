#ifndef VIEW_INTERFACE_HPP
#define VIEW_INTERFACE_HPP


class ViewInterface
{
public:
  virtual void init_command() = 0;
  
  virtual void add_command() = 0;
  virtual void add_directory_command() = 0;
  
  virtual void edit_command() = 0;
  virtual void edit_directory_command() = 0;
  
  virtual void delete_command() = 0;
  virtual void delete_directory_command() = 0;
  
  virtual void get_command() = 0;
  virtual void get_directory() = 0;
  
  virtual void handle_command() = 0;
  
  virtual ~ViewInterface() {};
};

#endif
