#include <iostream>
#include<thread>
#include<windows.h>
using namespace std;

#include "Shader.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Camera.h"

void processinput(GLFWwindow* window);

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {
    0,1,3,
    1,2,3
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

float lastX;
float lastY;
bool firstMouse = TRUE;
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));

void mouse_callback(GLFWwindow* window,double xPos,double yPos);


int main() {
    
    

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //open GLFW Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
    if (window == NULL) {
        cout << "OPen Window fail" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window,mouse_callback);

    //Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        cout << "Init GLEW fail" << endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    /*glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);*/
   // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   /*****************↓↓↓开启Z缓存↓↓↓****************************************************/
    glEnable(GL_DEPTH_TEST); 
   /*****************↑↑↑开启Z缓存↑↑↑****************************************************/
    
    Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");



    //VAO创建和绑定
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);//VAO创建
    glBindVertexArray(VAO);//VAO绑上

    //VBO创建加绑定
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);*/

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int TexBufferA;
    glGenTextures(1,&TexBufferA);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,TexBufferA);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data=stbi_load("container.jpg",&width,&height,&nrChannels,0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "load image failed"<<endl;
    }
    stbi_image_free(data);

    
    stbi_set_flip_vertically_on_load(true);

    unsigned int TexBufferB;
    glGenTextures(1, &TexBufferB);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, TexBufferB);
    unsigned char* data2 = stbi_load("awesomeface.jpg", &width, &height, &nrChannels, 0);

    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "load image failed" << endl;
    }
    stbi_image_free(data2);

    //Instantiate Camera class
   // Camera camera(glm::vec3(0,0,3.0f),glm::vec3(0,0,0),glm::vec3(0,1.0f,0));
   

    glm::mat4 trans;
    //trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0, 0, 1));
   // trans = glm::scale(trans, glm::vec3(1.02f,1.02f,1.02f));
    glm::mat4 modelMat;
    

    modelMat = glm::rotate(modelMat,glm::radians(-55.0f),glm::vec3(1.0f,0,0));

    glm::mat4 viewMat;
    //viewMat=glm::translate(viewMat,glm::vec3(0,0,-3.0f));
    viewMat = camera.GetViewMatrix();

    glm::mat4 projMat;
    projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    
    while (!glfwWindowShouldClose(window))
    {
        //
        //trans = glm::rotate(trans, glm::radians(0.1f), glm::vec3(0, 0, 1));
       // modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(0.01f), glm::vec3(0.5f, 1.0f, 0.0f));
        
        //input
        processinput(window);

        //render
        glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBufferA);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, TexBufferB);
        glBindVertexArray(VAO);
       // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        viewMat = camera.GetViewMatrix();

        for (int i = 0; i < 10; i++) {
            glm::mat4 modelMat2;
            modelMat2 = glm::translate(modelMat2, cubePositions[i]);

            myShader->use();
            glUniform1i(glGetUniformLocation(myShader->ID,"ourTexture"),0);
            glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 3);
            //glUniformMatrix4fv(glGetUniformLocation(myShader->ID,"transform"),1,GL_FALSE,glm::value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glDrawArrays(GL_TRIANGLES,0,36);
        }

        
        

        //check,swap
        glfwSwapBuffers(window);
        glfwPollEvents();
        camera.UpdateCameraPos();
    }

    glfwTerminate();
    return 0;
}


void processinput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.speedZ=1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.speedZ = -1.0f;
    }
    else {
        camera.speedZ = 0;
    }
   
}

void mouse_callback(GLFWwindow* window,double xPos,double yPos) {
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = FALSE;
    }
    
    float deltaX, deltaY;
    deltaX = xPos - lastX;
    deltaY = yPos - lastY;

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(deltaX, deltaY);
}
