#include <iostream>
#include <string>
using namespace std;

struct Node
{
    string name;
    Node* child[10];
    int count;

    Node(string n)
    {
        name = n;
        count = 0;
    }
};

// Add a child to a node
void addChild(Node* parent, Node* child)
{
    parent->child[parent->count] = child;
    parent->count++;
}

// Find a node by name
Node* search(Node* root, string key)
{
    if (root == NULL)
        return NULL;

    if (root->name == key)
        return root;

    for (int i = 0; i < root->count; i++)
    {
        Node* result = search(root->child[i], key);

        if (result != NULL)
            return result;
    }

    return NULL;
}

// Calculate height of a node
int height(Node* root)
{
    if (root == NULL)
        return -1;

    int maxHeight = -1;

    for (int i = 0; i < root->count; i++)
    {
        int h = height(root->child[i]);

        if (h > maxHeight)
            maxHeight = h;
    }

    return maxHeight + 1;
}

// Calculate depth of a node
int depth(Node* root, string key, int level)
{
    if (root == NULL)
        return -1;

    if (root->name == key)
        return level;

    for (int i = 0; i < root->count; i++)
    {
        int result = depth(root->child[i], key, level + 1);

        if (result != -1)
            return result;
    }

    return -1;
}

// Count leaf nodes
int countLeaves(Node* root)
{
    if (root == NULL)
        return 0;

    if (root->count == 0)
        return 1;

    int total = 0;

    for (int i = 0; i < root->count; i++)
        total += countLeaves(root->child[i]);

    return total;
}

// Main function
int main()
{
    // Create folder structure
    Node* root = new Node("Computer");

    Node* documents = new Node("Documents");
    Node* pictures = new Node("Pictures");
    Node* downloads = new Node("Downloads");

    addChild(root, documents);
    addChild(root, pictures);
    addChild(root, downloads);

    addChild(documents, new Node("Resume"));
    addChild(documents, new Node("Notes"));

    addChild(pictures, new Node("Photos"));

    addChild(downloads, new Node("Software"));

    // Display folder structure
    cout << "\nComputer Folder Structure\n\n";
    cout << "Computer\n";
    cout << "|-- Documents\n";
    cout << "|   |-- Resume\n";
    cout << "|   |-- Notes\n";
    cout << "|-- Pictures\n";
    cout << "|   |-- Photos\n";
    cout << "|-- Downloads\n";
    cout << "    |-- Software\n";

    // Enter folder name
    string key;

    cout << "\nEnter folder name to analyze: ";
    cin >> key;

    // Search for the selected node
    Node* selected = search(root, key);

    if (selected == NULL)
    {
        cout << "\nFolder not found!\n";
    }
    else
    {
        cout << "\nDegree of " << key << " = "
             << selected->count << endl;

        cout << "Height of " << key << " = "
             << height(selected) << endl;

        cout << "Depth of " << key << " = "
             << depth(root, key, 0) << endl;

        cout << "Total number of leaf nodes = "
             << countLeaves(root) << endl;
    }

    return 0;
}
