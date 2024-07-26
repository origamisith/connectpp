#include "board.h"
#include <json/value.h>
#include <sstream>

void board::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
	std::string cop(message);
	if(cop == "") return;

	Json::Value input;
	Json::CharReaderBuilder builder;
	std::string errs;
	std::istringstream is(message);
	bool ok = parseFromStream(builder, is, &input, &errs);
	if(!ok || input["HEADERS"] == "" || input["HEADERS"]["HX-Trigger"] == "") {
		wsConnPtr->send("Could not parse message sent by HTMX: " + errs);
		wsConnPtr->send(cop);
		return;
	}
	std::string id = input["HEADERS"]["HX-Trigger"].asString();
	wsConnPtr->send("<div class='box red' id=" + id + "></div>");
}

void board::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
}

void board::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
}
