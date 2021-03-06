// Dwight J. Browne
#include <iostream>
#include "primatives.h"
#include "glad.h"
#include <GLFW/glfw3.h>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "extra_funcs.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

#define IMAGENAME "subtle-white-feathers.png"
#ifdef __APPLE__
#define IMAGENAME2 "zanti.png"
#else
#define IMAGENAME2 "zanti2.png"
#endif


#include "Dragonfly.h"
#include "Color.h"

#include "Sphere.h"
#include "dflyGen.h"

void motion_gen();

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;


// camera
Camera g_camera(glm::vec3(6.0f, 6.0f, 18.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

// timing
float deltaTime = 10.0f;    // time between current frame and last frame
float lastFrame = 0.0f;
float g_angle = 0.0f;
float g_yaw = 1.0;
float g_pitch = 1.0;



int g_tex_flag = 0;
int g_poly_flag = 0;
int g_perspective = 1;
int g_light = 0;

// lighting
float g_l_dist = 7;
float g_l_zh = 0;
float g_l_y = 0;
int g_light_flag = 1;
glm::vec3 lightPos(g_l_dist * cos(g_l_zh), g_l_y, g_l_dist * sin(g_l_zh));
glm::vec3 lightPos2(g_l_dist * sin(g_l_zh), g_l_dist * cos(g_l_zh), g_l_y);

// objects
Dragonfly **dfly;
Dfly *flies = new Dfly();
int g_move = 1;    //wing motion flag
int g_motion = 1;
int g_pitch_flag = 1;
int g_motion_count = 0;
int g_motion_mod = 5000;
bool g_set_change = false;
int g_set_count = 0;
#ifdef __APPLE__
float g_pitch_const = .05;
float g_yaw_const = 0.025;
#else
float g_pitch_const = .025;
float g_yaw_const = 0.0125;
#endif


int main() {

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dwight Browne. Final Project CSCI5229", nullptr,
                                          nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);


    // Load Shaders
    // ------------------------------------
    Shader ourShader("vertex.glsl", "fragment.glsl");
    glCheckError();




    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    Color *c[3];
    c[0] = new Color(1, 0, 1, 1);
    c[1] = new Color(1, 1, 1, 1);
    c[2] = new Color(1, 0, 1, 1);
    Axes ax(4.5);
    ax.set_symmetric(1);
    ax.gen_vertices();

    Sphere *tent = new Sphere(68.8, 72, 72, false, c);
    dfly = flies->genFlies(&ourShader);



    // load and create a texture
    // -------------------------
    unsigned int texture1;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(IMAGENAME, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    unsigned int texture2;
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    data = stbi_load(IMAGENAME2, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    ourShader.use();

    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    glCheckError();
    ourShader.setInt("texture2", 1);
    glCheckError();
    ourShader.setInt("lightFlag", g_light);



    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {

        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glCheckError();
        ourShader.use();
        ourShader.setInt("texflag", g_tex_flag);
        ourShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("lightColor2", 1.0f, 1.0f, 1.0f);
        ourShader.setInt("material.diffuse", 0);
        ourShader.setInt("material.specular", 1);

        if (g_light_flag == 1) {
            g_l_zh = fmod(glfwGetTime(), 360.0);
        }
        lightPos[0] = g_l_dist * cos(g_l_zh);
        lightPos[2] = g_l_dist * sin(g_l_zh);
        lightPos[1] = g_l_y;

        lightPos2[0] = g_l_dist * sin(g_l_zh + 45);
        lightPos2[1] = g_l_dist * cos(g_l_zh);
        lightPos2[2] = g_l_y;

        ourShader.setVec3("lightPos", lightPos);
        ourShader.setInt("lightFlag", g_light);

        ourShader.setVec3("lightPos2", lightPos2);
        ourShader.setVec3("spotLight.position", lightPos2);
        ourShader.setVec3("viewPos", g_camera.Position);

        ourShader.setVec3("spotLight.direction", lightPos2);
        ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(.5f)));
        ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(.05f)));

        ourShader.setFloat("spotLight.constant", .050f);
        ourShader.setFloat("spotLight.linear", 0.01);
        ourShader.setFloat("spotLight.quadratic", 0.0032);

        ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);

        ourShader.setFloat("material.shininess", 32.0f);

        //-------------------------------------------- perspective
        // create transformations
        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 projection = glm::mat4(1.0f);
        ourShader.setInt("perspective", g_perspective);
        GLint dims[4] = {0};
        glGetIntegerv(GL_VIEWPORT, dims);

        glCheckError();

        if (g_perspective) {
            glm::mat4 projection = glm::perspective(glm::radians(g_camera.Zoom), (float) dims[2] / (float) dims[3],
                                                    0.1f, 100.0f);
            ourShader.setMat4("projection", projection);
            // camera/view transformation
            glm::mat4 view = g_camera.GetViewMatrix();
            ourShader.setMat4("view", view);
            // calculate the model matrix for each object and pass it to shader before drawing
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(g_angle), glm::vec3(1.0f, 1.0f, 0.5f));
            model = glm::rotate(model, glm::radians(g_yaw), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(g_pitch), glm::vec3(1, 0, 0));
            ourShader.setMat4("model", model);

        } else {
            projection = glm::ortho(-(float) dims[2], (float) dims[2], -(float) dims[3], (float) dims[3],
                                    0.1f, 100.0f);   //this is a cheat for now
            ourShader.setMat4("projection", projection);
        }


        for (int xx = 0; xx < flies->getFlyCount(); xx++) {
            dfly[xx]->draw(model, g_yaw, g_pitch, g_move, g_angle);
        }

//            dfly[0]->draw(model, g_yaw, g_pitch, g_move,g_angle);
//            dfly[3]->draw(model, g_yaw, g_pitch, g_move,g_angle);


        // Axes
        ax.draw();
        tent->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
        motion_gen();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    tent->deletebuffers();
    for (int xx = 0; xx < flies->getFlyCount(); xx++) {
        dfly[xx]->deletebuffers();
    }
//    dfly[0]->deletebuffers();
//    dfly[3]->deletebuffers();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void motion_gen() {
    if (g_motion == 1) {
        g_pitch += g_pitch_const * g_pitch_flag;
        g_yaw -= g_yaw_const * g_pitch_flag;

        g_motion_count++;
        if (g_motion_count % g_motion_mod == 0) {
            g_set_change = true;
        }
        if (g_set_change) {
            g_yaw -= .00125;
            g_pitch += .001335;
            g_set_count++;
        }

    if (g_set_count % 201 == 0) {
        g_set_change = false;
    }

    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        switch (g_poly_flag) {
            case 0:
                glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                break;
            case 1:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
            case 2:
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
            default:
                break;
        }
        g_poly_flag++;
        g_poly_flag %= 3;
    }


    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        g_light_flag *= -1;
    }


    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS) {
        g_pitch_const = g_pitch_const - .25 * g_pitch_const;
        g_yaw_const = g_yaw_const - .125 * g_yaw_const;
    }

    if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
        g_pitch_const = g_pitch_const + .25 * g_pitch_const;
        g_yaw_const = g_yaw_const + .25 * g_yaw_const;
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        g_motion *= -1;
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) { //< key
        g_l_zh += .1;
        g_l_zh = fmod(g_l_zh, 360.0);
    }

    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) { //< key
        if (g_move == 1) {
            g_move = 0;
        } else if (g_move == 0) {
            g_move = 1;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) { //> key
        g_l_zh -= .1;
        g_l_zh = fmod(g_l_zh, 360.0);

    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        switch (g_perspective) {
            case 0:
                g_perspective = 1;
                break;
            case 1:
                g_perspective = 0;
                break;
            default:
                break;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        g_light += 1;
        g_light %= 3;
    }


    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        g_tex_flag += 1;
        g_tex_flag %= 3;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        g_camera.ProcessKeyboard(FORWARD, deltaTime * 20);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        g_camera.ProcessKeyboard(BACKWARD, deltaTime * 20);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        g_camera.ProcessKeyboard(LEFT, deltaTime * 20);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        g_camera.ProcessKeyboard(RIGHT, deltaTime * 20);

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        g_pitch -= 1.5;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        g_pitch += 1.5;

    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        g_yaw -= 1.5;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        g_yaw += 1.5;
    }
    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
        g_camera.Position = glm::vec3(0.0f, 0.0f, 3.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
        g_angle -= 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        g_angle += 1.0;
    }




}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    GLint dims[4] = {0};
    glGetIntegerv(GL_VIEWPORT, dims);
    GLint fbWidth = dims[2];
    GLint fbHeight = dims[3];
    glViewport(0, 0, fbWidth, fbHeight);

}




