/* 
* 
* funtion: 逻辑层树节点
* 
* Date:2015-09-03
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_TREE_NODE_H_
#define _LOGIC_TREE_NODE_H_

#include <vector>
#include "logic_BasicModule.h"
#include "logic_Global.h"

class logic_TreeNode
{
public:
	_IdDataType mvi_NodeID; //树种存放的都是 logic_BasicModule 型节点 ID 号
	std::vector<logic_TreeNode *> mvvu_Children;
	logic_TreeNode *mvu_Parent;

	explicit logic_TreeNode();
	explicit logic_TreeNode(const _IdDataType data);
	explicit logic_TreeNode(logic_TreeNode *p,const _IdDataType data);
	~logic_TreeNode();

protected:


private:


};

#endif
