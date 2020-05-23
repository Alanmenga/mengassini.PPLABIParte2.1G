#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int utn_getInt(int* pResultado,char* mensaje,char* mensajeError,char minimo,char maximo,int reintentos)
{
    int retorno=-1;
    int auxInt;
    if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL)
    {
        do
        {
            printf("%s\n",mensaje);
            scanf("%d",&auxInt);
            if(auxInt>=minimo && auxInt<=maximo)
            {
                *pResultado=auxInt;
                retorno=0;
                break;
            }
            else
            {
                printf("%s\n",mensajeError);
                reintentos--;
            }
        }while(reintentos>0);
    }
    return retorno;
}

float utn_getFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos)
{
    int retorno=-1;
    float auxFloat;
    if(pResultado!=NULL && mensaje!=NULL && mensajeError!=NULL)
    {
        do
        {
            printf("%s\n",mensaje);
            scanf("%f",&auxFloat);
            if(auxFloat>=minimo && auxFloat<=maximo)
            {
                *pResultado=auxFloat;
                retorno=0;
                break;
            }
            else
            {
                printf("%s\n",mensajeError);
                reintentos--;
            }
        }while(reintentos>0);
    }
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un nombre valido
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
int esNombre(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief 	Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
 * 			un máximo de 'longitud - 1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamaño de cadena
 * \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
 *
 */

int getString(char* cadena, int longitud)
{
	int retorno=-1;
	char bufferString[4096]; // *****************************

	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)
		{
			if(bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n')
			{
				bufferString[strnlen(bufferString,sizeof(bufferString))-1] = '\0';
			}
			if(strnlen(bufferString,sizeof(bufferString)) <= longitud)
			{
				strncpy(cadena,bufferString,longitud);
				retorno=0;
			}
		}
	}
	return retorno;
}

/**
 * \brief Obtiene un string valido como nombre
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
int getNombre(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer))==0 &&
    		esNombre(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es una descripcion valida
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
int esDescripcion(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != '.' && cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ) && (cadena[i] < '0' || cadena[i] > '9' ) )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}


/**
 * \brief Obtiene un string valido como descripcion
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */
int getDescripcion(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer))==0 &&
    		esDescripcion(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

/** \brief Verifica si el valor recibido contiene solo letras
 * \param str Array con la cade a se analizada
 * \return 1 si contiene solo ' ' y letras, 0 si no lo es
 */
int esSoloLetras(char str[])
{
    int i=0;
    while(str[i]!='\0')
    {
        if((str[i]!=' ')&&(str[i]<'a'||str[i]>'z')&&(str[i]<'A'||str[i]>'Z'))
            return 0;
        i++;
    }
    return 1;
}

/** \brief Verifica si el valor recibido es numerico
 * \param str Array con la cadena a se analizada
 * \return 1 si es numerico y 0 si no lo es
 */

 int esNumericoInt(char str[])
 {
     int i=0;
     while(str[i]!='\0')
     {
         if(str[i]<'0'||str[i]>'9')
            return 0;
         i++;
     }
     return 1;
 }

 /** \brief Verifica si el valor recibido es numerico
 * \param str Array con la cadena a se analizada
 * \return 1 si es numerico y 0 si no lo es
 */

 float esNumericoFloat(char* cadena)
 {
     int i=0;
     int retorno=0;
     int contadorPuntos=0;

     if(cadena!=NULL && strlen(cadena)>0)
     {
         for(i=0;cadena[i]!='\0';i++)
         {
             if(i==0&&(cadena[i]=='-'||cadena[i]=='+'))
             {
                 continue;
             }
             if(cadena[i]<'0'||cadena[i]>'9')
             {
                 if(cadena[i]=='.'&& contadorPuntos==0)
                 {
                     contadorPuntos++;
                 }
                 else
                 {
                     retorno=1;
                     break;
                 }
             }
         }
     }

     return retorno;
 }

 /**
 * \brief Verifica si la cadena ingresada es numerica
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es numerica, 0 (falso) si no lo es y -1 en caso de error
 *
 */
int esNumerica(char* cadena, int limite)
{
	int retorno = -1; // ERROR
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1; // VERDADERO
		for(i=0;i<limite && cadena[i] != '\0';i++)
		{
			if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
			{
				continue;
			}
			if(cadena[i] < '0'||cadena[i] > '9')
			{
				retorno = 0;
				break;
			}
			//CONTINUE
		}
		//BREAK
	}
	return retorno;
}

/**
 * \brief Obtien un numero entero
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no
 *
 */
int getInt(int* pResultado)
{
    int retorno=-1;
    char bufferString[50];
    if(	pResultado != NULL &&
    	getString(bufferString,sizeof(bufferString)) == 0 &&
    	esNumerica(bufferString,sizeof(bufferString)))
	{
		retorno=0;
		*pResultado = atoi(bufferString) ;

	}
    return retorno;
}

