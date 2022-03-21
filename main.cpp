#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

class BinarySearchTree
{
private:
  struct NodeTree
  {
    NodeTree *left;
    NodeTree *right;
    int data;
  };
  NodeTree *root;

  /**
   * @brief Mendefinisikan method-method kelas BinarySearchTree
   *
   */
public:
  /**
   * @brief Construct a new Binary Search Tree object
   *
   */
  BinarySearchTree()
  {
    root = NULL;
  }

  /**
   * @brief Get the Root object
   *
   * @return NodeTree* | node sebagai root
   */
  NodeTree *getRoot() const { return root; }

  /**
   * @brief Mengecek apakah tree kosong
   *
   * @return true | bila kosong
   * @return false | bila tidak kosong
   */
  bool isEmpty() const { return root == NULL; }

  NodeTree *search(NodeTree *, int);

  void printInOrder();

  void inOrder(NodeTree *);

  void printPreOrder();

  void preOrder(NodeTree *);

  void printPostOrder();

  void postOrder(NodeTree *);

  int leftHeight(NodeTree *);

  int rightHeight(NodeTree *);

  int count(NodeTree *);

  int depth(NodeTree *);

  void insert(int);

  NodeTree *remove(NodeTree *, int);

  NodeTree *minValueNode(NodeTree *);
};

/**
 * @brief Mencari node dari tree
 *
 * @param NodeTree* parent | node yang digunakan untuk memulai pencarian,
 *                           baiknya menggunakan root untuk mencari secara menyeluruh.
 *
 * @param int | data node yang akan dicari
 * @return BinarySearchTree::NodeTree* | node yang dicari
 */
BinarySearchTree::NodeTree *BinarySearchTree::search(NodeTree *parent, int d)
{
  // jika parent tidak ditentukan maka mengembalikan null
  if (parent == NULL)
    return NULL;

  if (parent->data == d)
    return parent;

  // rekursif mencari ke child kiri
  NodeTree *leftChild = search(parent->left, d);
  // node found, no need to look further
  if (leftChild)
    return leftChild;

  // node tidak diemukan di child kiri,
  // lanjut ke child kanan
  NodeTree *rightChild = search(parent->right, d);

  if (rightChild)
    return rightChild;

  // bila tidak ditemukan sama sekali,
  // maka mengembalikan null
  return NULL;
}

/**
 * @brief Menyelipkan node baru ke susunan tree
 *
 * @param int d | data dari node yang akan diselipkan
 */
void BinarySearchTree::insert(int d)
{
  // memastikan data belum pernah dimasukkan
  if (search(root, d))
  {
    cout << " Data sudah ada" << endl;
    return;
  }

  // mendefinisikan node baru
  NodeTree *t = new NodeTree;
  // mendefinisikan node parent yang akan dijadikan parent oleh node baru
  NodeTree *parent;
  // menginisisasi node baru dengan data
  t->data = d;
  t->left = NULL;
  t->right = NULL;
  parent = NULL;

  if (isEmpty())
  {
    // bila tree kosong, maka node baru dijadikan root dari tree
    root = t;
  }
  else
  {
    // bila tree tidak kosong, maka dicek satu persatu untuk menentukan
    // pada parent yang mana node diselipkan
    // dan child yang mana saja yang akan ditautkan pada node baru

    // node current adalah node yang dijadikan cursor dalam menentukan node parent untuk node baru
    // pada kondisi pertama node current adalah root
    NodeTree *current = root;

    while (current)
    {
      parent = current;
      if (t->data > current->data)
        // bila data pada node baru lebih besar dari data pada node current
        // maka cursor diarahkan ke child kanan
        current = current->right;
      else
        // bila tidak, maka cursor diarahkan ke child kiri
        current = current->left;
    }

    if (t->data < parent->data)
      // bila node baru lebih kecil dari parent
      // maka node baru adalah child kiri dari parent
      parent->left = t;
    else
      // bila tidak, node baru adalah child kanan dari parent
      parent->right = t;
  }
}

/**
 * @brief Menghapus node dari susunan tree
 *
 * @param NodeTree* parent | node parent
 * @param int d | data pada node yang akan dihapus
 * @return BinarySearchTree::NodeTree* | node parent
 */
BinarySearchTree::NodeTree *BinarySearchTree::remove(NodeTree *parent, int d)
{
  if (parent == NULL)
    // bila parent nya null maka tidak menghapus apa-apa dan mengembalikan parent yang null
    return parent;

  if (d < parent->data)
    // bila node yang akan dihapus lebih kecil dari root,
    // maka direkursif dengan data child KIRI sebagai parent
    parent->left = remove(parent->left, d);

  else if (d > parent->data)
    // sebaliknya, bila node yang akan dihapus lebih besar dari root,
    // maka direkursif dengan data child KANAN sebagai parent
    parent->right = remove(parent->right, d);

  else
  // jika node yang dicari ketemu, maka node ini yang akan dihapus
  {
    if (parent->left == NULL && parent->right == NULL)
    {
      // node tidak memiliki child
      return NULL;
    }
    else if (parent->left == NULL)
    {
      // node yang hanya memiliki satu child di sebelah kanan
      NodeTree *temp = parent->right;
      if (root == parent)
      {
        root = temp;
      }
      free(parent);
      return temp;
    }
    else if (parent->right == NULL)
    {
      // node yang hanya memiliki satu child di sebelah kiri
      NodeTree *temp = parent->left;
      if (root == parent)
      {
        root = temp;
      }
      free(parent);
      return temp;
    }

    // bila node memiliki child di keduanya (kanan-kiri)
    // maka yg dicari node yang lebih kecil dengan menggunakan method minValueNode
    NodeTree *temp = minValueNode(parent->right);

    // Salin konten penerus inorder ke node
    parent->data = temp->data;

    // Hapus child secara inorder
    parent->right = remove(parent->right, temp->data);
  }

  // mengembalikan ke node parent
  return parent;
}

/**
 * @brief Mendapatkan node yang paling kecil dari susunan tree berdasarkan parent tertentu
 *
 * @param NodeTree *parent | node parent
 * @return BinarySearchTree::NodeTree* | node child terkecil dari susunan tree dari parent yang ditentukan
 */
BinarySearchTree::NodeTree *BinarySearchTree::minValueNode(NodeTree *parent)
{
  NodeTree *current = parent;

  // mendapatkan child terkecil
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

/**
 * @brief Mencetak tree secara in-order dari ROOT
 *
 */
void BinarySearchTree::printInOrder()
{
  if (!isEmpty())
    inOrder(root);
}

/**
 * @brief Menampilkan node-node pada tree secara in-order dari parent node tertentu
 *
 * @param NodeTree *parent | node parent yang digunakan untuk memulai
 */
void BinarySearchTree::inOrder(NodeTree *parent)
{
  if (parent != NULL)
  {
    if (parent->left)
      inOrder(parent->left);
    cout << " " << parent->data << " ";
    if (parent->right)
      inOrder(parent->right);
  }
  else
  {
    // bila tidak ada lagi node, proses selesai
    return;
  }
}

/**
 * @brief Mencetak tree secara pre-order dari ROOT
 *
 */
void BinarySearchTree::printPreOrder()
{
  if (!isEmpty())
    preOrder(root);
}

/**
 * @brief Menampilkan node-node pada tree secara pre-order dari parent node tertentu
 *
 * @param NodeTree *node | node parent yang digunakan untuk memulai
 */
void BinarySearchTree::preOrder(NodeTree *node)
{
  if (node != NULL)
  {
    cout << " " << node->data << " ";
    if (node->left)
      preOrder(node->left);
    if (node->right)
      preOrder(node->right);
  }
  else
  {
    // bila tidak ada lagi node, proses selesai
    return;
  }
}

/**
 * @brief Mencetak tree secara post-order dari ROOT
 *
 */
void BinarySearchTree::printPostOrder()
{
  if (!isEmpty())
    postOrder(root);
}

/**
 * @brief Menampilkan node-node pada tree secara post-order dari parent node tertentu
 *
 * @param NodeTree *node | node parent yang digunakan untuk memulai
 */
void BinarySearchTree::postOrder(NodeTree *node)
{
  if (node != NULL)
  {
    if (node->left)
      postOrder(node->left);
    if (node->right)
      postOrder(node->right);
    cout << " " << node->data << " ";
  }
  else
  {
    // bila tidak ada lagi node, proses selesai
    return;
  }
}

/**
 * @brief Mendapatkan ketinggian keturunan dari sisi kiri
 *
 * @param NodeTree *parent
 * @return int
 */
int BinarySearchTree::leftHeight(NodeTree *parent)
{
  int height = 0;
  while (parent)
  {
    // secara iteratif dihitung hingga tidak ada lagi node child kiri
    height++;
    parent = parent->left;
  }

  // mengembalikan ketinggian total
  return height;
}

/**
 * @brief Mendapatkan ketinggian keturuan dari sisi kanan
 *
 * @param NodeTree *parent
 * @return int
 */
int BinarySearchTree::rightHeight(NodeTree *parent)
{
  int height = 0;
  while (parent)
  {
    // secara iteratif dihitung hingga tidak ada lagi node child kanan
    height++;
    parent = parent->right;
  }

  // mengembalikan ketinggian total
  return height;
}

/**
 * @brief Menghitung keseluruhan node
 *
 * @param NodeTree *parent | parent untuk memulai menghitung
 *                           baiknya root, untuk menghitung dari keseluruhan
 * @return int
 */
int BinarySearchTree::count(NodeTree *parent)
{
  // bila parent null, langsung mengembalikan 0
  if (parent == NULL)
    return 0;

  // mendapatkan ketinggian masing-masing sisi
  int lh = leftHeight(parent);
  int rh = rightHeight(parent);

  if (lh == rh)
    // bila ketinggian masing-masing sisi sama
    // mengembalikan 2^height(1<<height) -1
    return (1 << lh) - 1;

  // bila tidak sama, secara rekursif menghitung dari masing-masing sisi
  return 1 + count(parent->left) + count(parent->right);
}

/**
 * @brief Mendapatkan kedalaman maksimal dari tree
 *
 * @param NodeTree *parent | node yang digunakan untuk memulai mencari kedalaman
 * @return int
 */
int BinarySearchTree::depth(NodeTree *parent)
{
  // bila node
  if (parent == NULL)
  {
    return -1;
  }
  else
  {
    // menghitung kedalaman masing-masing sisi
    int ld = depth(parent->left);
    int rd = depth(parent->right);

    // mengambil yang paling besar, apakah sisi kanan atau kiri
    if (ld > rd)
      return (ld + 1);
    else
      return (rd + 1);
  }
}

int main()
{
  BinarySearchTree b;
  int selectedOption, insertedData, deletedData;

  cout << " Hai Fellas, met datang di program Binary Search Tree " << endl;
  while (1)
  {
    cout << endl
         << endl;
    cout << " ----------------------------- " << endl;
    cout << " 1. Tambah data " << endl;
    cout << " 2. Pre-order " << endl;
    cout << " 3. In-order " << endl;
    cout << " 4. Post-order " << endl;
    cout << " 5. Jumlah node pada tree " << endl;
    cout << " 6. Kedalaman tree " << endl;
    cout << " 7. Hapus data " << endl;
    cout << " 8. Keluar " << endl;
    cout << " Masukkan pilihan : ";
    cin >> selectedOption;
    switch (selectedOption)
    {
    case 1:
      cout << " Masukkan node yang akan diselipkan : ";
      cin >> insertedData;
      b.insert(insertedData);
      break;
    case 2:
      cout << endl;
      cout << " Pre-order " << endl;
      cout << " -------------------" << endl;
      b.printPreOrder();
      break;
    case 3:
      cout << endl;
      cout << " In-order " << endl;
      cout << " -------------------" << endl;
      b.printInOrder();
      break;
    case 4:
      cout << endl;
      cout << " Post-order " << endl;
      cout << " --------------------" << endl;
      b.printPostOrder();
      break;
    case 5:
      cout << endl;
      cout << " Jumlah node pada tree " << endl;
      cout << " --------------------" << endl;
      cout << " ";
      cout << b.count(b.getRoot()) << endl;
      break;
    case 6:
      cout << endl;
      cout << " Kedalaman node " << endl;
      cout << " --------------------" << endl;
      cout << " ";
      cout << b.depth(b.getRoot()) << endl;
      break;
    case 7:
      cout << " Masukkan node yang akan dihapus: ";
      cin >> deletedData;
      b.remove(b.getRoot(), deletedData);
      break;
    case 8:
      return 0;
    default:
      cout << " Opsi tidak tersedia";
    }
  }
};