#include <memory>
#include <spdlog/spdlog.h>
#include "fuzztests.h"
#include "libcpu/cpu.h"
#include "libcpu/mem.h"

std::shared_ptr<spdlog::logger>
gLog;

int main(int argc, char *argv[])
{
   gLog = std::make_shared<spdlog::logger>("logger", std::make_shared<spdlog::sinks::stdout_sink_st>());
   gLog->set_level(spdlog::level::debug);

   mem::initialise();
   cpu::initialise();

   auto result = executeFuzzTests() ? 0 : 1;

   system("PAUSE");
   return result;
}
