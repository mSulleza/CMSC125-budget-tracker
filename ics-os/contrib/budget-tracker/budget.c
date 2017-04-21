
#include "../../sdk/dexsdk.h"
int main_menu()
{

  printf("BUDGET TRACKER\n");
  printf("An ICS-OS budget management application\n");
  printf("[1] Add Income\n[2] Add Expense\n[3] View Summary\n[4] Help\n[5] Exit\n");
  printf("Choice: ");
  return getch();

}
int main()
{
  int choice = main_menu();
  while(choice != 53)
  {
    switch(choice = main_menu())
    {
      case 49:
        printf("\n");
        printf("ADD INCOME\n");
        break;
      case 50:
        printf("\n");
        printf("ADD EXPENSE\n");
        break;
      case 51:
        printf("\n");
        printf("VIEW SUMMARY\n");
        break;
      case 52:
        printf("\n");
        printf("HELP\n");
        break;
      default:
        printf("\n");
        printf("INVALID INPUT!\n");
        break;

    }
  }
  printf("%d\n", main_menu());
  return 0;
}
