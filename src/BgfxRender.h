#pragma once

#include <memory>
#include <Render.h>
#include <SDL2/SDL.h>
#include <bgfx/bgfx.h>

namespace DemensDeum::Bombov
{

    class BgfxRender : public Render
    {

    public:
        void setWindow(SDL_Window *window) override;
        virtual void setScene(std::shared_ptr<DemensDeum::Bombov::Scene> scene) override;
        virtual void render() override;

    private:
        struct Vertex3D_UV
        {
            float x;
            float y;
            float z;
            float u;
            float v;

            static void init()
            {
                Vertex3D_UV::ms_layout
                    .begin()
                    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                    .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
                    .end();
            };

            static bgfx::VertexLayout ms_layout;
        };

        std::vector<BgfxRender::Vertex3D_UV> verticesVectorFromMap(std::shared_ptr<Map> map);

        bgfx::TextureHandle loadTexture(const char *filepath);

        std::vector<char> vertexShaderCode;
        std::vector<char> fragmentShaderCode;
        std::vector<Vertex3D_UV> verticesVector;

        bgfx::ProgramHandle program;
        bgfx::VertexBufferHandle vertexBuffer;
        bgfx::IndexBufferHandle indexBuffer;
        std::shared_ptr<Scene> scene;
        SDL_Window *window;

        bgfx::UniformHandle u_modelMatrix;
        bgfx::UniformHandle u_viewMatrix;
        bgfx::UniformHandle u_projMatrix;

        bgfx::TextureHandle texture;
        bgfx::UniformHandle s_texture0;

        std::shared_ptr<Camera> camera;
    };

}