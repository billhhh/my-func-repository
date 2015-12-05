/* 
* 
* funtion: 逻辑层树节点
* 
* Date:2015-09-03
* 
*    Author: Bill Wang
*/

#include <assert.h>
#include <climits>
#include "logic_TreeNode.h"

logic_TreeNode::logic_TreeNode()
	:mvi_NodeID(-1),mvu_Parent(NULL)
{

}

//针对于新建树根时
logic_TreeNode::logic_TreeNode(const _IdDataType data)
	:mvu_Parent(0)
{
	assert(data<INT_MAX);
	assert(data>INT_MIN);

	mvi_NodeID = data;
}

logic_TreeNode::logic_TreeNode(logic_TreeNode *p,const _IdDataType data)
	:mvu_Parent(p)
{
	assert(data<INT_MAX);
	assert(data>INT_MIN);

	mvi_NodeID = data;
}

logic_TreeNode::~logic_TreeNode()
{

}
