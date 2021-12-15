#include "cc_wrapper.hpp"

extern "C" __attribute__((visibility("default"))) void *create_tree() {
  return reinterpret_cast<void *>(new cc_wrapper<string_key *, char *>());
}