#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

GLboolean switchLight = false, ambLight = false, diffLight = false, specLight = false;
GLboolean switchLightDB = false, ambLightDB = false, diffLightDB = false, specLightDB = false;
double eyeX = 7.0, eyeY = 5, eyeZ = 38, refX = 13, refY = 0, refZ = 0;

static GLfloat dinh_KhoiLapPhuong[8][3] = { // dinh nghia mot mang 2 chieu luu tru tao do cac dinh cua khoi lap phuong
    {0.0, 0.0, 0.0}, // dinh 0
    {0.0, 0.0, 3.0}, // dinh 1
    {3.0, 0.0, 3.0}, // dinh 2
    {3.0, 0.0, 0.0}, // dinh 3
    {0.0, 3.0, 0.0}, // dinh 4
    {0.0, 3.0, 3.0}, // dinh 5
    {3.0, 3.0, 3.0}, // dinh 6
    {3.0, 3.0, 0.0}  // dinh 7
};

static GLubyte mat_KhoiLapPhuong[6][4] = {  // dinh nghia mang 2 chieu luu tru cac chi so nguyen tao thanh mat phang cua khoi lap phuong
    {0, 1, 2, 3}, // mat duoi
    {4, 5, 6, 7}, // mat tren
    {5, 1, 2, 6}, // mat truoc
    {0, 4, 7, 3}, // mat sau
    {2, 3, 7, 6}, // mat phai
    {1, 5, 4, 0}  // mat trai
};

static void getNormal3p // tinh vector phap tuyen cho mot mat phang 3 diem 
(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1; // tinh vector U
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1; // tinh vector V
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz; // tinh vector phap tuyen
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz); // dat vector phap tuyen vao bo dinh huong
}

void veKhoiLapPhuong(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX = 0, GLfloat ambY = 0, GLfloat ambZ = 0, GLfloat shine = 50) {
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS); // ve tu giac

    for (GLint i = 0; i < 6; i++) {
        getNormal3p(dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][0]][0], dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][0]][1], dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][0]][2],
            dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][1]][0], dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][1]][1], dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][1]][2],
            dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][2]][0], dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][2]][1], dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][2]][2]);
        glVertex3fv(&dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][0]][0]);
        glVertex3fv(&dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][1]][0]);
        glVertex3fv(&dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][2]][0]);
        glVertex3fv(&dinh_KhoiLapPhuong[mat_KhoiLapPhuong[i][3]][0]);
    }
    glEnd();
}

void veHinhCau(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 90) {
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere(3.0, 20, 16); // ve hinh cau
}

void veDaGiac(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine) {
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_POLYGON); // ve da giac
    glVertex2f(0, 0);
    glVertex2f(6, 0);
    glVertex2f(5.8, 1);
    glVertex2f(5.2, 2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3, 3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2, 1);

    glEnd();
}

void veDuongDaGiac(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine) {
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { shine };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_LINE_STRIP); // tap hop cac doan duoc noi voi nhau

    glVertex2f(6, 0);
    glVertex2f(5.8, 1);
    glVertex2f(5.2, 2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3, 3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2, 1);
    glVertex2f(0, 0);

    glEnd();
}

void phong() {
    // tuong ben trai
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(0.1, 4, 5);
    veKhoiLapPhuong(0.8, 0.7, 0.8941, 0.8, 0.8, 0.8941);
    glPopMatrix();
    // tuong ben phai
    glPushMatrix();
    glTranslatef(18, 0, 0);
    glScalef(0.1, 4, 5);
    veKhoiLapPhuong(0.8, 0.7, 0.8941, 0.8, 0.8, 0.8941);
    glPopMatrix();
    // tuong phia sau
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(6, 4, 0.1);
    veKhoiLapPhuong(0.8, 0.7, 0.8941, 0.8, 0.8, 0.8941);
    glPopMatrix();
    // tran nha
    glPushMatrix();
    glTranslatef(0, 11.7, 0);
    glScalef(6, 0.1, 5);
    veKhoiLapPhuong(0.8, 0.7, 0.8941, 0.8, 0.8, 0.8941);
    glPopMatrix();
    // nen nha
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(6, 0.1, 5);
    veKhoiLapPhuong(0.8509, 0.7608, 0.4471, 0.8509, 0.7608, 0.4471);
    glPopMatrix();

}

void Ban()
{
    // mat ban
    glPushMatrix();
    glTranslatef(5.6, 3, 5.01);
    glScalef(1, 0.1, 3);
    veKhoiLapPhuong(0.1764706, 0.4156863, 0.5176471, 0.1764706, 0.4156863, 0.5176471);
    glPopMatrix();

    // mat ban 1
    glPushMatrix();
    glTranslatef(8.6, 3, 5.01);
    glScalef(1, 0.1, 3);
    veKhoiLapPhuong(0.1764706, 0.4156863, 0.5176471, 0.1764706, 0.4156863, 0.5176471);
    glPopMatrix();

    // chan ban
    glPushMatrix();
    glTranslatef(8.3, 0, 5.01);
    glScalef(0.1, 1.5, 3);
    veKhoiLapPhuong(0.1764706, 0.4156863, 0.5176471, 0.1764706, 0.4156863, 0.5176471);
    glPopMatrix();
}

void ghe() {
    //Ghế 1
        //mặt ghế 
    glPushMatrix();
    glTranslatef(10.85, 1.5, 6.74);
    glScalef(0.6, 0.1, 0.6);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();


    //tựa lưng
    glPushMatrix();
    glTranslatef(12.35, 3, 6.74);
    glScalef(0.1, 0.2, 0.6);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân trái ghế 1
    glPushMatrix();
    glTranslatef(10.85, 0, 8.24);
    glScalef(0.1, 0.5, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân ghế 2
    glPushMatrix();
    glTranslatef(10.85, 0, 6.74);
    glScalef(0.1, 0.5, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân phải 1
    glPushMatrix();
    glTranslatef(12.35, 0, 8.24);
    glScalef(0.1, 1.2, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân phải ghế 2
    glPushMatrix();
    glTranslatef(12.35, 0, 6.74);
    glScalef(0.1, 1.2, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    //ghế 2
        //mặt ghế 
    glPushMatrix();
    glTranslatef(10.85, 1.5, 11.09);
    glScalef(0.6, 0.1, 0.6);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();


    //tựa lưng
    glPushMatrix();
    glTranslatef(12.35, 3, 11.09);
    glScalef(0.1, 0.2, 0.6);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân trái ghế 1
    glPushMatrix();
    glTranslatef(10.85, 0, 12.59);
    glScalef(0.1, 0.5, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân ghế 2
    glPushMatrix();
    glTranslatef(10.85, 0, 11.09);
    glScalef(0.1, 0.5, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân phải 1
    glPushMatrix();
    glTranslatef(12.35, 0, 12.59);
    glScalef(0.1, 1.2, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân phải ghế 2
    glPushMatrix();
    glTranslatef(12.35, 0, 11.09);
    glScalef(0.1, 1.2, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //ghế 3
        //mặt ghế 
    glPushMatrix();
    glTranslatef(4.29, 1.5, 6.74);
    glScalef(0.6, 0.1, 0.6);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();


    //tựa lưng
    glPushMatrix();
    glTranslatef(4.29, 3, 6.74);
    glScalef(0.1, 0.2, 0.6);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân trái ghế 1
    glPushMatrix();
    glTranslatef(5.79, 0, 8.24);
    glScalef(0.1, 0.5, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân ghế 2
    glPushMatrix();
    glTranslatef(5.79, 0, 6.74);
    glScalef(0.1, 0.5, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân phải 1
    glPushMatrix();
    glTranslatef(4.29, 0, 8.24);
    glScalef(0.1, 1.2, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân phải ghế 2
    glPushMatrix();
    glTranslatef(4.29, 0, 6.74);
    glScalef(0.1, 1.2, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
    //ghế 4
        //mặt ghế 
    glPushMatrix();
    glTranslatef(4.29, 1.5, 11.1);
    glScalef(0.6, 0.1, 0.6);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();


    //tựa lưng
    glPushMatrix();
    glTranslatef(4.29, 3, 11.1);
    glScalef(0.1, 0.2, 0.6);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân trái ghế 1
    glPushMatrix();
    glTranslatef(5.79, 0, 12.6);
    glScalef(0.1, 0.5, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân ghế 2
    glPushMatrix();
    glTranslatef(5.79, 0, 11.1);
    glScalef(0.1, 0.5, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân phải 1
    glPushMatrix();
    glTranslatef(4.29, 0, 12.6);
    glScalef(0.1, 1.2, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //chân phải ghế 2
    glPushMatrix();
    glTranslatef(4.29, 0, 11.1);
    glScalef(0.1, 1.2, 0.1);
    veKhoiLapPhuong(0.2, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
}

void mayTinh()
{
    // PC1
    // Man Hinh
    // Man
    glPushMatrix();
    glTranslatef(7.469999, 3.77, 6.1);
    glScalef(0.05, 0.5, 1);
    veKhoiLapPhuong(0.3490196, 0.3137255, 0.2784314, 0.3490196, 0.3137255, 0.2784314);
    glPopMatrix();
    // Gia do
    glPushMatrix();
    glTranslatef(7.62, 3.15, 7.427);
    glScalef(0.05, 0.5, 0.15);
    veKhoiLapPhuong(1, 0.8941177, 0.6862745, 1, 0.8941177, 0.6862745);
    glPopMatrix();
    // Ban Phim
    glPushMatrix();
    glTranslatef(6.27, 3.3, 6.43);
    glScalef(0.2, 0.01, 0.6);
    veKhoiLapPhuong(1, 0.6156863, 0.6156863, 1, 0.6156863, 0.6156863);
    glPopMatrix();
    // Chuot
    glPushMatrix();
    glTranslatef(6.4, 3.3, 8.481);
    glScalef(0.15, 0.05, 0.1);
    glutSolidSphere(1, 64, 64);
    glPopMatrix();

    // PC2
    // Man Hinh
    // Man
    glPushMatrix();
    glTranslatef(7.469999, 3.77, 10.63);
    glScalef(0.05, 0.5, 1);
    veKhoiLapPhuong(0.3490196, 0.3137255, 0.2784314, 0.3490196, 0.3137255, 0.2784314);
    glPopMatrix();
    // Gia do
    glPushMatrix();
    glTranslatef(7.62, 3.15, 11.957);
    glScalef(0.05, 0.5, 0.15);
    veKhoiLapPhuong(1, 0.8941177, 0.6862745, 1, 0.8941177, 0.6862745);
    glPopMatrix();
    // Ban Phim
    glPushMatrix();
    glTranslatef(6.27, 3.3, 11.13);
    glScalef(0.2, 0.01, 0.6);
    veKhoiLapPhuong(1, 0.6156863, 0.6156863, 1, 0.6156863, 0.6156863);
    glPopMatrix();
    // Chuot
    glPushMatrix();
    glTranslatef(6.4, 3.3, 13.4);
    glScalef(0.15, 0.05, 0.1);
    glutSolidSphere(1, 64, 64);
    glPopMatrix();

    // PC3
    // Man Hinh
    // Man
    glPushMatrix();
    glTranslatef(9.32, 3.77, 10.63);
    glScalef(0.05, 0.5, 1);
    veKhoiLapPhuong(0.3490196, 0.3137255, 0.2784314, 0.3490196, 0.3137255, 0.2784314);
    glPopMatrix();
    // Gia do
    glPushMatrix();
    glTranslatef(9.17, 3.15, 11.957);
    glScalef(0.05, 0.5, 0.15);
    veKhoiLapPhuong(1, 0.8941177, 0.6862745, 1, 0.8941177, 0.6862745);
    glPopMatrix();
    // Ban Phim
    glPushMatrix();
    glTranslatef(10.05, 3.3, 11.4);
    glScalef(0.2, 0.01, 0.6);
    veKhoiLapPhuong(1, 0.6156863, 0.6156863, 1, 0.6156863, 0.6156863);
    glPopMatrix();
    // Chuot
    glPushMatrix();
    glTranslatef(10.3, 3.3, 11);
    glScalef(0.15, 0.05, 0.1);
    glutSolidSphere(1, 64, 64);
    glPopMatrix();

    // PC4
    // Man Hinh
    // Man
    glPushMatrix();
    glTranslatef(9.32, 3.77, 6.04);
    glScalef(0.05, 0.5, 1);
    veKhoiLapPhuong(0.3490196, 0.3137255, 0.2784314, 0.3490196, 0.3137255, 0.2784314);
    glPopMatrix();
    // Gia do
    glPushMatrix();
    glTranslatef(9.17, 3.15, 7.417001);
    glScalef(0.05, 0.5, 0.15);
    veKhoiLapPhuong(1, 0.8941177, 0.6862745, 1, 0.8941177, 0.6862745);
    glPopMatrix();
    // Ban Phim
    glPushMatrix();
    glTranslatef(10.05, 3.3, 6.91);
    glScalef(0.2, 0.01, 0.6);
    veKhoiLapPhuong(1, 0.6156863, 0.6156863, 1, 0.6156863, 0.6156863);
    glPopMatrix();
    // Chuot
    glPushMatrix();
    glTranslatef(10.3, 3.3, 6.5);
    glScalef(0.15, 0.05, 0.1);
    glutSolidSphere(1, 64, 64);
    glPopMatrix();
}

void giasach() {
    // giá sách 1
        //canhtraitu
    glPushMatrix();
    glTranslatef(0.3, 0, 13.04);
    glScalef(0.3, 2.5, 0.05);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    //canhphaitu
    glPushMatrix();
    glTranslatef(0.3, 0, 5.39);
    glScalef(0.3, 2.5, 0.05);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    //ngan tu 1
    glPushMatrix();
    glTranslatef(0.3, 6.36, 5.54);
    glScalef(0.3, 0.02, 2.5);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    glPopMatrix();
    //ngan tu 2
    glPushMatrix();
    glTranslatef(0.3, 4.73, 5.54);
    glScalef(0.3, 0.02, 2.5);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    //ngan tu 3
    glPushMatrix();
    glTranslatef(0.3, 2.75, 5.54);
    glScalef(0.3, 0.02, 2.5);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    // giá sách 2
        //canhtraitu
    glPushMatrix();
    glTranslatef(17.1, 0, 12.36);
    glScalef(0.3, 2.5, 0.05);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    //canhphaitu
    glPushMatrix();
    glTranslatef(17.1, 0, 4.71);
    glScalef(0.3, 2.5, 0.05);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    //ngan tu 1
    glPushMatrix();
    glTranslatef(17.1, 6.66, 4.86);
    glScalef(0.3, 0.02, 2.5);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    glPopMatrix();
    //ngan tu 2
    glPushMatrix();
    glTranslatef(17.1, 5.03, 4.86);
    glScalef(0.3, 0.02, 2.5);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    //ngan tu 3
    glPushMatrix();
    glTranslatef(17.1, 3.05, 4.86);
    glScalef(0.3, 0.02, 2.5);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
}

void sach()
{
    // sach ben ke trai
    //sach1
    glPushMatrix();
    glTranslatef(0.3, 6.42, 12.89);
    glScalef(0.3, 0.3, 0.05);
    veKhoiLapPhuong(1.0, 0.8941177, 6862745, 1.0, 0.8941177, 6862745);
    glPopMatrix();
    //sach2
    glPushMatrix();
    glTranslatef(0.3, 6.48, 12.432);
    glRotatef(20, 1, 0, 0);
    glScalef(0.3, 0.3, 0.05);
    veKhoiLapPhuong(0.3839644, 0.8773585, 0.1688501, 0.3839644, 0.8773585, 0.1688501);
    glPopMatrix();
    //sach3
    glPushMatrix();
    glTranslatef(0.3, 6.506037, 12.179);
    glRotatef(25, 1, 0, 0);
    glScalef(0.3, 0.3, 0.05);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    //sach4
    glPushMatrix();
    glTranslatef(0.3, 6.506037, 11.93);
    glRotatef(30, 1, 0, 0);
    glScalef(0.3, 0.3, 0.05);
    veKhoiLapPhuong(0.6941177, 0.6196079, 0.5058824, 0.6941177, 0.6196079, 0.5058824);
    glPopMatrix();
    //sach5
    glPushMatrix();
    glTranslatef(0.3, 6.506037, 11.65);
    glRotatef(35, 1, 0, 0);
    glScalef(0.3, 0.3, 0.05);
    veKhoiLapPhuong(1, 0.6156863, 0.6156863, 1, 0.6156863, 0.6156863);
    glPopMatrix();

    //sach ngang 1
    glPushMatrix();
    glTranslatef(0.3, 4.79, 12.14);
    glScalef(0.3, 0.03, 0.3);
    veKhoiLapPhuong(0.8, 0.0, 0.0, 0.8, 0.0, 0.0);
    glPopMatrix();

    //sach ngang 2
    glPushMatrix();
    glTranslatef(0.3, 4.880001, 12.14);
    glScalef(0.3, 0.03, 0.3);
    veKhoiLapPhuong(1.0, 0.941, 0.608, 1.0, 0.941, 0.608);
    glPopMatrix();

    //sach ngang 3
    glPushMatrix();
    glTranslatef(0.3, 4.970001, 12.14);
    glScalef(0.3, 0.03, 0.3);
    veKhoiLapPhuong(0.0, 0.502, 0.0, 0.0, 0.502, 0.0);
    glPopMatrix();

    //sach ngang 4
    glPushMatrix();
    glTranslatef(0.3, 5.06, 12.14);
    glScalef(0.3, 0.03, 0.3);
    veKhoiLapPhuong(0.1, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    // sach ben ke phai
    //sach1
    glPushMatrix();
    glTranslatef(17.1, 6.720001, 12.21);
    glScalef(0.3, 0.3, 0.05);
    veKhoiLapPhuong(1.0, 0.8941177, 6862745, 1.0, 0.8941177, 6862745);
    glPopMatrix();
    //sach2
    glPushMatrix();
    glTranslatef(17.1, 6.780001, 11.752);
    glRotatef(20, 1, 0, 0);
    glScalef(0.3, 0.3, 0.05);
    veKhoiLapPhuong(0.3839644, 0.8773585, 0.1688501, 0.3839644, 0.8773585, 0.1688501);
    glPopMatrix();
    //sach3
    glPushMatrix();
    glTranslatef(17.1, 6.806038, 11.499);
    glRotatef(25, 1, 0, 0);
    glScalef(0.3, 0.3, 0.05);
    veKhoiLapPhuong(1, 1, 1, 1, 1, 1);
    glPopMatrix();
    //sach4
    glPushMatrix();
    glTranslatef(17.1, 6.806038, 11.25);
    glRotatef(30, 1, 0, 0);
    glScalef(0.3, 0.3, 0.05);
    veKhoiLapPhuong(0.6941177, 0.6196079, 0.5058824, 0.6941177, 0.6196079, 0.5058824);
    glPopMatrix();
    //sach5
    glPushMatrix();
    glTranslatef(17.1, 6.806038, 10.97);
    glRotatef(35, 1, 0, 0);
    glScalef(0.3, 0.3, 0.05);
    veKhoiLapPhuong(1, 0.6156863, 0.6156863, 1, 0.6156863, 0.6156863);
    glPopMatrix();

    //sach ngang 1
    glPushMatrix();
    glTranslatef(17.1, 5.090001, 11.46);
    glScalef(0.3, 0.03, 0.3);
    veKhoiLapPhuong(0.8, 0.0, 0.0, 0.8, 0.0, 0.0);
    glPopMatrix();

    //sach ngang 2
    glPushMatrix();
    glTranslatef(17.1, 5.180001, 11.46);
    glScalef(0.3, 0.03, 0.3);
    veKhoiLapPhuong(1.0, 0.941, 0.608, 1.0, 0.941, 0.608);
    glPopMatrix();

    //sach ngang 3
    glPushMatrix();
    glTranslatef(17.1, 5.270001, 11.46);
    glScalef(0.3, 0.03, 0.3);
    veKhoiLapPhuong(0.0, 0.502, 0.0, 0.0, 0.502, 0.0);
    glPopMatrix();

    //sach ngang 4
    glPushMatrix();
    glTranslatef(17.1, 5.360001, 11.46);
    glScalef(0.3, 0.03, 0.3);
    veKhoiLapPhuong(0.1, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();
}

void tham() {
    // Tham
    glPushMatrix();
    glTranslatef(1.33, 0.3, 2.58);
    glScalef(5, 0.01, 4);
    veKhoiLapPhuong(0.5, 0.0, 0.0, 0.5, 0.0, 0.0);
    glPopMatrix();
}

void dieuhoa() {

    glPushMatrix();
    glTranslatef(6.18, 9.7, 0.3);
    glScalef(2, 0.5, 0.3);
    veKhoiLapPhuong(0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
    glPopMatrix();

    //mo dieu hoa
    glPushMatrix();
    glTranslatef(7.02, 9.88, 1.2);
    glScalef(1.3, 0.15, 0.01);
    veKhoiLapPhuong(0.5, 0.8, 0.5, 0.5, 0.8, 0.5);
    glPopMatrix();

    //tem
    glPushMatrix();
    glTranslatef(11.33, 10.33, 1.2);
    glScalef(0.15, 0.15, 0.01);
    veKhoiLapPhuong(0.1, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();


}

void tranh() {
    //khung tranh1
    glPushMatrix();
    glTranslatef(6.58, 4.47, 0.3);
    glScalef(0.1, 1.5, 0.1);
    veKhoiLapPhuong(0.0, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //khung tranh2
    glPushMatrix();
    glTranslatef(11.38, 4.47, 0.3);
    glScalef(0.1, 1.5, 0.1);
    veKhoiLapPhuong(0.0, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //khung tranh3
    glPushMatrix();
    glTranslatef(6.88, 4.47, 0.3);
    glScalef(1.5, 0.1, 0.1);
    veKhoiLapPhuong(0.0, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //khung tranh4
    glPushMatrix();
    glTranslatef(6.88, 8.67, 0.3);
    glScalef(1.5, 0.1, 0.1);
    veKhoiLapPhuong(0.0, 0.1, 0.1, 0.1, 0.05, 0.05);
    glPopMatrix();

    //mat tranh4
    glPushMatrix();
    glTranslatef(6.88, 4.77, 0.3);
    glScalef(1.5, 1.3, 0.05);
    veKhoiLapPhuong(1.0, 0.941, 0.608, 1.0, 0.941, 0.608);
    glPopMatrix();
}

void bongDen()
{
    glPushMatrix(); // luu tru ma tran.
    glTranslatef(8.5, 11.5, 9.13); // phep dich chuyen
    glScalef(0.2, 0.1, 0.2); // phep co gian

    if (switchLight == true)
    {
        veHinhCau(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    }
    else
    {
        veHinhCau(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    }
    glPopMatrix(); // khoi phuc lai ma tran luu tru
}

void bongDenBan()
{
    //BongDen
    glPushMatrix(); // luu tru ma tran.
    glTranslatef(8.12, 6.5, 9.69); // phep dich chuyen
    glScalef(0.15, 0.1, 1); // phep co gian

    if (switchLightDB == true)
    {
        veKhoiLapPhuong(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    }
    else
    {
        veKhoiLapPhuong(0.4, 0.4, 0.4, 0.4, 0.4, 0.4);
    }
    glPopMatrix(); // khoi phuc lai ma tran luu tru

    // chan den
    glPushMatrix();
    glTranslatef(8.29, 3.01, 11.36);
    glScalef(0.05, 1.2, 0.1);
    veKhoiLapPhuong(0.3490196, 0.3137255, 0.2784314, 0.3490196, 0.3137255, 0.2784314);
    glPopMatrix();
}

void anhSang1() {
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat light_specular[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat light_position[] = { 9.91, 7.5, 12.4, 1.0 };

    if (ambLight == true)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
    }

    if (diffLight == true)
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
    }

    if (specLight == true)
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    }
    else
    {
        glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
    }
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void anhSangDenBan() {
    glPushMatrix();

    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat light_specular[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat light_position[] = { 8.12, 9.51, 9.69, 1.0 };
    GLfloat spot_direction[] = { 0, -1, 0 };
    GLfloat spot_cutoff = 70.0;

    if (ambLightDB == true)
    {
        glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    }
    else
    {
        glLightfv(GL_LIGHT1, GL_AMBIENT, no_light);
    }

    if (diffLightDB == true)
    {
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    }
    else
    {
        glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light);
    }

    if (specLightDB == true)
    {
        glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    }
    else
    {
        glLightfv(GL_LIGHT1, GL_SPECULAR, no_light);
    }
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction); // Thiết lập hướng của ánh sáng spotlight
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);
    glPopMatrix();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, 0, 1, 0);

    glEnable(GL_LIGHTING); // bat tinh nang chieu sang
    anhSang1();
    anhSangDenBan();
    bongDen();
    bongDenBan();
    phong();
    Ban();
    ghe();
    mayTinh();
    giasach();
    sach();
    tham();
    dieuhoa();
    tranh();
    glDisable(GL_LIGHTING);
    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
    case 'r': //reset diem nhin lai ban dau
        eyeX = 7.0; eyeY = 5; eyeZ = 38;
        refX = 13; refY = 0.0; refZ = 0.0;
        break;
    case 'w': // di chuyen camera len tren
        eyeY += 1.0;
        break;
    case 's': // di chuyen camera xuong duoi
        eyeY -= 1.0;
        break;
    case 'a': // di chuyen camera sang trai
        eyeX -= 1.0;
        break;
    case 'd': // di chuyen camera sang phai
        eyeX += 1.0;
        break;
    case 'o':  // nhin xa ra
        eyeZ += 1;
        break;
    case 'i': // nhin gan vao
        eyeZ -= 1;
        break;
    case 't': // di chuyen diem nhin len tren
        refY += 1.0;
        break;
    case 'g': // di chuyen diem nhin xuong duoi
        refY -= 1.0;
        break;
    case 'f': // di chuyen diem nhin sang trai
        refX -= 1.0;
        break;
    case 'h': // di chuyen diem nhin sang phai
        refX += 1.0;
        break;
    case '1': // bat tat den
        if (switchLight == false)
        {
            switchLight = true; ambLight = true; diffLight = true; specLight = true;
            glEnable(GL_LIGHT0);
            break;
        }
        else if (switchLight == true)
        {
            switchLight = false; ambLight = false; diffLight = false; specLight = false;
            glDisable(GL_LIGHT0);
            break;
        }
    case '2': // bat tat den ban
        if (switchLightDB == false)
        {
            switchLightDB = true; ambLightDB = true; diffLightDB = true; specLightDB = true;
            glEnable(GL_LIGHT1);
            break;
        }
        else if (switchLightDB == true)
        {
            switchLightDB = false; ambLightDB = false; diffLightDB = false; specLightDB = false;
            glDisable(GL_LIGHT1);
            break;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    std::cout << "Chuc nang: " << std::endl;
    std::cout << "1: bat den" << std::endl;
    std::cout << "w: di chuyen camera len tren" << std::endl;
    std::cout << "a: di chuyen camera sang phai" << std::endl;
    std::cout << "d: di chuyen camera sang trai" << std::endl;
    std::cout << "s: di chuyen camera xuong duoi" << std::endl;
    std::cout << "t: di chuyen goc nhin cua camera len tren " << std::endl;
    std::cout << "f: di chuyen goc nhin cua camera sang trai" << std::endl;
    std::cout << "h: di chuyen goc nhin cua camera sang phai" << std::endl;
    std::cout << "g: di chuyen goc nhin cua camera xuong duoi" << std::endl;
    std::cout << "i: nhin gan hon " << std::endl;
    std::cout << "o: nhin xa hon" << std::endl;
    std::cout << "r: reset diem nhin " << std::endl;


    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1024, 600);
    glutCreateWindow("PhongThuVien");


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    glutMainLoop();
    return 0;
}