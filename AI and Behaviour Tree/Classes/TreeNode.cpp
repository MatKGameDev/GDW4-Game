#include "TreeNode.h"
#include <algorithm>
#include "Boss.h"

TreeNode::TreeNode()
{
	status = new Status;
	*status = Status::unInitialized;
}

TreeNode::~TreeNode()
{
	delete status;
}


/*
 * This function returns true if the status is success, false if others
 */
bool TreeNode::isSuccess() const
{
	return *status == Status::success;
}

bool TreeNode::isFailure() const
{
	return *status == Status::failure;
}

bool TreeNode::isRunning() const
{
	return *status == Status::running;
}


/*
 * This function is similar to update functions, this function is called every frame
 * and will iterate through the tree
 */
TreeNode::Status TreeNode::tick(const float deltaT, Boss *boss)
{
	if ((*status) == Status::unInitialized)
		init();

	*status = update(deltaT, boss);

	if ((*status) != Status::running)
		terminate(status);

	return *status;
}

void TreeNode::init()
{
}

void TreeNode::terminate(Status *s)
{
	*s = unInitialized;
}

//De-allocate all memory used
DecoratorNode::~DecoratorNode()
{
	child = nullptr;
}

void DecoratorNode::addChild(TreeNode* nodeToAdd)
{
	/*
	 * Because a decorator node only has 1 child, it will throw an exception
	 * if the program tries to add a second node
	 */
	if (child == nullptr)
		child = nodeToAdd;
	else
		throw;
}

//De-allocate all memory used
CompositionNode::~CompositionNode()
{
	std::vector<TreeNode *>().swap(children);
}

void CompositionNode::addChild(TreeNode* nodeToAdd)
{
	children.push_back(nodeToAdd);
}

void RandomSelectorNode::init()
{
	*status = Status::running;
	for (size_t i = 0; i < children.size(); i++)
	{
		untriedChildrenNode.push_back(i);
	}
}

TreeNode::Status RandomSelectorNode::update(const float deltaT, Boss *boss)
{
	while(!untriedChildrenNode.empty())
	{
		//If the last frame update returned running 



		//If the last frame update returned failure
		//Choose a random index
		const int returnedRandomIndex = cocos2d::RandomHelper::random_int(0, static_cast<int>(untriedChildrenNode.size()));

		//update the index of the children vector
		const Status returnedStatus = children[untriedChildrenNode[returnedRandomIndex]]->tick(deltaT,boss);

		//fail, then remove from children list
		if (returnedStatus == failure)
		{
			untriedChildrenNode.erase(untriedChildrenNode.begin() + returnedRandomIndex);
		}
		//sucess then return success
		else
			return returnedStatus;
	}
	return failure;
}

SequenceNode::SequenceNode()
{
	*status = Status::running;
}

TreeNode::Status SequenceNode::update(const float deltaT, Boss *boss)
{
	for (auto iterator : children)
	{
		const Status returnedStatus = iterator->tick(deltaT, boss);

		if (returnedStatus != success)
			return returnedStatus;
	}
	return success;
}

TreeNode::Status NoLimitRepeater::update(const float deltaT, Boss *boss)
{
	while (true)
	{
		child->tick(deltaT, boss);
	}
}

TreeNode::Status BehaviourTree::update(const float deltaT, Boss *boss)
{
	return root->tick(deltaT, boss);
}

void BehaviourTree::setRoot(TreeNode* rootNode)
{
	this->root = rootNode;
}





