#include "logistics.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;




bool lessProduct(Product* a, Product* b) {
    if (a->getCategory() == b->getCategory())
        return a->getName() < b->getName();

    return a->getCategory() < b->getCategory();
}

/*class Product*/

Product::Product(int id, string n, string c, double w, double p) : productId(id), name(n),category(c), weight(w), price(p) {}

int Product::getId() const { return productId; }
string Product::getName() const { return name; }
double Product::getWeight() const { return weight; }
string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
vector<int> Product::getComponents() const { return componentIds; }

/*class Client*/

Client::Client(int id, const string& n, const string& c) : clientId(id), name(n), city(c) {}

int Client::getId() const { return clientId; }
string Client::getName() const { return name; }
string Client::getCity() const { return city; }
vector<int> Client::getVectorOrdersId() const { return vectorOrdersId; }

int Client::addOrder(int ord1) {
    if (ord1<1) return -1;
    for (int id : vectorOrdersId) {
        if (ord1 == id) return 1; }
 
    vectorOrdersId.push_back(ord1);
    return 0;
}
/*class warehouse*/

Warehouse::Warehouse(int id, const string& c) : warehouseId(id), city(c) {}
Warehouse::Warehouse(int id, const string& c, vector<pair<Product*,int>> vpq) : warehouseId(id), city(c),vectorPQ(vpq) {}

int Warehouse::getId() const { return warehouseId; }
string Warehouse::getCity() const { return city; }
vector<pair<Product*,int>> Warehouse::getVectorPQ() const { return vectorPQ; }
vector<pair<Product*,int>>& Warehouse::getVectorPQUpdate() { return vectorPQ; }
int Warehouse::addProduct(int prodId, int quant, ProductManagement& PrManager) {

    if (quant <= 0)
        return -1;

    Product* prod = nullptr;

    for (auto p : PrManager.getVectorProducts()) {
        if (p->getId() == prodId) {
            prod = p;
            break;
        }
    }

    if (prod == nullptr)
        return -1;
    // procurar produto no vetor
    for (auto &pq : vectorPQ) {
        if (pq.first->getId() == prodId) {
            pq.second += quant;   // atualizar quantidade
            return 1;
        }
    }

    vectorPQ.push_back(make_pair(prod, quant));

    return 0;
}
/*class order*/

Order::Order(int id, Client* cl, Warehouse* war, string dat) : orderId(id), client(cl), warehouse(war), date(dat) {}

int Order::getId() const { return orderId ;}
Client* Order::getClient() const { return client; }
Warehouse* Order::getWarehouse() const { return warehouse; }
vector<ProdQuan*> Order::getVectorProducts() const { return productQuant; }

int Order::addProduct(Product *prod, int quant) {
    if (prod==nullptr || quant<1) return -1;
    for (ProdQuan* pq : productQuant) {
        if (pq->product == prod) { 
        
            pq->quantity += quant;    
            return 1; }
        
        }
    ProdQuan *p=new ProdQuan(prod,quant);
    productQuant.push_back(p);
    return 0;
}

int Order::removeProduct(Product* prod, int quantity) {
    if (prod==nullptr || quantity<1) return -1;
    for (auto it = productQuant.begin(); it != productQuant.end(); ++it) {
        if ((*it)->product == prod) {
            (*it)->quantity -= quantity;
            if ((*it)->quantity <= 0) {
                delete *it;
                productQuant.erase(it);
            }
            return 0;
        }
    }
    return -1;
}

/*class ClientManagement*/

ClientManagement::ClientManagement(){ vectorClients.clear();};
ClientManagement::~ClientManagement(){
    while(vectorClients.size()!=0)
       {

	  	
            delete (vectorClients[vectorClients.size()-1]);
            vectorClients.pop_back();
                
       } 
    }


vector<Client*> ClientManagement::getVectorClients() const { return vectorClients; }

int ClientManagement::clientInsert(Client* cli) {
   if (cli==nullptr) return -1;
    for (auto it = vectorClients.begin(); it != vectorClients.end(); ++it) {
        if ((*it) == cli) {
            return 1;
        }
    }
    vectorClients.push_back(cli);
    return 0; 

}


/*class ProductManagement*/
ProductManagement::ProductManagement(){ vectorProducts.clear();};
ProductManagement::~ProductManagement(){
    while(vectorProducts.size()!=0)
       {

	  	
            delete (vectorProducts[vectorProducts.size()-1]);
            vectorProducts.pop_back();
                
       } 
    }


vector<Product*> ProductManagement::getVectorProducts() const { return vectorProducts; }
 

int ProductManagement::productInsert(Product* prod) {
   if (prod==nullptr) return -1;
    for (auto it = vectorProducts.begin(); it != vectorProducts.end(); ++it) {
        if ((*it) == prod) {
            return 1;
        }
    }
    vectorProducts.push_back(prod);
    return 0; 

}

/*class WarehouseManagement*/
WarehouseManagement::WarehouseManagement(){ vectorWarehouses.clear();};
WarehouseManagement::~WarehouseManagement(){
    while(vectorWarehouses.size()!=0)
       {

	  	
            delete (vectorWarehouses[vectorWarehouses.size()-1]);
            vectorWarehouses.pop_back();
                
       } 
    }


vector<Warehouse*> WarehouseManagement::getVectorWarehouses() const { return vectorWarehouses; }

int WarehouseManagement::warehouseInsert(Warehouse* ware) {
   if (ware==nullptr) return -1;
    for (auto it = vectorWarehouses.begin(); it != vectorWarehouses.end(); ++it) {
        if ((*it) == ware) {
            return 1;
        }
    }
    vectorWarehouses.push_back(ware);
    return 0; 

}

/*class OrderManagement*/
OrderManagement::OrderManagement(){ vectorOrders.clear();};
OrderManagement::~OrderManagement(){
    while(vectorOrders.size()!=0)
       {

	  	
            delete (vectorOrders[vectorOrders.size()-1]);
            vectorOrders.pop_back();
                
       } 
    }


vector<Order*> OrderManagement::getVectorOrders() const { return vectorOrders; }

int OrderManagement::orderInsert(Order* ord) {
   if (ord==nullptr) return -1;
    for (auto it = vectorOrders.begin(); it != vectorOrders.end(); ++it) {
        if ((*it) == ord) {
            return 1;
        }
    }
    vectorOrders.push_back(ord);
    return 0; 

}



int Product::addComponent(int compId, ProductManagement& ProdManagement) {
    if (compId == productId) return -1;
    for (int id : componentIds)
        if (id == compId) return 1;
    bool test=false;
    double w;
    for (Product* prod: ProdManagement.getVectorProducts()) {
        if (compId==prod->getId()) {
            test=true;
            w=prod->getWeight();
            break;
            }

    }
    if (!test) return -1;
    componentIds.push_back(compId);
    if (componentIds.size()==1) { 
            weight=w; 
        } 
        else {
        weight+=w; 
        }
    return 0;
}

void Product::displayProductInfo(ostream& o) const {
    o << productId << " | " << name << " | " << category << " | " << weight << " | " << price ;
   
    if (componentIds.size()>0) {o <<   " | Components: ";}
    for (int id : componentIds) o << id << " ";
    o << endl;
}

int Product::ChecktotalWeight(ProductManagement& ProdManagement) const {
    double soma=0.0;
    if (componentIds.size()==0) {
        return 1;
    } else {
        for (int cmp:componentIds){ 
            for (Product* prod: ProdManagement.getVectorProducts()) {
                if (cmp==prod->getId()) {
                    soma=soma+prod->getWeight();
                    break;
                }
            }
        }
        if (soma==weight) {
            return 1;
        } else return 0;
    }
    return 0;
}


int OrderManagement::updateOrders(string filename, ClientManagement& ClManager, ProductManagement& PrManager, WarehouseManagement& WareManager) {
    ifstream file(filename);
   
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return -1;
    }
    int total=0;
    string line;
    bool existClient=false;
    bool existWarehouse=false;
  //  bool existOrder=false;
    bool existProduct=false;
    Client* cli1;
    Warehouse *ware1;
    Product* prod1;
    while (getline(file, line)) {
        stringstream ss(line);
        int ordId, cliId,wareId,prodId, quant;
        string dat,str;
        
        getline(ss, str, ';');
        ordId = stoi(str);
        getline(ss, str, ';');
        cliId = stoi(str);
        getline(ss, str, ';');
        wareId = stoi(str);
        getline(ss, dat, ';');
        
        //existOrder=false;
        for (Order * ord: getVectorOrders()){
            if (ordId==ord->getId()){
                continue;
            }
        }
       

         existWarehouse=false;
        for (Warehouse * ware: WareManager.getVectorWarehouses()){
            if (wareId==ware->getId()){
                existWarehouse=true;
                ware1=ware;
            }
        }
        if (!existWarehouse) { continue;}
        

        existClient=false;
        for (Client * cli: ClManager.getVectorClients()){
            if (cliId==cli->getId()){
                existClient=true;
                cli1=cli;
            }
        }
        if (!existClient) { continue;}
        Order *ord = new Order(ordId,cli1,ware1,dat);

        while(getline(ss, str, ';')) {
         prodId = stoi(str);
         getline(ss, str, ';');   
         quant = stoi(str); 
          existProduct=false;
        for (Product * prod: PrManager.getVectorProducts()){
            if (prodId==prod->getId()){
                existProduct=true;
                prod1=prod;
            }
        }
        if (!existProduct) { continue;}   

        ord->addProduct(prod1,quant);


        }
       orderInsert(ord);
       cli1->addOrder(ordId);
    total++;
    }
    file.close();
   
    return total; 
}

vector<string> WarehouseManagement::WarehouseWihtProduct(int productId) {
    vector<string> vec;
     
    Product* prod;
   // vector<Product*> vp;
   // vector<int> vq;
    vector<pair<Product*,int>> vpq;
    for (Warehouse* ware : vectorWarehouses) {
       
     //   vp=ware->getVectorProducts();
     //   vq=ware->getQuantProducts();
        vpq=ware->getVectorPQ();
        for (size_t i=0;i<vpq.size();i++) {
            prod=vpq[i].first;

            if (prod->getId()==productId && vpq[i].second>0 ) {
              
                vec.push_back(ware->getCity());
            }
        }
    }

   
    sort(vec.begin(), vec.end());
    

   
    return vec;
}

Shipment::Shipment(int id, Order* ord, string st, string dd, string deld)
    : shipmentId(id), order(ord), status(st), dispatchDate(dd), deliveryDate(deld) {}

int Shipment::getId() const { return shipmentId; }
Order* Shipment::getOrder() const { return order; }
string Shipment::getStatus() const { return status; }
string Shipment::getDispatchDate() const { return dispatchDate; }
string Shipment::getDeliveryDate() const { return deliveryDate; }

ShipmentManagement::ShipmentManagement() {}

ShipmentManagement::~ShipmentManagement() {
    while (!listShipments.empty()) {
        delete listShipments.front();
        listShipments.pop_front();
    }
}

list<Shipment*> ShipmentManagement::getListShipments() const {
    return listShipments;
}

queue<Order*> ShipmentManagement::getPendingOrders() const {
    return queuePendingOrders;
}
priority_queue<Order*, vector<Order*>, CompareOrders>& ShipmentManagement::getPqPendingOrders() {
    return pqPendingOrders;
}

stack<string> ShipmentManagement::getStackOperations() const {
    return stackOperations;
}

int ShipmentManagement::shipmentInsert(Shipment* ship) {
    if (ship == nullptr) return -1;

    for (Shipment* s : listShipments) {
        if (s->getId() == ship->getId())
            return 1;
    }

    listShipments.push_back(ship);
    if (ship->getStatus() == "pending") {
        addPendingOrder(ship->getOrder());
    }
    return 0;
}

int ShipmentManagement::addPendingOrder(Order* ord) {
    if (ord==nullptr)
        return -1;
    for (queue<Order*> tempQueue = queuePendingOrders; !tempQueue.empty(); tempQueue.pop()) {
        if (tempQueue.front() == ord)            return 1;
    }
    queuePendingOrders.push(ord);
    pqPendingOrders.push(ord);
    return 0;
}

void ShipmentManagement::addStockOperation(string op) {
    stackOperations.push(op);
}



int ShipmentManagement::uploadShipments(string filename, OrderManagement& OrdManager) {
    ifstream file(filename);
    if (!file.is_open()) return -1;

    int total = 0;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string str;
        int shipId, orderId;
        string status, dispatchDate, deliveryDate;

        getline(ss, str, ';');
        shipId = stoi(str);

        getline(ss, str, ';');
        orderId = stoi(str);

        getline(ss, status, ';');
        getline(ss, dispatchDate, ';');
        getline(ss, deliveryDate, ';');

        Order* ord = nullptr;
        for (Order* o : OrdManager.getVectorOrders()) {
            if (o->getId() == orderId) {
                ord = o;
                break;
            }
        }

        if (ord == nullptr) continue;

        Shipment* ship = new Shipment(shipId, ord, status, dispatchDate, deliveryDate);

        if (shipmentInsert(ship) == 0) {
            total++;

            if (status == "pending")
                queuePendingOrders.push(ord);
        }
        else {
            delete ship;
        }
    }

    file.close();
    return total;
}
  

int ShipmentManagement::numberOrdersInQueue(int minProducts) {
    if (minProducts < 0) return -1;

    queue<Order*> temp = queuePendingOrders;
    int count = 0;

    while (!temp.empty()) {
        Order* ord = temp.front();
        temp.pop();

        if ((int)ord->getVectorProducts().size() >= minProducts)
            count++;
    }

    return count;
}

int ShipmentManagement::numberDeliveredOnDate(string date) {
    if (date.empty()) return -1;

    int count = 0;

    for (Shipment* ship : listShipments) {
        if (ship->getStatus() == "delivered" &&
            ship->getDeliveryDate() == date) {
            count++;
        }
    }

    return count;
}

string ShipmentManagement::mostReturnedProduct(int &num) {
    num = 0;

    vector<pair<string,int>> prodCounts;

    for (Shipment* ship : listShipments) {
        if (ship->getStatus() == "returned") {
            Order* ord = ship->getOrder();

            for (ProdQuan* pq : ord->getVectorProducts()) {
                string prodName = pq->product->getName();
                int quant = pq->quantity;

                bool found = false;

                for (size_t i = 0; i < prodCounts.size(); i++) {
                    if (prodCounts[i].first == prodName) {
                       
                        prodCounts[i].second += quant;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    prodCounts.push_back(make_pair(prodName, quant));
                }
            }
        }
    }

    string best = "";

    for (size_t i = 0; i < prodCounts.size(); i++) {
        if (prodCounts[i].second > num) {
            num = prodCounts[i].second;
            best = prodCounts[i].first;
        }
        else if (prodCounts[i].second == num && prodCounts[i].first < best) {
            best = prodCounts[i].first;
        }
    }

    return best;
}

int ShipmentManagement::undoLastStockOperation(WarehouseManagement& WareManager, ProductManagement& PrManager) {
    if (stackOperations.empty()) return -1;

    string op = stackOperations.top();
    stackOperations.pop();

    stringstream ss(op);
    string type, str;
    int warehouseId, productId, quantity;

    getline(ss, type, ' ');

    getline(ss, str, ' ');  
    getline(ss, str, ' ');
    getline(ss, str, ' ');
    warehouseId = stoi(str);

    getline(ss, str, ' ');
    getline(ss, str, ' ');
    productId = stoi(str);

    getline(ss, str, ' ');
    getline(ss, str, ' ');
    quantity = stoi(str);
    Warehouse* ware = nullptr;

    for (Warehouse* w : WareManager.getVectorWarehouses()) {
        if (w->getId() == warehouseId) {
            ware = w;
            break;
        }
    }

    if (ware == nullptr) return -1;

    if (type == "ADD") {
        // desfazer ADD => retirar stock
           for (auto &pq : ware->getVectorPQUpdate()) {
            if (pq.first->getId() == productId) {
                if (pq.second >= quantity) {
                    pq.second -= quantity;
                    return 0;
                }
            }
        }
    }
    else if (type == "REMOVE") {
        // desfazer REMOVE => voltar a adicionar
        return ware->addProduct(productId, quantity, PrManager) >= 0 ? 0 : -1;
    }

    return -1;
}

vector<string> ShipmentManagement::productsWithNotEnoughStock(WarehouseManagement& WareManager) {

    vector<pair<string,int>> needed; // produto + quantidade total pedida

    // 1 calcular necessidades totais
    queue<Order*> temp = queuePendingOrders;

    while (!temp.empty()) {
        Order* ord = temp.front();
        temp.pop();

        for (ProdQuan* pq : ord->getVectorProducts()) {
            string name = pq->product->getName();
            int quant = pq->quantity;

            bool found = false;

            for (size_t i = 0; i < needed.size(); i++) {
                if (needed[i].first == name) {
                    needed[i].second += quant;
                    found = true;
                    break;
                }
            }

            if (!found) {
                needed.push_back(make_pair(name, quant));
            }
        }
    }

    vector<string> result;

    //  verificar stock total nos armazéns
   for (int i = 0; i < (int)needed.size(); i++) {

        string prodName = needed[i].first;
        int required = needed[i].second;
        int stock = 0;

        for (Warehouse* w : WareManager.getVectorWarehouses()) {

            for (auto pq : w->getVectorPQ()) {
                if (pq.first->getName() == prodName) {
                    stock += pq.second;
                }
            }
        }

        if (stock < required) {
            result.push_back(prodName);
        } 
    }
    sort(result.begin(), result.end());
 
    return result;
}

// Class ProductBST

    ProductBST::ProductBST() : root(nullptr) {}
    Node* ProductBST::getRoot() const { return root; }
    Node* ProductBST::insert(Node* node, Product* p) {
        if (!node) return new Node(p);

        if (lessProduct(p, node->prod))
            node->left = insert(node->left, p);
        else
            node->right = insert(node->right, p);

        return node;
    }
    void ProductBST::insert(Product* p) {
        root = insert(root, p);
    }


// Class Graph

    Graph::Graph() {}         

  int Graph::getIndex(string name) {
        for (int i = 0; i < (int)nodes.size(); i++) {
            if (nodes[i] == name)
                return i;
        }
        return -1;
    }


    int Graph::addVertex(string name) {
        if (name.empty()) return -1;
        if (getIndex(name) == -1) {
            nodes.push_back(name);
            adj.push_back(vector<pair<int,int>>());
            return 0;
        } else {
            return 1;
        }
        return -1;
    }


    int Graph::addEdge(string u, string v, int weight) {
        if (u.empty() || v.empty() || weight <= 0) return -1;
        int iu = getIndex(u);
        int iv = getIndex(v);

        if (iu == -1 || iv == -1) return -1;

        adj[iu].push_back({iv, weight});
        adj[iv].push_back({iu, weight}); 
        return 0;
    }

    void Graph::buildGraph(ShipmentManagement &ShipManager, WarehouseManagement &WareManager, ProductManagement &ProdManager, string filename) {
        for (Warehouse* ware : WareManager.getVectorWarehouses()) {
            addVertex(ware->getCity());
        }

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file." << endl;
            return; 
        }
        while(getline(file, filename)) {
            stringstream ss(filename);
            string city1, city2;
            int weight;

            getline(ss, city1, ';');
            getline(ss, city2, ';');
            ss >> weight;

            addEdge(city1, city2, weight);
        }
        file.close();       

    }
/**************************/
/*      implemented      */
/**************************/
vector<Product*> ProductBST::top3MostExpensive(Node* node,  string cat) {

    vector<Product*> res;
    vector<Product*> sla;
    if(node == nullptr){
        return res;
    }

    res = top3MostExpensive(node->left, cat);
    sla = top3MostExpensive(node->right, cat);
    res.insert(res.end(), sla.begin(), sla.end());

    if(node->prod->getCategory() == cat){
        res.push_back(node->prod);
    }
    sort(res.begin(), res.end(), [](Product* a , Product* b){
        if(a->getPrice() != b->getPrice()){
            return a->getPrice() > b->getPrice();
        }

        return a->getName() < b->getName();

    });
    if(res.size() > 3){
        res.resize(3);
    }
    return res;

}

vector<pair<string,int>> ProductBST::countCategory(Node* node) {

    
    vector<pair<string,int>> res;
    vector<pair<string,int>> sla;

    if(node == nullptr){
        return res;
    }
    
    res = countCategory(node->left);
    sla = countCategory(node->right);
    for(auto& prods_sla : sla){
        bool encontrou = false;
        for(auto& prods_res : res){
            if(prods_res.first == prods_sla.first){
                encontrou = true;
                prods_res.second += prods_sla.second;
                break;
            }
        }
        if(!encontrou){
            res.push_back(prods_sla);
        }
    }

    string cat_atual = node->prod->getCategory();
    bool encontrou_atual = false;
    for(auto& lala : res){
        if(lala.first == cat_atual){
            lala.second += 1;
            encontrou_atual = true;
            break;
        }
    }
    if(!encontrou_atual){
        res.push_back({cat_atual, 1});
    }

    sort(res.begin(), res.end(), [](pair<string,int> a, pair<string,int> b){
        if(a.second == b.second){
            return a.first < b.first;
        }
        return a.second > b.second;
    });
    
    return res;

}


int ShipmentManagement::updateOrder(Order* target, string type, int productId, int quantity, ProductManagement& PrManager, WarehouseManagement& WareManager) {

    priority_queue<Order*, vector<Order*>, CompareOrders> pendingorder = this->getPqPendingOrders();
    if(target == nullptr || target == NULL || quantity <=0){
        return -2;
    }
    bool encontrado = false;
    if(type != "REMOVE" && type != "ADD"){
        return -3; // tipo invalido
    }
    vector<Product*> vecprod = PrManager.getVectorProducts();
    for(auto product : vecprod){
        if(product->getId() == productId){
            encontrado = true;
        }
    }
    if(!encontrado){
        return -2; //prod nao existe
    }
    encontrado = false;
    while(!pendingorder.empty()){
        if(target == pendingorder.top()){
            encontrado = true;
        }
        pendingorder.pop();
    }
    if(!encontrado){
        return -1; //pedido nao existe
    }
    encontrado = false;
    if(productId < 0){
        return -2; //produto nao existe
    }
    vector<Order*> copy;
    while(pqPendingOrders.top() != target){
        copy.push_back(pqPendingOrders.top());
        pqPendingOrders.pop();
    }
    pqPendingOrders.pop();
    for(auto& prod : (target->getVectorProducts())){
        if((prod->product)->getId() == productId){
            if(type == "ADD"){
                prod->quantity += quantity;
            }
            else{
                if(quantity < prod->quantity){
                    prod->quantity -= quantity;
                }
                else{
                    target->removeProduct(prod->product, prod->quantity);
                    break;
                }
            }
        }
    }
    pqPendingOrders.push(target);
    for(auto prod : copy){
        pqPendingOrders.push(prod);
    }
    return 0;

}
string Graph::mostConnectedCity() {
 
    int maiorn=0;
    string city;
    if(!nodes.empty()){
        city = nodes[0];
    }
    else{
        return "";
    }
    if(adj.empty() || nodes.empty()){
        return "";
    }
    for(int i=0; i<(int)nodes.size(); i++){
        int currsize = (int)adj[i].size();
        if(currsize > maiorn){
            maiorn = currsize;
            city = nodes[i];
        }
        else if(currsize == maiorn){
            if(nodes[i] > city){
                city = nodes[i];
            }
        }
    }
    return city;

}

vector<pair<Product*, Warehouse*>> Graph::deliverSameDay(Order* o, WarehouseManagement& WareManager) {

    if(o == nullptr){
        return {};
    }
    vector<pair<Product*, Warehouse*>> final;
    vector<ProdQuan*> copiaprod = o->getVectorProducts();
    int cidcli = getIndex(o->getClient()->getCity());
    if (cidcli == -1){return {};}
    vector<string> namewareclose;
    namewareclose.push_back(nodes[cidcli]);
    for(int i=0; i<(int)adj[cidcli].size();i++){
        if((adj[cidcli])[i].second <= 50){
            namewareclose.push_back(nodes[(adj[cidcli])[i].first]);
        }
    }
    for(auto wname : namewareclose){
        for(auto ware : WareManager.getVectorWarehouses()){
            if(ware->getCity() == wname){
                for(auto prodware : ware->getVectorPQ()){
                    for(auto& prodorder : copiaprod){
                        int i = 0;
                        if(prodware.first == prodorder->product){
                            if(prodware.second < prodorder->quantity){
                                prodorder->quantity -= prodware.second;
                                final.push_back({(prodorder->product), ware});
                            }
                            else{
                                final.push_back({prodorder->product, ware});
                                copiaprod.erase(copiaprod.begin() + i);
                            }
                        }
                        i++;
                    }
                }
            }
        }
    }
    return final;

}