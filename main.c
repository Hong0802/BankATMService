#include <stdio.h>
#include <string.h>

void lueRoskat(void);
int luenInt(void);
int scanint(const char *const message)
{
	int value;

    printf("%s ", message);
    while (scanf("%d", &value) != 1)
    {
        int chr;
        printf("\tinvalid input...\n");
        do {
            chr = getchar();
        } while ((chr != EOF) && (chr != '\n'));
        printf("%s ", message);
    }
    return value;
}
int main(void){

   char account_number[256];
   FILE * account;
   int result;
   char pincode[256];
   char verificationPin[256];
   long bank_amount, deposit, withdraw;
   int selection, sel_Quit = 0;
   int number_50cashes=0, number_20cashes=0, sum_withdraw=0;

   do {

		printf("\nenter your account number > ");
		fgets( account_number, 256, stdin );

		if( account_number[ strlen(account_number) -1] == '\n')
			account_number[ strlen(account_number) -1] = '\0';
		else
			lueRoskat();

		strcat(account_number, ".tili");

		if( ( account = fopen( account_number, "r" ))!=NULL){
			printf("Enter Pincode > ");

			fgets( pincode, 256, stdin );
			//printf("pincode %s", pincode);

			if( pincode[ strlen(pincode) -1] == '\n')
				pincode[ strlen(pincode) -1] = '\0';
			else
				lueRoskat();

			fgets( verificationPin, 256, account );
			//printf("VerificationPin: %s**** ", verificationPin);

			do {

				if( verificationPin[ strlen(verificationPin) -1] == '\n') //remove the line break
					verificationPin[ strlen(verificationPin) -1] = '\0';

				if( verificationPin[ strlen(verificationPin) -1] == '\r') {//poista telanpalautus cr
					verificationPin[ strlen(verificationPin) -1] = '\0';
               //printf("verificationPin check pin, %s", verificationPin);

            }
            if( (result = strcmp( pincode, verificationPin ))  == 0 ){

				fscanf( account, "%lu", &bank_amount);
				//printf("account-balance:::%lu", bank_amount);
				sel_Quit = 0;
				while  (sel_Quit == 0)
				{
					printf("\n\n********Welcome ATM Service**************\n");
					printf("1. Check Balance\n");
					printf("2. Withdraw Cash\n");
					printf("3. Deposit Cash\n");
					printf("4. Quit\n");
					printf("*********************************\n\n");
					selection = scanint("Enter your selection: ");
					switch(selection)
					{
						case 1:
							printf("\nYour Balance is Euro : %lu ",bank_amount);
							break;
						case 2:
							withdraw = scanint("Enter amount to withdraw:");
							sum_withdraw = sum_withdraw + withdraw;
							if (withdraw < 20) {
								printf("\nwithdraw can't be lower than 20. ");
							} else if (withdraw > bank_amount) {
								printf("\nInsufficient Funds!!!");
								sum_withdraw = sum_withdraw - withdraw;
							} else if (withdraw == 30) {
								printf("\nWithdraw may not 30e!");
							} else if ((withdraw > 1000) || (sum_withdraw > 1000))  {
								printf("\nThe maximum one-time withdraw may not exceed 1000e! ");
								sum_withdraw = sum_withdraw - withdraw;
							} else if (withdraw % 10 != 0) {
								printf("\nSingle-digit may not 1-9!");
							} else {
								number_50cashes = 0;
								number_20cashes = 0;
								if (withdraw % 50 == 0 ) {
									number_50cashes = withdraw / 50;
									printf("\n50e is: %d. ",number_50cashes);
								} else {
									if ((withdraw % 50 == 10) || (withdraw % 50 == 30)){
										if (withdraw / 50 != 0 )
											number_50cashes = withdraw / 50 - 1;
											number_20cashes = ( withdraw % 50 + 50 ) / 20;
										} else {
											number_50cashes = withdraw / 50;
											number_20cashes = ( withdraw % 50) / 20;
									}
									if ((withdraw / 50) == 0 )
										printf("\n20e is: %d. ",number_20cashes);
									else
										printf("\n50e is: %d, 20e is: %d. ",number_50cashes, number_20cashes);
								}
								bank_amount = bank_amount - withdraw;
								printf("\n\nPlease collect cash");
								printf("\nYour bank balance is %lu",bank_amount);
							}
							break;
						case 3:
							deposit = scanint("Enter amount to deposit:");
							if (deposit < 0) {
								printf("deposit can't be minus. ");
							} else {
								bank_amount = bank_amount + deposit;
								printf("Your bank balance is: %lu",bank_amount);
							}
							break;
						case 4:
							sel_Quit = 1;
							break;
						default:
							printf("\nInvalid selection");
					}
				}
				printf("\nTake your card!\nThank you for using ATM!\n\n");
				return 0;
            }else {
				sel_Quit = 1;
				printf("Error Pincode, try again ");
			}

        }while( !result );



      } else {
         printf("\nyour account is closed!\n");
      }

   }while(1);

   return 0;

}

void lueRoskat(void){

   while(fgetc(stdin) != '\n');

}



