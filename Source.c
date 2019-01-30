#include <locale.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <gtk/gtk.h>
struct liter
{
  wchar_t cyr;
  char lat[4];
};
const char program_name[] = "ISO 9";
const char text[] = "Текст:";
const char tolat[] = "В латиницу";
const char tocyr[] = "В кирилицу";
GtkWidget* window,* vertical_container,* horizontal_container,* textbox,* textboxtext,* tolat_button,* tocyr_button,* scroller;
GtkTextBuffer* textbox_buffer;
struct liter liters[]=
  {
    {L'А', "A"},   {L'а', "a"},
    {L'Б', "B"},   {L'б', "b"},
    {L'В', "V"},   {L'в', "v"},
    {L'Г', "G"},   {L'г', "g"},
    {L'Д', "D"},   {L'д', "d"},
    {L'Е', "E"},   {L'е', "e"},
    {L'Ё', "YO"},  {L'ё', "yo"},
    {L'Ж', "ZH"},  {L'ж', "zh"},
    {L'З', "Z"},   {L'з', "z"},
    {L'И', "I"},   {L'и', "i"},
    {L'Й', "J"},   {L'й', "j"},
    {L'К', "K"},   {L'к', "k"},
    {L'Л', "L"},   {L'л', "l"},
    {L'М', "M"},   {L'м', "m"},
    {L'Н', "N"},   {L'н', "n"},
    {L'О', "O"},   {L'о', "o"},
    {L'П', "P"},   {L'п', "p"},
    {L'Р', "R"},   {L'р', "r"},
    {L'С', "S"},   {L'с', "s"},
    {L'Т', "T"},   {L'т', "t"},
    {L'У', "U"},   {L'у', "u"},
    {L'Ф', "F"},   {L'ф', "f"},
    {L'Х', "X"},   {L'х', "x"},
    {L'Ц', "C"},   {L'ц', "c"},
    {L'Ч', "CH"},  {L'ч', "ch"},
    {L'Ш', "SH"},  {L'ш', "sh"},
    {L'Щ', "SHH"}, {L'щ', "shh"},
    {L'ъ', "``"},  {L'ъ', "``"},
    {L'Ы', "Y`"},  {L'ы', "y`"},
    {L'ь', "`"},   {L'ь', "`"},
    {L'Э', "E`"},  {L'э', "e`"},
    {L'Ю', "YU"},  {L'ю', "yu"},
    {L'Я', "YA"},  {L'я', "ya"},
  };
bool main(unsigned char arguments_count, char* arguments_value[]);
void update_buttons_status(void);
void build_gui(void);
void fill_liters(void);
void free_liters(void);
void tolat_f(void);
void tocyr_f(void);
bool main(unsigned char arguments_count, char* arguments_value[])
{
  gtk_init((int*)&arguments_count, &arguments_value);
  build_gui();
  gtk_main();
  exit(EXIT_SUCCESS);
  return 0;
}
void update_buttons_status(void)
{
  GtkTextIter start, end;
  gtk_text_buffer_get_bounds (textbox_buffer, &start, &end);
  if(gtk_text_buffer_get_text (textbox_buffer, &start, &end, 0)[0]!='\0')
    {
      gtk_widget_set_sensitive(tocyr_button, 1);
      gtk_widget_set_sensitive(tolat_button, 1);
    }
  else
    {
      gtk_widget_set_sensitive(tocyr_button, 0);
      gtk_widget_set_sensitive(tolat_button, 0);
    }
  return;
}
void tolat_f(void)
{
  GtkTextIter ti;
  bool skip;
  uint16_t i;
  uint32_t datarange;
  wchar_t converted[(gtk_text_buffer_get_char_count((GtkTextBuffer*)textbox_buffer)*3)+1];
  wchar_t buffer[sizeof(converted)/sizeof(wchar_t)];
  const wchar_t* path;
  char* unibyte;
  swprintf(converted, sizeof(converted)/sizeof(wchar_t), L"");
  setlocale(LC_ALL, "ru_RU.UTF-8");
  gtk_text_buffer_get_start_iter(textbox_buffer, &ti);
  while(gtk_text_iter_get_char(&ti)!='\0')
    {
      
      skip=0;
      for(i=0; i<66; i++)
	{
	  if(gtk_text_iter_get_char(&ti)==liters[i].cyr)
	    {
	      swprintf(buffer, sizeof(buffer)/sizeof(wchar_t), L"%ls%s", converted, liters[i].lat);
	      skip=1;
	      break;
	    }
	}
      if(!skip)
	{
	  swprintf(buffer, sizeof(buffer)/sizeof(wchar_t), L"%ls%lc", converted, gtk_text_iter_get_char(&ti));
	}
      swprintf(converted, sizeof(converted)/sizeof(wchar_t), L"%ls", buffer);
      gtk_text_iter_forward_char (&ti);
    }
  path = converted;
  unibyte = malloc(((datarange = wcsrtombs(0, &path, 0, 0)+1))*sizeof(char));
  wcsrtombs(unibyte, &path, datarange, 0);
  gtk_text_buffer_set_text((GtkTextBuffer*)textbox_buffer, unibyte, -1);
  free(unibyte);
  return;
}
void tocyr_f(void)
{
  GtkTextIter ti;
  bool skip;
  uint16_t i, j;
  uint32_t datarange;
  wchar_t original[gtk_text_buffer_get_char_count((GtkTextBuffer*)textbox_buffer)+1];
  wchar_t converted[sizeof(original)/sizeof(wchar_t)];
  wchar_t buffer[sizeof(converted)/sizeof(wchar_t)];
  const wchar_t* path;
  char* unibyte;
  swprintf(converted, sizeof(converted)/sizeof(wchar_t), L"");
  setlocale(LC_ALL, "ru_RU.UTF-8");
  gtk_text_buffer_get_start_iter(textbox_buffer, &ti);
  for(i=0; gtk_text_iter_get_char(&ti)!='\0'; i++, gtk_text_iter_forward_char (&ti))
    {
      original[i]=gtk_text_iter_get_char(&ti);
    }
  original[i]='\0';
  for(i=0; original[i]!='\0'; i++)
    {
      skip=0;
      if(original[i+1]!='\0'&&original[i+2]!='\0')
	{
	  for(j=52; j<54; j++)
	    {
	      if(original[i]==liters[j].lat[0]&&original[i+1]==liters[j].lat[1]&&original[i+2]==liters[j].lat[2])
		{
		  swprintf(buffer, sizeof(buffer)/sizeof(wchar_t), L"%ls%lc", converted, liters[j].cyr);
		  skip=1;
		  i+=2;
		  break;
		}
	    }
	}
      if(!skip&&original[i+1]!='\0')
	{
	  for(j=12; j<66; j++)
	    {
	      if((15<j&&j<48)||(51<j&&j<54)||(57<j&&j<60))
		{
		  continue;
		}
	      else
		{
		  if(original[i]==liters[j].lat[0]&&original[i+1]==liters[j].lat[1])
		    {
		      swprintf(buffer, sizeof(buffer)/sizeof(wchar_t), L"%ls%lc", converted, liters[j].cyr);
		      skip=1;
		      i++;
		      break;
		    }
		}
	    }
	}
      if(!skip)
	{
	  for(j=0; j<60; j++)
	    {
	      if((11<j&&j<16)||(47<j&&j<58))
		{
		  continue;
		}
	      else
		{
		  if(original[i]==liters[j].lat[0])
		    {
		      swprintf(buffer, sizeof(buffer)/sizeof(wchar_t), L"%ls%lc", converted, liters[j].cyr);
		      skip=1;
		      break;
		    }
		}
	    }
	}
      if(!skip)
	{
	  swprintf(buffer, sizeof(buffer)/sizeof(wchar_t), L"%ls%lc", converted, original[i]);
	}
      swprintf(converted, sizeof(converted)/sizeof(wchar_t), L"%ls", buffer);
    }
  path = converted;
  unibyte = malloc(((datarange = wcsrtombs(0, &path, 0, 0)+1))*sizeof(char));
  wcsrtombs(unibyte, &path, datarange, 0);
  gtk_text_buffer_set_text((GtkTextBuffer*)textbox_buffer, unibyte, -1);
  free(unibyte);
  return;
}
void build_gui(void)
{
  textbox_buffer = gtk_text_buffer_new(0);
  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  vertical_container=gtk_vbox_new(0, 0);
  textboxtext=gtk_label_new(text);
  textbox = gtk_text_view_new_with_buffer(textbox_buffer);
  horizontal_container=gtk_hbox_new(0,0);
  tolat_button = gtk_button_new_with_label(tolat);
  tocyr_button = gtk_button_new_with_label(tocyr);
  scroller = gtk_scrolled_window_new(0, 0);
  gtk_window_set_title((GtkWindow*)window, program_name);
  gtk_widget_set_size_request((GtkWidget*)window, 240, 320);
  gtk_misc_set_alignment ((GtkMisc*)textboxtext, 0, 0);
  gtk_widget_set_sensitive(tocyr_button, 0);
  gtk_widget_set_sensitive(tolat_button, 0);
  gtk_text_view_set_wrap_mode((GtkTextView*)textbox, GTK_WRAP_WORD_CHAR);
  gtk_scrolled_window_set_policy((GtkScrolledWindow*)scroller, GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
  gtk_container_add((GtkContainer*)window, vertical_container);
  gtk_box_pack_start((GtkBox*)vertical_container, textboxtext, 0, 0, 0);
  gtk_box_pack_start((GtkBox*)vertical_container, scroller, 1, 1, 0);
  gtk_container_add((GtkContainer*)scroller, textbox);
  gtk_box_pack_start((GtkBox*)vertical_container, horizontal_container, 0, 0, 0);
  gtk_box_pack_start((GtkBox*)horizontal_container, tolat_button, 1, 1, 0);
  gtk_box_pack_start((GtkBox*)horizontal_container, tocyr_button, 1, 1, 0);
  g_signal_connect ((GtkObject*)window, "delete-event", G_CALLBACK(gtk_main_quit), 0);
  g_signal_connect (textbox_buffer, "changed", G_CALLBACK(update_buttons_status), 0);
  g_signal_connect (tolat_button, "clicked", G_CALLBACK(tolat_f), 0);
  g_signal_connect (tocyr_button, "clicked", G_CALLBACK(tocyr_f), 0);
  gtk_widget_show_all(window);
  return;
}
