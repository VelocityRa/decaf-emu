#pragma once

#include <cstdint>
#include <unordered_map>

namespace opengl
{

struct SurfaceBuffer;

} // namespace opengl

namespace decaf
{

struct GraphicsDebugInfoGL {
   GraphicsDebugInfoGL(): fetchShaders(0), vertexShaders(0), pixelShaders(0), shaderPipelines(0), pSurfaces(nullptr), dataBuffers(0)
   {
   }

   GraphicsDebugInfoGL(uint64_t fetch_shaders, uint64_t vertex_shaders, uint64_t pixel_shaders, uint64_t shader_pipelines, std::unordered_map<uint64_t, opengl::SurfaceBuffer>* pSurfaces, uint64_t data_buffers)
      : fetchShaders(fetch_shaders),
        vertexShaders(vertex_shaders),
        pixelShaders(pixel_shaders),
        shaderPipelines(shader_pipelines),
        pSurfaces(pSurfaces),
        dataBuffers(data_buffers)
   {
   }

   uint64_t fetchShaders;
   uint64_t vertexShaders;
   uint64_t pixelShaders;

   uint64_t shaderPipelines;
   std::unordered_map<uint64_t, opengl::SurfaceBuffer>* pSurfaces;
   uint64_t dataBuffers;

   // TODO: Samplers?
};

} // namespace decaf
