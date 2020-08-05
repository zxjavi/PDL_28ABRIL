%{
#define IF     1
#define BOOLEAN     2
#define BREAK     3
#define CASE     4
#define STRING     5
#define DEFAULT     6
#define DO     7
#define ELSE     8
#define FALSEE     9
#define FOR     10
#define FUNCTION     11
#define INT     12
#define NULLL     13
#define INPUT     14
#define RETURN     15
#define SWITCH     16
#define TRUEE     17
#define VAR     18
#define WHILE     19
#define PRINT     20
#define CADENA     21
#define PARENTESIS 22
#define OpAritmetico 23
#define OpRelacion 24
#define OpLogico 25
#define OpAsignacion 26
#define OpAutoIncrementoDecremento 27
#define Llave 28
#define IDENTIFICADOR 29
#define PUNTOCOMA 30
#define COMA 31
#define DOSPUNTOS 32
#define MENOS 33



//por ejemplo
#define TIPOBOOLEAN -1
#define TIPOSTRING -2
#define TIPOENTERO -3
#define TIPOVACIO -4
#define TIPOFUNCION -5
#define TIPOVOID -6



#define CONSTENTERA 100


#define ERR "./Error"
#define FICHERO "./tablaSimbolos"
#define PARSE "./parse"

#include "ts2006.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "./Estructura.c"
struct Tokens {
   char* lexema;
   char* lexemaSintactico;
   int  tipo;
   char*  valor;
   int   valor2;
   int lineaDondeEsta;
  
} Token; 
#define SEMANTICO
#include "funciones_ayuda.h"

%}
OpAritmetico "+"|"-"|"*"|"/"|"%"
OpRelacion "=="|"!="|"<="|">="|"<"|">"
OpLogico "&&"|"!"|"\|\|"
OpAsignacion "="|"+="|"-="|"*="|"/="|"%="|"&="|"\|="
OpAutoIncrementoDecremento "++"|"--"
Interrogacion "\¿"|"\?"
digito        [0-9]  
num           {digito}+    
letra         [A-Za-z]  
ident         {letra}({letra}|{digito}|_)*
Parentesis   "\("|"\)"
Llave "{"|"}"
DosPuntos ":"
Coma ","
PuntoCOma ";"
menos "-"
CadenaDeCaracteres ([\'](?:\.|(\\\')|[^\''\n])*[\']|[\"](?:\.|(\\\")|[^\""\n])*[\"])

ComentariosDeLinea (\/\*[\s\S]*?\*\/|\/\/.*|(\t)+)
ComentariosTocho [/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]    
  
%%
<<EOF>> {printf("Reconocio EOf: %s\n",yytext); return 101; }
{menos}  {printf("Menos\n%s\n",yytext) ; return MENOS;}
{OpAritmetico} {printf("OpAritmetico: %s\n",yytext); return OpAritmetico; }
{OpRelacion} {printf("OpRelacion: %s\n",yytext); return OpRelacion; }
{OpLogico} {printf("OpLogico: %s\n",yytext); return OpLogico; }
{OpAsignacion} {printf("OpAsignacion: %s\n",yytext); return OpAsignacion; }
{OpAutoIncrementoDecremento} {printf("OpAutoIncrementoDecremento: %s\n",yytext); return OpAutoIncrementoDecremento;}
{Interrogacion} {printf("Interrogacion: %s\n",yytext); }
{Parentesis} { printf("Parentesis: %s\n",yytext);    return PARENTESIS;}
{Llave} {printf("Llave\n%s\n",yytext); return Llave; }
{DosPuntos} {printf("DosPuntos: %s\n",yytext) ; return DOSPUNTOS;}
{Coma} {printf("Coma\n%s\n",yytext) ; return COMA;}
{PuntoCOma} {printf("PuntoComa: %s\n",yytext); return PUNTOCOMA;}
{num} {if(atoi(yytext)<=32767)
                        { printf("Entero con valor: %s\n",yytext); return CONSTENTERA;}
       else; }

{CadenaDeCaracteres} {printf("CadenaDeCaracteres: %s\n",yytext) ; return CADENA;}
{ComentariosDeLinea} {printf("lo caza: %s\n",yytext) ;}
{ComentariosTocho} {printf("escribeeeeeeeeee: %s\n",yytext) ;}
if  {printf("Reconocio: %s\n",yytext) ; return     IF;}
boolean {printf("Reconocio: %s\n",yytext); return BOOLEAN;}
break {printf("Reconocio: %s\n",yytext); return BREAK;}
case {printf("Reconocio: %s\n",yytext); return CASE;}
string {printf("Reconocio: %s\n",yytext); return STRING;}
default {printf("Reconocio: %s\n",yytext);return DEFAULT;}
do {printf("Reconocio: %s\n",yytext);return DO;}
else {printf("Reconocio: %s\n",yytext);return ELSE;}
false {printf("Reconocio: %s\n",yytext);return FALSEE;}
for {printf("Reconocio: %s\n",yytext);return FOR;}
function {printf("Reconocio: %s\n",yytext);return FUNCTION;}
int {printf("Reconocio: %s\n",yytext);return INT;}
null {printf("Reconocio: %s\n",yytext);return NULLL;}
input {printf("Reconocio: %s\n",yytext);return INPUT;}
return {printf("Reconocio: %s\n",yytext);return RETURN;}
switch {printf("Reconocio: %s\n",yytext);return SWITCH;}
true {printf("Reconocio: %s\n",yytext);return TRUEE;}
var {printf("Reconocio: %s\n",yytext);return VAR;}
while {printf("Reconocio: %s\n",yytext);return WHILE;}
print {printf("Reconocio: %s\n",yytext);return PRINT;}
\n { yylineno++; }
{ident} {printf("Idenetificador con nombre :%s\n",yytext); return IDENTIFICADOR;}
%%
char* siguienteToken;
int indiceReglas=0;
int tablaGlobal;
int tablaLocal;
int tablaActual;
int tablas[100];
int indiceTablas=0;
int desplgeneral=0;
int desplfuncion=0;
int flagDeclaracionUso;
int indiceSintactico = 0;
int reglas[1000];
struct Tokens s1[1000];
struct Tokens sgtetoken;
int dentroFuncion=0;
int dentroDeReturn=0;
char  ultimoLexema[20];
int tipoRetornoActual;
int elTipoElegido;


char listIdentificadores[100][20] ;
int IndiceListaIdentificadores=0;
int indiceLista2=0;


const char* var1="var";
const char* if1="if";
const char* while1="while";
const char* identificador1="identificador";
const char* return1="return";
const char* print1="print";
const char* input1="input";
const char* masmas="++";
const char* menosmenos="--";
const char* parentesisA="(";
const char* exclamacion="!";
const char* doo="do";
const char* puntocoma1=";";
const char* function1="function";
const char* Eof1="Eof";//implementar

const char* intt ="int";
const char* cadena ="cadena";
const char* enteroo ="entero";
const char* truee ="true";
const char* falsee ="false";
const char* boolean1="boolean";
const char* strings="string";
const char* yy="&&";
const char* oo="||";
const char* mas="+";
const char* menos="-";
const char* por="*";
const char* division="/";
const char* iguall="=";
const char* comaa=",";
const char* parentesisC=")";
const char* igualigual="==";


static char* amain[11];
static char* bmain[11];
static char* cmain[11];
static char* dmain[11];
static char* emain[11];
static char* fmain[11];
static char* gmain[11];
static char* hmain[11];
static char* imain[11];
static char* jmain[11];
static char* kmain[11];
static char* lmain[11];
static char* nmain[11];
static char* zmain[11];
/*static char* amain[5];
static char* bmain[11];
static char* cmain[3];
static char* dmain[7];
static char* emain[7];
static char* fmain[3];
static char* gmain[3];
static char* hmain[7];
static char* imain[6];
static char* jmain[7];
static char* kmain[4];
static char* lmain[5];
static char* nmain[6];*/
/*
    char *b[9];
    b[0]=var1;
    b[1]=if1;
    b[2]=while1;
    b[3]=if1;
    b[4]=identificador1;
    b[5]=return1;*/

int comparar();
int errorSintactico();
void equiparar();
void aadirRegla();
void buscarSiguietneToken();
/*void P();
void B();
void Bp();
void Bpp();
void T();
void S();
void Sp();
void S2();
void S3();
void S4();
void X();
void C();
void F();
void H();
void A();
void K();
void L();
void Q();
void E();
void Ep();
void Epp();
void R();
void Rp();
void U();
void Up();
void Upp();
void V();
void Vp();*/

int axioma();
int A(Typito * A_devuelvo);
int SIMPLE();
int TIPO();
int W();
int A2();
int B();
int J();
int K();
int V();
int H();
int X();
int Z();
int R();
int R1();
int E();
int S();
int T();
int O1();
int O2();
int O3();
int G();

int comparar(char * a, char * b[], int t) {
  int sol = 1;

  for (int i = 0; i < t; i++) {

    if (strcmp(a, b[i]) == 0) {
      sol = 0;
      //printf("COMPARA CON UN FIRST (%s,%s)\n",a,b[i]);
      break;
    }
  }
  return sol;
}

int errorSintactico() {
    
  printf("errorSintactico(): nos hemos encontrado con siguienteToken: %s, en la linea %i\n", siguienteToken,sgtetoken.lineaDondeEsta);
  exit(1);
}

void aadirRegla(int a) {
  reglas[indiceReglas] = a;
  indiceReglas++;
}

void equiparar(char * token) {
  if (strcmp(siguienteToken, token) != 0) {
    printf("MALLLL EKIPARADOOOOOOOOOOOOOOOOOOOOOOO (%s,%s) \n",siguienteToken,token);
    errorSintactico();

  }

  if (strcmp(siguienteToken, "Eof") != 0) {
    
    printf("BIEN EQUIPARADO (%s,%s)\n",siguienteToken,"Eof");
    buscarSiguietneToken();

  } else siguienteToken = "Eof";

}

void buscarSiguietneToken() {
  printf("Ejecuta Buscar Siguiente Token :\n");
  char prueba[100];
  int tipoLexico = sgtetoken.tipo;
  int lineaToken = sgtetoken.lineaDondeEsta;

  switch (tipoLexico) {
  case VAR:

    siguienteToken = "var";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;

  case DOSPUNTOS:

    siguienteToken = ";";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case COMA:

    siguienteToken = ",";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case MENOS:

    siguienteToken = "-";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case PUNTOCOMA:

    siguienteToken = ";";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case IDENTIFICADOR:

    siguienteToken = "identificador";
    strcpy(ultimoLexema, "");
    //ultimoLexema=s1[indiceSintactico].lexemaSintactico; //s1[i].lexemaSintactico
    //ultimoLexema=listIdentificadores[indiceLista2];	

    strcpy(ultimoLexema, listIdentificadores[indiceLista2]);
    printf("Identificador con lexema: %s\n", ultimoLexema);
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);

    indiceLista2++;
    break;
  case PARENTESIS:
    if (sgtetoken.valor2 == 1) {
      siguienteToken = "(";
      printf("\tque es: %s\n", siguienteToken);
      printf("\tlinea: %d\n", lineaToken);
      break;
    } else {
      siguienteToken = ")";
      printf("\tque es: %s\n", siguienteToken);
      printf("\tlinea: %d\n", lineaToken);
      break;
    }

  case OpAritmetico:

    if (sgtetoken.valor2 == 1) {
      siguienteToken = "+";
    }
    if (sgtetoken.valor2 == 2) {
      siguienteToken = "-";
    }
    if (sgtetoken.valor2 == 3) {
      siguienteToken = "*";
    }
    if (sgtetoken.valor2 == 4) {
      siguienteToken = "/";
    }
    if (sgtetoken.valor2 == 5) {
      siguienteToken = "%";
    }
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case OpRelacion:
    if (sgtetoken.valor2 == 1) {
      siguienteToken = "==";
    }
    if (sgtetoken.valor2 == 2) {
      siguienteToken = "!=";
    }
    if (sgtetoken.valor2 == 3) {
      siguienteToken = "<=";
    }
    if (sgtetoken.valor2 == 4) {
      siguienteToken = ">=";
    }
    if (sgtetoken.valor2 == 5) {
      siguienteToken = "<";
    }
    if (sgtetoken.valor2 == 6) {
      siguienteToken = ">";
    }
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case OpLogico:
    if (sgtetoken.valor2 == 1) {
      siguienteToken = "&&";
    }
    if (sgtetoken.valor2 == 2) {
      siguienteToken = "!";
    }
    if (sgtetoken.valor2 == 3) {
      siguienteToken = "||";
    }
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case OpAsignacion:
    if (sgtetoken.valor2 == 1) {
      siguienteToken = "=";
    }
    if (sgtetoken.valor2 == 2) {
      siguienteToken = "+=";
    }
    if (sgtetoken.valor2 == 3) {
      siguienteToken = "-=";
    }
    if (sgtetoken.valor2 == 4) {
      siguienteToken = "*=";
    }
    if (sgtetoken.valor2 == 5) {
      siguienteToken = "/=";
    }
    if (sgtetoken.valor2 == 6) {
      siguienteToken = "%=";
    }
    if (sgtetoken.valor2 == 7) {
      siguienteToken = "&=";
    }
    if (sgtetoken.valor2 == 8) {
      siguienteToken = "|=";
    }

    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);

    break;
  case OpAutoIncrementoDecremento:
    if (sgtetoken.valor2 == 1) {
      siguienteToken = "++";
    }
    if (sgtetoken.valor2 == 2) {
      siguienteToken = "--";
    }
    printf("\tlinea: %d\n", lineaToken);
    break;
  case Llave:
    if (sgtetoken.valor2 == 1) {
      siguienteToken = "{";
    }
    if (sgtetoken.valor2 == 2) {
      siguienteToken = "}";
    }
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;

  case IF:
    siguienteToken = "if";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;

  case BOOLEAN:
    siguienteToken = "boolean";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case BREAK:
    siguienteToken = "break";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case CASE:
    siguienteToken = "case";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case STRING:
    siguienteToken = "string";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case DEFAULT:
    siguienteToken = "default";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case DO:
    siguienteToken = "do";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case ELSE:
    siguienteToken = "else";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case FALSEE:
    siguienteToken = "false";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case FOR:
    siguienteToken = "for";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case FUNCTION:
    siguienteToken = "function";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;

  case INT:
    siguienteToken = "int";
    printf("\tlinea: %d\n", lineaToken);
    break;
  case NULLL:
    siguienteToken = "null";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case INPUT:
    siguienteToken = "input";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case RETURN:
    siguienteToken = "return";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case SWITCH:
    siguienteToken = "switch";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case TRUEE:
    siguienteToken = "true";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;

  case WHILE:
    siguienteToken = "while";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case PRINT:
    siguienteToken = "print";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;

  case CADENA:
    siguienteToken = "cadena";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case CONSTENTERA:
    siguienteToken = "entero";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  case 101:
    siguienteToken = "Eof";
    printf("\tque es: %s\n", siguienteToken);
    printf("\tlinea: %d\n", lineaToken);
    break;
  }

  //strcmp(siguienteToken,sgtetoken.lexemaSintactico);
  printf("\n me he cargado : %s  ` \n", siguienteToken);
  sgtetoken = s1[++indiceSintactico];
}


/*

















*/
/*
Axioma ->  { CrearTablGeneral , DentroFuncion = false dezp =0 ,     crearEstructuraDeTabasFunciones }     A { Imprimir y DestruirTGyTF }
*/

int axioma() {
  int resultadoOp;
  FILE * ficherito;

  tablaGlobal = crear_tabla();
  tablas[0] = tablaGlobal;
  indiceTablas++;
  tablaActual = tablaGlobal;
  Typito * A_nt = (Typito * ) malloc(sizeof(Typito));
  if (A(A_nt) == ERROR_SSS) {
    return ERROR_SSS;
  }
  if ( dameTipo(A_nt) != TIPO_OK) {
    return ERROR_SSS;
  }
printf("TERMINA SINTACTICO-SEMANTICO SATISFACTORIAMENTE, IMPRIME TOKENS Y TABLAS\n");
  /* para resetear lo que esta escrito*/
  ficherito = fopen(FICHERO, "w");
  // fprintf(ficherito, "Primera Tabla Que Se muestra es la tabla Global, las demas son de funciones: \n");
  fclose(ficherito);

  for (int i = 0; i < indiceTablas; i++) {

    resultadoOp = escribir_tabla(tablas[i], FICHERO);

    if (resultadoOp < 0) {
      printf("Error: %s\n", consultar_descripcion_ultimo_error());
    } else {
      printf("Se ha escrito bien");
    }

  }

  for (int i = 0; i < indiceTablas; i++) {
    destruir_tabla(tablas[i]);
  }
printf("\nDESTRUYE TABLAS\n");

}



int errorSemantico(){
printf("errorSemantico\n");
return 0;
}


#define SINTACTICOSEMANTICO
#include "funciones_Typito.h"

int analizadorSintactico()
{
printf("analisisSintacticoEjecutando\n");
buscarSiguietneToken();
if(axioma()==ERROR_SSS)
    exit(1);
return 0;
}
int yywrap() { 

 
 return 1;

}




void main(int argc, char *argv[])
{

	//inicializacion de los terminales para el sintactico para que se almacene en el stack y no en el heap;
	//para P amain:
	//SIMPLE
	amain[0] = (char *)input1;
	amain[1] = (char *)masmas;
	amain[2] = (char *)print1;
	amain[3] = (char *)return1;
	amain[4] = (char *)puntocoma1;
	amain[5] = (char *)identificador1;

	//Para B bmain:
	//first A
	bmain[0] = (char *)input1;
	bmain[1] = (char *)masmas;
	bmain[2] = (char *)print1;
	bmain[3] = (char *)return1;
	bmain[4] = (char *)puntocoma1;
	bmain[5] = (char *)var1;
	bmain[6] = (char *)if1;
	bmain[7] = (char *)identificador1;
	bmain[8] = (char *)doo;
	bmain[9] = (char *)function1;
	bmain[10] = (char *)Eof1;

	//Para Bp cmain:
	cmain[0] = (char *)intt;
	cmain[1] = (char *)strings;
	cmain[2] = (char *)boolean1;

	//Para X dmain:
	dmain[0] = (char *)parentesisA;
	dmain[1] = (char *)exclamacion;
	dmain[2] = (char *)identificador1;
	dmain[3] = (char *)enteroo;
	dmain[4] = (char *)cadena;
	dmain[5] = (char *)truee;
	dmain[6] = (char *)falsee;

	// Para C emain:
	emain[0] = (char *)var1;
	emain[1] = (char *)if1;
	emain[2] = (char *)doo;
	emain[3] = (char *)print1;
	emain[4] = (char *)identificador1;
	emain[5] = (char *)return1;
	emain[6] = (char *)input1;

	//Para H fmain:
	fmain[0] = (char *)intt;
	fmain[1] = (char *)boolean1;
	fmain[2] = (char *)strings;
	//Para A gmain:
	gmain[0] = (char *)doo;
	gmain[1] = (char *)Eof1;
	gmain[2] = (char *)function1;
	gmain[3] = (char *)identificador1;
	gmain[4] = (char *)return1;
	gmain[5] = (char *)input1;
	gmain[6] = (char *)var1;
	gmain[7] = (char *)if1;
	gmain[8] = (char *)masmas;
	gmain[9] = (char *)puntocoma1;
	gmain[10] = (char *)print1;

	//Para L hmain:
	hmain[0] = (char *)parentesisA;
	hmain[1] = (char *)exclamacion;
	hmain[2] = (char *)identificador1;
	hmain[3] = (char *)enteroo;
	hmain[4] = (char *)cadena;
	hmain[5] = (char *)truee;
	hmain[6] = (char *)falsee;

	//Para E imain:
	imain[0] = (char *)identificador1;
	imain[1] = (char *)enteroo;
	imain[2] = (char *)cadena;
	imain[3] = (char *)parentesisA;
	imain[4] = (char *)truee;
	imain[5] = (char *)falsee;

	//Para Epp jmain:
	jmain[0] = (char *)truee;
	jmain[1] = (char *)falsee;
	jmain[2] = (char *)cadena;
	jmain[3] = (char *)identificador1;
	jmain[4] = (char *)parentesisA;
	jmain[5] = (char *)menos;
	jmain[6] = (char *)enteroo;

	//Para R kmain:
	kmain[0] = (char *)puntocoma1;
	kmain[1] = (char *)parentesisC;
	kmain[2] = (char *)comaa;

	//Para U lmain:
	lmain[0] = (char *)puntocoma1;
	lmain[1] = (char *)yy;
	lmain[2] = (char *)parentesisC;
	lmain[3] = (char *)comaa;

	//Para Upp nmain:
	nmain[0] = (char *)puntocoma1;
	nmain[1] = (char *)yy;
	nmain[2] = (char *)parentesisC;
	nmain[3] = (char *)comaa;
	nmain[4] = (char *)igualigual;

	//
	zmain[0] = (char *)mas;	//bien
	zmain[1] = (char *)comaa;
	zmain[2] = (char *)yy;
	zmain[3] = (char *)puntocoma1;	//bien
	zmain[4] = (char *)igualigual;
	zmain[5] = (char *)parentesisC;	//bien

	/*const char* var1="var";
	const char* if1="if";
	const char* while1="while";
	const char* identificador1="identificador";
	const char* return1="return";
	const char* print1="print";
	const char* input1="input";
	const char* masmas="++";
	const char* menosmenos="--";
	const char* parentesisA="(";
	const char* exclamacion="!";

	const char* intt ="int";
	const char* cadena ="cadena";
	const char* truee ="true";
	const char* falsee ="false";
	const char* booleaneaneanl="booleaneanean";
	const char* strings="string";
	const char* yy="&&";
	const char* oo="||";
	const char* mas="+";
	const char* menos="-";
	const char* por="*";
	const char* division="/";
	const char* modulo="%";

	*/

	FILE * fichero;
	fichero = fopen("./token.txt", "w");
	
    FILE * ficheroDraco;
	ficheroDraco = fopen("./tokendraco.txt", "w");

	FILE * parse;
	parse = fopen("./parse.txt", "w");

    int fd=0;
	//fd=open("./token.txt",777);
	int ret;
	//variable que me guarda el numero de linea del error
	int error = yylineno;
	//creamos la tabla de simbolos

	//necesitamos crear unas variables globales para gestionar las tablas de simbolo

	int contador = 0;

//////////////////////////////////////////////////
        if(argc != 2)
        {
                fprintf(stderr,"Uso: ./aplicacion nombre_archivo\n");
                exit(1);
        }

        yyin = fopen(argv[1],"r");
        if(yyin == NULL)
        {
                fprintf(stderr,"No se puede abrir el archivo: %s\n",argv[1]);
                exit(0);
        }

        
///////////////////////////////////////////////////////////////
	while ((ret = yylex()) != 0)
	{

		switch (ret)
		{

			case DOSPUNTOS:
				s1[contador].tipo = DOSPUNTOS;
				s1[contador].lexema = "dosPuntos";
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lineaDondeEsta = yylineno;
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case MENOS:

				s1[contador].tipo = MENOS;
				s1[contador].lexema = "-";
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lineaDondeEsta = yylineno;
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case COMA:
				s1[contador].tipo = COMA;
				s1[contador].lexema = "Coma";
				s1[contador].lineaDondeEsta = yylineno;
				s1[contador].lexemaSintactico = yytext;
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case PUNTOCOMA:
				s1[contador].tipo = PUNTOCOMA;
				s1[contador].lexema = "PuntoComa";
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lineaDondeEsta = yylineno;
				printf("%s111111\n", s1[contador].lexemaSintactico);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case 101:
				s1[contador].tipo = 101;
				s1[contador].lexemaSintactico = "Eof";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%s11\n", s1[contador].lexemaSintactico);

				fprintf(fichero, "<eof,->\n");
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				printf("salidellexico\n");
				sgtetoken = s1[0];

				printf("********antes de ejecutar el sintactico******\n");
				for (int i = 0; i < IndiceListaIdentificadores; i++)
				{
					printf("%s\n", listIdentificadores[i]);
				}
				analizadorSintactico();
				printf("Descendente Recursivo\n");
               // printf("¡¡¡¡HA TERMINADO TODO!!!!, SALVO EL PARSE: Ahora comenzaria a escribir el parse... pero da error...\n");
/////////////////////////////////////////////////////////////////////////////////////SE DETIENE AQUI
               
               fprintf(parse,"DescendenteRecursivo\n");
                printf("\nSE HA ESCRITO EN PARSE la frase \"Descendente Recursivo\"\n");
				for (int i = 0; i < indiceReglas; i++)
				{
					fprintf(parse, "%i ", reglas[i]);
				}
                printf("\nSE HA ESCRITO EL PARSE\n");
				//analizadorSemantico();

				exit(0);

			case IDENTIFICADOR:

				

				s1[contador].tipo = IDENTIFICADOR;

				//valor2 nos da la posicion de la tabla
				// s1[contador].valor2=buscar_posicion_entrada(tabla,yytext);
				//
				//char[100][20] listIdentificadores;
				// int IndiceListaIdentificadores;

				strcpy(listIdentificadores[IndiceListaIdentificadores], yytext);

				s1[contador].lexema = "identificador";
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lineaDondeEsta = yylineno;
			
				printf("%d+\n", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,%d>\n", s1[contador].lexema, s1[contador].valor2);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				IndiceListaIdentificadores++;
				break;

			case PARENTESIS:
				s1[contador].tipo = PARENTESIS;
				s1[contador].lineaDondeEsta = yylineno;
				s1[contador].lexema = "PARENTESIS";
				s1[contador].lexemaSintactico = yytext;
				printf("%s+", s1[contador].lexemaSintactico);
				char bbbb;
				if (strcmp(yytext, ")") != 0)
				{
					bbbb = '1';
					s1[contador].valor2 = 1;
					fprintf(ficheroDraco, "<%d,%c>\n", s1[contador].tipo, bbbb);
				}
				else
				{
					s1[contador].valor2 = 2;
					bbbb = '2';
					fprintf(ficheroDraco, "<%d,%c>\n", s1[contador].tipo, bbbb);
				}

				printf("%d+", s1[contador].tipo);
				printf("%d\n", s1[contador].valor2);
				fprintf(fichero, "<%s,%d>\n", s1[contador].lexema, s1[contador].valor2);

				contador++;

				break;

			case OpAritmetico:
				s1[contador].tipo = OpAritmetico;
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lexema = "OpAritmetico";
				s1[contador].lineaDondeEsta = yylineno;

				if (strcmp(yytext, "+") == 0)
				{
					s1[contador].valor2 = 1;
				}
				if (strcmp(yytext, "-") == 0)
				{
					s1[contador].valor2 = 2;
				}
				if (strcmp(yytext, "*") == 0)
				{
					s1[contador].valor2 = 3;
				}
				if (strcmp(yytext, "/") == 0)
				{
					s1[contador].valor2 = 4;
				}
				if (strcmp(yytext, "%") == 0)
				{
					s1[contador].valor2 = 5;
				}
				printf("%d+", s1[contador].tipo);
				printf("%d\n", s1[contador].valor2);
				fprintf(fichero, "<%s,%d>\n", s1[contador].lexema, s1[contador].valor2);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;

				break;

			case OpRelacion:
				s1[contador].tipo = OpRelacion;
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lexema = "OpRelacion";
				s1[contador].lineaDondeEsta = yylineno;
				if (strcmp(yytext, "==") == 0)
				{
					s1[contador].valor2 = 1;
				}
				if (strcmp(yytext, "!=") == 0)
				{
					s1[contador].valor2 = 2;
				}
				if (strcmp(yytext, "<=") == 0)
				{
					s1[contador].valor2 = 3;
				}
				if (strcmp(yytext, ">=") == 0)
				{
					s1[contador].valor2 = 4;
				}
				if (strcmp(yytext, "<") == 0)
				{
					s1[contador].valor2 = 5;
				}
				if (strcmp(yytext, ">") == 0)
				{
					s1[contador].valor2 = 6;
				}

				printf("%d+", s1[contador].tipo);
				printf("%d\n", s1[contador].valor2);
				fprintf(fichero, "<%s,%d>\n", s1[contador].lexema, s1[contador].valor2);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;

				break;

			case OpLogico:
				s1[contador].tipo = OpLogico;
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lexema = "OpLogico";
				s1[contador].lineaDondeEsta = yylineno;
				if (strcmp(yytext, "&&") == 0)
				{
					s1[contador].valor2 = 1;
				}
				if (strcmp(yytext, "!") == 0)
				{
					s1[contador].valor2 = 2;
				}
				if (strcmp(yytext, "||") == 0)
				{
					s1[contador].valor2 = 3;
				}

				printf("%d+", s1[contador].tipo);
				printf("%d\n", s1[contador].valor2);
				fprintf(fichero, "<%s,%d>\n", s1[contador].lexema, s1[contador].valor2);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;

			case OpAsignacion:
				s1[contador].tipo = OpAsignacion;
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lexema = "OpAsignacion";
				s1[contador].lineaDondeEsta = yylineno;

				if (strcmp(yytext, "=") == 0)
				{
					s1[contador].valor2 = 1;
				}
				if (strcmp(yytext, "+=") == 0)
				{
					s1[contador].valor2 = 2;
				}
				if (strcmp(yytext, "-=") == 0)
				{
					s1[contador].valor2 = 3;
				}
				if (strcmp(yytext, "*=") == 0)
				{
					s1[contador].valor2 = 4;
				}
				if (strcmp(yytext, "/=") == 0)
				{
					s1[contador].valor2 = 5;
				}
				if (strcmp(yytext, "%=") == 0)
				{
					s1[contador].valor2 = 6;
				}
				if (strcmp(yytext, "&=") == 0)
				{
					s1[contador].valor2 = 7;
				}
				if (strcmp(yytext, "|=") == 0)
				{
					s1[contador].valor2 = 8;
				}

				printf("%d+", s1[contador].tipo);
				printf("%d\n", s1[contador].valor2);
				fprintf(fichero, "<%s,%d>\n", s1[contador].lexema, s1[contador].valor2);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;

			case OpAutoIncrementoDecremento:
				s1[contador].tipo = OpAutoIncrementoDecremento;
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lexema = "OpAutoIncrementoDecremento";
				s1[contador].lineaDondeEsta = yylineno;
				if (strcmp(yytext, "++") == 0)
				{
					s1[contador].valor2 = 1;
				}
				if (strcmp(yytext, "--") == 0)
				{
					s1[contador].valor2 = 2;
				}

				printf("%d+", s1[contador].tipo);
				printf("%d\n", s1[contador].valor2);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;

			case Llave:
				s1[contador].tipo = Llave;
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lexema = "Llave";
				s1[contador].lineaDondeEsta = yylineno;
				char aaaa;
				if (strcmp(yytext, "{") == 0)
				{
					s1[contador].valor2 = 1;
					aaaa = '1';

					fprintf(ficheroDraco, "<%d,%c>\n", s1[contador].tipo, aaaa);
				}
				if (strcmp(yytext, "}") == 0)
				{
					s1[contador].valor2 = 2;
					aaaa = '2';

					fprintf(ficheroDraco, "<%d,%c>\n", s1[contador].tipo, aaaa);
				}

				printf("%d+", s1[contador].tipo);
				printf("%d\n", s1[contador].valor2);
				fprintf(fichero, "<%s,%d>\n", s1[contador].lexema, s1[contador].valor2);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;

			case IF:
				s1[contador].tipo = IF;
				s1[contador].lexema = "if";
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case BOOLEAN:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = BOOLEAN;
				s1[contador].lexema = "boolean";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case BREAK:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = BREAK;
				s1[contador].lexema = "break";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case CASE:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = CASE;
				s1[contador].lexema = "case";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case STRING:
				s1[contador].tipo = STRING;
				s1[contador].lexema = yytext;
				s1[contador].lexemaSintactico = yytext;
				s1[contador].lineaDondeEsta = yylineno;
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case DEFAULT:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = DEFAULT;
				s1[contador].lexema = "defeault";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case DO:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = DO;
				s1[contador].lexema = "do";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case ELSE:
				s1[contador].tipo = ELSE;
				s1[contador].lexema = "else";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case FALSEE:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = FALSEE;
				s1[contador].lexema = "false";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case FOR:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = FOR;
				s1[contador].lexema = "for";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case FUNCTION:
				//Aqui es necesario usar la tabla de simbolos para almacenar datos 
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = FUNCTION;
				s1[contador].lexema = "function";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case INT:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = INT;
				s1[contador].lexema = "int";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case NULLL:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = NULLL;
				s1[contador].lexema = "null";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;;
				break;
			case INPUT:
				s1[contador].tipo = INPUT;
				s1[contador].lexema = "input";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case RETURN:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = RETURN;
				s1[contador].lexema = "return";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case SWITCH:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = SWITCH;
				s1[contador].lexema = "switch";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case TRUEE:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = TRUEE;
				s1[contador].lexema = "true";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case VAR:
				//Aqui es necesario usar la tabla de simbolos para almacenar datos 
				s1[contador].tipo = VAR;
				s1[contador].lexema = "var";
				s1[contador].lexemaSintactico = yytext;

				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,%d>\n", s1[contador].lexema, s1[contador].valor2);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case WHILE:
				s1[contador].tipo = WHILE;
				s1[contador].lexema = "while";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
			case PRINT:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = PRINT;
				s1[contador].lexema = "print";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;

			case CADENA:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = CADENA;
				s1[contador].lexema = "cadena";
				s1[contador].lineaDondeEsta = yylineno;
				fprintf(fichero, "<%s,%s>\n", s1[contador].lexema, yytext);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				printf("cadenaaaaaa\n");
				break;

			case CONSTENTERA:
				s1[contador].lexemaSintactico = yytext;
				s1[contador].tipo = CONSTENTERA;
				s1[contador].lexema = "constanteEntera";
				s1[contador].lineaDondeEsta = yylineno;
				printf("%d+", s1[contador].tipo);
				printf("%s\n", s1[contador].lexema);
				fprintf(fichero, "<%s,->\n", s1[contador].lexema);
				fprintf(ficheroDraco, "<%d,>\n", s1[contador].tipo);
				contador++;
				break;
		}
	}
	//cuando salgo del bucle escribo la tabla de simbolos

}




