#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <math.h>
//#include <opencv2>
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
///TOTO JE DEMO PROGRAM...AK SI HO NASIEL NA PC V LABAKU NEPREPISUJ NIC,ALE SKOPIRUJ SI MA NIEKAM DO INEHO FOLDERA
/// AK HO MAS Z GITU A ROBIS NA LABAKOVOM PC, TAK SI HO VLOZ DO FOLDERA KTORY JE JASNE ODLISITELNY OD TVOJICH KOLEGOV
/// NASLEDNE V POLOZKE Projects SKONTROLUJ CI JE VYPNUTY shadow build...
/// POTOM MIESTO TYCHTO PAR RIADKOV NAPIS SVOJE MENO ALEBO NEJAKY INY LUKRATIVNY IDENTIFIKATOR
/// KED SA NAJBLIZSIE PUSTIS DO PRACE, SKONTROLUJ CI JE MIESTO TOHTO TEXTU TVOJ IDENTIFIKATOR
/// AZ POTOM ZACNI ROBIT... AK TO NESPRAVIS, POJDU BODY DOLE... A NIE JEDEN,ALEBO DVA ALE BUDES RAD
/// AK SA DOSTANES NA SKUSKU

using namespace cv;
using namespace std;

bool safety_stop = false;
bool emergency_stop = false;

//CKobuki kobuki;

bool isGesture_RightFist(skeleton skeleJoints)
{
        if(skeleJoints.joints[right_thumb_tip].y > skeleJoints.joints[right_index_mcp].y && skeleJoints.joints[right_thumb_tip].y < skeleJoints.joints[right_index_tip].y
        /*&& skeleJoints.joints[right_thumb_tip].x < skeleJoints.joints[right_index_tip].x && skeleJoints.joints[right_thumb_tip].x < skeleJoints.joints[right_index_mcp].x*/)
    {

        if(skeleJoints.joints[right_index_mcp].y < skeleJoints.joints[right_index_tip].y)
        {
            if(skeleJoints.joints[right_middle_mcp].y < skeleJoints.joints[right_middle_tip].y)
            {
                if(skeleJoints.joints[right_ring_mcp].y < skeleJoints.joints[right_ring_tip].y)
                {
                    if(skeleJoints.joints[right_pinky_mcp].y < skeleJoints.joints[right_pinky_tip].y)
                    {
                        //cout << "R_FIST";
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool isGesture_RightPalm(skeleton skeleJoints)
{
    if(skeleJoints.joints[right_thumb_cmc].y > skeleJoints.joints[right_thumb_mcp].y && skeleJoints.joints[right_thumb_mcp].y > skeleJoints.joints[right_thumb_tip].y)
    {
        if(skeleJoints.joints[right_index_cmc].y > skeleJoints.joints[right_index_mcp].y && skeleJoints.joints[right_index_mcp].y > skeleJoints.joints[right_index_tip].y)
        {
            if(skeleJoints.joints[right_middle_cmc].y > skeleJoints.joints[right_middle_mcp].y && skeleJoints.joints[right_middle_mcp].y > skeleJoints.joints[right_middle_tip].y)
            {
                if(skeleJoints.joints[right_ring_cmc].y > skeleJoints.joints[right_ring_mcp].y && skeleJoints.joints[right_ring_mcp].y > skeleJoints.joints[right_ring_tip].y)
                {
                    if(skeleJoints.joints[right_pinky_cmc].y > skeleJoints.joints[right_pinky_mcp].y && skeleJoints.joints[right_pinky_mcp].y > skeleJoints.joints[right_pinky_tip].y)
                    {
                        //cout << "R_PALM";
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool isGesture_LeftFist(skeleton skeleJoints)
{
        if(skeleJoints.joints[left_thumb_tip].y > skeleJoints.joints[left_index_mcp].y && skeleJoints.joints[left_thumb_tip].y < skeleJoints.joints[left_index_tip].y
        /*&& skeleJoints.joints[left_thumb_tip].x > skeleJoints.joints[left_index_tip].x && skeleJoints.joints[left_thumb_tip].x > skeleJoints.joints[left_index_mcp].x*/)
    {

        if(skeleJoints.joints[left_index_mcp].y < skeleJoints.joints[left_index_tip].y)
        {
            if(skeleJoints.joints[left_middle_mcp].y < skeleJoints.joints[left_middle_tip].y)
            {
                if(skeleJoints.joints[left_ring_mcp].y < skeleJoints.joints[left_ring_tip].y)
                {
                    if(skeleJoints.joints[left_pinky_mcp].y < skeleJoints.joints[left_pinky_tip].y)
                    {
                        //cout << "L_FIST";
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool isGesture_LeftPalm(skeleton skeleJoints)
{
    if(skeleJoints.joints[left_thumb_cmc].y > skeleJoints.joints[left_thumb_mcp].y && skeleJoints.joints[left_thumb_mcp].y > skeleJoints.joints[left_thumb_tip].y)
    {
        if(skeleJoints.joints[left_index_cmc].y > skeleJoints.joints[left_index_mcp].y && skeleJoints.joints[left_index_mcp].y > skeleJoints.joints[left_index_tip].y)
        {
            if(skeleJoints.joints[left_middle_cmc].y > skeleJoints.joints[left_middle_mcp].y && skeleJoints.joints[left_middle_mcp].y > skeleJoints.joints[left_middle_tip].y)
            {
                if(skeleJoints.joints[left_ring_cmc].y > skeleJoints.joints[left_ring_mcp].y && skeleJoints.joints[left_ring_mcp].y > skeleJoints.joints[left_ring_tip].y)
                {
                    if(skeleJoints.joints[left_pinky_cmc].y > skeleJoints.joints[left_pinky_mcp].y && skeleJoints.joints[left_pinky_mcp].y > skeleJoints.joints[left_pinky_tip].y)
                    {
                        //cout << "L_PALM";
                        return true;
                    }
                }
            }
        }
    }

    return false;
}


bool isGesture_LeftAboveHead(skeleton skeleJoints)
{
    if(skeleJoints.joints[left_wrist].y < skeleJoints.joints[nose].y && skeleJoints.joints[left_wrist].y > 0.0)
    {
        //cout << "L_UP";
        return true;
    }
    return false;
}

bool isGesture_RightAboveHead(skeleton skeleJoints)
{
    if(skeleJoints.joints[right_wrist].y < skeleJoints.joints[nose].y && skeleJoints.joints[right_wrist].y > 0.0)
    {
        //cout << "R_UP";
        return true;
    }
    return false;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //tu je napevno nastavena ip. treba zmenit na to co ste si zadali do text boxu alebo nejaku inu pevnu. co bude spravna
    ipaddress="127.0.0.1";//127.0.0.1//192.168.1.11toto je na niektory realny robot.. na lokal budete davat "127.0.0.1"
  //  cap.open("http://192.168.1.11:8000/stream.mjpg");
    ui->setupUi(this);
    datacounter=0;

    actIndex=-1;
    useCamera1=false;

    datacounter=0;
}

MainWindow::~MainWindow()
{
    //video.release();

    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    ///prekreslujem obrazovku len vtedy, ked viem ze mam nove data. paintevent sa
    /// moze pochopitelne zavolat aj z inych dovodov, napriklad zmena velkosti okna
    painter.setBrush(Qt::black);//cierna farba pozadia(pouziva sa ako fill pre napriklad funkciu drawRect)
    QPen pero;
    pero.setStyle(Qt::SolidLine);//styl pera - plna ciara
    pero.setWidth(3);//hrubka pera -3pixely
    pero.setColor(Qt::green);//farba je zelena
    QRect rect;
    rect= ui->frame->geometry();//ziskate porametre stvorca,do ktoreho chcete kreslit
    rect.translate(0,15);
    QRect rect2;
    rect2= ui->frame_2->geometry();//ziskate porametre stvorca,do ktoreho chcete kreslit
    rect2.translate(0,15);

    // main rectangle
    int x1_0 = 11;
    int y1_0 = 128;
    int x2_0 = rect.right();
    int y2_0 = rect.bottom();

    int width = x2_0 - x1_0;
    int height = y2_0 - y1_0;

    int width_ratio = width/8;
    int height_ratio = height/5;

    if(width_ratio > height_ratio)
    {
        width = height_ratio*8;
        x2_0 = x1_0 + width;
    }
    else
    {
        height = width_ratio*5;
        y2_0 = y1_0 + height;
    }


    rect.setCoords(11, 128, x2_0, y2_0);

    painter.drawRect(rect);

    // secondary rectangle
    int x1_1 = 11, y1_1 = 128, x2_1 = rect2.right(), y2_1 = rect2.bottom();

    int width2 = x2_1 - x1_1;
    int height2 = y2_1 - y1_1;

    int width_ratio2 = width2/8;
    int height_ratio2 = height2/5;

    if(width_ratio2 > height_ratio2)
    {
        width2 = height_ratio2*8;
        x2_1 = x1_1 + width2;
    }
    else
    {
        height2 = width_ratio2*5;
        y2_1 = y1_1 + height2;
    }

    rect2.setCoords(11, 128, x2_1, y2_1);

    painter.drawRect(rect2);


    cv::Mat clone_frame = frame[actIndex].clone();

    if(useCamera1==true && actIndex>-1)/// ak zobrazujem data z kamery a aspon niektory frame vo vectore je naplneny
    {
        //cv::Mat clone_frame = cv::Mat::clone(frame[actIndex]);
        cv::Mat clone_frame = frame[actIndex].clone();

        double f = 681.743;
        double Zd = -14.5;
        double Z = 21.0;
        double Yd = 11.5;

        double smallest_D = 500;

        for(int k=0;k<copyOfLaserData.numberOfScans/*360*/;k++)
        {
            double D = copyOfLaserData.Data[k].scanDistance/10;
            double X = D*cos((360.0-copyOfLaserData.Data[k].scanAngle)*3.14159/180.0);
            double Y = D*sin((360.0-copyOfLaserData.Data[k].scanAngle)*3.14159/180.0);

            double xobr = (clone_frame.cols / 2) - ((f * Y) / (X + Zd));
            double yobr = (clone_frame.rows / 2) + ((f * (-Z + Yd)) / (X + Zd));

            Point center(xobr, yobr);
            Point robot_center(425, 400);
            Point robot_center_right(445, 400);
            Point robot_center_left(405, 400);
            Point robot_center_back(425, 420);
            Scalar robot_Color(255, 0, 0);

            int b,g,r = 0;

            if(D > 5.0 && D < smallest_D)
            {
                smallest_D = D;
            }
            if(smallest_D < 30 && !emergency_stop && !safety_stop)
            {
                on_pushButton_4_clicked();
                emergency_stop = true;
            }

            if((360.0-copyOfLaserData.Data[k].scanAngle) < 32.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 0.0 || (360.0-copyOfLaserData.Data[k].scanAngle) <= 360.0 && (360.0-copyOfLaserData.Data[k].scanAngle) > 328.0)
            { // front
                if(D <= 50){
                    b = 0;
                    g = 0;
                    r = 255;
                    if(!safety_stop && D > 10)
                    {
                        cv::putText(clone_frame, "   Caution!", Point(100, 250), 2.0, 3.0, Scalar(0, 0, 255), 3, LINE_8);
                    }
                }
                else if(D > 50 && D <= 100){
                    b = 0;
                    g = 200;
                    r = 255;
                }
                else if(D > 100){
                    b = 0;
                    g = 255;
                    r = 0;
                }

                Scalar line_Color(b, g, r);
                cv::circle(clone_frame, center, 1,line_Color, 2);
            }
            else if((360.0-copyOfLaserData.Data[k].scanAngle) < 132.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 32.0)
            {
                if(D <= 50){
                    b = 0;
                    g = 0;
                    r = 255;
                    if(!safety_stop && D > 10)
                    {
                        cv::putText(clone_frame, "   Caution!", Point(100, 250), 2.0, 3.0, Scalar(0, 0, 255), 3, LINE_8);
                    }
                }
                else if(D > 50 && D <= 100){
                    b = 0;
                    g = 200;
                    r = 255;
                }
                else if(D > 100){
                    b = 0;
                    g = 255;
                    r = 0;
                }

                Scalar line_Color(b, g, r);
                cv::circle(clone_frame, robot_center, 10,robot_Color, 2);
                cv::ellipse(clone_frame, robot_center_left, Size(15, 15), 0, 90.0/*start angle*/, 270.0/*end angle*/, line_Color, 2);
            }
            else if((360.0-copyOfLaserData.Data[k].scanAngle) < 228.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 132.0)
            {
                if(D <= 50){
                    b = 0;
                    g = 0;
                    r = 255;
                    if(!safety_stop && D > 10)
                    {
                        cv::putText(clone_frame, "   Caution!", Point(100, 250), 2.0, 3.0, Scalar(0, 0, 255), 3, LINE_8);
                    }
                }
                else if(D > 50 && D <= 100){
                    b = 0;
                    g = 200;
                    r = 255;
                }
                else if(D > 100){
                    b = 0;
                    g = 255;
                    r = 0;
                }

                Scalar line_Color(b, g, r);
                cv::circle(clone_frame, robot_center, 10,robot_Color, 2);
                cv::ellipse(clone_frame, robot_center_back, Size(15, 15), 0, 0.0/*start angle*/, 180.0/*end angle*/, line_Color, 2);
            }
            else if((360.0-copyOfLaserData.Data[k].scanAngle) < 328.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 228.0)
            {
                if(D <= 50){
                    b = 0;
                    g = 0;
                    r = 255;
                    if(!safety_stop && D > 10)
                    {
                        cv::putText(clone_frame, "   Caution!", Point(100, 250), 2.0, 3.0, Scalar(0, 0, 255), 3, LINE_8);
                    }
                }
                else if(D > 50 && D <= 100){
                    b = 0;
                    g = 200;
                    r = 255;
                }
                else if(D > 100){
                    b = 0;
                    g = 255;
                    r = 0;
                }

                Scalar line_Color(b, g, r);
                cv::circle(clone_frame, robot_center, 10,robot_Color, 2);
                cv::ellipse(clone_frame, robot_center_right, Size(15, 15), 0, 270.0/*start angle*/, 90.0+360/*end angle*/, line_Color, 2);
            }
        }

        if(smallest_D > 50 && emergency_stop)
        {
            //cout << "safe?" << smallest_D << endl;
            emergency_stop = false;
        }

        // Bateria graficka znacka.
        int bateria = ((robotdata.Battery / 2.55) * 0.3) + 805;
        if((robotdata.Battery / 2.55) <= 50.0 && (robotdata.Battery / 2.55) > 25.0){
            cv::rectangle(clone_frame, Point(805, 15), Point(bateria, 25), Scalar(0, 200, 255), 10, 8);
        }
        else if((robotdata.Battery / 2.55) <= 25.0){
            cv::rectangle(clone_frame, Point(805, 15), Point(bateria, 25), Scalar(0, 0, 255), 10, 8);
        }
        else{
            cv::rectangle(clone_frame, Point(805, 15), Point(bateria, 25), Scalar(0, 255, 0), 10, 8);
        }

        cv::rectangle(clone_frame, Point(800, 10), Point(840, 30), Scalar(255, 0, 0), 2, 8);
        cv::rectangle(clone_frame, Point(840, 18), Point(843, 22), Scalar(255, 0, 0), 2, 8);

        if(safety_stop || (emergency_stop && safety_stop))
        {
            cv::putText(clone_frame, "System pause!", Point(100, 250), 2.0, 3.0, Scalar(0, 0, 255), 3, LINE_8);
        }
        else
        {
            cv::putText(clone_frame, "", Point(100, 250), 2.0, 3.0, Scalar(0, 0, 255), 3, LINE_8);
        }

        QImage image = QImage((uchar*)clone_frame.data, clone_frame.cols, clone_frame.rows, clone_frame.step, QImage::Format_RGB888  );//kopirovanie cvmat do qimage
        painter.drawImage(rect,image.rgbSwapped());

        if(updateLaserPicture==1) ///ak mam nove data z lidaru
        {
            updateLaserPicture=0;

            painter.setPen(pero);
            //teraz tu kreslime random udaje... vykreslite to co treba... t.j. data z lidaru
            for(int k=-1;k<copyOfLaserData.numberOfScans/*360*/;k++)
            {
                int dist;
                int xp;
                int yp;

                if(k == -1)
                {
                    dist = 0;
                    xp = rect2.width()/2 + rect2.topLeft().x();
                    yp= rect2.height()/2 + rect2.topLeft().y();

                    pero.setColor("orange");
                    painter.setPen(pero);
                    painter.drawEllipse(QPoint(xp, yp),5,5);
                    pero.setColor(Qt::green);
                    painter.setPen(pero);
                }
                else
                {
                    dist=copyOfLaserData.Data[k].scanDistance/80;//diag //vzdialenost nahodne predelena 20 aby to nejako vyzeralo v okne.. zmen podla uvazenia
                    xp=rect2.width()-(rect2.width()/2+dist*2*sin((360.0-copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect2.topLeft().x(); //prepocet do obrazovky
                    yp=rect2.height()-(rect2.height()/2+dist*2*cos((360.0-copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect2.topLeft().y();//prepocet do obrazovky
                    if(rect2.contains(xp,yp))//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit
                    {
                        painter.drawEllipse(QPoint(xp, yp),2,2);
                    }
                }


            }
        }
    }

    if(updateSkeletonPicture==1 )
    {
        int joint_coords[73][2];

        painter.setPen(Qt::red);
        for(int joint = left_wrist; joint != last; joint++)
        {
            joint_coords[joint][0] = rect.width()-rect.width() * skeleJoints.joints[joint].x+rect.topLeft().x();
            joint_coords[joint][1] = (rect.height() *skeleJoints.joints[joint].y)+rect.topLeft().y();

            /*if(joint == left_index_cmc && rect.contains(joint_coords[joint][0],joint_coords[joint][1]))
                painter.drawEllipse(QPoint(joint_coords[joint][0], joint_coords[joint][1]),5,5);
            else */if(rect.contains(joint_coords[joint][0],joint_coords[joint][1]))
                painter.drawEllipse(QPoint(joint_coords[joint][0], joint_coords[joint][1]),2,2);
        }

        if(!safety_stop)
        {
            if(isGesture_RightAboveHead(skeleJoints) && isGesture_RightPalm(skeleJoints)) //RIGHT PALM UP -> TURN RIGHT
            {
                rotationspeed = -3.14159/6;
                //robot.setRotationSpeed(-3.14159/2);
                //cout << "right"<< endl;
            }
            else if(isGesture_LeftAboveHead(skeleJoints) && isGesture_LeftPalm(skeleJoints)) //LEFT PALM UP -> TURN LEFT
            {
                rotationspeed = 3.14159/6;
                //robot.setRotationSpeed(3.14159/2);
                //cout << "left"<< endl;
            }
            else if(isGesture_RightAboveHead(skeleJoints) && isGesture_RightFist(skeleJoints)) // RIGHT FIST UP -> FORWARD
            {
                forwardspeed = 100;
                //robot.setTranslationSpeed(250);
                //cout << "forward"<< endl;
            }
            else if(isGesture_LeftAboveHead(skeleJoints) && isGesture_LeftFist(skeleJoints)) // LEFT FIST UP -> BACKWARD
            {
                forwardspeed = -100;
                //robot.setTranslationSpeed(-250);
                //cout << "backward"<< endl;
            }
            else
            {
                rotationspeed = 0;
                forwardspeed = 0;
                //cout << "nope" << endl;
            }
        }
        else
        {
            rotationspeed = 0;
            forwardspeed = 0;
        }
    }
}


/// toto je slot. niekde v kode existuje signal, ktory je prepojeny. pouziva sa napriklad (v tomto pripade) ak chcete dostat data z jedneho vlakna (robot) do ineho (ui)
/// prepojenie signal slot je vo funkcii  on_pushButton_9_clicked
void  MainWindow::setUiValues(double robotX,double robotY,double robotFi)
{
//     ui->lineEdit_2->setText(QString::number(robotX));
//     ui->lineEdit_3->setText(QString::number(robotY));
//     ui->lineEdit_4->setText(QString::number(robotFi));
}

///toto je calback na data z robota, ktory ste podhodili robotu vo funkcii on_pushButton_9_clicked
/// vola sa vzdy ked dojdu nove data z robota. nemusite nic riesit, proste sa to stane
int MainWindow::processThisRobot(TKobukiData robotdata)
{
    ///tu mozete robit s datami z robota
    /// ale nic vypoctovo narocne - to iste vlakno ktore cita data z robota
    ///teraz tu posielam rychlosti na zaklade toho co setne joystick a vypisujeme data z robota(kazdy 5ty krat. ale mozete skusit aj castejsie). vyratajte si polohu. a vypiste spravnu
    /// tuto joystick cast mozete vklude vymazat,alebo znasilnit na vas regulator alebo ake mate pohnutky... kazdopadne, aktualne to blokuje gombiky cize tak
    if(forwardspeed==0 && rotationspeed!=0)
        robot.setRotationSpeed(rotationspeed);
    else if(forwardspeed!=0 && rotationspeed==0)
        robot.setTranslationSpeed(forwardspeed);
    else if((forwardspeed!=0 && rotationspeed!=0))
        robot.setArcSpeed(forwardspeed,forwardspeed/rotationspeed);
    else
        robot.setTranslationSpeed(0);

///TU PISTE KOD... TOTO JE TO MIESTO KED NEVIETE KDE ZACAT,TAK JE TO NAOZAJ TU. AK AJ TAK NEVIETE, SPYTAJTE SA CVICIACEHO MA TU NATO STRING KTORY DA DO HLADANIA XXX

    if(datacounter%5)
    {

        ///ak nastavite hodnoty priamo do prvkov okna,ako je to na tychto zakomentovanych riadkoch tak sa moze stat ze vam program padne
                // ui->lineEdit_2->setText(QString::number(robotdata.EncoderRight));
                //ui->lineEdit_3->setText(QString::number(robotdata.EncoderLeft));
                //ui->lineEdit_4->setText(QString::number(robotdata.GyroAngle));
                /// lepsi pristup je nastavit len nejaku premennu, a poslat signal oknu na prekreslenie
                /// okno pocuva vo svojom slote a vasu premennu nastavi tak ako chcete. prikaz emit to presne takto spravi
                /// viac o signal slotoch tu: https://doc.qt.io/qt-5/signalsandslots.html
        ///posielame sem nezmysli.. pohrajte sa nech sem idu zmysluplne veci
        emit uiValuesChanged(robotdata.EncoderLeft,11,12);
        ///toto neodporucam na nejake komplikovane struktury.signal slot robi kopiu dat. radsej vtedy posielajte
        /// prazdny signal a slot bude vykreslovat strukturu (vtedy ju musite mat samozrejme ako member premmennu v mainwindow.ak u niekoho najdem globalnu premennu,tak bude cistit bludisko zubnou kefkou.. kefku dodam)
        /// vtedy ale odporucam pouzit mutex, aby sa vam nestalo ze budete pocas vypisovania prepisovat niekde inde

    }
    datacounter++;

    return 0;

}

///toto je calback na data z lidaru, ktory ste podhodili robotu vo funkcii on_pushButton_9_clicked
/// vola sa ked dojdu nove data z lidaru
int MainWindow::processThisLidar(LaserMeasurement laserData)
{


    memcpy( &copyOfLaserData,&laserData,sizeof(LaserMeasurement));
    //tu mozete robit s datami z lidaru.. napriklad najst prekazky, zapisat do mapy. naplanovat ako sa prekazke vyhnut.
    // ale nic vypoctovo narocne - to iste vlakno ktore cita data z lidaru
    updateLaserPicture=1;
    update();//tento prikaz prinuti prekreslit obrazovku.. zavola sa paintEvent funkcia


    return 0;

}

///toto je calback na data z kamery, ktory ste podhodili robotu vo funkcii on_pushButton_9_clicked
/// vola sa ked dojdu nove data z kamery
int MainWindow::processThisCamera(cv::Mat cameraData)
{
    cameraData.copyTo(frame[(actIndex+1)%3]);//kopirujem do nasej strukury
    actIndex=(actIndex+1)%3;//aktualizujem kde je nova fotka
    updateLaserPicture=1;
    return 0;
}

///toto je calback na data zo skeleton trackera, ktory ste podhodili robotu vo funkcii on_pushButton_9_clicked
/// vola sa ked dojdu nove data z trackera
int MainWindow::processThisSkeleton(skeleton skeledata)
{

    memcpy(&skeleJoints,&skeledata,sizeof(skeleton));

    updateSkeletonPicture=1;
    return 0;
}
void MainWindow::on_pushButton_9_clicked() //start button
{

    forwardspeed=0;
    rotationspeed=0;
    //tu sa nastartuju vlakna ktore citaju data z lidaru a robota
    connect(this,SIGNAL(uiValuesChanged(double,double,double)),this,SLOT(setUiValues(double,double,double)));

    ///setovanie veci na komunikaciu s robotom/lidarom/kamerou.. su tam adresa porty a callback.. laser ma ze sa da dat callback aj ako lambda.
    /// lambdy su super, setria miesto a ak su rozumnej dlzky,tak aj prehladnost... ak ste o nich nic nepoculi poradte sa s vasim doktorom alebo lekarnikom...
    robot.setLaserParameters(ipaddress,52999,5299,/*[](LaserMeasurement dat)->int{std::cout<<"som z lambdy callback"<<std::endl;return 0;}*/std::bind(&MainWindow::processThisLidar,this,std::placeholders::_1));
    robot.setRobotParameters(ipaddress,53000,5300,std::bind(&MainWindow::processThisRobot,this,std::placeholders::_1));
    //---simulator ma port 8889, realny robot 8000
    robot.setCameraParameters("http://"+ipaddress+":8889/stream.mjpg",std::bind(&MainWindow::processThisCamera,this,std::placeholders::_1));
    robot.setSkeletonParameters("127.0.0.1",23432,23432,std::bind(&MainWindow::processThisSkeleton,this,std::placeholders::_1));
    ///ked je vsetko nasetovane tak to tento prikaz spusti (ak nieco nieje setnute,tak to normalne nenastavi.cize ak napr nechcete kameru,vklude vsetky info o nej vymazte)
    robot.robotStart();



    //ziskanie joystickov
    instance = QJoysticks::getInstance();


    /// prepojenie joysticku s jeho callbackom... zas cez lambdu. neviem ci som to niekde spominal,ale lambdy su super. okrem toho mam este rad ternarne operatory a spolocneske hry ale to tiez nikoho nezaujima
    /// co vas vlastne zaujima? citanie komentov asi nie, inak by ste citali toto a ze tu je blbosti
    connect(
        instance, &QJoysticks::axisChanged,
        [this]( const int js, const int axis, const qreal value) { if(/*js==0 &&*/ axis==1){forwardspeed=-value*300;}
            if(/*js==0 &&*/ axis==0){rotationspeed=-value*(3.14159/2.0);}}
    );
}
void MainWindow::on_pushButton_2_clicked() //draw
{
    //pohyb dopredu
    //robot.setTranslationSpeed(500);
    updateMapPicture = 1;
}


void MainWindow::on_pushButton_4_clicked() //stop
{
    if(safety_stop == false)
    {
        safety_stop = true;
        ui->pushButton_4->setText("RESET");
        ui->pushButton_4->setStyleSheet("QPushButton#pushButton_4 { background-color: white }");
    }
    else
    {
        safety_stop = false;
        ui->pushButton_4->setText("STOP");
        ui->pushButton_4->setStyleSheet("QPushButton#pushButton_4 { background-color: gray }");
    }
}




void MainWindow::on_pushButton_clicked()
{
    if(useCamera1==true)
    {
        useCamera1=false;

        ui->pushButton->setText("use camera");
    }
    else
    {
        useCamera1=true;

        ui->pushButton->setText("use laser");
    }
}

void MainWindow::getNewFrame()
{

}
