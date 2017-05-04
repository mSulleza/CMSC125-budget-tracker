
#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

typedef struct NODES
{
  int value;
  int is_income; // boolean for determining if it is an income or an expense
  char category[50]; // stores the category
  // stores the time (number of seconds since Jan 1 1970)
  int time;
  int recurring; // boolean to determine if it is recuring or not
  // RECURRING VALUES
  // (1) - daily
  // (2) - weekly
  // (3) - monthly
  struct NODES * next;
  struct NODES * prev;
} NODE;

typedef struct CATEGORIES
{
  char category[50];
  int count;
  struct CATEGORIES * next;
  struct CATEGORIES * prev;
} CATEGORY;

NODE * main_pointer;
CATEGORY * category_main;

int balance = 0;
// function for getting the user's input
char * get_input()
{
  char * str;
  fflush(stdin);
  fgets(str, 50, stdin);
  strtok(str, "\n");
  return str;
}
// function for printing the main menu
void main_menu()
{

  printf("BUDGET TRACKER\n");
  printf("An ICS-OS budget management application\n");
  printf("[1] Add Income\n[2] Add Expense\n[3] View Summary\n[4] Help\n[5] Exit\n");
  printf("Choice: ");
  // return get_input();
}

int to_lower(int a)
{
  if (a >= 65 && a <= 90)
  {
    return (a + 32);
  }
}
void update_category_count(char category_name[])
{
  char lower_name[50];
  int i = 0;
  // converts the name to its lower case form
  while ( category_name[i] != '\0')
  {
    lower_name[i] = to_lower(category_name[i]);
    i += 1;
  }

  printf("LOWERCASE FORM IS: %s\n", lower_name);
  // CATEGORY * temp = category_main;
  // while (temp != NULL)
  // {
  // }
}

void add_expense()
{
  NODE * temp = (NODE *)malloc(sizeof(NODE));
  char str[50];
  fflush(stdin);

  // set is_income to false
  temp->is_income = 0;
  temp->next = NULL;
  temp->prev = NULL;
  printf("Category of expense: ");
  fgets(str, 50, stdin);
  strtok(str, "\n");
  strcpy(temp->category, str);
  printf("Value: ");
  fgets(str, 50, stdin);
  strtok(str, "\n");
  temp->value = atoi(str);

  // gets the current time
  temp->time = time();
  // update the value of the balance
  strcpy(str, "NULL");
  while(strcmp(str, "1") != 0 || strcmp(str, "2") != 0)
  {
    printf("IS THE EXPENSE RECURRING?\n[1]YES\n[2]NO\nChoice: ");
    fgets(str, 50, stdin);
    strtok(str, "\n");
    if (strcmp(str, "1") == 0)
    {
      strcpy(str, "NULL");
      while(strcmp(str, "1") != 0 || strcmp(str, "2") != 0 || strcmp(str, "3") != 0)
      {
        printf("How often?\n[1]Daily\n[2]Weekly\n[3]Monthly\nChoice: ");
        fgets(str, 50, stdin);
        strtok(str, "\n");
        if (strcmp(str, "1") == 0)
        {
          if (strcmp(str, "1") == 0)
          {
            printf("DAILY EXPENSE ADDED!\n");
            temp->recurring = 1;
            break;
          }
          else if (strcmp(str, "2") == 0)
          {
            printf("WEEKLY EXPENSE ADDED!\n");
            temp->recurring = 2;
            break;
          }
          else if (strcmp(str, "3") == 0)
          {
            printf("MONTHLY EXPENSE ADDED!\n");
            temp->recurring = 3;
            break;
          }
          else printf("INVALID INPUT!\n");
        }
        else if (strcmp(str, "2") == 0)
        {
          temp->recurring = 0;
          break;
        }
        else printf("INVALID INPUT!\n");
      }
    }
  }

  balance -= temp->value;
  printf("EXPENSE ADDED!\n");
  printf("CURRENT BALANCE: Php %d\n", balance);

  NODE * t = main_pointer;
  if (t == NULL)
  {
    main_pointer = temp;
    return;
  }
  while (t->next != NULL)
  {
    t = t->next;
  }
  t->next = temp;
  temp->prev = t;

}

void add_income()
{
  NODE * temp = (NODE *)malloc(sizeof(NODE));
  char str[50];
  fflush(stdin);

  // set is_income to false
  temp->is_income = 1;
  temp->next = NULL;
  temp->prev = NULL;
  printf("Category of income: ");
  fgets(str, 50, stdin);
  strtok(str, "\n");
  strcpy(temp->category, str);
  printf("Value: ");
  fgets(str, 50, stdin);
  strtok(str, "\n");
  temp->value = atoi(str);

  // gets the current time
  temp->time = time();
  // update the value of the balance
  strcpy(str, "NULL");
  while(strcmp(str, "1") != 0 || strcmp(str, "2") != 0)
  {
    printf("IS THE INCOME RECURRING?\n[1]YES\n[2]NO\nChoice: ");
    fgets(str, 50, stdin);
    strtok(str, "\n");
    if (strcmp(str, "1") == 0)
    {
      strcpy(str, "NULL");
      while(strcmp(str, "1") != 0 || strcmp(str, "2") != 0 || strcmp(str, "3") != 0)
      {
        printf("How often?\n[1]Daily\n[2]Weekly\n[3]Monthly\nChoice: ");
        fgets(str, 50, stdin);
        strtok(str, "\n");
        if (strcmp(str, "1") == 0)
        {
          if (strcmp(str, "1") == 0)
          {
            printf("DAILY INCOME ADDED!\n");
            temp->recurring = 1;
            break;
          }
          else if (strcmp(str, "2") == 0)
          {
            printf("WEEKLY INCOME ADDED!\n");
            temp->recurring = 2;
            break;
          }
          else if (strcmp(str, "3") == 0)
          {
            printf("MONTHLY INCOME ADDED!\n");
            temp->recurring = 3;
            break;
          }
          else printf("INVALID INPUT!\n");
        }
        else if (strcmp(str, "2") == 0)
        {
          temp->recurring = 0;
          break;
        }
        else printf("INVALID INPUT!\n");
      }
    }
  }

  balance += temp->value;
  printf("INCOME ADDED!\n");
  printf("CURRENT BALANCE: Php %d\n", balance);

  NODE * t = main_pointer;
  if (t == NULL)
  {
    main_pointer = temp;
    return;
  }
  while (t->next != NULL)
  {
    t = t->next;
  }
  t->next = temp;
  temp->prev = t;

}

void view_summary()
{

}

void update_recurring()
{
  NODE * t = main_pointer;
  // gets the time to day. (sec since Jan 1970)
  int time_today = time();
  while (t != NULL)
  {
    if (t->recurring == 1)
    {
      // update daily recurring transaction
      // seconds in one day
      int one_day = 60 * 60 * 24;
      if ((t->time + one_day) > time_today && (t->time + one_day) < (time_today + one_day))
      {
        NODE * new_transaction = (NODE *) malloc(sizeof(NODE));
        new_transaction->value = t->value;
        new_transaction->is_income = t->is_income;
        strcpy(new_transaction->category, t->category);
        new_transaction->time = time_today;
        new_transaction->recurring = t->recurring;

        // add to the linklist
        NODE * t2 = main_pointer;
        while (t2->next != NULL)
        {
          t2 = t2->next;
        }
        t2->next = new_transaction;
        t->prev = t2;
      }
    }
    else if (t->recurring == 2)
    {
      // update weekly recurring transaction
      // seconds in one week
      int one_week = 60 * 60 * 24 * 7;
      if ((t->time + one_week) > time_today && (t->time + one_week) < (time_today + one_week))
      {
        NODE * new_transaction = (NODE *) malloc(sizeof(NODE));
        new_transaction->value = t->value;
        new_transaction->is_income = t->is_income;
        strcpy(new_transaction->category, t->category);
        new_transaction->time = time_today;
        new_transaction->recurring = t->recurring;

        // add to the linklist
        NODE * t2 = main_pointer;
        while (t2->next != NULL)
        {
          t2 = t2->next;
        }
        t2->next = new_transaction;
        t->prev = t2;
      }
    }
    else if (t->recurring == 2)
    {
      // update monthly recurring transaction
      // seconds in one week
      int one_month = 60 * 60 * 24 * 30;
      if ((t->time + one_month) > time_today && (t->time + one_month) < (time_today + one_month))
      {
        NODE * new_transaction = (NODE *) malloc(sizeof(NODE));
        new_transaction->value = t->value;
        new_transaction->is_income = t->is_income;
        strcpy(new_transaction->category, t->category);
        new_transaction->time = time_today;
        new_transaction->recurring = t->recurring;

        // add to the linklist
        NODE * t2 = main_pointer;
        while (t2->next != NULL)
        {
          t2 = t2->next;
        }
        t2->next = new_transaction;
        t->prev = t2;
      }
    }

    t = t->next;
  }
}
int main()
{
  update_recurring();
  while(1)
  {
    delay(100);
    clrscr();
    main_menu();
    char str[50];
    fflush(stdin);
    fgets(str, 50, stdin);
    strtok(str, "\n");

    if(strcmp(str, "5") == 0)
    {
      break;
    }
    if(strcmp(str, "1") == 0)
    {
      clrscr();
      printf("ADD INCOME\n");
    }
    else if(strcmp(str, "2") == 0)
    {
      clrscr();
      add_expense();
    }
    else if(strcmp(str, "3") == 0)
    {
      clrscr();
      printf("VIEW SUMMARY\n");
    }
    else if(strcmp(str, "4") == 0)
    {
      clrscr();
      printf("HELP\n");
    }
    else
    {
      clrscr();
      printf("INVALID INPUT!\n");
    }
  }
  return 0;
}
