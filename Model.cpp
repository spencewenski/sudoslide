#include "Model.h"

Model& Model::get_instance()
{
  static Model model;
  return model;
}