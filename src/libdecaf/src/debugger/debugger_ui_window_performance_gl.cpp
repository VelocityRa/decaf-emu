#include "debugger_ui_window_performance_gl.h"
#include "decaf_graphics.h"
#include "decaf_graphics_info.h"
#include "libgpu/gpu_opengldriver.h"
#include "libgpu/src/opengl/opengl_driver.h"
#include "libgpu/latte/latte_enum_as_string.h"

#include <imgui.h>
#include <glbinding/Meta.h>

namespace debugger
{

namespace ui
{

static const ImVec4
   TitleTextColor = HEXTOIMV4(0xFFFFFF, 1.0f);
static const ImVec4
   ValueTextColor = HEXTOIMV4(0xC3C3C3, 1.0f);

PerformanceWindowGL::PerformanceWindowGL(const std::string &name) :
   PerformanceWindow(name)
{
   auto debugInfo = reinterpret_cast<gpu::OpenGLDriver*>(decaf::getGraphicsDriver());
   mDebugInfo.reset(debugInfo->getGraphicsDebugInfoPtr());
}

void PerformanceWindowGL::draw()
{
   ImGui::PushStyleColor(ImGuiCol_WindowBg, HEXTOIMV4(0x000000, 1.0f));
   ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2{500, 255});

   // Draw framerate/frametime graphs
   PerformanceWindow::drawGraphs();

   auto drawTextAndValue = [](const char *text, auto val) {
      ImGui::TextColored(TitleTextColor, text);
      ImGui::SameLine();
      ImGui::TextColored(ValueTextColor, ": %d", val);
   };
   auto drawTextAndString = [](const char *text, std::string val) {
      ImGui::TextColored(TitleTextColor, text);
      ImGui::SameLine();
      ImGui::TextColored(ValueTextColor, ": %s", val);
   };

   if (!mDebugInfo)
      return;

   // Graphics info
   ImGui::Separator();
   ImGui::Text("\tGraphics Debugging Info:\n");

   ImGui::Columns(2);

   drawTextAndValue("Vertex Shaders", mDebugInfo->vertexShaders);
   drawTextAndValue("Pixel  Shaders", mDebugInfo->pixelShaders);
   drawTextAndValue("Fetch  Shaders", mDebugInfo->fetchShaders);

   ImGui::NextColumn();

   drawTextAndValue("Shader Pipelines", mDebugInfo->shaderPipelines);
   drawTextAndValue("Surfaces", mDebugInfo->pSurfaces ? mDebugInfo->pSurfaces->size() : 0);
   drawTextAndValue("Data Buffers", mDebugInfo->dataBuffers);

   ImGui::Columns(1);

   if (ImGui::TreeNode("Textures"))
   {
      for (auto& mapSurface : *mDebugInfo->pSurfaces)
      {
         auto surfaceId = std::to_string(mapSurface.first).c_str();
         auto& surface = mapSurface.second;
         auto& activeSurface = surface.active;

         if (ImGui::TreeNode(surfaceId))
         {
            ImGui::Columns(3);

            drawTextAndValue("Width", activeSurface->width);
            drawTextAndValue("Height", activeSurface->height);
            drawTextAndValue("Depth", activeSurface->depth);
            drawTextAndValue("Degamma", activeSurface->degamma);

            ImGui::NextColumn();

            drawTextAndString("NumFormat", latte::enumAsString(surface.dbgInfo.numFormat));
            drawTextAndString("Format", latte::enumAsString(surface.dbgInfo.format));
            drawTextAndString("FormatComp", latte::enumAsString(surface.dbgInfo.formatComp));
            drawTextAndString("IsDepthBuffer", activeSurface->isDepthBuffer ? "true" : "false");

            ImGui::NextColumn();

            drawTextAndString("R swizzle", glbinding::Meta::getString(activeSurface->swizzleR));
            drawTextAndString("G swizzle", glbinding::Meta::getString(activeSurface->swizzleG));
            drawTextAndString("B swizzle", glbinding::Meta::getString(activeSurface->swizzleB));
            drawTextAndString("A swizzle", glbinding::Meta::getString(activeSurface->swizzleA));

            ImGui::Columns(1);

            if (ImGui::TreeNode("Texture Data"))
            {
               ImGui::Image(reinterpret_cast<void*>(surface.active->object), ImVec2(activeSurface->width, activeSurface->height));
               ImGui::TreePop();
            }
            ImGui::TreePop();
         }
      }
   }
   ImGui::PopStyleColor();
   ImGui::PopStyleVar();

   ImGui::End();
}

} // namespace ui

} // namespace debugger
