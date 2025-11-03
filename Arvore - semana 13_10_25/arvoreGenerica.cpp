#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

template <typename T>
class Node {
public:
    T element;
    Node<T>* father;
    vector<Node<T>*> subtrees;

    Node(T val) {
        element = val;
        father = nullptr;
    }

    void addSubtree(Node<T>* n) {
        n->father = this;
        subtrees.push_back(n);
    }

    bool removeSubtree(Node<T>* n) {
        for (auto it = subtrees.begin(); it != subtrees.end(); ++it) {
            if (*it == n) {
                subtrees.erase(it);
                n->father = nullptr;
                return true;
            }
        }
        return false;
    }

    Node<T>* getSubtree(int i) {
        if (i >= 0 && i < subtrees.size())
            return subtrees[i];
        return nullptr;
    }

    int getSubtreesSize() {
        return subtrees.size();
    }

    int size() {
        int count = 1;
        for (Node<T>* child : subtrees)
            count += child->size();
        return count;
    }

    void preOrder(vector<T>& result) {
        result.push_back(element);
        for (Node<T>* child : subtrees)
            child->preOrder(result);
    }

    void postOrder(vector<T>& result) {
        for (Node<T>* child : subtrees)
            child->postOrder(result);
        result.push_back(element);
    }

    void breadth(vector<T>& result) {
        queue<Node<T>*> q;
        q.push(this);
        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();
            result.push_back(current->element);
            for (Node<T>* child : current->subtrees)
                q.push(child);
        }
    }

    int height() {
        int h = 0;
        for (Node<T>* child : subtrees)
            h = max(h, 1 + child->height());
        return h;
    }

    int level() {
        int lvl = 0;
        Node<T>* current = father;
        while (current != nullptr) {
            lvl++;
            current = current->father;
        }
        return lvl;
    }

    void printTree(int indent = 0) {
        for (int i = 0; i < indent; i++) cout << "  ";
        cout << element << endl;
        for (Node<T>* child : subtrees)
            child->printTree(indent + 1);
    }

    bool moveSubtree(Node<T>* newFather) {
        if (this == newFather) return false;
        if (father != nullptr) {
            father->removeSubtree(this);
        }
        newFather->addSubtree(this);
        return true;
    }

    Node<T>* getLCA(Node<T>* a, Node<T>* b) {
        if (!a || !b) return nullptr;

        // sobe até o topo e guarda o caminho do primeiro nó
        vector<Node<T>*> ancestorsA;
        while (a) {
            ancestorsA.push_back(a);
            a = a->father;
        }

        // percorre ancestrais do segundo e acha o primeiro em comum
        while (b) {
            for (Node<T>* anc : ancestorsA) {
                if (anc == b) return b;
            }
            b = b->father;
        }
        return nullptr;
    }

    bool hasCycle(Node<T>* node, Node<T>* parent) {
        for (Node<T>* child : node->subtrees) {
            if (child == parent) return true; // ciclo simples
            if (hasCycle(child, node)) return true;
        }
        return false;
    }

    bool isConsistent(Node<T>* root) {
        // 1. Verifica se só há uma raiz
        // 2. Verifica se há ciclo
        return !hasCycle(root, nullptr);
    }
};

int main() {
    Node<string>* raiz = new Node<string>("App");
    Node<string>* config = new Node<string>("Configuracoes");
    Node<string>* notifi = new Node<string>("Notificacoes");


    // Montando a árvore
    raiz->addSubtree(config);
    config->addSubtree(notifi);

}
