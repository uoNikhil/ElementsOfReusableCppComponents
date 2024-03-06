#include <iostream>

template <typename data_type>
struct Node
{
    data_type value;
    Node* left = nullptr;
    Node* right = nullptr;
};

template <typename data_type>
class Tree
{
public:
    Tree(){}
    Tree(data_type val){
        m_root->value = val;
    }

    Node<data_type>* insert(Node<data_type>* curr = this->m_root, data_type val)
    {
        if (curr->val < val)
        {
            // go right;
            if (curr->right == nullptr)
            {
                Node<data_type>* newNode = new Node<data_type>;
                curr->right = newNode;
                newNode->value = val;
                return newNode;
            }
            else
            {
                return insert(curr->right, val);
            }
        }
        else if(curr->val > val)
        {
            // go left
            if (curr->left == nullptr)
            {
                Node<data_type>* newNode = new Node<data_type>;
                curr->left = newNode;
                newNode->value = val;
                return newNode;
            }
            else{
                return insert(curr->left,val);
            }
        }
        else
        {
            //ERROR: Value Already Exists
            std::cout << "ERROR: Value Already Exists";
            return nullptr;
        }
    }

    Node<data_type>* search(Node<data_type>* curr = this->m_root, data_type val)
    {
        if (curr->value == val)
        {
            return curr;
        }
        else if (curr->value < val)
        {
            // search right
            if (curr->right == nullptr)
                return nullptr;
            return search(curr->right,val);
        }
        else
        {
            if (curr->left == nullptr)
                return nullptr;
            return search(curr->left,val);
        }
    }    

    void delete()
    {

    }
    

private:
    Node<data_type> m_root;
};


int main()
{

}