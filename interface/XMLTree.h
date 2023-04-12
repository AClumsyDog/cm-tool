#pragma once

#include <map>
#include <memory>
#include <string>

namespace cm_tool {

enum class NodeType { ROOT, DATA_TYPES, VECTOR };

class BaseNode {
 public:
  BaseNode(NodeType type) : data_type_(type), parent_(nullptr) {}

  virtual ~BaseNode() = default;

  BaseNode(const BaseNode &) = delete;
  BaseNode &operator=(const BaseNode &) = delete;

  BaseNode(BaseNode &&) = default;
  BaseNode &operator=(BaseNode &&) = default;

  NodeType GetType() const { return data_type_; }

  void AddChild(std::unique_ptr<BaseNode> child) {
    child->SetParent(this);
    children_.push_back(std::move(child));
  }

  bool RemoveChild(const size_t &index) {
    if (children_.size() > index) {
      children_.erase(children_.begin() + index);
      return true;
    } else {
      return false;
    }
  }

  BaseNode *GetChild(const size_t &index) const {
    if (children_.empty()) {
      return nullptr;
    }
    return children_[index].get();
  }

  BaseNode *GetParent() const { return parent_; }

  void SetParent(BaseNode *parent) { parent_ = parent; }

  size_t GetNumChildren() const { return children_.size(); }

  std::vector<std::unique_ptr<BaseNode>> &GetChildren() { return children_; }

 private:
  NodeType data_type_;
  BaseNode *parent_;
  std::vector<std::unique_ptr<BaseNode>> children_;
};

template <typename T>
class DataNode : public BaseNode {
 public:
  DataNode(NodeType type);
  DataNode(NodeType type, std::unique_ptr<T> data);
  virtual ~DataNode();

  DataNode(const DataNode &) = delete;
  DataNode &operator=(const DataNode &) = delete;

  DataNode(DataNode &&) = default;
  DataNode &operator=(DataNode &&) = default;

  T *Get() const;
  std::unique_ptr<T> GetData();
  void SetData(std::unique_ptr<T> data);

  void AddAttribute(const std::string &name, const std::string &value);
  const std::map<std::string, std::string> &GetAttributes();

 private:
  std::map<std::string, std::string> attributes_;
  std::unique_ptr<T> data_;
};

template <typename T>
DataNode<T>::DataNode(NodeType type)
    : BaseNode(type), attributes_(), data_(nullptr) {}

template <typename T>
DataNode<T>::DataNode(NodeType type, std::unique_ptr<T> data)
    : BaseNode(type), attributes_(), data_(std::move(data)) {}

template <typename T>
DataNode<T>::~DataNode() {}

template <typename T>
T *DataNode<T>::Get() const {
  return data_.get();
}

template <typename T>
std::unique_ptr<T> DataNode<T>::GetData() {
  return std::move(data_);
}

template <typename T>
void DataNode<T>::SetData(std::unique_ptr<T> data) {
  data_ = std::move(data);
}

template <typename T>
void DataNode<T>::AddAttribute(const std::string &name,
                               const std::string &value) {
  attributes_[name] = value;
}

template <typename T>
const std::map<std::string, std::string> &DataNode<T>::GetAttributes() {
  return attributes_;
}
}  // namespace cm_tool