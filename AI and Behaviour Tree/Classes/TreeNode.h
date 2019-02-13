#pragma once
#include <vector>

class Boss;

class TreeNode
{
protected:
	//State enum
	enum Status
	{
		success,
		failure,
		running,
		unInitialized
	};

	Status *status;
	TreeNode();

public:
	virtual ~TreeNode();


	//Getters and Setters
	bool isSuccess()const;
	bool isFailure()const;
	bool isRunning()const;

	//Member Functions
	virtual Status update(const float deltaT, Boss *boss) = 0; //Probably need to add an AI pointer as second parameter
	virtual Status tick(const float deltaT, Boss *boss);
	virtual void init();
	virtual void terminate(Status* s);

};

//Decorator node in a behaviour tree only have 1 child
class DecoratorNode : public TreeNode
{
protected:
	TreeNode *child{nullptr};
public:
	virtual ~DecoratorNode();
	//Member functions
	void addChild(TreeNode* nodeToAdd);
};

//Composition node in a behaviour tree can have more than 1 node
class CompositionNode :public TreeNode
{
protected:
	std::vector<TreeNode*> children;
public:
	virtual ~CompositionNode();

	//Member Functions
	void addChild(TreeNode *nodeToAdd);
};

class RandomSelectorNode: public CompositionNode
{
private:
	std::vector<int> untriedChildrenNode; //This will consists of all index that has not been failed
public:
	void init() override;
	Status update(float deltaT, Boss *boss) override;
	void terminate(Status* s) override;

};

class SequenceNode: public CompositionNode
{
private:
	SequenceNode();
public:
	//void init() override;
	Status update(const float deltaT, Boss *boss) override;
};

class NoLimitRepeater: public DecoratorNode
{
public:
	Status update(const float deltaT, Boss *boss) override;
};

class Leaf: public TreeNode
{
protected:
	virtual Status update(const float deltaT, Boss *boss) = 0;
};

class BehaviourTree: public TreeNode
{
public:
	Status update(const float deltaT, Boss *boss) override;
	void setRoot(TreeNode *rootNode);
private:
	TreeNode *root{ nullptr };
};