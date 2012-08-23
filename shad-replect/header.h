//Program by Andrei Ghenoiu
//Fall 2011 - Vermont Technical College - Computer Graphics
//contact me at andrei_stefang@yahoo.com if you have any questions

void FreeTexture( GLuint texture )
{
  glDeleteTextures( 1, &texture );
}
//loading the texture
GLuint LoadTexture( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    //The following code will read in our RAW file
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture ); //generate the texture with the loaded data
    glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture to it�s array
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    //Here we are setting the parameter to repeat the texture instead of clamping the texture
    //to the edge of our shape.
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data ); //free the texture
    return texture; //return whether it was successfull
}

void createStreet(int NWpointX, int NWpointZ, int SEpointX, int SEpointZ,GLuint texture){

     glBindTexture( GL_TEXTURE_2D, texture );
    glPushMatrix();

    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0);
    glVertex3f(NWpointX,.03,NWpointZ);
    glTexCoord2f(10.0,0.0);
    glVertex3f(SEpointX,.03,NWpointZ);
     glTexCoord2f(1.0,1.0);
    glVertex3f(SEpointX,.03,SEpointZ);
    glTexCoord2f(0.0,1.0);
    glVertex3f(NWpointX,.03,SEpointZ);

    glEnd();
    glPopMatrix();

}

void createCar(float NWpointX, float NWpointZ, float SEpointX, float SEpointZ, float height){
    //front texture
    GLuint front = LoadTexture( "car-front.raw", 256, 256 );
    //rear texture
    GLuint rear = LoadTexture( "car-rear.raw", 256, 256 );
    //profile texture
    GLuint profile = LoadTexture( "car-profile.raw", 256, 256 );

    glPushMatrix();
    glScalef(1,-1,1);
    glTranslatef(0,-height,0);

    glBindTexture( GL_TEXTURE_2D, rear );
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(0.0,0.0);
    glVertex3f(NWpointX,0,SEpointZ);
    glTexCoord2f(1.0,0.0);
    glVertex3f(SEpointX,0,SEpointZ);
    glTexCoord2f(1.0,1.0);
    glVertex3f(SEpointX,height,SEpointZ);
    glTexCoord2f(0.0,1.0);
    glVertex3f(NWpointX,height,SEpointZ);
    glEnd();

    glBindTexture( GL_TEXTURE_2D, profile );
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(NWpointX,0,NWpointZ);
    glTexCoord2f(1.0,0.0);
    glVertex3f(NWpointX,0,SEpointZ);
    glTexCoord2f(1.0,1.0);
    glVertex3f(NWpointX,height,SEpointZ);
    glTexCoord2f(0.0,1.0);
    glVertex3f(NWpointX,height,NWpointZ);
    glEnd();

    glBindTexture( GL_TEXTURE_2D, front );
    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(NWpointX,0,NWpointZ);
    glTexCoord2f(1.0,0.0);
    glVertex3f(SEpointX,0,NWpointZ);
    glTexCoord2f(1.0,1.0);
    glVertex3f(SEpointX,height,NWpointZ);
    glTexCoord2f(0.0,1.0);
    glVertex3f(NWpointX,height,NWpointZ);
    glEnd();

    glBindTexture( GL_TEXTURE_2D, profile );
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(SEpointX,0,NWpointZ);
    glTexCoord2f(1.0,0.0);
    glVertex3f(SEpointX,0,SEpointZ);
    glTexCoord2f(1.0,1.0);
    glVertex3f(SEpointX,height,SEpointZ);
    glTexCoord2f(0.0,1.0);
    glVertex3f(SEpointX,height,NWpointZ);
    glEnd();

    glBindTexture( GL_TEXTURE_2D, profile );
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex3f(NWpointX,-height/100,NWpointZ);
    glTexCoord2f(10.0,0.0);
    glVertex3f(SEpointX,-height/100,NWpointZ);
     glTexCoord2f(10.0,10.0);
    glVertex3f(SEpointX,-height/100,SEpointZ);
    glTexCoord2f(0.0,10.0);
    glVertex3f(NWpointX,-height/100,SEpointZ);
    glEnd();

    glPopMatrix();

    FreeTexture(front);
    FreeTexture(rear);
    FreeTexture(profile);
}
void createBuilding(float NWpointX, float NWpointZ, float SEpointX, float SEpointZ, float height, GLuint texture){


    glBindTexture( GL_TEXTURE_2D, texture );
    glPushMatrix();

    glBegin(GL_QUADS);

    glNormal3f(0,0,1);
    glTexCoord2f(0.0,0.0);
    glVertex3f(NWpointX,0,SEpointZ);
    glTexCoord2f(4.0,0.0);
    glVertex3f(SEpointX,0,SEpointZ);
    glTexCoord2f(4.0,4.0);
    glVertex3f(SEpointX,height,SEpointZ);
    glTexCoord2f(0.0,4.0);
    glVertex3f(NWpointX,height,SEpointZ);

    glNormal3f(-1,0,0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(NWpointX,0,NWpointZ);
    glTexCoord2f(4.0,0.0);
    glVertex3f(NWpointX,0,SEpointZ);
    glTexCoord2f(4.0,4.0);
    glVertex3f(NWpointX,height,SEpointZ);
    glTexCoord2f(0.0,4.0);
    glVertex3f(NWpointX,height,NWpointZ);

    glColor3f(1,0,0);
     glTexCoord2f(0.0,0.0);
    glVertex3f(NWpointX,0,NWpointZ);
    glTexCoord2f(4.0,0.0);
    glVertex3f(SEpointX,0,NWpointZ);
    glTexCoord2f(4.0,4.0);
    glVertex3f(SEpointX,height,NWpointZ);
    glTexCoord2f(0.0,4.0);
    glVertex3f(NWpointX,height,NWpointZ);

    glNormal3f(1,0,0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(SEpointX,0,NWpointZ);
    glTexCoord2f(4.0,0.0);
    glVertex3f(SEpointX,0,SEpointZ);
    glTexCoord2f(4.0,4.0);
    glVertex3f(SEpointX,height,SEpointZ);
    glTexCoord2f(0.0,4.0);
    glVertex3f(SEpointX,height,NWpointZ);

    glTexCoord2f(0.0,0.0);
    glVertex3f(NWpointX,height,NWpointZ);
    glTexCoord2f(100.0,0.0);
    glVertex3f(SEpointX,height,NWpointZ);
     glTexCoord2f(100.0,100.0);
    glVertex3f(SEpointX,height,SEpointZ);
    glTexCoord2f(0.0,100.0);
    glVertex3f(NWpointX,height,SEpointZ);

    glEnd();
    glPopMatrix();
}



void createPlane(GLuint texture){
     glBindTexture( GL_TEXTURE_2D, texture );
     glColor4f(0,0,.5,0.6);
    glPushMatrix();
    glColor4f(0,1,0,0.7);
   // glTranslatef(0,-2.5,0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(-10,0,10);
    glTexCoord2f(10,0);
    glVertex3f(10,0,10);
    glTexCoord2f(10,10);
    glVertex3f(10,0,-10);
    glTexCoord2f(0,10);
    glVertex3f(-10,0,-10);
    glEnd();
    glPopMatrix();
}

void createPool(){
    //glBindTexture( GL_TEXTURE_2D, texture );
    glColor4f(0,0,1,0.6);
    glPushMatrix();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(4,.01,4);
    glTexCoord2f(1,0);
    glVertex3f(7,.01,4);
    glTexCoord2f(1,1);
    glVertex3f(7,.01,-4);
    glTexCoord2f(0,1);
    glVertex3f(4,.01,-4);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(-4,.01,-2);
    glTexCoord2f(1,0);
    glVertex3f(-2,.01,-2);
    glTexCoord2f(1,1);
    glVertex3f(-2,.01,-4);
    glTexCoord2f(0,1);
    glVertex3f(-4,.01,-4);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(-4,.01,8);
    glTexCoord2f(1,0);
    glVertex3f(-2,.01,8);
    glTexCoord2f(1,1);
    glVertex3f(-2,.01,6);
    glTexCoord2f(0,1);
    glVertex3f(-4,.01,6);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(-7,.01,5);
    glTexCoord2f(1,0);
    glVertex3f(-5,.01,5);
    glTexCoord2f(1,1);
    glVertex3f(-5,.01,3);
    glTexCoord2f(0,1);
    glVertex3f(-7,.01,3);
    glEnd();
    glPopMatrix();
}


void reflect1(){
    glClearStencil(0); //clear the stencil buffer
    glClearDepth(1.0f);
    glClearColor (0.0,0.0,0.0,1);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //clear the buffers
    glLoadIdentity();

    glTranslatef(0, 0, -10);
//start
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); //disable the color mask
    glDepthMask(GL_FALSE); //disable the depth mask

    glEnable(GL_STENCIL_TEST); //enable the stencil testing

    glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); //set the stencil buffer to replace our next lot of data

}

void reflect2(){
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //enable the color mask
    glDepthMask(GL_TRUE); //enable the depth mask

    glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //set the stencil buffer to keep our next lot of data

    glDisable(GL_DEPTH_TEST); //disable depth testing of the reflection
    glPushMatrix();

    //flip the reflection vertically
    glTranslatef(0,0,0); //translate the reflection onto the drawing plane
    glScalef(1.0f, -1.0f, 1.0f);
}

