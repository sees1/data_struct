#include <kdtree.h>
#include <iostream>

bool KDBranch::isLeaf()
{
  return false;
}

void KDBranch::setPivot(Pivot p)
{
  pivot.dimension = p.dimension;
  pivot.value = p.value;
}

void KDNode::setDepth(int d)
{
  depth = d;
}

KDNode* KDBranch::getLeafById(int i){
  if (i >= 0 && i < 3)
    return children[i];
  else
    std::cout << "you are idiot";
}

Pivot& KDBranch::getPivot()
{
  return pivot;
}

bool KDLeaf::isLeaf()
{
  return true;
}

std::vector<double>& KDLeaf::getPose() {
  return key;
}

double KDLeaf::getValue() {
  return value;
}

int KDLeaf::getDepth() {
  return depth;
}

void KDLeaf::setPose(std::vector<double>& pose)
{
  key = pose;
}

void KDLeaf::setValue(double v)
{
  value = v;
}

Pivot KDTree::findSplit(std::vector<double>& pose, std::vector<double>& leaf_pose)
{
  int split = 0;
  int max_split = 0;
  int dimension = -1;
  for(int i = 0; i < 3; ++i)
  {
    split = std::abs(pose[i] - leaf_pose[i]);
    if (split > max_split)
    {
      max_split = split;
      dimension = i;
    }
  }
  double value = (pose[dimension] + leaf_pose[dimension]) / 2.0;
  return {dimension, value};
}

void KDTree::insertNode(std::vector<double>& pose, double value)
{
  insertNodeImpl(NULL, root, pose, value);
}

void KDTree::insertNodeImpl(KDNode* parent, KDNode* node, std::vector<double>& pose, double value)
{
  int split;
  int max_split;

  if (node == NULL)
  {
    node = new KDLeaf();

    if(node == NULL)
    {
      node->setDepth(0);
    }
    else
    {
      node->setDepth(parent->depth + 1);
    }

    node->setPose(pose);
    node->setValue(value);
  }
  else if (node->isLeaf()) // assumption that node type if leaf
  {
    if(pose == node->getPose()) // so is the correct choise ! just increment value by new value and go upstair
      node->setValue(node->getValue() + value);
    else
    {
      std::vector<double> leaf_pose = node->getPose();
      double leaf_value = node->getValue();
      int    leaf_depth = node->getDepth();

      delete node;
      node = new KDBranch();

      node->setPivot(findSplit(pose, leaf_pose));
      node->setDepth(leaf_depth);

      if(pose[node->getPivot().dimension] < node->getPivot().value)
      {
        insertNodeImpl(node, node->getLeafById(0), pose, value);
        insertNodeImpl(node, node->getLeafById(1), leaf_pose, leaf_value);
      }
      else
      {
        insertNodeImpl(node, node->getLeafById(0), leaf_pose, leaf_value);
        insertNodeImpl(node, node->getLeafById(1), pose, value);
      }
    }
  }
  else // assumption that node type is branch
  {
    if(pose[node->getPivot().dimension] < node->getPivot().value)
      insertNodeImpl(node, node->getLeafById(0), pose, value);
    else
      insertNodeImpl(node, node->getLeafById(1), pose, value);
  }
}