#pragma once

#include "cuckoo_trie_internal.h"

#include "random.h"

#include "util.h"

#include "tree.h"
#include <iostream>
#include <map>

// used to define the interface of all benchmarking trees
template <class T, class P> class art_wrapper : public Tree<T, P> {
public:
  typedef std::pair<T, P> V;

  art_wrapper() { my_tree = ct_alloc(40000000); }

  void bulk_load(const V bulk_arr[], int num) {
    for (int i = 0; i < num; ++i) {
      ct_kv *kv = malloc(sizeof(ct_kv) + bulk_arr[i].first->length +
                         sizeof(bulk_arr[i].second));
      kv->key_size = bulk_arr[i].first->length;
      kv->value_size = sizeof(bulk_arr[i].second);
      memcpy(kv->bytes, bulk_arr[i].first->key, kv->key_size);
      memcpy(kv->bytes + kv->key_size, &(bulk_arr[i].second), kv->value_size);
      ct_insert(my_tree, kv);
    }
  }

  bool insert(const T &key, const P &payload) {
    if constexpr (std::is_pointer_v<T>) {
      ct_kv *kv = malloc(sizeof(ct_kv) + key->length + sizeof(payload));
      kv->key_size = key->length;
      kv->value_size = sizeof(payload);
      memcpy(kv->bytes, kv->key, kv->key_size);
      memcpy(kv->bytes + kv->key_size, &(payload), kv->value_size);
      auto ret = ct_insert(my_tree, kv);
      if (ret == S_OK) {
        return true;
      }
      return false;
    } else {
      // LOG_FATAL("The key must be string key in HOT!");
      std::cout << "The key must be string key in HOT!" << std::endl;
      exit(-1);
    }
  }

  bool search(const T &key, P *payload) const {
    if constexpr (std::is_pointer_v<T>) {
      auto ret = ct_lookup(my_tree, key->length, key->key);
      if (ret == NULL) {
        return false;
      }
      *payload = *reinterpret_cast<P *>(ret->bytes + ret->key_size);
      return true;
    } else {
      // LOG_FATAL("The key must be string key in HOT!");
      std::cout << "The key must be string key in HOT!" << std::endl;
      exit(-1);
    }
  }

  // 0 means no erase, 1 means erase 1
  bool erase(const T &key) { return false; }

  bool update(const T &key, const P &payload) { return false; }

  void print_min_max() {}

  void get_depth_info() {}

  int range_scan_by_size(const T &key, uint32_t to_scan, V *&result = nullptr) {
    return 0;
  }

private:
  cuckoo_trie *my_tree; // Store the pointer to the tree instance
};