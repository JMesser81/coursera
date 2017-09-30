#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }

    void addChild(Node *child) {
      this->children.push_back(child);
    }
};

int calc_tree_height(Node *node)
{
  int height = 1;
  if (node->children.empty())
  {
    return height;
  }

  //std::cout << "Node " << node->key << " has " << node->children.size() << " children." << std::endl;
  int maxHeight = 0;
  for (auto const& child : node->children)
  {
    //std::cout << "Calculating tree height for child " <<   child->key << std::endl;
    height = 1 + calc_tree_height(child);
    maxHeight = std::max(maxHeight, height);
  }
  return maxHeight;
}

int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  Node parent_nodes[n];
  for (int i = 0; i < n; i++)
  {
    parent_nodes[i].key = 0;
    parent_nodes[i].parent = nullptr;
    parent_nodes[i].children.clear();
  }
  int root_index = -1;

  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;

    if (parent_index >= 0)
    {
      nodes[child_index].setParent(&nodes[parent_index]);
      parent_nodes[parent_index].addChild(&nodes[child_index]);
      //std::cout << "Adding child node with index " << child_index << " to parent node with index " << parent_index << std::endl;
      parent_nodes[parent_index].key = parent_index;
    }
    else
    {
      root_index = child_index;
    }
    nodes[child_index].key = child_index;

  }
  //std::cout << "Parent node is at index " << root_index << std::endl;

  // Replace this code with a faster implementation
  int maxHeight = 0;
  if (root_index > -1)
  {
    // iterate over each of root's children, calculate height recursively
    //std::cout << "Root has " << parent_nodes[root_index].children.size() << " children\n";
    for (auto const& root_child : parent_nodes[root_index].children)
    {
      //std::cout << "Root child " << root_child->key << " has " << root_child->children.size() << " children\n";

      int height = 1 + calc_tree_height(root_child);
      maxHeight = std::max(maxHeight, height);
    }
  }

  /*
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  }
  */

  std::cout << maxHeight << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
