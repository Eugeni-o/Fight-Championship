Estrutura de Dados — Árvore Genérica (Node<T>)

Implementação em C++ de uma árvore genérica, onde cada nó pode ter qualquer número de subárvores (sem limitação binária).
A classe é template, ou seja, aceita qualquer tipo de dado como elemento (int, string, float, etc).

------------------------------------------------------------
ESTRUTURA DA CLASSE
------------------------------------------------------------

template <typename T>
class Node {
public:
    T element;                   // Valor armazenado no nó
    Node<T>* father;             // Ponteiro para o pai (nullptr se for a raiz)
    vector<Node<T>*> subtrees;   // Lista de filhos (subárvores)

    Node(T val);
    void addSubtree(Node<T>* n);
    bool removeSubtree(Node<T>* n);
    Node<T>* getSubtree(int i);
    int getSubtreesSize();
    int size();
    void preOrder(vector<T>& result);
    void postOrder(vector<T>& result);
    void breadth(vector<T>& result);
    int height();
    int level();
    void printTree(int indent = 0);
    bool moveSubtree(Node<T>* newFather);
    Node<T>* getLCA(Node<T>* a, Node<T>* b);
    bool hasCycle(Node<T>* node, Node<T>* parent);
    bool isConsistent(Node<T>* root);
};

------------------------------------------------------------
MÉTODOS E EXEMPLOS DE USO
------------------------------------------------------------

Node(T val)
Cria um novo nó com o valor informado.
Exemplo:
Node<string>* raiz = new Node<string>("Início");

------------------------------------------------------------
addSubtree(Node<T>* n)
Adiciona um nó filho ao nó atual e define o ponteiro father.
Exemplo:
Node<int>* raiz = new Node<int>(1);
Node<int>* filho = new Node<int>(2);
raiz->addSubtree(filho);
cout << filho->father->element; // Saída: 1

------------------------------------------------------------
removeSubtree(Node<T>* n)
Remove uma subárvore específica. Retorna true se o nó foi removido.
Exemplo:
raiz->removeSubtree(filho);
cout << raiz->getSubtreesSize(); // Saída: 0

------------------------------------------------------------
getSubtree(int i)
Retorna o i-ésimo filho do nó. Retorna nullptr se o índice for inválido.
Exemplo:
Node<int>* c0 = raiz->getSubtree(0);
if (c0) cout << c0->element;

------------------------------------------------------------
getSubtreesSize()
Retorna o número de subárvores diretas do nó.
Exemplo:
cout << raiz->getSubtreesSize(); // Exemplo: 3

------------------------------------------------------------
size()
Retorna o número total de nós abaixo (incluindo o próprio).
Exemplo:
cout << raiz->size(); // Exemplo: 7

------------------------------------------------------------
preOrder(vector<T>& result)
Percorre a árvore em pré-ordem (visita primeiro o nó, depois os filhos).
Exemplo:
vector<int> ordem;
raiz->preOrder(ordem);
for (int n : ordem) cout << n << " "; // Saída: 1 2 5 6 3 7 4

------------------------------------------------------------
postOrder(vector<T>& result)
Percorre a árvore em pós-ordem (visita filhos antes do nó).
Exemplo:
vector<int> ordem;
raiz->postOrder(ordem);
for (int n : ordem) cout << n << " "; // Saída: 5 6 2 7 3 4 1

------------------------------------------------------------
breadth(vector<T>& result)
Percorre em largura (nível por nível).
Exemplo:
vector<int> ordem;
raiz->breadth(ordem);
for (int n : ordem) cout << n << " "; // Saída: 1 2 3 4 5 6 7

------------------------------------------------------------
height()
Calcula a altura da árvore (maior profundidade a partir do nó atual).
Exemplo:
cout << raiz->height(); // Exemplo: 2

------------------------------------------------------------
level()
Retorna o nível do nó atual (distância até a raiz).
Exemplo:
cout << filho->level(); // Exemplo: 1

------------------------------------------------------------
printTree(int indent = 0)
Imprime a estrutura da árvore em formato hierárquico.
Exemplo:
raiz->printTree();

Saída:
1
  2
    5
    6
  3
    7
  4

------------------------------------------------------------
moveSubtree(Node<T>* newFather)
Move o nó atual para outro pai (preserva subárvores).
Exemplo:
sub3->moveSubtree(menu1);

------------------------------------------------------------
getLCA(Node<T>* a, Node<T>* b)
Retorna o ancestral comum mais próximo (LCA) entre dois nós.
Exemplo:
Node<int>* lca = raiz->getLCA(sub1, sub3);
cout << lca->element; // Saída: 1

------------------------------------------------------------
hasCycle(Node<T>* node, Node<T>* parent)
Detecta ciclos recursivamente (para evitar laços acidentais).

------------------------------------------------------------
isConsistent(Node<T>* root)
Verifica se a árvore está consistente (sem ciclos e com raiz única).
Exemplo:
cout << (raiz->isConsistent(raiz) ? "OK" : "Inconsistente");

------------------------------------------------------------
EXEMPLO COMPLETO (main)
------------------------------------------------------------

int main() {
    Node<int>* raiz = new Node<int>(1);

    Node<int>* menu1 = new Node<int>(2);
    Node<int>* menu2 = new Node<int>(3);
    Node<int>* menu3 = new Node<int>(4);

    Node<int>* sub1 = new Node<int>(5);
    Node<int>* sub2 = new Node<int>(6);
    Node<int>* sub3 = new Node<int>(7);

    raiz->addSubtree(menu1);
    raiz->addSubtree(menu2);
    raiz->addSubtree(menu3);

    menu1->addSubtree(sub1);
    menu1->addSubtree(sub2);
    menu2->addSubtree(sub3);

    raiz->printTree();
    return 0;
}

Saída esperada:
1
  2
    5
    6
  3
    7
  4

------------------------------------------------------------
OBSERVAÇÕES
------------------------------------------------------------
- A classe é totalmente genérica (template <typename T>).
- As relações pai–filho são automaticamente atualizadas em addSubtree() e moveSubtree().
- Evita loops e inconsistências via isConsistent() e hasCycle().
- Ideal para aplicações como:
  * Hierarquias de menus
  * Árvores sintáticas
  * Estruturas de diretórios
