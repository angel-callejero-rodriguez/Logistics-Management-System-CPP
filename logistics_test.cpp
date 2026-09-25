#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <list>
#include <queue>
#include <stack>
#include "logistics.hpp"

using namespace std;


int verifica_top3MostExpensive(ProductBST &bst)
{
    int er = 0;
    vector<Product*> res=bst.top3MostExpensive(bst.getRoot(),"Audio");
    vector<string> expected={"Colunas Bluetooth 9727", "Colunas Bluetooth 9122", "Colunas Bluetooth 9789"};
    if (res.size()!=3)
    {
        cout << "...verifica_top3MostExpensive: numero de produtos retornados (="<<res.size()<<") e' diferente do esperado (=3) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_top3MostExpensive: numero de produtos retornados (="<<res.size()<<") (ok)" << endl;
        for (size_t i=0;i<res.size();i++) {
            if (res[i]->getName() != expected[i]) {
                cout << "...    verifica_top3MostExpensive: produto na posicao "<< i <<" (="<<res[i]->getName()<<") e' diferente do esperado (="<<expected[i]<<") (ERRO)"<< endl;
                er++;
            }
            else
                cout << "...verifica_top3MostExpensive: produto na posicao "<< i <<" (="<<res[i]->getName()<<") (ok)" << endl;
        }
    } 
    return er;
}




int verifica_countCategory(ProductBST &bst)
{
    int er = 0;
    vector<pair<string,int>> res=bst.countCategory(bst.getRoot());
    vector<pair<string,int>> expected={{"Informática",4},{"Audio",3}};
    if (res.size()!=2)
    {
        cout << "...verifica_countCategory: numero de categorias retornadas (="<<res.size()<<") e' diferente do esperado (=2) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_countCategory: numero de categorias retornadas (="<<res.size()<<") (ok)" << endl;
        for (size_t i=0;i<res.size();i++) {
            if (res[i].first != expected[i].first || res[i].second != expected[i].second) {
                cout << "...    verifica_countCategory: categoria na posicao "<< i <<" (="<<res[i].first<<" - "<<res[i].second<<") e' diferente do esperado (="<<expected[i].first<<" - "<<expected[i].second<<") (ERRO)"<< endl;
                er++;
            }
            else
                cout << "...verifica_countCategory: categoria na posicao "<< i <<" (="<<res[i].first<<" - "<<res[i].second<<") (ok)" << endl;
        }
    } 
    return er;
}
   


int verifica_updateOrder(ShipmentManagement &ShipManager, ProductManagement &ProdManager,WarehouseManagement &WareManager)
{
    int er = 0;
  vector<Order*> temp;
 priority_queue<Order*, vector<Order*>, CompareOrders> shpq=    ShipManager.getPqPendingOrders();
    while (!shpq.empty()) {
        temp.push_back(shpq.top());
        shpq.pop();
        
    }
    Order* target = temp[0];
    
    for (Order* o : temp) {
        ShipManager.addPendingOrder(o);
    }
    int res=ShipManager.updateOrder(target, "ADD", 1, 2, ProdManager, WareManager);

    if (res!=0)
    {
        cout << "...verifica_updateOrder: retorno(="<<res<<") e' diferente do esperado (=0) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_updateOrder: retorno (="<<res<<") (ok)" << endl;
     
       int quant=target->getVectorProducts()[0]->quantity;
             if (quant!=4)
             {
                 cout << "...verifica_updateOrder: quantidade do produto 1 no pedido (="<<quant<<") e' diferente do esperado (=4) (ERRO)"<< endl ;
                    er++;
             }
             else 
                 cout << "...verifica_updateOrder: quantidade do produto 1 no pedido (="<<quant<<") (ok)" << endl;     
     
                      
      
    }
    return er;
}   

int verifica_mostConnectedCity(Graph &graph)
{
    int er = 0;
    string res=graph.mostConnectedCity();
   
    if (res!="Porto")
        {
            cout << "...verifica_mostConnectedCity: cidade retornada (="<<res<<") e' diferente do esperado (=Porto) (ERRO)"<< endl ;
            er++;
        }
        else {
            cout << "...verifica_mostConnectedCity: cidade retornada (="<<res<<") (ok)" << endl;
        
        }               
    return er;

}


int verifica_DeliverSameDay(Graph &graph, WarehouseManagement &wareManager, OrderManagement &OrderManager)
{
    int er = 0;
    Order* o=OrderManager.getVectorOrders()[3];
        vector<pair<Product*, Warehouse*>>  res=graph.deliverSameDay(o, wareManager);
         vector<pair<string,string>> expected={{"Rato Óptico 6644","Braga"},{"Colunas Bluetooth 9727","Braga"},{"Rato e colunas","Espinho"}}    ;
        string strtotal;    

  if (res.size()!=3)
    {
        cout << "...verifica_DeliverSameDay: numero de conjuntos de produtos armazens retornadas (="<<res.size()<<") e' diferente do esperado (=3) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_DeliverSameDay: numero de conjuntos de produtos armazens retornadas (="<<res.size()<<") (ok)" << endl;
        for (size_t i=0;i<res.size();i++) {
            if (res[i].first->getName() != expected[i].first || res[i].second->getCity() != expected[i].second) {
                cout << "...    verifica_DeliverSameDay: conjunto na posicao "<< i <<" (="<<res[i].first->getName()<<" - "<<res[i].second->getCity()<<") e' diferente do esperado (="<<expected[i].first<<" - "<<expected[i].second<<") (ERRO)"<< endl;
                er++;
            }
            else
                cout << "...verifica_DeliverSameDay: conjunto na posicao "<< i <<" (="<<res[i].first->getName()<<" - "<<res[i].second->getCity()<<") (ok)" << endl;
        }
    } 
    
    return er;
}


int importClients (string filename, ClientManagement &cliManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open clients.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    Client* cli;
    stringstream ss;
    int cliI;
    while (getline(file, line)) {
        
        string cliId,nam, ci;
        
            
        ss.clear();
        ss << line; 
        cliId.clear();
        
        getline(ss, cliId, ';');
        cliI=stoi(cliId);
        getline(ss, nam, ';');
        getline(ss, ci, ';');
        
        
     
        cli = new Client(cliI, nam, ci);
       
       cliManager.clientInsert(cli);
        count++;
    }
   
    
    file.close();


    return count;

}

int importProducts (string filename, ProductManagement &prodManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open products.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    Product* prod;
    stringstream ss;
    int proI,compI;
    float wei,pri;
     string proId,nam, ca, we,pr,comp;
    while (getline(file, line)) {
        
       
         
        ss.clear();
        ss << line; 
              
        getline(ss, proId, ';');
        proI=stoi(proId);
        getline(ss, nam, ';');
        getline(ss, ca, ';');
        getline(ss, we, ';');
        getline(ss, pr, ';');
        wei=stof(we);
        pri=stof(pr);
     
        prod = new Product(proI, nam, ca, wei, pri);
        prodManager.productInsert(prod);
       while(getline(ss, comp, ';')){
            compI=stoi(comp);
            prod->addComponent(compI, prodManager);
        }
        prodManager.productInsert(prod);
        count++;
    }
   
    
    file.close();


    return count;

}

int importWarehouses (string filename, WarehouseManagement &WareManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open warehouse.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    Warehouse* ware;
    stringstream ss;
    int wareI;
    while (getline(file, line)) {
        
        string wareId,ci;
        
            
        ss.clear();
        ss << line; 
        wareId.clear();
        
        getline(ss, wareId, ';');
        wareI=stoi(wareId);
        getline(ss, ci, ';');
             
        ware = new Warehouse(wareI, ci);
        WareManager.warehouseInsert(ware);
        count++;
    }
   
    
    file.close();


    return count;

}


int importWarehouses_stock (string filename, WarehouseManagement &WareManager, ProductManagement &ProdManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open warehouse_stock.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
 
    stringstream ss;
    vector<Warehouse*> vectorWarehouses=WareManager.getVectorWarehouses();
    int wareI,prodI,quant;
    while (getline(file, line)) {
        
        string wareId,prod,quan;
        
            
        ss.clear();
        ss << line; 
        wareId.clear();
        
        getline(ss, wareId, ';');
        wareI=stoi(wareId);
        getline(ss, prod, ';');
        getline(ss, quan, ';');
        prodI=stoi(prod);
        quant=stoi(quan);
             
        for (Warehouse* ware: vectorWarehouses){
            if (wareI==ware->getId()){
                ware->addProduct(prodI,quant, ProdManager);
                count++;
            }
        }
        
    }
   
    
    file.close();


    return count;

}


int importShipments (string filename,ShipmentManagement &ShipManager, OrderManagement &OrderManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to openshipments_realistic.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    vector<Order*> VO=OrderManager.getVectorOrders();
    stringstream ss;
     Order* ord1=nullptr;
     bool existOrder=false;
   int shI,ordI;
    while (getline(file, line)) {
        
        string shId,ord,sta,diDate,deDate;
        
            
        ss.clear();
        ss << line; 
        
        
        getline(ss, shId, ';');
        shI=stoi(shId);
        getline(ss, ord, ';');
        ordI=stoi(ord);
        getline(ss, sta, ';');
        getline(ss, diDate, ';');
        getline(ss, deDate, ';');
          
        existOrder=false;     
        for (Order* orde: VO){
            if (ordI==orde->getId()){
                existOrder=true;
                ord1=orde;
            }
        }
        if (!existOrder) { continue;}
        Shipment* ship=new Shipment(shI,ord1,sta,diDate,deDate);
        ShipManager.shipmentInsert(ship);
        count++;
    }
   
    
    file.close();


    return count;

}

int fillBST(ProductBST &bst, ProductManagement &prodManager) {
    int count = 0;
    vector<Product*> products = prodManager.getVectorProducts();
    for (Product* prod : products) {
        bst.insert(prod);
        count++;
    }
    return count;
}

int main()
{

    int errorCount = 0, error;

    cout << "INICIO DOS TESTES MAIS BASICOS\n\n" << endl;
   
    ClientManagement cliManager;
    int a=importClients("clientsSmall.csv",cliManager);
    cout <<"Importou: "<<a<<" clientes "<<endl;

    WarehouseManagement wareManager;
  //  int b=importWarehouses("warehouses.csv",wareManager);
  //  cout <<"Importou: "<<b<<" warehouses "<<endl <<endl;

    ProductManagement ProdManager;
    Product *prod1=new Product(1,"Rato Óptico 6644","Informática",7.2,1407.83);
    Product *prod2=new Product(2,"Colunas Bluetooth 9727","Audio",0.21,1297.53);
    Product *prod3=new Product(3,"Rato e colunas","Informática",10.72,631.16);
    Product *prod4=new Product(4,"Colunas Bluetooth 9789","Audio",12.77,131.16);
    Product *prod5=new Product(5,"Colunas Bluetooth 9122","Audio",15.72,331.45);
    Product *prod6=new Product(6,"Rato 123","Informática",1.72,31.16);
     Product *prod7=new Product(7,"Rato 34","Informática",2.72,31.16);
     
    ProdManager.productInsert(prod1);
    ProdManager.productInsert(prod2);
    ProdManager.productInsert(prod3);
    ProdManager.productInsert(prod4);
    ProdManager.productInsert(prod5);
    ProdManager.productInsert(prod6);   
     ProdManager.productInsert(prod7);
    
    OrderManagement OrdManager;

    vector<pair<Product*,int>> vpq1;
    pair<Product*,int> p1(prod1,16);
    pair<Product*,int> p2(prod2,4);
    vpq1.push_back(p1);
    vpq1.push_back(p2);
   
    vector<pair<Product*,int>> vpq2;
    pair<Product*,int> p3(prod3,6);
    vpq2.push_back(p3);
    vpq2.push_back(p2);


    Warehouse* ware1=new Warehouse(1,"Braga",vpq1);
    Warehouse* ware2=new Warehouse(2,"Setúbal",vpq1);
    Warehouse* ware3=new Warehouse(3,"Porto");
    Warehouse* ware4=new Warehouse(4,"Lisboa",vpq2);
    Warehouse* ware5=new Warehouse(5,"Espinho",vpq2);
    Warehouse* ware6=new Warehouse(6,"Penafiel");
    wareManager.warehouseInsert(ware1);
    wareManager.warehouseInsert(ware2);
    wareManager.warehouseInsert(ware3);
    wareManager.warehouseInsert(ware4);
    wareManager.warehouseInsert(ware5);
    wareManager.warehouseInsert(ware6);
    OrdManager.updateOrders("orders.csv",cliManager, ProdManager,wareManager);


    ShipmentManagement ShipManager;
    Shipment* ship1=new Shipment(1,OrdManager.getVectorOrders()[0],"pending","01-01-2026","08-01-2026");
    Shipment* ship2=new Shipment(2,OrdManager.getVectorOrders()[1],"pending","02-01-2026","06-01-2026");
    Shipment* ship3=new Shipment(3,OrdManager.getVectorOrders()[2],"pending","03-01-2026","07-01-2026");
    Shipment* ship4=new Shipment(4,OrdManager.getVectorOrders()[3],"pending","04-01-2026","08-01-2026");
    Shipment* ship5=new Shipment(5,OrdManager.getVectorOrders()[4],"delivered","05-01-2026","08-01-2026");
    Shipment* ship6=new Shipment(6,OrdManager.getVectorOrders()[5],"delivered","06-01-2026","08-01-2026");
Shipment* ship7=new Shipment(7,OrdManager.getVectorOrders()[6],"delivered","06-01-2026","08-01-2026");

   
    ShipManager.shipmentInsert(ship1);
    ShipManager.shipmentInsert(ship2);
    ShipManager.shipmentInsert(ship3);
    ShipManager.shipmentInsert(ship4);
    ShipManager.shipmentInsert(ship5);
    ShipManager.shipmentInsert(ship6);
      ShipManager.shipmentInsert(ship7);

    ShipManager.addPendingOrder(OrdManager.getVectorOrders()[0]);
    ShipManager.addPendingOrder(OrdManager.getVectorOrders()[1]);
    ShipManager.addPendingOrder(OrdManager.getVectorOrders()[2]);
    ShipManager.addPendingOrder(OrdManager.getVectorOrders()[3]);

   ProductBST bst;
   int count = fillBST(bst, ProdManager);
   cout << "BST preenchida com " << count << " produtos." << endl;

    Graph graph;
    graph.buildGraph(ShipManager, wareManager, ProdManager, "cities.csv");


    error = verifica_top3MostExpensive(bst);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_top3MostExpensive\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_top3MostExpensive passou\n\n" << endl;
    } 

    error = verifica_countCategory(bst);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_countCategory\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_countCategory  passou\n\n" << endl;
    }  
  

    error = verifica_updateOrder(ShipManager, ProdManager, wareManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_updateOrder\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_updateOrder passou\n\n" << endl;
    } 

    error = verifica_mostConnectedCity(graph);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_mostConnectedCity\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_mostConnectedCity passou\n\n" << endl;
    } 

   
     error = verifica_DeliverSameDay(graph, wareManager, OrdManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_DeliverSameDay\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_DeliverSameDay passou\n\n" << endl;
    } 


     if (errorCount == 0)
        cout << "FIM DOS TESTES: Todos os testes passaram\n" << endl;
    else
        cout << "FIM DOS TESTES: Foram encontrados "<< errorCount << " ERROS no total\n" << endl;

    return 0;
}

