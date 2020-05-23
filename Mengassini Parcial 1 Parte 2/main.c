#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datawarehouse.h"
#include "utn_mengassini.h"


#define TAM 15
#define TAMTIPOS 4
#define TAMCOLORES 5

#define TAMCLIENTES 15

#define TAMSERVICIOS 4
#define TAMTRABAJOS 8
#define CANTHARDCODE 10
#define CANTHARDCODETRABAJOS 5

typedef struct
{
    int dia;
    int mes;
    int anio;
} eFecha;

typedef struct
{
    int id;//Comienza en 1000
    char descripcion[20];

}eTipo;

typedef struct
{
    int id;//Comienza en 10000
    char nombreColor[20];
}eColor;

typedef struct
{
    int id;
    char marca[20];
    int idTipo;//Validar
    int idColor;//Validar
    int cilindrada;
    int idCliente;
    int isEmpty;
}eMoto;

typedef struct
{
    int id;//Comienza en 20000
    char descripcion[25];
    float precio;

}eServicio;


typedef struct
{
    int id;//Autoincremental
    int idMoto;//Debe existir
    int idServicio;//Debe existir
    eFecha fecha;//Validar dia, mes y año
    int isEmpty;
}eTrabajo;
//----------------------------------

typedef struct
{
    int idc;
    char nombre[20];
    char sexo;
}eCliente;
//----------------------------------
char menu();
void inicializarMotos(eMoto vec[],int tam);
void hardcodearMotos(eMoto motos[],int cant);
//void hardcodearClientes(eCliente clientes[],int tamClientes);

//---------------------------------------------------PUNTO A ALTA MOTO---------------------------
int altaMoto(int idx,eMoto moto[], int tamMotos,eTipo tipos[], int tamTipos,eColor colores[],int tamColores,int idC,eCliente clientes[],int tamClientes);
int buscarLibre(eMoto vec[], int tam);
//---------------------------------------------------PUNTO B MODIFICAR MOTO---------------------------
void modificarMoto(eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes);
int buscarMoto(int id,eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores);
//---------------------------------------------------PUNTO C BAJA MOTO--------------------------
void bajaMoto(eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes);
//---------------------------------------------------PUNTO D LISTAR MOTOS ORDENADAS---------------------------
int cargarDescripcionTipo(char descripcion[],int id,eTipo tipos[],int tamTipos);
int cargarDescripcionColor(char descripcion[],int id,eColor colores[],int tamColores);
int cargarNombreCliente(char nombre[],int id,eCliente clientes[],int tamClientes);
void mostrarMoto(eMoto moto,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes);
void mostrarMotos(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes);
//---------------------------------------------------PUNTO E LISTAR TIPOS---------------------------
void mostrarTipo(eTipo tipos,int tamTipos);
void mostrarTipos(eTipo tipos[],int tamTipos);
//---------------------------------------------------PUNTO F MOSTRAR COLORES---------------------------
void mostrarColor(eColor colores,int tamColores);
void mostrarColores(eColor colores[],int tamColores);
//---------------------------------------------------PUNTO G MOSTRAR SERVICIOS---------------------------
void mostrarServicio(eServicio servicios,int tamServicios);
void mostrarServicios(eServicio servicios[],int tamServicios);
//---------------------------------------------------PUNTO H ALTA TRABAJO---------------------------
void inicializarTrabajos(eTrabajo trabajos[],int tamTrabajos);
int buscarLibreTrabajos(eTrabajo trabajos[], int tamTrabajos);
int altaTrabajo(int idx,eTrabajo trabajos[],int tamTrabajos,eMoto moto[], int tamMotos,eTipo tipos[],
                int tamTipos,eColor colores[],int tamColores,eServicio servicios[],int tamServicios,eCliente clientes[],int tamClientes);
int validarFecha(int dia,int mes,int anio);
//---------------------------------------------------PUNTO I MOSTRAR TRABAJOS---------------------------
void mostrarTrabajo(eTrabajo trabajos,eMoto moto[],int tamMotos,eServicio servicios[],int tamServicios);
int cargarMarcaMoto(char marca[],int id,eMoto moto[],int tamMotos);
int cargarDescripcionServicio(char descripcion[],int id,eServicio servicio[],int tamServicio);
void mostrarTrabajos(eTrabajo trabajos[],int tamTrabajos,eMoto motos[],int tamMoto,eServicio servicios[],int tamServicios);
void hardcodearTrabajos(eTrabajo trabajo[],int tamTrabajos);

//-----------------------------------INFORMES--------------------------------------
//--------------------------PUNTO J MOSTRAR MOTOS SEGUN COLOR----------------------
void informarMotosColor(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes);
//--------------------------PUNTO K MOSTRAR MOTOS SEGUN TIPO----------------------
void informarMotosTipo(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes);
//--------------------------PUNTO L MOSTRAR MOTOS MAYOR CILINDRADA----------------------
void informarMotosMayorCilindrada(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes);
//--------------------------PUNTO M MOSTRAR MOTOS POR TIPO----------------------
void informarMotosXTipo(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes);
//--------------------------PUNTO N MOSTRAR MOTOS SEGUN COLOR Y TIPO----------------------
void informarMotosXColorXTipo(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes);
//--------------------------PUNTO O MOSTRAR COLORES MAS ELEGIDOS----------------------
void informarColorMasElegido(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes);

int main()
{
    char seguir='s';
    char confirma;
    int proximoIdMoto=1;
    int proximoIdTrabajo=500;
    int proximoIdCliente=100;

    eMoto lista[TAM];
    inicializarMotos(lista,TAM);
    eTrabajo listaTrabajos[TAMTRABAJOS];
    inicializarTrabajos(listaTrabajos,TAMTRABAJOS);

    hardcodearMotos(lista,CANTHARDCODE);
    proximoIdMoto+=CANTHARDCODE;
    proximoIdCliente+=CANTHARDCODE;

    hardcodearTrabajos(listaTrabajos,CANTHARDCODETRABAJOS);
    proximoIdTrabajo+=CANTHARDCODETRABAJOS;


    eTipo tipos[TAMTIPOS]={{1000,"Enduro"},{1001,"Chopera"},{1002,"Scooter"},{1003,"Ciclomotor"}};
    eColor colores[TAMCOLORES]={{10000,"Gris"},{10001,"Negro"},{10002,"Blanco"},{10003,"Azul"},{10004,"Rojo"}};
    eServicio servicios[TAMSERVICIOS]={{20000,"Cambio aceite",2500},{20001,"Cambio llantas",3000},{20002,"Cambio frenos",1000},{20003,"Cambio cadena",500}};
    eCliente listaClientes[CANTHARDCODE]={{100,"Juan",'m'},{101,"Lucia",'f'},{102,"Miguel",'m'},{103,"Daniela",'f'},{104,"Sofia",'f'},{105,"Gaston",'m'},{106,"Diego",'m'},{107,"Mia",'f'},{108,"Valentina",'f'},{109,"Luis",'m'}};
    do
    {
        switch(menu())
        {
            case 'a':
            {

                if(altaMoto(proximoIdMoto,lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,proximoIdCliente,listaClientes,TAMCLIENTES)==1)
                {
                    proximoIdMoto++;
                    proximoIdCliente++;
                }
                break;
            }
            case 'b':
            {
                modificarMoto(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,listaClientes,TAMCLIENTES);
                break;
            }
            case 'c':
            {
                bajaMoto(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,listaClientes,TAMCLIENTES);
                break;
            }
            case 'd':
            {
                mostrarMotos(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,listaClientes,TAMCLIENTES);
                break;
            }
            case 'e':
            {
                mostrarTipos(tipos,TAMTIPOS);
                break;
            }
            case 'f':
            {
                mostrarColores(colores,TAMCOLORES);
                break;
            }
            case 'g':
            {
                mostrarServicios(servicios,TAMSERVICIOS);
                break;
            }
            case 'h':
            {
                altaTrabajo(proximoIdTrabajo,listaTrabajos,TAMTRABAJOS,lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,servicios,TAMSERVICIOS,listaClientes,TAMCLIENTES);
                break;
            }
            case 'i':
            {
                mostrarTrabajos(listaTrabajos,TAMTRABAJOS,lista,TAM,servicios,TAMSERVICIOS);
                break;
            }
            case 'j':
            {
                informarMotosColor(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,listaClientes,TAMCLIENTES);
                break;
            }
            case 'k':
            {
                informarMotosTipo(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,listaClientes,TAMCLIENTES);
                break;
            }
            case 'l':
            {
                informarMotosMayorCilindrada(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,listaClientes,TAMCLIENTES);
                break;
            }
            case 'm':
            {
                informarMotosXTipo(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,listaClientes,TAMCLIENTES);
                break;
            }
            case 'n':
            {
                informarMotosXColorXTipo(lista,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,listaClientes,TAMCLIENTES);
                break;
            }
            case 'x':
            {
                printf("   | Confirma salir de gestion de empleados?(s/n): ");
                fflush(stdin);
                scanf("%c", &confirma);
                if(confirma=='s')
                {
                    seguir='n';
                }
                break;
            }
            default:
            {
                  printf("   | Opcion incorrecta.\n");
            }
        }
        system("pause");
    }
    while(seguir=='s');
    return 0;
}

char menu()
{
    char opcion;
    system("cls");
    printf("   |-----------------------------------------------------|\n");
    printf("   |-----------------Menu de Opciones--------------------|\n");
    printf("   | a- Alta Moto                                        |\n");
    printf("   | b- Modificar Moto                                   |\n");
    printf("   | c- Baja Moto                                        |\n");
    printf("   | d- Listar Motos                                     |\n");
    printf("   | e- Listar Tipos                                     |\n");
    printf("   | f- Listar Colores                                   |\n");
    printf("   | g- Listar Servicios                                 |\n");
    printf("   | h- Alta Trabajo                                     |\n");
    printf("   | i- Listar Trabajos                                  |\n");
    printf("   | j- Listar Motos por Color                           |\n");
    printf("   | k- Listar Motos del Tipo Elegido                    |\n");
    printf("   | l- Listar Motos de Mayor Cilindrada                 |\n");
    printf("   | m- Listar Motos por Tipo                            |\n");
    printf("   | n- Cantidad de Motos segun Color y Tipo             |\n");
    printf("   | m-                             |\n");
    printf("   | x- Salir                                            |\n\n");
    printf("   | Ingrese letra de opcion: ");
    fflush(stdin);
    scanf("%c",&opcion);

    return opcion;
}

void inicializarMotos(eMoto vec[],int tam)
{
    for(int i=0; i<tam; i++)
    {
        vec[i].isEmpty=1;
    }
}

void hardcodearMotos(eMoto motos[],int cant)
{
    for(int i=0;i<cant;i++)
    {
        motos[i].id=ids[i];
        strcpy(motos[i].marca,marcas[i]);
        motos[i].idTipo=idsTipos[i];
        motos[i].idColor=idsColores[i];
        motos[i].cilindrada=cilindradas[i];
        motos[i].idCliente=idClientes[i];
        motos[i].isEmpty=0;
    }
}

//---------------------------------------------------PUNTO A ALTA MOTO---------------------------
int buscarLibre(eMoto vec[], int tam)
{
    int indice=-1;
    for(int i=0; i<tam; i++)
    {
        if (vec[i].isEmpty==1)//==(vec[i].isEmpty)
        {
            indice=i;
            break;
        }
    }
    return indice;
}


int altaMoto(int idx,eMoto moto[], int tamMotos,eTipo tipos[], int tamTipos,eColor colores[],int tamColores,int idC,eCliente clientes[],int tamClientes)
{
    int retorno=0;
    int indice=buscarLibre(moto,tamMotos);
    eMoto auxMoto;
    system("cls");
    printf("   |-----------------------------------------------------|\n");
    printf("   |---------------------Alta Motos----------------------|\n");
    if (indice==-1)
    {
        printf("   | Sistema Completo\n\n");
    }
    else
    {
            auxMoto.id=idx;
            printf("   | Posibles marcas: Benelli-BMW-Ducati-Gilera-Honda-Kawasaki-Suzuki-Yamaha\n");
            printf("   |     \n");
            printf("   | Ingrese marca: ");
            fflush(stdin);
            gets(auxMoto.marca);
            while(esSoloLetras(auxMoto.marca)!=1)
            {
                printf("   | Error. Marca incorrecto.\n");
                printf("   | Ingrese marca: ");
                gets(auxMoto.marca);
            }

            mostrarTipos(tipos,tamTipos);
            printf("   |     \n");
            printf("   | Ingrese el tipo: ");
            scanf("%d",&auxMoto.idTipo);
            while(auxMoto.idTipo<1000||auxMoto.idTipo>1003)
            {
                printf("   | Error. Id-Tipo incorrecto.\n");
                printf("   | Ingrese el tipo: ");
                scanf("%d",&auxMoto.idTipo);
            }

            mostrarColores(colores,tamColores);
            printf("   |     \n");
            printf("   | Ingrese el color: ");
            scanf("%d",&auxMoto.idColor);
            while(auxMoto.idColor<10000||auxMoto.idColor>10004)
            {
                printf("   | Error. Id-Color incorrecto.\n");
                printf("   | Ingrese el color: ");
                scanf("%d",&auxMoto.idColor);
            }

            printf("   |     \n");
            printf("   | Ingrese cilindrada(50-125-500-600-750): ");
            scanf("%d",&auxMoto.cilindrada);
            while(auxMoto.cilindrada!=50&&auxMoto.cilindrada!=125&&auxMoto.cilindrada!=500&&auxMoto.cilindrada!=600&&auxMoto.cilindrada!=750)
            {
                printf("   | Error. Cilindrada incorrecta.\n");
                printf("   | Ingrese cilindrada(50-125-500-600-750): ");
                scanf("%d",&auxMoto.cilindrada);
            }
            //------------------------------------------------------------------
            auxMoto.idCliente=idC;
            clientes->idc=idC;
            printf("   | Ingrese el nombre del cliente: ");
            fflush(stdin);
            gets(clientes->nombre);
            while(esSoloLetras(clientes->nombre)!=1)
            {
                printf("   | Error. Marca incorrecto.\n");
                printf("   | Ingrese marca: ");
                gets(clientes->nombre);
            }


            printf("   | Ingrese el sexo del cliente: ");
            fflush(stdin);
            scanf("%s",&clientes->sexo);
            while(clientes->sexo!='m'&&clientes->sexo!='f')
            {
                printf("   | Error. Sexo incorrecto.\n");
                printf("   | Ingrese el sexo del cliente: ");
                fflush(stdin);
                scanf("%c",&clientes->sexo);
            }

            auxMoto.isEmpty=0;
            moto[indice]=auxMoto;//Copio al vector al empleado nuevo
            retorno=1;
    }
    return retorno;
}

//---------------------------------------------------PUNTO B MODIFICAR MOTO---------------------------
void modificarMoto(eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes)
{
    int id;
    int existe;
    int opcion;
    int nuevoIdColor;
    int nuevaCilindrada;
    system("cls");
    printf("   |-----------------------------------------------------|\n");
    printf("   |-------------------Modificar Moto--------------------|\n");
    printf("   |     \n");
    printf("   |  Ingrese id: ");
    scanf("%d",&id);

    existe=buscarMoto(id,moto,tamMotos,tipos,tamTipos,colores,tamColores);
    if(existe==-1)
    {
        printf("   |     \n");
        printf("   | No existe moto con este id: %d\n",id);
    }
    else
    {
        mostrarMoto(moto[existe],tipos,tamTipos,colores,tamColores,clientes,tamClientes);
        printf("   |-----------------------------------------------------|\n");
        printf("   |-----------------Modificar Moto Id %d ---------------|\n",id);
        printf("   |     \n");
        printf("   | 1-Cilindrada\n");
        printf("   | 2-Color\n");
        printf("   | Que dato desea modificar?: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                {
                    printf("   |     \n");
                    printf("   | Ingrese nueva cilindrada(50-125-500-600-750): ");
                    scanf("%d",&nuevaCilindrada);
                    while(nuevaCilindrada!=50&&nuevaCilindrada!=125&&nuevaCilindrada!=500&&nuevaCilindrada!=600&&nuevaCilindrada!=750)
                        {
                            printf("   | Error. Cilindrada incorrecta.\n");
                            printf("   | Ingrese cilindrada(50-125-500-600-750): ");
                            scanf("%d",&nuevaCilindrada);
                        }
                    moto[existe].cilindrada=nuevaCilindrada;
                    printf("   |     \n");
                    printf("   | Se ha actualizado la cilindrada con exito.");
                    break;
                }
            case 2:
                {
                    mostrarColores(colores,tamColores);
                    printf("   |     \n");
                    printf("   | Ingrese el nuevo color: ");
                    scanf("%d",&nuevoIdColor);
                    while(nuevoIdColor<10000||nuevoIdColor>10004)
                        {
                            printf("   | Error. Id-Color incorrecto.\n");
                            printf("   | Ingrese el color: ");
                            scanf("%d",&nuevoIdColor);
                        }
                    moto[existe].idColor=nuevoIdColor;
                    printf("   |     \n");
                    printf("   | Se ha actualizado el color con exito.");
                    break;
                }
            default:
                {
                    printf("   |     \n");
                    printf("   | Opcion Incorrecta.");
                    break;
                }
        }

    }
}

int buscarMoto(int id,eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores)
{
    int indice=-1;
    for(int i=0; i<tamMotos; i++)
    {
        if (moto[i].id==id && moto[i].isEmpty==0)//==(moto[i].isEmpty)
        {
            indice=i;
            break;
        }
    }
    return indice;
}

//---------------------------------------------------PUNTO C BAJA MOTO--------------------------

void bajaMoto(eMoto moto[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes)
{
    int id;
    int existe;
    char confirma;
    system("cls");
    printf("   |-----------------------------------------------------|\n");
    printf("   |----------------------Baja Moto----------------------|\n");
    printf("   | Ingrese id: ");
    scanf("%d",&id);
    existe=buscarMoto(id,moto,tamMotos,tipos,tamTipos,colores,tamColores);
    if(existe==-1)
    {
        printf("   | No existe moto con este id: %d\n",id);
    }

    else
    {
        mostrarMoto(moto[existe],tipos,tamTipos,colores,tamColores,clientes,tamClientes);
        printf("\n   | Confirma Baja?(s/n): ");
        fflush(stdin);
        scanf("%c",&confirma);
        if(confirma=='s')
        {
            moto[existe].isEmpty=1;
            printf("   | Se ha realizado la baja con exito.\n\n");
        }
        else
        {
            printf("   | Se ha cancelado la operacion;");
        }
    }
}

//---------------------------------------------------PUNTO D LISTAR MOTOS ORDENADAS---------------------------

int cargarDescripcionTipo(char descripcion[],int id,eTipo tipos[],int tamTipos)
{
    int retorno=0;
    for(int i=0;i<tamTipos;i++)
    {
        if(tipos[i].id==id)
        {
            strcpy(descripcion,tipos[i].descripcion);
            retorno=1;
        }
    }
    return retorno;
}

int cargarDescripcionColor(char descripcion[],int id,eColor colores[],int tamColores)
{
    int retorno=0;
    for(int i=0;i<tamColores;i++)
    {
        if(colores[i].id==id)
        {
            strcpy(descripcion,colores[i].nombreColor);
            retorno=1;
        }
    }
    return retorno;
}

int cargarNombreCliente(char nombre[],int id,eCliente clientes[],int tamClientes)
{
    int retorno=0;
    for(int i=0;i<tamClientes;i++)
    {
        if(clientes[i].idc==id)
        {
            strcpy(nombre,clientes[i].nombre);
            retorno=1;
        }
    }
    return retorno;
}

void mostrarMoto(eMoto moto,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes)
{
    char descripcionTipo[20];
    char descripcionColor[20];
    char nombreCliente[20];
    cargarDescripcionTipo(descripcionTipo,moto.idTipo,tipos,tamTipos);
    cargarDescripcionColor(descripcionColor,moto.idColor,colores,tamColores);
    cargarNombreCliente(nombreCliente,moto.idCliente,clientes,tamClientes);
    printf("   |  %02d   %10s   %10s  %10s        %3d             %s\n", moto.id,moto.marca,descripcionTipo,descripcionColor,moto.cilindrada,nombreCliente);
}



void mostrarMotos(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes)
{
    int flag=0;
    //system("cls");
    printf("   |--------------------------------------------------------|\n");
    printf("   |---------------------Listado Motos----------------------|\n");
    printf("   |  id        Marca      Tipo          Color      Cilindrada     Cliente\n");
    for(int i=0; i<tamMotos; i++)
    {
        if(motos[i].isEmpty==0)
        {
            mostrarMoto(motos[i],tipos,tamTipos,colores,tamColores,clientes,tamClientes);
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("\n   |---------No hay motos que listar-----------\n");
    }
}

//---------------------------------------------------PUNTO E MOSTRAR LOS TIPOS---------------------------

void mostrarTipo(eTipo tipos,int tamTipos)
{
    printf("   |   %d   %10s   \n",tipos.id,tipos.descripcion);
}



void mostrarTipos(eTipo tipos[],int tamTipos)
{
    //system("cls");
    printf("   |-----------------------------------------------------|\n");
    printf("   |---------------------Tipos de Motos------------------|\n");
    printf("   |    Id         Tipo      \n");
    for(int i=0; i<tamTipos; i++)
    {
            mostrarTipo(tipos[i],tamTipos);
    }
}

//---------------------------------------------------PUNTO F MOSTRAR COLORES---------------------------

void mostrarColor(eColor colores,int tamColores)
{
    printf("   |  %d   %10s   \n",colores.id,colores.nombreColor);
}



void mostrarColores(eColor colores[],int tamColores)
{
    //system("cls");
    printf("   |-----------------------------------------------------|\n");
    printf("   |-------------------Colores de Motos------------------|\n");
    printf("   |    id         Tipo  \n");
    for(int i=0; i<tamColores; i++)
    {
            mostrarColor(colores[i],tamColores);
    }
}


//---------------------------------------------------PUNTO G MOSTRAR SERVICIOS---------------------------

void mostrarServicio(eServicio servicios,int tamServicios)
{
    printf("   |  %d   %15s     %.2f\n",servicios.id,servicios.descripcion,servicios.precio);
}



void mostrarServicios(eServicio servicios[],int tamServicios)
{
    //system("cls");
    printf("   |------------------------------------------------------|\n");
    printf("   |-------------------Servicios de Motos-----------------|\n");
    printf("   |    id      Descripcion        Precio\n");
    for(int i=0; i<tamServicios; i++)
    {
            mostrarServicio(servicios[i],tamServicios);
    }
}

//---------------------------------------------------PUNTO H ALTA TRABAJO---------------------------

void inicializarTrabajos(eTrabajo trabajos[],int tamTrabajos)
{
    for(int i=0; i<tamTrabajos; i++)
    {
        trabajos[i].isEmpty=1;
    }
}

int buscarLibreTrabajos(eTrabajo trabajos[], int tamTrabajos)
{
    int indice=-1;
    for(int i=0; i<tamTrabajos; i++)
    {
        if (trabajos[i].isEmpty==1)//==(trabajos[i].isEmpty)
        {
            indice=i;
            break;
        }
    }
    return indice;
}


int altaTrabajo(int idx,eTrabajo trabajos[],int tamTrabajos,eMoto moto[], int tamMotos,eTipo tipos[],
                int tamTipos,eColor colores[],int tamColores,eServicio servicios[],int tamServicios,eCliente clientes[],int tamClientes)
{
    int retorno=0;
    int existe;
    int indice=buscarLibreTrabajos(trabajos,tamTrabajos);
    eTrabajo auxTrabajo;
    system("cls");
    printf("   |-----------------------------------------------------|\n");
    printf("   |-------------------Alta de Trabajos------------------|\n");
    if (indice==-1)
    {
        printf("   | Sistema Completo\n\n");
    }
    else
    {
            auxTrabajo.id=idx;

            mostrarMotos(moto,TAM,tipos,TAMTIPOS,colores,TAMCOLORES,clientes,tamClientes);
            printf("   | Ingrese id moto: ");
            scanf("%d",&auxTrabajo.idMoto);

            existe=buscarMoto(auxTrabajo.idMoto,moto,tamMotos,tipos,tamTipos,colores,tamColores);
            while(existe==-1)
            {
                printf("   |     \n");
                printf("   | No existe moto con este id: %d\n",auxTrabajo.idMoto);
                printf("   |     \n");
                printf("   | Ingrese id moto: ");
                scanf("%d",&auxTrabajo.idMoto);
                existe=buscarMoto(auxTrabajo.idMoto,moto,tamMotos,tipos,tamTipos,colores,tamColores);
            }

            mostrarServicios(servicios,TAMSERVICIOS);
            printf("   | Ingrese id de servicio: ");
            scanf("%d",&auxTrabajo.idServicio);
            while(auxTrabajo.idServicio<20000||auxTrabajo.idServicio>20003)
            {
                printf("   | Error. Id-Servicio incorrecto.\n");
                printf("   | Ingrese id de servicio: ");
                scanf("%d",&auxTrabajo.idServicio);
            }

            printf("   | Ingrese dia del trabajo: ");
            scanf("%d",&auxTrabajo.fecha.dia);
            printf("   | Ingrese mes del trabajo: ");
            scanf("%d",&auxTrabajo.fecha.mes);
            printf("   | Ingrese anio del trabajo: ");
            scanf("%d",&auxTrabajo.fecha.anio);

            printf("%d",validarFecha(auxTrabajo.fecha.dia,auxTrabajo.fecha.mes,auxTrabajo.fecha.anio));
            while(validarFecha(auxTrabajo.fecha.dia,auxTrabajo.fecha.mes,auxTrabajo.fecha.anio)==-1)
            {
                printf("   | Fecha Incorrecta. Intente otra vez.\n");
                printf("   | Ingrese dia del trabajo: ");
                scanf("%d",&auxTrabajo.fecha.dia);
                printf("   | Ingrese mes del trabajo: ");
                scanf("%d",&auxTrabajo.fecha.mes);
                printf("   | Ingrese anio del trabajo: ");
                scanf("%d",&auxTrabajo.fecha.anio);
            }

            auxTrabajo.isEmpty=0;
            trabajos[indice]=auxTrabajo;//Copio al vector al empleado nuevo
            retorno=1;
    }
    return retorno;
}

int validarFecha(int dia,int mes,int anio)
{
    int retorno=-1;

    if(anio>=1900&&anio<=2020)
    {
        if ( mes>=1 && mes<=12 )
        {
            switch (mes)
            {
                case 1://enero
                case 3://marzo
                case 5://mayo
                case 7://julio
                case 8://agosto
                case 10://octubre
                case 12:/*diciembre*/if(dia>=1 && dia<=31)
                                     {
                                            //printf("   | Fecha correcta.\n");
                                            retorno=0;
                                     }
                                     else
                                     {
                                            //printf("   | Fecha incorrecta.\n");
                                            retorno=-1;
                                     }
                                     break;

                case 4://abril
                case 6://junio
                case 9://sptiembre
                case 11:/*noviembre*/if(dia>=1 && dia<=30)
                                     {
                                           //printf("   | Fecha correcta.\n");
                                            retorno=0;
                                     }
                                     else
                                     {
                                            //printf("   | Fecha incorrecta.\n");
                                            retorno=-1;
                                     }
                                     break;
                case 2:/*febrero*/if((anio%4==0 && anio%100!=0) || anio%400==0)
                                  {
                                      if (dia>=1 && dia<=29)
                                      {
                                            //printf("   | Fecha correcta.\n");
                                            retorno=0;
                                      }
                                       else
                                      {
                                            //printf("   | Fecha incorrecta.\n");
                                            retorno=-1;
                                      }
                                  }
                                  else
                                  {
                                     if (dia>=1 && dia<=28)
                                      {
                                            //printf("   | Fecha correcta.\n");
                                            retorno=0;
                                      }
                                       else
                                      {
                                            //printf("   | Fecha incorrecta.\n");
                                            retorno=-1;
                                      }
                                  }

            }
        }
        else
        {
            //printf("   | Fecha incorrecta.\n");
            retorno=-1;
        }
    }
    else
    {
        //printf("   | Fecha incorrecta.\n");
        retorno=-1;
    }

    return retorno;
}

//---------------------------------------------------PUNTO I MOSTRAR TRABAJOS---------------------------

int cargarMarcaMoto(char marca[],int id,eMoto moto[],int tamMotos)
{
    int retorno=0;
    for(int i=0;i<tamMotos;i++)
    {
        if(moto[i].id==id)
        {
            strcpy(marca,moto[i].marca);
            retorno=1;
        }
    }
    return retorno;
}

int cargarDescripcionServicio(char descripcion[],int id,eServicio servicio[],int tamServicio)
{
    int retorno=0;
    for(int i=0;i<tamServicio;i++)
    {
        if(servicio[i].id==id)
        {
            strcpy(descripcion,servicio[i].descripcion);
            retorno=1;
        }
    }
    return retorno;
}

void mostrarTrabajo(eTrabajo trabajos,eMoto moto[],int tamMotos,eServicio servicios[],int tamServicios)
{
    char marcaMoto[20];
    char descripcionServicio[20];

    cargarMarcaMoto(marcaMoto,trabajos.idMoto,moto,tamMotos);
    cargarDescripcionServicio(descripcionServicio,trabajos.idServicio,servicios,tamServicios);
    printf("   |    %02d           %02d      %10s       %15s         %02d/%02d/%d\n",trabajos.id,trabajos.idMoto,marcaMoto,descripcionServicio,trabajos.fecha.dia,trabajos.fecha.mes,trabajos.fecha.anio);
}

void mostrarTrabajos(eTrabajo trabajos[],int tamTrabajos,eMoto motos[],int tamMoto,eServicio servicios[],int tamServicios)
{
    int flag=0;
    //system("cls");
    printf("   |-----------------------------------------------------|\n");
    printf("   |--------------------Lista Trabajos-------------------|\n");
    printf("   |  Id-Trabajo    Id-Moto    Marca-Moto     Descripcion-Servicio    Fecha-Trabajo\n");
    for(int i=0; i<tamTrabajos; i++)
    {
        if(trabajos[i].isEmpty==0)
        {
            mostrarTrabajo(trabajos[i],motos,tamMoto,servicios,tamServicios);
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("\n   |---------No hay servicios que listar-----------\n");
    }
}

void hardcodearTrabajos(eTrabajo trabajo[],int tamTrabajos)
{
    for(int i=0;i<tamTrabajos;i++)
    {
        trabajo[i].id=idTrabajos[i];
        trabajo[i].idMoto=idMotos[i];
        trabajo[i].idServicio=idServicios[i];
        trabajo[i].fecha.dia=diasTrabajos[i];
        trabajo[i].fecha.mes=mesesTrabajos[i];
        trabajo[i].fecha.anio=aniosTrabajos[i];
        trabajo[i].isEmpty=0;
    }
}

//-----------------------------------INFORMES--------------------------------------
//--------------------------PUNTO J MOSTRAR MOTOS SEGUN COLOR----------------------
void informarMotosColor(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes)
{
    int flag=0;
    int color;
    //system ("cls");
    mostrarColores(colores,tamColores);
    printf("   |------------------------------------------------------------------|\n");
    printf("   |---------------------Listado Motos Por Color----------------------|\n");
    printf("   |     \n");
    printf("   | Ingrese el color: ");
    scanf("%d",&color);
    while(color<10000||color>10004)
            {
                printf("   | Error. Id-Color incorrecto.\n");
                printf("   | Ingrese el color: ");
                scanf("%d",&color);
            }
    printf("   |------------------------------------------------------------------|\n");
    printf("   |  id        Marca      Tipo          Color      Cilindrada     Cliente\n");
    for(int i=0; i<tamMotos; i++)
    {
        if(motos[i].isEmpty==0&&motos[i].idColor==color)
        {
            mostrarMoto(motos[i],tipos,tamTipos,colores,tamColores,clientes,tamClientes);
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("\n   |---------No hay motos de ese color que listar-----------\n");
    }
}

//--------------------------PUNTO K MOSTRAR MOTOS SEGUN TIPO----------------------
void informarMotosTipo(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes)
{
    int flag=0;
    int tipo;
    //system ("cls");
    mostrarTipos(tipos,tamTipos);
    printf("   |------------------------------------------------------------------|\n");
    printf("   |---------------------Listado Motos Por Tipo-----------------------|\n");
    printf("   |     \n");
    printf("   | Ingrese el tipo: ");
    scanf("%d",&tipo);
    while(tipo<1000||tipo>1003)
            {
                printf("   | Error. Id-Tipo incorrecto.\n");
                printf("   | Ingrese el tipo: ");
                scanf("%d",&tipo);
            }
    printf("   |------------------------------------------------------------------|\n");
    printf("   |  id        Marca      Tipo          Color      Cilindrada     Cliente\n");
    for(int i=0; i<tamMotos; i++)
    {
        if(motos[i].isEmpty==0&&motos[i].idTipo==tipo)
        {
            mostrarMoto(motos[i],tipos,tamTipos,colores,tamColores,clientes,tamClientes);
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("\n   |---------No hay motos de ese tipo que listar-----------\n");
    }
}

//--------------------------PUNTO L MOSTRAR MOTOS MAYOR CILINDRADA----------------------
void informarMotosMayorCilindrada(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes)
{
    int flag=0;
    int mayorCilindrada=0;
    //system ("cls");
    printf("   |-----------------------------------------------------------------------------|\n");
    printf("   |---------------------Listado Motos de Mayor Cilindrada-----------------------|\n");
    printf("   |     \n");
    for(int i=0; i<tamMotos; i++)
    {
        if(motos[i].isEmpty==0||flag==0)
        {
            if(motos[i].cilindrada>mayorCilindrada || flag==0)
            {
                mayorCilindrada=motos[i].cilindrada;
                flag=1;
            }
        }
    }
    printf("   |  La mayor cilindrada es %d y pertenece a :\n",mayorCilindrada);
    printf("   |------------------------------------------------------------------|\n");
    printf("   |  id        Marca      Tipo          Color      Cilindrada     Cliente\n");
    for(int i=0;i<tamMotos;i++)
    {
        if(motos[i].isEmpty==0 && motos[i].cilindrada==mayorCilindrada)
        {
            mostrarMoto(motos[i],tipos,tamTipos,colores,tamColores,clientes,tamClientes);
        }
    }
}

//--------------------------PUNTO M MOSTRAR MOTOS POR TIPO----------------------
void informarMotosXTipo(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes)
{
    int flag;
    //system("cls");
    printf("   |-----------------------------------------------------------------------------|\n");
    printf("   |--------------------------Listado Motos por Tipo-----------------------------|\n");

    for(int t=0; t<tamTipos; t++)
    {
        flag=0;
        printf("   |------------------- Motos del tipo %s ------\n\n",tipos[t].descripcion);
        printf("   |  id        Marca      Tipo          Color      Cilindrada     Cliente\n");

        for(int e=0; e<tamMotos; e++)
        {
            if(motos[e].isEmpty==0 && motos[e].idTipo==tipos[t].id)
            {
                mostrarMoto(motos[e],tipos,tamTipos,colores,tamColores,clientes,tamClientes);
                flag=1;
            }
        }
        if(flag==0)
        {
            printf("\n   |---------No hay motos de este tipo que listar-----------\n");
        }
    }
}

//--------------------------PUNTO N MOSTRAR MOTOS SEGUN COLOR Y TIPO----------------------
void informarMotosXColorXTipo(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes)
{
    //int flag;
    int color;
    char nombreColor[20];
    char nombreTipo[20];
    int tipo;
    int contador=0;
    //system("cls");
    printf("   |-----------------------------------------------------------------------------|\n");
    printf("   |--------------------Listado Motos Segun Color y Tipo-------------------------|\n");

    mostrarColores(colores,tamColores);
    printf("   |     \n");
    printf("   | Ingrese el color: ");
    scanf("%d",&color);
    while(color<10000||color>10004)
            {
                printf("   | Error. Id-Color incorrecto.\n");
                printf("   | Ingrese el color: ");
                scanf("%d",&color);
            }
    mostrarTipos(tipos,tamTipos);
    printf("   |     \n");
    printf("   | Ingrese el tipo: ");
    scanf("%d",&tipo);
    while(tipo<1000||tipo>1003)
            {
                printf("   | Error. Id-Tipo incorrecto.\n");
                printf("   | Ingrese el tipo: ");
                scanf("%d",&tipo);
            }

    for(int t=0; t<tamMotos; t++)
    {
        //flag=0;
        if(motos[t].isEmpty==0 && motos[t].idTipo==tipo && motos[t].idColor==color)
        {
            contador++;
            //flag=1;
        }
    }
    cargarDescripcionTipo(nombreTipo,tipo,tipos,tamTipos);
    cargarDescripcionColor(nombreColor,color,colores,tamColores);
    printf("   | Hay %d motos de color %s y tipo %s.\n",contador,nombreColor,nombreTipo);
}


//--------------------------PUNTO O MOSTRAR COLORES MAS ELEGIDOS----------------------
void informarColorMasElegido(eMoto motos[],int tamMotos,eTipo tipos[],int tamTipos,eColor colores[],int tamColores,eCliente clientes[],int tamClientes)
{

}

