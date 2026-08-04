#include "pch.h"

#include "Model.h"
#include "Texture.h"
#include "Renderer.h"
#include "Transform.h"
#include "EngineMath.h"

#include <iostream>

namespace ChiefEngine {
    bool Renderer::Initialize(const char* name, short windowWidth, short windowHeight) {
        m_window_size.x = windowWidth;
        m_window_size.y = windowHeight;

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_window = SDL_CreateWindow(name, windowWidth, windowHeight, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        SDL_SetRenderVSync(m_renderer, -1);

        return true;
    }

    void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) const {
        SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);
    }

    void Renderer::SetColorFloat(float red, float green, float blue, float alpha) const {
        SDL_SetRenderDrawColorFloat(m_renderer, red, green, blue, alpha);
    }

    void Renderer::SetColorVector(Color color, float alpha) const {
        SDL_SetRenderDrawColorFloat(m_renderer, color.r, color.g, color.b, alpha);
    }

    void Renderer::Clear() const {
        SDL_RenderClear(m_renderer);
    }

    void Renderer::Present() const {
        SDL_RenderPresent(m_renderer);
    }

    void Renderer::DrawPoint(float x, float y) const {
        SDL_RenderPoint(m_renderer, x, y);
    }

    void Renderer::ShutDown() const {
        TTF_Quit();
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Renderer::DrawRect(const SDL_FRect* rectangle) const {
        SDL_RenderRect(m_renderer, rectangle);
    }

    void Renderer::DrawFillRect(const SDL_FRect* rectangle) const {
        SDL_RenderFillRect(m_renderer, rectangle);
    }

    void Renderer::DrawFillRect(float x, float y, float w, float h) const {
        SDL_FRect rectangle{ x, y, w, h };
        SDL_RenderFillRect(m_renderer, &rectangle);
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2) const {
        SDL_RenderLine(m_renderer, x1, y1, x2, y2);
    }

    void Renderer::DrawMesh(const class Mesh& mesh, const struct Transform& transform) const {
        SetColor((Uint8)mesh.GetColor().r, (Uint8)mesh.GetColor().g, (Uint8)mesh.GetColor().b);

        auto& points = mesh.GetPoints();
        auto numPoints = mesh.GetPoints().size();

        for (int index = 0; (index + 1) < numPoints; index++) {
            Vector2 v1 = points[index];
            Vector2 v2 = points[index + 1];

            v1 *= transform.scale;
            v2 *= transform.scale;

            v1 = v1.Rotate(transform.rotation * DEGREE_TO_RADIAN);
            v2 = v2.Rotate(transform.rotation * DEGREE_TO_RADIAN);

            v1 += transform.position;
            v2 += transform.position;

            DrawLine(v1.x, v1.y,v2.x, v2.y);
        }
    }

    void Renderer::DrawModel(const class Model& model, const struct Transform& transform) const {
        for (auto mesh : model.GetMeshes()) {
            DrawMesh(mesh, transform);
        }
    }

    void Renderer::DrawText(float x, float y, std::string string) const {
        SDL_RenderDebugText(m_renderer, x, y, string.c_str());
    }

    void Renderer::DrawTexture(Texture* texture, float x, float y) {
        Vector2 size = texture->GetSize();

        SDL_FRect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.w = size.x;
        destRect.h = size.y;

        // https://wiki.libsdl.org/SDL3/SDL_RenderTexture
        SDL_RenderTexture(m_renderer, texture->m_texture, NULL, &destRect);
    }
}
