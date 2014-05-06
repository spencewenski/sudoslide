#ifndef MODEL_H
#define MODEL_H 1

#include <string>
#include <map>
#include <memory>

class Board;

class Model {
public:
  static Model& get_instance();
private:
  using Board_ptr_t = std::shared_ptr<Board>;
  using Board_map_t = std::map<int, Board_ptr_t>;

  Board_map_t boards;

  Model();
  ~Model();
  Model(const Model&) = delete;
  Model& operator=(const Model&) = delete;
  Model(Model&&) = delete;
  Model& operator=(Model&&) = delete;
};

#endif /*MODEL_H*/