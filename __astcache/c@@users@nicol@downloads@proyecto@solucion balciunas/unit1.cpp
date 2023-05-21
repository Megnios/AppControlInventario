// Hecho por Nicolás Balciunas

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVentanaPrincipal *VentanaPrincipal;
//---------------------------------------------------------------------------
__fastcall TVentanaPrincipal::TVentanaPrincipal(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*
  @descripcion: Le pide un nombre de un material al usuario.

  @parametros: nombreMaterial: Objeto donde se guarda el nombre provisto por el usuario.

  @details: Devuelve un valor booleano que depende de si el usuario envió el nombre o canceló antes.


  @ejemplos de uso:

	String* nombre;
	bool resultadoEnviado = PedirNombreMaterial(nombre);

	nombre contendrá lo que el usuario haya escrito.
	resultadoEnviado será True si el usuario clickeó en "Aceptar" en la ventana emergente.
	o será False si clickeó en "Cancelar"


  Pre: nombreMaterial es un puntero válido.

  Post: Se le asigna el contenido ingresado por el usuario a nombreMaterial.

		Devuelve False si el usuario canceló la ventana. True si no la canceló.
*/
bool TVentanaPrincipal::PedirNombreMaterial(String *nombreMaterial)
{

	return (InputQuery("Agregar Material", "Ingrese el nombre del material",
													*nombreMaterial));

}


//---------------------------------------------------------------------------


void __fastcall TVentanaPrincipal::AgregarMaterialClick(TObject *Sender)
{
    String nombreMaterial;

	if (TreeSolucion->Selected == nullptr) {
		ShowMessage("Tenes que seleccionar la categoria de este material antes");
	}

	else if (PedirNombreMaterial(&nombreMaterial) && nombreMaterial.Length() > 0) {

		TTreeNode* ultimoNodo = TreeSolucion->Items->AddChild(TreeSolucion->Selected,
															  nombreMaterial);
        ultimoNodo->ImageIndex = 1;
        ultimoNodo->SelectedIndex = 1;
	}
}


//---------------------------------------------------------------------------


/*
  @descripcion: Determina si una cadena contiene un caracter numerico.

  @parametros: cadena: La cadena a analizar.

  @details: Los caracteres numericos pueden ser cualquier dígito del 0 al 9.

  @ejemplos de uso:

	String cadena = "A123";
	bool esNumerica = EsCadenaNumerica(cadena);

	esNumerica será True porque cadena contiene por lo menos un número.


  Pre: -

  Post: Devuelve True si la cadena de entrada contiene algún numero.
		False en cualquier otro caso.

*/


bool TVentanaPrincipal::EsCadenaNumerica(String cadena)
{

    bool esNumerica = false;
	int i = 1;

	while(!esNumerica && i <= cadena.Length()) {

		if (isdigit(cadena[i])) {
			esNumerica = true;
        }
		i++;

	}

	return esNumerica;

}


//---------------------------------------------------------------------------
/*
  @descripcion: Le pide un nombre de una categoria al usuario hasta que este
				cierre la ventana o el texto ingresado sea totalmente alfabético.

  @parametros: nombreCategoria: Objeto donde se guarda el nombre provisto por el usuario.

  @details: Devuelve un valor booleano que depende de si el usuario envió el nombre o canceló antes.

  @ejemplos de uso:

	String* nombre;
	bool resultadoEnviado = PedirNombreCategoria(nombre);

	nombre contendrá lo que el usuario haya escrito.
	resultadoEnviado será True si el usuario clickeó en "Aceptar" en la ventana emergente.
	o será False si clickeó en "Cancelar"


Pre: nombreCategoria es un puntero válido.

Post: Se le asigna el contenido ingresado por el usuario a nombreCategoria.

	  Devuelve False si el usuario canceló la ventana. True si no la canceló.
*/


bool TVentanaPrincipal::PedirNombreCategoria(String *nombreCategoria)
{
	bool ingresoNombre = InputQuery("Agregar Categoria",
									"Ingrese el nombre de la categoria",
									 *nombreCategoria);

	while(EsCadenaNumerica(*nombreCategoria) && ingresoNombre) {

		ShowMessage("El nombre de la categoria no puede contener numeros");
		ingresoNombre = InputQuery("Agregar Categoria",
									"Ingrese el nombre de la categoria",
									 *nombreCategoria);
	}

    return ingresoNombre;
}


//---------------------------------------------------------------------------


void __fastcall TVentanaPrincipal::AgregarCategoriaClick(TObject *Sender)
{
	String nombreCategoria;

	if (PedirNombreCategoria(&nombreCategoria) && nombreCategoria.Length() > 0) {

		TTreeNode* ultimoNodo = TreeSolucion->Items->Add(NULL, nombreCategoria);
		ultimoNodo->StateIndex = 0;

		TreeSolucion->CustomSort(NULL, 0);
	}

}
//---------------------------------------------------------------------------


void __fastcall TVentanaPrincipal::LimpiarClick(TObject *Sender)
{
	if (MessageDlg("¿Estás seguro de borrar toda la informacion?",mtConfirmation,
					TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
	{
        TreeSolucion->Items->Clear();
	}

	else {

		ShowMessage("No se eliminará nada de información");
	}

}
//---------------------------------------------------------------------------

/*
  @descripcion: Redimensiona todas las imagenes de ListaImagenes al tamaño indicado por el usuario.

  @parametros: anchoImagen: El ancho que tendrán las imagenes redimensionadas.

			   altoImagen: El alto que tendrán las imagenes redimensionadas.


  @details: Modifica el objeto original donde se guardan las imágenes.

  @ejemplos de uso:

	RedimensionarImagenes(100, 100);

	Las imagenes de ListaImagenes van a tener ahora un tamaño de 100x100.


  Pre: anchoImagen y altoImagen deben ser positivos.

  Post: Redimensiona las imagenes de ListaImagenes.

*/

void TVentanaPrincipal::RedimensionarImagenes(int anchoImagen, int altoImagen)
{
	TImageList* imagenesTemporales = new TImageList(NULL);
	imagenesTemporales->Width = anchoImagen;
	imagenesTemporales->Height = altoImagen;

	for (int i = 0; i < ListaImagenes->Count; i++) {

		TBitmap* imagenOriginal = new TBitmap();
		ListaImagenes->GetBitmap(i, imagenOriginal);

        TBitmap* imagenRedimensionada = new TBitmap();
		imagenRedimensionada->SetSize(anchoImagen, altoImagen);
		imagenRedimensionada->Canvas->StretchDraw(TRect(0, 0, anchoImagen, altoImagen), imagenOriginal);

		imagenesTemporales->Add(imagenRedimensionada, nullptr);

        delete imagenOriginal;
		delete imagenRedimensionada;
	}

	ListaImagenes->Assign(imagenesTemporales);

	if (imagenesTemporales != nullptr) {
		delete imagenesTemporales;
    }
}

//---------------------------------------------------------------------------

/*
  @descripcion: Redimensiona el tamaño del boton indicado.

  @parametros: boton: El objeto que representa al boton a redimensionar.

			   ancho: El ancho que que tendrá el botón

			   alto: El alto que tendrá el botón.

			   distanciaIzq: La distancia que habrá entre el borde de la ventana
							 y el lado oriental del botón.

			   distanciaTop: La distancia que habrá entre la parte superior de la ventana
							 y la parte superior del botón.

			   tamanioFuente: El tamaño que tendrá el texto del botón.


  @details: Se puede superponer fácilmente con otros elementos si no se tiene
			en consideración el tamaño.

  @ejemplos de uso:

	TButton* boton;

	RedimensionarBoton(boton, 100, 50, 250, 500, 15);


	boton tendrá un ancho de 100 px, un alto de 50 px, estará a 250 px del lado izquierdo de la ventana,
	estará a 500 px de la parte superior de la ventana y la fuente de su texto sera de 15 pt.


  Pre: boton es un puntero válido.

  Post: Redimensiona boton de la manera indicada.

*/

void TVentanaPrincipal::RedimensionarBoton(TButton* boton, int ancho, int alto, int distanciaIzq, int distanciaTop, int tamanioFuente)
{
	boton->Width = ancho;
	boton->Height = alto;
	boton->Left = distanciaIzq;
	boton->Top = distanciaTop;
	boton->Font->Size = tamanioFuente;

}

//---------------------------------------------------------------------------

//Este metodo se encarga de que los elementos se ajusten al tamaño de la ventana.


void __fastcall TVentanaPrincipal::FormResize(TObject *Sender)
{

	int alturaBoton = ClientHeight / 12;
	int anchoBoton = ClientWidth / 3;

	RedimensionarBoton(AgregarCategoria, anchoBoton, alturaBoton, anchoBoton / 13,
					  ClientHeight - (alturaBoton * 3 / 2),
					  (alturaBoton + anchoBoton) / 25);

	RedimensionarBoton(AgregarMaterial, anchoBoton, alturaBoton,
					  ClientWidth / 2 - anchoBoton / 4,
					  ClientHeight - (alturaBoton * 3 / 2),
					  (alturaBoton + anchoBoton) / 25);

    RedimensionarBoton(Limpiar, anchoBoton / 2, alturaBoton,
					  ClientWidth - (anchoBoton / 2) * 9 / 8,
					  ClientHeight - (alturaBoton * 3 / 2),
					  (alturaBoton + anchoBoton) / 25);

    PanelBotones->Height = alturaBoton * 2;

	TreeSolucion->Font->Size = (alturaBoton + anchoBoton) / 25;

	RedimensionarImagenes(ClientWidth / 45, ClientHeight / 35);


}
//---------------------------------------------------------------------------

