#ifndef $(UPMODULENAME) _COMMON_H_
#define $(UPMODULENAME) _COMMON_H_

#include "ara/com/types.h"

$(NAMESPACESHEADER)
$(DEFINECONTENTS)

class $(MODULENAME) Serializer : public ara::com::Serializer {
 public:
  using ara::com::Serializer::serialize;

  $(MODULENAME) Serializer() : ara::com::Serializer("$(MODULENAME)") {}

  ~$(MODULENAME) Serializer() {}

  $(SERILIAZECONTENT)
  template <class T>
  bool serialize(const std::vector<T>& value) {
    if (m_sizeOfArrayLengthField == 1) {
      uint8_t len = value.size() * sizeof(T);
      serialize(len);
    } else if (m_sizeOfArrayLengthField == 2) {
      uint16_t len = value.size() * sizeof(T);
      serialize(len);
    } else if (m_sizeOfArrayLengthField == 4) {
      uint32_t len = value.size() * sizeof(T);
      serialize(len);
    } else {
      uint32_t len = value.size() * sizeof(T);
      serialize(len);
    }

    for (auto v : value) {
      serialize(v);
    }

    return true;
  }

  template <class K, class V>
  bool serialize(const std::map<K, V>& value) {
    if (m_sizeOfArrayLengthField == 1) {
      uint8_t len = value.size() * (sizeof(K) + sizeof(V));
      serialize(len);
    } else if (m_sizeOfArrayLengthField == 2) {
      uint16_t len = value.size() * (sizeof(K) + sizeof(V));
      serialize(len);
    } else if (m_sizeOfArrayLengthField == 4) {
      uint32_t len = value.size() * (sizeof(K) + sizeof(V));
      serialize(len);
    } else {
      uint32_t len = value.size() * (sizeof(K) + sizeof(V));
      serialize(len);
    }

    for (auto v : value) {
      serialize(v.first);
      serialize(v.second);
    }

    return true;
  }
};

class $(MODULENAME) Deserializer : public ara::com::Deserializer {
 public:
  using ara::com::Deserializer::deserialize;

  $(MODULENAME)
  Deserializer(const uint8_t* data, uint32_t size)
      : ara::com::Deserializer(data, size, "$(MODULENAME)") {}

  ~$(MODULENAME) Deserializer() {}
  $(DESERILIAZECONTENT)
  template <class T>
  bool deserialize(std::vector<T>& value) {
    sint32 size = 0;
    T val;

    if (m_sizeOfArrayLengthField == 1) {
      uint8_t len = 0;
      if (!deserialize(len)) {
        return false;
      }
      size = len / sizeof(T);
    } else if (m_sizeOfArrayLengthField == 2) {
      uint16_t len = 0;
      if (!deserialize(len)) {
        return false;
      }
      size = len / sizeof(T);
    } else if (m_sizeOfArrayLengthField == 4) {
      uint32_t len = 0;
      if (!deserialize(len)) {
        return false;
      }
      size = len / sizeof(T);
    } else {
      uint32_t len = 0;
      if (!deserialize(len)) {
        return false;
      }
      size = len / sizeof(T);
    }

    value.clear();

    for (int i = 0; i < size; i++) {
      if (!deserialize(val)) {
        return false;
      }
      value.push_back(val);
    }

    return true;
  }

  template <class K, class V>
  bool deserialize(std::map<K, V>& value) {
    sint32 size = 0;
    K key;
    V val;

    if (m_sizeOfArrayLengthField == 1) {
      uint8_t len = 0;
      if (!deserialize(len)) {
        return false;
      }
      size = len / (sizeof(K) + sizeof(V));
    } else if (m_sizeOfArrayLengthField == 2) {
      uint16_t len = 0;
      if (!deserialize(len)) {
        return false;
      }
      size = len / (sizeof(K) + sizeof(V));
    } else if (m_sizeOfArrayLengthField == 4) {
      uint32_t len = 0;
      if (!deserialize(len)) {
        return false;
      }
      size = len / (sizeof(K) + sizeof(V));
    } else {
      uint32_t len = 0;
      if (!deserialize(len)) {
        return false;
      }
      size = len / (sizeof(K) + sizeof(V));
    }

    value.clear();

    for (int i = 0; i < size; i++) {
      if (!deserialize(key)) {
        return false;
      }
      if (!deserialize(val)) {
        return false;
      }

      value[key] = val;
    }

    return true;
  }
};
$(NAMESPACESEND)
#endif  //$(UPMODULENAME)_COMMON_H_