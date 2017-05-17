
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
  int isIncome;
  struct CATEGORIES * next;
  struct CATEGORIES * prev;
} CATEGORY;

NODE * main_pointer;
CATEGORY * category_main;

int balance = 0;
// function for getting the user's input
void get_input(char input[50])
{
  write_text("Input: ", 10, 180, WHITE, 0);
  int limit = 0;
  char key;
  while (1)
  {

    key = (char) getch();

    if (key == '\n')
    {
      input[limit] = '\0';
      return;
    }
    // for deletion
    if (key == '\b' && limit >= 0)
    {
      limit -= 1;
      fill_rect(70 + limit * 10, 180 , 10, 10,BLACK);
      continue;
    }
    input[limit] = key;
    write_char(key, 70 + limit*10, 180, WHITE, 0);
    limit += 1;
  }
}
// function for printing the main menu
void main_menu()
{  
  set_graphics(VGA_320X200X256);
  write_text("BUDGET TRACKER", 100, 10, WHITE, 0);
  write_text("An ICS-OS budget management app", 15, 25, WHITE, 0);
  write_text("[1] Add Income", 80, 60, WHITE, 0);
  write_text("[2] Add Expense", 80, 72, WHITE, 0);
  write_text("[3] View Summary", 80, 84, WHITE, 0);
  write_text("[4] Help", 80, 96, WHITE, 0);
  write_text("[5] Exit", 80, 108, WHITE, 0);
    
    char str[50];
    sprintf(str, "BALANCE: Php %d", balance);
    write_text(str, 80, 145, WHITE, 0);
}

int to_lower(int a)
{
  if (a >= 65 && a <= 90)
  {
    return (a + 32);
  }
}
void update_category_count(char category_name[], int isIncome)
{
  char lower_name[50];
  int i = 0;
  // converts the name to its lower case form
  while ( category_name[i] != '\0')
  {
    lower_name[i] = to_lower(category_name[i]);
    i += 1;
  }
  // adds a terminating character
  lower_name[i] = '\0';

  // printf("LOWERCASE FORM IS: %s\n", lower_name);
  CATEGORY * temp = category_main;
  CATEGORY * new_category = (CATEGORY * ) malloc(sizeof(CATEGORY));
  strcpy(new_category->category, lower_name);
  new_category->count = 1;
  new_category->next = NULL;
  new_category->prev = NULL;
  new_category->isIncome = isIncome;
  if (temp == NULL)
  {
    category_main = new_category;
    return;
  }

  while (temp->next != NULL)
  {
    if(strcmp(temp->category, lower_name) == 0)
    {
      temp->count += 1;
      return;
    }
    temp = temp->next;
  }

  temp->next = new_category;
  new_category->prev = temp;

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
  set_graphics(VGA_320X200X256);
  write_text("Category of expense?", 15, 25, WHITE, 0);
  get_input(str);
  update_category_count(str, 0);
  strcpy(temp->category, str);
  set_graphics(VGA_320X200X256);
  write_text("Value?", 15, 25, WHITE, 0);
  get_input(str);
  temp->value = atoi(str);

  // gets the current time
  temp->time = time();
  // update the value of the balance
  strcpy(str, "NULL");
  while(1)
  {
    clrscr();
    printf("IS THE EXPENSE RECURRING?\n[1]YES\n[2]NO\nChoice: ");
    fgets(str, 50, stdin);
    strtok(str, "\n");
    set_graphics(VGA_320X200X256);
    write_text("Recurring?", 15, 25, WHITE, 0);
    write_text("[1] Yes", 20, 45, WHITE, 0);
    write_text("[2] No", 20, 55, WHITE, 0);
    get_input(str);
    if (strcmp(str, "2") == 0)
    {
      temp->recurring = 0;
      break;
    }
    if (strcmp(str, "1") == 0)
    {
      strcpy(str, "NULL");
      while(1)
      {
        set_graphics(VGA_320X200X256);
        write_text("How often?", 15, 25, WHITE, 0);
        write_text("[1] Daily", 15, 35, WHITE, 0);
        write_text("[2] Weekly", 15, 45, WHITE, 0);
        write_text("[3] Monthly", 15, 55, WHITE, 0);
        get_input(str);
        if (strcmp(str, "1") == 0)
        {
          set_graphics(VGA_320X200X256);
          write_text("DAILY EXPENSE ADDED!", 60, 80, WHITE, 0);
          temp->recurring = 1;
          break;
        }
        else if (strcmp(str, "2") == 0)
        {
          set_graphics(VGA_320X200X256);
          write_text("WEEKLY EXPENSE ADDED!", 60, 80, WHITE, 0);
          temp->recurring = 1;
          break;
        }
        else if (strcmp(str, "3") == 0)
        {
          set_graphics(VGA_320X200X256);
          write_text("MONTHLY EXPENSE ADDED!", 60, 80, WHITE, 0);
          temp->recurring = 1;
          break;
        }
        else
        {
          set_graphics(VGA_320X200X256);
          write_text("INVALID INPUT!", 60, 80, RED, 0);
        }
      }
      break;
    }
    else write_text("INVALID INPUT!", 60, 80, RED, 0);
  }

  balance -= temp->value;
  char balance_text[50];
  sprintf(balance_text, "Current Balance: Php %d", balance);
  delay(50);
  set_graphics(VGA_320X200X256);
  if (balance > 0)
  {
    write_text(balance_text, 50, 80, GREEN, 0);
  }
  else write_text(balance_text, 50, 80, RED, 0);

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
  // write_text("ADD INCOME", 80, 10, WHITE, 0);
  NODE * temp = (NODE *)malloc(sizeof(NODE));
  char str[50];
  fflush(stdin);

  // set is_income to false
  temp->is_income = 1;
  temp->next = NULL;
  temp->prev = NULL;
  set_graphics(VGA_320X200X256);
  write_text("Category of income?", 15, 25, WHITE, 0);
  get_input(str);
  update_category_count(str, 1);
  strcpy(temp->category, str);
  set_graphics(VGA_320X200X256);
  write_text("Value?", 15, 25, WHITE, 0);
  get_input(str);
  temp->value = atoi(str);

  // gets the current time
  temp->time = time();
  // update the value of the balance
  strcpy(str, "NULL");
  while(1)
  {
    set_graphics(VGA_320X200X256);
    write_text("Recurring?", 15, 25, WHITE, 0);
    write_text("[1] Yes", 20, 45, WHITE, 0);
    write_text("[2] No", 20, 55, WHITE, 0);
    get_input(str);
    if (strcmp(str, "2") == 0)
    {
      temp->recurring = 0;
      break;
    }
    if (strcmp(str, "1") == 0)
    {
      strcpy(str, "NULL");
      while(1)
      {
        set_graphics(VGA_320X200X256);
        write_text("How often?", 15, 25, WHITE, 0);
        write_text("[1] Daily", 15, 35, WHITE, 0);
        write_text("[2] Weekly", 15, 45, WHITE, 0);
        write_text("[3] Monthly", 15, 55, WHITE, 0);
        get_input(str);
        if (strcmp(str, "1") == 0)
        {
          set_graphics(VGA_320X200X256);
          write_text("DAILY INCOME ADDED!", 60, 80, WHITE, 0);
          temp->recurring = 1;
          break;
        }
        else if (strcmp(str, "2") == 0)
        {
          set_graphics(VGA_320X200X256);
          write_text("WEEKLY INCOME ADDED!", 60, 80, WHITE, 0);
          temp->recurring = 1;
          break;
        }
        else if (strcmp(str, "3") == 0)
        {
          set_graphics(VGA_320X200X256);
          write_text("MONTHLY INCOME ADDED!", 60, 80, WHITE, 0);
          temp->recurring = 1;
          break;
        }
        else
        {
          set_graphics(VGA_320X200X256);
          write_text("INVALID INPUT!", 60, 80, RED, 0);
        }
      }
      break;
    }
  }

  balance += temp->value;
  char balance_text[50];
  sprintf(balance_text, "Current Balance: Php %d", balance);
  delay(50);
  set_graphics(VGA_320X200X256);
  if (balance > 0)
  {
    write_text(balance_text, 50, 80, GREEN, 0);
  }
  else write_text(balance_text, 50, 80, RED, 0);


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
  int total_income_categories = 0;
  int total_expense_categories = 0;
  CATEGORY * category_ptr = category_main;
  NODE * temp = category_main;

  while(category_ptr != NULL)
  {
    if (category_ptr->isIncome == 1) total_income_categories += 1;
    else total_expense_categories += 1;
    category_ptr = category_ptr->next;
  }

  textcolor(GREEN);
  //printf("INCOME SUMMARY\n");
  write_text("----------------------", 65, 20, WHITE, 0);
  category_ptr = category_main;
  char bal[20];
  int enter = 40;
  char key;

  while(category_ptr != NULL)
  {
    //prints income categories
    if (category_ptr->isIncome == 1)
    {
      int percentage = (category_ptr->count/total_income_categories) * 100;
      write_text(category_ptr->category, 10, enter, GREEN, 0);
      sprintf(bal, "%d", percentage);
      write_text(bal, 230, enter, GREEN, 0);
      category_ptr = category_ptr->next;
      enter+=15;
    }

    //prints expense categories
    else if(category_ptr->isIncome == 0) {
      int percentage = (category_ptr->count/total_expense_categories) * 100;
      write_text(category_ptr->category, 30, enter, WHITE, 0);
      sprintf(bal, "%d", percentage);
      write_text(bal, 230, enter, WHITE, 0);
      category_ptr = category_ptr->next;
      enter+=15;
    }
  }  

  //back button
  key = (char) getch();

    if(key == '\b') {
      main();
    }
  //write_text("-----------", 80, 80, WHITE, 0);
  //textcolor(WHITE);
  // NODE * transaction_ptr = main_pointer;
  // while (transaction_ptr != NULL)
  // {
  //
  // }
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

void fill_rect(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,color);
}

void write_file()
{
  FILE * fp;
  fp = fopen("transaction_nodes.txt", "w+");

  NODE * temp = main_pointer;

  while(temp != NULL)
  {
    fwrite(temp->value, 1, sizeof(temp->value), fp);
    // fwrite(temp->is_income, 1, sizeof(temp->is_income), fp);
    // fwrite(temp->category, 1, sizeof(temp->category), fp);
    // fwrite(temp->time, 1, sizeof(temp->time), fp);
    // fwrite(temp->recurring, 1, sizeof(temp->recurring), fp);
    temp = temp->next;
  }
  fclose(fp);
}
int main()
{
  update_recurring();
  set_graphics(VGA_320X200X256);

  while(1)
  {
    delay(100);
    clrscr();
    char input[50];
    main_menu();
    get_input(input);
   // strcmp(str, get_input());
     // fflush(stdin);
     // fgets(str, 50, stdin);
     // strtok(str, "\n");

    if(strcmp(input, "5") == 0)
    {
      set_graphics(VGA_320X200X256);
      set_graphics(VGA_TEXT80X25X16);
      write_file();
      exit(0);
    }
    if(strcmp(input, "1") == 0)
    {
      set_graphics(VGA_320X200X256);
      add_income();
    }
    else if(strcmp(input, "2") == 0)
    {
      set_graphics(VGA_320X200X256);
      write_text("ADD EXPENSE", 80, 10, WHITE, 0);
      add_expense();
    }
    else if(strcmp(input, "3") == 0)
    {
      set_graphics(VGA_320X200X256);
      write_text("VIEW SUMMARY", 110, 10, WHITE, 0);
      view_summary();
    }
    else if(strcmp(input, "4") == 0)
    {
      set_graphics(VGA_320X200X256);
      write_text("HELP", 140, 20, WHITE, 0);
      write_text("This app helps you", 70, 60, WHITE, 0);
      write_text("manage your budget.", 70, 70, WHITE, 0);
      write_text("2017 UPLB", 120, 180, WHITE, 0);
    }
    else
    {
      set_graphics(VGA_320X200X256);
      write_text("INVALID INPUT!", 80, 60, RED, 0);
    }
   }
  return 0;
}
