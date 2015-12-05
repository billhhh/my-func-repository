/* 
* 
* funtion: 逻辑层树组织结构
* 
* Date:2015-09-03
* 
*    Author: Bill Wang
*/

#include <iostream>
#include <assert.h>
#include <climits>
#include "logic_Tree.h"

using namespace std;
typedef logic_TreeNode tree_node;

//logic_Tree 构造、析构方法
logic_Tree::logic_Tree() //默认构建一棵root ID为0的节点
	:mvu_root(new logic_TreeNode(0))
{
	Init();
}

logic_Tree::logic_Tree(_IdDataType rootId)
{
	assert(rootId<INT_MAX);
	assert(rootId>INT_MIN);

	tree_node* node = new tree_node(rootId); //建立root节点
	this->mvu_root = node;
	Init();
}

logic_Tree::logic_Tree(tree_node *node)
	:mvu_root(node)
{
	assert(node);
	assert(node->mvi_NodeID<INT_MAX);
	assert(node->mvi_NodeID>INT_MIN);

	Init();
}

logic_Tree::~logic_Tree()
{
	cout<<"进入logic_Tree析构函数"<<endl;
	Destroy(mvu_root);
}

void logic_Tree::Init()
{
	this->mvi_TreeID = this->mvu_root->mvi_NodeID; //树ID用root ID标识
}

void logic_Tree::Destroy(tree_node *some)
{
	//后序删除
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++)
		Destroy(some->mvvu_Children[i]);
	SAFE_DELETE(some);
}

//迭代器
logic_Tree::iterator::iterator()
	:_node(0) //NULL
{

}

logic_Tree::iterator::iterator(tree_node *node)
	:_node(node)
{

}

logic_Tree::iterator::~iterator()
{

}

tree_node* logic_Tree::iterator::get_cur_node()
{
	return _node;
}//迭代器 END

tree_node* logic_Tree::getRoot()
{
	return this->mvu_root;
}

//增、删、查功能外部接口
bool logic_Tree::add_node(_IdDataType parent_ID,_IdDataType ID)
{
	iterator *temPos = search(ID);
	if ( NULL != temPos ) //如果已经存在，错误
	{
		SAFE_DELETE(temPos);
		return false;
	}

	tree_node *tmp = new tree_node(ID);
	iterator* position = search(parent_ID);

	if ( NULL == position)
	{
		SAFE_DELETE(position);
		return false;
	}

	position->_node->mvvu_Children.push_back(tmp);
	tmp->mvu_Parent = position->_node;
	SAFE_DELETE(position); //delete position;

	return true;
}

bool logic_Tree::insert_node(_IdDataType parent_ID,_IdDataType suc_ID,_IdDataType ID)
{
	iterator* positionA = search(parent_ID);
	iterator* positionB = search(suc_ID);

	if ( NULL == positionA || NULL == positionB)
	{
		//发现内存问题报错
		SAFE_DELETE(positionA);
		SAFE_DELETE(positionB);
		return false;
	}

	//如果suc_ID节点不是parent_ID节点直接孩子，错误
	int index = isChild(positionA,positionB);
	if (index == -1)
	{
		SAFE_DELETE(positionA);
		SAFE_DELETE(positionB);
		return false;
	}

	tree_node *tmp = new tree_node(ID);
	positionA->_node->mvvu_Children.erase(positionA->_node->mvvu_Children.begin()+index); //删除parent_ID节点中的suc_ID节点孩子
	positionA->_node->mvvu_Children.push_back(tmp);
	tmp->mvvu_Children.push_back(positionB->_node);
	tmp->mvu_Parent = positionA->_node;
	positionB->_node->mvu_Parent = tmp;

	SAFE_DELETE(positionA);
	SAFE_DELETE(positionB);

	return true;
}

int logic_Tree::isChild(iterator* p, iterator* c) const
{
	int Search_ID = c->_node->mvi_NodeID;
	for (int i=0;i<p->_node->mvvu_Children.size();++i)
	{
		if (Search_ID == p->_node->mvvu_Children[i]->mvi_NodeID)
		{
			return i;
		}
	}

	return -1;
}

bool logic_Tree::del_node(_IdDataType ID)
{
	assert(ID != mvi_TreeID);

	iterator* position = search(ID);
	if (NULL == position)
	{
		SAFE_DELETE(position);
		return false;
	}

	tree_node *cur_node = position->_node;
	for (int i=0;i<cur_node->mvvu_Children.size();++i)
	{
		//将待删除节点的所有儿子传给父亲
		cur_node->mvu_Parent->mvvu_Children.push_back(cur_node->mvvu_Children[i]);
		cur_node->mvvu_Children[i]->mvu_Parent = cur_node->mvu_Parent;
	}
	//将其父亲的此儿子删除
	for (int i=0;i<cur_node->mvu_Parent->mvvu_Children.size();++i)
	{
		if(cur_node->mvu_Parent->mvvu_Children[i]->mvi_NodeID == ID)
			cur_node->mvu_Parent->mvvu_Children.erase(cur_node->mvu_Parent->mvvu_Children.begin()+i);
	}

	SAFE_DELETE(cur_node);
	SAFE_DELETE(position);

	return true;
}

logic_Tree::iterator* logic_Tree::search(_IdDataType ID)
{
	tree_node* some = mvu_root;
	tree_node* res = recurs_render(mvu_root,ID);

	if (res == NULL)
		return NULL;

	//会在调用search方法的地方释放
	iterator* tmp = new iterator(res);
	return tmp;
}

tree_node* logic_Tree::recurs_render(tree_node* some,const _IdDataType ID)
{
	if (ID == some->mvi_NodeID)
		return some;

	for (unsigned i = 0; i < some->mvvu_Children.size(); i++)
	{
		tree_node* r = recurs_render(some->mvvu_Children[i],ID);

		if(NULL != r)
			return r;
	}

	return NULL;
}

void logic_Tree::recurs_print(tree_node* some,int floor) const
{
	std::cout << "floor " << floor << ": ";
	++floor;
	std::cout << some->mvi_NodeID << std::endl;
	for (unsigned i = 0; i < some->mvvu_Children.size(); i++)
		recurs_print(some->mvvu_Children[i],floor);
	--floor;
}
