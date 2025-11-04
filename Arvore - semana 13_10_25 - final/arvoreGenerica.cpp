//só funciona no windows1

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <windows.h>

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
        for (int i = 0; i < indent; i++) cout << "-";
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
        return !hasCycle(root, nullptr);
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8); // Para exibir caracteres especiais corretamente no console do Windows

    Node<string>* raiz = new Node<string>("Pagina Principal");
    Node<string>* lutadores = new Node<string>("Lutadores");
    Node<string>* perdedores = new Node<string>("Perdedores");
    Node<string>* configuracoes = new Node<string>("Configuracoes");
    Node<string>* notificacoes = new Node<string>("Notificacoes");
    Node<string>* perfil = new Node<string>("Meu Perfil");
    Node<string>* ajuda = new Node<string>("Ajuda");

    raiz->addSubtree(lutadores);
    raiz->addSubtree(perdedores);
    raiz->addSubtree(configuracoes);
    configuracoes->addSubtree(notificacoes);
    configuracoes->addSubtree(perfil);
    raiz->addSubtree(ajuda);

    Node<string>* kenji = new Node<string>("Kenji");
    Node<string>* daigo = new Node<string>("Daigo");
    Node<string>* arun = new Node<string>("Arun");
    Node<string>* mali = new Node<string>("Mali");
    Node<string>* akira = new Node<string>("Akira");
    Node<string>* hiro = new Node<string>("Hiro");
    Node<string>* surya = new Node<string>("Surya");
    Node<string>* goro = new Node<string>("Goro");

    // Subnós de Kenji
    Node<string>* kenjiArte = new Node<string>("Arte Marcial: Karatê Shotokan + Boxe");
    Node<string>* kenjiAltura = new Node<string>("Altura: 1,48 m");
    Node<string>* kenjiIdade = new Node<string>("Idade: 13 anos");
    Node<string>* kenjiDesc = new Node<string>("Descrição: Iniciante talentoso e muito rápido nos socos. Cheio de energia e confiança.");

    // Subnós de Daigo
    Node<string>* daigoArte = new Node<string>("Arte Marcial: Karatê Kyokushin");
    Node<string>* daigoAltura = new Node<string>("Altura: 1,70 m");
    Node<string>* daigoIdade = new Node<string>("Idade: 18 anos");
    Node<string>* daigoDesc = new Node<string>("Descrição: Temperamento forte e golpes devastadores. Tatuagens representam sua linhagem guerreira.");

    // Subnós de Arun
    Node<string>* arunArte = new Node<string>("Arte Marcial: Muay Thai");
    Node<string>* arunAltura = new Node<string>("Altura: 1,58 m");
    Node<string>* arunIdade = new Node<string>("Idade: 16 anos");
    Node<string>* arunDesc = new Node<string>("Descrição: Especialista em joelhadas e chutes altos. Treinado no templo de seu país desde pequeno.");

    // Subnós de Mali
    Node<string>* maliArte = new Node<string>("Arte Marcial: Muay Thai Boran");
    Node<string>* maliAltura = new Node<string>("Altura: 1,54 m");
    Node<string>* maliIdade = new Node<string>("Idade: 15 anos");
    Node<string>* maliDesc = new Node<string>("Descrição: Forte para sua idade. Técnicas antigas e movimentos giratórios são seu diferencial.");

    // Subnós de Akira
    Node<string>* akiraArte = new Node<string>("Arte Marcial: Karatê + Kickboxing");
    Node<string>* akiraAltura = new Node<string>("Altura: 1,62 m");
    Node<string>* akiraIdade = new Node<string>("Idade: 17 anos");
    Node<string>* akiraDesc = new Node<string>("Descrição: Tem estilo agressivo e ofensivo. Rival direto do Daigo, quer ser o nº1 do dojo.");

    // Subnós de Hiro
    Node<string>* hiroArte = new Node<string>("Arte Marcial: Karatê Tradicional");
    Node<string>* hiroAltura = new Node<string>("Altura: 1,50 m");
    Node<string>* hiroIdade = new Node<string>("Idade: 13 anos");
    Node<string>* hiroDesc = new Node<string>("Descrição: Melhor amigo (e rival amigável) de Kenji. Passos leves e esquivas rápidas.");

    // Subnós de Surya
    Node<string>* suryaArte = new Node<string>("Arte Marcial: Muay Thai + Sanda");
    Node<string>* suryaAltura = new Node<string>("Altura: 1,73 m");
    Node<string>* suryaIdade = new Node<string>("Idade: 19 anos");
    Node<string>* suryaDesc = new Node<string>("Descrição: Golpes amplos e extremamente fortes. Seu estilo mistura tradição e acrobacias.");

    // Subnós de Goro
    Node<string>* goroArte = new Node<string>("Arte Marcial: Luta Livre / Grappling");
    Node<string>* goroAltura = new Node<string>("Altura: 1,80 m");
    Node<string>* goroIdade = new Node<string>("Idade: 20 anos");
    Node<string>* goroDesc = new Node<string>("Descrição: O mais forte fisicamente. Especialista em agarrões e imobilizações brutais.");

    // Adicionar subnós aos lutadores
    kenji->addSubtree(kenjiArte);
    kenji->addSubtree(kenjiAltura);
    kenji->addSubtree(kenjiIdade);
    kenji->addSubtree(kenjiDesc);

    daigo->addSubtree(daigoArte);
    daigo->addSubtree(daigoAltura);
    daigo->addSubtree(daigoIdade);
    daigo->addSubtree(daigoDesc);

    arun->addSubtree(arunArte);
    arun->addSubtree(arunAltura);
    arun->addSubtree(arunIdade);
    arun->addSubtree(arunDesc);

    mali->addSubtree(maliArte);
    mali->addSubtree(maliAltura);
    mali->addSubtree(maliIdade);
    mali->addSubtree(maliDesc);

    akira->addSubtree(akiraArte);
    akira->addSubtree(akiraAltura);
    akira->addSubtree(akiraIdade);
    akira->addSubtree(akiraDesc);

    hiro->addSubtree(hiroArte);
    hiro->addSubtree(hiroAltura);
    hiro->addSubtree(hiroIdade);
    hiro->addSubtree(hiroDesc);

    surya->addSubtree(suryaArte);
    surya->addSubtree(suryaAltura);
    surya->addSubtree(suryaIdade);
    surya->addSubtree(suryaDesc);

    goro->addSubtree(goroArte);
    goro->addSubtree(goroAltura);
    goro->addSubtree(goroIdade);
    goro->addSubtree(goroDesc);

    // Adicionar lutadores ao nó "Lutadores"
    lutadores->addSubtree(kenji);
    lutadores->addSubtree(daigo);
    lutadores->addSubtree(arun);
    lutadores->addSubtree(mali);
    lutadores->addSubtree(akira);
    lutadores->addSubtree(hiro);
    lutadores->addSubtree(surya);
    lutadores->addSubtree(goro);

    auto clearScreen = []() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    };

    // Função para pausar a execução
    auto pressAnyKeyToContinue = []() {
        cout << "\nPressione qualquer tecla para continuar...";
        cin.get();
    };

    auto findNodeByName = [](Node<string>* root, const string& name) -> Node<string>* {
        if (!root) return nullptr;
        queue<Node<string>*> q;
        q.push(root);
        while(!q.empty()){
            Node<string>* current = q.front();
            q.pop();
            if (current->element == name) return current;
            for(Node<string>* child : current->subtrees){
                q.push(child);
            }
        }
        return nullptr;
    };

    int choice;
    do {
        cout << "--- Gerenciador de Menu (Arvore) ---" << endl;
        cout << "1. Visualizar Menu (Arvore Completa)" << endl;
        cout << "2. Inserir Item no Menu" << endl;
        cout << "3. Mover Subarvore" << endl;
        cout << "4. Remover Subarvore" << endl;
        cout << "5. Consultas" << endl;
        cout << "6. Verificar Consistencia da Arvore" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> choice;


        string nodeName1, nodeName2;
        Node<string>* selectedNode1 = nullptr;
        Node<string>* selectedNode2 = nullptr;

        switch (choice) {
            case 1: { // Visualizar Menu
                cout << "--- Menu Atual ---" << endl;
                raiz->printTree();
                pressAnyKeyToContinue();
                break;
            }
            case 2: { // Inserir Item
                cout << "--- Inserir Novo Item no Menu ---\n";
                raiz->printTree();
                cout << "\n";

                // Encontrar o nó pai
                while (selectedNode1 == nullptr) {
                    cout << "Digite o nome do NO PAI onde deseja inserir o novo item: ";
                    getline(cin, nodeName1);
                    selectedNode1 = findNodeByName(raiz, nodeName1);
                    if (selectedNode1 == nullptr) {
                        cout << "No '" << nodeName1 << "' nao encontrado. Tente novamente." << endl;
                    }
                }

                cout << "Digite o nome do NOVO ITEM: ";
                string newItemName;
                getline(cin, newItemName);
                Node<string>* newItem = new Node<string>(newItemName);
                selectedNode1->addSubtree(newItem);

                cout << "Item '" << newItemName << "' inserido em '" << selectedNode1->element << "' com sucesso!" << endl;
                pressAnyKeyToContinue();
                break;
            }
            case 3: { // Mover Subarvore
                cout << "--- Mover Subarvore ---\n";
                raiz->printTree();
                cout << "\n";

                // Nó a ser movido
                while (selectedNode1 == nullptr) {
                    cout << "Digite o nome do NO que deseja MOVER: ";
                    getline(cin, nodeName1);
                    selectedNode1 = findNodeByName(raiz, nodeName1);
                    if (selectedNode1 == nullptr) {
                        cout << "No '" << nodeName1 << "' nao encontrado. Tente novamente." << endl;
                    }
                }

                // Novo nó pai
                while (selectedNode2 == nullptr) {
                    cout << "Digite o nome do NO PAI para onde deseja MOVER: ";
                    getline(cin, nodeName2);
                    selectedNode2 = findNodeByName(raiz, nodeName2);
                    if (selectedNode2 == nullptr) {
                        cout << "No '" << nodeName2 << "' nao encontrado. Tente novamente." << endl;
                    }
                }

                if (selectedNode1 == raiz) {
                    cout << "Erro: Nao e possivel mover a raiz da arvore." << endl;
                } else if (selectedNode1->moveSubtree(selectedNode2)) {
                    cout << "Subarvore '" << selectedNode1->element << "' movida para '" << selectedNode2->element << "' com sucesso!" << endl;
                } else {
                    cout << "Erro ao mover a subarvore. Verifique se o novo pai nao e descendente do no a ser movido ou se nao e o proprio no." << endl;
                }
                pressAnyKeyToContinue();
                break;
            }
            case 4: { // Remover Subarvore
                cout << "--- Remover Subarvore ---\n";
                raiz->printTree();
                cout << "\n";

                // Nó a ser removido
                while (selectedNode1 == nullptr) {
                    cout << "Digite o nome do NO que deseja REMOVER (e todos os seus descendentes): ";
                    getline(cin, nodeName1);
                    selectedNode1 = findNodeByName(raiz, nodeName1);
                    if (selectedNode1 == nullptr) {
                        cout << "No '" << nodeName1 << "' nao encontrado. Tente novamente." << endl;
                    }
                }

                if (selectedNode1 == raiz) {
                    cout << "Erro: Nao e possivel remover a raiz da arvore por esta operacao." << endl;
                } else if (selectedNode1->father) { // Verifica se tem pai antes de tentar remover
                    if (selectedNode1->father->removeSubtree(selectedNode1)) {
                        // O destrutor de Node (~) será chamado recursivamente ao deletar 'selectedNode1'
                        delete selectedNode1;
                        cout << "Subarvore removida com sucesso!" << endl;
                    } else {
                        cout << "Erro: Nao foi possivel remover a subarvore." << endl;
                    }
                } else {
                    cout << "Erro: No sem pai (o que e inesperado para um no nao-raiz aqui)." << endl;
                }
                pressAnyKeyToContinue();
                break;
            }
            case 5: { // Consultas
                cout << "--- Consultas ---\n";
                raiz->printTree();
                cout << "\n";

                int queryChoice;
                do {
                    cout << "\n--- Menu de Consultas ---" << endl;
                    cout << "1. Altura da arvore" << endl;
                    cout << "2. Grau maximo da arvore" << endl;
                    cout << "3. Numero de folhas" << endl;
                    cout << "4. Numero de nos internos" << endl;
                    cout << "5. Percurso pre-ordem" << endl;
                    cout << "6. Percurso pos-ordem" << endl;
                    cout << "7. Percurso em largura (breadth-first)" << endl;
                    cout << "8. LCA (Lowest Common Ancestor) de dois nos" << endl;
                    cout << "9. Caminho(x, y): sequencia de navegacao do item x ate y." << endl;
                    cout << "0. Voltar ao Menu Principal" << endl;
                    cout << "Escolha uma opcao: ";
                    cin >> queryChoice;
                    cout << "--- Resultados da Consulta ---\n";

                    vector<string> resultVector;
                    switch (queryChoice) {
                        case 1:
                            cout << "Altura da arvore: " << raiz->height() << endl;
                            break;
                        case 2: { // Grau máximo da árvore
                            int maxDegree = 0;
                            queue<Node<string>*> q;
                            q.push(raiz);
                            while(!q.empty()){
                                Node<string>* current = q.front();
                                q.pop();
                                maxDegree = max(maxDegree, current->getSubtreesSize()); // Usando getSubtreesSize() para o grau
                                for(Node<string>* child : current->subtrees){
                                    q.push(child);
                                }
                            }
                            cout << "Grau maximo da arvore: " << maxDegree << endl;
                            break;
                        }
                        case 3: { // Numero de folhas
                            int leafCount = 0;
                            queue<Node<string>*> q;
                            q.push(raiz);
                            while(!q.empty()){
                                Node<string>* current = q.front();
                                q.pop();
                                if (current->getSubtreesSize() == 0) { // É uma folha
                                    leafCount++;
                                }
                                for(Node<string>* child : current->subtrees){
                                    q.push(child);
                                }
                            }
                            cout << "Numero de folhas: " << leafCount << endl;
                            break;
                        }
                        case 4: { // Numero de nós internos
                            int internalNodeCount = 0;
                            queue<Node<string>*> q;
                            q.push(raiz);
                            while(!q.empty()){
                                Node<string>* current = q.front();
                                q.pop();
                                if (current->getSubtreesSize() > 0) { // É um nó interno
                                    internalNodeCount++;
                                }
                                for(Node<string>* child : current->subtrees){
                                    q.push(child);
                                }
                            }
                            cout << "Numero de nos internos: " << internalNodeCount << endl;
                            break;
                        }
                        case 5:
                            raiz->preOrder(resultVector);
                            cout << "Percurso Pre-Ordem: ";
                            for (const string& s : resultVector) cout << s << " -> ";
                            cout << "FIM" << endl;
                            break;
                        case 6:
                            raiz->postOrder(resultVector);
                            cout << "Percurso Pos-Ordem: ";
                            for (const string& s : resultVector) cout << s << " -> ";
                            cout << "FIM" << endl;
                            break;
                        case 7:
                            raiz->breadth(resultVector);
                            cout << "Percurso em Largura: ";
                            for (const string& s : resultVector) cout << s << " -> ";
                            cout << "FIM" << endl;
                            break;
                        case 8: { // LCA(x, y)
                            selectedNode1 = nullptr;
                            selectedNode2 = nullptr;
                            while (selectedNode1 == nullptr) {
                                cout << "Digite o nome do PRIMEIRO NO: ";
                                getline(cin, nodeName1);
                                selectedNode1 = findNodeByName(raiz, nodeName1);
                                if (selectedNode1 == nullptr) {
                                    cout << "No '" << nodeName1 << "' nao encontrado. Tente novamente." << endl;
                                }
                            }
                            while (selectedNode2 == nullptr) {
                                cout << "Digite o nome do SEGUNDO NO: ";
                                getline(cin, nodeName2);
                                selectedNode2 = findNodeByName(raiz, nodeName2);
                                if (selectedNode2 == nullptr) {
                                    cout << "No '" << nodeName2 << "' nao encontrado. Tente novamente." << endl;
                                }
                            }
                            Node<string>* lcaNode = raiz->getLCA(selectedNode1, selectedNode2);
                            if (lcaNode) {
                                cout << "LCA de '" << selectedNode1->element << "' e '" << selectedNode2->element << "': " << lcaNode->element << endl;
                            } else {
                                cout << "Nao foi possivel encontrar o LCA (nos nao conectados ou um deles e nulo)." << endl;
                            }
                            break;
                        }
                        case 9: { // Caminho(x, y)
                            selectedNode1 = nullptr;
                            selectedNode2 = nullptr;
                            while (selectedNode1 == nullptr) {
                                cout << "Digite o nome do NO DE PARTIDA (x): ";
                                getline(cin, nodeName1);
                                selectedNode1 = findNodeByName(raiz, nodeName1);
                                if (selectedNode1 == nullptr) {
                                    cout << "No '" << nodeName1 << "' nao encontrado. Tente novamente." << endl;
                                }
                            }
                            while (selectedNode2 == nullptr) {
                                cout << "Digite o nome do NO DE CHEGADA (y): ";
                                getline(cin, nodeName2);
                                selectedNode2 = findNodeByName(raiz, nodeName2);
                                if (selectedNode2 == nullptr) {
                                    cout << "No '" << nodeName2 << "' nao encontrado. Tente novamente." << endl;
                                }
                            }

                            vector<Node<string>*> path;
                            Node<string>* commonAncestor = raiz->getLCA(selectedNode1, selectedNode2);

                            if (commonAncestor) {
                                vector<Node<string>*> path1;
                                Node<string>* current = selectedNode1;
                                while(current != commonAncestor->father) { //
                                    path1.push_back(current);
                                    if(current == commonAncestor) break;
                                    current = current->father;
                                }
                                reverse(path1.begin(), path1.end());

                                vector<Node<string>*> path2;
                                current = selectedNode2;
                                while(current != commonAncestor) {
                                    path2.push_back(current);
                                    current = current->father;
                                }
                                reverse(path2.begin(), path2.end());

                                for (Node<string>* n : path1) {
                                    path.push_back(n);
                                }
                                for (Node<string>* n : path2) {
                                    path.push_back(n);
                                }

                                cout << "Caminho de '" << selectedNode1->element << "' para '" << selectedNode2->element << "': ";
                                for (size_t i = 0; i < path.size(); ++i) {
                                    cout << path[i]->element;
                                    if (i < path.size() - 1) {
                                        cout << " -> ";
                                    }
                                }
                                cout << endl;

                            } else {
                                cout << "Nao foi possivel encontrar um caminho (nos nao conectados)." << endl;
                            }
                            break;
                        }
                        case 0:
                            cout << "Voltando ao Menu Principal." << endl;
                            break;
                        default:
                            cout << "Opcao invalida. Tente novamente." << endl;
                            break;
                    }
                    pressAnyKeyToContinue();
                } while (queryChoice != 0);
                break;
            }
            case 6: { // Verificar Consistencia
                cout << "--- Verificador de Consistencia ---" << endl;
                if (raiz->isConsistent(raiz)) {
                    cout << "A arvore e CONSISTENTE." << endl;
                } else {
                    cout << "A arvore e INCONSISTENTE (ciclo detectado ou problema de raiz)." << endl;
                }
                pressAnyKeyToContinue();
                break;
            }
            case 0: { // Sair
                cout << "Saindo do programa. Ate mais!" << endl;
                break;
            }
            default: {
                cout << "Opcao invalida. Tente novamente." << endl;
                pressAnyKeyToContinue();
                break;
            }
        }
    } while (choice != 0);

    // Libera a memória alocada para a árvore
    delete raiz;

    return 0;
}

