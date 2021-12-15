#include "cc_wrapper.hpp"

extern "C" void *create_tree() {
  return reinterpret_cast<void *>(new cc_wrapper<string_key *, char *>());
}
