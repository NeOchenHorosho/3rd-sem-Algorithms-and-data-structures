#include <fstream>

using namespace std;

struct Node
{
    long long val;
    Node *left_child;
    Node *right_child;
    Node *parent;
    Node(long long _val, Node* _parent) : val(_val),parent(_parent), left_child(nullptr), right_child(nullptr) {}
};
Node *delete_node(Node *root, long long val)
{
    if (root == nullptr)
        return root;
    if (val < root->val)
    {
        root->left_child = delete_node(root->left_child, val);
    }
    else if (val > root->val)
    {
        root->right_child = delete_node(root->right_child, val);
    }
    else
    {

        if (root->left_child == nullptr)
        {
            Node *temp = root->right_child;
            if (temp)
                temp->parent = root->parent;
            return temp;
        }
        else if (root->right_child == nullptr)
        {
            Node *temp = root->left_child;
            if (temp)
                temp->parent = root->parent;
            return temp;
        }

        Node *temp = root->right_child;
        while (temp->left_child != nullptr)
        {
            temp = temp->left_child;
        }

        root->val = temp->val;
        root->right_child = delete_node(root->right_child, temp->val);
    }
    return root;
}
void pre_order_traversal(Node *root, ofstream &out)
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
    int val_to_delete;
    in >> val_to_delete;
    in >> val;
    Node *root = new Node(val, nullptr);

    while (in >> val)
    {
        Node *curr_node = root;
        while (true)
        {
            if (val == curr_node->val)
                break;
            if (val < curr_node->val)
            {
                if (curr_node->left_child != nullptr)
                    curr_node = curr_node->left_child;
                else
                {
                    curr_node->left_child = new Node(val, curr_node);
                    curr_node = curr_node->left_child;
                    break;
                }
            }
            else
            {
                if (curr_node->right_child != nullptr)
                    curr_node = curr_node->right_child;
                else
                {
                    curr_node->right_child = new Node(val, curr_node);
                    curr_node = curr_node->right_child;
                    break;
                }
            }
        }
    }
    root = delete_node(root, val_to_delete);

    pre_order_traversal(root, out);
}