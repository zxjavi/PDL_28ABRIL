#ifdef SINTACTICOSEMANTICO
int A(Typito *A_devuelvo)
{
	//amain[9];
	
	if (comparar(siguienteToken, amain, 6) == 0)
	{
	aadirRegla(1);

        printf("entra en A() SIMPLE\n");
		Typito *SIMPLE_nt = (Typito*) malloc(sizeof(Typito));
		if (SIMPLE(SIMPLE_nt) == ERROR_SSS){return ERROR_SSS;}
		
		
		equiparar(";");


		Typito *A_nt = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt) == ERROR_SSS){return ERROR_SSS;}

		if (dameTipo(A_nt) == TIPO_OK && dameTipo(SIMPLE_nt) == TIPO_OK)
		{
			rellenarTipo(A_devuelvo, TIPO_OK);
		}
		else
		{
			//hay un error antes
			return ERROR_SSS;
		}

		
        printf("sale de A() SIMPLE\n");
		free(SIMPLE_nt);
		free(A_nt);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "if") == 0)
	{
	aadirRegla(2);
        printf("entra en A() IF\n");
		equiparar("if");
		equiparar("(");
		Typito *E_nt = (Typito*) malloc(sizeof(Typito));
		if (E(E_nt) == ERROR_SSS || dameTipo(E_nt) != TIPOBOOLEAN){
        perror("LA CONDICIÓN DE IF NO ES TIPO BOOLEAN\n");
        return ERROR_SSS;}
       
		equiparar(")");
		Typito *W_nt = (Typito*) malloc(sizeof(Typito));
		if (W(W_nt) == ERROR_SSS || dameTipo(W_nt) != TIPO_OK){return ERROR_SSS;}

		if (dameTipo(E_nt) == TIPOBOOLEAN && dameTipo(W_nt) == TIPO_OK)
		{
			rellenarTipo(A_devuelvo, TIPO_OK);
            printf("sale de A() IF\n");
			free(E_nt);
			free(W_nt);
			return TODO_OK;
		}
		else
		{

			return ERROR_SSS;
		}
	}
	else if (strcmp(siguienteToken, "do") == 0)
	{
	aadirRegla(3);
        printf("entra en A() DO\n");
		equiparar("do");
		equiparar("{");
		Typito *A_nt1 = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt1) == ERROR_SSS || dameTipo(A_nt1) != TIPO_OK){return ERROR_SSS;}
		equiparar("}");
		equiparar("while");
		equiparar("(");
		Typito *E_nt = (Typito*) malloc(sizeof(Typito));
		if (E(E_nt) == ERROR_SSS){return ERROR_SSS;}
    
        if(dameTipo(E_nt) != TIPOBOOLEAN){        
            perror("LA CONDICIÓN DE DO-WHILE NO ES TIPO BOOLEAN\n");
            return ERROR_SSS;
        }
		equiparar(")");
		equiparar(";");
		Typito *A_nt2 = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt2) == ERROR_SSS || dameTipo(A_nt2) != TIPO_OK){return ERROR_SSS;}

		if (dameTipo(E_nt) == TIPOBOOLEAN && dameTipo(A_nt1) == TIPO_OK && dameTipo(A_nt2) == TIPO_OK)
		{
            printf("sale de A() DO\n");
			rellenarTipo(A_devuelvo, TIPO_OK);
			free(A_nt2);
			free(E_nt);
			free(A_nt1);
			return TODO_OK;
		}
		else
		{
			return ERROR_SSS;
		}

		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "var") == 0)
	{
	aadirRegla(4);
        printf("entra en A() VAR\n");
		equiparar("var");

		Typito *TIPO_nt = (Typito*) malloc(sizeof(Typito));
		if (TIPO(TIPO_nt) == ERROR_SSS){return ERROR_SSS;}

		equiparar("identificador");
		int latabla;
		if (dentroFuncion == 1 && existe_entrada(tablaActual, ultimoLexema) == 0){
            perror("YA EXISTE UNA VARIABLE CON ESE LEXEMA EN LA TABLA DE FUNCION\n");
            return ERROR_SSS;
        }
		if (dentroFuncion == 0 && existe_entrada(tablaGlobal, ultimoLexema) == 0){
            perror("YA EXISTE UNA VARIABLE CON ESE LEXEMA EN LA TABLA DE GENERAL\n");
            return ERROR_SSS;
        }
		else if (dentroFuncion == 1 && existe_entrada(tablaActual, ultimoLexema) != 0)
		{
			latabla = tablaActual;
		}
		else
		{
			latabla = tablaGlobal;
		}

		crear_entrada(latabla, ultimoLexema);

		elTipoElegido = dameTipo(TIPO_nt);	////TODOS SEAN ESTE TIPO

		crear_atributo_cadena(latabla, ultimoLexema, "Tipo", deEnteroATexto(elTipoElegido));

		if (dentroFuncion == 1)
		{
			crear_atributo_entero(latabla, ultimoLexema, "desplazamiento", desplfuncion);
		}
		else
		{
			crear_atributo_entero(latabla, ultimoLexema, "desplazamiento", desplgeneral);
		}
		int aInsertar;
		if (dentroFuncion == 1 && elTipoElegido != TIPOSTRING)
		{
			aInsertar = desplfuncion + 1;
			desplfuncion = aInsertar;
		}
		else if (dentroFuncion == 1 && elTipoElegido == TIPOSTRING)
		{
			aInsertar = desplfuncion + 64;
			desplfuncion = aInsertar;
		}
		else if (dentroFuncion == 0 && elTipoElegido != TIPOSTRING)
		{
			aInsertar = desplgeneral + 1;
			desplgeneral = aInsertar;
		}
		else
		{
			aInsertar = desplgeneral + 64;
			desplgeneral = aInsertar;
		}

		Typito *R_nt = (Typito*) malloc(sizeof(Typito));
		if (R(R_nt) == ERROR_SSS){return ERROR_SSS;}
        
		if (dameTipo(R_nt) != elTipoElegido){return ERROR_SSS;}
		equiparar(";");

		Typito *A_nt = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt) == ERROR_SSS){return ERROR_SSS;}
		if (dameTipo(A_nt) != TIPO_OK){return ERROR_SSS;}
		rellenarTipo(A_devuelvo, TIPO_OK);
        printf("sale de A() VAR\n");
			free(A_nt);
			free(TIPO_nt);
			free(R_nt);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "function") == 0)
	{
	aadirRegla(5);
        printf("entra en A() FUNCTION\n");
		if (dentroFuncion == 1){perror("NO SE PUEDE DECLARAR UNA FUNCION DENTRO DE OTRA FUNCION");return ERROR_SSS;}
		dentroFuncion = 1;
		equiparar("function");
		Typito *Z_nt = (Typito*) malloc(sizeof(Typito));
		if (Z(Z_nt) == ERROR_SSS){return ERROR_SSS;}
		int tipoRetornoDeFuncion = dameTipo(Z_nt);	//puede ser void(vacio),entero,cadena,etc...
		// El tipo de Z, va a ser el tipo de Retorno
		tipoRetornoActual = dameTipo(Z_nt);
		equiparar("identificador");
		if (existe_entrada(tablaGlobal, ultimoLexema) == 0){perror("YA EXISTE UN IDENTIFICADOR CON ESE NOMBRE");return ERROR_SSS;}

		tablas[indiceTablas] = crear_tabla();
		tablaActual = tablas[indiceTablas];
		indiceTablas++;

		crear_entrada(tablaGlobal, ultimoLexema);
		crear_atributo_cadena(tablaGlobal, ultimoLexema, "Tipo", "funcion");
		crear_atributo_cadena(tablaGlobal, ultimoLexema, "TipoRetorno", deEnteroATexto(tipoRetornoDeFuncion));
		crear_entrada(tablaActual, ultimoLexema);
		desplfuncion = 0;
		crear_atributo_entero(tablaActual, ultimoLexema, "desplazamiento", desplfuncion);
		crear_atributo_entero(tablaGlobal, ultimoLexema, "desplazamiento", desplgeneral);
		if (tipoRetornoDeFuncion == TIPOSTRING)
		{
			desplfuncion = desplfuncion + 2;
			desplgeneral = desplgeneral + 2;
		}
		else
		{
			desplfuncion = desplfuncion + 1;
			desplgeneral = desplgeneral + 1;
		}

		crear_atributo_cadena(tablaActual, ultimoLexema, "Tipo", "funcion");
		crear_atributo_cadena(tablaActual, ultimoLexema, "TipoRetorno", deEnteroATexto(tipoRetornoDeFuncion));

		equiparar("(");
		int anchoDeLexema=(int)sizeof(ultimoLexema);
		char functionLexema[anchoDeLexema];
		strcpy(functionLexema, ultimoLexema);
		Typito *H_nt = (Typito*) malloc(sizeof(Typito));
		if (H(H_nt) == ERROR_SSS){return ERROR_SSS;}

		if (dameNumParametros(H_nt) == 0)
		{
			crear_atributo_entero(tablaActual, functionLexema, "numParam", 0);
			crear_atributo_entero(tablaGlobal, functionLexema, "numParam", 0);
		}
		else
		{

			escribirParametrosEnTabla(tablaActual, functionLexema, dameParametros(H_nt));
			escribirParametrosEnTabla(tablaGlobal, functionLexema, dameParametros(H_nt));
			crear_atributo_entero(tablaActual, functionLexema, "numParam", dameNumParametros(H_nt));
			crear_atributo_entero(tablaGlobal, functionLexema, "numParam", dameNumParametros(H_nt));
       
		}
		//SI H.tipo vacio entonces parametros vacios
		//Si H.tipo funcion 
		equiparar(")");
		equiparar("{");
		Typito *A_nt1 = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt1) == ERROR_SSS && dameTipo(A_nt1) != TIPO_OK){return ERROR_SSS;}
		equiparar("}");
		dentroFuncion = 0;
		tablaActual = tablaGlobal;
		Typito *A_nt2 = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt2) == ERROR_SSS && dameTipo(A_nt2) != TIPO_OK){return ERROR_SSS;}
        printf("sale de A() FUNCTION\n");
		rellenarTipo(A_devuelvo, TIPO_OK);
		free(A_nt1);
		free(A_nt2);
		free(H_nt);
		free(Z_nt);
		
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "}") == 0)
	{
	aadirRegla(6);
		//LAMBDA
        printf("entra en A() LAMBDA\n");
		rellenarTipo(A_devuelvo, TIPO_OK);
        printf("sale de A() LAMBDA\n");
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "Eof") == 0)
	{
	aadirRegla(7);
		printf("entra en A() EOF\n");
		equiparar("Eof");
        printf("sale de A() EOF\n");
		rellenarTipo(A_devuelvo, TIPO_OK);
		return TODO_OK;
	}
	else
	{
        printf("NO entra bien en A() hubo error por token\n");
		errorSintactico();
		return 0;
	}
}
int SIMPLE(Typito *SIMPLE_devuelvo)
{
	int marcador;
	printf("entra en SIMPLE()\n");
	if (strcmp(siguienteToken, "return") == 0)
	{
	aadirRegla(8);
		if (dentroFuncion == 1)
		{
			dentroDeReturn=1;
			if(tipoRetornoActual == TIPOVOID){
                perror("ERROR SEMÁNTICO: SE ESTÁ REALIZANDO UN RETURN EN UNA FUNCION VOID\n");
                return ERROR_SSS;
            }
			equiparar("return");

			Typito *E_nt = (Typito*) malloc(sizeof(Typito));
			if (E(E_nt) == ERROR_SSS){return ERROR_SSS;}

            
			if (tipoRetornoActual != dameTipo(E_nt))
			{
                perror("ERROR SEMÁNTICO. SE ESTÁ REALIZANDO UN RETURN DE TIPO DIFERENTE AL DE RETORNO DE LA FUNCIÓN\n \t\tO SE ESTÁ RETORNANDO VALORES CON IDENTIFICADORES QUE NO EXISTEN EN TABLAS.\n");
				return ERROR_SSS;
			}
			rellenarTipo(SIMPLE_devuelvo, TIPO_OK);
			free(E_nt);
			dentroDeReturn=0;
			return TODO_OK;
		}
        perror("ERROR SINTÁCTICO: SE ESTÁ REALIZANDO UN RETURN FUERA DE UNA FUNCIÓN\n");
		return ERROR_SSS;
	}
	else if (strcmp(siguienteToken, "++") == 0)
	{
	aadirRegla(9);

		equiparar("++");
		equiparar("identificador");
		int laTabla;
		if      (dentroFuncion == 1 && existe_entrada(tablaActual, ultimoLexema) == 0){laTabla = tablaActual;}
		else if (dentroFuncion == 0 && existe_entrada(tablaGlobal, ultimoLexema) == 0){laTabla = tablaGlobal;}
		else{
			laTabla = tablaGlobal;
			crear_entrada(laTabla, ultimoLexema);
			crear_atributo_cadena(laTabla, ultimoLexema, "Tipo", "entero");
			crear_atributo_entero(laTabla, ultimoLexema, "desplazamiento", desplgeneral);			
			desplgeneral = desplgeneral + 1;
		}
		

		char *tipoDeTablaId = consultar_valor_atributo_cadena(laTabla, ultimoLexema, "Tipo");
		if (strcmp(tipoDeTablaId, "entero") != 0){perror("SOLO SE PUEDE HACER PRE-INCREMENTO DE UNA VARIABLE ENTERA");return ERROR_SSS;}
		rellenarTipo(SIMPLE_devuelvo, TIPO_OK);
		
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, ";") == 0)
	{
	aadirRegla(10);
		//lambdareturn 0;
        rellenarRetorno(SIMPLE_devuelvo,TIPOVOID);
		rellenarTipo(SIMPLE_devuelvo, TIPO_OK);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "identificador") == 0)
	{
	aadirRegla(11);
		/*
		{if DentroFuncion== true
		idBuscado := Buscar id en TF o/y Buscar id TG
		else idBuscado := Buscar id en TG,
		llamaFuncion := false,
		llamaIgualdad := false }
		G { 	if llamaFuncion == true && idBuscado== false then ERROR}

		cantar(5,6,7); cantar funcion, retorno Vacio
		cantar = 8;
		cantar = 8 + 9;
		cantar = 90 + 4;

		*/
		equiparar("identificador");
		int laTabla;

		if (dentroFuncion == 1 && existe_entrada(tablaActual, ultimoLexema) == 0)
		{

			
			laTabla = tablaActual;	//EXISTE EN TABLA FUNCION
			
		}
		else if ( existe_entrada(tablaGlobal, ultimoLexema) == 0)
		{

			
			laTabla = tablaGlobal;	//EXISTE EN TABLA GENERAL
			
		}
		else{

			laTabla = tablaGlobal;	//EXISTE EN TABLA GENERAL COMO ENTERO
			
			
			crear_entrada(laTabla, ultimoLexema);
			crear_atributo_cadena(laTabla, ultimoLexema, "Tipo", "entero");
			crear_atributo_entero(laTabla, ultimoLexema, "desplazamiento", desplgeneral);
			
			desplgeneral = desplgeneral + 1;
            
		}	
		char *tipoDeTablaId;
		char *retornoDeTablaId;

			tipoDeTablaId = consultar_valor_atributo_cadena(laTabla, ultimoLexema, "Tipo");
			retornoDeTablaId = consultar_valor_atributo_cadena(laTabla, ultimoLexema, "TipoRetorno");
		
		Typito *G_nt = (Typito*) malloc(sizeof(Typito));
		if (G(G_nt) == ERROR_SSS){return ERROR_SSS;}

		if (strcmp(tipoDeTablaId, "funcion") == 0 && retornoDeTablaId != NULL &&
			dameTipo(G_nt) == TIPOFUNCION && strcmp(retornoDeTablaId, "void") == 0)
		{
			/// Entra aqui solo si es una funcion, de retorno void, tipo cantar(8,9);            
			Typito *EnTabla_nt = (Typito*) malloc(sizeof(Typito));
            EnTabla_nt->numparametros = 0;
       
            
            
			traerParametrosAunTypito(laTabla, ultimoLexema, EnTabla_nt);	//RELLENAMOS ARRAY con datos de tabla

            
			int numParametrosIdTabla = consultar_valor_atributo_entero(laTabla, ultimoLexema, "numParam");
          
			int numParametrosG = dameNumParametros(G_nt);

			if (numParametrosIdTabla != numParametrosG)
			{
                		perror("NO SE HAN INTRODUCIDO EL MIMSMO NUMERO DE PARAMETROS DE LA FUNCION");
				return ERROR_SSS;
			}	// SI NO TIENEN MISMO NUMERO PARAMETROS, ERROR

			if (numParametrosG != 0 && compararParametrosEntreTypitos(EnTabla_nt, G_nt) == COMPARACION_MALA)
			{
               
                
				perror("PARAMETROS MAL PASADOS AL A FUNCION, NO COINCIDEN LOS TIPOS");
				return ERROR_SSS;
			}
            
         
			rellenarTipo(SIMPLE_devuelvo, TIPO_OK);
            		free(G_nt);
			   free(EnTabla_nt);
			return TODO_OK;
		}
		else if (dameTipo(G_nt) != TIPOFUNCION && dameTipo(G_nt) != TIPOVACIO && deTextoAEntero(tipoDeTablaId)==dameTipo(G_nt))
		{
			// cantar = "hola" && true .... ; cantar existe en tabla
            
			rellenarTipo(SIMPLE_devuelvo, TIPO_OK);
			free(G_nt);
			return TODO_OK;
		}
		else
		{

			perror("ERROR SEMANTICO DISTINTOS TIPOS EN LA ASIGNACION");
			return ERROR_SSS;
		}
	}
	else if (strcmp(siguienteToken, "input") == 0)
	{
	aadirRegla(12);
		equiparar("input");
		equiparar("(");
		equiparar("identificador");
		int laTabla;
		int marcador;
		//estmaos dentor de  funcion y existe la entrada
		if (dentroFuncion == 1 && existe_entrada(tablaActual, ultimoLexema) == 0)
		{
			
			laTabla = tablaActual;	//EXISTE EN TABLA DE FUNCION
			marcador = 1;
		}
		//
		else if (existe_entrada(tablaGlobal, ultimoLexema) == 0)
		{
			
			laTabla = tablaGlobal;	//EXISTE EN TABLA
			marcador = 1;
		}
		else{
			laTabla = tablaGlobal;	//EXISTE EN TABLA G porque vamos a crearla entera
			marcador = 1;
			
			crear_entrada(laTabla, ultimoLexema);
			crear_atributo_cadena(laTabla, ultimoLexema, "Tipo", "entero");
			crear_atributo_entero(tablaActual, ultimoLexema, "desplazamiento", desplgeneral);
			
			desplgeneral = desplgeneral + 1;
		}	

		char *tipoDeTablaId = consultar_valor_atributo_cadena(laTabla, ultimoLexema, "Tipo");
		if (!(strcmp(tipoDeTablaId, "entero") == 0 || strcmp(tipoDeTablaId, "cadena") == 0))
		{
			perror("ERROR SEMÁNTICO INPUT SOLO ADMITE VALORES ENTERO O CADENA");
			return ERROR_SSS;
		}

		equiparar(")");
		rellenarTipo(SIMPLE_devuelvo, TIPO_OK);
		
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "print") == 0)
	{
	aadirRegla(13);
		equiparar("print");
		equiparar("(");
		Typito *J_nt = (Typito*) malloc(sizeof(Typito));
		if (J(J_nt) == ERROR_SSS){return ERROR_SSS;}
		
		if (comparameParametrosString(J_nt) == COMPARACION_MALA)
		{
			
			perror("ERROR SEMÁNTICO PRINT SOLO ADMITE VALORES ENTERO O CADENA");
			return ERROR_SSS;
		}
		
		equiparar(")");
		rellenarTipo(SIMPLE_devuelvo, TIPO_OK);
		free(J_nt);
		return TODO_OK;
	}
	else
		errorSintactico();
	return ERROR_SSS;
}
/*
#define TIPOBOOLEAN -1
#define TIPOSTRING -2
#define TIPOENTERO -3
#define TIPOVACIO -4

*/
int TIPO(Typito *TIPO_devuelvo)
{

	printf("entra en TIPO()\n");
	if (strcmp(siguienteToken, "int") == 0)
	{
	aadirRegla(14);
		equiparar("int");
		rellenarTipo(TIPO_devuelvo, TIPOENTERO);
		rellenarTamanio(TIPO_devuelvo, 1);

		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "string") == 0)
	{
	aadirRegla(15);
		equiparar("string");
		rellenarTipo(TIPO_devuelvo, TIPOSTRING);
		rellenarTamanio(TIPO_devuelvo, 64);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "boolean") == 0)
	{
	aadirRegla(16);
		equiparar("boolean");
		rellenarTipo(TIPO_devuelvo, TIPOBOOLEAN);
		rellenarTamanio(TIPO_devuelvo, 1);
		return TODO_OK;
	}
	else
		errorSintactico();
	return ERROR_SSS;
}

int G(Typito *G_devuelvo)
{
	
	// {G.tipo:=E.tipo }
	if (strcmp(siguienteToken, "=") == 0)
	{
	aadirRegla(17);
        printf("entra en G() = E\n");
		equiparar("=");
		Typito *E_nt1 = (Typito*) malloc(sizeof(Typito));
		if (E(E_nt1) == ERROR_SSS){return ERROR_SSS;}
		printf("------Estoy En G = E y la E ha funcionado es de tipo -(%i)---\n",dameTipo(E_nt1));	
			
		rellenarTipo(G_devuelvo, dameTipo(E_nt1));
        printf("POR AQUI el tipo de G %i\n",dameTipo(G_devuelvo));
		free(E_nt1);
        printf("sale de G() = E\n");
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "(") == 0)
	{
        printf("entra en G() B\n");
	aadirRegla(18);
		//{G.parametros:=B.parametros }
		Typito *B_nt1 = (Typito*) malloc(sizeof(Typito));
		if (B(B_nt1) == ERROR_SSS){return ERROR_SSS;}
		copiarParametros(B_nt1, G_devuelvo);
		rellenarTipo(G_devuelvo, TIPOFUNCION);
		free(B_nt1);
        printf("Sale de G() B\n");
		return TODO_OK;
	}
	else
	{
		errorSintactico();
		return ERROR_SSS;
	}
}
int W(Typito *W_devuelvo)
{

	printf("entra en W()\n");
	if (comparar(siguienteToken, amain, 6) == 0)
	{
	aadirRegla(19);
		Typito *SIMPLE_nt = (Typito*) malloc(sizeof(Typito));
		if (SIMPLE(SIMPLE_nt) == ERROR_SSS){return ERROR_SSS;}
        if(dameRetorno(SIMPLE_nt) == TIPOVOID){
                perror("ERROR SINTACTICO, SE ESPERABA UNA SENTENCIA DETRAS DEL IF DE LINEA\n");
                return ERROR_SSS;}
		equiparar(";");
		Typito *A_nt = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt) == ERROR_SSS){return ERROR_SSS;}
		if (dameTipo(A_nt) == TIPO_OK && dameTipo(SIMPLE_nt) == TIPO_OK)
		{
			rellenarTipo(W_devuelvo, TIPO_OK);
		}
		else
		{

			return ERROR_SSS;
		}
		free(SIMPLE_nt);
		free(A_nt);
        
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "{") == 0)
	{
		aadirRegla(20);
		equiparar("{");
        
		Typito *A_nt = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt) == ERROR_SSS){return ERROR_SSS;}
        if (dameTipo(A_nt) != TIPO_OK){return ERROR_SSS;}
		equiparar("}");
		Typito *A2_nt = (Typito*) malloc(sizeof(Typito));
		if (A2(A2_nt) == ERROR_SSS){return ERROR_SSS;}
        if (dameTipo(A2_nt) != TIPO_OK){return ERROR_SSS;}
		free(A_nt);
		free(A2_nt);
		rellenarTipo(W_devuelvo, TIPO_OK);
		return TODO_OK;
	}
	else
	{
		errorSintactico();
		return ERROR_SSS;
	}
}
int A2(Typito *A2_devuelvo)
{

	

	if (strcmp(siguienteToken, "else") == 0)
	{
	aadirRegla(21);
        printf("entra en A2() ELSE\n");
		equiparar("else");
		equiparar("{");

		Typito *A_nt1 = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt1) == ERROR_SSS){return ERROR_SSS;}

		equiparar("}");
		Typito *A_nt2 = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt2) == ERROR_SSS){return ERROR_SSS;}
		free(A_nt1);
		free(A_nt2);
		rellenarTipo(A2_devuelvo, TIPO_OK);
		return TODO_OK;
	}
	else if (comparar(siguienteToken, bmain, 9) == 0 || strcmp(siguienteToken, "Eof") == 0)
	{
	aadirRegla(22);
        printf("entra en A2() A\n");
		Typito *A_nt3 = (Typito*) malloc(sizeof(Typito));
		if (A(A_nt3) == ERROR_SSS){return ERROR_SSS;}
		free(A_nt3);
		rellenarTipo(A2_devuelvo, TIPO_OK);
		return TODO_OK;
	}
	else
	{
		errorSintactico();
		return ERROR_SSS;
	}
}

int H(Typito *H_devuelvo)
{
	printf("entra en H()\n");
	if (comparar(siguienteToken, cmain, 3) == 0)
	{
	aadirRegla(23);

		Typito *TIPO_nt = (Typito*) malloc(sizeof(Typito));
		if (TIPO(TIPO_nt) == ERROR_SSS){return ERROR_SSS;}
		//{H.paramatros := ID.TIPO+++X.parametros }

		equiparar("identificador");
		if (existe_entrada(tablaActual, ultimoLexema) == 0){return ERROR_SSS;}
		crear_entrada(tablaActual, ultimoLexema);;
		crear_atributo_cadena(tablaActual, ultimoLexema, "Tipo", deEnteroATexto(dameTipo(TIPO_nt)));
		crear_atributo_entero(tablaActual, ultimoLexema, "desplazamiento", desplfuncion);
		int aInsertar;
		//cambiar el desplazamiento
		if (elTipoElegido != TIPOSTRING)
		{
			aInsertar = desplfuncion + 1;
			desplfuncion = aInsertar;
		}
		else
		{
			aInsertar = desplfuncion + 64;
			desplfuncion = aInsertar;
		}
		Typito *X_nt = (Typito*) malloc(sizeof(Typito));
		if (X(X_nt) == ERROR_SSS){return ERROR_SSS;}
		creaParametrosDeTipoYParametros(TIPO_nt, X_nt, H_devuelvo);
		free(X_nt);
		free(TIPO_nt);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, ")") == 0)
	{
	aadirRegla(24);
		//LAMBDA
		rellenarTipo(H_devuelvo, TIPOVACIO);
		return TODO_OK;
	}
	else
		errorSintactico();
	return ERROR_SSS;
}

int X(Typito *X_devuelvo)
{
	printf("entra en X()\n");
	if (strcmp(siguienteToken, ")") == 0)
	{
	aadirRegla(25);
		//LAMBDA
		rellenarTipo(X_devuelvo, TIPOVACIO);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, ",") == 0)
	{
	aadirRegla(26);

		equiparar(",");
		Typito *TIPO_nt = (Typito*) malloc(sizeof(Typito));
		if (TIPO(TIPO_nt) == ERROR_SSS){return ERROR_SSS;}

		equiparar("identificador");
		if (existe_entrada(tablaActual, ultimoLexema) == 0){perror("YA EXISTE UN PARAMETRO CON ESE LEXEMA EN LA FUNCION");return ERROR_SSS;}
		crear_entrada(tablaActual, ultimoLexema);
		crear_atributo_cadena(tablaActual, ultimoLexema, "Tipo", deEnteroATexto(dameTipo(TIPO_nt)));
		
		crear_atributo_entero(tablaActual, ultimoLexema, "desplazamiento", desplfuncion);
		int aInsertar;
		//cambiar el desplazamiento
		elTipoElegido=dameTipo(TIPO_nt);
		if (elTipoElegido != TIPOSTRING)
		{
			aInsertar = desplfuncion + 1;
			desplfuncion = aInsertar;
		}
		else
		{
			aInsertar = desplfuncion + 64;
			desplfuncion = aInsertar;
		}
		

		Typito *X_nt = (Typito*) malloc(sizeof(Typito));
		if (X(X_nt) == ERROR_SSS){return ERROR_SSS;}
		creaParametrosDeTipoYParametros(TIPO_nt, X_nt, X_devuelvo);
		free(X_nt);
		free(TIPO_nt);
		return TODO_OK;
	}
	else
		errorSintactico();
	return ERROR_SSS;
}

int Z(Typito *Z_devuelvo)
{
	printf("entra en Z()\n");
	/*
{Z.tipo:=TIPO.tipo}
*/
	if (comparar(siguienteToken, cmain, 3) == 0)
	{
	aadirRegla(27);
		Typito *TIPO_nt = (Typito*) malloc(sizeof(Typito));
		if (TIPO(TIPO_nt) == ERROR_SSS){return ERROR_SSS;}
		rellenarTipo(Z_devuelvo, dameTipo(TIPO_nt));
		free(TIPO_nt);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "identificador") == 0)
	{
	aadirRegla(28);
		//LAMBDA
		rellenarTipo(Z_devuelvo, TIPOVOID);
		return TODO_OK;
	}
	else{

		errorSintactico();

	return ERROR_SSS;}
}

int R(Typito *R_devuelvo)
{
	printf("entra en R()\n");
	if (strcmp(siguienteToken, ",") == 0)
	{
	aadirRegla(29);
		equiparar(",");

		equiparar("identificador");

		if (existe_entrada(tablaActual, ultimoLexema) == 0){
            perror("YA EXISTE UNA VARIABLE CON ESE LEXEMA EN LA TABLA \n");
            return ERROR_SSS;
        }
		crear_entrada(tablaActual, ultimoLexema);
		crear_atributo_cadena(tablaActual, ultimoLexema, "Tipo", deEnteroATexto(elTipoElegido));

		if (dentroFuncion == 1)
		{
			crear_atributo_entero(tablaActual, ultimoLexema, "desplazamiento", desplfuncion);
		}
		else
		{
			crear_atributo_entero(tablaActual, ultimoLexema, "desplazamiento", desplgeneral);
		}

		int aInsertar;
		if (dentroFuncion == 1 && elTipoElegido != TIPOSTRING)
		{
			aInsertar = desplfuncion + 1;
			desplfuncion = aInsertar;
		}
		else if (dentroFuncion == 1 && elTipoElegido == TIPOSTRING)
		{
			aInsertar = desplfuncion + 64;
			desplfuncion = aInsertar;
		}
		else if (dentroFuncion == 0 && elTipoElegido != TIPOSTRING)
		{
			aInsertar = desplgeneral + 1;
			desplgeneral = aInsertar;
		}
		else
		{
			aInsertar = desplgeneral + 64;
			desplgeneral = aInsertar;
		}

		Typito *R_nt = (Typito*) malloc(sizeof(Typito));
		if (R(R_nt) == ERROR_SSS){return ERROR_SSS;}

		if (dameTipo(R_nt) != elTipoElegido){return ERROR_SSS;}

		rellenarTipo(R_devuelvo, elTipoElegido);
		free(R_nt);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "=") == 0)
	{
	aadirRegla(30);
		equiparar("=");

		Typito *E_nt = (Typito*) malloc(sizeof(Typito));
		if (E(E_nt) == ERROR_SSS){return ERROR_SSS;}
        
		if (dameTipo(E_nt) != elTipoElegido){
            perror("Error Semantico: ESTÁ DECLARANDO VARIABLES CON VALOR INICIAL QUE NO CORRESPONDEN CON EL TIPO QUE DESEA\n");
            return ERROR_SSS;}

		Typito *R1_nt = (Typito*) malloc(sizeof(Typito));
		if (R1(R1_nt) == ERROR_SSS){return ERROR_SSS;}
		if (dameTipo(R1_nt) != elTipoElegido){return ERROR_SSS;}//ver error

		rellenarTipo(R_devuelvo, elTipoElegido);
		free(R1_nt);
		free(E_nt);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, ";") == 0)
	{
	aadirRegla(31);
		//lambda

		rellenarTipo(R_devuelvo, elTipoElegido);
		return TODO_OK;
	}
	else
		errorSintactico();
	return ERROR_SSS;
}

int R1(Typito *R1_devuelvo)
{
	printf("entra en R1()\n");
	if (strcmp(siguienteToken, ",") == 0)
	{
	aadirRegla(32);
		equiparar(",");
		equiparar("identificador");
		if (existe_entrada(tablaActual, ultimoLexema) == 0){
            perror("YA EXISTE UNA VARIABLE CON ESE LEXEMA EN LA TABLA\n");
            return ERROR_SSS;
        }
		crear_entrada(tablaActual, ultimoLexema);
		crear_atributo_cadena(tablaActual, ultimoLexema, "Tipo", deEnteroATexto(elTipoElegido));

		if (dentroFuncion == 1)
		{
			crear_atributo_entero(tablaActual, ultimoLexema, "desplazamiento", desplfuncion);
		}
		else
		{
			crear_atributo_entero(tablaActual, ultimoLexema, "desplazamiento", desplgeneral);
		}

		int aInsertar;
		if (dentroFuncion == 1 && elTipoElegido != TIPOSTRING)
		{
			aInsertar = desplfuncion + 1;
			desplfuncion = aInsertar;
		}
		else if (dentroFuncion == 1 && elTipoElegido == TIPOSTRING)
		{
			aInsertar = desplfuncion + 64;
			desplfuncion = aInsertar;
		}
		else if (dentroFuncion == 0 && elTipoElegido != TIPOSTRING)
		{
			aInsertar = desplgeneral + 1;
			desplgeneral = aInsertar;
		}
		else
		{
			aInsertar = desplgeneral + 64;
			desplgeneral = aInsertar;
		}

		Typito *R_nt = (Typito*) malloc(sizeof(Typito));
		if (R(R_nt) == ERROR_SSS){return ERROR_SSS;}
		if (dameTipo(R_nt) != elTipoElegido){ perror("Error Semantico: ESTÁ DECLARANDO VARIABLES CON VALOR INICIAL QUE NO CORRESPONDEN CON EL TIPO QUE DESEA\n");return ERROR_SSS;}
		rellenarTipo(R1_devuelvo, elTipoElegido);
		free(R_nt);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, ";") == 0)
	{
	aadirRegla(33);
		//LAMBDA
		rellenarTipo(R1_devuelvo, elTipoElegido);
		return TODO_OK;
	}
	else
		errorSintactico();
	return ERROR_SSS;
}

int E(Typito *E_devuelvo)
{

	/*
{
	if O1.TIpo== vacia then E.TIpo := S.Tipo else if {O1.TIpo==Booleano && S.TIpo==Booleano then E.TIpo := Booleano else error}
*/
	
	if (comparar(siguienteToken, jmain, 7) == 0)
	{
	aadirRegla(34);
	
 if(tipoRetornoActual == TIPOVOID && dentroDeReturn ==1){
                perror("ERROR SEMÁNTICO: SE ESTÁ REALIZANDO UN RETURN EN UNA FUNCIÓN VOID\n"); return ERROR_SSS;
}
        printf("entra en E()\n");
		Typito *S_nt = (Typito*) malloc(sizeof(Typito));
		if (S(S_nt) == ERROR_SSS){return ERROR_SSS;}
        printf("Este es el tipo de S: %i\n",dameTipo(S_nt));
		Typito *O1_nt = (Typito*) malloc(sizeof(Typito));
		if (O1(O1_nt) == ERROR_SSS){return ERROR_SSS;}
        printf("Este es el tipo de O1: %i\n",dameTipo(O1_nt));
		if (dameTipo(O1_nt) == TIPOVACIO)
		{
			rellenarTipo(E_devuelvo, dameTipo(S_nt));
		}
		else if (dameTipo(O1_nt) == TIPOBOOLEAN && dameTipo(S_nt) == TIPOBOOLEAN)
		{
			rellenarTipo(E_devuelvo, TIPOBOOLEAN);
		}
		else{ 
            perror("OPERACION (de izquierda a derecha) MAL COMPUESTA\n");
            return ERROR_SSS;}
		free(S_nt);
		free(O1_nt);
        printf("Sale de E()\n");
		return TODO_OK;
	}
	else
	{
		errorSintactico();
		return ERROR_SSS;
	}
}

int S(Typito *S_devuelvo)
{
	
	if (comparar(siguienteToken, jmain, 7) == 0)
	{
	aadirRegla(35);	
        printf("entra en S() T O2\n");
		Typito *T_nt = (Typito*) malloc(sizeof(Typito));
		if (T(T_nt) == ERROR_SSS){return ERROR_SSS;}

		Typito *O2_nt = (Typito*) malloc(sizeof(Typito));
		if (O2(O2_nt) == ERROR_SSS){return ERROR_SSS;}
		if (dameTipo(O2_nt) == TIPOVACIO)
		{
			rellenarTipo(S_devuelvo, dameTipo(T_nt));
		}
		else if (dameTipo(T_nt) == TIPOBOOLEAN && dameTipo(O2_nt) == TIPOBOOLEAN)
		{
			rellenarTipo(S_devuelvo, TIPOBOOLEAN);
		}
		else if (dameTipo(T_nt) == TIPOENTERO && dameTipo(O2_nt) == TIPOENTERO)
		{
			rellenarTipo(S_devuelvo, TIPOBOOLEAN);
		}
		else
		{
            perror("OPERACION (de izquierda a derecha) MAL COMPUESTA\n");
			return ERROR_SSS;
		}
		
        printf("Estos son los tipos de T %i y de O2 %i y devolvemos una S con \n",dameTipo(T_nt),dameTipo(O2_nt),dameTipo(S_devuelvo));
        free(T_nt);
		free(O2_nt);
        printf("sale de S() T O2\n");
		return TODO_OK;
	}
	else
	{
		errorSintactico();
		return ERROR_SSS;
	}
}

int T(Typito *T_devuelvo)
{
	

	/*
{if O3.TIpo == Vacio then T.tipo := V.Tipo }
        if V.Tipo == entero && O3.Tipo == entero then T.tipo:= Entero
        else error
*/
	if (comparar(siguienteToken, jmain, 7) == 0)
	{
	aadirRegla(36);
        printf("entra en T() V O3\n");
		Typito *V_nt = (Typito*) malloc(sizeof(Typito));
		if (V(V_nt) == ERROR_SSS){return ERROR_SSS;}

		Typito *O3_nt = (Typito*) malloc(sizeof(Typito));
		if (O3(O3_nt) == ERROR_SSS){return ERROR_SSS;}
		if (dameTipo(O3_nt) == TIPOVACIO)
		{
			rellenarTipo(T_devuelvo, dameTipo(V_nt));
            printf("sale T() V O3\n");
            printf("Estos son los tipos de V %i y de O3 %i y devolvemos una T con \n",dameTipo(V_nt),dameTipo(O3_nt),dameTipo(T_devuelvo));
            free(V_nt);
		    free(O3_nt);
		    return TODO_OK;
			
		}
		else if (dameTipo(V_nt) == TIPOENTERO && dameTipo(O3_nt) == TIPOENTERO)
		{
			rellenarTipo(T_devuelvo, TIPOENTERO);
            printf("Estos son los tipos de V %i y de O3 %i y devolvemos una T con \n",dameTipo(V_nt),dameTipo(O3_nt),dameTipo(T_devuelvo));
            free(V_nt);
		    free(O3_nt);
             printf("sale T() V O3\n");
		    return TODO_OK;
		}
		else
		{
            perror("OPERACION (de izquierda a derecha) MAL COMPUESTA\n");
			return ERROR_SSS;
		}
		
	}
	else
	{
		errorSintactico();
		return ERROR_SSS;
	}
}

int O1(Typito *O1_devuelvo)
{

	
	if (strcmp(siguienteToken, "&&") == 0)
	{
	aadirRegla(37);
        printf("entra en O1() -> && O1\n");
		/*
		{if S.tipo==bool && (O1.tipo==bool ||
		O1.tipo==vacio) then O1.tipo:=bool
		else ERROR}
		*/

		equiparar("&&");

		Typito *S_nt = (Typito*) malloc(sizeof(Typito));
		if (S(S_nt) == ERROR_SSS){return ERROR_SSS;}

		Typito *O1_nt = (Typito*) malloc(sizeof(Typito));
		if (O1(O1_nt) == ERROR_SSS){return ERROR_SSS;}
		if (dameTipo(S_nt) == TIPOBOOLEAN && (dameTipo(O1_nt) == TIPOBOOLEAN || dameTipo(O1_nt) == TIPOVACIO))
		{
			rellenarTipo(O1_devuelvo, TIPOBOOLEAN);
		}
		else
		{
            perror("OPERACION (de izquierda a derecha) MAL COMPUESTA\n");
			return ERROR_SSS;
		}
		free(S_nt);
		free(O1_nt);
        printf("sale de O1() -> && O1\n");
		return TODO_OK;
	}
	else if (comparar(siguienteToken, kmain, 3) == 0)
	{
	aadirRegla(38);
		//lambda
        printf("entra en O1() -> lambda\n");
		rellenarTipo(O1_devuelvo, TIPOVACIO);
        printf("sale de O1() -> lambda\n");
		return TODO_OK;
	}
	else{
		errorSintactico();
	return ERROR_SSS;}
}
int O2(Typito *O2_devuelvo)
{
	/*
	{
		if O2.tipo== vacio then O2.tipo:= T.tipo 
	  elseif T.tipo == entero && O2.tipo== entero then O2.tipo:= entero
	  elseif T.tipo == entero && O2.tipo== bool then O2.tipo:= entero
	else ERROR }
	*/
	
	if (strcmp(siguienteToken, "==") == 0)
	{
	aadirRegla(39);
        printf("entra en O2() -> == T O2\n");
		equiparar("==");

		Typito *T_nt = (Typito*) malloc(sizeof(Typito));
		if (T(T_nt) == ERROR_SSS){return ERROR_SSS;}

		Typito *O2_nt = (Typito*) malloc(sizeof(Typito));
		if (O2(O2_nt) == ERROR_SSS){return ERROR_SSS;}
		if (dameTipo(O2_nt) == TIPOVACIO)
		{
			rellenarTipo(O2_devuelvo, dameTipo(T_nt));
		}
		else if (dameTipo(T_nt) == TIPOENTERO && dameTipo(O2_nt) == TIPOBOOLEAN)
		{
			rellenarTipo(O2_devuelvo, TIPOENTERO);
		}
		else if (dameTipo(T_nt) == TIPOBOOLEAN && dameTipo(O2_nt) == TIPOBOOLEAN)
		{
			rellenarTipo(O2_devuelvo, TIPOBOOLEAN);
		}
		else
		{   
            perror("OPERACION (de izquierda a derecha) MAL COMPUESTA\n");
			return ERROR_SSS;
		}

		free(T_nt);
		free(O2_nt);
        printf("sale de O2() -> == T O2\n");
		return TODO_OK;
	}
	else if (comparar(siguienteToken, lmain, 4) == 0)
	{
	aadirRegla(40);
		//lambda
        printf("entra en O2() -> lambda\n");
		rellenarTipo(O2_devuelvo, TIPOVACIO);
        printf("sale de O2() -> lambda\n");
		return TODO_OK;
        
	}
	else{
		errorSintactico();
	    return ERROR_SSS;
    }
}
int O3(Typito *O3_devuelvo)
{
	/*
	{if V.tipo==int && (O3.tipo==int || O3.tipo==vacio) then
	O3.tipo:=int 
	else ERROR} 
	*/
	
	if (strcmp(siguienteToken, "+") == 0)
	{
	aadirRegla(41);
        printf("entra en O3() + ...\n");
		equiparar("+");
		Typito *V_nt = (Typito*) malloc(sizeof(Typito));
		if (V(V_nt) == ERROR_SSS){return ERROR_SSS;}

		Typito *O3_nt = (Typito*) malloc(sizeof(Typito));
		if (O3(O3_nt) == ERROR_SSS){return ERROR_SSS;}
		if (dameTipo(V_nt) == TIPOENTERO && (dameTipo(O3_nt) == TIPOENTERO || dameTipo(O3_nt) == TIPOVACIO))
		{
			rellenarTipo(O3_devuelvo, TIPOENTERO);
            free(V_nt);
		    free(O3_nt);
            printf("Sale de O3() + ...\n");
		    return TODO_OK;
		}
		else
		{
            perror("OPERACIÓN (de izquierda a derecha) MAL DESARROLLADA\n");
            errorSintactico(); 
			return ERROR_SSS;
		}
		
	}
	else if (comparar(siguienteToken, nmain, 5) == 0)
	{
	aadirRegla(42);
		//lambda
        printf("entra en O3() Lambda \n");
		rellenarTipo(O3_devuelvo, TIPOVACIO);
        printf("Sale de O3() Lamda\n");
		return TODO_OK;
	}

		errorSintactico();            
        return ERROR_SSS;

	
	
}

int B(Typito *B_devuelvo)
{
	
	if (strcmp(siguienteToken, "(") == 0)
	{
	aadirRegla(43);
        printf("entra en B() (J) \n");
		rellenarTipo(B_devuelvo, TIPOFUNCION);
		equiparar("(");
		//{ B.tipoparemetros:=J.tipoparametros}
		Typito *J_nt = (Typito*) malloc(sizeof(Typito));
		if (J(J_nt) == ERROR_SSS){return ERROR_SSS;}
		copiarParametros(J_nt, B_devuelvo);
		equiparar(")");
		free(J_nt);
        printf("sale de B() (J) \n");
		return TODO_OK;
	}
	else if (comparar(siguienteToken, zmain, 6) == 0)
	{
	aadirRegla(44);
		//lambda
        printf("entra en B() LAMBDA\n");
		rellenarTipo(B_devuelvo, TIPOVACIO);
        printf("Sale de B() LAMBDA\n");
		return TODO_OK;
	}
	else
	{

		errorSintactico();
		return ERROR_SSS;
	}
}

int J(Typito *J_devuelvo)
{
	//{J.paramatros := E.parametros+++K.parametros }
	
	if (comparar(siguienteToken, jmain, 7) == 0)
	{
	aadirRegla(45);
        printf("entra en J() -> E K\n");
		/*

J.tipo =
J.parametro = E.tipo { + K.parametros
(si K tiene parametros)

J -> lambda

J.tipo = vacio
J.parametro 
*/
		Typito *E_nt = (Typito*) malloc(sizeof(Typito));
		if (E(E_nt) == ERROR_SSS){printf("problema en la e \n");return ERROR_SSS;}

		Typito *K_nt = (Typito*) malloc(sizeof(Typito));
		if (K(K_nt) == ERROR_SSS){printf("problema en la k \n");return ERROR_SSS;}
		creaParametrosDeTipoYParametros(E_nt, K_nt, J_devuelvo);
		free(E_nt);
		free(K_nt);
        printf("Sale de J() -> E K\n");
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, ")") == 0)
	{
	aadirRegla(46);
        printf("entra en J() -> lambda\n");
		rellenarTipo(J_devuelvo, TIPOVACIO);
        printf("Sale de J()\n");
		//lambda
		return TODO_OK;
	}
	else
	{
		
		errorSintactico();
		return ERROR_SSS;
	}
}

int K(Typito *K_devuelvo)
{
	
	/*
	Si J.parametros es un array vacio 
	entonces ERROR SINTACTICO
	K.parametros = J.parametros
	K -> lambda

	K.tipo = vacio
	K.parametro
	*/
	if (strcmp(siguienteToken, ",") == 0)
	{
	aadirRegla(47);
        printf("entra en K() -> , J\n");
		equiparar(",");
		Typito *J_nt = (Typito*) malloc(sizeof(Typito));
		if (J(J_nt) == ERROR_SSS){return ERROR_SSS;}
		if (dameTipo(J_nt) == TIPOVACIO){perror("ERROR SEMANTICO FALTA UN PARAMETROS O VARIOS MAS , REVISE LA COMA AL LLAMAR A LA FUNCION");return ERROR_SSS;}
		copiarParametros(J_nt, K_devuelvo);
        printf("sale de K() -> , J\n");
		free(J_nt);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, ")") == 0)
	{
	aadirRegla(48);
		//lambda
        printf("entra en K() lambda\n");
		rellenarTipo(K_devuelvo, TIPOVACIO);
        printf("sale de K() lambda\n");
		return TODO_OK;
	}
	else
	{
		errorSintactico();
		return ERROR_SSS;
	}
}

int V(Typito *V_devuelvo)
{


	if (strcmp(siguienteToken, "identificador") == 0)
	{
	aadirRegla(49);
        printf("entra en V() -> id\n");
		equiparar("identificador");
		//si esta	

		int laTabla;
		if (dentroFuncion == 1 && existe_entrada(tablaActual, ultimoLexema) == 0)
		{
			
			laTabla = tablaActual;
		}
		else if (existe_entrada(tablaGlobal, ultimoLexema) == 0)
		{
			
			laTabla = tablaGlobal;
		}
		else{
			laTabla = tablaGlobal;	//EXISTE EN TABLA
			
			
			crear_entrada(laTabla, ultimoLexema);
			crear_atributo_cadena(laTabla, ultimoLexema, "Tipo", "entero");
			crear_atributo_entero(tablaActual, ultimoLexema, "desplazamiento", desplgeneral);
			
			desplgeneral = desplgeneral + 1;
		}

		/*	{if DentroFuncion == true
		idBuscado := buscarIdenTF o buscarIdenTG
		else  idBuscado:= buscarIdenTG
		if idBuscado:= false (no encontrado) id se crea, id.Tipo:= entero,
		}
		*/

		Typito *B_nt = (Typito*) malloc(sizeof(Typito));
		if (B(B_nt) == ERROR_SSS){return ERROR_SSS;}	//CREAMOS B

		char *tipoIdentificador = consultar_valor_atributo_cadena(laTabla, ultimoLexema, "Tipo");

		int idEsFuncion = strcmp(tipoIdentificador, "funcion");
		int identEsFuncion = dameTipo(B_nt) == TIPOFUNCION;
        
		if (idEsFuncion == 0 && identEsFuncion)
		{
            printf("ENTRA\n");
			//SI EN LA TABLA ES FUNCION Y B ES FUNCION HACEMOS ESO
            Typito *EnTabla_nt	 = (Typito*) malloc(sizeof(Typito));
            EnTabla_nt->numparametros = 0;
			traerParametrosAunTypito(laTabla, ultimoLexema, EnTabla_nt);	//RELLENAMOS typito con datos de tabla

			int numParametrosIdTabla = consultar_valor_atributo_entero(laTabla, ultimoLexema, "numParam");
			int numParametrosB = dameNumParametros(B_nt);

			if (numParametrosIdTabla != numParametrosB)
			{
                perror("DISTINTOS NUMERO DE PARAMETROS AL LLAMAR A LA FUNCION\n");
				return ERROR_SSS;
			}	// SI NO TIENEN MISMO NUMERO PARAMETROS, ERROR

			if (numParametrosB != 0 && compararParametrosEntreTypitos(EnTabla_nt, B_nt) == COMPARACION_MALA)
			{
                perror("NO COINCIDEN LOS TIPOS DE LOS PARAMETROS AL LLAMAR A LA FUNCION\n");
				return ERROR_SSS;
			}	//se cierra o no

			char *tipoRetorno = consultar_valor_atributo_cadena(laTabla, ultimoLexema,"TipoRetorno");
            
			//rellenarRetorno(V_devuelvo, deTextoAEntero(tipoRetorno));
            V_devuelvo->tipo=deTextoAEntero(tipoRetorno);
            printf("Sale de V() -> id B\n");
			free(B_nt);
			free(EnTabla_nt);
			return TODO_OK;
		}
		else if (idEsFuncion != 0 && identEsFuncion)
		{
			//si no es funcion en la tabla pero B si es funcion

			rellenarTipo(V_devuelvo, deTextoAEntero(tipoIdentificador));
			return TODO_OK;
		}
		else if (idEsFuncion != 0 && dameTipo(B_nt) == TIPOVACIO)
		{
			char *tipoVdevuelto = consultar_valor_atributo_cadena(laTabla, ultimoLexema,
				"Tipo");
			rellenarTipo(V_devuelvo, deTextoAEntero(tipoVdevuelto));
			return TODO_OK;
		}
		else
		{
			perror("ESTAS LLAMANDO COMO FUNCION A UNA VARIABLE QUE NO LO ES ");return ERROR_SSS;
		}
		/*{
		if B.parametros == idBuscado.parametros (incluye vacio)
		    V.tipo := idBuscado.returnTipo || idBuscado.Tipo
		else ERROR
		}
		*/

		errorSintactico();
		return ERROR_SSS;
	}
	else if (strcmp(siguienteToken, "entero") == 0)
	{
	aadirRegla(50);
		equiparar("entero");
		rellenarTipo(V_devuelvo, TIPOENTERO);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "-") == 0)
	{
	aadirRegla(51);
		equiparar("-");
		equiparar("entero");
		rellenarTipo(V_devuelvo, TIPOENTERO);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "(") == 0)
	{
	aadirRegla(52);
		equiparar("(");
		Typito *E_nt = (Typito*) malloc(sizeof(Typito));
		if (E(E_nt) == ERROR_SSS){return ERROR_SSS;}
		//{V.tipo:=E.tipo}
		rellenarTipo(V_devuelvo, dameTipo(E_nt));
		equiparar(")");
		free(E_nt);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "cadena") == 0)
	{
	aadirRegla(53);
		equiparar("cadena");
		rellenarTipo(V_devuelvo, TIPOSTRING);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "false") == 0)
	{
	aadirRegla(54);
		equiparar("false");
		rellenarTipo(V_devuelvo, TIPOBOOLEAN);
		return TODO_OK;
	}
	else if (strcmp(siguienteToken, "true") == 0)
	{
	aadirRegla(55);
		equiparar("true");
		rellenarTipo(V_devuelvo, TIPOBOOLEAN);
		return TODO_OK;
	}
	else
	{
		errorSintactico();
		return ERROR_SSS;
	}
}
# endif
