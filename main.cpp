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

/* FUENTES */
DATAFILE *datafile;
FONT     *Arkarnoid;
FONT     *NTRS;

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

/* PANTALLAS */
int     pant1[63]={1,1,1,1,1,1,1,1,1,
                   2,2,2,2,2,2,2,2,2,
                   3,3,3,3,3,3,3,3,3,
                   4,4,4,4,4,4,4,4,4,
                   5,5,5,5,5,5,5,5,5,
                   6,6,6,6,6,6,6,6,6,
                   7,7,7,7,7,7,7,7,7};

int     pant2[63]={1,2,3,4,0,0,5,6,7,
                   5,6,7,0,0,1,2,3,4,
                   1,3,4,0,0,3,3,3,3,
                   4,4,4,4,5,5,5,5,5,
                   2,0,0,1,1,0,0,7,7,
                   3,4,5,6,7,1,2,0,0,
                   0,0,0,7,7,2,1,0,0};
/* *** */

/* DECLARACIONES*/
int inicializar ();
void inicilizarSonidos();
void inicilizarPantalla();
void armadoPantalla ();
void inicializarJuegoData();
void inicializarNivel();
void validacionBase();
void muestraLadrillo();
void nuevaBola();
void teclasSonido();
void jugar();
void ConfiguraNivel();
void RetomarJuego();

/* FUNCIONES */
/* DETECTAR TARJETA DE SONIDO, TECLADO E INICIALIZAR ALLEGRO */
int inicializar (){
    allegro_init();//INICIALIZAR ALLEGRO
    install_keyboard();//INICIALIZAR TECLADO
    set_window_title("Arkanoid -By Pykana-");//TITULO DE LA VENTANA DE JUEGO
    if(install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL)!=0 ){//DETECTAR TARJETA SONIDO
        allegro_message("Error !  Inicializando sistema de sonido \n\n\n" , allegro_error);//MENSAJE EN CASO DE ERROR
        return 1;//RETORNA 1 EN CASO DE ERRORES
    }
    /* CARGA DE FUENTES */
    datafile=load_datafile("font/Fuentes.dat");//CARGA DE FUENTES DESDE EL ARCHIVO GENERADO POR TTF2PCX Y GRABBER
    Arkarnoid=(FONT*)datafile[0].dat;//CARGA LA FUENTE DE LA POSICION 0 Y LO ASIGNA A ARKANOID
    NTRS=(FONT*)datafile[1].dat;//CARGA LA FUENTE DE LA POSICION 1 Y LO ASIGNA A NTRS
    /* **** */
    inicilizarPantalla();//INICIA LA CARGA DE IMAGENES
    inicilizarSonidos();//INICIA LA CARGA DE SONIDOS
    return 0;//RETORNA 0 EN CASO DE NO TENER ERRORES
}

/* CARGAR SONIDOS A MEMORIA */
void inicilizarSonidos(){
    set_volume(230,209);//INICIALIZAR VOLUMEN
    MusicaInicio=load_midi("bgm/ark.mid");//CARGAR ARCHIVO MIDI DE LA RUTA ESTABLECIDA
    MusicaJuego=load_midi("bgm/Arkanoid.mid");//CARGAR ARCHIVO MIDI DE LA RUTA ESTABLECIDA
    SonidoInicioJuegoSelect=load_wav("bgm/InicioJuego.wav");//CARGAR ARCHIVO WAV DE LA RUTA ESTABLECIDA
    SonidoInicioNivel=load_wav("bgm/inicioNivel.wav");//CARGAR ARCHIVO WAV DE LA RUTA ESTABLECIDA
    SonidoLadrillo=load_wav("bgm/ladrilloRoto.wav");//CARGAR ARCHIVO WAV DE LA RUTA ESTABLECIDA
    SonidoReboteBola=load_wav("bgm/rebotePelota.wav");//CARGAR ARCHIVO WAV DE LA RUTA ESTABLECIDA
    SonidoVidaExtra=load_wav("bgm/vidaExtra.wav");//CARGAR ARCHIVO WAV DE LA RUTA ESTABLECIDA
    SonidoVidaPerdida=load_wav("bgm/fallo.wav");//CARGAR ARCHIVO WAV DE LA RUTA ESTABLECIDA
    SonidoGameOver=load_wav("bgm/SonidoGameOver.wav");//CARGAR ARCHIVO WAV DE LA RUTA ESTABLECIDA
    SonidoRevivir=load_wav("bgm/revivir.wav");//CARGAR ARCHIVO WAV DE LA RUTA ESTABLECIDA
    SonidoReboteBolaPared=load_wav("bgm/rebotaParedes.wav");//CARGAR ARCHIVO WAV DE LA RUTA ESTABLECIDA
}

/* CARGA ELEMENTOS DE MEMORIA */
void inicilizarPantalla(){
    set_color_depth(32);//PROFUNDIDAD DE COLOR DE 32 BITS
    set_gfx_mode(GFX_AUTODETECT,ancho,alto,0,0);//ALLEGRO - AUTODETECTAR EL CONTROLADOR DE GRAFICOS Y DEFINIR LAS DIMENSIONES DE LA PANTALLA  (X,Y,0,0)  LOS OTROS DOS 0 SE USAN PARA SCROLLING , EN CASO DE QUERER AÑADIR PIXELES OCULTOS
    buffer=create_bitmap(ancho,alto);//CREACION DE BUFFER CON LAS DIMENSIONES ESTABLECIDAS
    logo=load_bitmap("img/logo.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
    panel=load_bitmap("img/panel.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
    recuadro=load_bitmap("img/recuadro.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
    gameover=load_bitmap("img/gameover.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
    /*FONDOS*/
    fondo1=load_bitmap("img/fondo1.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
      fondo2=load_bitmap("img/fondo2.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
        fondo3=load_bitmap("img/fondo3.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
          fondo4=load_bitmap("img/fondo4.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
            fondo5=load_bitmap("img/fondo5.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
    /*LADRILLOS*/
    lad1=load_bitmap("img/ladrillo1.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
     lad2=load_bitmap("img/ladrillo2.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
      lad3=load_bitmap("img/ladrillo3.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
       lad4=load_bitmap("img/ladrillo4.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
        lad5=load_bitmap("img/ladrillo5.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
         lad6=load_bitmap("img/ladrillo6.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
          lad7=load_bitmap("img/ladrillo7.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
           ladd=load_bitmap("img/ladrilloduro.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
    /*RECTANGULO BASE - JUGADOR*/
    base=load_bitmap("img/base.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
     base2=load_bitmap("img/base2.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
      base3=load_bitmap("img/base3.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
       base4=load_bitmap("img/base4.bmp", NULL);//CARGAR BITMAP DESDE LA RUTA ESTABLECIDA
}

/* MOSTRADO DE ELEMENTOS DE PANTALLA */
void armadoPantalla (){
    //clear_to_color(buffer,makecol(0,0,0));//CARGAR COLOR DE BUFFER PERO USANDO LA FUNCIONA MAKECOL PARA LOS COLORES EN LUGAR HEX
    clear_to_color(buffer,0x000000);//CARGAR COLOR DE BUFFER CON EL COLOR EN DATOS HEXADECIMAL
    draw_sprite(buffer,logo,615,5);//CARGAR SPRITE EN LA POSICION ESTABLECIDA       (X),  (Y)
    draw_sprite(buffer,panel,620,140);//CARGAR SPRITE EN LA POSICION ESTABLECIDA    (X),  (Y)
    /* TEXTO EN PANTALLA */
    textprintf_ex(panel,NTRS,170,23,makecol(0,0,0),makecol(0,0,0),"              ");//DIBUJAR EN PANEL , USAR LETRA NTRS, POSICION 130 (X), POSICION 3(Y), COLOR DE LETRA, COLOR DE FONDO, OBJETO A DIBUJAR
    textprintf_ex(panel,NTRS,170,23,makecol(255,0,0),makecol(0,0,0),"%d",level);//DIBUJAR EN PANEL , USAR LETRA NTRS, POSICION 130 (X), POSICION 3(Y), COLOR DE LETRA, COLOR DE FONDO, OBJETO A DIBUJAR (LEVE)
    textprintf_ex(panel,NTRS,200,85,makecol(0,0,0),makecol(0,0,0),"              ");//DIBUJAR EN PANEL , USAR LETRA NTRS, POSICION 130 (X), POSICION 3(Y), COLOR DE LETRA, COLOR DE FONDO, OBJETO A DIBUJAR
    textprintf_ex(panel,NTRS,200,85,makecol(255,0,0),makecol(0,0,0),"%d",score);//DIBUJAR EN PANEL , USAR LETRA NTRS, POSICION 130 (X), POSICION 3(Y), COLOR DE LETRA, COLOR DE FONDO, OBJETO A DIBUJAR (LEVE)
    textprintf_ex(panel,NTRS,170,150,makecol(0,0,0),makecol(0,0,0),"              ");//DIBUJAR EN PANEL , USAR LETRA NTRS, POSICION 130 (X), POSICION 3(Y), COLOR DE LETRA, COLOR DE FONDO, OBJETO A DIBUJAR
    textprintf_ex(panel,NTRS,170,150,makecol(255,0,0),makecol(0,0,0),"%d",vidas);//DIBUJAR EN PANEL , USAR LETRA NTRS, POSICION 130 (X), POSICION 3(Y), COLOR DE LETRA, COLOR DE FONDO, OBJETO A DIBUJAR (LEVE)
    /* *** */
    draw_sprite(buffer,recuadro,5,10);//CARGAR SPRITE EN LA POSICION ESTABLECIDA    (X),  (Y)
    draw_sprite(buffer,fondo1,11,16);//CARGAR SPRITE EN LA POSICION ESTABLECIDA     (X),  (Y)
    draw_sprite(buffer,base,baseX,660);//CARGAR SPRITE EN LA POSICION ESTABLECIDA   (X),  (Y)
    circlefill(buffer,bolaX,bolaY,10, makecol(124,250,16) );//CREAR CIRULO CON RELLENO EN BUFFER , CON DIMENSIONES (X), (Y), DIAMETRO, COLOR
    blit(buffer,screen,0,0,0,0, ancho,alto);//MANDAR A PANTALLA LAS COSAS CARGADAS A BUFFER , SCREEN (PUEDE IR OTRO BUFFER), COORDENADAS (0,0,0,0), ANCHO Y ALTO DE VENTANA
}

/* ESTADO DE NUEVO JUEGO */
void inicializarJuegoData(){
        level==1;//EN JUEGO NUEVO INICIA EN NIVEL 1
        fin=false;//RESETEA EL ESTADO FIN DE JUEGO A FALSE PARA NUEVA PARTIDA
}

/* CREACION DE ESCENARIO PARA JUEGO */
void inicializarNivel(){
    ConfiguraNivel();//ENTRA A LA CONFIGURACION DEL NIVEL - PANTALLA POR NIVEL
    RetomarJuego();//ENTRA A RETOMAR JUEGO - CAMBIO PARAMETROS A SU ESTADO BASE
    if(efectos){//VERIFICA EL ESTADO ACTUAL DE EFECTOS
        play_sample(SonidoInicioNivel,200,150,1000,0);//ARCHIVO SAMPLE, VOLUMEN, PAN, FRECUENCIA, LOOP
    }
}

/* CONFIGURACION DEL NIVEL */
void ConfiguraNivel(){
   for (int i=0;i<63;i++){//RECORRIDO DE CADA MAPA DE LADRILLOS
          switch(level){//VERIFICA EN QUE NIVEL SE ENCUENTRA EL JUGADOR
            case 1:  mapa[i]=pant1[i];//LEVEL 1 = CARGA PANTALLA1
            case 2:  mapa[i]=pant2[i];//LEVEL 2 = CARGA PANTALLA2
            default: mapa[i]=rand()%9;//LEVEL 3 EN ADELANTE PONES LADRILLOS ALEATORIOS
          }
    }
}

/* CONFIGURACION Y VALIDACION DEL ESTADO DEL JUEGO */
void RetomarJuego(){
    baseX=255;//CENTRA LADRIO BASE - JUGADOR
    bolaX=285;//CENTRA BOLA POSICION X
    bolaY=650;//CENTRA BOLA POSICION Y
    enjuego = false;//VUELVE AL ESTADO FALSE - EN ESPERA DEL JUGADOR
    nuevonivel= false;//DETIENE EL ARMADO
    armadoPantalla();//LLAMAR A ARMAR PANTALLA
}

/* VALIDACION DE LA BASE DEL JUGADOR */
void validacionBase(){

}

/* CONFIGURACION Y MOSTRADO DE LADRILLOS */
void muestraLadrillo(){

}

/* CREACION DE LA BOLA */
void nuevaBola(){

}

/* VALIDACION DE LA TECLAS DE SONIDO */
void teclasSonido(){
  if(musica){//VERIFICA EL ESTADO DE MUSICA
      if(key[KEY_DEL]){//SI PRESIONA DEL
        musica =false;//VALOR MUSICA A FALSE
        midi_pause();//PAUSA MUSICA
    }else{//SI NO
        musica=true;//VALOR MUSICA A TRUE
        midi_resume();//RESUME LA MUSICA
    }
  }
  if(efectos){//VERIFICA EL ESTADO DE MUSICA
      if(key[KEY_TAB]){//SI PRESIONA TAB
        musica=true;//VALOR EFECTOS A TRUE
    }else{//SI NO
        musica=true;//VALOR EFECTOS A TRUE
    }
  }
}

/*  INTERACCION CON EL JUEGO  */
void jugar(){
        inicializarJuegoData();//PONER LOS VALORES DEFAULT
        while(!key[KEY_ESC]&& !fin){//CICLO CONTINUO MIENTRAS EL JUGADOR JUEGA
            inicializarNivel();//CREAR NIVEL
                while(!nuevonivel && !key[KEY_ESC] && vidas>0){//VERIFICA SI EL USUARIO TERMINO EL NIVEL
                        if(key[KEY_SPACE]&& enjuego==false){//VALIDACION DE TECLAS EN CASO EL JUGADOR ESTE JUGANDO
                                enjuego=true;//INICIA EL JUEGO
                        }
                    validacionBase();//VERIFICA EL ESTADO ACTUAL DE LA BASE QUE MANEJA DEL JUGADOR - LADRILLO
                    if(enjuego){
                        muestraLadrillo();//VERIFICA EL ESTADO ACTUAL DE LOS BLOQUES CON LOS QUE INTERACTUA EL JGADOR
                        nuevaBola();//CREA UNA BOLA EN LA POSICION INICIAL
                    }
                    teclasSonido();//VERIFICA SI EL JUGADOR PRESIONO LA TECLA ESPECIFICA PARA MANEJAR EL SONIDO
                    armadoPantalla();//ARMADO DE PANTALLA EN TIEMPO REAL -- CUANDO EL JUGADOR INTERACTUE CON LOS BLOQUES
                }
        }
}

/*  INICIO */
int main (){
if(inicializar() == 1) return 1;//VERIFICAR EL SISTEMA DE SONIDO , EN CASO DE ERROR CIERRA TODO
    while(!fin){//CICLO CONTINUO MIENTRAS NO TERMINE EL JUEGO
        armadoPantalla();//CARGAR LOS DATOS A PANTALLA
        if( key[KEY_ESC] )fin =true;//EN CASO DE PRESIONAR ESC , SE CIERRA EL JUEGO
        if( key[KEY_ENTER]&& juegoiniciado == false ){//EN CASO DE PRESIONAR ENTER , INICIA EL JUEGO
           jugar();//LLAMAR A FUNCION PARA INICIAR JUEGO
        }
    }
}
END_OF_MAIN()
