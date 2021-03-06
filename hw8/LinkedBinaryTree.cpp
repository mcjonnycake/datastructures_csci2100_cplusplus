template <typename Object>
LinkedBinaryTree<Object>::LinkedBinaryTree()
	: _root(NULL), n(0) { }

template <typename Object>
int LinkedBinaryTree<Object>::size() const
{
	return n;
}

template <typename Object>
bool LinkedBinaryTree<Object>::empty() const
{
	return size() == 0;
}

template <typename Object>
bool LinkedBinaryTree<Object>::isBST(const Node* v) const
{
	int num = 0;
	inorderQueue(v);
	while(!inorderQ.empty()){
		if(num == 0){
			num = inorderQ.front();
		}
		else if(inorderQ.front() < num){
			return false;
		}
		else{
			num = inorderQ.front();
		}
		inorderQ.pop();
	}
	return true;
}

template <typename Object>
typename LinkedBinaryTree<Object>::Position LinkedBinaryTree<Object>::root() const
{
	return Position(_root);
}

template <typename Object>
void LinkedBinaryTree<Object>::addRoot(const Object& value)
{
	_root = new Node;
	_root->elem = value;
	n = 1;
}

template <typename Object>
void LinkedBinaryTree<Object>::addLeftLeaf(const Position& p, const Object& value)
{
	Node* v = p.v;
	v -> left = new Node;
	v -> left -> elem = value;
	v -> left -> parent = v;
	n++;
}

template <typename Object>
void LinkedBinaryTree<Object>::addRightLeaf(const Position& p, const Object& value)
{
	Node* v = p.v;
	v -> right = new Node;
	v -> right -> elem = value;
	v -> right -> parent = v;
	n++;
}

template <typename Object>
void LinkedBinaryTree<Object>::preorderPrint() const
{
	preorder(_root);
}

template <typename Object>
void LinkedBinaryTree<Object>::preorder(const Node* v) const
{
	if(v == NULL) return;
	cout << v -> elem << endl;
	preorder(v -> left);
	preorder(v -> right);
}

template <typename Object>
void LinkedBinaryTree<Object>::inorderPrint() const
{
	inorder(_root);
}

template <typename Object>
void LinkedBinaryTree<Object>::inorder(const Node* v) const
{
	if(v == NULL) return;
	inorder(v -> left);
	cout << v -> elem << endl;
	inorder(v -> right);
}

template <typename Object>
void LinkedBinaryTree<Object>::inorderQueue(const Node* v)
{
	if(v == NULL) return;
	inorder(v -> left);
	inorderQ.push(int(v -> elem));
	inorder(v -> right);
}

template <typename Object>
void LinkedBinaryTree<Object>::postorderPrint() const
{
	postorder(_root);
}

template <typename Object>
void LinkedBinaryTree<Object>::postorder(const Node* v) const
{
	if(v == NULL) return;
	postorder(v -> left);
	postorder(v -> right);
	cout << v -> elem << endl;
}

template <typename Object>
void LinkedBinaryTree<Object>::expandExternal(const Position& p)
{
	Node* v = p.v;
	v -> left = new Node;
	v -> left -> parent = v;
	v -> right = new Node;
	v -> right -> parent = v;
	n += 2;
}

template <typename Object>
typename LinkedBinaryTree<Object>::Position LinkedBinaryTree<Object>::removeAboveExternal(const Position& p)
{
	Node* w = p.v;
	Node* v = w -> parent;
	Node* sib = (w == v -> left ? v -> right : v -> left);
	if( v == _root){
		_root = sib;
	}
	else{
		Node* gpar = v -> parent;
		if(v == gpar -> left)
			gpar -> left = sib;
		else
			gpar -> right = sib;
		sib -> par = gpar;
	}
	delete w;
	delete v;
	n -= 2;
	return Position(sib);
}
