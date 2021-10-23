#include "interfaz.h"
#include "ui_interfaz.h"

Interfaz::Interfaz(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Interfaz)
{
    ui->setupUi(this);

    //----------Escenas----------
            //Principal
    menu_princi = new QGraphicsScene;
    menu_princi->setSceneRect(0,0,1260,650);
            //Nivel 1
    level_one = new QGraphicsScene;
            //Nivel 2
    level_two = new QGraphicsScene;
            //Nivel 3
    level_three = new QGraphicsScene;
            //BossFight
    bossfight = new QGraphicsScene;
    //----------------------------



    //----Crear objetos en escenas-----
    crearMenu();
    crearLevelOne();
    crearLevelTwo();
    crearLevelThree();
    //---------------------------------

    //----------Timer------------------
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    //---------------------------------

}

Interfaz::~Interfaz()
{
    delete ui;
}

void Interfaz::actualizar()
{
    int copy_y=jugador1->getY(),copy_x=jugador1->getX();
    jugador1->jump(0.1f);
    jugador1->setPos(jugador1->getX(),jugador1->getY());
    if(evaluarColisionSalto(jugador1))
    {
        jugador1->resetVX();
        jugador1->setposis(copy_x,copy_y);
        jugador1->setPos(jugador1->getX(),jugador1->getY());
    }
    else if(evaluarColisionJugador(jugador1)) //and veye<=-40)
    {
        timer->stop();
        jugador1->setposis(copy_x,copy_y);
        jugador1->setPos(jugador1->getX(),jugador1->getY());
        jugador1->resetVX();
        jugador1->resetVY();
    }
}

void Interfaz::crearMenu()//Crea y agrega los elementos del menu inicial
{
    //-------------------Imagenes---------------
    menu.append(new Imagenes(-11,0,1281,651,2)); // Background
    menu.append(new Imagenes(275,-100,700,400,1)); // Logo

    QList<Imagenes*>::iterator it;
    int cont = 0;
    for(it = menu.begin(); it!= menu.end(); it++)
    {
        menu_princi->addItem(menu.at(cont));
        cont++;
    }
    //------------------------------------------

    //-------------------Fondo------------------
//    fondo = new QMediaPlayer;
//    vw = new QVideoWidget;

//    fondo->setVideoOutput(vw);
//    fondo->setMedia();

//    vw->setGeometry(0,0,1280,720);
//    fondo->play();
//    menu_princi->addWidget(vw);
    //------------------------------------------

    //------------------Botones-----------------
    buttons.append(new botones(525,275,225,75,1));
    buttons.append(new botones(525,350,225,75,2));
    buttons.append(new botones(525,275,225,75,3));
    buttons.append(new botones(525,350,225,75,3));
    buttons.append(new botones(525,425,225,75,3));

    menu_princi->addItem(buttons.at(0));
    menu_princi->addItem(buttons.at(1));
    //------------------------------------------
    //Set Scene para el menu inicial
    ui->graphicsView->setScene(menu_princi);
}

void Interfaz::crearLevelOne()//Crea y agrega los elementos del nivel 1
{
    //-------------------Imagenes---------------
    imagenes_lvl1.append(new Imagenes(0,0,2500,1200,3)); // Background

    QList<Imagenes*>::iterator it;
    int cont = 0;
    for(it = imagenes_lvl1.begin(); it!= imagenes_lvl1.end(); it++)
    {
        level_one->addItem(imagenes_lvl1.at(cont));
        cont++;
    }
    //------------------------------------------

    //-----------------Se saca la base del mapa------------------
    ifstream archivo;
    string coorde,numero,int1,int2,int3,int4,digi;
    int ente1,ente2,ente3,ente4,len,conta;
    archivo.open(PATH_BASE_LVL1, ios::in);
    while(!archivo.eof())
    {
        if (archivo.eof())
            break;
        getline(archivo,coorde);
        len=coorde.length();
        conta=0;
        for (int i=0; i<=len;i++)
        {
            digi=coorde[i];
            if (digi!="," and digi[0]!='\000' )
            {
                numero+=digi;
            }
            else
            {
                conta+=1;
                if(conta==1)
                    int1+=numero;
                else if(conta==2)
                    int2+=numero;
                else if(conta==3)
                    int3+=numero;
                else if(conta==4)
                    int4+=numero;
                numero.erase();
            }
        }
        ente1=atoi(int1.c_str());
        ente2=atoi(int2.c_str());
        ente3=atoi(int3.c_str());
        ente4=atoi(int4.c_str());
        int1.erase();
        int2.erase();
        int3.erase();
        int4.erase();
        base_lvl1.append(new plataforma(ente1,ente2,ente3,ente4));
        level_one->addItem(base_lvl1.back());
    }
    archivo.close();
    //------------------------------------------------------------
}

void Interfaz::crearLevelTwo()//Crea y agrega los elementos del nivel 2
{
    //-------------------Imagenes---------------
    imagenes_lvl2.append(new Imagenes(0,0,2500,1200,4)); // Background

    QList<Imagenes*>::iterator it;
    int cont = 0;
    for(it = imagenes_lvl2.begin(); it!= imagenes_lvl2.end(); it++)
    {
        level_two->addItem(imagenes_lvl2.at(cont));
        cont++;
    }
    //------------------------------------------

    //-----------------Se saca la base del mapa------------------
    ifstream archivo;
    string coorde,numero,int1,int2,int3,int4,digi;
    int ente1,ente2,ente3,ente4,len,conta;
    archivo.open(PATH_BASE_LVL2, ios::in);
    while(!archivo.eof())
    {
        if (archivo.eof())
            break;
        getline(archivo,coorde);
        len=coorde.length();
        conta=0;
        for (int i=0; i<=len;i++)
        {
            digi=coorde[i];
            if (digi!="," and digi[0]!='\000' )
            {
                numero+=digi;
            }
            else
            {
                conta+=1;
                if(conta==1)
                    int1+=numero;
                else if(conta==2)
                    int2+=numero;
                else if(conta==3)
                    int3+=numero;
                else if(conta==4)
                    int4+=numero;
                numero.erase();
            }
        }
        ente1=atoi(int1.c_str());
        ente2=atoi(int2.c_str());
        ente3=atoi(int3.c_str());
        ente4=atoi(int4.c_str());
        int1.erase();
        int2.erase();
        int3.erase();
        int4.erase();
        base_lvl2.append(new plataforma(ente1,ente2,ente3,ente4));
        level_two->addItem(base_lvl2.back());
    }
    archivo.close();
    //------------------------------------------------------------
}

void Interfaz::crearLevelThree()//Crea y agrega los elementos del nivel 3
{
    //-------------------Imagenes---------------
    imagenes_lvl3.append(new Imagenes(0,0,2500,681,5)); // Background

    QList<Imagenes*>::iterator it;
    int cont = 0;
    for(it = imagenes_lvl3.begin(); it!= imagenes_lvl3.end(); it++)
    {
        level_three->addItem(imagenes_lvl3.at(cont));
        cont++;
    }
    //------------------------------------------

    //---------Se saca las paredes del mapa----------
    {
        ifstream archivo;
        string coorde,numero,int1,int2,int3,int4,digi;
        int ente1,ente2,ente3,ente4,len,conta;
        archivo.open(PATH_PARED_LVL3, ios::in);
        while(!archivo.eof())
        {
            if (archivo.eof())
                break;
            getline(archivo,coorde);
            len=coorde.length();
            conta=0;
            for (int i=0; i<=len;i++)
            {
                digi=coorde[i];
                if (digi!="," and digi[0]!='\000' )
                {
                    numero+=digi;
                }
                else
                {
                    conta+=1;
                    if(conta==1)
                        int1+=numero;
                    else if(conta==2)
                        int2+=numero;
                    else if(conta==3)
                        int3+=numero;
                    else if(conta==4)
                        int4+=numero;
                    numero.erase();
                }
            }
            ente1=atoi(int1.c_str());
            ente2=atoi(int2.c_str());
            ente3=atoi(int3.c_str());
            ente4=atoi(int4.c_str());
            int1.erase();
            int2.erase();
            int3.erase();
            int4.erase();
            pared_lvl3.append(new plataforma(ente1,ente2,ente3,ente4));
            level_three->addItem(pared_lvl3.back());
        }
        archivo.close();
    }
    //------------------------------------------------------------

    //-----------------Se saca la base del mapa------------------
    {
        ifstream archivo;
        string coorde,numero,int1,int2,int3,int4,digi;
        int ente1,ente2,ente3,ente4,len,conta;
        archivo.open(PATH_BASE_LVL3, ios::in);
        while(!archivo.eof())
        {
            if (archivo.eof())
                break;
            getline(archivo,coorde);
            len=coorde.length();
            conta=0;
            for (int i=0; i<=len;i++)
            {
                digi=coorde[i];
                if (digi!="," and digi[0]!='\000' )
                {
                    numero+=digi;
                }
                else
                {
                    conta+=1;
                    if(conta==1)
                        int1+=numero;
                    else if(conta==2)
                        int2+=numero;
                    else if(conta==3)
                        int3+=numero;
                    else if(conta==4)
                        int4+=numero;
                    numero.erase();
                }
            }
            ente1=atoi(int1.c_str());
            ente2=atoi(int2.c_str());
            ente3=atoi(int3.c_str());
            ente4=atoi(int4.c_str());
            int1.erase();
            int2.erase();
            int3.erase();
            int4.erase();
            base_lvl3.append(new plataforma(ente1,ente2,ente3,ente4));
            level_three->addItem(base_lvl3.back());
        }
        archivo.close();
    }
    //------------------------------------------------------------
}

bool Interfaz::evaluarColisionJugador(personaje *personaje)
{
    QList<plataforma*>::iterator it;

    for(it=base_lvl3.begin();it!=base_lvl3.end();it++)
    {
        if(personaje->collidesWithItem(*it))
        {
            return true;
        }
    }
    return false;
}

int Interfaz::evaluarColisionSalto(personaje *personaje)
{
    QList<plataforma*>::iterator it;

    for(it=pared_lvl3.begin();it!=pared_lvl3.end();it++)
    {
        if(personaje->collidesWithItem(*it))
        {
            return 1;
        }
    }
    return 0;
}

void Interfaz::validacion()
{

    ven2 = new QMainWindow();


    QString x = letra(":/imagenes/bug.ttf");
    QFont y(x);
    y.setPointSize(16);
    ven2->show();
}

void Interfaz::mousePressEvent(QMouseEvent *event)//Evento de clic con mouse
{
    //---------------Menu Principal--------------
    cont++;
    if(buttons.at(0)->get_Pressed())
    {
        if(cont==1)validacion();

        menu_princi->removeItem(buttons.at(0));
        menu_princi->removeItem(buttons.at(1));

        menu_princi->addItem(buttons.at(2));
        menu_princi->addItem(buttons.at(3));
        menu_princi->addItem(buttons.at(4));
    }
    else if(buttons.at(1)->get_Pressed())
    {
        //hacer botones para partidas (pensar luego)
    }





    //----------Partidas un jugador--------------USANDO PARA PROBAR NIVELES
    if(buttons.at(2)->get_Pressed())
    {
        jugador1 = new personaje(35,585);
        level_one->setSceneRect(0,0,1281,651);
        level_one->addItem(jugador1);
        ui->graphicsView->setScene(level_one); //cambio de escena para probar el lvl 1
    }
    if(buttons.at(3)->get_Pressed())
    {
        jugador1 = new personaje(35,585);
        level_two->setSceneRect(0,0,1281,651);
        level_two->addItem(jugador1);
        ui->graphicsView->setScene(level_two);//cambio de escena para probar el lvl 2
    }
    if(buttons.at(4)->get_Pressed())
    {
        jugador1 = new personaje(35,585);
        level_three->setSceneRect(0,0,1281,651);
        level_three->addItem(jugador1);
        ui->graphicsView->setScene(level_three);//cambio de escena para probar el lvl 3
    }
    //-------------------------------------------
}

QString Interfaz::letra(QString x)
{
    int id;
    id = QFontDatabase::addApplicationFont(x);

    QStringList letra = QFontDatabase::applicationFontFamilies(id);
    letra = letra.takeLast().split('.');

    return letra[0];
}


void Interfaz::keyPressEvent(QKeyEvent *i)
{
    //----------------Movimiento--------------------------
    if(i->key() == Qt::Key_D)
    {
        jugador1->setVX(7);
        jugador1->moveRight();
        if(evaluarColisionJugador(jugador1))
        {
            jugador1->setVX(-7);
            jugador1->moveLeft();
        }
    }
    else if(i->key() == Qt::Key_A)
    {
        jugador1->setVX(-7);
        jugador1->moveLeft();
        if(evaluarColisionJugador(jugador1))
        {
            jugador1->setVX(7);
            jugador1->moveRight();
        }
    }
    else if(i->key() == Qt::Key_W)
    {
        jugador1->resetVX();
        timer->start(16);
    }
    else if(i->key() == Qt::Key_S)
    {
        jugador1->resetVY();
        jugador1->moveDown();
        if(evaluarColisionJugador(jugador1))
            jugador1->moveUp();
    }
    //----------------------------------------------------
}
