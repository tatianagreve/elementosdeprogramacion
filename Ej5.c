#include<stdio.h>
#include <stdlib.h>
typedef struct{
                int codigo;
                char descripcion[51];
                int stock;
                }Tstock;
typedef struct{
                int codigo;
                int cantidad;
                }Tventa;

void GrabarArch(Tstock[],int);
int Busqueda (Tstock[],int,int);
void Mostrar1();
void Mostrar2();
int main()
{
    Tstock Vprod[5],aux;
    Tventa a;
    int cont=0,cod,cant,i,pos;
    FILE *pf;
    FILE *falt;
    Mostrar1();
    falt=fopen("Faltantes.dat","wb");
    if(falt==NULL)
    {
        printf("\nNo se pudo abrir el archivo.");
        exit(1);
    }
    pf=fopen("Stock.dat","rb");
    if(pf==NULL)
    {
        printf("\nNo se pudo abrir el archivo.");
        exit(1);
    }
    fread(&aux,sizeof(Tstock),1,pf);
    while(!feof(pf)&&cont<=5)
    {
        Vprod[cont]=aux;
        cont++;
        fread(&aux,sizeof(Tstock),1,pf);
    }
    fclose(pf);

    do{
        printf("\n Ingrese codigo del producto que desea comprar: ");
        scanf("%d",&cod);
        }while(cod<0);
    while(cod!=0)
    {
        pos=Busqueda(Vprod,5,cod);
        if(pos!=-1)
        {
            do{
                printf("\nIngrese la cantidad que desea: ");
                scanf("%d",&cant);
                }while(cant<0);
            if(cant<=Vprod[pos].stock)
            {
                Vprod[pos].stock-=cant;
            }
            else
            {
                i=cant-Vprod[pos].stock;
                Vprod[pos].stock=0;
                a.codigo=cod;
                a.cantidad=i;
                fwrite(&a,sizeof(Tventa),1,falt);
            }


        }
        do{
        printf("\n Ingrese codigo del producto que desea comprar: ");
        scanf("%d",&cod);
        }while(cod<0);
    }
    fclose(falt);
    GrabarArch(Vprod,5);
    Mostrar1();
    Mostrar2();
}
//////////////////////////////////////////////
void GrabarArch(Tstock V[],int ce)
{
    int i;
    FILE *pf;
    pf=fopen("Stock.dat","wb");
    if(pf==NULL)
    {
        printf("No se pudo abrir el archivo2");
        exit(1);
    }
    for(i=0;i<ce;i++)
        fwrite(&V[i],sizeof(Tstock),1,pf);
    fclose(pf);
}
/////////////////////////////////////
void Mostrar1()
{   Tstock prod;
    FILE *pf;
    pf=fopen("Stock.dat","rb");
    if(pf==NULL)
    {
        printf("\nFalla de apertura del archivo");
        exit(1);
    }
    printf("\nCODIGO\tSTOCK\tDESCRIPCION");

    fread(&prod,sizeof(Tstock),1,pf);
    while(!feof(pf))
    {
       printf("\n%d\t%d\t%s",prod.codigo,prod.stock,prod.descripcion);
       fread(&prod,sizeof(Tstock),1,pf);
    }
    fclose(pf);
}
////////////////////////////////////////////
void Mostrar2()
{   Tventa prod;
    FILE *pf;
    pf=fopen("Faltantes.dat","rb");
    if(pf==NULL)
    {
        printf("\nFalla de apertura del archivo");
        exit(1);
    }
    printf("\nCODIGO\tCANTIDAD");

    fread(&prod,sizeof(Tventa),1,pf);
    while(!feof(pf))
    {
       printf("\n%d\t%d",prod.codigo,prod.cantidad);
       fread(&prod,sizeof(Tventa),1,pf);
    }
    fclose(pf);
}

///////////////////////////////////////////////////

int Busqueda (Tstock p[],int a,int cod)
{
int i=0,pos=-1;
    while(i<a&&pos==-1)
    {
        if(cod==p[i].codigo)
        {
            pos=i;
        }
        else
        {
          i++;
        }

    }
    return pos;
}

//Este es un comentario de prueba
