#include <iostream>
#include "buttons.h"

// Add definition of your processing function here
void buttons::load_board(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) {
	std::cout << "Loading the board";
	HttpResponsePtr resp = HttpResponse::newHttpViewResponse("BoardView.csp");
	callback(resp);
}
