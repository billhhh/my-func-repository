/* 
* 
* funtion: 逻辑层树组织结构
* 
* Date:2015-09-03
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_TREE_H_
#define _LOGIC_TREE_H_

#include "logic_TreeNode.h"
#include "logic_Global.h"

class logic_Tree
{
protected:
	typedef logic_TreeNode tree_node;
public:
	_IdDataType mvi_TreeID; //TreeID即rootID

	explicit logic_Tree();
	explicit logic_Tree(_IdDataType rootId);
	explicit logic_Tree(tree_node *node);
	~logic_Tree();

	//迭代器嵌套类
	class iterator{
	public:
		//构造与析构
		iterator();
		explicit iterator(tree_node *node);
		~iterator();

		tree_node *_node;

		tree_node* get_cur_node(); //获取当前节点
		// 		iterator begin() const; //开始位置
		// 		iterator end() const; //结束位置

	protected:

	private:
		//tree_node* _find_end(tree_node* current) const;
	};

public:
	tree_node * getRoot();

	//增、删、查功能外部接口
	bool add_node(_IdDataType parent_ID,_IdDataType ID); //接在parent后
	bool insert_node(_IdDataType parent_ID,_IdDataType suc_ID,_IdDataType ID); //插在两个节点中间
	bool del_node(_IdDataType ID);
	iterator* search(_IdDataType ID); //遍历搜索
	void recurs_print(tree_node* some,int floor=0) const; //DFS打印测试

protected:

private:
	tree_node *mvu_root;

	void Init();
	void Destroy(tree_node *some); /////销毁some节点及其所有后代，销毁整棵树
	int isChild(iterator* p, iterator* c) const; //判断c是不是p的直接孩子，如果找到返回i，没找到-1
	tree_node* recurs_render(tree_node* some,const _IdDataType ID); //递归DFS

};

#endif
