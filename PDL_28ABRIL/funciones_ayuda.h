#ifdef SEMANTICO
#define NUM_PARAMETROS 50
#define COMPARACION_BUENA 0
#define COMPARACION_MALA - 1
#define TODO_OK 0
#define ERROR_SSS - 1
#define TIPO_OK 0

//PILA DE TERMINALES/
typedef struct Typito
{
	int tipo;
	int tamanio;
	int retorno;
	int parametros[NUM_PARAMETROS];
	int numparametros;
} Typito ;

void rellenarTipo(Typito *mi_est, int tipo)
{
	mi_est->tipo = tipo;
}
int dameTipo(Typito *mi_est)
{
	return mi_est->tipo;
}

void rellenarTamanio(Typito *mi_est, int tamanio)
{
	mi_est->tamanio = tamanio;
}
int dameTamanio(Typito *mi_est)
{
	return mi_est->tamanio;
}

void rellenarRetorno(Typito *mi_est, int retorno)
{
	mi_est->retorno = retorno;
}
int dameRetorno(Typito *mi_est)
{
	return mi_est->retorno;
}

void rellenarParametro(Typito *mi_est, int parametro_nuevo)
{
	mi_est->parametros[mi_est->numparametros] = parametro_nuevo;
	mi_est->numparametros++;
}
int *dameParametros(Typito *mi_est)
{
	return mi_est->parametros;
}
int dameNumParametros(Typito *mi_est)
{
	return mi_est->numparametros;
}
/**
Para usarlo, se hace:
int *losparametros = dameParametros(miTypito);
int i;
for (i = 0; i < dameNumParametros(miTypito); i++){

    losparametros[i]

}

***/

int compararParametrosEntreTypitos(Typito *primera, Typito *segunda)
{
    
	if (memcmp(dameParametros(primera), dameParametros(segunda), NUM_PARAMETROS) != 0)
	{
		return COMPARACION_MALA;
	}
	return COMPARACION_BUENA;
}

int compararParametrosEntreArrayYTypito(int *un_array, Typito *segunda)
{
for(int h = 0; h<NUM_PARAMETROS;h++)
    

	if ( memcmp(un_array, dameParametros(segunda), NUM_PARAMETROS) != 0)
	{
		return COMPARACION_MALA;
	}
	return COMPARACION_BUENA;
}
void copiarParametros(Typito *primera, Typito *segunda)
{
	int *losparametros = dameParametros(primera);
	for (int i = 0; i < dameNumParametros(primera); i++)
	{
		rellenarParametro(segunda, losparametros[i]);
	}
}
void sumarParametros(Typito *izquierda, Typito *derecha, Typito *destino)
{

		int *losparametrosA = dameParametros(izquierda);
		int i;
		for (i = 0; i < dameNumParametros(izquierda); i++)
		{
			rellenarParametro(destino, losparametrosA[i]);
		}
		int *losparametrosB = dameParametros(derecha);
		int j;
		for (j = 0; j < dameNumParametros(derecha); j++)
		{
			rellenarParametro(destino, losparametrosB[j]);
		}
}
void creaParametrosDeTipoYParametros(Typito *izquierda, Typito *derecha, Typito *destino){

        rellenarParametro(destino, dameTipo(izquierda));
        int j;
		for (j = 0; j < dameNumParametros(derecha); j++)
		{
			rellenarParametro(destino, dameParametros(derecha)[j]);
		}
}


//FUNCIONES ESPECIALES PARA LA TABLA DE SIMBOLOS

int deTextoAEntero(char * texto){

    if(strcmp(texto,"funcion")==0){ return TIPOFUNCION;}
    if(strcmp(texto,"boolean")==0){ return TIPOBOOLEAN;}
    if(strcmp(texto,"entero")==0){ return TIPOENTERO;}
    if(strcmp(texto,"cadena")==0){ return TIPOSTRING;}
    if(strcmp(texto,"vacio")==0){ return TIPOVACIO;}
	if(strcmp(texto,"void")==0){ return TIPOVOID;}

    return ERROR_SSS;

}

char * deEnteroATexto(int  entero){

    if(entero==TIPOFUNCION){ return "funcion";}
    if(entero==TIPOBOOLEAN){ return "boolean";}
    if(entero==TIPOENTERO){ return "entero";}
    if(entero==TIPOSTRING){ return "cadena";}
    if(entero==TIPOVACIO){ return "vacio";}
	 if(entero==TIPOVOID){ return "void";}

    return "ERROR";

}


int traerParametrosAunTypito(int id_tabla, char *lexema, Typito * TypitoDestino){
    /* SI LLAMAMOS A ESTA FUNCIÓN ES PORQUE ESTAMOS SEGUROS DE QUE ES UNA FUNCIÓN ESTE LEXEMA*/
    int numeroParametros = consultar_valor_atributo_entero(id_tabla, lexema, "numParam");
    if(numeroParametros==0){ return TODO_OK;}
    char tipoParamXX[11];
    int i;

    for(i=0; i< numeroParametros ; i++){
        int o=i+1;
        sprintf(tipoParamXX, "tipoParam%i", o); //CONCATENA tipoParam con lo que valga i, por ejemplo si i vale 45 nos tipoParamXX="tipoParam45"
        rellenarParametro(TypitoDestino, deTextoAEntero ( consultar_valor_atributo_cadena(id_tabla, lexema, tipoParamXX)    ));
        
    }

    return TODO_OK;
}

int escribirParametrosEnTabla(int id_tabla, char *lexema, int * arrayParametros){
    /* SI LLAMAMOS A ESTA FUNCIÓN ES PORQUE ESTAMOS SEGUROS DE QUE ES UNA FUNCIÓN ESTE LEXEMA*/
    int i;
    char tipoParamXX[11];
    for( i=1 ; i<NUM_PARAMETROS+1 ; ++i){
        if(arrayParametros[i-1]!=0){
            sprintf(tipoParamXX, "tipoParam%i", i);
            if(crear_atributo_cadena(id_tabla, lexema, tipoParamXX, deEnteroATexto(arrayParametros[i-1]))==-1){return ERROR_SSS;}

        }
    }
    return TODO_OK;
}

int comparameParametrosString(Typito *mi_est)
{
    int num = mi_est->numparametros;
    int * nuevoArray =  mi_est->parametros;
    int i;


    for(i = 0; i<dameNumParametros(mi_est); i++){

            if(nuevoArray[i]==TIPOBOOLEAN){return COMPARACION_MALA;}
    }
	return COMPARACION_BUENA;
}


# endif
