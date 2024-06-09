// isko barae mehrbani beghair chere kam karyega
#include "MenuManagement.cpp"
class OrderProcessing:public MenuManagement{
    public:
    vector<pair<string, int>> OrderedItems;  
    OrderProcessing(){}
    
    void printOrder() {
        cout << "Current Order:" << endl;
        for(const auto &item : OrderedItems) {
            cout << "Item: " << item.first << ", Quantity: " << item.second << endl;
        }
    }
    
    vector<pair<string, int>> placeOrder(){
        try{ 
            displayMenu();
            cout<<"How many orders do you want to place?"<<endl;
            int n;
            cin>>n;
            string order;
            int quantity;
            for(int i=0;i<n;i++){
                while(true){
                    cout<<"Order Please:)"<<endl;
                    cin>>order;

                    cout<<"Quantity:"<<endl;
                    cin>>quantity;

                    if(validateMenu(order) && validQuantity(quantity)){
                        OrderedItems.push_back(make_pair(order, quantity));
                        cout << "Item added successfully." << endl;
                        break;
                    }
                    else{
                        cout<<"Invalid item name or quantity-Please choose from menu."<<endl<< "Quantity range is 1 to 10"<<endl;
                    }
                }
            }
            printOrder();
        }
        catch (const exception &e)
        {
            cerr << "Exception caught: " << e.what() << endl;
        }
        catch (...)
        {
            cerr << "Unknown exception caught" << endl;
        }
        return OrderedItems;
    }

   vector<pair<string, int>> modifyOrder(){
    try{
        string itemName;
        int option;
        cout << "Enter your choice: "<<endl<<"1) Add"<<endl <<"2) Update"<<endl <<"3) Remove" << endl;
        cin >> option;

        switch(option) {
            case 1: 
            {
                string newItemName;
                int newQuantity;
                cout << "Enter the name for the new item:" << endl;
                cin >> newItemName;
                cout << "Enter the quantity for the new item:" << endl;
                cin >> newQuantity;
                OrderedItems.push_back(make_pair(newItemName, newQuantity));
                cout << "Item added successfully." << endl;
                break;
            }
            case 2: 
            {
                string itemName, newName;
                int newQuantity;
                cout << "Enter the name of the item you wish to update:" << endl;
                cin >> itemName;
                cout << "Enter the new name for the item:" << endl;
                cin >> newName;
                cout << "Enter the new quantity for the item:" << endl;
                cin >> newQuantity;

                for(auto &order : OrderedItems){
                    if(order.first == itemName){
                        order.first = newName;
                        order.second = newQuantity;
                        cout << "Order updated successfully." << endl;
                    }
                }
                break;
            }
            case 3: 
            {
                string itemName;
                cout << "Enter the name of the item you wish to remove:" << endl;
                cin >> itemName;

                for(auto it = OrderedItems.begin(); it != OrderedItems.end();){
                    if(it->first == itemName){
                        it = OrderedItems.erase(it);
                        cout << "Order removed successfully." << endl;
                    } else {
                        ++it;
                    }
                }
                break;
            }
            default:
                cout << "Invalid option!" << endl;
                break;
        }
    }
    catch (const exception &e)
    {
        cerr << "Exception caught: " << e.what() << endl;
    }
    catch (...)
    {
        cerr << "Unknown exception caught" << endl;
    }
    return OrderedItems;
}
void cancelOrder() {
    OrderedItems.clear();
    cout << "Order has been cancelled successfully." << endl;
}
friend class BillingPayment;

    

};



