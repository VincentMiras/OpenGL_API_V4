#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "game.h"
#include "board.h"



using namespace std;

int main()
{
    string path = "/home/VIncent/tp_cours/OpenGL_API_V4";
    /////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


    /////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //définition de la taille de la fenêtre
    int width=600;
    int height=600;

    //On récupère les dimensions de l'écran pour créer la fenètre
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);

    //Enfin on crée la fenêtre
    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL_API",NULL,NULL);
    glfwSwapInterval(1);
    //On vérifie que l'initialisation a bien marché
    if (window==NULL){
        fprintf(stderr, "Erreur lors de la création de la fénêtre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);



    /////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Initialisation de GLEW
    glewExperimental=true;
    if (glewInit() != GLEW_OK){
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

    /////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;


    /////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader(path+"/shaders/SimpleVertexShader.vertexshader", path+"/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

    /////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

    /////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    NavigationControls controls(window, &cam);

    /////////////////////////Création des formes à afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    std::vector<glm::vec3> vb_board = {
        glm::vec3(-0.8f,  0.0f, -0.8f),
        glm::vec3( 0.8f,  0.0f, -0.8f),
        glm::vec3( 0.8f,  0.0f, 0.8f),
        glm::vec3(-0.8f,  0.0f, -0.8f),
        glm::vec3(-0.8f,  0.0f, 0.8f),
        glm::vec3( 0.8f,  0.0f, 0.8f)
    };
    std::vector<glm::vec3> vb_bordure = {
        glm::vec3(-0.8f, -0.2f, -0.8f),
        glm::vec3( 0.8f, -0.2f, -0.8f),
        glm::vec3( 0.8f, -0.2f,  0.8f),
        glm::vec3(-0.8f, -0.2f, -0.8f),
        glm::vec3(-0.8f, -0.2f,  0.8f),
        glm::vec3( 0.8f, -0.2f,  0.8f),

        glm::vec3(-0.8f, -0.2f, -0.8f),
        glm::vec3(-0.8f,  0.0f, -0.8f),
        glm::vec3( 0.8f, -0.2f, -0.8f),
        glm::vec3( 0.8f,  0.0f, -0.8f),
        glm::vec3(-0.8f,  0.0f, -0.8f),
        glm::vec3( 0.8f, -0.2f, -0.8f),

        glm::vec3(-0.8f, -0.2f,  0.8f),
        glm::vec3( 0.8f, -0.2f,  0.8f),
        glm::vec3(-0.8f,  0.0f,  0.8f),
        glm::vec3( 0.8f,  0.0f,  0.8f),
        glm::vec3( 0.8f, -0.2f,  0.8f),
        glm::vec3(-0.8f,  0.0f,  0.8f),

        glm::vec3( 0.8f, -0.2f, -0.8f),
        glm::vec3( 0.8f, -0.2f,  0.8f),
        glm::vec3( 0.8f,  0.0f, -0.8f),
        glm::vec3( 0.8f,  0.0f,  0.8f),
        glm::vec3( 0.8f, -0.2f,  0.8f),
        glm::vec3( 0.8f,  0.0f, -0.8f),

        glm::vec3(-0.8f, -0.2f, -0.8f),
        glm::vec3(-0.8f, -0.2f,  0.8f),
        glm::vec3(-0.8f,  0.0f, -0.8f),
        glm::vec3(-0.8f,  0.0f,  0.8f),
        glm::vec3(-0.8f, -0.2f,  0.8f),
        glm::vec3(-0.8f,  0.0f, -0.8f)
    };

    std::vector<glm::vec2> g_uv_buffer_data = {
        glm::vec2( 0,1),
        glm::vec2( 1,1),
        glm::vec2( 1,0),
        glm::vec2( 0,1),
        glm::vec2( 0,0),
        glm::vec2( 1,0)
    };

    std::vector<glm::vec2> g_uv_buffer_data_bord = {
        glm::vec2( 0, 0),
        glm::vec2( 1, 0),
        glm::vec2( 1, 1),
        glm::vec2( 0, 0),
        glm::vec2( 0, 1),
        glm::vec2( 1, 1),

        glm::vec2( 0, 0),
        glm::vec2( 0, 1),
        glm::vec2( 1, 0),
        glm::vec2( 1, 1),
        glm::vec2( 0, 1),
        glm::vec2( 1, 0),

        glm::vec2( 0, 0),
        glm::vec2( 1, 0),
        glm::vec2( 0, 1),
        glm::vec2( 1, 1),
        glm::vec2( 1, 0),
        glm::vec2( 0, 1),

        glm::vec2( 0, 0),
        glm::vec2( 1, 0),
        glm::vec2( 0, 1),
        glm::vec2( 1, 1),
        glm::vec2( 1, 0),
        glm::vec2( 0, 1),

        glm::vec2( 0, 0),
        glm::vec2( 1, 0),
        glm::vec2( 0, 1),
        glm::vec2( 1, 1),
        glm::vec2( 1, 0),
        glm::vec2( 0, 1),

        glm::vec2( 0, 0),
        glm::vec2( 1, 0),
        glm::vec2( 0, 1),
        glm::vec2( 1, 1),
        glm::vec2( 1, 0),
        glm::vec2( 0, 1),
    };

    std::string texture_blanc = path+"/textures/marbre_white.jpg";
    std::string texture_noir = path+"/textures/marbre_black.jpg";

    Object o(vb_board, g_uv_buffer_data, path+"/textures/damier2.jpg");
    Object ob(vb_bordure, g_uv_buffer_data_bord, path+"/textures/bois.jpg");

    Game partie=Game();
    partie.initialise_game();


    /////////////////////////Création de la matrice MVP/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cam.computeMatrices(width, height);
    glm::mat4 m = o.getModelMatrix();
    glm::mat4 v = cam.getViewMatrix();
    glm::mat4 p = cam.getProjectionMatrix();

    glm::mat4 mvp = p*v*m;

    shader.setUniformMat4f("MVP", mvp);


    /////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //On indique la couleur de fond
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //On autorise les tests de profondeur

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    float lastTime = glfwGetTime();
    float currentTime, deltaTime;

    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)){
        currentTime = glfwGetTime();
        deltaTime = currentTime-lastTime;
        lastTime = currentTime;

        controls.update(deltaTime, &shader);
        cam.computeMatrices(width, height);
        m = o.getModelMatrix();
        v = cam.getViewMatrix();
        p = cam.getProjectionMatrix();

        mvp = p*v*m;
        shader.setUniformMat4f("MVP", mvp);

        ////////////////On commence par vider les buffers///////////////
        renderer.Clear();
        renderer.Draw(va, o, shader);
        renderer.Draw(va, ob, shader);

        for (Piece* piece:partie.etat_jeu.list_pieces){
            if (piece->color==PieceColor::WHITE){
                Object p(piece->getforme(), piece->getbuffer_image(), texture_blanc);
                renderer.Draw(va, p, shader);
            }
            else{
                Object p(piece->getforme(), piece->getbuffer_image(), texture_noir);
                renderer.Draw(va, p, shader);
            }
        }

        partie.Make_a_move();

        ////////////////Partie rafraichissement de l'image et des évènements///////////////
        //Swap buffers : frame refresh
        glfwSwapBuffers(window);
        //get the events
        glfwPollEvents();
    }
    glfwTerminate();




    return 0;
}
