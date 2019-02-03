// CurbShifter Copyright 2019 Distributed under GPLv3
// Based on Example: HTTP server, small
// Copyright (c) 2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/boostorg/beast

#include "HttpServer.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

http_connection::http_connection(tcp::socket socket)
		: socket_(std::move(socket))
{
}

// Initiate the asynchronous operations associated with the connection.
void http_connection::start()
{
	read_request();
	check_deadline();
}

// Asynchronously receive a complete request message.
void http_connection::read_request()
{
	auto self = shared_from_this();

	http::async_read(
		socket_,
		buffer_,
		request_,
		[self](beast::error_code ec,
			std::size_t bytes_transferred)
	{
		boost::ignore_unused(bytes_transferred);
		if (!ec)
			self->process_request();
	});
}

// Determine what needs to be done with the request message.
void http_connection::process_request()
{
	response_.version(request_.version());
	response_.keep_alive(false);

	switch (request_.method())
	{
	case http::verb::get:
		response_.result(http::status::ok);
		response_.set(http::field::server, "Beast");
		create_response();
		break;

	default:
		// We return responses indicating an error if
		// we do not recognize the request method.
		response_.result(http::status::bad_request);
		response_.set(http::field::content_type, "text/plain");
		beast::ostream(response_.body())
			<< "Invalid request-method '"
			<< request_.method_string().to_string()
			<< "'";
		break;
	}

	write_response();
}

// Construct a response message based on the program state.
void http_connection::create_response()
{
	String targetStr(request_.target().to_string());
	if (targetStr.startsWith("/hotwallet?"))
	{
		StringArray arguments = StringArray::fromTokens(targetStr.fromFirstOccurrenceOf("?", false, true), "&", "");
		String requestHeader;
		String recipient;
		String amountNQT;
		String feeNQT;
		String msg;
		String notifierURL;
		bool encrypted = false;
		
		for (int i = 0; i < arguments.size(); i++)
		{
			if (arguments[i].startsWith("requestHeader"))
				requestHeader = URL::removeEscapeChars(arguments[i].fromFirstOccurrenceOf("requestHeader=", false, true));
			if (arguments[i].startsWith("recipient"))
				recipient = URL::removeEscapeChars(arguments[i].fromFirstOccurrenceOf("recipient=", false, true));
			if (arguments[i].startsWith("amountNQT"))
				amountNQT = arguments[i].fromFirstOccurrenceOf("amountNQT=", false, true);
			if (arguments[i].startsWith("feeNQT"))
				feeNQT = arguments[i].fromFirstOccurrenceOf("feeNQT=", false, true);
			if (arguments[i].startsWith("msg"))
				msg = URL::removeEscapeChars(arguments[i].fromFirstOccurrenceOf("msg=", false, true));
		//	if (arguments[i].startsWith("notifierURL"))
		//		notifierURL = URL::removeEscapeChars(arguments[i].fromFirstOccurrenceOf("notifierURL=", false, true));
			if (arguments[i].startsWith("encrypted"))
				encrypted = arguments[i].fromFirstOccurrenceOf("encrypted=", false, true).compareIgnoreCase("true") ||
							 arguments[i].fromFirstOccurrenceOf("encrypted=", false, true).compareIgnoreCase("1");
		}
		interfaceListeners.call(&InterfaceListener::SetupTransaction, requestHeader, recipient, amountNQT, feeNQT, msg, encrypted);
		
		response_.set(http::field::content_type, "text/html");
		response_.set(http::field::access_control_allow_origin, "*"); // Access-Control-Allow-Origin
		beast::ostream(response_.body()) << "{\"response\":\"OK\"}";
	}
	else
	{
		response_.result(http::status::not_found);
		response_.set(http::field::content_type, "text/plain");
		beast::ostream(response_.body()) << "File not found\r\n";
	}
}

// Asynchronously transmit the response message.
void http_connection::write_response()
{
	auto self = shared_from_this();

	response_.set(http::field::content_length, response_.body().size());

	http::async_write(
		socket_,
		response_,
		[self](beast::error_code ec, std::size_t)
	{
		self->socket_.shutdown(tcp::socket::shutdown_send, ec);
		self->deadline_.cancel();
	});
}

// Check whether we have spent enough time on this connection.
void http_connection::check_deadline()
{
	auto self = shared_from_this();

	deadline_.async_wait(
		[self](beast::error_code ec)
	{
		if (!ec)
		{
			// Close socket to cancel any outstanding operation.
			self->socket_.close(ec);
		}
	});
}

HttpServer::HttpServer() : Thread("HttpServer"), returnValue(0)
{
}

HttpServer::~HttpServer()
{
	ioc.stop();
	stopThread(5000);
}

void HttpServer::run()
{
	try
	{
		auto const address = net::ip::make_address("127.0.0.1"); // only localhost
		unsigned short port = 41137;

		tcp::acceptor acceptor{ ioc, {address, port} };
		tcp::socket socket{ ioc };
		http_server(acceptor, socket);

		ioc.run();
	}
	catch (std::exception const& e)
	{
		//std::cerr << "Error: " << e.what() << std::endl;
		returnValue = EXIT_FAILURE;
	}
}
