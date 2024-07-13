#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// struct are the userdefine datatypes in the c language
struct items{
    char item[20];
    float price;
    int qyt;
};

struct orders
{
    char customer[50];
    char date[50];
    int numofitems;
    struct items itm[50];
};

// function to generate the bills
void generatebillHeader(char name[90], char date[30]){
    printf("\n\n");
        printf("\t    ADV. Restaurant");
        printf("\n\t    --------------------");
        printf("\nDate:%s", date);
        printf("\nInvoice To: %s", name);
        printf("\n");
        printf("--------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n-------------------------------------");
        printf("\n\n");
}

void generatebillBody(char item[30], int Qyt, float price){
    printf("%s\t\t", item);
        printf("%d\t\t", Qyt);
        printf("%.2f\t\t", Qyt*price);       
        printf("\n");
}


void generatebillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total-dis;
    float cgst = 0.09*netTotal;
    float grandTotal = netTotal + (2*cgst);
    printf("-------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t\t%.2f","%s", dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------\n");
}

int main(){
    
    float total;
    int n;
    char saveBill = 'y';
    char continueFlag = 'y';
    FILE *fp;
    int opt;
    struct orders ord; //calling the orders struct
    struct orders order;
    char name[50];
    int found = 0;

    while (continueFlag == 'y')
    {
        //dashboard
        printf("\t==========ADV. RESTAURANT==========");
        printf("\n\nPlease select your prefered option:- ");
        printf("\n 1. Generate the Invoice");
        printf("\n 2. Show all the Invoices");
        printf("\n 3. Search the Invoices");
        printf("\n 4. Exit");

        printf("\n\nYour Choice:- ");
        scanf("%d", &opt);
        fgetc(stdin); //need to use it for the consumption of the /n
        // printf("\n you have chosen:-  %d", opt);
        // printf("\n\n");

        switch (opt)
        {
        case 1:
            system("cls");
            printf("\n Please enter the name of the customer:- ");
            //scanf consume \n and that need to remove that why we use fgets.
            fgets(ord.customer,50,stdin); //store the input in customer, second is maximum limit, stdin- is standard input
            //This will automatically add /n at the end so in order to delete that we do
            ord.customer[strlen(ord.customer)-1]=0;//strlen(ord.customer)- is the length, as \n add to last so it will make it equal to 0
            //previously it is saving as name\n eg.. ram\n (ram and new line)
            strcpy(ord.date, __DATE__); //strcpy() is predefine function that copy string and paste to other variable
            // __DATE__ - gives the date of the system and strcpy copy it to variable ord.date
            printf("\nPlease enter the number of the iteams:- ");
            scanf("%d", &n);
            ord.numofitems = n;

            for(int i=0; i<n;i++){
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the iteam %d :-", i+1);
                fgets(ord.itm[i].item, 20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                printf("\nPlease enter the quantity :");
                scanf("%d", &ord.itm[i].qyt); //we are using scanf as there is no list, it is a integer datatype so do not store space
                printf("\nPlease enter the unit price: ");
                scanf("%f", &ord.itm[i].price);
                total += ord.itm[i].qyt*ord.itm[i].price;
            }

            generatebillHeader(ord.customer, ord.date);
            for(int i=0; i<ord.numofitems;i++){
                generatebillBody(ord.itm[i].item, ord.itm[i].qyt, ord.itm[i].price);
            }
            generatebillFooter(total);

            printf("\nDo you want to save the invoice:\t");
            scanf("%s", &saveBill);

            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.dat", "a+");
                // fwrite(pointer, size of struct, how many instance need to save, file pointer);
                fwrite(&ord,sizeof(struct orders), 1, fp);
                if (fwrite != 0 ){
                    printf("\nSuccessfully invoice updated....");
                }
                else{
                    printf("\nThere is some problem occured..");
                }
                fclose(fp);
            }
            break;
        
        case 2:
            system("cls");
            fp = fopen("RestaurantBill.dat", "r");
            printf("\n *******Your Previous Invoices *******\n");
            while (fread(&order, sizeof(struct orders), 1, fp)){
                float tot = 0;
                generatebillHeader(order.customer, order.date);
                for (int i = 0; i < order.numofitems; i++)
                {
                    generatebillBody(order.itm[i].item, order.itm[i].qyt, order.itm[i].price);
                    tot += order.itm[i].qyt*order.itm[i].price;
                }
                generatebillFooter(tot);

                printf("\n\n");
                printf("\n#-----#-----#------#-----#------#------#------#\n\n");
                
            }
            

            break;
        
        case 3:
            system("cls");
            printf("Enter the name of the customer:\t");
            // fgetc(stdin); // once defined - need to be define again in the loop
            fgets(name,50, stdin);
            // printf("\n%d\n" , strlen(name));
            name[strlen(name)-1]=0;
            fp = fopen("RestaurantBill.dat", "r");
            while (fread(&order, sizeof(struct orders), 2, fp)){
                if (!strcmp(order.customer, name)) //strcmp(order.customer, name) return 0 if name match so we use !
                {
                    printf("\n *******Invoices We Found*******\n");
                    float tot = 0;
                    generatebillHeader(order.customer, order.date);
                    for (int i = 0; i < order.numofitems; i++)
                    {
                        generatebillBody(order.itm[i].item, order.itm[i].qyt, order.itm[i].price);
                        tot += order.itm[i].qyt*order.itm[i].price;
                    }
                    generatebillFooter(tot);
                    found++;
                    printf("\n\n");
                    printf("\n#-----#-----#------#-----#------#------#------#\n\n");
                }
            }
            if (found==0){
                printf("\n *******No Invoices Found*******\n");
            }


            break;
        
        case 4:
            system("cls");
            printf("\n\t\tBye Bye....:");
            exit(0);
            break;

        default:
            printf("\nSorry Invalid Option....:");
            break;
        }

        printf("Would you like to go for next one : ");
        scanf("%s", &continueFlag);
        
    }

    return 0;
}