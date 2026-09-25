#ifndef LOGISTICS_HPP
#define LOGISTICS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <stack>
using namespace std;

/* CLASSES */

class Product; /** @brief Class to represent a product. */
class Client; /** @brief Class to represent a client. */
class Warehouse; /** @brief Class to represent a warehouse. */
class Order; /** @brief Class to represent a Order. */
class ProductManagement; /** @brief Class to represent all products. */
class ClientManagement; /** @brief Class to represent all clients. */
class WarehouseManagement; /** @brief Class to represent all warehouses. */
class Shipment; /** @brief Class to represent a shipment. */
class ShipmentManagement; /** @brief Class to represent all shipments. */
class ProductBST; /** @brief Class to represent a binary search tree of products.   */
class Graph; /** @brief Class to represent a graph of cities. */

/* STRUCTS */
struct ProdQuan {
    Product *product; /** @brief pointer to product. */
    int quantity; /** @brief  quantity of the product*/
    /* --- Constructor --- */
    ProdQuan(Product *prod, int quant): product(prod), quantity(quant) {} 
};

struct Node {
        Product* prod; /** @brief pointer to product. */
        Node* left;  /** @brief pointer to left node. */
        Node* right; /** @brief pointer to right node. */
        /* --- Constructor --- */
        Node(Product* p) : prod(p), left(nullptr), right(nullptr) {}
};

class Product {
private:
    /* ATTRIBUTES */
    int productId; /** @brief product id */
    string name; /** @brief name */
    string category; /** @brief name */
    double weight; /** @brief weight */
    double price; /** @brief price */
    vector<int> componentIds; /** @brief Vector with all products components */
   
public:
    /* METHODS */

    /* --- Constructor --- */
    /** 
    *  @brief Product (parameterized) - Create an object of the class Product.
    *  @param id Product Id.
    *  @param n Name of the product.
    *  @param c Category of the product.
    *  @param w Weight of the product.
    *  @param p price of the product.
    *  @note  Initialize each attribute with the corresponding argument.
     */
    Product(int id, string n, string c, double w, double p); 

    /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the product's productId.
    *  @return 'productId' attribute.
    */
    int getId() const;

    /** 
    *  @brief  Get the product's name.
    *  @return 'name' attribute.
    */
    string getName() const;

       /** 
    *  @brief  Get the product's category.
    *  @return 'category' attribute.
    */
    string getCategory() const;

    /** 
    *  @brief  Get the product's weight.
    *  @return 'weight' attribute.
    */
    double getWeight() const;

    /** 
    *  @brief  Get the product's price.
    *  @return 'price' attribute.
    */
    double getPrice() const;

    /** 
    *  @brief  Get the all products that are part of this product.
    *  @return 'componentIds' attribute.
    */
    vector<int> getComponents() const;
 
    /* --- Other Methods --- */

    /** 
    *  @brief  Add a new product to a composite product.
    *  @param  productId product Id.
    *  @param  ProdManager Object with all the products in the platform.
    *  @return 0 if the new products is added successfully | 1 if the new product already exists |
    *  @return -1 if the parameteres are invalid or compoent not exist
    */
    int addComponent(int productId, ProductManagement& ProdManagement);

    /** 
    *  @brief  Display the information of a Product.
    *  @return void
    */
    void displayProductInfo(ostream& o) const;

    /** 
    *  @brief Check if the product weight is equal to the total weight of all components products.
    *  @param  ProdManager Object with all the products in the platform.
    *  @return If there are no components, it returns 1.
    *  @return For components products, return 1 if equal and 0 if different.
    */
    int ChecktotalWeight(ProductManagement& ProdManagement) const;
};

class Client {
private:
    /* ATTRIBUTES */
    int clientId; /** @brief client id */
    string name; /** @brief name */
    string city; /** @brief city*/
    vector<int> vectorOrdersId; /** @brief Vector with orders id */
public:
    /* METHODS */

    /* --- Constructor --- */
    /** 
    *  @brief Client (parameterized) - Create an object of the class client.
    *  @param id Product Id.
    *  @param n Name of the client.
    *  @param c City of the client.
   
    *  @note  Initialize each attribute with the corresponding argument.
     */
    Client(int id, const string& n, const string& c) ;

     /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the client's clientId.
    *  @return 'clientId' attribute.
    */
    int getId() const;

    /** 
    *  @brief  Get the client's name.
    *  @return 'name' attribute.
    */
    string getName() const;

    /** 
    *  @brief  Get the client's city.
    *  @return 'city' attribute.
    */
    string getCity() const;

    /** 
    *  @brief  Get the all orders which belong to the client.
    *  @return 'listOrdersId' attribute.
    */
    vector<int> getVectorOrdersId() const;
        

  /** 
    *  @brief  Add a new order to a client.
    *  @param  ordId pointer to order.
    *  @return 0 if the new orderId is added successfully | 1 if the new orderId already exists |
    *  @return -1 if the parameteres are invalid or compoent not exist
    */
    int addOrder(int ordId);
};

class Warehouse {
private:
    /* ATTRIBUTES */
    int warehouseId; /** @brief warehouse id */
    string city;  /** @brief city */
    vector<pair<Product*,int>> vectorPQ; 
public:
    /* METHODS */

    /* --- Constructor --- */
    /** 
    *  @brief Warehouse (parameterized) - Create an object of the class warehouse.
    *  @param id Warehouse Id.
    *  @param c city.
    *  @param vp vector with all products.
    *  @param qp vector with all quantity.
    *  @note  Initialize each attribute with the corresponding argument.
     */
    Warehouse(int id, const string& c);
    Warehouse(int id, const string& c, vector<pair<Product*,int>> vpq);

    /* --- Get Methods --- */

    /** 
    *  @brief  Get the warehouse's warehouseId.
    *  @return 'warehouseId' attribute.
    */
    int getId() const;

    /** 
    *  @brief  Get the warehouse's city.
    *  @return 'city' attribute.
    */
    string getCity() const;


     /** 
    *  @brief  Get vector of pair of produxts and quantities.
    *  @return 'getVectorPQ' attribute.
    */
    vector<pair<Product*,int>> getVectorPQ() const;
    vector<pair<Product*,int>>& getVectorPQUpdate() ;

      /** 
    *  @brief  insert a product and its quantity into a warehouse.
    *  @param proI Id of the product.
    *  @param quant Quantity of the product.
    *  @return -1 if the parameteres are invalid or product not exist | 0 if the new product is added successfully | 1 if the new product already exists and the quantity is updated
    */
   int addProduct(int prodI, int quant, ProductManagement& PrManager);
};

class Order {
private:
    /* ATTRIBUTES */
    int orderId; /** @brief order id */
    Client* client; /** @brief pointer to client */
    Warehouse* warehouse; /** @brief pointer to warehouse */
    string date; /** @brief date of the order */
    vector<ProdQuan*> productQuant; /** @brief Vector with all produtcs and quantity  */
public:
    /* METHODS */

    /* --- Constructor --- */
    /** 
    *  @brief Order (parameterized) - Create an object of the class Order.
    *  @param id Order Id.
    *  @param cl  pointer to client.
    *  @param war pointer to warehouse.
    *  @param dat Date.
    *  @note  Initialize each attribute with the corresponding argument.
     */
    Order(int id,Client *cl,Warehouse *war,string dat);

       /* --- Get Methods --- */

    /** 
    *  @brief  Get the order's orderId.
    *  @return 'orderId' attribute.
    */
    int getId() const;

    /** 
    *  @brief  Get the order's client.
    *  @return 'client' attribute.
    */
    Client* getClient() const;

       /** 
    *  @brief  Get the order's warehouse.
    *  @return 'warehouse' attribute.
    */
    Warehouse* getWarehouse() const;

    /** 
    *  @brief  Get the vector wiht all products and quantity off the order.
    *  @return 'productQuant' attribute.
    */
    vector<ProdQuan*> getVectorProducts() const;
    
      /** 
    *  @brief  Add a new product to a order.
    *  @param  productId pointer to product.
    *  @param  quant Quantity of the product.
    *  @return 0 if the new product is added successfully | 1 if the new product already exists |
    *  @return -1 if the parameteres are invalid or compoent not exist
    */
    int addProduct(Product* prod, int quant);

    /** 
    *  @brief  Remove a product from an order.
    *  @param  productId pointer to product.
    *  @param  quant Quantity of the product.
    *  @return 0 if the product is removed successfully | -1 if the parameteres are invalid or compoent not exist
    */
    int removeProduct(Product* prod, int quantity);
};

class ClientManagement {
private:
    /* ATTRIBUTES */
    vector<Client*> vectorClients; /** @brief vector with all clients. */

public:
    /* METHODS */

    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class ClientManagement.
    *  @note  Make sure the vector 'vectorClients' is empty.
    */
     ClientManagement();

    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the vector 'vectorClients'.
    */
    ~ClientManagement();

    /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the vector with all the Clients.
    *  @return 'vectorClients' attribute.
    */
    vector<Client*> getVectorClients() const;

    /** 
    *  @brief  Add a new client.
    *  @param  cli New client to be added.
    *  @return 0 if the client is added successfully | -1 if the parameter is invalid | 1 if the client already exists in the vector
    */
    int clientInsert(Client* cli);
};

class ProductManagement {
private:
    /* ATTRIBUTES */
    vector<Product*> vectorProducts; /** @brief vector with all products. */

public:
    /* METHODS */

    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class ProductManagement.
    *  @note  Make sure the vector 'vectorProducts' is empty.
    */
     ProductManagement();

    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the vector 'vectorProducts'.
    */
    ~ProductManagement();

    /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the vector with all the Products.
    *  @return 'vectorProducts' attribute.
    */
    vector<Product*> getVectorProducts() const;
    

    /** 
    *  @brief  Add a new product.
    *  @param  prod New product to be added.
    *  @return 0 if the product is added successfully | -1 if the parameter is invalid | 1 if the product already exists in the vector
    */
    int productInsert(Product* prod);
};

class WarehouseManagement {
private:
    /* ATTRIBUTES */
    vector<Warehouse*> vectorWarehouses; /** @brief vector with all warehouses. */

public:
    /* METHODS */

    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class WarehouseManagement.
    *  @note  Make sure the list 'vectorWarehouses' is empty.
    */
     WarehouseManagement();

    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the vector 'vectorWarehouses'.
    */
    ~WarehouseManagement();

    /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the vector with all the Warehouse.
    *  @return 'vectorWarehouses' attribute.
    */
    vector<Warehouse*> getVectorWarehouses() const;

     /* --- Other Methods --- */

    /** 
    *  @brief  Add a new warehouse.
    *  @param  prod New warehouse to be added.
    *  @return 0 if the warehouse is added successfully | -1 if the parameter is invalid | 1 if the warehouse already exists in the vector
    */
    int warehouseInsert(Warehouse* ware); 

  
    /** 
    *  @brief  List with the name of the city of the warehouses wiht a give product.
    *  @param  productId  product.
    *  @return vector with the name of the warehouses ordered in ascending order
    */ 
    vector<string> WarehouseWihtProduct(int productId);
};



class OrderManagement {
private:
    /* ATTRIBUTES */
    vector<Order*> vectorOrders; /** @brief vector with all orders. */

public:
    /* METHODS */

    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class OrderManagement.
    *  @note  Make sure the list 'vectorOrders' is empty.
    */
     OrderManagement();

    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the vector 'vectorOrders'.
    */
    ~OrderManagement();

    /* --- Get Methods --- */
        
    /** 
    *  @brief  Get the vector with all the Orders.
    *  @return 'vectorOrders' attribute.
    */
    vector<Order*> getVectorOrders() const;

     /* --- Other Methods --- */

    /** 
    *  @brief  Add a new warehouse.
    *  @param  prod New warehouse to be added.
    *  @return 0 if the warehouse is added successfully | -1 if the parameter is invalid | 1 if the warehouse already exists in the vector
    */
    int orderInsert(Order* ord); 

    /** 
    *  @brief  Update the orders in the vector of the orders and in the clients by reading a text file.
    *  @param  filename Filename of the text file containing the orders information.
    *  @param  ClManager Object with all the clients in the platform.
    *  @param  PrManager Object with all the products in the platform.
    *  @param  WareManager Object with all the warehouse in the platform.
    *  @return number of orders registed | -1 if an error occurs
    *  @note   Each line of the file contains the required information in the following format: OrderId;ClientId;warehouseId;date;product1Id;quant1;product2Id;quant2…
    *  @note   Other functions implemented in this library can be used to implement this method.
    *  @note   Check:
    *  @note    -> client exists  : NO  -ignore this line | YES - update the vector
    *  @note    -> warehouse exists: NO  - ignore this line | YES - update the vetor
    *  @note    -> product exists: NO  - only ignore this product not ignore this line
    */ 
    int updateOrders(string filename, ClientManagement& ClManager, ProductManagement& PrManager, WarehouseManagement& WareManager);


};
class Shipment {
private:
    int shipmentId; /** @brief Unique identifier for the shipment. */
    Order* order;   /** @brief Pointer to the order associated with the shipment. */
    string status;  /** @brief Status of the shipment. (pending, delivered, returned)*/        
    string dispatchDate; /** @brief Date when the shipment was dispatched. */
    string deliveryDate; /** @brief Date when the shipment was delivered. */

public:
       /* METHODS */

    /* --- Constructor --- */
    /** 
    *  @brief Shipment (parameterized) - Create an object of the class Shipment.
    *  @param id Shipment Id.
    *  @param ord pointer to order.
    *  @param st Status of the shipment.
    *  @param dd Dispatch date of the shipment.
    *  @param deld Delivery date of the shipment.
    *  @note  Initialize each attribute with the corresponding argument.
     */ 
    Shipment(int id, Order* ord, string st, string dd, string deld); 

     /* --- Get Methods --- */
     
     /** 
    *  @brief  Get the shipment's shipmentId.
    *  @return 'shipmentId' attribute.
    */
    int getId() const;
    /**
    *  @brief  Get the shipment's order.
    *  @return 'order' attribute.
    */
    Order* getOrder() const;
    /**
    *  @brief  Get the shipment's status.
    *  @return 'status' attribute.
    */
    string getStatus() const;
    /**
    *  @brief  Get the shipment's dispatch date.
    *  @return 'dispatchDate' attribute.
    */
    string getDispatchDate() const;
    /**
    *  @brief  Get the shipment's delivery date.
    *  @return 'deliveryDate' attribute.
    */
    string getDeliveryDate() const;
};

struct CompareOrders {
    bool operator()(Order* a, Order* b) {
        // nº de produtos
        int na = a->getVectorProducts().size();
        int nb = b->getVectorProducts().size();

        if (na == nb) {
            // desempate por peso total
            double wa = 0, wb = 0;

            for (auto pq : a->getVectorProducts())
                wa += pq->product->getWeight() * pq->quantity;

            for (auto pq : b->getVectorProducts())
                wb += pq->product->getWeight() * pq->quantity;

            return wa < wb; // maior peso → maior prioridade
        }

        return na < nb; // mais produtos → maior prioridade
    }
};


class ShipmentManagement {
private:
    list<Shipment*> listShipments;/*brief List of all shipments */
    queue<Order*> queuePendingOrders; /*brief Queue of pending orders */
    priority_queue<Order*, vector<Order*>, CompareOrders> pqPendingOrders; /*brief Priority queue of pending orders, ordered by the number of products in the order (orders with more products have higher priority) */ 
    stack<string> stackOperations; /*brief Stack of stock operations (e.g., "ADD to warehouse X product Y with Z", "REMOVE from warehouse X product Y with Z") */

public:
        /* METHODS */
    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class ShipmentManagement.
    *  @note  Make sure the list 'listShipments', the queue 'queuePendingOrders' and the stack 'stackOperations' are empty.
    */
    ShipmentManagement();
    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the list 'listShipments', the queue 'queuePendingOrders' and the stack 'stackOperations'.
    */
    ~ShipmentManagement();
    /* --- Get Methods --- */
            
    /**   
     * @brief  Get the list with all the Shipments.
     * @return 'listShipments' attribute.
     */
    list<Shipment*> getListShipments() const;
    /**
     * @brief  Get the queue with all the pending orders.
     * @return 'queuePendingOrders' attribute.
     */
    queue<Order*> getPendingOrders() const;

      /**
     * @brief  Get the priority queue with all the pending orders.
     * @return 'pqPendingOrders' attribute.
     */
    priority_queue<Order*, vector<Order*>, CompareOrders>& getPqPendingOrders() ;
    /**
     * @brief  Get the stack with all the stock operations.
     * @return 'stackOperations' attribute.
     */
    stack<string> getStackOperations() const;
        /* --- Other Methods --- */

    /** 
    *  @brief  Add a new shipment.
    *  @param  ship New shipment to be added.
    *  @return 0 if the shipment is added successfully | -1 if the parameter is invalid | 1 if the shipment already exists in the list
    */      
    int shipmentInsert(Shipment* ship);

    /**
     * @brief   Add a new pending order to the queue of pending orders.     
     * @param ord New order to be added to the queue of pending orders.
     * @return 0 if the order is added successfully | -1 if the parameter is invalid | 1 if the order already exists in the queue
     * @note   An order is considered pending if it has been placed but not yet dispatched.
     */
    int addPendingOrder(Order* ord);

    /**
    * @brief   Add a new stock operation to the stack of stock operations.
    * @param op Description of the stock operation to be added to the stack.
    * @return void
    * @note   Stock operations can include actions such as adding or removing products from warehouses, updating product quantities, etc.
    */
    void addStockOperation(string op);


    /*  @brief  Count the number of orders in the queue of pending orders that have at least a product with a quantity greater than or equal to a given value.
    *  @param  minProducts Minimum quantity of products to be considered.
    *  @return Number of orders in the queue of pending orders that have at least a product with a quantity greater than or equal to 'minProducts'.
    */
    int numberOrdersInQueue(int minProducts);

    /*  @brief  Count the number of shipments with a status of "delivered" that were delivered on a specific date.
    *  @param  date Date to be checked (format: "DD-MM-YYYY").
    *  @return Number of shipments with a status of "delivered" that were delivered on the specified date.
    */
    int numberDeliveredOnDate(string date);

  

    /*  @brief  Update the shipments in the list of shipments by reading a text file.
    *  @param  filename Name of the text file to read.
    *  @param  OrdManager Reference to the order management object.
    *  @return 0 if the shipments are updated successfully | -1 if the parameter is invalid.
    */
    int uploadShipments(string filename, OrderManagement& OrdManager);
    
    /*  @brief  Undo the last stock operation performed by popping the last operation from the stack of stock operations and reversing its effect on the warehouses and products.
    *  @param  WareManager Reference to the warehouse management object.
    *  @param  PrManager Reference to the product management object.
    *  @return 0 if the last stock operation is undone successfully | -1 if the stack of stock operations is empty or if an error occurs while undoing the operation.
    *  @note   The function should parse the description of the last stock operation to determine what action was
    *  @note  if the last operation was "ADD to warehouse X product Y with Z", the function should remove product Y from warehouse X with quantity Z. if the last operation was "REMOVE from warehouse X product Y with Z", the function should add product Y to warehouse X with quantity Z.
    */
    int undoLastStockOperation(WarehouseManagement& WareManager, ProductManagement& PrManager);
/*  @brief  Identify the most returned product based on the shipments with a status of "returned" in the list of shipments.
    *  @param  num Reference to an integer where the function will store the number of times the most returned product was returned.
    *  @return Name of the most returned product.
    *  @note   The function should iterate through the list of shipments, count the occurrences of each product in the shipments with a status of "returned", and identify the product that was returned most frequently. If there are multiple products with the same highest return count, the function should return the one that comes first in alphabetical order.
    */
    string mostReturnedProduct(int &num);
/*  @brief  List the products that are in short supply across all warehouses.
    *  @param  WareManager Reference to the warehouse management object.
    *  @return vector with the name of the products ordered in ascending order
    * @note   A product is considered to be in short supply if the total quantity available across all warehouses is less than the total quantity required by the pending orders in the queue of pending orders. 
    * The function should iterate through the queue of pending orders, calculate the total quantity required for each product, and compare it with the total quantity available across all warehouses to determine which products are in short supply.
    */
    vector<string> productsWithNotEnoughStock(WarehouseManagement& WareManager) ;

    /*brief Update the information of a specific order and updade the priority_queue
    * @param target  pointer to the order to be updated
    * @param type type of update (ADD or REMOVE)
    * @param productId ID of the product to be updated
    * @param quantity quantity of the product to be updated
    * @param PrManager reference to the product management object
    * @param WareManager reference to the warehouse management object
    * @return 0 if the order and priority are updated successfully, -1 if the the order not exists ,  -2 if the product is invalid or if the product does not exist, - 3 if the warehouse(must be the warehouse of the target order) have stock to remove or if the order does not have the product to remove, -4 if the type is invalid.
    * @note The function should first check if the target order exists. If it does not exist, the function should return -1. Then, it should check if the productId is valid and exists in the product management. If it is invalid or does not exist, the function should return -2. Finally, depending on the type of update (ADD or REMOVE), the function should check if the warehouse has enough stock to remove or if the order has the product to remove. If any of these conditions are not met, the function should return -3. If all checks pass, the function should update the order accordingly and also update the priority queue to reflect any changes in the number of products in the order.
    */
    int updateOrder(Order* target, string type, int productId, int quantity, ProductManagement& PrManager, WarehouseManagement& WareManager);
};

bool lessProduct(Product* a, Product* b);

class ProductBST {
private:

    Node* root;/*brief pointer to the root of the BST   */

    Node* insert(Node* node, Product* p);/*brief functiont to insert a new node */

public:
        /* METHODS */
    /* --- Constructor --- */

    /** 
    *  @brief Constructor (default) - Create an object of the class ProductBST.
    *  @note  Make sure the pointer 'root' is initialized to nullptr.
     */ 
     ProductBST();
        
        /* --- Get Methods --- */       
    Node* getRoot() const ;/*brief Get the pointer to the root of the BST. */

     /* --- Other Methods --- */

     /** 
    *  @brief  Insert a new product into the BST.
    *  @param  p Pointer to the product to be inserted.
    *  @return void
    *  @note   The function should insert the new product into the BST according to the following ordering: first by category in ascending order, and if two products have the same category, then by name in ascending order. The function should use the 'lessProduct' function to compare products and determine their correct position in the BST.
    */                      
    void insert(Product* p) ;

    /** 
         * @brief  Find the top 3 most expensive products in a given category in the BST.    
         * @param  node Pointer to the root of the BST.  
         * @param  cat Category to be searched.
         * @return Vector containing pointers to the top 3 most expensive products in the specified category, or a vector with fewer elements if less than 3 products are found.
         * @note   The function should traverse the BST to find all products in the specified category and keep track of the most expensive ones  found. If multiple products in the same category have the same highest price, the function should return the one that comes first in alphabetical order.
         */
    vector<Product*> top3MostExpensive(Node* node,string cat);

    /** 
    *  @brief  Count the number of products in each category in the BST.
    *  @param  node Pointer to the root of the BST.
    *  @return Vector of pairs, where each pair contains a category name and the corresponding count of products in that category. The vector should be ordered in desascending order by category count, in case of a tie in the count, the categories should be ordered in ascending alphabetical order.
    *  @note   The function should traverse the BST and count the number of products in each category, storing the results in a vector of pairs. Each pair should consist of a category name    and the count of products in that category. After counting, the function should sort the vector of pairs according to the specified ordering criteria before returning it.
    */
    vector<pair<string,int>> countCategory(Node* node);
};

class Graph {
private:
    vector<string> nodes; // @brief Vector with the name of the cities (nodes)
    vector<vector<pair<int,int>>> adj;  // @brief Adjacency vector to represent the graph, where each element is a vector of pairs (neighborIndex, weight)
  
public:
        /* METHODS */

        /* --- Constructor --- */   


    /**
    *  @brief Constructor (default) - Create an object of the class Graph.
    *  @note  Make sure the vector 'nodes' and the adjacency list 'adj' are initialized to be empty.
    */
    Graph();            
     
    /*brief Get the index of a city in the graph given its name.
    * @param name Name of the city to find.
    * @return Index of the city in the graph if found, or -1 if the city does not exist in the graph.
    */
    int getIndex(string name); 
   
    /*  @brief  Add a new vertex to the graph.
    *  @param  name Name of the city to be added as a vertex.
    *  @return 0 if the vertex is added successfully | -1 if the parameter  is invalid | 1 if the vertex already exists in the graph
    */  
    int addVertex(string name);

     /* @brief  Add a new edge to the graph.
    *  @param  u Name of the first city.
    *  @param  v Name of the second city.
    *  @param  weight Weight of the edge.
    *  @return 0 if the edge is added successfully | -1 if one or both cities do not exist in the graph.
    */
    int addEdge(string u, string v, int weight);


        /** 
    *  @brief  Build a graph representing the relationships between shipments, warehouses, and products.
    *  @param  ShipManager Reference to the shipment management object.
    *  @param  WareManager Reference to the warehouse management object.
    *  @param  ProdManager Reference to the product management object.
    * @param  filename Name of the text file containing the information about the relationships between shipments, warehouses, and products. Each line of the file contains the required information in the following format: ShipmentId;WarehouseId;ProductId;Quantity.
    *  @return void
    *  @note   The function should create a graph where nodes represent cities and edges represent shipment routes between warehouses.
    */
    void buildGraph(ShipmentManagement &ShipManager, WarehouseManagement &WareManager, ProductManagement &ProdManager, string filename);

    /*  @brief  Find the city with the most direct connections to other cities in the graph.
    *  @return Name of the city with the most direct connections to other cities in the graph. If there are multiple cities with the same highest number of connections, the function should return the one that comes first in alphabetical order.
    */
    string mostConnectedCity(); 

    // brief Find products that can be delivered same day.
    // @param o pointer to the order to be delivered
    // @param WareManager reference to the warehouse management object containing information about the warehouses and their stock
    // @return vector of pairs, where each pair contains a pointer to a product and a pointer to the warehouse from which the product will be delivered. The vector should only include products that can be delivered from warehouses that have a direct connection to the client's city and are within 50km distance. Can exist more than one pair with the same product if it can be delivered from different warehouses.
    // @note The function should check the client's city from the order, find all warehouses that have a direct connection to that city in the graph, and then check if those warehouses have the products in the order with sufficient quantity. If a warehouse meets these conditions, the corresponding products should be added to the result vector along with the warehouse information. 
    // @note Products that cannot be delivered same day should not be included in the result vector. Can exist more than one pair with the same product if it can be delivered from different warehouses even if the quantity is not enough in one warehouse but the total quantity from different warehouses is enough to fulfill the order.
    vector<pair<Product*, Warehouse*>> deliverSameDay(Order* o, WarehouseManagement& WareManager) ;
};

#endif