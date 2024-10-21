#include <vector>
#include <array>
#include <cmath>

class KDTree;

struct Pivot
{
  int dimension;
  int value;
};

class KDNode
{
public:
  KDNode() {};
  ~KDNode() {};

  // Both methods
  void setDepth(int d);
  virtual bool isLeaf() = 0;

  // Branch methods
  virtual Pivot& getPivot() {};
  virtual void   setPivot(Pivot p) {};
  virtual KDNode* getLeafById(int i) {}; 

  // Leaf methods
  virtual std::vector<double>& getPose() {};
  virtual double getValue() {};
  virtual int    getDepth() {};
  virtual void   setPose(std::vector<double>& pose) {};
  virtual void   setValue(double v) {};

public:
  int depth;
};

class KDBranch : public KDNode
{
public:
  KDBranch() : children{NULL, NULL} {}
  ~KDBranch() {};

  bool isLeaf() override;

  Pivot& getPivot() override;
  KDNode* getLeafById(int i) override;

  void setPivot(Pivot p) override;

private:
  Pivot pivot;
  std::array<KDNode*, 2> children;
};

class KDLeaf : public KDNode
{
public:
  KDLeaf() {};
  ~KDLeaf() {};

  bool isLeaf() override;

  std::vector<double>& getPose() override;
  double getValue() override;
  int    getDepth() override;

  void setPose(std::vector<double>& pose) override;
  void setValue(double v) override;

private:
  std::vector<double> key;
  double value;
};

class KDTree
{
public:
  KDTree() {};
  ~KDTree() {};

  void insertNode(std::vector<double>& pose, double value);

private:
  void insertNodeImpl(KDNode* parent, KDNode* node, std::vector<double>& pose, double value);
  Pivot findSplit(std::vector<double>& pose, std::vector<double>& leaf_pose);

public:
  std::vector<double> size;

  KDNode* root;
  int node_count;
  int node_count_max;

  int max_split;
};