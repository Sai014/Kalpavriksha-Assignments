#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 20

//Structure of Product
typedef struct 
{
    int productID;
    char productName[MAX_SIZE];
    float price;
    int quantity;
}Product;


//List of all functions used.
void inputValues(Product *products, int size);
void addProduct(Product **products, int *size);
void displayProducts(Product *products, int size);
void updateQuantity(Product *products, int size);
void searchProductID(Product *products, int size);
void searchProductName(Product *products,int size);
void searchProductPrice(Product *products, int size);
void deleteProduct(Product **products, int *size);


int main()
{
    int size;
    printf("Enter initial number of products: ");
    scanf("%d",&size);

    Product *products=(Product *)malloc(size*sizeof(Product));
    if (!products)
    {
        printf("Memory not allocated!\n");
        return 1;
    }
    inputValues(products,size);

    //MENU
    while(1)
    {
        int ch;
        printf("\n========= INVENTORY MENU =========\n");
        printf("1. Add New Product\n");
        printf("2. View All Products\n");
        printf("3. Update Quantity\n");
        printf("4. Search Product by ID\n");
        printf("5. Search Product by Name\n");
        printf("6. Search Product by Price Range\n");
        printf("7. Delete Product\n");
        printf("8. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: addProduct(&products,&size);break;
            
            case 2: displayProducts(products,size); break;

            case 3: updateQuantity(products,size); break;

            case 4: searchProductID(products,size); break;

            case 5: searchProductName(products,size); break;

            case 6: searchProductPrice(products,size); break;

            case 7: deleteProduct(&products,&size); break;

            case 8: exit(0);

            default: printf("Enter a valid choice!"); break;
        }

    }
}

//Inputs the inital Products from the user.
void inputValues(Product *products, int size)
{
    for(int i=0;i<size;i++)
    {
        printf("\nEnter details of product %d:\n",i+1);
        printf("Product ID: ");
        scanf("%d",&((products+i)->productID));
        printf("Product Name: ");
        scanf("%s",&((products+i)->productName));
        printf("Product Price: ");
        scanf("%f",&((products+i)->price));
        printf("Product Quantity: ");
        scanf("%d",&((products+i)->quantity));
    }
}


//Displays the products on console.
void displayProducts(Product *products, int size)
{
    printf("========= PRODUCT LIST =========\n");
    for(int i=0;i<size;i++)
    {
        printf("Product ID: %d | Product Name: %s | Price: %.2f | Quantity: %d \n",(products+i)->productID, (products+i)->productName, (products+i)->price, (products+i)->quantity);
    }
}


//Adds product by reallocating memory.
void addProduct(Product **products, int *size)
{
    *products=realloc(*products,(*size+1)*sizeof(Product));
    if(!products)
    {
        printf("Memory not allocated.\n");
        return;
    }

    printf("Enter details of product %d: \n",*(size)+1);
    printf("Product ID: ");
    scanf("%d",&((*products+*size)->productID));
    printf("Product Name: ");
    scanf("%s",&((*products+*size)->productName));
    printf("Product Price: ");
    scanf("%f",&((*products+*size)->price));
    printf("Product Quantity: ");
    scanf("%d",&((*products+*size)->quantity));
    (*size)++;
    printf("Product successfully added!\n");
}

//Updates quantity of a product
void updateQuantity(Product *products, int size)
{
    int productID;
    printf("Enter Product ID to update quantity: ");
    scanf("%d",&productID);
    for(int i=0;i<size;i++)
    {
        if((products+i)->productID==productID)
        {
            printf("Enter new Quantity: ");
            scanf("%d",&((products+i)->quantity));
            printf("Quantity updated successfully!\n");
            return;
        }
    }
    printf("Invalid Product ID!\n");
    return;
}


//Searches the product by taking ID as an input.
void searchProductID(Product *products,int size)
{
     int productID;
    printf("Enter Product ID to search: ");
    scanf("%d",&productID);
    int found=0;
    printf("Product Found: \n");
    for(int i=0;i<size;i++)
    {
        if((products+i)->productID==productID)
        { 
        printf("Product ID: %d | Product Name: %s | Price: %.2f | Quantity: %d \n",(products+i)->productID, (products+i)->productName, (products+i)->price, (products+i)->quantity);
        found=1;
    }
    }
    if(found==0)printf("Invalid Product ID!\n");
    return;
}


//Searches the product by taking name as an input.
void searchProductName(Product *products,int size)
{
    char *name=malloc(MAX_SIZE*sizeof(char));
    printf("Enter name to search (partial allowed): ");
    scanf("%s",name);

    for(int i=0;i<size;i++)
    {
        for(int j=0;name[j]!='\0';j++)
        {
            if(((products+i)->productName)[j]==*(name+j))
            {
                if(*(name+j+1)=='\0')
                {
                    printf("Product Found: \nProduct ID: %d | Product Name: %s | Price: %.2f | Quantity: %d \n",(products+i)->productID, (products+i)->productName, (products+i)->price, (products+i)->quantity);
                }
                else continue;
            }
            else break;
        }
    }
}

//Searches the product by taking price range as an input.
void searchProductPrice(Product *products, int size)
{
    int minPrice;
    int maxPrice;
    printf("Enter minimum price: ");
    scanf("%d",&minPrice);
    printf("Enter maximum price: ");
    scanf("%d",&maxPrice);

    int found=0;
    printf("Products in range: \n");

    for(int i=0;i<size;i++)
    {
        if((products+i)->price>=minPrice && (products+i)->price<=maxPrice)
        {
            found=1;
            printf("Product ID: %d | Product Name: %s | Price: %.2f | Quantity: %d \n",(products+i)->productID, (products+i)->productName, (products+i)->price, (products+i)->quantity);
        }
    }
    if(found==0)printf("No Products Found in price range!\n");
    return;
}

//Function to delete the product based on product ID. 
void deleteProduct(Product **products, int *size)
{
    int ID;
    printf("Enter Product ID to delete: ");
    scanf("%d",&ID);
    int found=0;
    for(int i=0;i<*(size);i++)
    {
        if(((*products)+i)->productID==ID)
        {
            for(int j=i;j<*(size);j++)
            {
                *(*products+j)=*(*products+j+1);
            }
            found=1;
            break;
        }
    }
    if(found==1)
    {
        *products=realloc(*products,(*(size)-1)*sizeof(Product));
        printf("Product deleted successfully!\n");
        (*size)--;
        return;
    }
    printf("Incorrect Product ID.\n");

}