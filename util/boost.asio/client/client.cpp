// boost_1_73_0/doc/html/boost_asio/example/cpp11/echo/blocking_tcp_echo_client.cpp

//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::socket s(io_context);
    tcp::resolver resolver(io_context);
    boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));

    while (1) {
      //std::cout << "Enter message: ";
      char request[max_length] = "hello client 1"; //
      //char request[max_length] = "hello client 2"; //
      //std::cin.getline(request, max_length);
      size_t request_length = std::strlen(request);
      boost::asio::write(s, boost::asio::buffer(request, request_length));

      char reply[max_length];
      size_t reply_length = boost::asio::read(s,
          boost::asio::buffer(reply, 26)); //
      //std::cout << "Reply is: ";
      std::cout.write(reply, reply_length) << std::endl;
      //std::cout << "\n";
      sleep(1);
    }

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

/*

terminal client 1:

$ ./a1 192.168.1.97 10240
hello client 1 from server
hello client 1 from server
hello client 1 from server
hello client 1 from server
hello client 1 from server
hello client 1 from server
hello client 1 from server
hello client 1 from server
^C


terminal client 2:

$ ./a2 192.168.1.97 10240
hello client 2 from server
hello client 2 from server
hello client 2 from server
hello client 2 from server
hello client 2 from server
hello client 2 from server
hello client 2 from server
^C

*/
