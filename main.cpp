// Dwight J. Browne
//@TODO: Add Axes
//@TODO: Add WASD keys


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


#define IMAGENAME "awesomeface.png"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float POINT_COUNT = 9;

int g_tex_flag = 0;
int g_poly_flag = 0;
int g_perspective = 0;
int g_bottom_flag = 1;

int main()
{

    int total_vertices;
    int vertices_to_render;
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
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Testbed2", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
//    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertex.shader", "fragment.shader");


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    Polyg xxx(1.0, POINT_COUNT);
    xxx.set_z_axis(.85);
    xxx.gen_vertices();
    xxx.print_vertices();
    xxx.print_indices();
    float *vertices = xxx.get_vertices();
    unsigned int *indices = xxx.get_indices();
    total_vertices = xxx.get_vertex_count();


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * xxx.get_vertex_size(), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * POINT_COUNT, indices, GL_STATIC_DRAW);
    glCheckError();

    // Position attribute
    glVertexAttribPointer(0, xxx.VERTEX_SIZE, GL_FLOAT, GL_FALSE,
                          (xxx.VERTEX_SIZE + xxx.COLOR_SIZE + xxx.TEXTURE_SIZE) * sizeof(float), (void *) 0);
    glCheckError();

    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, xxx.COLOR_SIZE, GL_FLOAT, GL_FALSE,
                          (xxx.VERTEX_SIZE + xxx.COLOR_SIZE + xxx.TEXTURE_SIZE) * sizeof(float),
                          (void *) (xxx.VERTEX_SIZE * sizeof(float)));
    glCheckError();

    glEnableVertexAttribArray(1);

    //texture attribute

    glVertexAttribPointer(2, xxx.TEXTURE_SIZE, GL_FLOAT, GL_FALSE,
                          (xxx.VERTEX_SIZE + xxx.COLOR_SIZE + xxx.TEXTURE_SIZE) * sizeof(float),
                          (void *) ((xxx.VERTEX_SIZE + xxx.COLOR_SIZE) * sizeof(float)));
    glCheckError();

    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


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

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
//        processInput(window);


        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        ourShader.setInt("texflag", g_tex_flag);
        ourShader.use();

        //-------------------------------------------- perspective
        // create transformations
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        ourShader.setInt("perspective", g_perspective);
        if (g_perspective) {
            model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);

        } else {
            projection = glm::ortho(-(float) SCR_WIDTH, (float) SCR_WIDTH, -(float) SCR_HEIGHT, (float) SCR_HEIGHT,
                                    0.1f, 100.0f);   //this is a cheat for now
        }
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        ourShader.setMat4("projection", projection);





        //----------------------------------------------
        if (g_bottom_flag == 1) {
            vertices_to_render = total_vertices;
        } else {
            vertices_to_render = total_vertices / 2;
        }

        // render
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3 * vertices_to_render);

//        glDrawElements(GL_TRIANGLES, 3 * POINT_COUNT, GL_UNSIGNED_INT, 0);
        glCheckError();

        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        g_tex_flag += 1;
        g_tex_flag %= 3;
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