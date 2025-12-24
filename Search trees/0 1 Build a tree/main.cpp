#include <fstream>

using namespace std;

struct Node
{
    long long val;
    Node *left_child;
    Node *right_child;

    Node(long long _val): val(_val), left_child(nullptr), right_child(nullptr){}
};
void pre_order_traversal(Node* root, ofstream& out)
{
    if (root == nullptr)
        return;
    out << root->val << '\n';
    pre_order_traversal(root->left_child, out);
    pre_order_traversal(root->right_child, out);
}
int main()
{

    ifstream in("input.txt");
    ofstream out("output.txt");
    int val;
    in >> val;
    Node root(val);


    while(in >> val)
    {
    Node* curr_node = &root;
        while (true)
        {
            if(val == curr_node->val) break;
            if(val < curr_node->val)
            {
                if(curr_node->left_child != nullptr)
                    curr_node=curr_node->left_child;
                else
                {
                    curr_node->left_child = new Node(val);
                    curr_node = curr_node->left_child;
                    break;
                }
            }
            else
            {
                if(curr_node->right_child != nullptr)
                    curr_node=curr_node->right_child;
                else
                {
                    curr_node->right_child = new Node(val);
                    curr_node = curr_node->right_child;
                    break;
                }
            }
        }
        
    }
    pre_order_traversal(&root, out);

}