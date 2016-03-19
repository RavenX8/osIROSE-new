#include "ccharserver.h"
#include "ccharisc.h"
#include "config.h"

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  size_t q_size = 1048576;
  spdlog::set_async_mode(q_size);
  auto console = spdlog::stdout_logger_mt("console");
  console->notice("Starting up server...");

  Core::Config& config = Core::Config::getInstance();
  Core::NetworkThreadPool::GetInstance(config.serverdata().maxthreads());

  CCharServer clientServer;
  CCharServer iscServer(true);
  CCharISC iscClient;
  iscClient.Init(config.char_server().loginip(), config.char_server().loginiscport());
  iscClient.SetLogin(true);

  clientServer.Init(config.serverdata().ip(), config.char_server().clientport());
  clientServer.Listen();
  clientServer.GetISCList().push_front((CCharISC*)&iscClient);

  iscServer.Init(config.serverdata().ip(), config.char_server().iscport());
  iscServer.Listen();
  iscClient.Connect();

  while (clientServer.IsActive()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  console->notice( "Server shutting down..." );
  Core::NetworkThreadPool::DeleteInstance();
  spdlog::drop_all();
  return 0;
}
