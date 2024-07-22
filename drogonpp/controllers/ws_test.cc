#include "ws_test.h"
#include <json/value.h>
#include <sstream>
void ws_test::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
	std::string cop(message);
	if(cop == "") return;
	Json::Value input;
	Json::CharReaderBuilder builder;
	std::string errs;
	std::istringstream is(message);
	bool ok = parseFromStream(builder, is, &input, &errs);
	if(!ok) {
		wsConnPtr->send("Could not parse message sent by HTMX: " + errs);
		wsConnPtr->send(cop);
		return;
	}
	if(!input["chat_message"].isString()) {
		wsConnPtr->send("Could not parse chat message");
		return;
	}
	std::string m = input["chat_message"].asString();
	
	std::string html = R"(<p id="a_message">)" + m + R"(</p>
		<div id="notifications" hx-swap-oob="beforeend">
			Notification Received\n
		</div>)";
	Json::Value res;
	res["result"] = html;
	Json::Value hxRequest;
	hxRequest["HX-Request"] = "newMessage";
	res["HEADERS"] = hxRequest;
	wsConnPtr->sendJson(res);
}

void ws_test::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
}

void ws_test::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    // write your application logic here
}
