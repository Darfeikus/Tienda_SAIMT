//install to compile:	sudo apt-get install libgtk-3-dev
//Compile with:			gcc `pkg-config --cflags gtk+-3.0` -o 1329256 1329256.c `pkg-config --libs gtk+-3.0`
/*
  Program: SAIMT inventory management system
  Antonio Diaz Flores
  A01329256
  Oscar Barbosa Aquino
  A01329173
  Date: 16/11/18
*/
#include <gtk/gtk.h>
#include "avlTree.h"

struct node* root = NULL;

/*
  Function that displays an error message if a key is not found, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void key_not_found(GtkWidget *widget, gpointer data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "ID no encontrado!");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("OK");

  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  GtkWidget *confirmacionID;
  confirmacionID = gtk_label_new ("ID no encontrado!");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, 0, 2, 1);

  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_widget_show_all (window);
}

/*
  Function that displays an error message if a file is not found, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void file_not_found()
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "ID no encontradoArchivo no encontrado!");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("OK");

  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  GtkWidget *confirmacionID;
  confirmacionID = gtk_label_new ("Archivo no encontrado! Se crea un nuevo data.adob");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, 0, 2, 1);

  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_widget_show_all (window);
}

/*
  Function that displays a product addition confirmation message, receives data of type int and Gtkwidget and returns nothing.
*/
static void confirmacion_agregado(GtkWidget *widget, int correcto)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  if (correcto)
    gtk_window_set_title (GTK_WINDOW (window), "Agregado correctamente");
  else
  	gtk_window_set_title (GTK_WINDOW (window), "Error! :(");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("OK");

  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  GtkWidget *confirmacionID;
  if (correcto)
    confirmacionID = gtk_label_new ("Producto agregado!");
  else
  	confirmacionID = gtk_label_new ("ID repetido :(");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, 0, 2, 1);

  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_widget_show_all (window);
}

/*
  Function that handles the data of an input field, receives data Gtkwidget and returns nothing.
*/
static void agregarVarios( GtkWidget *widget,
                            GtkWidget **entry )
{
  const gchar **entry_text = malloc(4*sizeof(gchar*));
  char** copiaentry  = malloc(5*sizeof(char*));
  for (int i = 0; i < 4; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  	*(copiaentry+i) = malloc(strlen(*(entry_text+i)));
  	strcpy(*(copiaentry+i),*(entry_text+i));
  }
  *(copiaentry+4)=malloc(sizeof(char)*5);
  *(copiaentry+4)="1";
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  confirmacion_agregado(NULL,insert(&root,copiaentry,key));
}

/*
  Function that displays the add product window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void agregar_producto(GtkWidget *widget, gpointer data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Agregar producto");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("Agregar producto");

  gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 2, 1);

  GtkWidget** entries = malloc(4*sizeof(GtkWidget*));


  GtkWidget *textoID;
  textoID = gtk_label_new ("ID");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 0, 1, 1);

  *(entries+0) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+0)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+0), 1, 0, 1, 1);

  GtkWidget *textoNombre;
  textoNombre = gtk_label_new ("Producto");
  gtk_grid_attach (GTK_GRID (grid), textoNombre, 0, 1, 1, 1);

  *(entries+1) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+1)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+1), 1, 1, 1, 1);
  
  GtkWidget *textoPrecioCompra;
  textoPrecioCompra = gtk_label_new ("Cantidad");
  gtk_grid_attach (GTK_GRID (grid), textoPrecioCompra, 0, 2, 1, 1);

  *(entries+2) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+2)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+2), 1, 2, 1, 1);

  GtkWidget *textoPrecioVenta;
  textoPrecioVenta = gtk_label_new ("Precio");
  gtk_grid_attach (GTK_GRID (grid), textoPrecioVenta, 0, 3, 1, 1);

  *(entries+3) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+3)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+3), 1, 3, 1, 1);

  g_signal_connect (button, "clicked", G_CALLBACK (agregarVarios), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_widget_show_all (window);
}

/*
  Function that displays a product edit confirmation message, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void confirmacion_editado(GtkWidget *widget, gpointer data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Editado correctamente");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("OK");

  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  GtkWidget *confirmacionID;
  confirmacionID = gtk_label_new ("Producto editado!");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, 0, 2, 1);

  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_widget_show_all (window);
}

/*
  Function that handles the data of an input field, receives data Gtkwidget and returns nothing.
*/
static void editarVarios( GtkWidget *widget,
                            GtkWidget **entry )
{
  const gchar **entry_text = malloc(4*sizeof(gchar*));
  char** copiaentry  = malloc(4*sizeof(char*));
  for (int i = 0; i < 4; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  	*(copiaentry+i) = malloc(strlen(*(entry_text+i)));
  	strcpy(*(copiaentry+i),*(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  editDis(copiaentry);
  confirmacion_editado(NULL,NULL);
}

/*
  Function that displays the product auxiliary edition window, receives data of type char** and Gtkwidget and returns nothing.
*/
static void editar_producto_aux(GtkWidget *widget, char **originales)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Editar producto");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("Editar producto");

  gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 2, 1);

  GtkWidget** entries = malloc(4*sizeof(GtkWidget*));


  GtkWidget *textoID;
  textoID = gtk_label_new ("ID");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 0, 1, 1);

  *(entries+0) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+0)),1024);
  gtk_entry_set_text (GTK_ENTRY (*(entries+0)), *(originales+0));
  gtk_editable_set_editable(GTK_EDITABLE(*(entries+0)), FALSE);
  gtk_grid_attach (GTK_GRID (grid), *(entries+0), 1, 0, 1, 1);

  GtkWidget *textoNombre;
  textoNombre = gtk_label_new ("Producto");
  gtk_grid_attach (GTK_GRID (grid), textoNombre, 0, 1, 1, 1);

  *(entries+1) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+1)),1024);
  gtk_entry_set_text (GTK_ENTRY (*(entries+1)), *(originales+1));
  gtk_grid_attach (GTK_GRID (grid), *(entries+1), 1, 1, 1, 1);
  
  GtkWidget *textoPrecioCompra;
  textoPrecioCompra = gtk_label_new ("Cantidad");
  gtk_grid_attach (GTK_GRID (grid), textoPrecioCompra, 0, 2, 1, 1);

  *(entries+2) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+2)),1024);
  gtk_entry_set_text (GTK_ENTRY (*(entries+2)), *(originales+2));
  gtk_grid_attach (GTK_GRID (grid), *(entries+2), 1, 2, 1, 1);

  GtkWidget *textoPrecioVenta;
  textoPrecioVenta = gtk_label_new ("Precio");
  gtk_grid_attach (GTK_GRID (grid), textoPrecioVenta, 0, 3, 1, 1);

  *(entries+3) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+3)),1024);
  gtk_entry_set_text (GTK_ENTRY (*(entries+3)), *(originales+3));
  gtk_grid_attach (GTK_GRID (grid), *(entries+3), 1, 3, 1, 1);

  g_signal_connect (button, "clicked", G_CALLBACK (editarVarios), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_widget_show_all (window);
}

/*
  Function that handles the data of an input field, receives data Gtkwidget and returns nothing.
*/
static void editarUno( GtkWidget *widget,
                            GtkWidget **entry )
{
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  char** dec = modifyId(&root,key);
  if(*(dec+4))
  	editar_producto_aux(NULL,dec);
  else
  	key_not_found(NULL,NULL);
}

/*
  Function that displays the edit product window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void editar_producto(GtkWidget *widget, gpointer data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Editar producto");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  GtkWidget** entries = malloc(1*sizeof(GtkWidget*));

  button = gtk_button_new_with_label ("Editar producto");

  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 2, 1);

  GtkWidget *textoID;
  textoID = gtk_label_new ("ID");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 0, 1, 1);

  *(entries+0) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+0)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+0), 1, 0, 1, 1);

  g_signal_connect (button, "clicked", G_CALLBACK (editarUno), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_widget_show_all (window);
}

/*
  Function that displays a product reactivation confirmation message, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void confirmacion_reactivado(GtkWidget *widget, char **entries)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Estas seguro?");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("Si");
  g_signal_connect (button, "clicked", G_CALLBACK (recoverDis), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 5, 2, 1);

  button = gtk_button_new_with_label ("No");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 2, 5, 2, 1);

  GtkWidget *textoID;
  textoID = gtk_label_new ("ID");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 1, 1, 1);

  GtkWidget *textoInfoID;
  textoInfoID = gtk_label_new (*(entries+0));
  gtk_grid_attach (GTK_GRID (grid), textoInfoID, 1, 1, 3, 1);

  GtkWidget *textoProducto;
  textoProducto = gtk_label_new ("Producto");
  gtk_grid_attach (GTK_GRID (grid), textoProducto, 0, 2, 1, 1);

  GtkWidget *textoInfoProducto;
  textoInfoProducto = gtk_label_new (*(entries+1));
  gtk_grid_attach (GTK_GRID (grid), textoInfoProducto, 2, 2, 3, 1);

  GtkWidget *textoPrecioCompra;
  textoPrecioCompra = gtk_label_new ("Cantidad");
  gtk_grid_attach (GTK_GRID (grid), textoPrecioCompra, 0, 3, 1, 1);

  GtkWidget *textoInfoPrecioCompra;
  textoInfoPrecioCompra = gtk_label_new (*(entries+2));
  gtk_grid_attach (GTK_GRID (grid), textoInfoPrecioCompra, 2, 3, 3, 1);

  GtkWidget *textoPrecioVenta;
  textoPrecioVenta = gtk_label_new ("Precio Venta");
  gtk_grid_attach (GTK_GRID (grid), textoPrecioVenta, 0, 4, 1, 1);

  GtkWidget *textoInfoPrecioVenta;
  textoInfoPrecioVenta = gtk_label_new (*(entries+3));
  gtk_grid_attach (GTK_GRID (grid), textoInfoPrecioVenta, 2, 4, 3, 1);

  GtkWidget *confirmacionID;
  confirmacionID = gtk_label_new ("Estas seguro de que quieres recuperar el siguiente producto?");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, 0, 4, 1);

  gtk_widget_show_all (window);
}

/*
  Function that handles the data of an input field, receives data Gtkwidget and returns nothing.
*/
static void reactivarUno( GtkWidget *widget,
                            GtkWidget **entry )
{
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  char** dec = recoverId(&root,key);
  if(*(dec+4))
  	confirmacion_reactivado(NULL,dec);
  else
  	key_not_found(NULL,NULL);
}

/*
  Function that displays the product reactivation window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void reactivar_producto(GtkWidget *widget, gpointer data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Recuperar producto");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  GtkWidget** entries = malloc(1*sizeof(GtkWidget*));

  button = gtk_button_new_with_label ("Recuperar producto");

  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 2, 1);

  GtkWidget *textoID;
  textoID = gtk_label_new ("ID");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 0, 1, 1);

  *(entries+0) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+0)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+0), 1, 0, 1, 1);

  g_signal_connect (button, "clicked", G_CALLBACK (reactivarUno), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_widget_show_all (window);
}

/*
  Function that displays a product deletion confirmation message, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void confirmacion_borrado(GtkWidget *widget, char **entries)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Estas seguro?");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("Si");
  g_signal_connect (button, "clicked", G_CALLBACK (deleteDis), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 5, 2, 1);

  button = gtk_button_new_with_label ("No");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 2, 5, 2, 1);

  GtkWidget *textoID;
  textoID = gtk_label_new ("ID");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 1, 1, 1);

  GtkWidget *textoInfoID;
  textoInfoID = gtk_label_new (*(entries+0));
  gtk_grid_attach (GTK_GRID (grid), textoInfoID, 1, 1, 3, 1);

  GtkWidget *textoProducto;
  textoProducto = gtk_label_new ("Producto");
  gtk_grid_attach (GTK_GRID (grid), textoProducto, 0, 2, 1, 1);

  GtkWidget *textoInfoProducto;
  textoInfoProducto = gtk_label_new (*(entries+1));
  gtk_grid_attach (GTK_GRID (grid), textoInfoProducto, 2, 2, 3, 1);

  GtkWidget *textoPrecioCompra;
  textoPrecioCompra = gtk_label_new ("Cantidad");
  gtk_grid_attach (GTK_GRID (grid), textoPrecioCompra, 0, 3, 1, 1);

  GtkWidget *textoInfoPrecioCompra;
  textoInfoPrecioCompra = gtk_label_new (*(entries+2));
  gtk_grid_attach (GTK_GRID (grid), textoInfoPrecioCompra, 2, 3, 3, 1);

  GtkWidget *textoPrecioVenta;
  textoPrecioVenta = gtk_label_new ("Precio Venta");
  gtk_grid_attach (GTK_GRID (grid), textoPrecioVenta, 0, 4, 1, 1);

  GtkWidget *textoInfoPrecioVenta;
  textoInfoPrecioVenta = gtk_label_new (*(entries+3));
  gtk_grid_attach (GTK_GRID (grid), textoInfoPrecioVenta, 2, 4, 3, 1);

  GtkWidget *confirmacionID;
  confirmacionID = gtk_label_new ("Estas seguro de que quieres borrar el siguiente producto?");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, 0, 4, 1);

  gtk_widget_show_all (window);
}

/*
  Function that handles the data of an input field, receives data Gtkwidget and returns nothing.
*/
static void borrarUno( GtkWidget *widget,
                            GtkWidget **entry )
{
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  char** dec = deleteData(&root,key);
  if(*(dec+4))
  	confirmacion_borrado(NULL,dec);
  else
  	key_not_found(NULL,NULL);
}

/*
  Function that displays the product deletion window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void borrar_producto(GtkWidget *widget, gpointer data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Borrar producto");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  GtkWidget** entries = malloc(1*sizeof(GtkWidget*));

  button = gtk_button_new_with_label ("Borrar producto");

  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 2, 1);

  GtkWidget *textoID;
  textoID = gtk_label_new ("ID");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 0, 1, 1);

  *(entries+0) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+0)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+0), 1, 0, 1, 1);

  g_signal_connect (button, "clicked", G_CALLBACK (borrarUno), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_widget_show_all (window);
}

/*
  Function that prints the search results window, receives data of type char*** and Gtkwidget and returns nothing.
*/
static void printBuscar(GtkWidget *widget, char ***entradasReporte) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Resultados");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  int i = 1;

  GtkWidget *confirmacionID;
  GtkWidget *confirmacionProducto;
  GtkWidget *confirmacionPrecioCompra;
  GtkWidget *confirmacionPrecioVenta;

  confirmacionID = gtk_label_new ("\tID\t");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, i, 1, 1);

  confirmacionProducto = gtk_label_new ("\tProducto\t");
  gtk_grid_attach (GTK_GRID (grid), confirmacionProducto, 2, i, 1, 1);

  confirmacionPrecioCompra = gtk_label_new ("\tCantidad\t");
  gtk_grid_attach (GTK_GRID (grid), confirmacionPrecioCompra, 4, i, 1, 1);

  confirmacionPrecioVenta = gtk_label_new ("\tPrecio Venta\t");
  gtk_grid_attach (GTK_GRID (grid), confirmacionPrecioVenta, 6, i, 1, 1);

  i++;
  while(*entradasReporte){
    confirmacionID = gtk_label_new (*((*entradasReporte)+0));
    gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, i, 2, 1);

    confirmacionProducto = gtk_label_new (*((*entradasReporte)+1));
    gtk_grid_attach (GTK_GRID (grid), confirmacionProducto, 2, i, 2, 1);

    confirmacionPrecioCompra = gtk_label_new (*((*entradasReporte)+2));
    gtk_grid_attach (GTK_GRID (grid), confirmacionPrecioCompra, 4, i, 2, 1);

    confirmacionPrecioVenta = gtk_label_new (*((*entradasReporte)+3));
    gtk_grid_attach (GTK_GRID (grid), confirmacionPrecioVenta, 6, i, 2, 1);

    i++;
  	entradasReporte++;
  }

  button = gtk_button_new_with_label ("OK");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 4, i, 4, 1);

  gtk_widget_show_all (window);
}

/*
  Function that handles the data of an input field, receives data Gtkwidget and returns nothing.
*/
static void buscarIdExacto( GtkWidget *widget,
                            GtkWidget **entry )
{
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  char*** dec = searchExactMatch(root,key);
  if(dec)
  	printBuscar(NULL,dec);
  else
  	key_not_found(NULL,NULL);
  free(dec);
}

/*
  Function that handles the data of an input field, receives data Gtkwidget and returns nothing.
*/
static void buscarIdMenor( GtkWidget *widget,
                            GtkWidget **entry )
{
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  char*** dec = searchLesser(root,key);
  if(dec)
  	printBuscar(NULL,dec);
  else
  	key_not_found(NULL,NULL);
  free(dec);
}

/*
  Function that handles the data of an input field, receives data Gtkwidget and returns nothing.
*/
static void buscarIdMayor( GtkWidget *widget,
                            GtkWidget **entry )
{
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  char*** dec = searchGreater(root,key);
  if(dec)
  	printBuscar(NULL,dec);
  else
  	key_not_found(NULL,NULL);
  free(dec);
}

/*
  Function that handles the data of an input field, receives data Gtkwidget and returns nothing.
*/
static void buscarTextoParcial( GtkWidget *widget,
                            GtkWidget **entry )
{
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  char*** dec = searchPartialMatch(root,key);
  if(dec)
  	printBuscar(NULL,dec);
  else
  	key_not_found(NULL,NULL);
  free(key);
  free(dec);
}

/*
  Function that handles the data of an input field, receives data Gtkwidget and returns nothing.
*/
static void buscarTextoExacto( GtkWidget *widget,
                            GtkWidget **entry )
{
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  char*** dec = searchStr(root,key);
  if(dec)
  	printBuscar(NULL,dec);
  else
  	key_not_found(NULL,NULL);
  free(dec);
}

/*
  Function that displays the product auxiliary search window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void buscar_producto_otro(GtkWidget *widget, gpointer data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Buscar producto");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  GtkWidget** entries = malloc(1*sizeof(GtkWidget*));

  GtkWidget *textoID;
  textoID = gtk_label_new ("Texto");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 0, 1, 1);

  *(entries+0) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+0)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+0), 1, 0, 1, 1);


  button = gtk_button_new_with_label ("Texto exacto");
  g_signal_connect (button, "clicked", G_CALLBACK (buscarTextoExacto), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 1, 1);


  button = gtk_button_new_with_label ("Subtexto");
  g_signal_connect (button, "clicked", G_CALLBACK (buscarTextoParcial), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 1, 2, 1, 1);


  gtk_widget_show_all (window);
}

/*
  Function that displays the product auxiliary search window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void buscar_producto_id(GtkWidget *widget, gpointer data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Buscar producto");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  GtkWidget** entries = malloc(1*sizeof(GtkWidget*));

  GtkWidget *textoID;
  textoID = gtk_label_new ("ID");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 0, 1, 1);

  *(entries+0) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+0)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+0), 1, 0, 1, 1);


  button = gtk_button_new_with_label ("ID exacto");
  g_signal_connect (button, "clicked", G_CALLBACK (buscarIdExacto), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 1, 1);


  button = gtk_button_new_with_label ("ID <=");
  g_signal_connect (button, "clicked", G_CALLBACK (buscarIdMenor), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 1, 2, 1, 1);


  button = gtk_button_new_with_label ("ID >=");
  g_signal_connect (button, "clicked", G_CALLBACK (buscarIdMayor), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 2, 2, 1, 1);


  gtk_widget_show_all (window);
}

/*
  Function that displays the product search window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void buscar_producto(GtkWidget *widget, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Buscar producto");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("ID");
  g_signal_connect (button, "clicked", G_CALLBACK (buscar_producto_id), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  button = gtk_button_new_with_label ("Otra");
  g_signal_connect (button, "clicked", G_CALLBACK (buscar_producto_otro), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 2, 1, 2, 1);

  GtkWidget *confirmacionID;
  confirmacionID = gtk_label_new ("Buscar por");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, 0, 4, 1);

  gtk_widget_show_all (window);
}

/*
  Function that encrypts a message with a key, receives data of type *char and returns another *char.
*/
static char *xorencrypt(char *message, char *key) {
    size_t messagelen = strlen(message);
    size_t keylen = strlen(key);

    char *encrypted = malloc(messagelen+1);

    int i;
    for(i = 0; i < messagelen; i++) {
        encrypted[i] = message[i] ^ key[i % keylen];
    }
    encrypted[messagelen] = '\0';

    return encrypted;
}

/*
  Function that handles the data of an input field and desencrypts it, receives data Gtkwidget and returns nothing.
*/
static void procInicio(char **entry_text) {
  root = NULL;
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);

  FILE *in_file = fopen(key, "r"); // write only 
           
  // test for files not existing.
  if (in_file == NULL) 
  {   
    printf("Archivo no presente\n");
    file_not_found();
    free(key);
    return;
  } 

  char* entrada = (char*)malloc(1024*sizeof(char));
  char** aAgregar = (char**)malloc(5*sizeof(char*));
  *aAgregar = (char*)malloc(1024*sizeof(char));
  *(aAgregar+1) = (char*)malloc(1024*sizeof(char));
  *(aAgregar+2) = (char*)malloc(1024*sizeof(char));
  *(aAgregar+3) = (char*)malloc(1024*sizeof(char));
  *(aAgregar+4) = (char*)malloc(1024*sizeof(char));
  int i=0;
  while(fgets(entrada, 1024,in_file)){
    for (int j = 0; *(entrada+j)!='\0'; ++j)
    {
      if(*(entrada+j)=='\n') {
        *(entrada+j)='\0';
        j--;
      }
    }
    strcpy(*(aAgregar+i),entrada);
    if(i==4)
      insert(&root,aAgregar,*aAgregar);
    i=(i+1)%5;
  }
  fclose(in_file);
  free(entrada);
  free(key);
  // write to file vs write to screen 
}

/*
  Function that handles the data of an input field and desencrypts it, receives data Gtkwidget and returns nothing.
*/
static void procDesencriptar(GtkWidget *widget, GtkWidget **entry) {
  root = NULL;
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);

  FILE *in_file = fopen(key, "r"); // write only 
           
  // test for files not existing.
  if (in_file == NULL) 
  {   
    printf("Error! Could not open file\n");
    free(key);
    return;
  } 

  char* entrada = (char*)malloc(1024*sizeof(char));
  char** aAgregar = (char**)malloc(5*sizeof(char*));
  *aAgregar = (char*)malloc(1024*sizeof(char));
  *(aAgregar+1) = (char*)malloc(1024*sizeof(char));
  *(aAgregar+2) = (char*)malloc(1024*sizeof(char));
  *(aAgregar+3) = (char*)malloc(1024*sizeof(char));
  *(aAgregar+4) = (char*)malloc(1024*sizeof(char));
  int i=0;
  while(fgets(entrada, 1024,in_file)){
  	for (int j = 0; *(entrada+j)!='\0'; ++j)
  	{
  		if(*(entrada+j)=='\n') {
  			*(entrada+j)='\0';
  			j--;
  		}
  	}
  	strcpy(*(aAgregar+i),entrada);
  	if(i==4)
  		insert(&root,aAgregar,*aAgregar);
  	i=(i+1)%5;
  }
  fclose(in_file);
  free(entrada);
  free(key);
  // write to file vs write to screen 
}

/*
  Function that displays the upload window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void cargar(GtkWidget *widget, gpointer user_data)
{
  printf ("Seguro de que quieres borrar tus datos actuales y cargar desde un archivo?\n");

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Estas seguro?");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  GtkWidget** entries = malloc(1*sizeof(GtkWidget*));

  button = gtk_button_new_with_label ("Si");
  g_signal_connect (button, "clicked", G_CALLBACK (procDesencriptar), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 2, 1);

  button = gtk_button_new_with_label ("No");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 2, 2, 2, 1);

  GtkWidget *textoID;
  textoID = gtk_label_new ("Nombre archivo");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 1, 2, 1);

  *(entries+0) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+0)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+0), 2, 1, 2, 1);

  GtkWidget *confirmacionID;
  confirmacionID = gtk_label_new ("Seguro de que quieres borrar tus datos actuales y cargar desde un archivo?");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, 0, 4, 1);

  gtk_widget_show_all (window);
}

/*
  Function that handles the data of an input field and writes a file, receives data Gtkwidget and returns nothing.
*/
static void guardarReporte(GtkWidget *widget, GtkWidget **entry) {
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);

  char*** dec = guardarArbol(root);

  FILE *out_file = fopen(key, "w"); // write only 
  // test for files not existing.
  if (out_file == NULL) 
  {   
    printf("Error! Could not open file\n");
    free(key);
    return;
  } 

  while(*dec){
    for (int i = 0; i < 5; ++i)
    {
      fprintf(out_file, "%20s\t", *((*dec)+i)); // write to file 
      fprintf(stdout, "%20s\t", *((*dec)+i)); // write to screen  
  	}
    dec++;
    fprintf(out_file, "\n"); // write to file 
    fprintf(stdout, "\n"); // write to screen 
  }
  fclose(out_file);
  free(key);
  // write to file vs write to screen 
}

/*
  Function that handles the data of an input field and writes a file, receives data Gtkwidget and returns nothing.
*/
static void guardarFinal(GtkWidget *widget, gchar **entry_text) {
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  strcat(key,".adob");

  char*** dec = guardarArbol(root);

  if(dec)
    {
      FILE *out_file = fopen(key, "w"); // write only 
                 
      // test for files not existing.
      if (out_file == NULL) 
      {   
        printf("Error! Could not open file\n");
        free(key);
        return;
      } 
      while(*dec){
        for (int i = 0; i < 5; ++i)
        {
          char *entrada = *((*dec)+i);
          fprintf(out_file, "%s\n", entrada); // write to file 
          fprintf(stdout, "%s\n", entrada); // write to screen
          free(entrada);
        }
        dec++;
      }
      fclose(out_file);
      // write to file vs write to screen 
    }
    else{
       FILE *out_file = fopen(key, "w"); // write only
       fprintf(out_file, "\n"); // write to file 
       fclose(out_file);
    }
    free(key);
}

/*
  Function that handles the data of an input field and writes a file, receives data Gtkwidget and returns nothing.
*/
static void guardarEncriptado(GtkWidget *widget, GtkWidget **entry) {
  const gchar **entry_text = malloc(1*sizeof(gchar*));
  for (int i = 0; i < 1; ++i)
  {
    *(entry_text+i) = gtk_entry_get_text (GTK_ENTRY (*(entry+i)));
  	printf ("Entry contents: %s\n", *(entry_text+i));
  }
  char* key = (char*)(malloc(sizeof(char)*1024));
  strcpy(key,*entry_text);
  strcat(key,".adob");

  char*** dec = guardarArbol(root);

  if(dec){
    FILE *out_file = fopen(key, "w"); // write only 
             
    // test for files not existing.
    if (out_file == NULL) 
    {   
      printf("Error! Could not open file\n");
      free(key);
      return;
    } 
  
    while(*dec){
      for (int i = 0; i < 5; ++i)
      {
        char *entrada = *((*dec)+i);
        fprintf(out_file, "%s\n", entrada); // write to file 
        fprintf(stdout, "%s\n", entrada); // write to screen
        free(entrada);
      }
      dec++;
    }
    fclose(out_file);
    // write to file vs write to screen 
  }
  free(key);
}

/*
  Function that displays the save window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void guardar(GtkWidget *widget, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Guardar");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  GtkWidget** entries = malloc(1*sizeof(GtkWidget*));

  GtkWidget *textoID;
  textoID = gtk_label_new ("Nombre archivo");
  gtk_grid_attach (GTK_GRID (grid), textoID, 0, 0, 1, 1);

  *(entries+0) = gtk_entry_new();
  gtk_entry_set_max_length (GTK_ENTRY (*(entries+0)),1024);
  gtk_grid_attach (GTK_GRID (grid), *(entries+0), 1, 0, 1, 1);


  button = gtk_button_new_with_label ("Reporte");
  g_signal_connect (button, "clicked", G_CALLBACK (guardarReporte), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 1, 1);


  button = gtk_button_new_with_label (".adob");
  g_signal_connect (button, "clicked", G_CALLBACK (guardarEncriptado), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 1, 2, 1, 1);


  gtk_widget_show_all (window);
}

/*
  Function that displays the administrative tools window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void administrativas(GtkWidget *widget, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Buscar producto");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("Guardar");
  g_signal_connect (button, "clicked", G_CALLBACK (guardar), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  button = gtk_button_new_with_label ("Cargar");
  g_signal_connect (button, "clicked", G_CALLBACK (cargar), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 2, 1, 2, 1);

  GtkWidget *confirmacionID;
  confirmacionID = gtk_label_new ("Herramientas administrativas");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, 0, 4, 1);

  gtk_widget_show_all (window);
}

int mandar = 0;

/*
  Function that displays the auxiliary report export window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void reporteUno( GtkWidget *widget,
                            gpointer data)
{
  int key  = mandar;
  printf("%d\n", key);
  char*** entradasReporte = reporteSwitch(root,key);

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Reporte");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  int i = 1;

  GtkWidget *confirmacionID;
  GtkWidget *confirmacionProducto;
  GtkWidget *confirmacionPrecioCompra;
  GtkWidget *confirmacionPrecioVenta;

  confirmacionID = gtk_label_new ("\tID\t");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, i, 1, 1);

  confirmacionProducto = gtk_label_new ("\tProducto\t");
  gtk_grid_attach (GTK_GRID (grid), confirmacionProducto, 2, i, 1, 1);

  confirmacionPrecioCompra = gtk_label_new ("\tCantidad\t");
  gtk_grid_attach (GTK_GRID (grid), confirmacionPrecioCompra, 4, i, 1, 1);

  confirmacionPrecioVenta = gtk_label_new ("\tPrecio Venta\t");
  gtk_grid_attach (GTK_GRID (grid), confirmacionPrecioVenta, 6, i, 1, 1);

  i++;
  while(entradasReporte && *entradasReporte){
    confirmacionID = gtk_label_new (*((*entradasReporte)+0));
    gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, i, 2, 1);

    confirmacionProducto = gtk_label_new (*((*entradasReporte)+1));
    gtk_grid_attach (GTK_GRID (grid), confirmacionProducto, 2, i, 2, 1);

    confirmacionPrecioCompra = gtk_label_new (*((*entradasReporte)+2));
    gtk_grid_attach (GTK_GRID (grid), confirmacionPrecioCompra, 4, i, 2, 1);

    confirmacionPrecioVenta = gtk_label_new (*((*entradasReporte)+3));
    gtk_grid_attach (GTK_GRID (grid), confirmacionPrecioVenta, 6, i, 2, 1);

    i++;
  	entradasReporte++;
  }

  button = gtk_button_new_with_label ("OK");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 4, i, 4, 1);

  gtk_widget_show_all (window);
}

static void mandar1(GtkWidget *widget, gpointer data) {
  mandar = 1;
  reporteUno(NULL,NULL);
}

static void mandar2(GtkWidget *widget, gpointer data) {
  mandar = 2;
  reporteUno(NULL,NULL);
}

static void mandar3(GtkWidget *widget, gpointer data) {
  mandar = 3;
  reporteUno(NULL,NULL);
}

static void mandar4(GtkWidget *widget, gpointer data) {
  mandar = 4;
  reporteUno(NULL,NULL);
}

static void mandar5(GtkWidget *widget, gpointer data) {
  mandar = 5;
  reporteUno(NULL,NULL);
}

static void mandar6(GtkWidget *widget, gpointer data) {
  mandar = 6;
  reporteUno(NULL,NULL);
}

static void mandar7(GtkWidget *widget, gpointer data) {
  mandar = 7;
  reporteUno(NULL,NULL);
}

static void mandar8(GtkWidget *widget, gpointer data) {
  mandar = 8;
  reporteUno(NULL,NULL);
}

/*
  Function that displays the report export window, receives data of type gpointer and Gtkwidget and returns nothing.
*/
static void reporte(GtkWidget *widget, gpointer data) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Reporte");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  grid = gtk_grid_new ();

  gtk_container_add (GTK_CONTAINER (window), grid);

  GtkWidget *confirmacionID;
  confirmacionID = gtk_label_new ("Reporte");
  gtk_grid_attach (GTK_GRID (grid), confirmacionID, 0, 0, 8, 1);

  button = gtk_button_new_with_label ("ID ascendente");
  g_signal_connect (button, "clicked", G_CALLBACK (mandar1), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  button = gtk_button_new_with_label ("ID descendente");
  g_signal_connect (button, "clicked", G_CALLBACK (mandar2), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 2, 1);

  button = gtk_button_new_with_label ("Producto ascendente");
  g_signal_connect (button, "clicked", G_CALLBACK (mandar3), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 2, 1, 2, 1);

  button = gtk_button_new_with_label ("Producto descendente");
  g_signal_connect (button, "clicked", G_CALLBACK (mandar4), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 2, 2, 2, 1);

  button = gtk_button_new_with_label ("Cantidad ascendente");
  g_signal_connect (button, "clicked", G_CALLBACK (mandar5), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 4, 1, 2, 1);

  button = gtk_button_new_with_label ("Cantidad descendente");
  g_signal_connect (button, "clicked", G_CALLBACK (mandar6), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 4, 2, 2, 1);

  button = gtk_button_new_with_label ("Precio venta ascendente");
  g_signal_connect (button, "clicked", G_CALLBACK (mandar7), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 6, 1, 2, 1);

  button = gtk_button_new_with_label ("Precio venta descendente");
  g_signal_connect (button, "clicked", G_CALLBACK (mandar8), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 6, 2, 2, 1);

  gtk_widget_show_all (window);
}

/*
  Function that enables the application and creates the main window, receives data of type gpointer and Gtkapplication and returns nothing.
*/
static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Ahuehuete v0.1 alpha: Tienda SAIMT");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("Agregar producto");
  g_signal_connect (button, "clicked", G_CALLBACK (agregar_producto), NULL);

  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("Borrar producto");
  g_signal_connect (button, "clicked", G_CALLBACK (borrar_producto), NULL);

  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

  button = gtk_button_new_with_label ("Editar producto");
  g_signal_connect (button, "clicked", G_CALLBACK (editar_producto), NULL);

  /* Place the second button in the grid cell (2, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);

  button = gtk_button_new_with_label ("Recuperar producto borrado");
  g_signal_connect (button, "clicked", G_CALLBACK (reactivar_producto), NULL);

  /* Place the second button in the grid cell (3, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 1, 1);

  button = gtk_button_new_with_label ("Reporte");
  g_signal_connect (button, "clicked", G_CALLBACK (reporte), NULL);

  /* Place the first button in the grid cell (0, 1), and make it fill
   * just 1 cells horizontally and 1 vertically
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);

  button = gtk_button_new_with_label ("Buscar");
  g_signal_connect (button, "clicked", G_CALLBACK (buscar_producto), NULL);

  /* Place the first button in the grid cell (1, 1), and make it fill
   * just 1 cells horizontally and 1 vertically
   */
  gtk_grid_attach (GTK_GRID (grid), button, 1, 1, 1, 1);

  button = gtk_button_new_with_label ("Herramientas administrativas");
  g_signal_connect (button, "clicked", G_CALLBACK (administrativas), NULL);

  /* Place the second button in the grid cell (2, 1), and make it fill
   * just 2 cells horizontally and 1 vertically
   */
  gtk_grid_attach (GTK_GRID (grid), button, 2, 1, 2, 1);

  button = gtk_button_new_with_label ("Salir");
  gchar **entries = (gchar**) malloc(sizeof(gchar*));
  *entries = (gchar*)malloc(sizeof(gchar)*1024);
  *entries="data";
  g_signal_connect (button, "clicked", G_CALLBACK (guardarFinal), entries);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  /* Place the Quit button in the grid cell (0, 2), and make it
   * span 4 columns.
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 4, 1);


  /* Now that we are done packing our widgets, we show them all
   * in one go, by calling gtk_widget_show_all() on the window.
   * This call recursively calls gtk_widget_show() on all widgets
   * that are contained in the window, directly or indirectly.
   */
  gtk_widget_show_all (window);
  
  gchar **entries2 = (gchar**) malloc(sizeof(gchar*));
  *entries2 = (gchar*)malloc(sizeof(gchar)*1024);
  *entries2="data.adob";
  procInicio(entries2);

}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.adf.tiendaSAIMT", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}