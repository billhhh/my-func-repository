logic_Tree.h //树的头文件
logic_Tree.cpp //树的实现文件
logic_TreeNode.h //树节点头文件
logic_TreeNode.cpp //树节点实现文件

具体测试方法类似如下代码：

void logic_Test::testTree()
{
	typedef logic_TreeNode node_type;
	typedef logic_Tree tree_type;

	tree_type tree1(5);
	
 	tree1.add_node(5,7);
 	tree1.add_node(5,8);
 	tree1.add_node(5,10);
 	tree1.insert_node(5,10,6);
 	tree1.add_node(6,11);
 	tree1.recurs_print(tree1.getRoot());

 	cout<<"\n删除后："<<endl;
 	tree1.del_node(6);
	tree1.recurs_print(tree1.getRoot());

	delete tree1;
}


注：
1. recurs_print() 函数用作编写调试用，可以不用管floor错误
2. 上次测试所有错误已进行断言检查
3. 需要在用完tree后delete
4. destroy() 函数是私有函数，不可外部调用