#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <string>

using namespace std;

struct TreeNode{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode( int x ) : val(x), left(NULL), right(NULL){}
};

struct Command{
	string s; //go, print
	TreeNode * node;
	Command( string s, TreeNode *node ) : s(s), node(node){}
};

class Solution{

public:
	vector<int> preorderTraversal( TreeNode *root ){
		
		vector<int> res;
		if( NULL == root )
			return res;

		stack<Command> stack;
		stack.push( Command( "go", root ) );
		
		while( !stack.empty() ){
			Command cmd = stack.top();
			stack.pop();

			if( cmd.s == "print" )
				res.push_back( cmd.node->val );
			else{
				assert( cmd.s == "go" );
				if( cmd.node->right )
					stack.push( Command( "go", cmd.node->right ) );
				if( cmd.node->left )
					stack.push( Command( "go", cmd.node->left ) );
				stack.push( Command( "print", cmd.node ) );
			}
		}

		return res;
	}

	vector<int> inorderTraversal( TreeNode *root ){

		vector<int> res;
		if( NULL == root )
			return res;

		stack<Command> stack;
		stack.push( Command( "go", root ) );

		while( !stack.empty() ){
			Command cmd = stack.top();
			stack.pop();

			if( cmd.s.compare("print") == 0  )
				res.push_back( cmd.node->val );
			else{
				assert( cmd.s.compare("go") == 0 );
				if( cmd.node->right )
					stack.push( Command( "go", cmd.node->right ) );
				stack.push( Command( "print", cmd.node ) );
				if( cmd.node->left )
					stack.push( Command( "go", cmd.node->left ) );
			}
		}

		return res;
	}

	vector<int> postorderTraversal( TreeNode *root ){

		vector<int> res;
		if( NULL == root )
			return res;

		stack<Command> stack;
		stack.push( Command( "go", root ) );

		while( !stack.empty() ){
			Command cmd = stack.top();
			stack.pop();

			if( cmd.s.compare("print") == 0  )
				res.push_back( cmd.node->val );
			else{
				assert( cmd.s.compare("go") == 0 );
				stack.push( Command( "print", cmd.node ) );
				if( cmd.node->right )
					stack.push( Command( "go", cmd.node->right ) );
				if( cmd.node->left )
					stack.push( Command( "go", cmd.node->left ) );
			}
		}

		return res;
	}

	vector<int> preorderTraversal1( TreeNode *root ){
		vector<int> res;
		if( NULL == root )
			return res;

		stack<TreeNode*> ss;
		ss.push( root );
		while( !ss.empty() ){
			TreeNode *cur = ss.top();
			ss.pop();

			res.push_back( cur->val );
			if( cur->right )
				ss.push( cur->right );
			if( cur->left )
				ss.push( cur->left );
		}
		return res;
	}

	vector<int> inorderTraversal1( TreeNode *root ){
		vector<int> res;

		stack<TreeNode*> ss;
		TreeNode *p = root;
		while( p || !ss.empty() ){
			
			while( p ){
				ss.push( p );
				p = p->left;
			}

			p = ss.top();
			ss.pop();
			res.push_back( p->val );
			p = p->right;
		}
		return res;
	}

	vector<int> postorderTraversal1( TreeNode *root ){
		vector<int> res;

		stack<TreeNode*> ss;
		TreeNode *p = root;
		TreeNode *mark = NULL;
		while( p || !ss.empty() ){

			while( p ){
				ss.push( p );
				p = p->left;
			}

			p = ss.top();
			if( p->right && p->right != mark )
				p = p->right;
			else{
				ss.pop();
				res.push_back( p->val );
				mark = p;
				p = NULL;
			}			
		}
		return res;
	}

	vector<int> preorderTraversal2( TreeNode *root ){
		vector<int> res;
		if( NULL == root )
			return res;

		res.push_back( root->val );
		vector<int> lres = preorderTraversal2( root->left );
		vector<int> rres = preorderTraversal2( root->right );
		res.insert( res.end(), lres.begin(), lres.end() );
		res.insert( res.end(), rres.begin(), rres.end() );

		return res;
	}

	vector<int> inorderTraversal2( TreeNode *root ){
		vector<int> res;
		if( NULL == root )
			return res;

		vector<int> lres = inorderTraversal2( root->left );
		vector<int> rres = inorderTraversal2( root->right );
		res.insert( res.end(), lres.begin(), lres.end() );
		res.push_back( root->val );
		res.insert( res.end(), rres.begin(), rres.end() );

		return res;
	}

	vector<int> postorderTraversal2( TreeNode *root ){
		vector<int> res;
		if( NULL == root )
			return res;

		vector<int> lres = postorderTraversal2( root->left );
		vector<int> rres = postorderTraversal2( root->right );
		res.insert( res.end(), lres.begin(), lres.end() );
		res.insert( res.end(), rres.begin(), rres.end() );
		res.push_back( root->val );

		return res;
	}

	//利用两个栈，一个用于存放根结点，另一个用于存放输出
	vector<int> postorderTraversal3( TreeNode* root ){
		vector<int> res;
		if( NULL == root )
			return res;

		stack<TreeNode*> s1, s2;
		s1.push( root );
		
		while( !s1.empty() ){
			TreeNode* cur = s1.top();
			s1.pop();
			s2.push( cur );

			if( cur->left )
				s1.push( cur->left );
			if( cur->right )
				s1.push( cur->right );
		}

		while( !s2.empty() ){
			res.push_back( s2.top()->val );
			s2.pop();
		}

		return res;
	}
};

//root 表示子树的根，key 表示子树根的值
TreeNode* createTree( TreeNode* root, int key ){

	//root 为空，表示当前子树还没创建出来
	if( NULL == root ){
		root = new TreeNode( key );
		return root;
	}

	if( key < root->val )
		root->left = createTree( root->left, key );
	else
		root->right = createTree( root->right, key );

	return root;
}

int main()
{
	int t[] = { 5, 4, 6, 3, 7 };
	TreeNode *root = NULL;
	for( int i = 0; i < sizeof(t)/sizeof(int); ++i )
		root = createTree( root, t[i] );

	vector<int> res = Solution().postorderTraversal3( root );
	
	copy( res.begin(), res.end(), ostream_iterator<int>( cout, " " ) );
	cout << endl;

	system("pause");
	return 0;
}