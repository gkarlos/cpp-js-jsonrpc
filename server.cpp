#include <iostream>
#include <cxxtools/arg.h>
#include <cxxtools/log.h>
#include <cxxtools/json/rpcserver.h>
#include <cxxtools/eventloop.h>
#include <cxxtools/http/server.h>
#include <cxxtools/json/httpservice.h>

std::string echo(const std::string& message)
{
  std::cout << "echo( " << message << ")" << std::endl;
  return std::string("{\"type\": 1, \"value\":\"hello world\"}");
}

double add(double a1, double a2)
{
  std::cout << "add( " << a1 << ", " << a2 << ")";
  return a1 + a2;
}

bool finish(void) {
  std::cout << "exiting\n";
  //TODO send OK response
  std::exit(1);
  return true;
}

////////////////////////////////////////////////////////////////////////
// main
//
int main(int argc, char* argv[])
{
  try
  {
    // initialize logging - this reads the file log.xml from the current directory
    log_init();

    // read the command line options

    // option -i <ip-address> defines the ip address of the interface, where the
    // server waits for connections. Default is empty, which tells the server to
    // listen on all local interfaces
    cxxtools::Arg<std::string> ip(argc, argv, 'i');

    // option -p <number> specifies the port, where jsonrpc requests are expected.
    // The default port is 7004 here.
    cxxtools::Arg<unsigned short> port(argc, argv, 'p', 7004);

    // create an event loop
    cxxtools::EventLoop loop;
    // Define a http server first
    cxxtools::http::Server httpServer(loop, 8077);

    // for json rpc over http we need a service object
    cxxtools::json::HttpService service;

    // we register our functions
    service.registerFunction("add", add);
    service.registerFunction("echo", echo);
    service.registerFunction("finish", finish);
    
    // ... and register the service under a url
    httpServer.addService("/jsonrpc", service);
    ////////////////////////////////////////////////////////////////////////
    // Run

    // now start the servers by running the event loop
    loop.run();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}