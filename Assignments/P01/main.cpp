
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;

  Node(int x) {
    data = x;
    left = right = nullptr;
  }
};

class GraphvizBST {
public:
  static void saveDotFile(const std::string &filename,
                          const std::string &dotContent) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
      outFile << dotContent;
      outFile.close();
      std::cout << "DOT file saved: " << filename << std::endl;
    } else {
      std::cerr << "Error: Could not open file " << filename << std::endl;
    }
  }

  static std::string generateDot(const Node *root) {
    std::string dot = "digraph BST {\n";
    dot += "    node [fontname=\"Arial\"];\n";
    dot += generateDotHelper(root);
    dot += "}\n";
    return dot;
  }

private:
  static std::string generateDotHelper(const Node *node) {
    if (!node)
      return "";
    std::string result;
    if (node->left) {
      result += "    " + std::to_string(node->data) + " -> " +
                std::to_string(node->left->data) + " [label=\"L\"];\n";
      result += generateDotHelper(node->left);
    } else {
      std::string nullNode = "nullL" + std::to_string(node->data);
      result += "    " + nullNode + " [shape=point];\n";
      result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n";
    }
    if (node->right) {
      result += "    " + std::to_string(node->data) + " -> " +
                std::to_string(node->right->data) + " [label=\"R\"];\n";
      result += generateDotHelper(node->right);
    } else {
      std::string nullNode = "nullR" + std::to_string(node->data);
      result += "    " + nullNode + " [shape=point];\n";
      result += "    " + std::to_string(node->data) + " -> " + nullNode + ";\n";
    }
    return result;
  }
};

class Bst {
  Node *root;

  void _print(Node *subroot) {
    if (!subroot) {
      return;
    } else {
      _print(subroot->left);
      cout << subroot->data << " ";
      _print(subroot->right);
    }
  }
  void _insert(Node *&subroot, int x) {
    if (!subroot) { // if(root == nullptr)
      subroot = new Node(x);
    } else {
      if (x < subroot->data) {
        _insert(subroot->left, x);
      } else {
        _insert(subroot->right, x);
      }
    }
  }
  int _ipl(Node *root, int depth = 0) {
    if (!root)
      return 0; // Base case: Empty subtree contributes 0 to IPL
    return depth + _ipl(root->left, depth + 1) + _ipl(root->right, depth + 1);
  }
  Node *_delete(Node *&subroot, int x) {
    // Base case: nothing in the tree nothing to delete
    if (!subroot) {
      return NULL;
    }

    // Traveresal of the tree
    if (x < subroot->data) {
      subroot->left = _delete(subroot->left, x);
    } else if (x > subroot->data) {
      subroot->right = _delete(subroot->right, x);
    } else {

      // Case 1: No child nodes.

      // Checking for children.
      if (subroot->left == nullptr && subroot->right == nullptr) {
        delete subroot;
        return nullptr;
      }

      // Case 2: 1 child node.

      // Checking for children
      if (subroot->left != nullptr && subroot->right == nullptr) {
        // Storing replacment value in temp
        Node *temp = subroot->left;
        delete subroot;
        return temp;

      } else if (subroot->left == nullptr && subroot->right != nullptr) {
        Node *temp = subroot->right;
        delete subroot;
        return temp;
      }

      // Case 3: 2 child nodes. Inorder predecessor approach.

      // Starting inorder predecessor approach.
      Node *current = subroot->left;
      while (current != nullptr && current->right != nullptr) {
        current = current->right;
      }

      // Swapping values to eventually delete the subroot node.
      subroot->data = current->data;
      // Using recursion to let the previous cases handle the deletion
      subroot->left = _delete(subroot->left, current->data);
    }

    return subroot;
  }

public:
  Bst() { root = nullptr; }
  void insert(int x) { _insert(root, x); }

  // Using a public wrapper to pass parameters to private method.
  void deleteNode(int x) { root = _delete(root, x); }
  bool search(int key) { return 0; }
  void print() { _print(root); }
  void saveDotFile(const std::string &filename) {
    std::string dotContent = GraphvizBST::generateDot(root);
    GraphvizBST::saveDotFile(filename, dotContent);
  }

  /**
   * Computes the Internal Path Length (IPL) of a Binary Search Tree (BST).
   *
   * Definition:
   * The Internal Path Length (IPL) of a BST is the sum of the depths of all
   * nodes in the tree. The depth of a node is the number of edges from the root
   * to that node.
   *
   * Example:
   *        10
   *       /  \
   *      5    15
   *     / \     \
   *    2   7    20
   *
   * IPL = (depth of 10) + (depth of 5) + (depth of 15) + (depth of 2) + (depth
   * of 7) + (depth of 20) = 0 + 1 + 1 + 2 + 2 + 2 = 8
   *
   * @param root Pointer to the root node of the BST.
   * @param depth Current depth of the node (default is 0 for the root call).
   * @return The sum of depths of all nodes (Internal Path Length).
   */
  int ipl() { return _ipl(root); }
};

bool unique_value(int *arr, int n, int x) {
  for (int i = 0; i < n; i++) {
    if (arr[i] == x) {
      return false;
    }
  }
  return true;
}

int main() {
  Bst tree;
  int root = pow(2, 15) / 2;
  int max = pow(2, 15) - 1;
  vector<int> arr;
  arr.push_back(root);
  tree.insert(root);
  for (int i = 1; i < 5000; i++) {
    int r = rand() % max;
    while (!unique_value(arr.data(), arr.size(), r)) {
      r = rand() % max;
    }
    tree.insert(r);
    arr.push_back(r);
    // tree.deleteNode(r);
  }
  // tree.deleteNode(root);

  // Test Cases

  // Bst t;
  // t.deleteNode(10);
  // t.print();

  // Bst t;
  // t.insert(10);
  // t.deleteNode(10);
  // t.print();

  // Bst t;
  // t.insert(10);
  // t.insert(5);
  // t.insert(15);
  // t.deleteNode(5);
  // t.print();

  // Bst t;
  // t.insert(10);
  // t.insert(5);
  // t.insert(2);
  // t.deleteNode(5);
  // t.print();

  // Bst t;
  // t.insert(10);
  // t.insert(15);
  // t.insert(20);
  // t.deleteNode(15);
  // t.print();

  // Bst t;
  // t.insert(10);
  // t.insert(5);
  // t.deleteNode(10);
  // t.print();

  // Bst t;
  // t.insert(10);
  // t.insert(5);
  // t.insert(15);
  // t.insert(2);
  // t.insert(7);
  // t.print();

  // Bst t;
  // t.insert(10);
  // t.insert(5);
  // t.insert(15);
  // t.insert(2);
  // t.insert(7);
  // t.insert(12);
  // t.insert(20);
  //
  // t.deleteNode(10);
  // t.print();

  // Bst t;
  // t.insert(10);
  // t.insert(5);
  // t.insert(15);
  // t.insert(2);
  // t.insert(7);
  // t.insert(6);
  //
  // t.deleteNode(10);
  // t.print();

  // Bst t;
  // t.insert(10);
  // t.insert(5);
  // t.insert(15);
  // t.insert(2);
  // t.insert(7);
  //
  // t.deleteNode(2);
  // t.deleteNode(5);
  // t.deleteNode(10);
  // t.print();

  Bst tree2;
  tree2.insert(10);
  tree2.insert(5);
  tree2.insert(15);
  tree2.insert(2);
  tree2.insert(7);
  tree2.insert(20);

  // tree.print();
  tree.saveDotFile("bst_snapshot.dot");
  // t.saveDotFile("bst_snapshot2.dot");
  cout << "Internal Path Length: " << tree2.ipl() << endl;
}
