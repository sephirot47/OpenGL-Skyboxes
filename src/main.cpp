#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <cstring>
#include <stdio.h>

#include "../include/RealEngine.h"

using namespace std;
using namespace glm;
using namespace RE;

const float width = 1500, height = 800;

GBuffer *gbuffer;
Mesh *mesh1, *mesh2, *mesh3;
Light *light, *light2;
Material *material1, *material2, *material3;
vec3 cameraRot, cameraPos;
SkyBox *skybox;
CubeTexture *skyCubeTexture;
Texture *tex;

void Init()
{
    glClearColor(0.0, 0.0, 0.3, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LEQUAL);

    tex = new Texture(width, height);

    mesh1 = new Mesh();
    mesh1->LoadFromFile("Assets/Models/luigi.obj");
    Texture *texture1 = new Texture("Assets/Textures/luigiD.jpg");
    material1 = new Material();
    material1->SetTexture(*texture1);

    mesh2 = new Mesh();
    mesh2->LoadFromFile("Assets/Models/gordaco.obj");
    Texture *texture2 = new Texture("Assets/Textures/gordaco.bmp");
    material2 = new Material();
    material2->SetTexture(*texture2);

    mesh3 = new Mesh();
    mesh3->LoadFromFile("Assets/Models/quad.obj");
    Texture *texture3 = new Texture("Assets/Textures/wall.jpg");
    material3 = new Material();
    material3->SetTexture(*texture3);

    //Creamos el cielo
    Image *cm1, *cm2, *cm3, *cm4, *cm5, *cm6;
    cm1 = new Image("Assets/Textures/sky4/posx.tga");
    cm2 = new Image("Assets/Textures/sky4/negx.tga");
    cm3 = new Image("Assets/Textures/sky4/posy.tga");
    cm4 = new Image("Assets/Textures/sky4/negy.tga");
    cm5 = new Image("Assets/Textures/sky4/posz.tga");
    cm6 = new Image("Assets/Textures/sky4/negz.tga");

    skyCubeTexture = new CubeTexture();
    skyCubeTexture->SetFaceTexture(CubeTexture::CubeTextureFace::PositiveX, *cm1);
    skyCubeTexture->SetFaceTexture(CubeTexture::CubeTextureFace::NegativeX, *cm2);
    skyCubeTexture->SetFaceTexture(CubeTexture::CubeTextureFace::PositiveY, *cm3);
    skyCubeTexture->SetFaceTexture(CubeTexture::CubeTextureFace::NegativeY, *cm4);
    skyCubeTexture->SetFaceTexture(CubeTexture::CubeTextureFace::PositiveZ, *cm5);
    skyCubeTexture->SetFaceTexture(CubeTexture::CubeTextureFace::NegativeZ, *cm6);

    skybox = new SkyBox();
    skybox->SetCubeTexture(*skyCubeTexture);
    //

    gbuffer = new GBuffer(width, height);

    light = new Light(DirectionalLight, width, height);
    light->SetPosition(vec3(10.0f, 0.5f, 10.0f));
    light->SetDirection(-light->GetPosition());
    light->SetColor(vec3(1.0f, 1.0f, 1.0f));
    light->SetIntensity(2.0f);

    light2 = new Light(PointLight, width, height);
    light2->SetPosition(vec3(0.0f, 0.0f, 2.0f));
    light2->SetDirection(-light2->GetPosition());
    light2->SetColor(vec3(1.0f, 0.0f, 0.0f));
    light2->SetIntensity(2.0f);
    light2->SetRange(2.0f);

    cameraPos = vec3(0, 0, 7.0f);
    cameraRot = vec3(0, 0, 0.0f);
}

float rot = 0.0f, sphereRot = 0.0f, appTime = 0.0f;

bool lightMode = false;

void RenderScene()
{
    appTime += 0.03f;
    sphereRot += 0.03f;
    light->SetPosition(vec3(sin(appTime) * 7.0f, 0.5f, 10.0f));
    light->SetDirection(-light->GetPosition());

    light2->SetRange((sin(appTime)*0.5+0.5) * 10.0f);
    light2->SetDirection(-light2->GetPosition());

    mat4 model(1.0f);
    vec3 axis(0.0, 1.0, 0.0), translate, scale;
    mat4 T = glm::translate(model,  translate);
    mat4 R = glm::rotate_slow(model, rot, axis);
    mat4 S = glm::scale(model, scale);

    gbuffer->ClearColorDepth();

    mat4 projection = perspective(45.0f * 3.1415f/180.0f, width/height, 1.0f, 150.0f);
    if(lightMode) projection = light2->GetProjection(width, height);

    model = mat4(1.0f);
    translate = vec3(sin(appTime) * 0.8f, 0.0f, 3.0f);
    scale = vec3(0.005f);
    T = glm::translate(model, translate);
    R = glm::rotate_slow(model, sphereRot, axis);
    S = glm::scale(model, scale);
    mesh1->SetModelMatrix(T * R * S);

    model = mat4(1.0f);
    translate = vec3(-0.0f, -0.3f, 0.0f);
    scale = vec3(0.02f);
    T = glm::translate(model, translate);
    R = glm::rotate_slow(model, 0.0f, axis);
    S = glm::scale(model, scale);
    mesh2->SetModelMatrix(T * R * S);

    model = mat4(1.0f);
    translate = vec3(0.0f, 0.5f, -4.0f);
    scale = vec3(0.005f);
    T = glm::translate(model, translate);
    R = glm::rotate_slow(model, 0.0f, axis);
    scale = vec3(6.0f);
    S = glm::scale(model, scale);
    mesh3->SetModelMatrix(T * R * S);

    model = mat4(1.0f);
    translate = vec3(0.0f, 0.0f, 0.0f);
    scale = vec3(50.0f);
    T = glm::translate(model, translate);
    R = glm::rotate_slow(model, sphereRot, axis);
    S = glm::scale(model, scale);
    skybox->GetMesh()->SetModelMatrix(T * R * S);

    mat4 view = mat4(1.0f);
    T = glm::translate(view, cameraPos);
    R = glm::rotate_slow(view, rot, axis);
    view = glm::inverse(T * R);
    if(lightMode) view = light2->GetView();

    glDisable(GL_CULL_FACE);
    //skybox->Render(*gbuffer, view, projection);
    glEnable(GL_CULL_FACE);
    gbuffer->ClearDepth();

    material1->SetShininess(50.0f);
    material1->SetSpecularColor(vec3(1.0, 1.0, 1.0));
    material2->SetSpecularColor(vec3(1.0, 1.0, 1.0));
    material3->SetSpecularColor(vec3(0.0, 0.0, 0.0));

    mesh1->Render(*gbuffer, *material1, view, projection);
    mesh2->Render(*gbuffer, *material2, view, projection);
    mesh3->Render(*gbuffer, *material3, view, projection);

    light->ClearBufferMeshShadow();
    light2->ClearBufferMeshShadow();

    light->ShadowMapMesh(*mesh1, width, height);
    light->ShadowMapMesh(*mesh2, width, height);
    light->ShadowMapMesh(*mesh3, width, height);

    light2->ShadowMapMesh(*mesh1, width, height);
    light2->ShadowMapMesh(*mesh2, width, height);
    light2->ShadowMapMesh(*mesh3, width, height);

    light->ApplyLight(*gbuffer, view, projection);
    light2->ApplyLight(*gbuffer, view, projection);

    gbuffer->RenderToScreen();
}

bool IsPressed(int keyCode)
{
    int n;
    const Uint8 *state = SDL_GetKeyboardState(&n);
    int i = SDL_GetScancodeFromKey(keyCode);
    if(i < n && n >= 1) return state[i] == 1;
    return false;
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* win;
    win = SDL_CreateWindow("Real Engine", 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_GLContext context;
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    context = SDL_GL_CreateContext(win);

    float totalTime = 0.0f;
    int frames = 0;

    Init();
    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            float camSpeed = 0.3f;
            if(event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN && IsPressed(SDLK_RIGHT)) cameraPos.x += camSpeed;
            if (event.type == SDL_KEYDOWN && IsPressed(SDLK_LEFT)) cameraPos.x -= camSpeed;
            if (event.type == SDL_KEYDOWN && IsPressed(SDLK_UP)) cameraPos.z -= camSpeed;
            if (event.type == SDL_KEYDOWN && IsPressed(SDLK_DOWN)) cameraPos.z += camSpeed;
            if (event.type == SDL_KEYDOWN && IsPressed(SDLK_s)) cameraPos.y -= camSpeed;
            if (event.type == SDL_KEYDOWN && IsPressed(SDLK_w)) cameraPos.y += camSpeed;
            if (event.type == SDL_KEYDOWN && IsPressed(SDLK_0)) lightMode = !lightMode;
            if (event.type == SDL_KEYDOWN && IsPressed(SDLK_1)) light->SetEnabled(!light->GetEnabled());
            if (event.type == SDL_KEYDOWN && IsPressed(SDLK_2)) light2->SetEnabled(!light2->GetEnabled());
        }

        float t = Time::GetMiliseconds();

        RenderScene();
        SDL_GL_SwapWindow(win);

        totalTime += Time::GetMiliseconds() - t;
        float fps = float(++frames)/totalTime;
        if(frames % 3 == 0) DbgLog(int(fps * 1000.0f) << " fps" );
        if(frames > 100) frames = totalTime = 0;
        //SDL_Delay(10);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
