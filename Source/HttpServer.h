//
// Copyright (c) 2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: HTTP server, small
//
//------------------------------------------------------------------------------

#if BEAST_SERVER == 1

//#include <boost/beast.hpp>
//#include <boost/container/detail/workaround.hpp>
#include "../JuceLibraryCode/JuceHeader.h"
#include "Listeners.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

class http_connection : public std::enable_shared_from_this<http_connection>, public HttpServerListener
{
public:
	http_connection(boost::asio::ip::tcp::socket socket);

	// Initiate the asynchronous operations associated with the connection.
	void start();

	void addInterfaceListener(InterfaceListener* const l) { interfaceListeners.add(l); };
	void removeInterfaceListener(InterfaceListener* const l) { interfaceListeners.remove(l); };
	ListenerList <InterfaceListener> interfaceListeners;
private:
	// The socket for the currently connected client.
	boost::asio::ip::tcp::socket socket_;

	// The buffer for performing reads.
	boost::beast::flat_buffer buffer_{ 8192 };

	// The request message.
	boost::beast::http::request<boost::beast::http::dynamic_body> request_;

	// The response message.
	boost::beast::http::response<boost::beast::http::dynamic_body> response_;

	// The timer for putting a deadline on connection processing.
	boost::asio::basic_waitable_timer<std::chrono::steady_clock> deadline_{
		socket_.get_executor().context(), std::chrono::seconds(60) };

	// Asynchronously receive a complete request message.
	void read_request();

	// Determine what needs to be done with the request message.
	void process_request();

	// Construct a response message based on the program state.
	void create_response();

	// Asynchronously transmit the response message.
	void write_response();

	// Check whether we have spent enough time on this connection.
	void check_deadline();
};


class HttpServer : public Thread
{
public:
	HttpServer();
	~HttpServer();

	void addInterfaceListener(InterfaceListener* const l) { listener = (l); };

	InterfaceListener* listener;
	int returnValue;
	void run();
private:
	boost::asio::io_context ioc{ 1 };

	// "Loop" forever accepting new connections.
	void http_server(boost::asio::ip::tcp::acceptor& acceptor, boost::asio::ip::tcp::socket& socket)
	{
		acceptor.async_accept(socket, [&](boost::beast::error_code ec)
		{
			if (!ec)
			{
				std::shared_ptr<http_connection> connection = std::make_shared<http_connection>(std::move(socket));

				connection->addInterfaceListener(listener);
				connection->start();
			}
			http_server(acceptor, socket);
		});
	}
};

#endif // NO_BEAST
