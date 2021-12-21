#pragma once

#include "cuckoo_trie.h"

#include "tree_api.h"
#include <iostream>
#include <map>

// used to define the interface of all benchmarking trees
class cc_wrapper : public tree_api {
public:
  cc_wrapper() { my_tree = ct_alloc(40000000); }

  bool insert(const char *key, size_t key_sz, const char *value,
              size_t value_sz) override {
    ct_kv *kv =
        reinterpret_cast<ct_kv *>(malloc(sizeof(ct_kv) + key_sz + value_sz));
    kv->key_size = key_sz;
    kv->value_size = value_sz;
    memcpy(kv->bytes, key, kv->key_size);
    memcpy(kv->bytes + kv->key_size, value, kv->value_size);
    auto ret = ct_insert(my_tree, kv);
    if (ret == S_OK) {
      return true;
    }
    return false;
  }

  bool find(const char *key, size_t sz, char *value_out) override {
    auto ret = ct_lookup(my_tree, sz,
                         reinterpret_cast<uint8_t *>(const_cast<char *>(key)));
    if (ret == NULL) {
      return false;
    }
    memcpy(value_out, ret->bytes + ret->key_size, sizeof(uint64_t));
    return true;
  }

  bool update(const char *key, size_t key_sz, const char *value,
              size_t value_sz) override {
    return true;
  }

  bool remove(const char *key, size_t key_sz) override { return true; }

  int scan(const char *key, size_t key_sz, int scan_sz,
           char *&values_out) override {

    return 0;
  }

private:
  cuckoo_trie *my_tree; // Store the pointer to the tree instance
};