#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <math.h>
//#include <opencv2>
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<QMouseEvent>
#include <iostream>
#include <fstream>
///TOTO JE DEMO PROGRAM...AK SI HO NASIEL NA PC V LABAKU NEPREPISUJ NIC,ALE SKOPIRUJ SI MA NIEKAM DO INEHO FOLDERA
/// AK HO MAS Z GITU A ROBIS NA LABAKOVOM PC, TAK SI HO VLOZ DO FOLDERA KTORY JE JASNE ODLISITELNY OD TVOJICH KOLEGOV
/// NASLEDNE V POLOZKE Projects SKONTROLUJ CI JE VYPNUTY shadow build...
/// POTOM MIESTO TYCHTO PAR RIADKOV NAPIS SVOJE MENO ALEBO NEJAKY INY LUKRATIVNY IDENTIFIKATOR
/// KED SA NAJBLIZSIE PUSTIS DO PRACE, SKONTROLUJ CI JE MIESTO TOHTO TEXTU TVOJ IDENTIFIKATOR
/// AZ POTOM ZACNI ROBIT... AK TO NESPRAVIS, POJDU BODY DOLE... A NIE JEDEN,ALEBO DVA ALE BUDES RAD
/// AK SA DOSTANES NA SKUSKU

double getTickToMeter(unsigned short previousTick, unsigned short tick);
int misionCount = 0;
using namespace cv;
using namespace std;
bool isCorrectPosition = false;
bool isCorrectAngle = false;
bool misionComplete = false;
bool Run = false;
int M = 0;
bool misionPosibility = true;
bool startApp = true;
void mapCreator();
double xZelana = 5.25;//5.25
double yZelana = 2.30;//2.30
int positionX = 0;
int positionY = 0;
int grid[240][240] = {{0}};
int path[2][240] = {{0}};
int misie[3][240] = {{0}};
double mapKoty[53][2] = {{0,0},{574.5,0},{574.5,460.5},{550.5,460.5},{550.5,471.5},{55.5,471.5},{55.5,431.5},{0,431.5},{0,0},//obvod
                  {264.5,0},{264.5,154.5},{267.5,154.5},{267.5,0},//1
                  {264.5,151.5},{264.5,154.5},{110,154.5},{110,151.5},//2
                  {110,151.5},{110,309},{114,309},{114,154.5},//3
                  {110,154.5},{110,309},{114,309},{114,154.5},//4
                  {574.5,309},{574.5,312},{365.5,312},{365.5,309},//5
                  {423,309},{423,154.5},{420,154.5},{420,309},//6
                  {423,154.50},{477.5,154.5},{477.5,157.5},{423,157.5},//7
                  {365.5,312},{365.5,366.5},{368.5,366.5},{368.5,312},//8
                  {267.5,254.5},{267.5,309},{264.5,309},{264.5,254.5},//9
                  {267.5,309},{267.5,312},{213,312},{213,309},//10
                  {213,309},{213,254.5},{216,254.5},{216,309}};//11


PositionData positionDataStruct;
//int** generateJointCoords(skeleton skeleJoints, QRect rect)
//{
//    int** jointCoords = new int*[2];

//    int axis = 0; //  X

//    for (int joint = left_wrist; joint != last; joint++) {
//        jointCoords[axis] = new int[73];
//        jointCoords[axis][joint] = rect.width()-rect.width() * skeleJoints.joints[joint].x+rect.topLeft().x();
////        cout << jointCoords[axis][joint] << ' ';
//    }

//    axis = 1; // Y

//    for (int joint = left_wrist; joint != last; joint++) {
//        jointCoords[axis] = new int[73];
//        jointCoords[axis][joint] = (rect.height() *skeleJoints.joints[joint].y)+rect.topLeft().y();
//    }

//    return jointCoords;
//}


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
    if(skeleJoints.joints[left_wrist].y < skeleJoints.joints[nose].y && skeleJoints.joints[left_wrist].y > (0.0))
    {
        //cout << "L_UP";
        return true;
    }
    return false;
}

bool isGesture_RightAboveHead(skeleton skeleJoints)
{
    if(skeleJoints.joints[right_wrist].y < skeleJoints.joints[nose].y && skeleJoints.joints[right_wrist].y > (0.0))
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
        positionDataStruct.x = 0.5;
        positionDataStruct.y = 0.5;
        positionX = positionDataStruct.x * 100; // to  * 100 is to transform m into cm
        positionY = positionDataStruct.y * 100;

    //tu je napevno nastavena ip. treba zmenit na to co ste si zadali do text boxu alebo nejaku inu pevnu. co bude spravna
    ipaddress="127.0.0.1";//192.168.1.11toto je na niektory realny robot.. na lokal budete davat "127.0.0.1"
  //  cap.open("http://192.168.1.11:8000/stream.mjpg");
    ui->setupUi(this);
    datacounter=0;
  //  timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(getNewFrame()));
    actIndex=-1;
    useCamera1=false;
    activeMode=1;




    datacounter=0;


}

MainWindow::~MainWindow()
{
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


    // vypisi rozmerov grafickeho okna
//    cout<<"x1 = " << (int) rect.left() << endl;  //defaul is: 11
//    cout<<"y1 = " << (int) rect.top() << endl;  //defaul is: 128
//    cout<<"x2 = " << (int) rect.right() << endl;  //defaul is: 803
//    cout<<"y2 = " << (int) rect.bottom() << endl;  //defaul is: 611
//    cout<<"----------------------------" << endl;
//    cout<<"dlzka x = " << (int) rect.right() - rect.left() << endl;  //defaul is: 792
//    cout<<"dlzka y = " << (int) rect.bottom() - rect.top()<< endl;  //defaul is: 483
//    cout<<"----------------------------" << endl;

//    for(int x=8 + 11,y=5 + 128;
//        x <= ((int) rect.right() - 5) &&
//        y <= ((int) rect.bottom() - 5);
//        x+=8,y+=5){

//        x2 = x;
//        y2 = y;
////        cout<<"x2 = " << x2 << endl;  //defaul is: 803
////        cout<<"y2 = " << y2 << endl;  //defaul is: 611
//    }

    // main rectangle
    int x1 = 11;
    int y1 = 128;
    int x2 = rect.right();
    int y2 = rect.bottom();

    int width = x2 - x1;
    int height = y2 - y1;

    int width_ratio = width/8;
    int height_ratio = height/5;

    if(width_ratio > height_ratio)
    {
        width = height_ratio*8;
        x2 = x1 + width;
    }
    else
    {
        height = width_ratio*5;
        y2 = y1 + height;
    }


    rect.setCoords(11, 128, x2, y2);

    painter.drawRect(rect);

    // secondary rectangle
    int x11 = 11, y11 = 128, x22 = rect2.right(), y22 = rect2.bottom();

    int width2 = x22 - x11;
    int height2 = y22 - y11;

    int width_ratio2 = width2/8;
    int height_ratio2 = height2/5;

    if(width_ratio2 > height_ratio2)
    {
        width2 = height_ratio2*8;
        x22 = x11 + width2;
    }
    else
    {
        height2 = width_ratio2*5;
        y22 = y11 + height2;
    }

    rect2.setCoords(11, 128, x22, y22);

    painter.drawRect(rect2);





    cv::Mat clone_frame = frame[actIndex].clone();

    if(useCamera1==true && actIndex>-1)/// ak zobrazujem data z kamery a aspon niektory frame vo vectore je naplneny
    {
        //cv::Mat clone_frame = cv::Mat::clone(frame[actIndex]);
        cv::Mat clone_frame = frame[actIndex].clone();

//        std::cout<<actIndex<<std::endl;

        double f = 681.743;
        double Zd = -14.5;
        double Z = 21.0;
        double Yd = 11.5;

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

            if((360.0-copyOfLaserData.Data[k].scanAngle) < 32.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 0.0 || (360.0-copyOfLaserData.Data[k].scanAngle) <= 360.0 && (360.0-copyOfLaserData.Data[k].scanAngle) > 328.0)
            { // front
                if(D <= 50){
                    b = 0;
                    g = 0;
                    r = 255;
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
    //            else if((360.0-copyOfLaserData.Data[k].scanAngle) < 102.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 62.0)//132-32  left
            else if((360.0-copyOfLaserData.Data[k].scanAngle) < 132.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 32.0)
            {
                if(D <= 50){
                    b = 0;
                    g = 0;
                    r = 255;
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
    //                cv::circle(frame[actIndex], robot_center, 10,line_Color, 2);
                cv::ellipse(clone_frame, robot_center_left, Size(15, 15), 0, 90.0/*start angle*/, 270.0/*end angle*/, line_Color, 2);
            }
    //            else if((360.0-copyOfLaserData.Data[k].scanAngle) < 198.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 162.0)//228-132 back
            else if((360.0-copyOfLaserData.Data[k].scanAngle) < 228.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 132.0)
            {
                if(D <= 50){
                    b = 0;
                    g = 0;
                    r = 255;
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
    //                cv::circle(frame[actIndex], robot_center, 10,line_Color, 2);
                cv::ellipse(clone_frame, robot_center_back, Size(15, 15), 0, 0.0/*start angle*/, 180.0/*end angle*/, line_Color, 2);
            }
    //            else if((360.0-copyOfLaserData.Data[k].scanAngle) < 298.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 258.0)//328-228 right
            else if((360.0-copyOfLaserData.Data[k].scanAngle) < 328.0 && (360.0-copyOfLaserData.Data[k].scanAngle) >= 228.0)
            {
                if(D <= 50){
                    b = 0;
                    g = 0;
                    r = 255;
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
    //                cv::circle(frame[actIndex], robot_center, 10,line_Color, 2);
                cv::ellipse(clone_frame, robot_center_right, Size(15, 15), 0, 270.0/*start angle*/, 90.0+360/*end angle*/, line_Color, 2);
            }
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



        if(!misionPosibility && Run == false){
            cv::putText(clone_frame, "Imposible mision!", Point(25, 250), 2.0, 3.0, Scalar(0, 0, 255), 3, LINE_8);
            ui->Mision_start->setText("Mision Start");
        }
        else if(Run == false){
            cv::putText(clone_frame, "System pause!", Point(100, 250), 2.0, 3.0, Scalar(0, 0, 255), 3, LINE_8);
        }
        else{
            cv::putText(clone_frame, "", Point(100, 250), 2.0, 3.0, Scalar(0, 0, 255), 3, LINE_8);
        }
        if(misie[2][M] == 3 && misionComplete == true){
            cv::putText(clone_frame, "Som v cieli", Point(100, 250), 2.0, 3.0, Scalar(0, 0, 255), 3, LINE_8);
        }

    //        cout<<"stav baterie 1 = " << (int) robotdata.Battery << endl;


        QImage image = QImage((uchar*)clone_frame.data, clone_frame.cols, clone_frame.rows, clone_frame.step, QImage::Format_RGB888  );//kopirovanie cvmat do qimage
        painter.drawImage(rect,image.rgbSwapped());
    }
    if(useCamera1==true && actIndex>-1){
        if(updateLaserPicture==1) ///ak mam nove data z lidaru
        {
            updateLaserPicture=0;

            painter.setPen(pero);
            //teraz tu kreslime random udaje... vykreslite to co treba... t.j. data z lidaru
         //   std::cout<<copyOfLaserData.numberOfScans<<std::endl;
            for(int k=0;k<copyOfLaserData.numberOfScans/*360*/;k++)
            {

//                int diag = (sqrt(pow(((int) rect2.right() - (int) rect2.left()), 2) + pow(((int) rect2.bottom() - (int) rect2.top()), 2)));
//                diag = ((((int) (-diag / 100) * 5) + 100) / 5) + 15;
//                cout<<"diag = " << diag << endl;

                int dist=copyOfLaserData.Data[k].scanDistance/80;//diag //vzdialenost nahodne predelena 20 aby to nejako vyzeralo v okne.. zmen podla uvazenia
                int xp=rect2.width()-(rect2.width()/2+dist*2*sin((360.0-copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect2.topLeft().x(); //prepocet do obrazovky
                int yp=rect2.height()-(rect2.height()/2+dist*2*cos((360.0-copyOfLaserData.Data[k].scanAngle)*3.14159/180.0))+rect2.topLeft().y();//prepocet do obrazovky
                if(rect2.contains(xp,yp))//ak je bod vo vnutri nasho obdlznika tak iba vtedy budem chciet kreslit

                    painter.drawEllipse(QPoint(xp, yp),2,2);
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


//        isGesture_LeftFist(skeleJoints);
//        cout << "___";
//        isGesture_LeftPalm(skeleJoints);
//        cout << "___";
//        isGesture_RightFist(skeleJoints);
//        cout << "___";
//        isGesture_RightPalm(skeleJoints);
//        cout << "___";
//        isGesture_LeftAboveHead(skeleJoints);
//        cout << "___";
//        isGesture_RightAboveHead(skeleJoints);
//        cout << "    ";

        if(!isGesture_LeftAboveHead(skeleJoints) && !isGesture_RightAboveHead(skeleJoints))
        {
            robot.setRotationSpeed(0);
            robot.setTranslationSpeed(0);
        }
        else if(isGesture_RightAboveHead(skeleJoints) && isGesture_RightPalm(skeleJoints)) //RIGHT PALM UP -> TURN RIGHT
        {
            robot.setRotationSpeed(-3.14159/2);
        }
        else if(isGesture_LeftAboveHead(skeleJoints) && isGesture_LeftPalm(skeleJoints)) //LEFT PALM UP -> TURN LEFT
        {
            robot.setRotationSpeed(3.14159/2);
        }
        else if(isGesture_RightAboveHead(skeleJoints) && isGesture_RightFist(skeleJoints)) // RIGHT FIST UP -> FORWARD
        {
            robot.setTranslationSpeed(250);
        }
        else if(isGesture_LeftAboveHead(skeleJoints) && isGesture_LeftFist(skeleJoints)) // LEFT FIST UP -> BACKWARD
        {
            robot.setTranslationSpeed(-250);
        }

        //cout << "endl";
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
    if(startApp) {
            positionDataStruct.previousEncoderLeft = robotdata.EncoderLeft;
            positionDataStruct.previousEncoderRight = robotdata.EncoderRight;

            startApp = false;
        }

    static double firstGyro=robotdata.GyroAngle;
    positionDataStruct.fi_gyro=(robotdata.GyroAngle-firstGyro)/100.0;

    long double d = 0.23; // vzdialenost medzi kolesami v metroch
    double lengthRight = getTickToMeter(positionDataStruct.previousEncoderRight, robotdata.EncoderRight);
    double lengthLeft = getTickToMeter(positionDataStruct.previousEncoderLeft, robotdata.EncoderLeft);

    positionDataStruct.fi = (robotdata.GyroAngle/100.0);
    if((robotdata.GyroAngle/100.0) < 0){
        positionDataStruct.fi = positionDataStruct.fi + 360.0;
    }
    positionDataStruct.x += ((lengthRight + lengthLeft)/2) * cos(positionDataStruct.fi_gyro*PI/180.0);
    positionDataStruct.y += ((lengthRight + lengthLeft)/2) * sin(positionDataStruct.fi_gyro*PI/180.0);

    positionDataStruct.previousEncoderLeft = robotdata.EncoderLeft;
    positionDataStruct.previousEncoderRight = robotdata.EncoderRight;

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


    //cout << angle_at_left_wrist << endl;

//    if(angle_at_left_wrist >= 45)
//    {
//        cout << "Forward" << angle_at_left_wrist << endl;
//        robot.setTranslationSpeed(500);
//    }

///TU PISTE KOD... TOTO JE TO MIESTO KED NEVIETE KDE ZACAT,TAK JE TO NAOZAJ TU. AK AJ TAK NEVIETE, SPYTAJTE SA CVICIACEHO MA TU NATO STRING KTORY DA DO HLADANIA XXX

    //(((int) (positionDataStruct.x * 100.0)/5.0) == misie[0][M]) && (((int) (positionDataStruct.y * 100.0)/5.0) == misie[1][M])
        for(; (misie[2][M] != 0) && Run == true /*&& misionComplete == true*/; M++){
            for(int i = 0; i < 240; i++) { // vycistenie mapy
                for(int j = 0; j < 240; j++) {
                    grid[i][j] = 0;
                }
            }
            for(int i = 0; i < 2; i++) { // vycistenie path
                for(int j = 0; j < 240; j++) {
                    grid[i][j] = 0;
                }
            }
            cout << "misia:" << misie[2][M] << endl;
            cout << "MM:" << M << endl;
            mapCreator();

    //        ofstream myfile("C:/Users/Lenovo/OneDrive/Dokumenty/HMI/git/PerfeknaMapa_predRozsirenimStien.txt");
            ofstream myfile("C:/Users/Lenovo/OneDrive/Dokumenty/HMI/git/PerfeknaMapa_predRozsirenimStien.txt");
            if (myfile.is_open()){
                myfile << "Here is your map! " << endl;
                for (int i = 0; i < 240; i++)
                {
                    myfile << "" << endl;
                    for (int j = 0; j < 240; j++){
                        myfile << " " << grid[i][j];
                    }
                }
                myfile.close();
            }
            else cout << "Unable to open file";

            /*
             * Uloha 4
             */
            executeTask4(M); //tato uloha bi sa mala spustit len raz na zaciatku celeho procesu a potom uz len pracovat s maticou suradnic trasi ktoru vytvorila, ak bi sa spustila znou trasa a aj zaplavovy algoritmus bi sa prepisali v zmisle aktualnej pozicie robota ako startovacia pozicia.

            misionComplete == false;
        }

//        misionEzecute();//vykonanie misii

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

void MainWindow::misionEzecute(){
    double wanted_angle = atan2((misie[1][M] - positionDataStruct.y),(misie[0][M] - positionDataStruct.x))*(180/PI);
        if(wanted_angle < 0) {
            wanted_angle += 360;
        }
    if(!isCorrectAngle) {
        if(abs(wanted_angle - positionDataStruct.fi) < 1.0) {
            robot.setRotationSpeed(0);
            isCorrectAngle = true;
        } else {
            double rotation_speed = 3.14159/4;
            misionComplete == false;
        }
    }
    else{
        if(abs(misie[0][M] - (positionDataStruct.x * 100)) < 0.05 && abs(misie[1][M] - (positionDataStruct.y * 100)) < 0.05) {
           isCorrectPosition = true;
           robot.setTranslationSpeed(0);
        }
        else{
            robot.setTranslationSpeed(200);
            misionComplete == false;
        }
    }
}

void MainWindow::xecuteTask1(){
    if(misie[2][M] == 1){//prejazdovy
        //executeTask1()
        if(isCorrectPosition){
            misionComplete == true;
        }

    }
    else if(misie[2][M] == 2){//uloha
        //executeTask1()
        if(isCorrectPosition){
            if(abs(180.0 - positionDataStruct.fi) < 2.0)
            {
                robot.setRotationSpeed(0);
                misionComplete == true;
            }
            else{
                robot.setRotationSpeed(3.14159/4);
            }
        }

    }
    else if(misie[2][M] == 3){//cielovy
        //executeTask1()
        if(isCorrectPosition){
            misionComplete == true;

        }

    }
}

void MainWindow::executeTask4(int M){
//    int polomer_robota = 15;
    int matica = 0;

    for(int i = 0; i < 240; i++) { // rozsirenie hran stien
        for(int j = 0; j < 240; j++) {
            matica = grid[i][j];
            if(matica == 1){
                for(int k = 1; k <= 3; k++){ //k=3 lebo 5cm * 3 = 15 cm je polomer robota
                    for(int p = i - 3; p <= (i + 3); p++){
                        for(int n = j - 3; n <= (j + 3); n++){
                            if((p >= 0 && p < 240) && (n >= 0 && n < 240) && (grid[p][n] == 0)) // ak maica necacina od 0 a konci v 239 treva zmenit podmienky
                                grid[p][n] = 3;
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < 240; i++) { // rozsirenie hran stien cast 2
        for(int j = 0; j < 240; j++) {
            matica = grid[i][j];
            if(matica == 3){
                grid[i][j] = 1;
            }
        }
    }

    ofstream rozsirena("C:/Users/Lenovo/OneDrive/Dokumenty/HMI/git/PerfeknaMapa_poRozsireni.txt");
    if (rozsirena.is_open()){
        for (int i = 0; i < 240; i++)
        {
            rozsirena << "" << endl;
            for (int j = 0; j < 240; j++){
                rozsirena << " " << grid[i][j];
            }
        }
        rozsirena.close();
    }
    else cout << "Unable to open file";

    ofstream miss("C:/Users/Lenovo/OneDrive/Dokumenty/HMI/git/misie.txt");
    if (miss.is_open()){
        for (int i = 0; i < 3; i++)
        {
            miss << "" << endl;
            for (int j = 0; j < 240; j++){
                miss << " " << misie[i][j];
            }
        }
        miss.close();
    }
    else cout << "Unable to open file";

    cout << "M = " << M  << endl;
    cout << "gridx " << (int) (misie[0][M])/5  << endl;
    cout << "gridy " << (int) (misie[1][M])/5  << endl;

    grid[(int) (misie[0][M])/5][(int) (misie[1][M])/5] = 2; // position of finish
    int startX = (int) (positionDataStruct.x * 100.0)/5.0; // starting position x in cm
    int startY = (int) (positionDataStruct.y * 100.0)/5.0; // starting position y in cm


    for(int k = 2; !(grid[startX][startY] > 2); k++){ // zaplavovi algoritmus

     //   cout << "grid" << grid[startX][startY] << endl;

        for(int i = 0; i < 240; i++) {
            for(int j = 0; j < 240; j++) {
                matica = grid[i][j];
                if(matica == k){
                    if((i+1 >= 0 && i+1 < 240) && (j >= 0 && j < 240) && grid[i+1][j] == 0)
                        grid[i+1][j] = k+1;

                    if((i-1 >= 0 && i-1 < 240) && (j >= 0 && j < 240) && grid[i-1][j] == 0)
                        grid[i-1][j] = k+1;

                    if((i >= 0 && i < 240) && (j+1 >= 0 && j+1 < 240) && grid[i][j+1] == 0)
                        grid[i][j+1] = k+1;

                    if((i >= 0 && i < 240) && (j-1 >= 0 && j-1 < 240) && grid[i][j-1] == 0)
                        grid[i][j-1] = k+1;
                }                
            }
        }
        if(k >= 240){
            Run = false;
            misionPosibility = false;
        }
        else{
            misionPosibility = true;
        }
    }

    ofstream mapa("C:/Users/Lenovo/OneDrive/Dokumenty/HMI/git/PerfeknaMapa.txt");
    if (mapa.is_open()){
        for (int i = 0; i < 240; i++)
        {
            mapa << "" << endl;
            for (int j = 0; j < 240; j++){
                if(grid[i][j] < 10) mapa << "  ";
                else if(grid[i][j] < 100) mapa << " ";
                mapa << " " << grid[i][j];
            }
        }
        mapa.close();
    }
    else cout << "Unable to open file";

    path[0][0] = startX;
    path[1][0] = startY;
    //najst cestu od zaciatku po ciel (mnozina bodov)
    for(int controled_position = 0, i = startX, j = startY, k = 0, direction = 0; !(controled_position == 2); i = path[0][k], j = path[1][k]) {

        if((i+1 >= 0 && i+1 < 240) && grid[i+1][j] == (grid[i][j]) - 1){ // down
            if (direction == 1){
                path[0][k] = i + 1;
                path[1][k] = j;
                direction = 1;
            }
            else{
                path[0][k+1] = i + 1;
                path[1][k+1] = j;
                direction = 1;
                k++;
            }

            controled_position = grid[i+1][j];
        }
        else if((j+1 >= 0 && j+1 < 240) && grid[i][j+1] == (grid[i][j]) - 1){ // right
            if (direction == 2){
                path[0][k] = i;
                path[1][k] = j + 1;
                direction = 2;
            }
            else{
                path[0][k+1] = i;
                path[1][k+1] = j + 1;
                direction = 2;
                k++;
            }

            controled_position = grid[i][j+1];
        }
        else if((i-1 >= 0 && i-1 < 240) && grid[i-1][j] == (grid[i][j]) - 1){ //up
            if (direction == 3){
                path[0][k] = i - 1;
                path[1][k] = j;
                direction = 3;
            }
            else{
                path[0][k+1] = i - 1;
                path[1][k+1] = j;
                direction = 3;
                k++;
            }

            controled_position = grid[i-1][j];
        }
        else if((j-1 >= 0 && j-1 < 240) && grid[i][j-1] == (grid[i][j]) - 1){ // left
            if (direction == 4){
                path[0][k] = i;
                path[1][k] = j - 1;
                direction = 4;
            }
            else{
                path[0][k+1] = i;
                path[1][k+1] = j - 1;
                direction = 4;
                k++;
            }

            controled_position = grid[i][j-1];
        }
    }

 ofstream trasa("C:/Users/Lenovo/OneDrive/Dokumenty/HMI/git/Trasa.txt");
 if (trasa.is_open()){
     for (int i = 0; i < 2; i++)
     {
         trasa << "" << endl;
         for (int j = 0; j < 240; j++){
             trasa << " " << path[i][j];
         }
     }
     trasa.close();
 }
 else cout << "Unable to open file";
}

void mapCreator(){
    for(int i = 0; i < 52; i++){
        if(mapKoty[i][0] == mapKoty[i+1][0]){//suradnice x
            int j = 0;
            if(mapKoty[i][1] > mapKoty[i+1][1]){
                for(j = mapKoty[i][1]; j > mapKoty[i+1][1]; j--){
                    grid[(int) (mapKoty[i][0]) / 5][(int) j / 5] = 1;
                }
            }
            else{
                for(j = mapKoty[i][1]; j < mapKoty[i+1][1]; j++){
                    grid[(int) (mapKoty[i][0]) / 5][(int) j / 5] = 1;
                }
            }
        }
        else if(mapKoty[i][1] == mapKoty[i+1][1]){//suradnice y
            int j = 0;
            if(mapKoty[i][0] > mapKoty[i+1][0]){
                for(j = mapKoty[i][0]; j > mapKoty[i+1][0]; j--){
                    grid[(int) j / 5][(int) (mapKoty[i][1]) / 5] = 1;
                }
            }
            else{
                for(j = mapKoty[i][0]; j < mapKoty[i+1][0]; j++){
                    grid[(int) j / 5][(int) (mapKoty[i][1]) / 5] = 1;
                }
            }
        }
        else{//sikme steny
            if(i%4 != 0){
                double Dis = sqrt(pow((mapKoty[i+1][0] - mapKoty[i][0]), 2) + pow((mapKoty[i+1][1] - mapKoty[i][1]), 2));
                double Ux = (mapKoty[i+1][0] - mapKoty[i][0]) / Dis;
                double Uy = (mapKoty[i+1][1] - mapKoty[i][1]) / Dis;

                for (int l = 1; (sqrt(pow((((Ux * l) + mapKoty[i][0]) - mapKoty[i][0]), 2) + pow((((Uy * l) + mapKoty[i][1]) - mapKoty[i][1]), 2))) < Dis ; l++){
                    grid[(int) (((Ux * l) + mapKoty[i][0]) / 5)][(int) (((Uy * l) + mapKoty[i][1]) / 5)] = 1;
                }
            }
        }
    }
}

double getTickToMeter(unsigned short previousTick, unsigned short tick) {
    double tickToMeter = 0.000085292090497737556558;
    double res = ((double)tick - (double)previousTick);
    if(res > 5000) {
        res = (long double)(tick-65536) - (long double)previousTick;
    } else if(res < -5000) {
        res = (long double)(tick+65536)- (long double)previousTick;
    }
    return tickToMeter * res;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    onMouseEvent(event->pos());
    event->accept();
    cout << "mousePressEvent" << endl;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){
    onMouseEvent(event->pos());
    event->accept();
    cout << "mouseDoubleClickEvent" << endl;
}

void MainWindow::onMouseEvent(const QPoint &pos){
    misie[0][misionCount] = pos.x();
    misie[1][misionCount] = pos.y();
    misie[2][misionCount] = activeMode;
    misionCount++;
    cout << "Pos-x" << pos.x() << endl;
    cout << "Pos-y" << pos.y() << endl;

    cout << "M = " << M  << endl;
    cout << "gridx " << (int) (misie[0][M])/5  << endl;
    cout << "gridy " << (int) (misie[1][M])/5  << endl;
}

void MainWindow::on_pushButton_2_clicked() //forward
{
    //pohyb dopredu
    robot.setTranslationSpeed(500);

}

void MainWindow::on_pushButton_3_clicked() //back
{
    robot.setTranslationSpeed(-250);

}

void MainWindow::on_pushButton_6_clicked() //left
{
robot.setRotationSpeed(3.14159/2);

}

void MainWindow::on_pushButton_5_clicked()//right
{
robot.setRotationSpeed(-3.14159/2);

}

void MainWindow::on_pushButton_4_clicked() //stop
{
    robot.setTranslationSpeed(0);

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




void MainWindow::on_pushButton_mode_clicked()
{
    if(activeMode == 1)
    {
        activeMode = 2;

        ui->pushButton_mode->setText("Mode uloha");
    }
    else if(activeMode == 2)
    {
        activeMode = 3;

        ui->pushButton_mode->setText("Mode ciel");
    }
    else if(activeMode == 3)
    {
        activeMode = 1;

        ui->pushButton_mode->setText("Mode prejazd");
    }
}


void MainWindow::on_Mision_start_clicked()
{
    if(Run==true)
    {
        Run=false;

        ui->Mision_start->setText("Mision Start");
    }
    else
    {
        Run=true;

        ui->Mision_start->setText("Mision Stop");
    }
}

