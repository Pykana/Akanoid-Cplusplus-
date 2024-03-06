/* LIBRERIAS */
#include <allegro.h>
#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include <winalleg.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

/* DEFINICION DE VENTANA*/
#define ancho 1080
#define alto 740

/* DEFINICION DE VARIABLES GLOBALES*/
#define velocidadInicial 3

/* OBJETOS */
MIDI    *MusicaInicio;
MIDI    *MusicaJuego;
SAMPLE  *SonidoInicioJuegoSelect;
SAMPLE  *SonidoInicioNivel;
SAMPLE  *SonidoLadrillo;
SAMPLE  *SonidoReboteBola;
SAMPLE  *SonidoRevivir;
SAMPLE  *SonidoVidaExtra;
SAMPLE  *SonidoReboteBolaPared;
SAMPLE  *SonidoVidaPerdida;
SAMPLE  *SonidoBoteBolaBase;
SAMPLE  *SonidoGameOver;

/* IMAGENES */
BITMAP  *buffer;
BITMAP  *logo;
BITMAP  *panel;
BITMAP  *recuadro;
BITMAP  *fondo1;
BITMAP  *fondo2;
BITMAP  *fondo3;
BITMAP  *fondo4;
BITMAP  *fondo5;
BITMAP  *gameover;
BITMAP  *lad1;
BITMAP  *lad2;
BITMAP  *lad3;
BITMAP  *lad4;
BITMAP  *lad5;
BITMAP  *lad6;
BITMAP  *lad7;
BITMAP  *ladd;
BITMAP  *base;
BITMAP  *base2;
BITMAP  *base3;
BITMAP  *base4;

/* BLOQUES */
using namespace std;

/* VARIABLES */
int     retardo = 100;
int     vidas =3;
int     level =1;
int     score=0;
int     dirY=-1;
int     dirX=1;
int     velocidad=3;
int     fondo =1;
bool    juegoiniciado=false;
bool    fin =false;
bool    nuevonivel=false;
bool    enjuego=false;
bool    muerte=false;
int     secuenciamuerte=1;
bool    musica=true;
bool    efectos=true;
bool    existearchivo=false;
int     higscore=0;
int     baseX=255;
int     bolaX=295;
int     bolaY=650;
int     mapa[63];
int     bordeizquiera;
int     bordederecha;
int     colBola;
int     filaBola;
int     elemento;
int     fila[]={20,50,80,110,140,170,200};


/* DECLARAR */
int inicializar ();
void inicilizarPantalla ();
void inicilizarSonidos();


/* FUNCIONES */
int inicializar (){

    allegro_init();
    install_keyboard();

    set_window_title("Arkanoid -By Pykana-");

    if(install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL)!=0 ){
        allegro_message("Error !  Inicializando sistema de sonido \n\n\n" , allegro_error);
        return 1;
    }

    inicilizarPantalla();
    return 0;
}

void inicilizarSonidos(){
    set_volume(230,209);

    MusicaInicio=load_midi("bgm/ark.mid");
    MusicaJuego=load_midi("bgm/Arkanoid.mid");

    SonidoInicioJuegoSelect=load_wav("bgm/InicioJuego.wav");
    SonidoInicioNivel=load_wav("bgm/inicioNivel.wav");
    SonidoLadrillo=load_wav("bgm/ladrilloRoto.wav");
    SonidoReboteBola=load_wav("bgm/rebotePelota.wav");
    SonidoVidaExtra=load_wav("bgm/vidaExtra.wav");
    SonidoVidaPerdida=load_wav("bgm/fallo.wav");
    SonidoGameOver=load_wav("bgm/SonidoGameOver.wav");
    SonidoRevivir=load_wav("bgm/revivir.wav");
    SonidoReboteBolaPared=load_wav("bgm/rebotaParedes.wav");

}

void inicilizarPantalla(){

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT,ancho,alto,0,0);
    buffer=create_bitmap(ancho,alto);

    logo=load_bitmap("img/logo.bmp", NULL);
    panel=load_bitmap("img/panel.bmp", NULL);
    recuadro=load_bitmap("img/recuadro.bmp", NULL);
    fondo1=load_bitmap("img/fondo1.bmp", NULL);
      fondo2=load_bitmap("img/fondo2.bmp", NULL);
        fondo3=load_bitmap("img/fondo3.bmp", NULL);
          fondo4=load_bitmap("img/fondo4.bmp", NULL);
            fondo5=load_bitmap("img/fondo5.bmp", NULL);
    lad1=load_bitmap("img/lad1.bmp", NULL);
     lad2=load_bitmap("img/lad2.bmp", NULL);
      lad3=load_bitmap("img/lad3.bmp", NULL);
       lad4=load_bitmap("img/lad4.bmp", NULL);
        lad5=load_bitmap("img/lad5.bmp", NULL);
         lad6=load_bitmap("img/lad6.bmp", NULL);
          lad7=load_bitmap("img/lad7.bmp", NULL);
           ladd=load_bitmap("img/ladd.bmp", NULL);
    gameover=load_bitmap("img/gameover.bmp", NULL);
    base=load_bitmap("img/base.bmp", NULL);
     base2=load_bitmap("img/base2.bmp", NULL);
      base3=load_bitmap("img/base3.bmp", NULL);
       base4=load_bitmap("img/base4.bmp", NULL);
}

/*  CODIGO */
int main (){

if(inicializar() ==1) return 1;

    while(!fin){
        if( key[KEY_ESC] )fin =true;
        if( key[KEY_ENTER]&& juegoiniciado == false ){

        }
    }

}
END_OF_MAIN()
