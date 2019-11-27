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
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Cylinder.h"
#include "ellipse.h"
#include "Parallelogram.h"
#include "LightCube.h"
#include "box.h"
#define IMAGENAME "awesomeface.png"

#include "Color.h"

#include "Sphere.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;


// camera
Camera g_camera(glm::vec3(0.0f, 0.0f, 18.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 10.0f;    // time between current frame and last frame
float lastFrame = 0.0f;
float g_angle = 95.0f;
float g_yaw = 1.0;
float g_pitch = 1.0;



int g_tex_flag = 0;
int g_poly_flag = 0;
int g_perspective = 1;
int g_bottom_flag = 1;
int g_size = 1;
bool g_resize = false;
const int MAX_ITEMS = 4;
int g_light = 0;

// lighting
float g_l_dist = 7;
float g_l_zh = 0;
float g_l_y = 0;
int g_light_flag = 1;
glm::vec3 lightPos(g_l_dist * cos(g_l_zh), g_l_y, g_l_dist * sin(g_l_zh));
glm::vec3 lightPos2(g_l_dist * sin(g_l_zh), g_l_dist * cos(g_l_zh), g_l_y);


int main()
{
    int total_vertices[MAX_ITEMS];
    int vertices_to_render[MAX_ITEMS];
    unsigned int Axis_VAO, Axis_VBO;
    unsigned int Light_VAO, Light_VBO;
    unsigned int VBO[MAX_ITEMS];
    unsigned int VAO[MAX_ITEMS];
    unsigned int EBO[MAX_ITEMS];

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Testbed2 with lighting", nullptr, nullptr);
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
    Shader lightShader("lamp_vec.glsl", "lamp_frag.glsl");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    LightCube *Lc = new LightCube();
    Color *c[3];
    c[0] = new Color(0, 0, 1, 1);
    c[1] = new Color(0, 1, 1, 1);
    c[2] = new Color(1, 0, 0, 1);
    Axes ax(1.5);
    ax.set_symmetric(1);
    ax.gen_vertices();
    Sphere *yyy = new Sphere(68.8, 36, 36, false, c);

    c[0] = new Color(0, 0, 1, 1);
    c[1] = new Color(1, 1, .02, 1);
    c[2] = new Color(0, 1, 0, 1);

    Sphere *yy = new Sphere(1.5, 72, 72, true, c);
    c[0] = new Color(0, 0, 1, 1);
    c[1] = new Color(.5, .5, 1, 1);
    c[2] = new Color(.8, .5, 1, 1);
    int cyl_count = 6;
    Cylinder *tail_segments[cyl_count];
    for (int i = 0; i < cyl_count; i++) {
        tail_segments[i] = new Cylinder(1.25, 1, 36, 2, 0, 0, 0);
        tail_segments[i]->gen_vertices();
        tail_segments[i]->rotate(0, 90);
        tail_segments[i]->translate(glm::vec3(0, -1 - i * 2, -.85));
    }

    Sphere *ey1 = new Sphere(.5, 72, 18, true, c);
    Sphere *ey2 = new Sphere(.5, 72, 18, true, c);
    ey1->rotate(0, 105);
    ey1->rotate(1, 15);
    ey1->translate(glm::vec3(1, 4, .45));

    ey2->rotate(0, 105);
    ey2->rotate(1, -15);
    ey2->translate(glm::vec3(-1, 4, .45));


    float y_off = 4.95;
    Box *bb = new Box(90, 2, .25, .0625, 0, 0, 0);
    bb->gen_vertices();
    bb->translate(glm::vec3(-1, y_off, -1.25));

    Box *bb2 = new Box(90, 2, .25, .0625, 0, 0, 0);
    bb2->gen_vertices();
    bb2->translate(glm::vec3(-1, y_off, -1.75));

    Box *bb3 = new Box(90, .25, .0625, .5, 0, 0, 0);
    bb3->gen_vertices();

    bb3->rotate(0, 180);
    bb3->rotate(2, 90);
    bb3->translate(glm::vec3(-1, y_off, -1.1875));


    Box *bb4 = new Box(90, .25, .0625, .5625, 0, 0, 0);
    bb4->gen_vertices();
    bb4->rotate(0, 180);
    bb4->rotate(2, 90);
    bb4->translate(glm::vec3(1., y_off, -1.1875));

    c[0] = new Color(0, 0, 0, 1);
    c[1] = new Color(0, 0, 0, 1);
    c[2] = new Color(0, 0, 0, 1);

    Box *back = new Box(90, 2, .5625, .005, 0, 0, 0, c);
    back->gen_vertices();
    back->rotate(0, -90);
    back->translate(glm::vec3(-1, y_off, -1.1875));




    Cylinder *cc = new Cylinder(1.5, 1.125, 36, 4, 0, 0, 0);
    cc->gen_vertices();
    cc->rotate(0, 90.0);
    cc->translate(glm::vec3(0., 3., -.85));

    Ellipse *xxx[MAX_ITEMS];

    int TEETH = 9;
    Polyg *teeth[TEETH];
    float t_z = -1.70;
    float t_y = 5.0;
    teeth[0] = new Polyg(.0625, 36, .27);
    teeth[0]->gen_vertices();
    teeth[0]->translate(glm::vec3(0, t_y, t_z));

    teeth[1] = new Polyg(.0625, 36, .27);
    teeth[1]->gen_vertices();
    teeth[1]->translate(glm::vec3(-.25, t_y, t_z));


    teeth[2] = new Polyg(.0625, 36, .27);
    teeth[2]->gen_vertices();
    teeth[2]->rotate(0, -15);
    teeth[2]->translate(glm::vec3(-.45, t_y, t_z));

    teeth[3] = new Polyg(.0625, 36, .27);
    teeth[3]->gen_vertices();
    teeth[3]->rotate(0, -22);
    teeth[3]->translate(glm::vec3(-.65, t_y + t_y * sin(-22), t_z));


    teeth[4] = new Polyg(.0625, 36, .27);
    teeth[4]->gen_vertices();
    teeth[4]->rotate(0, -22);
    teeth[4]->translate(glm::vec3(.65, t_y + t_y * sin(-22), t_z));

    teeth[5] = new Polyg(.0625, 36, .27);
    teeth[5]->gen_vertices();
    teeth[5]->rotate(0, -27);
    teeth[5]->translate(glm::vec3(.45, t_y + t_y * sin(-27), t_z));

    teeth[6] = new Polyg(.0625, 36, .27);
    teeth[6]->gen_vertices();
    teeth[6]->rotate(0, -22);
    teeth[6]->translate(glm::vec3(.31, t_y + t_y * sin(-22), t_z));

    teeth[7] = new Polyg(.06, 36, .28);
    teeth[7]->gen_vertices();
    teeth[7]->rotate(0, -29);
    teeth[7]->translate(glm::vec3(.73, t_y + t_y * sin(-29), t_z));

    teeth[8] = new Polyg(.06, 36, .28);
    teeth[8]->gen_vertices();
    teeth[8]->rotate(0, -20);
    teeth[8]->translate(glm::vec3(-.83, t_y + t_y * sin(-20), t_z));



    float *vertices[MAX_ITEMS];

    for (int i = 0; i < MAX_ITEMS; i++) {
        if (i < 2) {
            xxx[i] = new Ellipse(2.5 - (5 * i), .5, .25, 2.5, .5, 2, 32);
            xxx[i + 2] = new Ellipse(2.5 - (5 * i), 1.5, .25, 2.5, .5, 2, 32);
            xxx[i + 2]->set_color(.25, 1, .75, .4, 1);
            xxx[i + 2]->set_color(.5, 0, .5, .9, 0);
            xxx[i + 2]->set_color(1, 1, .5, .9, 2);
        }

        xxx[i]->gen_vertices();
        vertices[i] = xxx[i]->get_vertices();
        indices[i] = xxx[i]->get_indices();
        total_vertices[i] = xxx[i]->get_vertex_count();
    }
    xxx[0]->rotate(2, 20);
    xxx[1]->rotate(2, -20);
    xxx[2]->rotate(2, -20);
    xxx[3]->rotate(2, 20);
    xxx[1]->translate(glm::vec3(0, 1.05, 0));
    xxx[0]->translate(glm::vec3(0, 1.05, 0));

    yy->translate(glm::vec3(0, 3.5, -.85));



    float *axes_verts = ax.get_vertices();

    for (int i = 0; i < MAX_ITEMS; i++) {
        glGenVertexArrays(1, &VAO[i]);
        glGenBuffers(1, &VBO[i]);
        glGenBuffers(1, &EBO[i]);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * xxx[i]->get_vertex_size(), vertices[i], GL_STATIC_DRAW);

        glCheckError();
        // Position attribute
        glVertexAttribPointer(0, xxx[i]->VERTEX_SIZE, GL_FLOAT, GL_FALSE,
                              (xxx[i]->VERTEX_SIZE + xxx[i]->COLOR_SIZE + xxx[i]->TEXTURE_SIZE + xxx[i]->NORMAL_SIZE) *
                              sizeof(float),
                              (void *) 0);
        glCheckError();
        glEnableVertexAttribArray(0);

        //color attribute
        glVertexAttribPointer(1, xxx[i]->COLOR_SIZE, GL_FLOAT, GL_FALSE,
                              (xxx[i]->VERTEX_SIZE + xxx[i]->COLOR_SIZE + xxx[i]->TEXTURE_SIZE + xxx[i]->NORMAL_SIZE) *
                              sizeof(float),
                              (void *) (xxx[i]->VERTEX_SIZE * sizeof(float)));
        glCheckError();
        glEnableVertexAttribArray(1);

        //texture attribute
        glVertexAttribPointer(2, xxx[i]->TEXTURE_SIZE, GL_FLOAT, GL_FALSE,
                              (xxx[i]->VERTEX_SIZE + xxx[i]->COLOR_SIZE + xxx[i]->TEXTURE_SIZE + xxx[i]->NORMAL_SIZE) *
                              sizeof(float),
                              (void *) ((xxx[i]->VERTEX_SIZE + xxx[i]->COLOR_SIZE) * sizeof(float)));
        glCheckError();
        glEnableVertexAttribArray(2);

        //normal attribute
        glVertexAttribPointer(3, xxx[i]->NORMAL_SIZE, GL_FLOAT, GL_FALSE,
                              (xxx[i]->VERTEX_SIZE + xxx[i]->COLOR_SIZE + xxx[i]->TEXTURE_SIZE + xxx[i]->NORMAL_SIZE) *
                              sizeof(float),
                              (void *) ((xxx[i]->VERTEX_SIZE + xxx[i]->COLOR_SIZE + xxx[i]->TEXTURE_SIZE) *
                                        sizeof(float)));
        glCheckError();
        glEnableVertexAttribArray(3);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }

    //Axis
    glGenVertexArrays(1, &Axis_VAO);
    glGenBuffers(1, &Axis_VBO);
    glBindVertexArray(Axis_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, Axis_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axes_verts) * ax.get_vertex_size(), axes_verts, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, ax.VERTEX_SIZE, GL_FLOAT, GL_FALSE,
                          (ax.VERTEX_SIZE + ax.COLOR_SIZE + ax.TEXTURE_SIZE) * sizeof(float), (void *) 0);
    glCheckError();

    //color attribute
    glVertexAttribPointer(1, ax.COLOR_SIZE, GL_FLOAT, GL_FALSE,
                          (ax.VERTEX_SIZE + ax.COLOR_SIZE + ax.TEXTURE_SIZE) * sizeof(float),
                          (void *) (ax.VERTEX_SIZE * sizeof(float)));
    glCheckError();
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(0);


    //LightCube
    glGenVertexArrays(1, &Light_VAO);
    glGenBuffers(1, &Light_VBO);
    glBindVertexArray(Light_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, Light_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Lc->get_vertex_size(), Lc->get_vertices(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, Lc->VERTEX_SIZE, GL_FLOAT, GL_FALSE,
                          (Lc->VERTEX_SIZE + Lc->NORMAL_SIZE + Lc->TEXTURE_SIZE + Lc->COLOR_SIZE) * sizeof(float),
                          (void *) 0);
    glCheckError();
    glEnableVertexAttribArray(0);


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

    ourShader.use();
    ourShader.setInt("texture1", 0);
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
        glCheckError();
        ourShader.use();
        ourShader.setInt("texflag", g_tex_flag);
        ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("lightColor2", 1.0f, .25f, .25f);
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


        if (g_resize) {
            g_resize = false;
            for (int i = 0; i < MAX_ITEMS; i++) {
                xxx[i]->increment(g_size);
                xxx[i]->gen_vertices();
                vertices[i] = xxx[i]->get_vertices();
                total_vertices[i] = xxx[i]->get_vertex_count();
                glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * xxx[i]->get_vertex_size(), vertices[i],
                             GL_STATIC_DRAW);
            }
        }

        //-------------------------------------------- perspective
        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
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
            model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
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

        for (int i = 0; i < MAX_ITEMS; i++) {
            //----------------------------------------------
            if (g_bottom_flag == 1) {
                vertices_to_render[i] = total_vertices[i];
            } else {
                if (xxx[i]->has_bottom()) {
                    vertices_to_render[i] = total_vertices[i] / 2;
                } else {
                    vertices_to_render[i] = total_vertices[i];
                }
            }
            // render

            glBindVertexArray(VAO[i]);
            glDrawArrays(GL_TRIANGLES, 0, vertices_to_render[i]);

        }
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glDrawElements(GL_TRIANGLES, xxx.get_vertex_count(), GL_UNSIGNED_INT, 0);


        // sphere
        yyy->draw();
        bb->draw();
        cc->draw();
        yy->draw();
        ey1->draw();
        ey2->draw();
        for (int i = 0; i < cyl_count; i++) {
            tail_segments[i]->draw();
        }
        bb2->draw();
        bb3->draw();
        bb4->draw();
        back->draw();
        for (int i = 0; i < TEETH; i++) {
            teeth[i]->draw();
        }

        // Axes
            glBindVertexArray(Axis_VAO);
            glDrawArrays(GL_LINES, 0, ax.get_vertex_count());


        // Light
        lightShader.use();
//        view = glm::mat4(1.0f);
//        projection = glm::perspective(glm::radians(g_camera.Zoom), (float) dims[2] / (float) dims[3],.1f, 100.0f);
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(.05f));
        lightShader.setMat4("model", model);
        glCheckError();
        glBindVertexArray(Light_VAO);
        glCheckError();
        glDrawArrays(GL_TRIANGLES, 0, Lc->get_vertex_count());
        glCheckError();

        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    for (int i = 0; i < MAX_ITEMS; i++) {
        glDeleteVertexArrays(1, &VAO[i]);
        glDeleteBuffers(1, &VBO[i]);
    }
    yyy->deletebuffers();
    yy->deletebuffers();
    bb->delete_buffers();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
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

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        switch (g_bottom_flag) {
            case 0:
                g_bottom_flag = 1;
                break;
            case 1:
                g_bottom_flag = 0;
                break;
            default:
                break;

        }

    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        g_light_flag *= -1;
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) { //< key
        g_l_zh -= .1;
        g_l_zh = fmod(g_l_zh, 360.0);
        std::cout << g_l_zh;
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) { //> key
        g_l_zh += .1;
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

    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {   //+
        g_size = 1;
        g_resize = true;
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {   //+
        g_size = -1;
        g_resize = true;
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
        g_pitch += 1.5;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        g_pitch -= 1.5;

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




