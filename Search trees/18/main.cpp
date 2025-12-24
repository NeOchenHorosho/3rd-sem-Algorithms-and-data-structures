#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Node
{
    long long height;
    long long max_height_paths_num; // которое l_h(v), но мне это название больше по душе
    long long max_path_passing_num;
    long long key;
    Node *parent;
    Node *left_child;
    Node *right_child;

    Node(long long _key, Node *_parent) : height(0), max_height_paths_num(1), max_path_passing_num(0), key(_key), parent(_parent), left_child(nullptr), right_child(nullptr) {}
};

long long max_path_len = 0;

void calc_heights_and_max_path_len(Node *node)
{
    if (!node)
        return;

    if (!node->left_child && !node->right_child)
    {
        node->height = 0;
        node->max_height_paths_num = 1;
        return;
    }

    calc_heights_and_max_path_len(node->left_child);
    calc_heights_and_max_path_len(node->right_child);

    long long height_left = (node->left_child) ? node->left_child->height : -1;
    long long height_right = (node->right_child) ? node->right_child->height : -1;

    node->height = max(height_left, height_right) + 1;

    if (height_left == height_right)
    {
        long long paths_left = (node->left_child) ? node->left_child->max_height_paths_num : 1;
        long long paths_right = (node->right_child) ? node->right_child->max_height_paths_num : 1;
        node->max_height_paths_num = paths_left + paths_right;
    }
    else if (height_left > height_right)
    {
        node->max_height_paths_num = node->left_child->max_height_paths_num;
    }
    else
    {
        node->max_height_paths_num = node->right_child->max_height_paths_num;
    }

    long long current_max_path_len = height_left + height_right + 2;
    if (current_max_path_len > max_path_len)
    {
        max_path_len = current_max_path_len;
    }
}

void calc_max_heights_paths_num(Node *node, long long paths_from_above)
{
    if (!node)
        return;

    long long height_left = (node->left_child) ? node->left_child->height : -1;
    long long height_right = (node->right_child) ? node->right_child->height : -1;
    long long max_height_paths_left = (node->left_child) ? node->left_child->max_height_paths_num : 1;
    long long max_height_paths_right = (node->right_child) ? node->right_child->max_height_paths_num : 1;

    long long root_paths = 0;

    if (height_left + height_right + 2 == max_path_len)
    {
        root_paths = max_height_paths_left * max_height_paths_right;
    }

    long long through_paths = paths_from_above * node->max_height_paths_num;

    node->max_path_passing_num = through_paths + root_paths;

    long long to_left = 0;

    if (paths_from_above > 0 && node->height == height_left + 1)
    {
        to_left += paths_from_above;
    }
    if (height_right + 1 + 1 + height_left == max_path_len)
    {
        to_left += max_height_paths_right;
    }

    long long to_right = 0;
    if (paths_from_above > 0 && node->height == height_right + 1)
    {
        to_right += paths_from_above;
    }
    if (height_left + 1 + 1 + height_right == max_path_len)
    {
        to_right += max_height_paths_left;
    }

    calc_max_heights_paths_num(node->left_child, to_left);
    calc_max_heights_paths_num(node->right_child, to_right);
}

void find_candidates(Node *node, vector<long long> &candidates)
{
    if (!node)
        return;
    if (node->max_path_passing_num > 0 && node->max_path_passing_num % 2 == 0)
    {
        candidates.push_back(node->key);
    }
    find_candidates(node->left_child, candidates);
    find_candidates(node->right_child, candidates);
}

Node *delete_node(Node *root, long long key)
{
    if (key < root->key)
    {
        root->left_child = delete_node(root->left_child, key);
    }
    else if (key > root->key)
    {
        root->right_child = delete_node(root->right_child, key);
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

        root->key = temp->key;
        root->right_child = delete_node(root->right_child, temp->key);
    }
    return root;
}

void print_left_straight(Node *node, fstream &out)
{
    if (!node)
        return;
    out << node->key << "\n";
    print_left_straight(node->left_child, out);
    print_left_straight(node->right_child, out);
}

void build_tree(std::fstream &in, long long &key, Node *root);

int main()
{
    fstream in("tst.in", ios::in);
    fstream out("tst.out", ios::out);

    long long key;
    if (!(in >> key))
        return 0;

    Node *root = new Node(key, nullptr);

    build_tree(in, key, root);

    calc_heights_and_max_path_len(root);

    calc_max_heights_paths_num(root, 0);

    vector<long long> candidates;
    find_candidates(root, candidates);

    if (!candidates.empty())
    {
        long long min_key_to_delete = candidates[0];
        for (long long k : candidates)
        {
            if (k < min_key_to_delete)
            {
                min_key_to_delete = k;
            }
        }
        root = delete_node(root, min_key_to_delete);
    }

    print_left_straight(root, out);

    in.close();
    out.close();
    return 0;
}

void build_tree(std::fstream &in, long long &key, Node *root)
{
    while (in >> key)
    {
        Node *curr_node = root;
        while (true)
        {
            if (key < curr_node->key)
            {
                if (curr_node->left_child == nullptr)
                {
                    curr_node->left_child = new Node(key, curr_node);
                    break;
                }
                else
                {
                    curr_node = curr_node->left_child;
                }
            }
            else if (key > curr_node->key)
            {
                if (curr_node->right_child == nullptr)
                {
                    curr_node->right_child = new Node(key, curr_node);
                    break;
                }
                else
                {
                    curr_node = curr_node->right_child;
                }
            }
            else
                break;
        }
    }
}
