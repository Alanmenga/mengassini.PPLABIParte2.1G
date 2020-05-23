#ifndef UTN_MENGASSINI_H_INCLUDED
#define UTN_MENGASSINI_H_INCLUDED



#endif // UTN_MENGASSINI_H_INCLUDED

int utn_getInt(int* pResultado,char* mensaje,char* mensajeError,char minimo,char maximo,int reintentos);
float utn_getFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos);

int getString(char* cadena, int longitud);
int esNombre(char* cadena,int longitud);
int getNombre(char* pResultado,int longitud);

int esDescripcion(char* cadena,int longitud);
int getDescripcion(char* pResultado, int longitud);

int esSoloLetras(char str[]);
int esNumericoInt(char str[]);
float esNumericoFloat(float str);

int esNumerica(char* cadena, int limite);
int getInt(int* pResultado);
