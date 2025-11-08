#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 20


typedef struct 
{
    int productID;
    char productName[MAX_SIZE];
    float price;
    int quantity;
}Product;



void addInitialProducts(Product *products, int size);
void addProduct(Product **products, int *size);
void displayProducts(Product *products, int size);
void updateQuantity(Product *products, int size);
void searchProductByID(Product *products, int size);
void searchProductByName(Product *products,int size);
void searchProductByPrice(Product *products, int size);
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
    addInitialProducts(products,size);

    
    while(1)
    {
        int choice;
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
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: addProduct(&products,&size);break;
            
            case 2: displayProducts(products,size); break;

            case 3: updateQuantity(products,size); break;

            case 4: searchProductByID(products,size); break;

            case 5: searchProductByName(products,size); break;

            case 6: searchProductByPrice(products,size); break;

            case 7: deleteProduct(&products,&size); break;

            case 8: free(products);products=NULL;exit(0);

            default: printf("Enter a valid choice!"); break;
        }

    }
}


void addInitialProducts(Product *products, int size)
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



void displayProducts(Product *products, int size)
{
    printf("========= PRODUCT LIST =========\n");
    for(int i=0;i<size;i++)
    {
        printf("Product ID: %d | Product Name: %s | Price: %.2f | Quantity: %d \n",(products+i)->productID, (products+i)->productName, (products+i)->price, (products+i)->quantity);
    }
}



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



void searchProductByID(Product *products,int size)
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



void searchProductByName(Product *products,int size)
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


void searchProductByPrice(Product *products, int size)
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
