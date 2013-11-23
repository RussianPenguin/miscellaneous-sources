#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

int function_start_menu(void);
int function_player_kick(void);
int function_player_block(void);                                /* Прототипы */
int function_bot_block(void);
int function_stats(void);

/******************************************************************************/

int main(void)
{
  int n_player_kick, n_player_block, n_bot_kick, n_bot_block, \
    n_player_life, n_bot_life, n_player_wins = 0, n_player_looses = 0, n_stat;

  function_start_menu();

  n_player_life = n_bot_life = 36;

BEGIN_OF_THE_FIGHT:                                             /* Метка */

  while(1)
  {
    n_player_kick = function_player_kick();
    n_player_block = function_player_block();
    n_bot_block = function_bot_block();

    switch(n_player_kick)
    {
      case(1):
      case(2):
      case(3):
      case(4):
      case(5):
      {
        if((n_bot_life <= 0) || (n_player_life <= 0))         /* Если у кого-нибудь кончились хиты, выходим из боя */
        {
          goto END_OF_FIGHT;
        }
        if(n_player_kick != n_bot_block)                      /* Если бот не заблокировал наш удар, бьём его */
        {
          do
          {
            n_player_kick = rand();
          }while(n_player_kick >= 5);
          n_bot_life = n_bot_life - n_player_kick;
          _sleep(2000);
          printf("\nThis is realy good kick (-%d): [%d/36]\n", n_player_kick, n_bot_life);
        }
        else                                                  /* Если заблокировал - плохо! */
        {
          _sleep(2000);
          printf("\nThe Bot Is Blocked Your Kick\n\n");
        }
        break;
      }
      default:
      {
        exit(1);                                              /* Аварийный выход */
      }
    } /* End of switch */

    switch(n_player_block)
    {
      case(1):
      case(2):
      case(3):
      case(4):
      case(5):
      {
        if(n_player_block != n_bot_kick)                      /* Если мы не заблокировали удар бота ... */
        {
          do
          {
            n_bot_kick = rand();
          }while(n_bot_kick >= 5);
          n_player_life = n_player_life - n_bot_kick;
          _sleep(2000);
          printf("\nThe Bot Kicked On (-%d): [%d/36]\n\n", n_bot_kick, n_player_life);
        }
        else                                                   /* Если заблокировали - он труп */
        {
          _sleep(2000);
          printf("\nYou Blocked The Kick Of The Bot\n\n");
        }
        break;
      }
      default:
      {
        exit(1);
      }
    } /* End of switch */
  } /* End of while */

END_OF_FIGHT:

  if(n_player_life > n_bot_life)
  {
    printf("\n");
    puts(" ---------");
    puts("| You win |");
    puts(" ---------");
    n_player_wins = n_player_wins + 1;
  }
  else if(n_player_life < n_bot_life)
  {
    printf("\n");
    puts(" -----------");
    puts("| You loose |");
    puts(" -----------");
    n_player_looses = n_player_looses + 1;
  }
  printf("\n wins:%d\n", n_player_wins);
  printf("looses:%d\n", n_player_looses);

  if(n_player_wins == 3)
  {
    goto FIRST_LEVEL;
  }
  else
  {
    goto BEGIN_OF_THE_FIGHT;
  }

/******************************************************************************/

FIRST_LEVEL:

  n_stat = function_stats();

  switch(n_stat)
  {
    case(1):                                                      /* Прибавили силу? */
    {
      while(1)
      {
        n_player_kick = function_player_kick();
        n_player_block = function_player_block();
        n_bot_block = function_bot_block();

        switch(n_player_kick)
        {
          case(1):
          case(2):
          case(3):
          case(4):
          case(5):
          {
            if((n_bot_life <= 0) || (n_player_life <= 0))         /* Если у кого-нибудь кончились хиты, выходим из боя */
            {
              goto END_OF_FIGHT;
            }
            if(n_player_kick != n_bot_block)                      /* Если бот не заблокировал наш удар, бьём его */
            {
              do
              {
                n_player_kick = rand();
              }while((n_player_kick >= 7) && (n_player_kick <= 2)); /* Генерируем удар, учитывая, что мы прибавилу силу */
              n_bot_life -= n_player_kick;
              _sleep(2000);
              printf("\nThis is realy good kick (-%d): [%d/36]\n", n_player_kick, n_bot_life);
            }
            else                                                  /* Если заблокировал - плохо! */
            {
              _sleep(2000);
              printf("\nThe Bot Is Blocked Your Kick\n\n");
            }
            break;
          }
          default:
          {
            exit(1);                                              /* Аварийный выход */
          } 
        } /* End of switch */

        switch(n_player_block)
        {
          case(1):
          case(2):
          case(3):
          case(4):
          case(5):
          {
            if(n_player_block != n_bot_kick)                      /* Если мы не заблокировали удар бота ... */
            {
              do
              {
                n_bot_kick = rand();
              }while(n_bot_kick >= 5);
              n_player_life = n_player_life - n_bot_kick;
              _sleep(2000);
              printf("\nThe Bot Kicked On (-%d): [%d/36]\n\n", n_bot_kick, n_player_life);
            }
            else                                                   /* Если заблокировали - он труп */
            {
              _sleep(2000);
              printf("\nYou Blocked The Kick Of The Bot\n\n");
            }
            break;
          }
          default:
          {
            exit(1);
          }
        } /* End of switch */
      } /* End of while */
      break;
    }
    case(2):                                                      /* Прибавили ловкость? */
    {
      while(1)
      {
        n_player_kick = function_player_kick();
        n_player_block = function_player_block();
        n_bot_block = function_bot_block();
        switch(n_player_kick)
        {
          case(1):
          case(2):
          case(3):
          case(4):
          case(5):
          {
            if((n_bot_life <= 0) || (n_player_life <= 0))         /* Если у кого-нибудь кончились хиты, выходим из боя */
            {
              goto END_OF_FIGHT;
            }
            if(n_player_kick != n_bot_block)                      /* Если бот не заблокировал наш удар, бьём его */
            {
              do
              {
                n_player_kick = rand();
              }while(n_player_kick >= 5);
              n_bot_life = n_bot_life - n_player_kick;
              _sleep(2000);
              printf("\nThis is realy good kick (-%d): [%d/36]\n", n_player_kick, n_bot_life);
            }
            else                                                  /* Если заблокировал - плохо! */
            {
              _sleep(2000);
              printf("\nThe Bot Is Blocked Your Kick\n\n");
            }
            break;
          }
          default:
          {
            exit(1);                                              /* Аварийный выход */
          }
        } /* End of switch */
        switch(n_player_block)
        {
          case(1):
          case(2):
          case(3):
          case(4):
          case(5):
          {
            if(n_player_block != n_bot_kick)                      /* Если мы не заблокировали удар бота ... */
            {
              do
              {
                n_bot_kick = rand();
              }while(n_bot_kick >= 5);
              n_player_life = n_player_life - n_bot_kick;
              _sleep(2000);
              printf("\nThe Bot Kicked On (-%d): [%d/36]\n\n", n_bot_kick, n_player_life);
            }
            else                                                   /* Если заблокировали - он труп */
            {
              _sleep(2000);
              printf("\nYou Blocked The Kick Of The Bot\n\n");
            }
            break;
          }
          default:
          {
            exit(1);
          }
        } /* End of switch */
      } /* End of while */
    }
  }
  system("PAUSE");
  return(0);
}/* End of main */

/******************************************************************************/

int function_start_menu(void)
{
 printf("\nTHIS PROGRAM ORIGINALY CREATED BY _Udaff_ AND MODIFED BY ILikeLSD\n");
 printf("If you have any questions, mailto: _Udaff_@inbox.ru or ILikeLSD@yandex.ru\n");
 return 0;
}

/******************************************************************************/

int function_player_kick(void)
{
  int n_kick;
START_KICK:                                /* Метка */
  printf("\n\nKICK TO:\n");
  puts("|-----------|");
  puts("|1.  HEAD   |");
  puts("|2.  TORS   |");
  puts("|3. STOMACH |");
  puts("|4.  EGGS   |");
  puts("|5.  LEGS   |");
  puts("|-----------|");
  printf("==>");

  n_kick = getche();
  fflush(stdin);                            /* Очиста потока ввода (буфера) */
  if(isdigit(n_kick) == 0)                  /* Если ввели символ, идём к метке */
  {
    printf("\nIncorrect Kick\n\n");
    goto START_KICK;
  }

  switch(n_kick)
  {
    case('1'):
    {
      return(1);
      break;
    }
    case('2'):
    {
      return(2);
      break;
    }
    case('3'):
    {
      return(3);
      break;
    }
    case('4'):
    {
      return(4);
      break;
    }
    case('5'):
    {
      return(5);
      break;
    }
    default:
    {
      printf("\nIncorrect Kick!\n\n");
      goto START_KICK;
    }
  }
}

/******************************************************************************/

int function_player_block(void)
{
  int n_block;
  char c_pointer = 14;
START_BLOCK:                               /* Метка */
  printf("\n\nBLOCK TO:\n");
  puts("|-----------|");
  puts("|1.  HEAD   |");
  puts("|2.  TORS   |");
  puts("|3. STOMACH |");
  puts("|4.  EGGS   |");
  puts("|5.  LEGS   |");
  puts("|-----------|");
  printf("==>");

  n_block = getche();
  fflush(stdin);                            /* Очиста потока ввода (буфера) */
  if(isdigit(n_block) == 0)                 /* Если ввели символ, идём к метке */
  {
    puts("\nTry again\n");
    goto START_BLOCK;
  }

  switch(n_block)
  {
    case('1'):
    {
      return(1);
      break;
    }
    case('2'):
    {
      return(2);
      break;
    }
    case('3'):
    {
      return(3);
      break;
    }
    case('4'):
    {
      return(4);
      break;
    }
    case('5'):
    {
      return(5);
      break;
    }
    default:
    {
      puts("Try again");
      goto START_BLOCK;
    }
  }
}

/******************************************************************************/

int function_bot_block(void)
{
  int n_b_block;

  do
  {
    n_b_block = rand();
  }while(n_b_block >= 5);

  return(n_b_block);
}

/******************************************************************************/

int function_stats(void)                    /* Набрали уровень - кидаем стат */
{
  int stat;
STATS:                                     /* Метка */
  puts("So, you have 1 stat free:");
  puts("|-----------|");
  puts("|1.  Power  |");
  puts("|2.Dexterity|");
  puts("|3.Intuition|");
  puts("|4.  Life   |");
  puts("|-----------|");

  stat = getch();
  fflush(stdin);                            /* Очистка потока ввода (буфера) */
  if(isdigit(stat) == 0)                    /* Если ввели символ, идём к метке */
  {
    printf("\nOnly 1 to 4 please\n");
    goto STATS;
  }
  if((stat < 1) || (stat > 4))
  {
    printf("\nOnly 1 to 4 please\n");
    goto STATS;
  }

  switch(stat)
  {
    case('1'):
    {
      return(1);
      break;
    }
    case('2'):
    {
      return(2);
      break;
    }
    case('3'):
    {
      return(3);
      break;
    }
    case('4'):
    {
      return(4);
      break;
    }
    default:
    {
      exit(1);                                /* Аварийный выход */
    }
  }/* End of switch */
}

/******************************************************************************/

